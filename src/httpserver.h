#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>




class HttpServer{
  


public:
  void begin();
  
  static String listDir(String prefix,const char * dirname, uint8_t levels);
  static void getLogFile();
  static void getFile();
  static void listDir();
  static void getConfig();
  static void batt() ;
  static void setParameter();
  static void clearLogFile();
  static void serveWifiSetupPage();
  static void serveMqtt();
  static void serveSetMqtt();
  static void aplist();
  static void logStat();
  static void serveRoot();

  
#ifdef OZ890BMS
  static void raweeprom();
  static void eeprom();
  static void readEeprom();
#endif 

#ifdef ANTBMS
  static void antFrame();
#endif
  
  /*int getIntParam(String urlLine,String paramName,int defval);
  String getStringParam(String urlLine,String paramName,String defval);
  bool setStringIfStartsWith(String& s, String startswith, String& set);
*/
  void WifiLoop();
};

#endif
