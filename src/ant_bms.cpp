#ifdef ANTBMS
#include "ant_bms.h"
#include "logline.h"
#include "config.h"
#include <byteswap.h>
#include "FastCRC.h"

FastCRC16 FCRC16;


Bms_::Bms_()
{
  bmsOk = false;
};

bool Bms_::init()
{
  first = true;
  readeeprom = 0;
  clearlog = 0;
  logInterval=10000;
  lasttime=millis();
  lastLogTime=millis();
  Serial2.begin(19200, SERIAL_8N1, RXD2, TXD2);
  vTot = 0;
  Ah = 0;
  sleep(3);
  //bmsOk = ReadEeprom();
  int cells = 13;
  //cellNumber = oz890Eeprom[0x26] & 0x0f;
  cellNumber = 13;
  for (int i = 0; i < Bms.cellNumber; i++)
    minCellVoltages[i] = 43000;
  return bmsOk;
}

void Bms_::readBms()
{
  if((lasttime+200)<millis()) {
    sendBmsReq(REQ_READ,0);
    lasttime=millis();
  }
  float vTmp = 0;
  if (p >= sizeof(buffer))
    p = 0;
  String s;
  while (Serial2.available())
  {
    c3 = c2;
    c2 = c1;
    c1 = c;
    c = Serial2.read();
    lastReadMs=millis();
    // Serial.print(String(" ")+String(p)+String(c<16? " 0" : " ")+String(c, 16));
    if ((c3 == 0xaa) && (c2 == 0x55) && (c1 == 0xaa) && (c == 0xff))
    {
      p = 0;
      buffer[p++] = c3;
      buffer[p++] = c2;
      buffer[p++] = c1;
      buffer[p++] = c;
    }
    else
    {
      buffer[p++] = c;
      if (p >= sizeof(buffer))
        p = 0;
    }
  }
  if ((lastReadMs+100)<millis() && p > 0 && p < sizeof(buffer) && buffer[0] == 0xaa && buffer[1] == 0x55 && buffer[2] == 0xaa && buffer[3 == 0xff])
  {
    memcpy(&frame, &buffer, p);
    frameLen = p;
    parseAntFrame(frame, frameLen);
    lasttime=millis();
    p = 0;
  }
}

void Bms_::sendBmsReq(req req,int parameter)
{
  unsigned char *reqFrame;
  unsigned int reqLen=0;
  switch(req) {
    case REQ_READ:         reqFrame=(unsigned char*)"\x5a\x5a\x00\x00\x01\x01"; reqLen=6; break;
    case REQ_READ_REM_CAP: reqFrame=(unsigned char*)"\x5a\x5a\x0b\x33\x01\x01\x32\x5f"; reqLen=6; break;
  }
  if(reqLen>0) sendBms(reqFrame,reqLen); 
}

void Bms_::sendBms(unsigned char *frame, unsigned int frameLen)
{
  unsigned char *p=frame;
  unsigned short crc=FCRC16.modbus(frame+2, sizeof(2));
  Serial.print("Sending to bms: "+String(crc,16));
  for (int i = 0; i < frameLen; i++)
    Serial.print(String(frame[i] < 16 ? " 0" : " ") + String(frame[i], 16));
  Serial.println();
  for(int i=0;i<frameLen;i++) Serial2.write(*p++);
}

void Bms_::parseAntFrame(unsigned char *frame, unsigned int frameLen)
{
  ant_frame *ant = (ant_frame *)frame;

  unsigned short crc=FCRC16.modbus(frame+4, 136-4);
  Serial.print(String("frame:") + String(frameLen) +" "+ String(crc,16)+":"+String(ant->checkSum,16)+String(" ")+String((int)&(ant->numSeriesCell)-(int)frame)+" ");
  for (int i = 0; i < frameLen; i++)
    Serial.print(String(frame[i] < 16 ? " 0" : " ") + String(frame[i], 16));
  Serial.println();

  
  vTot = __bswap_16(ant->vtot) / 10.0;
  short cur = __bswap_16(ant->current[1]);
  current = cur / 10.0;
  short cur0 = __bswap_16(ant->current[0]);
  unsigned int ttime=__bswap_32(ant->cumulativeTime);
  Serial.print("V:"+String(vTot) + "V "+String(current) + "A " + String(cur0) + " "+String(ant->chargePersentage)+"% "+String(ttime)+" "+String(ant->numSeriesCell));
  for (int i = 0; i < NUM_CELL_MAX; i++)
    cellVoltages[i] = __bswap_16(ant->vcell[i]);
  Serial.println();
  for (int i = 0; i < NUM_CELL_MAX; i++)
    Serial.print(String(__bswap_16(ant->vcell[i]) / 1000.0) + " ");
  Serial.println();
  if(millis()>lastLogTime+logInterval) {
    lastLogTime=millis();
    ll = LogLine(vTot, current, Ah, 0, &cellVoltages[0], lasttime);
   LogFile.addLogLine(&ll);
  }
};

Bms_ Bms = Bms_();
#endif