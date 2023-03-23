#ifdef OZ890BMS
#ifndef _BMS_H_
#define _BMS_H_



#define LOGSIZE 10
#include "logline.h"
#include "logfile.h"
#include <Arduino.h>

#include "config.h"
#include "MedianFilter.h"
#define NUM_CELL_MAX 13


class Bms_  {
  public:
  
    Bms_();
    double Thermistor(int RawADC);
    bool   ReadEeprom();
    bool   init();
    void   eepromProg();
    void   dumpEEProm();
    void   reverseDumpEEProm();
    void readBms();

    
    bool bmsOk;
    byte val1,val2,stat1,stat2;
    bool first=true;
    int i2cadr; 

    unsigned long lasttime,lastLogTime,lastMqttTime,lastt;
    unsigned long dischargeLogInterval;
    unsigned long chargeLogInterval;
    unsigned long idleLogInterval;
    unsigned long logInterval;
    unsigned long mqttInterval;
    unsigned long lastReadMs;

    int n; 
    double espBatV;

    // From configFile
    float cellFullVolt;
    float cellEmptyVolt;


    double vTot=0;
    double Ah=0;
    uint8_t numCell; // Number of cells in use

    float minVolt,maxVolt;
    int minCell,maxCell;

    MedianFilter<int, 3> cellVoltFlts[NUM_CELL_MAX];
    MedianFilter<int, 3> currentFltr;
     uint16_t cellVoltages[NUM_CELL_MAX];
     uint16_t minCellVoltages[NUM_CELL_MAX];
     uint16_t idleCellVoltages[NUM_CELL_MAX];
    double current;
    

// OZ890 runtime regs
    uint8_t cellNumber; // cellNumberReg 0x06
    uint8_t shutdownStatus; // shutDownRegister // 0x15
    uint8_t errorStatus;  // CheckYesRegister 0x1c
    uint8_t fetEnable; // FET Enable Register 0x1e
    uint8_t fetDisable; // FET Disable Register 0x1f
    uint8_t senseResistor; // Current sense resistor 0x34
    uint8_t progeeprom=0; // Flag to trigger program eeprom
    uint8_t readeeprom=0; // Flag to trigger read eeprom
   // Oz890 Eeprom
     uint16_t correction[12];
    uint8_t oz890Eeprom[128];
    
    uint8_t clearlog=0;
    LogLine ll;
    LogLine combinedll;


    uint16_t logptr;
    float alog[LOGSIZE];
    float vlog[LOGSIZE];
    uint32_t mslog[LOGSIZE];
};

extern  Bms_ Bms;
#endif
#endif
