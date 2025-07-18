#define ANTBMS
#ifdef ANTBMS
#include "ant_bms.h"
#include "logline.h"
#include "config.h"
#include <byteswap.h>
#include "FastCRC.h"
#include "configfile.h"
#include "mqtt.h"

FastCRC16 FCRC16;
extern ConfigFile configFile;


void uartBmsTask(void *parameter)
{
  String s, s2;
  double vTmp;

  Serial.println("Created uartBmsTask:");
  Bms.init();
  Serial.println("BMS Initialized");

  while (1)
  {
    #ifdef LOGFILE
    if (Bms.clearlog)
    {
      LogFile.clearLog();
      Bms.clearlog = 0;
    };
    #endif
    Bms.readBms();
    delay(150);
  }
}



Bms_::Bms_()
{
  bmsOk = false;
};

bool Bms_::init()
{
  LogLine ll;
  File f;

  first = true;
  clearlog = 0;
  logInterval=10000;
  lasttime=millis();
  lastt=millis();
  lastLogTime=millis();
  chargeLogInterval=60*1000;
  dischargeLogInterval=60*1000;
  idleLogInterval=10*60*1000;
  mqttInterval=configFile.getMqttInterval();
  cellFullVolt=configFile.getCellFullVolt();

  Serial2.begin(19200, SERIAL_8N1, RXD2, TXD2);
  vTot = 0;
  Ah = 0;
  sleep(3);
  
  
  numCell = 0;
  for (int i = 0; i < NUM_CELL_MAX; i++)
    minCellVoltages[i] = 43000;

    int index=-1;
  #ifdef LOGFILE
    ll=LogFile.getLogLineAt(index,f);
    if(ll.isValid()) {
      String s=ll.toString();
      Ah=ll.ah;
      Serial.print("Read initial logLine:"+s);
      Serial.println();
      Serial.println("Setting Ah:"+String(Ah,3));
  } 
  #endif
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
  /*Serial.print("Sending to bms: "+String(crc,16));
  for (int i = 0; i < frameLen; i++)
    Serial.print(String(frame[i] < 16 ? " 0" : " ") + String(frame[i], 16));
  Serial.println();*/
  for(int i=0;i<frameLen;i++) Serial2.write(*p++);
}

void Bms_::parseAntFrame(unsigned char *frame, unsigned int frameLen)
{
  ant_frame *ant = (ant_frame *)frame;

  unsigned short crc=FCRC16.modbus(frame+4, 136-4);
#if ANTDEBUG2
  Serial.print(String("frame:") + String(frameLen) +" "+ String(crc,16)+":"+String(ant->checkSum,16)+String(" ")+String((int)&(ant->numSeriesCell)-(int)frame)+" ");
  for (int i = 0; i < frameLen; i++)
    Serial.print(String(frame[i] < 16 ? " 0" : " ") + String(frame[i], 16));
  Serial.println();
#endif
  float capEst=0.0;

  
  vTot = __bswap_16(ant->vtot) / 10.0;
  short cur = __bswap_16(ant->current[1]);
  current = cur / -10.0; // - is discharge
  short cur0 = __bswap_16(ant->current[0]);
  uint32_t ttime=__bswap_32(ant->cumulativeTime);
  numCell=ant->numSeriesCell;
  float remCap=__bswap_32(ant->remainingCapacity);
  float chargePersentage=ant->chargePersentage;
  SoC=chargePersentage;
  remaining_Ah=remCap*0.000001;
  capacity_Ah=__bswap_32(ant->capacity);

  for (int i = 0; i < numCell; i++)
    cellVoltages[i] = __bswap_16(ant->vcell[i]);

  #if ANTDEBUG
  Serial.print("V:"+String(vTot) + "V "+String(current) + "A " + String(cur0) + " "+String(ant->chargePersentage)+"% "+String(remaining_Ah,3)+"Ah "+String(ant->remainingCapacity,16)+" " +String(ttime)+" "+String(ant->numSeriesCell));
  Serial.println(); 
  #endif
  
  #ifdef ANTDEBUG2
  for (int i = 0; i < numCell; i++)
    Serial.print(String(__bswap_16(ant->vcell[i]) / 1000.0) + " ");
  Serial.println();
  #endif
  minVolt = 100.0;
  maxVolt = 0;
  for (int i = 0; i < numCell; i++) {
    if ((cellVoltages[i] / 1000.0) > maxVolt) {
      maxCell = i;
      maxVolt = cellVoltages[i] / 1000.0;
    }
    if ((cellVoltages[i] / 1000.0) < minVolt) {
      minCell = i;
      minVolt = cellVoltages[i] / 1000.0;
    }
  }
  if (current < 0.5 && current > -0.5) {
    for (int i = 0; i < numCell; i++) idleCellVoltages[i] = Bms.cellVoltages[i];
  }

  if (current <= -0.2) {
    for (int i = 0; i < numCell; i++) {
      if (cellVoltages[i] < minCellVoltages[i]) minCellVoltages[i] = cellVoltages[i];
    }
  }
  if (current >= 0.5) {
    for (int i = 0; i < numCell; i++) minCellVoltages[i] = cellVoltages[i]; // charging, minimum voltage not known
  }
  uint32_t status=(ant->chargeFetState)<<24+(ant->dischargeFetState)<<16+(ant->balancerState)<<8;
  unsigned long t=millis();
  Ah+=(t-lastt)*current/(1000*3600); // ms in hour
  //if(current>0.2 && maxVolt>cellFullVolt) Ah=0; // Battery full and chrging, reset Ah
  ll = LogLine(vTot,    current, Ah,        remCap,                 chargePersentage,       capEst,            status,          numCell,           &cellVoltages[0],       t,    ttime);

  // Log and send 

  //     LogLine(float _v,float _a,float _ah,float _remainingCapacity,float _chargePersentage,float _capacityEst,uint32_t _status,uint16_t _numcell, uint16_t *_cellVoltages,long int _ms,uint32_t _t)   
  if(((lastLogTime+chargeLogInterval)<t && current>0.2 )|| ((lastLogTime+dischargeLogInterval)<t  && current<-0.2) || (lastLogTime+idleLogInterval)<t)
    {
    #ifdef LOGFILE
    LogFile.addLogLine(&combinedll);
    #endif
    combinedll=ll;
    lastLogTime=t;
  } else combinedll.combine(ll);



  //LogFile.addLogLine(&ll);
  lastt=t;
};

