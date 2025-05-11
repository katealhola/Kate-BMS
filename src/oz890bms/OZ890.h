#ifndef _OZ890_H_
#define _OZ890_H_

#include <Arduino.h>

void doi2cscan();

int read(int reg); 

uint16_t getRegister(uint8_t regAddress);
uint8_t eepromBusy(void) ;
void setRegister(uint8_t regAddress, uint8_t regValue) ;
uint16_t getVoltage(uint8_t byteL, uint8_t byteH) ;
uint16_t getCellVoltage(uint8_t cell);
void sendStatusBit(uint8_t bit);
int getEepromWord(uint8_t address);
int getEepromWordDontDisable(uint8_t address) ;
bool putEepromByte(uint8_t address, uint8_t data) ;
bool putEepromByteDontDisable(uint8_t address, uint8_t data); 
int16_t get16bitRegister(uint8_t address);
int16_t getCurrent();
int16_t getCurrentRaw();
int16_t getCurrentOffset();

 #endif
