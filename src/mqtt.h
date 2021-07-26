#ifndef _MQTT_H_
#define _MQTT_H_
#include "logline.h"

void mqttInit();
void mqttPublish(LogLine ll);
void mqttTask(void *parameter);
void mqttReconnect();

#endif