
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
#include "configfile.h"
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "mqtt.h"

const char *ssid = DEFAULT_SSID;
const char *password = DEFAULT_PASSWORD;

#ifdef OZ890BMS
void i2cTask(void *parameter);
int i2cscan();
#endif

WiFiClient espClient;
PubSubClient mqttclient(espClient);
ConfigFile configFile;

void displayInit();
void startUpDisplay();
void connectingDisplay();


#define LOGSIZE 100

#ifdef OLED
// Initialize the OLED display using Wire library
SSD1306 display(0x3c, I2C_SDA, I2C_SCL);
#endif

#ifdef TFT
//Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
// Use hardware SPI
TFT_eSPI display = TFT_eSPI();
int ILI9341_COLOR;
#define CUSTOM_DARK 0x4228 // Background color
void spiDisplayTask(void *parameter);
void uartBmsTask(void *parameter);

#endif

#include "logline.h"
#ifdef LOGFILE
#include "logfile.h"
#endif
#include "httpserver.h"

int packetCounter;
HttpServer httpServer;
int showConnected = 0;

void WiFiEvent(WiFiEvent_t event)
{
  Serial.printf("[WiFi-event] event: %d\n", event);

  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    showConnected = 1;
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("WiFi lost connection");
    break;
  }
}

void setup()
{

  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL, 80000);
  Serial.printf("i2c initialized I2C_SDA=%d, I2C_SCL=%d\n",I2C_SDA, I2C_SCL);

  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);

  //   Wire.begin(I2C_SDA,I2C_SCL,300000);

  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS Mount Failed");
  }
  Serial.println("SPIFFS Mounted total_bytes:"+String(SPIFFS.totalBytes())+" used:"+String(SPIFFS.usedBytes()));
  configFile.loadConfiguration(CONFIGFILE);
  Serial.println(configFile.toString());
  #ifdef LOGFILE
  LogFile.init();
  Serial.println("LogFile.init() done");
  #endif
  displayInit();

  // Wire.setClock(300000);
  Serial.println();

  startUpDisplay();

  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(configFile.getString(CLIENTSSID, DEFAULT_SSID));

  connectingDisplay();

  WiFi.begin(configFile.getString(CLIENTSSID, DEFAULT_SSID).c_str(), configFile.getString(CLIENTPASSWORD, DEFAULT_PASSWORD).c_str());
  WiFi.setAutoReconnect(true);
  WiFi.onEvent(WiFiEvent);
  
#ifdef OZ890BMS
  i2cscan();
  xTaskCreate(i2cTask,   /* Task function. */
              "i2cTask", /* String with name of task. */
              10000,     /* Stack size in words. */
              NULL,      /* Parameter passed as input of the task */
              2,         /* Priority of the task. */
              NULL);     /* Task handle. */
#endif

#ifdef ANTBMS
  xTaskCreate(uartBmsTask,   /* Task function. */
              "uartBmsTask", /* String with name of task. */
              10000,         /* Stack size in words. */
              NULL,          /* Parameter passed as input of the task */
              5,             /* Priority of the task. */
              NULL);         /* Task handle. */
#endif
#ifdef JIKONGBMS
  xTaskCreate(uartBmsTask,   /* Task function. */
              "modbusBmsTask", /* String with name of task. */
              10000,         /* Stack size in words. */
              NULL,          /* Parameter passed as input of the task */
              5,             /* Priority of the task. */
              NULL);         /* Task handle. */
#endif
#ifdef TFT
  delay(500);
  xTaskCreate(spiDisplayTask,   /* Task function. */
              "spiDisplayTask", /* String with name of task. */
              10000,            /* Stack size in words. */
              NULL,             /* Parameter passed as input of the task */
              2,                /* Priority of the task. */
              NULL);            /* Task handle. */

#endif
#ifdef MQTT
mqttInit();
xTaskCreate(mqttTask,   /* Task function. */
              "mqttTask", /* String with name of task. */
              10000,            /* Stack size in words. */
              NULL,             /* Parameter passed as input of the task */
              2,                /* Priority of the task. */
              NULL);            /* Task handle. */
              #endif

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  httpServer.begin();

  delay(2000);
}

void loop()
{
  httpServer.WifiLoop();
  if (!WiFi.isConnected())
  {
    Serial.println("trying to reconnect Wifi");
    WiFi.reconnect();
    delay(5000);
  } else {
    //mqttclient.loop();
  }
}





int i2cscan()
{
  byte error, address;
  int nDevices;

  //Serial.println("Scanning.. SDA:"+String(Wire.sda)+" SCL:"+String(Wire.scl)+" "+String(Wire.num));

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  return nDevices;
}
