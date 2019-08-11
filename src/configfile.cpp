#include "configfile.h"
#include <SD.h>
#include "config.h"


// Loads the configuration from a file
void ConfigFile::loadConfiguration(const char *filename) {
  // Open file for reading
  File file = SD.open(filename);

//  _root = jsonBuffer.parseObject(file);
  DeserializationError error = deserializeJson(doc, file);
 /* if (!_root.success())
    Serial.println("Failed to read file, using default configuration");*/
    if (error)
    Serial.println(F("Failed to read file, using default configuration"));
    
    /*_root = jsonBuffer.parseObject(DEFAULTCONFIG);
    if (!_root.success())
    Serial.println(String("Failed to parse default configuration")+DEFAULTCONFIG);
*/
  // Copy values from the JsonObject to the Config
  //clientSsid=root()["clientSsid"] | "tapla",  // <- source
       
  // Close the file (File's destructor doesn't close the file)
  file.close();
}
String ConfigFile::getClientSsid() {
  return doc["clientSsid"] | DEFAULT_SSID; // <- source
}

String ConfigFile::getString(const char * key,const char *defval) {
  return doc[key] | defval; // <- source
}

void ConfigFile::saveConfiguration(const char *filename) {
  // Delete existing file, otherwise the configuration is appended to the file
  SD.remove(filename);

  // Open file for writing
  File file = SD.open(filename, FILE_WRITE);
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

