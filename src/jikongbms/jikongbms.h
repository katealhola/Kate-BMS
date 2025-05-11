#ifdef JIKONGBMS
#ifndef _BMS_H_
#define _BMS_H_

#define LOGSIZE 10
#ifdef LOGFILE
#include "logfile.h"
#endif
#include "logline.h"
#include <Arduino.h>
#include "FS.h"
#include <SD.h>
#include "SPIFFS.h"
#include "config.h"
#include "MedianFilter.h"

#define NUM_CELL_MAX 32

#define ANT_BUF_LEN 160


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
  bool init(int modbus_id = 1);
  void readBms();
  void parseJkFrame(unsigned char *frame, unsigned int frameLen);
  void sendBmsReq(req, int parameter);
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
  float espBatV;

  int modbusId;

  float vTot = 0;
  float Ah = 0;
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
  float current;

  float capacity_Ah;
  float remaining_Ah;
  float SoC;


  uint8_t clearlog = 0;
  LogLine ll;
  LogLine combinedll;
};

extern Bms_ Bms;
#ifdef BMS2
extern  Bms_ Bms2;
#endif
#endif
#endif
