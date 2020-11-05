#ifdef ANTBMS
#ifndef _BMS_H_
#define _BMS_H_



#define LOGSIZE 10
#include "logline.h"
#include "logfile.h"
#include <Arduino.h>
#include "FS.h"
#include <SD.h>
#include "SPIFFS.h"
#include "config.h"
#include "MedianFilter.h"
#define NUM_CELL_MAX 32

#define ANT_BUF_LEN 160

typedef class {
  public:
  unsigned char frame_sync[4]; // frame sync 0xaa, 0x55,0xaa,0xff
  unsigned short vtot;
  unsigned short vcell[NUM_CELL_MAX];
  unsigned short current[2];
  unsigned char chargePersentage;
  unsigned int capacity;  
  unsigned int remainingCapacity;
  unsigned int cycleCapacity;
  unsigned int cumulativeTime;
  unsigned short temperature[6];
  unsigned char chargeFetState;
  unsigned char dischargeFetState;
  unsigned char balanderState;
  unsigned short tireLenght;
  unsigned short pulseNumber;
  unsigned char relaySwitch;
  unsigned int power;
  unsigned char batNumHighCellVolt;
  unsigned short highCellVolt;
  unsigned char batNumLowCellVolt;
  unsigned short lowCellVolt;
  unsigned short avgCellVolt;
  unsigned char numSeriesCell;
  unsigned short disChargeFetVolt;
  unsigned short chargeFetVolt;
  unsigned short zeroCurrentVolt;
  unsigned int inBalanceCellFlag;
  unsigned short systemLog;
  unsigned short checkSum;
  } __attribute__ ((packed)) ant_frame  ;

class Bms_  {
  enum req {REQ_NULL,REQ_READ,REQ_READ_REM_CAP};
  public:
  
    Bms_();
    double Thermistor(int RawADC);
    bool   ReadEeprom();
    bool   init();
    void   eepromProg();
    void   dumpEEProm();
    void   reverseDumpEEProm();
    void   readBms();
    void   sendBms(unsigned char *frame, unsigned int frameLen);
    void   parseAntFrame(unsigned char *frame, unsigned int frameLen);
    void   sendBmsReq(req,int parameter);
    String antFrameToJson();
    unsigned char c, c1, c2, c3;   // Frame header detection
    unsigned char buffer[ANT_BUF_LEN];
    unsigned int  p;
    unsigned char frame[ANT_BUF_LEN];
    unsigned int frameLen;
    bool bmsOk;
    byte val1,val2,stat1,stat2;
    bool first=true;
    long lasttime;
    long lastLogTime;
    long logInterval;
    long lastReadMs;
    int n; 
    double espBatV;

    double vTot=0;
    double Ah=0;

    float minVolt,maxVolt;
    int minCell,maxCell;


    MedianFilter<int, 3> cellVoltFlts[NUM_CELL_MAX];
    MedianFilter<int, 3> currentFltr;
     uint16_t cellVoltages[NUM_CELL_MAX];
     uint16_t minCellVoltages[NUM_CELL_MAX];
     uint16_t idleCellVoltages[NUM_CELL_MAX];
    double current;
    uint8_t cellNumber; // cellNumberReg 0x06
    uint8_t shutdownStatus; // shutDownRegister // 0x15
    uint8_t errorStatus;  // CheckYesRegister 0x1c
    uint8_t fetEnable; // FET Enable Register 0x1e
    uint8_t fetDisable; // FET Disable Register 0x1f
    uint8_t senseResistor; // Current sense resistor 0x34
    uint8_t progeeprom=0; // Flag to trigger program eeprom
    uint8_t readeeprom=0; // Flag to trigger read eeprom
    uint8_t clearlog=0;
    LogLine ll;


    uint16_t logptr;
    float alog[LOGSIZE];
    float vlog[LOGSIZE];
    uint32_t mslog[LOGSIZE];
};

extern  Bms_ Bms;
#endif
#endif
