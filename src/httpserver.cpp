#include "config.h"
#include "httpserver.h"
#include "bms.h"
#include "ant_bms.h"
#include "configfile.h"

extern ConfigFile configFile;

//WiFiServer server(80);
WebServer server(80);

String getNextToken(String& s, int& offset);

void HttpServer::begin()
{
  server.begin();
  server.on("/", serveRoot); 
  server.on("/antframe", antFrame); 
  server.on("/logStatus",logStat);  
  server.on("/config",getConfig);                      
  server.on("/dir",static_cast<void (*)()>(listDir));           
  server.on("/clearlog",clearLogFile);  
  server.on("/batt",batt);
  server.on("/setupmqtt",serveMqtt);
  server.on("/setmqtt",serveSetMqtt);
  server.on("/setupwifi",serveWifiSetupPage);
  server.on("/aplist.json",aplist);
  server.on("/logdata",getLogFile);
  server.on("/setparameter",setParameter);

  
}



void HttpServer::WifiLoop()
{
  #if 0
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
            client.println("Access-Control-Allow-Origin:*");
            if (urlLine.startsWith("GET /getfile")) {
              client.println("Content-Type: application/octet-stream");
              client.println();
              String fileName=getStringParam(urlLine,"file=",String(""));
              getFile(client,fileName,true);
            } else {
              if (urlLine.startsWith("GET /setup")) client.println("Content-Type: text/html; charset=utf-8");
              else client.println("Content-Type: application/json; charset=utf-8");
              client.println();
            }
#ifdef ANTBMS
            if (urlLine.startsWith("GET /antframe")) antFrame(client);  
#endif
#ifdef O890BMS
            if (urlLine.startsWith("GET /eeprom")) eeprom(client);  
            if (urlLine.startsWith("GET /readeeprom")) readEeprom(client); 
            if (urlLine.startsWith("GET /progeeprom")) { Bms.progeeprom=1; }// Schedule EEPROM programming 
            if (urlLine.startsWith("GET /raweeprom")) raweeprom(client);
#endif
            if (urlLine.startsWith("GET /logStatus")) logStat(client);  
            if (urlLine.startsWith("GET /config")) getConfig(client);                 
           
            if (urlLine.startsWith("GET /dir")) listDir(client);
            
            if (urlLine.startsWith("GET /clearlog")) clearLogFile(client);
            if (urlLine.startsWith("GET /logfile")) {
              int from=getIntParam(urlLine,"from=",-100);
              int n=getIntParam(urlLine,"n=",100);
              int c=getIntParam(urlLine,"c=",1);                              
              getLogFile(client,from,n,c);
            }
            if (urlLine.startsWith("GET /batt")) batt(client);
            if (urlLine.startsWith("GET /setupmqtt")) serveMqtt(client,urlLine);
            if (urlLine.startsWith("GET /setup")) serveWifiSetupPage(client);
            if (urlLine.startsWith("GET /aplist.json")) aplist(client);
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
  #endif
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}

//void HttpServer::getLogFile(WiFiClient &client,int offset,int nlines,int combine)
void HttpServer::getLogFile()

{
  int offset=-1;
  int nlines=100;
  int combine=false;

  if(server.hasArg("offset")) offset=server.arg("offset").toInt();
  if(server.hasArg("nlines")) nlines=server.arg("nlines").toInt();


  LogLine ll;
  int lines=0;
  String s;
  File f;
  int first=1;
  
  ll=LogFile.getLogLineAt(offset,f);
  Serial.println("- read from file:"+String(f.name())+" len:"+String(f.size())+"loglines:"+String(f.size()/sizeof(ll))+" from="+String(offset)+" nlines="+String(nlines)+" combine="+String(combine)+" valid="+String(ll.isValid()));
  Serial.println(ll.toString());
  s="{\"data\":[";
  while(f  &&  ll.isValid()) {
        if(!first) s+=",";
        s+=ll.toJson();
        first=0;
        if(s.length()>2048) {
          server.sendContent(s);
          s="";
        };
        
      /*  do { // Re-sync
          int n=file.read((uint8_t*)&ll,sizeof(ll));
          if(n==sizeof(ll) && !ll.isValid()) file.seek(1-sizeof(ll),SeekCur);
          if(n!=sizeof(ll)) nlines=0; // No more to read
        }
        while(file.available() && !ll.isValid() && nlines);*/
        Serial.println(String(offset)+" f="+String(f.position())+" "+ll.toJson());
        ll=LogFile.getLogLineAt(offset,f);
    };
    s+="]}";
    server.sendContent(s);
}

