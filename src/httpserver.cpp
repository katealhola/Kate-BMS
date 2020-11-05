#include "config.h"
#include "httpserver.h"
#include "bms.h"
#include "ant_bms.h"
#include "configfile.h"

extern ConfigFile configFile;

WiFiServer server(80);

void HttpServer::begin()
{
  server.begin();
  
}



void HttpServer::WifiLoop()
{
   WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
  //  Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    String urlLine = "";
  
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
 //       Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            Serial.println("Handling request:"+urlLine);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: application/json; charset=utf-8");
            client.println("Access-Control-Allow-Origin:*");
            client.println();
#ifdef ANTBMS
            if (urlLine.startsWith("GET /antframe")) antFrame(client);  
#endif
#ifdef O890BMS
            if (urlLine.startsWith("GET /eeprom")) eeprom(client);  
            if (urlLine.startsWith("GET /readeeprom")) readEeprom(client); 
            if (urlLine.startsWith("GET /progeeprom")) { Bms.progeeprom=1; }// Schedule EEPROM programming 
            if (urlLine.startsWith("GET /raweeprom")) raweeprom(client);
#endif

            if (urlLine.startsWith("GET /config")) getConfig(client);                 
           
            if (urlLine.startsWith("GET /dir")) listDir(client);
            if (urlLine.startsWith("GET /getfile")) {
              String fileName=getStringParam(urlLine,"file=",String(""));
              getFile(client,fileName,true);
            }
            if (urlLine.startsWith("GET /clearlog")) clearLogFile(client);
            if (urlLine.startsWith("GET /logfile")) {
              int from=getIntParam(urlLine,"from=",-100);
              int n=getIntParam(urlLine,"n=",100);
              int c=getIntParam(urlLine,"c=",1);                              
              getLogFile(client,from,n,c);
            }
            if (urlLine.startsWith("GET /batt")) batt(client);
            if (urlLine.startsWith("GET /logdata")) getLogFile(client,-100,100,0);
            if (urlLine.startsWith("GET /setparameter")) {         
                setParameter(client,urlLine);
            }

            

            
           
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            if(urlLine.length()==0) urlLine=currentLine;
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void HttpServer::getLogFile(WiFiClient &client,int offset,int nlines,int combine)
{
  
  LogLine ll;
  int lines=0;
  String s;
  File file = SPIFFS.open(LOGFILE);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    int fileSize=file.size()/sizeof(ll);
    file.seek((offset>=0?offset:fileSize+offset)*sizeof(ll));

    Serial.println("- read from file:"+String(LOGFILE)+" len:"+String(file.size())+"loglines:"+String(file.size()/sizeof(ll))+" from="+String(offset)+" nlines="+String(nlines)+" combine="+String(combine));
    client.print("{\"data\":[");
    while(file.available() && nlines-- ){
        if(s.length()>0) s+=",";
        client.println(s);
        do { // Re-sync
          int n=file.read((uint8_t*)&ll,sizeof(ll));
          if(n==sizeof(ll) && !ll.isValid()) file.seek(1-sizeof(ll),SeekCur);
          if(n!=sizeof(ll)) nlines=0; // No more to read
        }
        while(file.available() && !ll.isValid() && nlines);
        Serial.println(ll.toString()+" f="+String(file.position()));
        s=ll.toJson();
    };
    s+="]}";
    client.println(s);
}

void HttpServer::getFile(WiFiClient &client,String fileName,bool textMode)
{
  LogLine ll;
  int lines=0;
  String s;
  File file = SPIFFS.open(fileName);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    while(file.available()){
         s=file.readStringUntil('\n');
         client.println(s);     
    };
}



void HttpServer::listDir(WiFiClient &client)
{
    client.print("{");
    client.print("\"totalBytes\":"+String(SPIFFS.totalBytes())+",");
    client.print("\"usedBytes\":"+String(SPIFFS.usedBytes())+",");
    client.print("\"dir\":[");
    listDir(client,String("/"),"/",5);
    client.print("]}");
}

void HttpServer::getConfig(WiFiClient &client)
{
    client.print(configFile.toString());
}

#ifdef ANTBMS
void HttpServer::antFrame(WiFiClient &client)
{
  String s=Bms.antFrameToJson();
  Serial.println(s);
  client.print(s);
};


#endif


#ifdef OZ890BMS
void HttpServer::raweeprom(WiFiClient &client) {
   // the content of the HTTP response follows the header:
            client.print("{\"values\":[");
            for (int i = 0; i < 128; i++) 
            {
              client.print(Bms.oz890Eeprom[i]);
              if(i<128-1)client.print(',');
             }
            client.print("],\n");
            client.print("\"gain\":1\}");
}

void HttpServer::readEeprom(WiFiClient &client) {
    Bms.readeeprom=1;
    int i=10;
    while(i-- && Bms.readeeprom) sleep(1);
   // the content of the HTTP response follows the header:
            client.print("{\"values\":[");
            for (int i = 0; i < 128; i++) 
            {
              client.print(Bms.oz890Eeprom[i]);
              if(i<128-1)client.print(',');
             }
            client.print("],\n");
            client.print("\"gain\":1\}");
}



void HttpServer::eeprom(WiFiClient &client) {
   // the content of the HTTP response follows the header:
      client.print("{");
      
      client.print("\"parameters\":[");
            for (int i = 0; i < 13; i++) 
            {
              client.print(parameter("CV"+String(i+1)+"O",i+5,"Cell Voltage offset",String(Bms.oz890Eeprom[i+5]*0.00122,3))+",\n");
            }
      
             client.print(parameter("INTO",2,"InternalTempOffset",String(Bms.oz890Eeprom[2]))+",\n");
             client.print(parameter("CSO",0x16,"currentOffset",String((int16_t)((uint8_t)Bms.oz890Eeprom[0x16]+(uint8_t)Bms.oz890Eeprom[0x17]*256),6))+",\n");
             client.print(parameter("SR",0x34,"Current sense resistor",String(Bms.oz890Eeprom[0x34]*0.1,2))+",\n");
             client.print(parameter("PFR",0x18,"PFRecord","\""+String(Bms.oz890Eeprom[0x18],16)+"\"")+",\n");
             client.print(parameter("ATE_FRZ",0x25,"ATE_Freeze",String(Bms.oz890Eeprom[0x25]>>7))+",\n");
             client.print(parameter("CNUM",0x26,"Number of cells",String((uint8_t)Bms.oz890Eeprom[0x26]&0xf))+",\n");
             client.print(parameter("BTYP",0x26,"Cell type",String((uint8_t)Bms.oz890Eeprom[0x26]&0x30>>4))+",\n");
             client.print(parameter("COCO",0x03,"Charge over current offset",String(Bms.oz890Eeprom[0x3]&0xf0>>4))+",\n");
             client.print(parameter("SCO",0x03,"Short circuit offset",String(Bms.oz890Eeprom[0x3]&0xf))+",\n");
             client.print(parameter("DOCO",0x04,"Discharge over current offset",String(Bms.oz890Eeprom[0x4]&0xf0>>4))+",\n");
             client.print(parameter("DCTC",0x28,"Discharge state treshold",String(Bms.oz890Eeprom[0x28]&0xe0>>5))+",\n");
             client.print(parameter("OCCFC",0x28,"Charge overcurrent",String(Bms.oz890Eeprom[0x28]&0x1f))+",\n");
             client.print(parameter("CCTC",0x29,"Charge state treshold",String(Bms.oz890Eeprom[0x29]&0xc0>>6))+",\n");
             client.print(parameter("OCCFD",0x29,"Discharge overcurrent",String(Bms.oz890Eeprom[0x29]&0x3f))+",\n");
            
             client.print(parameter("OCDS",0x2a,"overcurrent delay",String(Bms.oz890Eeprom[0x2a]&7))+",\n");
             client.print(parameter("OCDN",0x2a,"overcurrent delay number",String(Bms.oz890Eeprom[0x2a]>>3))+",\n");
             client.print(parameter("SCC",0x2b,"Short circuit treshold",String(Bms.oz890Eeprom[0x2b]&0x3f))+",\n");

             
             client.print(parameter("SCDN",0x2c,"Short circuit delay number",String((Bms.oz890Eeprom[0x2c]&0xf8)>>3))+",\n");
             client.print(parameter("SCDS",0x2c,"Short circuit delay unit",String(Bms.oz890Eeprom[0x2c]&7))+",\n");

             client.print(parameter("NO_ER_DSPL",0x2d,"Disable the error display",String(Bms.oz890Eeprom[0x2d]&0x80>>7))+",\n");
             client.print(parameter("IDL_NLD_ENB",0x2d,"Idle bleeding enable",String(Bms.oz890Eeprom[0x2d]&0x40>>6))+",\n");
             client.print(parameter("DOCRC",0x2d,"Discharge OC release time",String(Bms.oz890Eeprom[0x2d]&0x38>>3))+",\n");
             client.print(parameter("COCRC",0x2d,"Charge OC release time",String(Bms.oz890Eeprom[0x2d]&7))+",\n");
             
             client.print(parameter("I2CADDR",0x30,"i2caddress ",String(Bms.oz890Eeprom[0x30]&15))+",\n");
             client.print(parameter("PEC_ENB",0x30,"i2 packet error check ",String(Bms.oz890Eeprom[0x30]&0x10))+",\n");
             client.print(parameter("SCRC",0x30,"short circuit reset delay",String(Bms.oz890Eeprom[0x30]>>5))+",\n");

             client.print(parameter("BCNC",0x30,"Maximum bleeding cell number (+1) 0x03",String(Bms.oz890Eeprom[0x33]&3))+",\n");

             
             client.print(parameter("BCNC",0x33,"Maximum bleeding cell number (+1) 0x03",String(Bms.oz890Eeprom[0x33]&3))+",\n");
             client.print(parameter("SEB",0x33,"Select external bleeding 0x04",String(Bms.oz890Eeprom[0x33]>>4&1))+",\n");
             client.print(parameter("BS",0x33,"Enable bleeding function 0x08",String(Bms.oz890Eeprom[0x33]>>7&1))+",\n");
             client.print(parameter("PS",0x33,"Enable pre-charge function 0x10",String(Bms.oz890Eeprom[0x33]>>4&1))+",\n");
             client.print(parameter("SS",0x33,"Enable the sleep mode 0x20",String(Bms.oz890Eeprom[0x33]>>5&1))+",\n");
             client.print(parameter("UC",0x33,"Safety scan, access to user data 0xc0",String(Bms.oz890Eeprom[0x33]>>6&3))+",\n");
             
             client.print(parameter("OVT",0x4b,"Over voltage Treshold",String((int16_t)(Bms.oz890Eeprom[0x4a]+Bms.oz890Eeprom[0x4b]*256)*0.00122/8,3))+",\n");
             client.print(parameter("OVR",0x4b,"Over voltage  Releasse",String((int16_t)(Bms.oz890Eeprom[0x4c]+Bms.oz890Eeprom[0x4d]*256)/8*0.00122,3))+",\n");
             client.print(parameter("UVT",0x4f,"Under voltage Treshold",String((int16_t)(Bms.oz890Eeprom[0x4e]+Bms.oz890Eeprom[0x4f]*256)/8*0.00122,3))+",\n");
             client.print(parameter("UVR",0x51,"Under voltage Releasse",String((int16_t)(Bms.oz890Eeprom[0x50]+Bms.oz890Eeprom[0x51]*256)/8*0.00122,3)));
             client.print("]}\n");
}

void HttpServer::setParameter(WiFiClient &client,String urlLine)
{
  Serial.println("setParameter:"+urlLine);
    Bms.oz890Eeprom[0x29]=0xd4;  // OCCDF=15  Over Discharge current treshold 
    Bms.oz890Eeprom[0x2b]=0xc7;  // SCC Short circuit treshold = 78
    Bms.oz890Eeprom[0x2d]=0x53;  // IDL_BLD_ENB=1 COCRC=2 ( Charge over current release 2s) DOCRC=2 ( DisCharge over current release 2s) 
    Bms.oz890Eeprom[0x2c]=0xf3;      //SCDN=30, SCDS=2 (64uc)
    Bms.oz890Eeprom[0x33]=0x6f;  // UC=01 ( safety scan on, can read write user data SS=1 sleep mode on BS=1 enable bleeding, ENS, external bleeding, max bleed 4 cells
  
}
#endif

#ifndef OZ890BMS
void HttpServer::setParameter(WiFiClient &client,String urlLine)
{

  
}
#endif

String HttpServer::parameter(String name,int Reg,String comment,String value)
{
 return(String("{\"name\":")+"\""+name+"\","+"\"value\":"+value+",\"comment\":"+"\""+comment+"\"}");
}

void HttpServer::batt(WiFiClient &client) 
{
  client.print("{\"cellVoltages\":[");
   for (int i = 0; i < NUM_CELL_MAX; i++)      
   {
      client.print(String((Bms.cellVoltages[i]) / 1000.0, 3));
      if(i<12)client.print(',');
   
   }
   client.print("],");
   client.print("\"minCellVoltages\":[");
   for (int i = 0; i < NUM_CELL_MAX; i++)      
   {
      client.print(String((Bms.minCellVoltages[i]) / 1000.0, 3));
      if(i<12)client.print(',');
   
   }
   client.print("],");
   client.print("\"idleCellVoltages\":[");
   for (int i = 0; i < NUM_CELL_MAX; i++)      
   {
      client.print(String((Bms.idleCellVoltages[i]) / 1000.0, 3));
      if(i<12)client.print(',');
   
   }
   client.print("],");
   
   client.print("\"V\":"+String(Bms.vTot,2)+",");
   client.print("\"A\":"+String(Bms.current)+",");
   client.print("\"Ah\":"+String(Bms.Ah)+",");
   client.print("\"NumberOfCells\":"+String(Bms.cellNumber&015)+",");
   client.print("\"ShutdownStatus\":\""+String(Bms.shutdownStatus,16)+"\",");
   client.print("\"ErrorStatus\":\""+String(Bms.errorStatus,16)+"\",");
   client.print("\"FetEnable\":\""+String(Bms.fetEnable,16)+"\",");
   client.print("\"FetDisable\":\""+String(Bms.fetDisable,16)+"\"\}");
}




void HttpServer::clearLogFile(WiFiClient &client)
{
  Bms.clearlog=1;
}

int HttpServer::getIntParam(String urlLine,String paramName,int defval)
{
 int res=defval;
 int pos;
 urlLine=urlLine.substring(0,urlLine.indexOf(" HTTP"));
 if((pos=urlLine.indexOf(paramName))>5) {
  pos+=paramName.length();
  String s=urlLine.substring(pos,urlLine.indexOf("&",pos));
  res=s.toInt();
  Serial.println("from:"+urlLine+" parameter:"+paramName+"="+s+":"+String(res));
 }
 return res;
}

String HttpServer::getStringParam(String urlLine,String paramName,String defval)
{
 String res=defval;
 int pos;
 urlLine=urlLine.substring(0,urlLine.indexOf(" HTTP"));
 if((pos=urlLine.indexOf(paramName))>5) {
  pos+=paramName.length();
  String s=urlLine.substring(pos,urlLine.indexOf("&",pos));
  res=s;
  Serial.println("from:"+urlLine+" parameter:"+paramName+"="+s);
 }
 return res;
}

void HttpServer::listDir(WiFiClient &client,String prefix,const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = SPIFFS.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        client.print(String("{\"error\":\"failed to open directory\",\"directory”:\"")+dirname+"\"}");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        client.print(String("{\"error\":\"- not a directory\",\"directory\":\"")+dirname+"\"}");
        return;
    }

  
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(client,prefix+file.name()+"/",file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
            client.print(String("{\"name\":\"")+file.name()+"\",\"size\":"+String(file.size())+"}");
        }
        file = root.openNextFile();
    }
}


