#ifndef _CONFIG_H_
#define _CONFIG_H_

#if __has_include("localcredentials.h") 
#include "localcredentials.h"
#endif

#if __has_include("localdefaultconfigfile.h") 
#include "localdefaultconfigfile.h"
#endif


//#define OLED
//#define TFT


#ifdef OLED
#define I2C_SDA 4
#define I2C_SCL 15
#define OZ890_RESETN 2
#define OLED_RSTN 16
#define BUTTON 0
#define ADC_IN      13
#endif

// TTGO T4 2.2in TFT
#ifdef TFT
#ifdef T4_V12
#include "T4_V12.h"
#endif
#ifdef T4_V13
#include "T4_V13.h"
#endif
#ifdef TTGO_T_DISPLAY
#include "ttgo-t-display.h"
#endif

#ifdef OZ890BMS
#define OZ890_RESETN 34
#define NUMOFCELL 13
#endif

#ifdef ANTBMS
#define NUMOFCELL 20
#endif

#ifdef JIKONGBMS
#define NUMOFCELL 20
#endif

#define BUTTON BUTTON_1

/*#define I2C_SDA 21
#define I2C_SCL 22
//#define OLED_RSTN 16

#define BUTTON1 38
#define BUTTON2 37
#define BUTTON3 39
#define ADC_IN      35*/
#endif

#ifndef DEFAULT_SSID
#define DEFAULT_SSID "KateBms"
#endif
#ifndef DEFAULT_PASSWORD
#define DEFAULT_PASSWORD "KateBms"
#endif
#ifndef DEFAULT_MQTT_SERVER "192.168.1.5"
#define DEFAULT_MQTT_SERVER "192.168.1.5"
#endif
// Define thios in platformio.ini
//#define LOGFILE "/battery.log"
#define CONFIGFILE "/config.json"
#ifndef DEFAULTCONFIG
#define DEFAULTCONFIG "{'ClientSsid':'KattiMesh','DeviceName':'KateBMS','MqttServer':'192.168.1.5','CellFullVolt':'4.10'}"
#endif
#define CLIENTSSID "ClientSsid"
#define CLIENTPASSWORD "ClientPassword"
#define DEFAULT_AP_SSID "KateBms"
#define DEFAULT_AP_PASSWORD ""




#endif