String Bms_::antFrameToJson()
{
  String s;
  ant_frame *ant = (ant_frame *)frame;
  s=String("{\"cellVolt\":[");
  for (int i = 0; i < NUM_CELL_MAX; i++) {
    s+=String(__bswap_16(ant->vcell[i]) / 1000.0);
    if(i<(NUM_CELL_MAX-1)) s+="'";
  };
  s+="\n";
  s+=String("\"vtot\":")+String(__bswap_16(ant->vtot) / 10.0)+",\n";
  s+=String("\"I1\":")+String(__bswap_16(ant->current[1]/10.0))+",\n";
  s+=String("\"I0\":")+String(__bswap_16(ant->current[0]/10.0))+",\n";
  s+=String("\"t\":")+String(__bswap_32(ant->cumulativeTime))+",\n";
  s+=String("\"chargePresentage\":")+String(ant->chargePersentage)+",\n";
  s+=String("\"capacity\":")+String(__bswap_32(ant->capacity))+",\n";
  s+=String("\"remainingCapacity\":")+String(__bswap_32(ant->remainingCapacity))+",\n";
  s+=String("\"cycleCapacity\":")+String(__bswap_32(ant-> cycleCapacity))+",\n";
  s+=String("\"t\":")+String(__bswap_32(ant->cumulativeTime))+",\n";
  s+=String("\"batNumHighCellVolt\":")+String(ant->batNumHighCellVolt)+",\n";
  s+=String("\"highCellVolt\":")+String(__bswap_16(ant->highCellVolt))+",\n";
  s+=String("\"batNumLowCellVolt\":")+String(ant->batNumLowCellVolt)+",\n";
  s+=String("\"lowCellVolt\":")+String(__bswap_16(ant->lowCellVolt))+",\n";
  s+=String("\"avgCellVolt\":")+String(__bswap_16(ant->avgCellVolt))+",\n";
  s+=String("\"numSeriesCell\":")+String(ant->numSeriesCell)+",\n";
  s+=String("\"disChargeFetVolt\":")+String(__bswap_16(ant->disChargeFetVolt))+",\n";
  s+=String("\"hargeFetVolt\":")+String(__bswap_16(ant->chargeFetVolt))+",\n";
  s+=String("\"zeroCurrentVolt\":")+String(__bswap_16(ant->zeroCurrentVolt))+",\n";
  s+="}";
  return s;
};

Bms_ Bms = Bms_();
#endif