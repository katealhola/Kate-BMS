#define JIKONGBMS
#ifdef JIKONGBMS
#include "jikongbms.h"
#include "logline.h"
#include "config.h"
#include <byteswap.h>
#include "configfile.h"
#include "mqtt.h"
#include "DFRobot_RTU.h"

extern ConfigFile configFile;

#define MODBUS

#ifdef MODBUS
DFRobot_RTU modbus(&Serial2);
#endif

unsigned short htons(unsigned short s)
{
  return (((s&0xff)<<8)) | (((s>>8)&0xff));
}


void uartBmsTask(void *parameter)
{
  String s, s2;
  double vTmp;
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Created uartBmsTask ");
  Bms.init(1);
  #ifdef BMS2
  Bms2.init(2);
  #endif
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
    delay(1500);
    #ifdef BMS2
    Bms2.readBms();
    #endif
    delay(1500);
  }
}

Bms_::Bms_()
{
  bmsOk = false;
};

bool Bms_::init(int modbus_id )
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
  modbusId=modbus_id;

  vTot = 0;
  Ah = 0;
  
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

void Bms_::parseJkFrame(unsigned char* frame,unsigned int frameLen)
{

};

void Bms_::readBms()
{
  uint16_t readregs[128];
  Serial.println("Reading modbus:");
  int numregs=37;
  #ifdef MODBUS
  uint8_t ret = modbus.readHoldingRegister(modbusId, 0x1200,&readregs,numregs*2);
  #endif
  Serial.printf("modbus id=%d 0x1200 read=%d\n",modbusId,ret);
  if(ret == 0){
    for(int i=0;i<numregs;i++) readregs[i]=htons(readregs[i]);
    for(int i=0;i<numregs;i++) {
      if((i&7)==0)  Serial.printf("%02x ",i);
      Serial.printf("%04x %05d  ",readregs[i],readregs[i]);
      if((i&7)==7)  Serial.printf("\n");
    }
    int cellSta=readregs[33]+(readregs[32]<<16);
    n=cellSta;
    int count = 0;
    while (n) {
        n &= (n - 1);  // clear the least significant bit set
        count++;
    }
    numCell=count;
    Serial.printf("cellSta=%08x numcell=%d\n",cellSta,numCell);
    for(int i=0;i< NUM_CELL_MAX;i++) cellVoltages[i]=readregs[i];
  }
  Serial.printf("\n");
  #if 0 
  numregs=37;
  ret = modbus.readHoldingRegister(1, 0x1240,&readregs,numregs*2);
  Serial.printf("modbus 0x1240 read=%d\n",ret);
    if(ret == 0){
      for(int i=0;i<numregs;i++) {
        if((i&7)==0)  Serial.printf("%02x ",i);
        Serial.printf("%04x %05d %05d  ",readregs[i],readregs[i],htons(readregs[i]));
        if((i&7)==7)  Serial.printf("\n");
      }
  }
  #endif
  numregs=32;
  Serial.printf("\n");
  ret = modbus.readHoldingRegister(modbusId, 0x128a,&readregs,numregs*2);
    Serial.printf("modbus id=%d 0x128a read=%d\n",modbusId,ret);
    if(ret == 0){
      for(int i=0;i<numregs;i++) readregs[i]=htons(readregs[i]);
      for(int i=0;i<numregs;i++) {
        if((i&7)==0)  Serial.printf("%02x ",i);
        Serial.printf("%04x %05d   ",readregs[i],readregs[i]);
        if((i&7)==7)  Serial.printf("\n");
      }
    float tempMos=htons(readregs[0])*0.1;
    float V=(readregs[4]+(readregs[3]<<16))*0.001;
    float W=(readregs[6]+(readregs[5]<<16))*0.001;
    float A=(readregs[8]+(readregs[7]<<16))*0.001;
    vTot=V;
    current=A;
    float tempBat1=readregs[9]*0.1;
    float tempBat2=readregs[10]*0.1;
    // 11 and 12 status word
    float balA=readregs[13]*0.001;
    SoC=readregs[14]&0xff;
    float remAh=(readregs[15]+(readregs[14]<<16))*0.001;
    float fullAh=(readregs[17]+(readregs[16]<<16))*0.001;
    Serial.printf("V=%f A=%f W=%f mosTmp=%f batTmp1=%f batTmp2=%f balA=%f SoC=%d remAh=%f fullAh=%f\n",
      V,A,W,tempMos,tempBat1,tempBat2,balA,SoC,remAh,fullAh);

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
  }
  int status=0;
  unsigned long t=millis();
  uint32_t ttime=0;
  ll = LogLine(vTot,    current, Ah,        remaining_Ah,                 SoC,       capacity_Ah,            status,          numCell,           &cellVoltages[0],       t,    ttime);

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
 


}

Bms_ Bms = Bms_();
#ifdef BMS2
Bms_ Bms2 = Bms_();
#endif
#endif