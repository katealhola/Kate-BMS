#include "config.h"
#include "OZ890.h"
#include "Wire.h"

int i2cadr = 0x30; 

int read(int reg) {
  byte val1, val2, stat1, stat2;
  Wire.beginTransmission(i2cadr);
  Wire.write(reg);
  stat1 = Wire.endTransmission(false);
  stat2 = Wire.requestFrom(i2cadr, 2);
  val1 = Wire.read();
  val2 = Wire.read();
#ifdef debug
  Serial.println("Val1: " + String(val1) + " " + String(val1, BIN));
  Serial.println("Val2: " + String(val2) + " " + String(val2, BIN));
  Serial.println("Word: " + String(((val2 << 8) + val1)) + " " + String(((val2 << 8) + val1), BIN));
#endif
  return ((val2 << 8) + val1);
}



uint16_t getRegister(uint8_t regAddress) {
  // try send device address (write) and check for errors

  Wire.beginTransmission(i2cadr);
  Wire.write(regAddress);
  int tstat=Wire.endTransmission(false);
  int rstat=Wire.requestFrom(i2cadr, 1);
  uint8_t byte = Wire.read();
  //Serial.println("readReg(w="+String(tstat)+" r="+String(rstat)+"):"+String(regAddress,16)+"="+String(byte,16));
  if(tstat!=0) {
    Serial.println("readReg(w="+String(tstat)+" r="+String(rstat)+"):"+String(regAddress,16)+"="+String(byte,16)+" SCL="+String(digitalRead(I2C_SCL))+" SDA="+String(digitalRead(I2C_SDA)));
    if(!digitalRead(I2C_SCL) && !digitalRead(I2C_SDA)) {
      Serial.println("Reset OZ890 SCL="+String(digitalRead(I2C_SCL))+" SDA="+String(digitalRead(I2C_SDA)));
  /*    digitalWrite (OZ890_RESETN, LOW);
      delay(200);
      digitalWrite (OZ890_RESETN, HIGH);*/
   }

  // Wire.reset();
  };
  return byte;
}



void setRegister(uint8_t regAddress, uint8_t regValue) {
  Wire.beginTransmission(i2cadr);
  Wire.write(regAddress);
  Wire.write(regValue);
  Wire.endTransmission(true);
}


boolean waitEepromBysy()
{
  int timeout=10;
   while (timeout-- && eepromBusy()); // wait for eeprom not be busy
   return timeout>0;
  
}

uint8_t eepromBusy(void) {
  uint8_t byte = getRegister(0x5f); // EEPROM Control Register
  return (byte & (1 << 7)); // bit 7 = busy flag
}

uint16_t getVoltage(uint8_t byteL, uint8_t byteH) {
  uint32_t val = (byteL >> 3) & 0b00011111;
  val = (byteH << 5) | val;
  return (val * 122) / 100 ;
}

uint16_t getCellVoltage(uint8_t cell) {
  if (!cell || cell > 13) return 0;

  uint8_t regAddr = 0x30 + (cell * 2);
  return getVoltage(getRegister(regAddr), getRegister(regAddr + 1));
}


void sendStatusBit(uint8_t bit) {
  if (bit) Serial.write(("yes"));
  else Serial.write(("no"));
}

int getEepromWord(uint8_t address) {

  boolean eepromOk=true;
  Serial.println("getEepromWord");
  if(eepromOk && (eepromOk=waitEepromBysy()))  setRegister(0x5e, address); // set eeprom address to read
  Serial.println("getEepromWord 2");
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5f, 0x55); // b01010101 (or 0x55) set eeprom access & word reading mode

  uint8_t byte1, byte2;
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  byte1 = getRegister(0x5d); // odd addr
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  byte2 = getRegister(0x5c); // even addr

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5f, 0x00); // disable eeprom access
  Serial.print(String("getEepromByte(")+String(address)+")="+String(byte2,16)+":"+String(byte1,16)+" ");

  if(!eepromOk) return -1;
   return (byte2<<8)+byte1;
}

int getEepromWordDontDisable(uint8_t address) {
  boolean eepromOk=true;
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5e, address); // set eeprom address to read

  if(eepromOk && (eepromOk=waitEepromBysy()))  
  setRegister(0x5f, 0x55); // b01010101 (or 0x55) set eeprom access & word reading mode

  uint8_t byte1, byte2;
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  byte1 = getRegister(0x5d); // odd addr
 if(eepromOk && (eepromOk=waitEepromBysy())) 
  byte2 = getRegister(0x5c); // even addr

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  //setRegister(0x5f, 0x00); // disable eeprom access

  if(!eepromOk) return -1;
  if (address % 2) return byte1;
  else return byte2;
}

bool putEepromByte(uint8_t address, uint8_t data) {
   bool eepromOk=true;
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5c, data); // data to write to eeprom

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5e, address); // set eeprom address to write

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5f, 0x5B); // eeprom byte write

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5f, 0x5A); // eeprom mapping

  if(eepromOk && (eepromOk=waitEepromBysy())) setRegister(0x5f, 0x00); // disable eeprom access

  if(eepromOk) eepromOk=waitEepromBysy(); 
  return eepromOk;
}

bool putEepromByteDontDisable(uint8_t address, uint8_t data) {
  bool eepromOk=true;
  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5c, data); // data to write to eeprom

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5e, address); // set eeprom address to write

  if(eepromOk && (eepromOk=waitEepromBysy())) 
  setRegister(0x5f, 0x5B); // eeprom byte write

  if(eepromOk) eepromOk=waitEepromBysy(); 
  return eepromOk;
}

int16_t get16bitRegister(uint8_t address)
{
  uint16_t l,h;
  l=getRegister(address);
   h=getRegister(address+1);
   return h*256+l;
}



int16_t getCurrentRaw() {  
  //int16_t val = (getRegister(0x55) << 8) + getRegister(0x54);
  //int16_t val=get16bitRegister(0x54);
  uint8_t cl=getRegister(0x54);
  uint8_t ch=getRegister(0x55);
 
  uint16_t val=ch*256+cl;
  return val;
}

int16_t getCurrentOffset() {
  
  int16_t val = (getRegister(0x5b) << 8) | getRegister(0x5a);
  return val;
}

