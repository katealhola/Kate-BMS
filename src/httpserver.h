#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_
#include <Arduino.h>
#include <WiFi.h>




class HttpServer{


public:
  void begin();
  
  void listDir(WiFiClient &client,String prefix,const char * dirname, uint8_t levels);
  void getLogFile(WiFiClient &client,int offset,int nlines,int combine);
  void getFile(WiFiClient &client,String fileName,bool textMode);
  void listDir(WiFiClient &client);
  void getConfig(WiFiClient &client);
  void batt(WiFiClient &client) ;
  void setParameter(WiFiClient &client,String urlLine);
  void clearLogFile(WiFiClient &client);
  
#ifdef OZ890BMS
  void raweeprom(WiFiClient &client);
  void eeprom(WiFiClient &client);
  void readEeprom(WiFiClient &client);
#endif 

#ifdef ANTBMS
  void antFrame(WiFiClient &client);
#endif
  void logStat(WiFiClient &client);
  String parameter(String name,int reg,String comment,String value);
  int getIntParam(String urlLine,String paramName,int defval);
  String getStringParam(String urlLine,String paramName,String defval);

  void WifiLoop();
};

#endif
