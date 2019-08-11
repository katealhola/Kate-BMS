#ifndef _CONFIG_H_
#define _CONFIG_H_

#if __has_include("localcredentials.h") 
#include "localcredentials.h"
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
#include "T4_V12.h"
//#include "T4_V13.h"

#define OZ890_RESETN 34

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
#define LOGFILE "/battery.log"
#define CONFIGFILE "/config.json"
#define DEFAULTCONFIG "{'ClientSsid':'$DEFAULT_SSID ','ClientPassword':'$DEFAULT_PASSWORD'}"
#define CLIENTSSID "ClientSsid"
#define CLIENTPASSWORD "ClientPassword"



#endif
