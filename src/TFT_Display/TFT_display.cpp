#include "config.h"
#include "bms.h"
#include <WiFi.h>

#define TFT
#ifdef TFT
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include <Fonts/GFXFF/gfxfont.h>
#include "Mono16.h"
#include "Dialog28.h"
#include "Dialog24.h"
#include "Dialog22.h"
#include "Dialog20.h"
#include "Dialog16.h"
#include "Dialog12.h"
#include "Dseg20.h"
#include "Dseg22.h"
#include "Dialog32.h"

#include "TFT_display.h"


#include "TFT_eSPI.h"
#include "TFTShape.h"
extern TFT_eSPI  display ;
#define CUSTOM_DARK 0x4228 // Background color
#define TFT_GREY 0x5AEB
#define TFT_ORANGE      0xFD20      /* 255, 165,   0 */

#define M_SIZE 0.6


extern const char* ssid;

//float ltx = 0;    // Saved x coord of bottom of needle
//uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update


void displayInit()
{
   display.init();
#if defined(SMALLDISPLAY) | defined(BMS2)
  display.setRotation(1);
#else
 display.setRotation(0);
#endif
  display.fillScreen(TFT_BLACK);
  display.setTextColor(TFT_WHITE);
  display.setTextWrap(true);
  display.setCursor(0, 0);
  display.setFreeFont(FSB18); 
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  display.setTextColor(TFT_GREEN, TFT_BLACK);
  display.fillScreen(TFT_BLACK);
  display.setTextDatum(MC_DATUM);
}

void startUpDisplay()
{
   display.fillScreen(CUSTOM_DARK);
  display.setTextColor(TFT_WHITE);
  display.setCursor(0, 0);
  display.println();
  display.setFreeFont(FSB18); 
  display.print("KateBMS");
}

void connectingDisplay()
{
 /*display.fillScreen(CUSTOM_DARK);
  display.setTextColor(TFT_WHITE);
  display.setCursor(20, 0);*/
  display.println();  
  display.setFreeFont(FSB12); 
  display.print("connecting to ");
  display.print(ssid); 
}


void displayString(int x, int y, String s)
{
  display.setCursor(x + 20, y);
  display.println(s);
}

void networkDisplay(TFT_eSprite &m )
{
  if (!WiFi.isConnected()) {
    m.println("trying to reconnect Wifi");
    m.println(String("ssid ") + ssid);
  } else
  {
    m.println("connected");
    m.println(String("ssid ") + ssid);
    String ips = WiFi.localIP().toString();
    m.println(ips);
  }
}

int valueToPixels(float val, float minval, float maxval,int maxPixels)
{

  float eval=val<maxval?val:maxval;
  eval=eval>minval?eval:minval;
  
  return round(maxPixels/(maxval-minval)*(val-minval));
}


