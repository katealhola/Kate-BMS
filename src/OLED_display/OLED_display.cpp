#include "config.h"
#ifdef OLED

#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "OLEDDisplayUi.h"
#include "CustomOledFonts.h"

extern SSD1306  display;


#include "bms.h";
#include <WiFi.h>
extern const char* ssid;

void displayInit()
{
  pinMode(OLED_RSTN,OUTPUT); 
   digitalWrite(OLED_RSTN, LOW); // set GPIO16 low to reset OLED 
   delay(50); 
   digitalWrite(OLED_RSTN, HIGH); // while OLED is running, must set GPIO16 to high 
   delay(500); 
   display.init();
   display.clear();   // clear the display
   display.setFont(ArialMT_Plain_16);
   display.drawString(0, 0, "KateBMS");
   display.display();
   delay(500);
}

void startUpDisplay()
{
  display.clear();   // clear the display
   display.setFont(ArialMT_Plain_16);
   display.drawString(0, 0, "KateBMS");
   display.display();
   delay(500);
}

void connectingDisplay()
{
   display.clear();   // clear the display
   display.setFont(ArialMT_Plain_16);
   display.drawString(0, 0, "connecting to");
   display.drawString(0, 20, ssid);
   display.display(); 
}

void displayString(int x,int y,String s)
{
          display.drawString(x, y, s);
}

void networkDisplay()
{   
   display.setFont(ArialMT_Plain_16); 
   displayString(0, 0, String("ssid ")+ ssid);
   String ips=WiFi.localIP().toString();
   displayString(0, 16,ips );
   Serial.println(ssid+String(" ")+ips);
   displayString(0,32,String(SPIFFS.totalBytes()/1024)+"/"+String(SPIFFS.usedBytes()/1024));
   
}

void cellVoltagesDisplay()
{
  String s;
  int x=0;
  display.setFont(Dialog_plain_12);
  for (int i = 0; i < Bms.cellNumber; i++) {
    if(s.length()==0) s+=String(i+1)+":";
    s+=String(0.001*Bms.cellVoltages[i],2);
    if((i%3==0 && i!=0) || i+1==Bms.cellNumber) {
      displayString(0,x,s);
      s="";
      x+=16;
    } else s+=" ";
    }
}

int valueToPixels(float val, float minval, float maxval,int maxPixels)
{

  float eval=val<maxval?val:maxval;
  eval=eval>minval?eval:minval;
  
  return round(maxPixels/(maxval-minval)*(val-minval));
}

void barplot(SSD1306  &m )
{
  float plotmin=2.4;
  
  
 // m.fillRect(0, 0, m.width() - 1, m.height() - 1);
  m.setFont(ArialMT_Plain_10);
  for (int i = 0; i < 12; i++) {
    float v=4.4 - i * 0.2;
    int pix=valueToPixels(v,4.4,plotmin,m.height());
    if(i>0 && !(i&1)) m.drawString(0, pix-2,String(v, 1));
    if(i>0)m.drawLine(20, m.height()-pix , m.width(), m.height()-pix);
  }
  for(int i=0;i<Bms.cellNumber;i++) {
    float v=Bms.cellVoltages[i] / 1000.0;
    float idleV=Bms.idleCellVoltages[i] / 1000.0;
    float minV=Bms.minCellVoltages[i] / 1000.0;
    int pix=valueToPixels(v,4.4,plotmin,m.height());
    int minPix=valueToPixels(minV,4.4,plotmin,m.height());
    int idlePix=valueToPixels(idleV,4.4,plotmin,m.height());
    m.fillRect(i*8+20,pix,3,m.height()-pix);
    m.fillRect(i*8+19,minPix,6,4);
    String s=String(i)+" "+String(valueToPixels(v,4.4,3.0,m.height()))+"v="+String(v,2);
   // Serial.println(s);
  }
}


void statusDisplay()
  {
    String s,s2;
  
  //  s="V="+String(Bms.vTot,2);
    
    display.setFont(ArialMT_Plain_16);       
    
  
  s = String(Bms.vTot, 2) + "V ";
  s += String(Bms.current, 2) + "A ";
  displayString(0,0,s);
  s2 = s;
  
  s = String(Bms.Ah, 1) + "Ah ";
  s += String(Bms.current * Bms.vTot, 0) + "W ";
  displayString(0,17,s);
  s2 += s;
  display.setFont(ArialMT_Plain_10);
  s = String(Bms.minCell + 1) + "=" + String(Bms.minVolt, 2);
  s += " " + String(Bms.maxCell + 1) + "=" + String(Bms.maxVolt, 2);
  s += " b=" + String(Bms.espBatV,2);
  s2 += s;
  
  displayString(0,36,s);
  if(Bms.shutdownStatus!=0 || Bms.errorStatus!=0 || Bms.fetEnable!=0 || Bms.fetDisable!=0) {
    s = "s=" + String(Bms.shutdownStatus, 16) + " e=" + String(Bms.errorStatus, 16) + " n=" + String(Bms.fetEnable, 16) + " d=" + String(Bms.fetDisable, 16);
    displayString(0,50,s);
  }
  }

#endif
