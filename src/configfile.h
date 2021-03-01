#ifndef _CONFIGFILE_H_
#define _CONFIGFILE_H_

#include <Arduino.h>
#include <ArduinoJson.h>

class ConfigFile {
  public:
  ConfigFile() {};
  void loadConfiguration(const char *filename);
  void saveConfiguration(const char *filename); 
  String getClientSsid();
  String getString(const char* key,const char  *defval);
  String getClientPasswd();
  String getApSsid();
  void setApSsid();
  String getApPasswd();
  void setApPasswd();
  String toString();
  void setMqttPort(int);
  int getMqttPort();
  void setDeviceName(String);
  String getDeviceName();
  void setMqttUser(String);
  String getMqttUser();
  void setMqttPassword(String);
  String getMqttPassword();
  void setMqttServer(String);
  String getMqttServer(String);
  StaticJsonDocument<512> doc;
  JsonVariant _root;

  /*const JsonObject& root() const { 
      return _root;
    }*/
  
};
#endif
