#ifdef OZ890BMS
#include "oz890_bms.h"
#include "logline.h"
#include "OZ890.h"
#include "config.h"

#include "configfile.h"
#include "mqtt.h"

extern ConfigFile configFile;

#ifdef OZ890BMS
void i2cTask(void *parameter)
{
  String s, s2;
  double vTmp;

  Serial.print("Created i2cTask: Executing on core ");
  Serial.println(xPortGetCoreID());
  Bms.init();
  Serial.println("BMS Initialized");

  unsigned int n = 0;
  int refresh = 0;
  unsigned int dispTimeout = 0;
  int bt = 0;
  int btb = 0;
  int b;
  int dispmode = 0;
  while (1)
  {
#ifndef TFT // TFT dispolay is handled in separate tesk
    b = digitalRead(BUTTON);
    if (b == 0 && bt == 1)
    {
      refresh = 1;
      dispTimeout = n;
    }
    bt = b;
    // Serial.println("Button="+String(bt)+" "+String(n)+" "+String(dispTimeout)+" "+String(millis()));
#endif

    n++;

    if (Bms.bmsOk && Bms.progeeprom)
    {
      Serial.println("Programming eeprom");
      Bms.progeeprom = 0;
      Bms.eepromProg();
    }
    if ((n % 50 == 0 && !Bms.bmsOk) || Bms.readeeprom)
    {
      Serial.println("Reading  eeprom");

      Bms.bmsOk = Bms.ReadEeprom();
      Bms.readeeprom = 0;
    }
    if (Bms.clearlog)
    {
      Bms.clearlog = 0;
      LogFile.clearLog();
    }
    s = "";
    if (n % 10 == 0)
    {
      Bms.readBms();
      refresh = 1;
    }
    if (refresh)
    {
      refresh = 0;
#ifdef OLED

      display.init();
      display.clear(); // clear the display

      if ((bt == 0) && (btb == 1))
        dispmode = dispmode >= 2 ? 0 : dispmode + 1;
      btb = bt;
      if (fabs(Bms.current) > 0.5 || Bms.fetDisable)
        dispTimeout = n;
      if (n < (dispTimeout + 600))
      {
        if (bt)
          statusDisplay();
        else
        {
          if (dispmode == 0)
            networkDisplay();
          if (dispmode == 1)
            barplot(display);
          if (dispmode == 2)
            cellVoltagesDisplay();
        }
      }
      display.display();
#endif
    }

    delay(100);
  }
}
#endif



Bms_::Bms_() {
  bmsOk = false;
};

bool Bms_::init() {
  first = true;
  progeeprom = 0;
  readeeprom=0;
  clearlog = 0;
  i2cadr = 0x30;
  lasttime;

  logInterval=10000;
  lasttime=millis();
  lastt=millis();
  lastLogTime=millis();
  chargeLogInterval=60*1000;
  dischargeLogInterval=60*1000;
  idleLogInterval=10*60*1000;
  mqttInterval=configFile.getMqttInterval();
  cellFullVolt=configFile.getCellFullVolt();

  vTot = 0;
  Ah = 0;
  sleep(3);
  bmsOk = ReadEeprom();
  int cells = 13;
  cellNumber = oz890Eeprom[0x26] & 0x0f;
  //cellNumber = 13;
  numCell=cellNumber;
  senseResistor = oz890Eeprom[0x34];
  if (senseResistor == 0) senseResistor = 25; // 25 mOhm
  
   for (int i = 0; i < Bms.cellNumber; i++) minCellVoltages[i]=43000;
  return bmsOk;

}

bool Bms_::ReadEeprom()
{
  bool readOk=true;
  for (int i = 0; i < 128; i+=2) {
    if ((i & 0xf) == 0)Serial.print(String( i) + " ");
    int eepromWord=getEepromWord(i);
    
    if(eepromWord>=0)
      {
        oz890Eeprom[i] = (eepromWord>>8)&0xff;
        oz890Eeprom[i+1] = eepromWord&0xff;
    
    Serial.print((String((oz890Eeprom[i] < 16) ? " 0" : " ")) + String(oz890Eeprom[i], 16));
    Serial.print((String((oz890Eeprom[i+1] < 16) ? " 0" : " ")) + String(oz890Eeprom[i+1], 16));
      } else {
        Serial.print(String(eepromWord));
        readOk=false;
      }
    
    if ((i & 0xf) == 0xe)Serial.println();
  }
  if(readOk) for (int i = 0; i < 12; i++) {
    correction[i] = ((int8_t)oz890Eeprom[0x05 + i]) * 1.22;
  //  Serial.println("correction(" + String(i + 1) + ")=" + String(correction[i] / 1000.0, 3));
  }
  return readOk ;
}

void Bms_::eepromProg() {

  //  dumpEEProm();

  while (eepromBusy()); // wait for eeprom not be busy

  //setRegister(0x5f, 0x5A);
  // authenticate
  //setPassword();


  Serial.println("Block erase...");
  setRegister(0x5f, 0b1010011); // block erase!
  while (eepromBusy());

  Serial.println("Mapping...");
  setRegister(0x5f, 0b1011010); // eeprom unfreeze / mapping / block read

  Serial.println("Reverse dump...");
  reverseDumpEEProm();

  /* for (int i = 0; i < 12; i++)
     putEepromByteDontDisable(0x05 + i,
       calib(getCellVoltage(i + 1)+(int8_t)getEepromByteDontDisable(0x05+i)*1.22,
         calibrated[i]));*/

  while (eepromBusy());
  Serial.println("Mapping...");
  setRegister(0x5f, 0x5A); // eeprom mapping

  while (eepromBusy());
  setRegister(0x5f, 0x00); // disable eeprom access

  while (eepromBusy());
  Serial.println("Done.");
}


