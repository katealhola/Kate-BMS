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

typedef class
{
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
  unsigned char balancerState;
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
} __attribute__((packed)) ant_frame;

class Bms_
{
  enum req
  {
    REQ_NULL,
    REQ_READ,
    REQ_READ_REM_CAP
  };

public:
  Bms_();
  double Thermistor(int RawADC);
  bool ReadEeprom();
  bool init();
  void eepromProg();
  void dumpEEProm();
  void reverseDumpEEProm();
  void readBms();
  void sendBms(unsigned char *frame, unsigned int frameLen);
  void parseAntFrame(unsigned char *frame, unsigned int frameLen);
  void sendBmsReq(req, int parameter);
  String antFrameToJson();
  unsigned char c, c1, c2, c3; // Frame header detection
  unsigned char buffer[ANT_BUF_LEN];
  unsigned int p;
  unsigned char frame[ANT_BUF_LEN];
  unsigned int frameLen;
  bool bmsOk;
  byte val1, val2, stat1, stat2;
  bool first = true;
  unsigned long lasttime,lastLogTime,lastMqttTime,lastt;
  unsigned long dischargeLogInterval;
  unsigned long chargeLogInterval;
  unsigned long idleLogInterval;
  unsigned long logInterval;
  unsigned long mqttInterval;
  unsigned long lastReadMs;
  int  n;
  double espBatV;

  double vTot = 0;
  double Ah = 0;
  uint8_t numCell; // Number of cells in use
  // From configFile
    float cellFullVolt;
    float cellEmptyVolt;


  float minVolt, maxVolt;
  int minCell, maxCell;

  MedianFilter<int, 3> cellVoltFlts[NUM_CELL_MAX];
  MedianFilter<int, 3> currentFltr;
  uint16_t cellVoltages[NUM_CELL_MAX];
  uint16_t minCellVoltages[NUM_CELL_MAX];
  uint16_t idleCellVoltages[NUM_CELL_MAX];
  double current;


  uint8_t clearlog = 0;
  LogLine ll;
  LogLine combinedll;
};

extern Bms_ Bms;
#endif
#endif
