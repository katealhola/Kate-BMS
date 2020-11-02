#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <stdint.h>
#include <Arduino.h>
#include <config.h>
#include "FS.h"
#include <SD.h>
#include "SPIFFS.h"
#include "logline.h"



class LogFile_ {
    public:
    File logFile;
    LogFile_();
    void addLogLine(LogLine *ll);
    void clearLog();
    uint32_t lastLogMs;
    uint32_t dischargeLogPeriod;
    uint32_t chargeLogPeriod;
    uint32_t idleLogPeriod;


};

extern  LogFile_ LogFile;

#endif