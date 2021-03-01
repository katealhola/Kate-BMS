#ifndef _LOGLINE_H_
#define _LOGLINE_H_

#include <stdint.h>
#include <Arduino.h>
#include <config.h>



class LogLine {
  public: 
    uint32_t sync;
    LogLine();
    LogLine(const LogLine &ll);
    //LogLine(float _v,float _a,float _ah,float remainingCapacity,uint32_t _status,uint16_t *_cellVoltages,long int _ms);
    LogLine(float _v,float _a,float _ah,float _remainingCapacity,float _chargePersentage,float _capacityEst,uint32_t _status,uint16_t _numcell, uint16_t *_cellVoltages,long int _ms,uint32_t _t);   

    void combine(LogLine ll);
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
    float chargePersentage;
    uint16_t speed;
    uint16_t numCell;
    uint32_t status;
    uint32_t ms;
    uint32_t t;
    uint16_t cellVoltages[NUMOFCELL];
 };
 #endif

