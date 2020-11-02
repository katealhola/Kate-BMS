
#include <Wire.h>

#include "config.h"


#ifdef OLED
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
//#include "OZ890.h"
#include "OLEDDisplayUi.h"
#endif

#ifdef TFT
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "TFT_eSPI.h"

#endif

#include <WiFi.h>
//#include <PubSubClient.h>
#include "FS.h"
#include <SD.h>
#include "SPIFFS.h"
#include "bms.h"
#include "ant_bms.h"
#include "configfile.h"
#include <ArduinoJson.h>


const char* ssid     = DEFAULT_SSID;
const char* password = DEFAULT_PASSWORD;


 #ifdef OZ890BMS
 void i2cTask( void * parameter );
 #endif

WiFiClient espClient;
//PubSubClient client(espClient);
ConfigFile configFile;

void displayInit();
void startUpDisplay();
void connectingDisplay();
#ifdef OLED
void statusDisplay();
void networkDisplay();
void barplot(SSD1306  &m );
void cellVoltagesDisplay();
#endif

#define LOGSIZE 100

#ifdef OLED
 // Initialize the OLED display using Wire library
SSD1306  display(0x3c, I2C_SDA, I2C_SCL);
#endif

#ifdef TFT
//Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
// Use hardware SPI
TFT_eSPI  display = TFT_eSPI();
int ILI9341_COLOR;
#define CUSTOM_DARK 0x4228 // Background color
void spiDisplayTask( void * parameter );
void uartBmsTask( void * parameter );

#endif

#include "logline.h"
#include "logfile.h"
#include "httpserver.h"
 

int packetCounter;
File logFile;
HttpServer httpServer;
int showConnected=0;

void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        showConnected=1;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        break;
    }
}



void setup() {

  Serial.begin(115200);
  Wire.begin(I2C_SDA,I2C_SCL,80000);

   pinMode(BUTTON ,INPUT); 
   digitalWrite(BUTTON, HIGH);

 //   Wire.begin(I2C_SDA,I2C_SCL,300000);


  if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");  
  } 
   configFile.loadConfiguration(CONFIGFILE);
   Serial.println(configFile.toString());


  displayInit();

 
  // Wire.setClock(300000); 
   Serial.println();

  startUpDisplay();


   logFile = SPIFFS.open(LOGFILE, FILE_APPEND);
    if(!logFile){
        Serial.println("- failed to open file for appending:"+String(LOGFILE));
        if(!logFile){
          Serial.println("- failed to open file for writing:"+String(LOGFILE));
        }
    }
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(configFile.getString(CLIENTSSID,DEFAULT_SSID));


 connectingDisplay();


   WiFi.begin(configFile.getString(CLIENTSSID,DEFAULT_SSID).c_str(), configFile.getString(CLIENTPASSWORD,DEFAULT_PASSWORD).c_str());
   WiFi.setAutoReconnect(true);
   WiFi.onEvent(WiFiEvent);
  #ifdef OZ890BMS
   //i2cscan();
   xTaskCreate(i2cTask,       /* Task function. */
                    "i2cTask",     /* String with name of task. */
                    10000,             /* Stack size in words. */
                    NULL,              /* Parameter passed as input of the task */
                    2,                 /* Priority of the task. */
                    NULL);             /* Task handle. */
#endif
#ifdef ANTBMS
   xTaskCreate(uartBmsTask,       /* Task function. */
                    "uartBmsTask",     /* String with name of task. */
                    10000,             /* Stack size in words. */
                    NULL,              /* Parameter passed as input of the task */
                    2,                 /* Priority of the task. */
                    NULL);             /* Task handle. */
#endif
#ifdef TFT
  xTaskCreate(spiDisplayTask,       /* Task function. */
                    "spiDisplayTask",     /* String with name of task. */
                    10000,             /* Stack size in words. */
                    NULL,              /* Parameter passed as input of the task */
                    2,                 /* Priority of the task. */
                    NULL);             /* Task handle. */

#endif
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

   
    httpServer.begin();

    
    delay(2000); 
  
}

void loop() {  
  httpServer.WifiLoop();
  if(!WiFi.isConnected()) {
    Serial.println("trying to reconnect Wifi");
     WiFi.reconnect();
    delay(5000);
  }
}


#ifdef ANTBMS
void uartBmsTask( void * parameter ){
    String s,s2;
    double vTmp;
  
    Serial.print("Created uartBmsTask: Executing on core ");
    Serial.println(xPortGetCoreID());
    Bms.init();
    Serial.println("BMS Initialized");
    
    while(1) {
       if(Bms.clearlog) {
         LogFile.clearLog();
          Bms.clearlog=0;
       };
       Bms.readBms();
       delay(20);
  }
}
#endif

#ifdef OZ890BMS
void i2cTask( void * parameter ){
    String s,s2;
    double vTmp;
  
    Serial.print("Created i2cTask: Executing on core ");
    Serial.println(xPortGetCoreID());
    Bms.init();
    Serial.println("BMS Initialized");
 
    unsigned int n=0;
    int refresh=0;
    unsigned int dispTimeout=0;
    int bt=0;
    int btb=0;
    int b;
    int dispmode=0;
    while(1) {
      #ifndef TFT  // TFT dispolay is handled in separate tesk
        b=digitalRead(BUTTON);
        if(b==0 && bt==1) {
          refresh=1;
          dispTimeout=n;
         }
        bt=b;
       // Serial.println("Button="+String(bt)+" "+String(n)+" "+String(dispTimeout)+" "+String(millis()));
      #endif
      n++;
  

      if(Bms.bmsOk && Bms.progeeprom) {
        Serial.println("Programming eeprom");
        Bms.progeeprom=0;
        Bms.eepromProg();
      }
      if((n%50==0 &&!Bms.bmsOk) || Bms.readeeprom) {
        Serial.println("Reading  eeprom");
        
        Bms.bmsOk=Bms.ReadEeprom();
        Bms.readeeprom=0;
      }
      if(Bms.clearlog) {
        Bms.clearlog=0;
        LogFile.clearLog();
      }
       s="";
       if(n%10==0) {
       Bms.readBms();
        refresh=1;
       }
      if(refresh) {
        refresh=0;
#ifdef OLED
       
       display.init();
       display.clear();   // clear the display
 
       if((bt==0) && (btb==1)) dispmode=dispmode >=2?0:dispmode+1;
       btb=bt;
       if(fabs(Bms.current)>0.5 || Bms.fetDisable) dispTimeout=n;
       if(n<(dispTimeout+600)) {
          if(bt) statusDisplay();
            else {
              if(dispmode==0) networkDisplay();
              if(dispmode==1) barplot(display);
              if(dispmode==2) cellVoltagesDisplay();
            }
       }
       display.display();
#endif 
    }
    delay(100);
  }
}
#endif







int i2cscan()
{
  byte error, address;
  int nDevices;
 
  //Serial.println("Scanning.. SDA:"+String(Wire.sda)+" SCL:"+String(Wire.scl)+" "+String((int32_t)Wire.i2c,16)+" "+String(Wire.num));
 
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

    return nDevices;
}