void HttpServer::getFile()
{
  String fileName=server.arg("fileName");
  bool textMode;
  int lines=0;
  int n;
  String s;
  uint8_t buf[128];
  File file = SPIFFS.open(fileName);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    /*while(file.available()){
         s=file.readStringUntil('\n');
         client.println(s);     
    };*/
    
  String   dataType = "application/octet-stream";
  

  if (server.streamFile(file, dataType) != file.size()) {
    Serial.println("Sent less data than expected!");
  }
  file.close();
}



void HttpServer::listDir()
{
  String s;
    s+="{";
    s+="\"totalBytes\":"+String(SPIFFS.totalBytes())+",";
    s+="\"usedBytes\":"+String(SPIFFS.usedBytes())+",";
    s+="\"dir\":[";
    s+=listDir(String("/"),"/",5);
    s+="]}";
    server.send(200,"application/json",s);
}

void HttpServer::getConfig()
{
    server.send(200,"application/json",configFile.toString());
}

void HttpServer::logStat()
{
  String s=LogFile.toJson();
  Serial.println(s);
  server.send(200,"application/json",s);
};

#ifdef ANTBMS
void HttpServer::antFrame()
{
  String s=Bms.antFrameToJson();
  Serial.println(s);
  server.send(200,"application/json",s);
};


#endif


#ifdef OZ890BMS
void HttpServer::raweeprom() {
   // the content of the HTTP response follows the header:
   String s;
             s="{\"values\":[";
            for (int i = 0; i < 128; i++) 
            {
              s+=Bms.oz890Eeprom[i]);
              if(i<128-1)s+=",";
             }
             s+="],\n";
            s+="\"gain\":1\}";
            server.send(200,"application/json",s);
}

void HttpServer::readEeprom() {
    Bms.readeeprom=1;
    int i=10;
    String s;
    while(i-- && Bms.readeeprom) sleep(1);
   // the content of the HTTP response follows the header:
            s="{\"values\":[";
            for (int i = 0; i < 128; i++) 
            {
              s+=Bms.oz890Eeprom[i]);
              if(i<128-1)s+=",";
             }
            s+="],\n";
            s+="\"gain\":1\}";
            server.send(200,"application/json",s);
}