int statusDisplay(TFT_eSprite &m,Bms_ Bms,const GFXfont *font)
{
  int xpos =  0;
  int ypos =  0;

  String s, s2;
  //m.setFreeFont(FM18);
  //m.setFreeFont(&Monospaced_plain_16);
  #ifdef BMS2
  //m.setFreeFont(&Dialog_plain_22);
  m.setFreeFont(&DialogInput_plain_22);
  //m.setFreeFont(&DSEG14_Modern_Regular_22);
  //display.setTextColor(TFT_GREEN, TFT_BLACK);
  #else
  m.setFreeFont(&Dialog_plain_32);
  #endif
  s = String(Bms.vTot, 1) + "V ";
  s += String(Bms.current, 2) + "A ";
  s2 = s;
  m.drawString(s, xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
  ypos += m.fontHeight(GFXFF);                      // Get the font height and move ypos down

  //m.println(s);
  //m.setFreeFont(FM12);
  #if 0
  m.setFreeFont(&Dialog_plain_28);
  s = String(Bms.Ah, 2) + "Ah ";
  s += String(Bms.current * Bms.vTot, 0) + "W ";
  s2 += s;
  m.drawString(s, xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
  ypos += m.fontHeight(GFXFF);                      // Get the font height and move ypos down
  #endif
  //m.println(s);

  s = String(Bms.SoC,0) + "% ";
  s += String(Bms.remaining_Ah,3) + "Ah ";
  s2 += s;
  m.drawString(s, xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
  ypos += m.fontHeight(GFXFF);                      // Get the font height and move ypos down
  //m.println(s);

  m.setFreeFont(FM9);
  
  s = String(Bms.minCell + 1) + "=" + String(Bms.minVolt, 2);
  s += " " + String(Bms.maxCell + 1) + "=" + String(Bms.maxVolt, 2);
  s += " b=" + String(Bms.espBatV,2);
  s2 += s;
  m.drawString(s, xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
  ypos += m.fontHeight(GFXFF);                      // Get the font height and move ypos down
  
  return ypos;
}


int barplot(TFT_eSprite &m,Bms_ BMS )
{
  float plotmin=2.4;
  float cellMin=5.0;
  float cellMax=0.0;
  unsigned int cellMaxI=0;
  unsigned int cellMinI=0;
  int fh;
  int pix;
  
  
  m.fillRect(0, 0, m.width() - 1, m.height() - 1, TFT_BLACK);
  m.setFreeFont(FM9);
  for (int i = 0; i < 12; i++) {
    float v=4.4 - i * 0.2;
    pix=valueToPixels(v,Bms.cellFullVolt,plotmin,m.height());
    if(i>0 && !(i&1)) m.drawString(String(v, 1), 0, pix-5);
    if(i>0)m.drawLine(40, m.height()-pix , m.width(), m.height()-pix,TFT_WHITE);
  }
  int w=(m.width()-60)/(Bms.numCell ? Bms.numCell:13);

  for(int i=0;i<Bms.numCell;i++) {
    float v=Bms.cellVoltages[i] / 1000.0;
    if(v>cellMax) {
      cellMax=v;
      cellMaxI=i;
    }
    if(v<cellMin) {
      cellMin=v;
      cellMinI=i;
    }
  }

  for(int i=0;i<Bms.numCell;i++) {
    float v=Bms.cellVoltages[i] / 1000.0;
    float idleV=Bms.idleCellVoltages[i] / 1000.0;
    float minV=Bms.minCellVoltages[i] / 1000.0;
    pix=valueToPixels(v,Bms.cellFullVolt,plotmin,m.height());
    int minPix=valueToPixels(minV,Bms.cellFullVolt,plotmin,m.height());
    int idlePix=valueToPixels(idleV,Bms.cellFullVolt,plotmin,m.height());
    int color=TFT_GREEN;
    if(i==cellMaxI) color=TFT_GREENYELLOW;
    if(i==cellMinI) color=0x5E0;
    m.fillRect(i*w+60,pix,w-4,m.height()-pix,color);
    m.fillRect(i*w+58,minPix,w+1,4,TFT_WHITE);
    //String s=String(i)+" "+String(valueToPixels(v,4.4,3.0,m.height()))+","+String(i*w+60)+" v="+String(v,2);
    //Serial.println(s);
  }

  int labelw=55;
  m.setFreeFont(FMB9);
  fh=m.fontHeight(GFXFF);  
  pix=valueToPixels(cellMax,Bms.cellFullVolt,plotmin,m.height());
  m.fillRect(0,pix-(fh),labelw,(fh),TFT_BLACK);
  m.drawRect(0,pix-(fh),labelw,(fh),TFT_WHITE);
  m.drawLine(10, pix-1 , 45, pix,TFT_WHITE);
  m.drawString(String(cellMax, 3), 0, pix-fh);

  pix=valueToPixels(cellMin,Bms.cellFullVolt,plotmin,m.height());
  m.fillRect(0,pix,labelw,fh,TFT_BLACK);
  m.drawLine(10, pix , labelw, pix,TFT_WHITE);
  m.drawRect(0,pix,labelw,fh,TFT_WHITE);
  m.drawString(String(cellMin, 3), 0, pix);
  return m.height() - 1;
}



void spiDisplayTask( void * parameter ) {
  int refresh = 0;
  unsigned int dispTimeout = 0;
  int bt = 0;
  int b;
  int dispmode = 0;
  unsigned int n = 0;
  int espBatV;
  displayInit();
  int status_h=100;
  int bar_h=120;
  const GFXfont *status_font;
  #ifdef BMS2
  #ifdef SMALLDISPLAY
  status_font=&DialogInput_plain_12;
  status_h=80;
  #else
  status_font=&DialogInput_plain_22;
  #endif
  #else
  status_font=&Dialog_plain_28;
  #endif

  //display.fillScreen(CUSTOM_DARK);
  display.fillScreen(TFT_BLUE);
  display.setTextColor(TFT_WHITE, TFT_BLACK);
  display.setCursor(0, 0);
  display.println("spiDisplayTask");
  Serial.println("spiDisplayTask:Initialized\n");
  analogGauge *gauge=new analogGauge();
 // display.setFreeFont(FM12);
  while (1) {
#ifdef SMALLDISPLAYX
TFT_eSprite m = TFT_eSprite(&display);
    m.setColorDepth(8);
    m.createSprite(display.width(), 128);
    m.fillSprite(TFT_BLACK);

    //m.setTextFont(2);
    m.setFreeFont(FM12);
    m.setTextDatum(TL_DATUM);
    m.setTextColor(TFT_WHITE);
    m.setCursor(0, 0);
    m.println();
    b = digitalRead(BUTTON);
    //Serial.println("b="+String(b)+" ref="+String(refresh)+" to="+String(dispTimeout));
    if((b==0) && (bt==1)) dispmode=dispmode >=2?0:dispmode+1;
       bt=b;
       if(fabs(Bms.current)>0.5) dispTimeout=n;
       if(n<(dispTimeout+600)) {
          if(bt) statusDisplay(m,Bms);
            else {
              if(dispmode==0) networkDisplay(m);
              if(dispmode==1) barplot(m,Bms);
             // if(dispmode==2) cellVoltagesDisplay(m);
            }
       }
    m.pushSprite(0, 0);
    m.deleteSprite();
#else    
    // display.fillScreen(CUSTOM_DARK);
    TFT_eSprite m = TFT_eSprite(&display);
    m.setColorDepth(8);
    #ifdef BMS2
    m.createSprite((display.width()/2)-2, status_h);
    #else
    m.createSprite(display.width(), status_h);
    #endif 
    m.fillSprite(TFT_BLACK);
    
    b = digitalRead(BUTTON);
    b=1;
    //display.println("b="+String(b));
    if (b == 0 && bt == 1) {
      refresh = 1;
      dispTimeout = n;
    }
    bt = b;
    if (bt) {
      statusDisplay(m,Bms,status_font);
    }
    else networkDisplay(m);
    m.pushSprite(0, 0);
    m.deleteSprite();
 
    #ifdef BMS2
    m.createSprite((display.width()/2)-2, status_h);
    //m.fillSprite(TFT_BLACK);
    statusDisplay(m,Bms2,status_font);
    m.pushSprite(display.width()/2, 0);
    m.deleteSprite();
    m.createSprite((display.width()/2)-2, bar_h);
    //m.fillSprite(TFT_BLACK);
    barplot(m,Bms);
    m.pushSprite(display.width()/2, status_h);
    m.deleteSprite();
    m.createSprite((display.width()/2)-2, bar_h);
    #else
    m.createSprite(display.width(), bar_h);
    #endif 
    //m.fillSprite(TFT_BLACK);
    barplot(m,Bms);
    m.pushSprite(0, status_h);
  #if 0
    gauge->drawGauge(m,s1,s2,Bms.current);
    m.pushSprite(0,70);
  #endif
    m.deleteSprite();
    #endif
    delay(200);
  }

}

#endif