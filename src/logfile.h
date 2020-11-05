#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <stdint.h>
#include <Arduino.h>
#include <config.h>
#include "FS.h"
#include <SD.h>
#include "SPIFFS.h"
#include "logline.h"

#define NFILES 4

struct logF {
    String name;
    int seq;
    int fileSize;
    int items;
};

class LogFile_ {
    public:
    struct logF files[NFILES];
    File logFile;
    LogFile_();
    void addLogLine(LogLine *ll);
    void scanLogFiles();
    void clearLog();
    uint32_t lastLogMs;
    uint32_t dischargeLogPeriod;
    uint32_t chargeLogPeriod;
    uint32_t idleLogPeriod;


};

extern  LogFile_ LogFile;

#endif