#ifndef _LOGLINE_H_
#define _LOGLINE_H_

#include <stdint.h>
#include <Arduino.h>
#include <config.h>



class LogLine {
   uint32_t sync;
  public: 
    LogLine() ;
    LogLine(float _v,float _a,float _ah,float remainingCapacity,uint32_t _status,uint16_t *_cellVoltages,long int _ms);
    void awgSum(LogLine ll);
    void awgDiv(int n);
    String toJson();
    String toString() ;
    bool isValid();
 
    float v;
    float a;
    float ah; // Use Ah
    float capacityEstimate;
    float remainingCapacity;
    uint16_t speed;
    uint32_t status;
    uint32_t ms;
    uint16_t cellVoltages[NUMOFCELL];
 };
 #endif