void Bms_::reverseDumpEEProm() {
  uint8_t b;
  for (uint8_t readWordAddress = 0; readWordAddress <= 127; readWordAddress++) {
    // dump eeprom
    Serial.print(Bms.oz890Eeprom[readWordAddress], HEX);
    Serial.print(" ");
    // store it
    putEepromByteDontDisable(readWordAddress, oz890Eeprom[readWordAddress]);
  }
}

void Bms_::dumpEEProm() {
 /* uint8_t b;
  for (uint8_t readWordAddress = 0; readWordAddress <= 127; readWordAddress+=2) {
    // dump eeprom
    Serial.print(b = getEepromWord(readWordAddress), HEX);
    Serial.print(" ");
    // store it
    Bms.oz890Eeprom[readWordAddress] = b;
  }*/
}

void Bms_::readBms() {
  float vTmp = 0;
  String s;
  for (int i = 0; i < NUM_CELL_MAX; i++) {
    uint16_t cellVoltage = 0;
    int j=0;
    while(j++<10 &&(cellVoltage > 5000 || cellVoltage < 100)) cellVoltage = getCellVoltage(i + 1);
    // uint16_t cv=(getRegister(0x32 +i*2)>>3)+(getRegister(0x33 +i*2)<<5);
    cellVoltages[i] = cellVoltage > 7000 ? 0 : cellVoltage;
     s += " Cell " + String(i + 1) + ":" + String((cellVoltages[i]) / 1000.0, 3);
     //+" "+String(cellVoltage,16)+" "+String(cellVoltage);
    vTmp += cellVoltages[i] / 1000.0;
  }
  //Serial.println(s);
  espBatV = analogRead(ADC_IN)/587.3;
  vTot = vTmp;
  int16_t rawCurrent3 = getCurrentRaw();

  int16_t currentOffset = getCurrentOffset();
  uint8_t ch=getRegister(0x55);
  uint8_t cl=getRegister(0x54);
  uint16_t rawCurrent2=ch*256+cl;
  int16_t rawCurrent = getCurrentRaw();
  currentFltr.addSample(rawCurrent);
  float current2 = (rawCurrent* 7.63E-6)/(senseResistor/10000.0);
  float current3 = rawCurrent / 352.255;
  current = currentFltr.getMedian() / 227.083;
  if (current > 0.0) current *= 0.652079; // Positive currents have different coefficient
  Ah += current * (millis() - lasttime) / (1000.0 * 3600);
  first = 0;
  lasttime = millis();
  n++;

  Serial.println(String("RawCurrent:")+String(rawCurrent)+":"+String(rawCurrent,16)+"/"+String(rawCurrent2)+":"+String(rawCurrent2,16)+"/"+String(rawCurrent3)+":"+String(rawCurrent3,16)+
  " Current:"+String(current,2)+"/"+String(current2,2)+"/"+String(current3,2)+" offset:"+String(currentOffset));

  minVolt = 100.0;
  maxVolt = 0;
  for (int i = 0; i < Bms.cellNumber; i++) {
    if ((Bms.cellVoltages[i] / 1000.0) > maxVolt) {
      maxCell = i;
      maxVolt = Bms.cellVoltages[i] / 1000.0;
    }
    if ((Bms.cellVoltages[i] / 1000.0) < minVolt) {
      minCell = i;
      minVolt = Bms.cellVoltages[i] / 1000.0;
    }
  }
  if (current < 0.5 && current > -0.5) {
    for (int i = 0; i < Bms.cellNumber; i++) idleCellVoltages[i] = Bms.cellVoltages[i];

  }
  if (current <= -0.2) {
    for (int i = 0; i < Bms.cellNumber; i++) {
      if (Bms.cellVoltages[i] < minCellVoltages[i]) minCellVoltages[i] = Bms.cellVoltages[i];
    }
  }
  if (current >= 0.5) {
    for (int i = 0; i < Bms.cellNumber; i++) minCellVoltages[i] = Bms.cellVoltages[i]; // charging, minimum voltage not known
  }


  shutdownStatus = getRegister(0x15);
  errorStatus = getRegister(0x1c);
  fetEnable = getRegister(0x1e);
  fetDisable = getRegister(0x1f);
  int status=shutdownStatus<<16+errorStatus<<8+fetDisable;
  int remCap=0;
  int chargePersentage=0;
  int capacityEst=0;

  unsigned long t=millis();
  Ah+=(t-lastt)*current/(1000*3600); // ms in hour
  //if(current>0.2 && maxVolt>cellFullVolt) Ah=0; // Battery full and chrging, reset Ah

  //ll = LogLine(vTot, current, Ah, shutdownStatus<<16+errorStatus<<8+fetDisable,0.0, &cellVoltages[0], lasttime);
  ll = LogLine(vTot, current, Ah, remCap,chargePersentage,capacityEst, status, numCell, &cellVoltages[0], t,t/1000);
  if(!combinedll.isValid()) combinedll=ll;
  if(((lastLogTime+chargeLogInterval)<t && current>0.2 )|| ((lastLogTime+dischargeLogInterval)<t  && current<-0.2) || (lastLogTime+idleLogInterval)<t)
    {
    LogFile.addLogLine(&combinedll);
    combinedll=ll;
    lastLogTime=t;
  } else combinedll.combine(ll);

  lastt=t;
}


double Bms_::Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0 * ((8192.0 / RawADC - 1)));
  //         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}


Bms_ Bms = Bms_();
#endif