void HttpServer::eeprom() {
   // the content of the HTTP response follows the header:
   String s;
      s="{";
      
      s+="\"parameters\":[";
            for (int i = 0; i < 13; i++) 
            {
              s+=parameter("CV"+String(i+1)+"O",i+5,"Cell Voltage offset",String(Bms.oz890Eeprom[i+5]*0.00122,3))+",\n";
            }
      
             s+=parameter("INTO",2,"InternalTempOffset",String(Bms.oz890Eeprom[2]))+",\n");
             s+=parameter("CSO",0x16,"currentOffset",String((int16_t)((uint8_t)Bms.oz890Eeprom[0x16]+(uint8_t)Bms.oz890Eeprom[0x17]*256),6))+",\n";
             s+=parameter("SR",0x34,"Current sense resistor",String(Bms.oz890Eeprom[0x34]*0.1,2))+",\n";
             s+=parameter("PFR",0x18,"PFRecord","\""+String(Bms.oz890Eeprom[0x18],16)+"\"")+",\n";
             s+=parameter("ATE_FRZ",0x25,"ATE_Freeze",String(Bms.oz890Eeprom[0x25]>>7))+",\n";
             s+=parameter("CNUM",0x26,"Number of cells",String((uint8_t)Bms.oz890Eeprom[0x26]&0xf))+",\n";
             s+=parameter("BTYP",0x26,"Cell type",String((uint8_t)Bms.oz890Eeprom[0x26]&0x30>>4))+",\n";
             s+=parameter("COCO",0x03,"Charge over current offset",String(Bms.oz890Eeprom[0x3]&0xf0>>4))+",\n";
             s+=parameter("SCO",0x03,"Short circuit offset",String(Bms.oz890Eeprom[0x3]&0xf))+",\n";
             s+=parameter("DOCO",0x04,"Discharge over current offset",String(Bms.oz890Eeprom[0x4]&0xf0>>4))+",\n";
             s+=parameter("DCTC",0x28,"Discharge state treshold",String(Bms.oz890Eeprom[0x28]&0xe0>>5))+",\n";
             s+=parameter("OCCFC",0x28,"Charge overcurrent",String(Bms.oz890Eeprom[0x28]&0x1f))+",\n";
             s+=parameter("CCTC",0x29,"Charge state treshold",String(Bms.oz890Eeprom[0x29]&0xc0>>6))+",\n";
             s+=parameter("OCCFD",0x29,"Discharge overcurrent",String(Bms.oz890Eeprom[0x29]&0x3f))+",\n";
            
             s+=parameter("OCDS",0x2a,"overcurrent delay",String(Bms.oz890Eeprom[0x2a]&7))+",\n";
             s+=parameter("OCDN",0x2a,"overcurrent delay number",String(Bms.oz890Eeprom[0x2a]>>3))+",\n";
             s+=parameter("SCC",0x2b,"Short circuit treshold",String(Bms.oz890Eeprom[0x2b]&0x3f))+",\n";

             
             s+=parameter("SCDN",0x2c,"Short circuit delay number",String((Bms.oz890Eeprom[0x2c]&0xf8)>>3))+",\n";
             s+=parameter("SCDS",0x2c,"Short circuit delay unit",String(Bms.oz890Eeprom[0x2c]&7))+",\n";

             s+=parameter("NO_ER_DSPL",0x2d,"Disable the error display",String(Bms.oz890Eeprom[0x2d]&0x80>>7))+",\n";
             s+=parameter("IDL_NLD_ENB",0x2d,"Idle bleeding enable",String(Bms.oz890Eeprom[0x2d]&0x40>>6))+",\n";
             s+=parameter("DOCRC",0x2d,"Discharge OC release time",String(Bms.oz890Eeprom[0x2d]&0x38>>3))+",\n";
             s+=parameter("COCRC",0x2d,"Charge OC release time",String(Bms.oz890Eeprom[0x2d]&7))+",\n";
             
             s+=parameter("I2CADDR",0x30,"i2caddress ",String(Bms.oz890Eeprom[0x30]&15))+",\n";
             s+=parameter("PEC_ENB",0x30,"i2 packet error check ",String(Bms.oz890Eeprom[0x30]&0x10))+",\n";
             s+=parameter("SCRC",0x30,"short circuit reset delay",String(Bms.oz890Eeprom[0x30]>>5))+",\n";

             s+=parameter("BCNC",0x30,"Maximum bleeding cell number (+1) 0x03",String(Bms.oz890Eeprom[0x33]&3))+",\n";

             
             s+=parameter("BCNC",0x33,"Maximum bleeding cell number (+1) 0x03",String(Bms.oz890Eeprom[0x33]&3))+",\n";
             s+=parameter("SEB",0x33,"Select external bleeding 0x04",String(Bms.oz890Eeprom[0x33]>>4&1))+",\n";
             s+=parameter("BS",0x33,"Enable bleeding function 0x08",String(Bms.oz890Eeprom[0x33]>>7&1))+",\n";
             s+=parameter("PS",0x33,"Enable pre-charge function 0x10",String(Bms.oz890Eeprom[0x33]>>4&1))+",\n";
             s+=parameter("SS",0x33,"Enable the sleep mode 0x20",String(Bms.oz890Eeprom[0x33]>>5&1))+",\n";
             s+=parameter("UC",0x33,"Safety scan, access to user data 0xc0",String(Bms.oz890Eeprom[0x33]>>6&3))+",\n";
             
             s+=parameter("OVT",0x4b,"Over voltage Treshold",String((int16_t)(Bms.oz890Eeprom[0x4a]+Bms.oz890Eeprom[0x4b]*256)*0.00122/8,3))+",\n";
             s+=parameter("OVR",0x4b,"Over voltage  Releasse",String((int16_t)(Bms.oz890Eeprom[0x4c]+Bms.oz890Eeprom[0x4d]*256)/8*0.00122,3))+",\n";
             s+=parameter("UVT",0x4f,"Under voltage Treshold",String((int16_t)(Bms.oz890Eeprom[0x4e]+Bms.oz890Eeprom[0x4f]*256)/8*0.00122,3))+",\n";
             s+=parameter("UVR",0x51,"Under voltage Releasse",String((int16_t)(Bms.oz890Eeprom[0x50]+Bms.oz890Eeprom[0x51]*256)/8*0.00122,3));
             s+="]}\n";
             server.send(200,"application/json",s);
}

void HttpServer::setParameter()
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
void HttpServer::setParameter()
{
  String param;
  String val;
  if(server.hasArg("param=")) param=server.arg("param=");
  if(server.hasArg("val=")) val=server.arg("val=");
  
}
#endif

