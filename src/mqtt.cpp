#include "configfile.h"
#include <PubSubClient.h>
#include "bms.h"
#include "ant_bms.h"
#include "mqtt.h"



extern PubSubClient mqttclient;
extern ConfigFile configFile;
String topic;
String mqttserver;

void mqttTask(void *parameter)
{
  String s, s2;
  double vTmp;
  unsigned long lastMqttPublish=millis();;

  Serial.print("Created mqttTask: Executing on core ");
  Serial.println(xPortGetCoreID());
  mqttInit();
  unsigned long mqttInterval=configFile.getMqttInterval();
  Serial.println("mqtt Initialized interval:"+String(mqttInterval));

  while (1)
  {
    if (!mqttclient.connected()) mqttReconnect();
    mqttclient.loop();
    if(millis()>(lastMqttPublish+mqttInterval)) {
        mqttPublish(Bms.ll);
        lastMqttPublish=millis();
    }
    delay(10);
  }
}

void mqttInit()
{
    //dev = _settings._deviceName.c_str();
  topic = configFile.getDeviceName();
  mqttserver=configFile.getMqttServer();
  Serial.println("mqttInit() deviceName:"+topic+" server:"+mqttserver+" por:t"+String(configFile.getMqttPort()));
  mqttclient.setServer(mqttserver.c_str(), configFile.getMqttPort());
  //mqttclient.setCallback(callback);
}

void mqttReconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttclient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = configFile.getDeviceName();
      clientId += String(random(0xffff), HEX);
      
      if (mqttclient.connect(clientId.c_str())) {
        Serial.println("Connected.");
      } else sleep(5);
   }
}
void mqttPublish(LogLine ll)
{

    if(mqttserver.length()>0 && topic.length()>0)
    {
        mqttclient.publish((String(topic) + String("/V")).c_str(), String(Bms.vTot, 1).c_str());
        Serial.printf("mqttPublish topic:%s = %s\n",(String(topic) + String("/V")).c_str(),String(Bms.vTot, 1).c_str());
        mqttclient.publish((String(topic) + String("/A")).c_str(), String(Bms.current, 2).c_str());
        mqttclient.publish((String(topic) + String("/Ah")).c_str(), String(Bms.Ah, 2).c_str());
        mqttclient.publish((String(topic) + String("/state")).c_str(), Bms.ll.toJson().c_str());
    }

}   