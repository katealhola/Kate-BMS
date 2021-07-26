#include "configfile.h"
#include <SD.h>
#include "SPIFFS.h"
#include "config.h"


// Loads the configuration from a file
void ConfigFile::loadConfiguration(const char *filename) {
  // Open file for reading
  File file = SPIFFS.open(filename);

//  _root = jsonBuffer.parseObject(file);
  DeserializationError error = deserializeJson(doc, file);
 /* if (!_root.success())
    Serial.println("Failed to read file, using default configuration");*/
    if (error)
    Serial.println(F("Failed to read file, using default configuration"));
    error = deserializeJson(doc, DEFAULTCONFIG);
    if (error) Serial.println(F("Failed to serialize default configuration"));
      
  // Close the file (File's destructor doesn't close the file)
  file.close();
}
String ConfigFile::getClientSsid() {
  return doc["clientSsid"] | DEFAULT_SSID; // <- source
}

String ConfigFile::getString(const char * key,const char* defval) {
  return doc[key] | String(defval); // <- source
}

void ConfigFile::saveConfiguration(const char *filename) {
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove(filename);

  // Open file for writing
  File file = SPIFFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }
  // Serialize JSON to file
  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }
  // Close the file (File's destructor doesn't close the file)
  file.close();
}

String ConfigFile::toString()
{
  String s;
  serializeJson(doc,s);
  return(s);
}

String ConfigFile::getApSsid(){return doc["ApSsid"] | DEFAULT_AP_SSID; };
  void ConfigFile::setApSsid(String s){doc["ApSsid"]=s;};
  String ConfigFile::getApPasswd(){return doc["ApPasswd"] | DEFAULT_AP_PASSWORD;};
  void ConfigFile::setApPasswd(String s){doc["ApPasswd"]=s;};
  void ConfigFile::setMqttPort(int i){doc["MqttPort"]=String(i);};
  int ConfigFile::getMqttPort(){return String(doc["MqttPort"] | "1883").toInt();};
  void ConfigFile::setDeviceName(String s){doc["DeviceName"]=s;};
  String ConfigFile::getDeviceName(){return doc["DeviceName"] | "KateBMS";};
  void ConfigFile::setMqttUser(String s){doc["MqttUser"]=s;};
  String ConfigFile::getMqttUser(){return doc["MqttUser"] | "";};
  void ConfigFile::setMqttPassword(String s){doc["MqttPassword"]=s;};
  String ConfigFile::getMqttPassword(){return doc["MqttPassword"] | "";};
  void ConfigFile::setMqttServer(String s){doc["MqttServer"]=s;};
  String ConfigFile::getMqttServer(){return doc["MqttServer"] | DEFAULT_MQTT_SERVER; };
  float ConfigFile::getCellFullVolt(){return String(doc["CellFullVolt"] | "4.10").toFloat();};
  void ConfigFile::setCellFullVolt(float f) {doc["CellFullVolt"]=String(f,3);};

  void ConfigFile::setMqttInterval(unsigned long i){doc["MqttInterval"]=String(i);};
  unsigned long  ConfigFile::getMqttInterval(){return String(doc["MqttInterval"] | "10000").toInt();};
  void ConfigFile::setIdleLogInterval(unsigned long i){doc["MqttIdleLogInterval"]=String(i);};
  unsigned long ConfigFile::getIdleLogInterval(){return String(doc["MqttIdleLogInterval"] | "10000").toInt();};