String HttpServer::parameter(String name,int Reg,String comment,String value)
{
 return(String("{\"name\":")+"\""+name+"\","+"\"value\":"+value+",\"comment\":"+"\""+comment+"\"}");
}

void HttpServer::batt() 
{
  String s = "";
  s+=("{\"cellVoltages\":[");
   for (int i = 0; i < NUM_CELL_MAX; i++)      
   {
      s+=String((Bms.cellVoltages[i]) / 1000.0, 3);
      if(i<NUM_CELL_MAX)s+",";
   
   }
   s+="],";
   s+="\"minCellVoltages\":[";
   for (int i = 0; i < NUM_CELL_MAX; i++)      
   {
      s+=String((Bms.minCellVoltages[i]) / 1000.0, 3);
      if(i<NUM_CELL_MAX)s+=",";
   
   }
   s+="],";
   s+="\"idleCellVoltages\":[";
   for (int i = 0; i < NUM_CELL_MAX; i++)      
   {
      s+=String((Bms.idleCellVoltages[i]) / 1000.0, 3);
      if(i<NUM_CELL_MAX)s+=",";
   
   }
   s+="],";
   s+="\"V\":"+String(Bms.vTot,2)+",";
   s+="\"A\":"+String(Bms.current)+",";
   s+="\"Ah\":"+String(Bms.Ah)+",";
   s+="\"NumberOfCells\":"+String(Bms.numCell)+"}";
   #if 0
   s+="\"ShutdownStatus\":\""+String(Bms.shutdownStatus,16)+"\",";
   s+="\"ErrorStatus\":\""+String(Bms.errorStatus,16)+"\",";
   s+="\"FetEnable\":\""+String(Bms.fetEnable,16)+"\",";
   s+="\"FetDisable\":\""+String(Bms.fetDisable,16)+"\"\}";
   #endif
   server.send(200,"application/json",s);
}

void HttpServer::aplist()
{
  server.send(200,"application/json","[]");
  
}


void HttpServer::clearLogFile()
{
  Bms.clearlog=1;
}


 

void HttpServer::serveWifiSetupPage()
{
  String s = "";
  //appendHttp200(s);

  //This thing was automatically generated from html source
  s += F("<div><H1>Wifi Setup</H1></div>\r\n<div id=\"id01\">Searching for networks...</div>\r\n</html>\r\n\r\n");
  s += F("<script>\r\n\tvar xmlhttp = new XMLHttpRequest();\r\n\tvar url = \"aplist.json\";\r\n\r\n\txmlhttp.onreadystatechange = function() {\r\n");
  s += F("\t\tif (xmlhttp.readyState == 4 && xmlhttp.status == 200) {\r\n\t\t\tvar myArr = JSON.parse(xmlhttp.responseText);\r\n\t\t\tmyFunction(myArr);");
  s += F("\r\n\t\t}\r\n\t}\r\n\txmlhttp.open(\"GET\", url, true);\r\n\txmlhttp.send();\r\n\r\n\tfunction myFunction(arr) {\r\n");
  s += F("\t\tvar out = \"<fieldset><legend>WiFi Network to connect to</legend>\";\r\n\t\tout += '<form action=setap method=GET><table style=\"width:80%\">';\r\n\t\tvar i;\r\n");
  s += F("\t\tfor(i = 0; i < arr.length; i++) \r\n\t\t{\r\n\t\t\tout += '<tr><td align=right><input type=radio name=ssid id=\"s' + i + '\" value=\"' + arr[i].n + '\"/></td>' \r\n");
  s += F("\t\t\t\t+ '<td><label for=s' + i + '>' + arr[i].n + ' (' + arr[i].r + 'db)</label></td>'\r\n\t\t\t\t+ '</tr>';\r\n\t\t}\r\n");
  //s += F("\t\tout += \"<tr><td align=right><input type=radio name=ssid id=sc value=''></td><td><input type=text value='Custom SSID' onfocus='document.getElementById(sc).checked=true'></input></input></td></tr>\";\r\n");
  s += F("\t\tout += \"<tr><td><br></td></tr>\"\r\n\t\tout += \"<tr><td width=1 align=right>Password:</td><td><input type=text name=pass></input></td></tr>\"\r\n\t\tout += \"<tr><td><br></td></tr>\"\r\n");
  s += F("\t\tout += \"<tr><td></td><td>Note: Password is sent over plaintext, only use on secure network.</td></tr>\"\r\n\t\tout += \"<tr><td></td><td><input type=submit value='Submit'/></td></tr>\"\r\n\t\t");
  s += F("\t\tout += '</table></form>'\r\n\t\tdocument.getElementById(\"id01\").innerHTML = out;\r\n\t}\r\n</script>");

  server.send(200,"text/html",s);
  
}

