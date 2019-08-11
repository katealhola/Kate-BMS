#ifndef _LOGLINE_H_
#define _LOGLINE_H_

#include <stdint.h>
#include <Arduino.h>

#define NUMOFCELL 13

class LogLine {
   uint32_t sync;
  public: 
    LogLine() ;
    LogLine(float _v,float _a,float _ah,uint8_t _errorStatus,uint8_t _shutdownStatus,uint8_t _fetDisable,    uint16_t *_cellVoltages,long int _ms);
    void combine(LogLine ll);
    String toJson();
    String toString() ;
    bool isValid();
 
    float v;
    float a;
    float ah;
    uint16_t speed;
    uint16_t cellVoltages[NUMOFCELL];
    uint8_t fetDisable;
    uint8_t shutdownStatus;
    uint8_t errorStatus;
    uint32_t ms;
 };
 #endif