//MQTT and device name
void HttpServer::serveMqtt()
{
  String s = "";
 // appendHttp200(s);

  //This thing was automatically generated from html source
  s += F("<H1>MQTT server & device name</H1></html>\r\n\r\n");

  s += F("<form action=setmqtt>");
  s += F("<table>");
  s += F("<tr><td><b>Setting</b></td><td><b>Value Key</b></td></tr>");
  s += F("<tr><td>Mqtt Server</td><td><input type=text name=w width=20 value='");
  s += configFile.getMqttServer();
  s += F("'></td><td><input type=text name=r width=20 value='");
  s += String(configFile.getMqttPort());
  s += F("'></td></tr>");
  s += F("<tr><td>Mqtt User/pass</td><td><input type=text name=u width=20 value='");
 s += configFile.getMqttUser();
  s += F("'></td><td><input type=text name=p width=20 value='");
  s += configFile.getMqttPassword();
  s += F("'></td></tr>");
  
  s += F("<tr><td>Device Name</td><td><input type=text name=n width=20 value='");
  s += configFile.getDeviceName();
  s += F("'></td></tr>");
  
  s += F("<tr><td><br></td></tr>");
  
  s += F("<tr><td>Update rate</td><td><input type=text name=i width=5 value='");
  s += configFile.getMqttInterval();
  s += F("'></td><td>microseconds</td></tr>");

  s += F("<tr><td></td><td></td><td><input type=submit value='    Save Settings   '></td></tr>");
  s += F("</table></form>");
  s += F("</html>\r\n\r\n");  
  server.send(200,"text/html",s);
  
}


//Apply mqtt settings
void HttpServer::serveSetMqtt()
{
  String s = "";

  Serial.println("serveSetMqtt args="+String(server.args())+"  w="+server.arg("w")+" n="+server.arg("n"));
 
  if(server.hasArg("w")) configFile.setMqttServer(server.arg("w"));
  if(server.hasArg("n")) configFile.setDeviceName(server.arg("n"));
  if(server.hasArg("u")) configFile.setMqttUser(server.arg("u"));
  if(server.hasArg("p")) configFile.setMqttPassword(server.arg("p"));
  if(server.hasArg("r")) configFile.setMqttPort(server.arg("p").toInt());
  if(server.hasArg("i")) configFile.setMqttInterval(server.arg("i").toInt());
  Serial.println(configFile.toString());
  configFile.saveConfiguration(CONFIGFILE);
  server.send(200, "text/plain", "");
}


String HttpServer::listDir(String prefix,const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    String s;
    File root = SPIFFS.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        s+=String("{\"error\":\"failed to open directory\",\"directory”:\"")+dirname+"\"}";
        return s;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        s+=String("{\"error\":\"- not a directory\",\"directory\":\"")+dirname+"\"}";
        return s;
    }

  
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                s+=listDir(prefix+file.name()+"/",file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
            s+=String("{\"name\":\"")+file.name()+"\",\"size\":"+String(file.size())+"}";
        }
        file = root.openNextFile();
    }
    return s;
}

void HttpServer::serveRoot()
{
  String s = "";
  
    s += F("<H1>KateBMS</H1></html>\r\n\r\n");
    s += F("<a href=\"setupmqtt\">Configure MQTT</a><br>");
    s += F("<a href=\"setupwifi\">Configure Wifi</a><br>");
    s += F("<a href=\"dir\">FFS directory listing</a><br>");
    s += F("<a href=\"batt\">Battery status</a><br>");
    s += F("<a href=\"antframe\">Ant BMS raw frameBattery status</a><br>");
    s += F("<a href=\"logStatus\">LogStatus</a><br>");
    s += F("<a href=\"config\">Get raw config</a><br>");
    s += F("<a href=\"logdata\">Get raw logdata 100 last lines</a><br>");
    s += F("<a href=\"clearlog\">delete all logfiles</a><br>");
    

    //s += ("Devicename:"+ _settings._deviceName +"<br>");
    //s += ("Type:"+ _settings._deviceType +"<br>");
    //s += F("IP:"+ String(ip) +"<br>");
    
    s += F("<br><br><a href=\"reboot\">Reboot device</a><br>");
    
    s += F("<br><br><br><br><br>Kate Alhola<br>");

  s += F("</html>\r\n\r\n");
  s += F("");
  server.send(200,"text/html",s);
}



