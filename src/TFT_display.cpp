#include "config.h"

#ifdef TFT
#include "Free_Fonts.h" // Include the header file attached to this sketch

//#include "SPI.h"
#include "TFT_eSPI.h"
#include <TFTShape.h>
extern TFT_eSPI  display ;
#define CUSTOM_DARK 0x4228 // Background color
#define TFT_GREY 0x5AEB
#define TFT_ORANGE      0xFD20      /* 255, 165,   0 */

#define M_SIZE 0.7

#include "bms.h";
#include <WiFi.h>
extern const char* ssid;

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed

void plotNeedle(TFT_eSprite &tft,int value, byte ms_delay);
void analogMeter(TFT_eSprite &tft,String label1,String label2,float val1);
void drawarc(TFT_eSprite &tft,int x,int y, int r,int arcStart,int arcEnd,int w,uint16_t color);


void displayInit()
{
   display.init();
  display.setRotation(0);
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
 display.fillScreen(CUSTOM_DARK);
  display.setTextColor(TFT_WHITE);
  display.setCursor(20, 0);
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

void networkDisplay()
{
  if (!WiFi.isConnected()) {
    display.println("trying to reconnect Wifi");
    display.println(String("ssid ") + ssid);
  } else
  {
    display.println("connected");
    display.println(String("ssid ") + ssid);
    String ips = WiFi.localIP().toString();
    display.println(ips);
  }
}

int valueToPixels(float val, float minval, float maxval,int maxPixels)
{

  float eval=val<maxval?val:maxval;
  eval=eval>minval?eval:minval;
  
  return round(maxPixels/(maxval-minval)*(val-minval));
}


void statusDisplay(TFT_eSprite &m )
{
  String s, s2;

  s = String(Bms.vTot, 2) + "V ";
  s += String(Bms.current, 2) + "A ";
  s2 = s;
  m.println(s);
  s = String(Bms.Ah, 1) + "Ah ";
  s += String(Bms.current * Bms.vTot, 3) + "W ";
  s2 += s;
  m.setFreeFont(FM9);
  m.println(s);
  s = String(Bms.minCell + 1) + "=" + String(Bms.minVolt, 2);
  s += " " + String(Bms.maxCell + 1) + "=" + String(Bms.maxVolt, 2);
  s += " b=" + String(Bms.espBatV,2);
  s2 += s;
  m.println(s);
  if(Bms.shutdownStatus!=0 || Bms.errorStatus!=0 || Bms.fetEnable!=0 || Bms.fetDisable!=0) {
    s = "s=" + String(Bms.shutdownStatus, 16) + " e=" + String(Bms.errorStatus, 16) + " n=" + String(Bms.fetEnable, 16) + " d=" + String(Bms.fetDisable, 16);
    m.println(s);
  }

}


void barplot(TFT_eSprite &m )
{
  float plotmin=2.4;
  
  
  m.fillRect(0, 0, m.width() - 1, m.height() - 1, TFT_PURPLE);
  m.setFreeFont(FM9);
  for (int i = 0; i < 12; i++) {
    float v=4.4 - i * 0.2;
    int pix=valueToPixels(v,4.4,plotmin,m.height());
    if(i>0 && !(i&1)) m.drawString(String(v, 1), 0, pix-5);
    if(i>0)m.drawLine(40, m.height()-pix , m.width(), m.height()-pix,TFT_WHITE);
  }
  for(int i=0;i<Bms.cellNumber;i++) {
    float v=Bms.cellVoltages[i] / 1000.0;
    float idleV=Bms.idleCellVoltages[i] / 1000.0;
    float minV=Bms.minCellVoltages[i] / 1000.0;
    int pix=valueToPixels(v,4.4,plotmin,m.height());
    int minPix=valueToPixels(minV,4.4,plotmin,m.height());
    int idlePix=valueToPixels(idleV,4.4,plotmin,m.height());
    m.fillRect(i*13+60,pix,9,m.height()-pix,TFT_GREEN);
    m.fillRect(i*13+58,minPix,14,4,TFT_WHITE);
    String s=String(i)+" "+String(valueToPixels(v,4.4,3.0,m.height()))+"v="+String(v,2);
   // Serial.println(s);
  }
}



void spiDispkayTask( void * parameter ) {
  int refresh = 0;
  unsigned int dispTimeout = 0;
  int bt = 0;
  int b;
  int dispmode = 0;
  unsigned int n = 0;
  int espBatV;
  display.fillScreen(CUSTOM_DARK);
  display.setTextColor(TFT_WHITE, TFT_BLACK);
  display.setCursor(0, 0);
  display.println();
  display.setFreeFont(FM12);
  while (1) {
    
    // display.fillScreen(CUSTOM_DARK);
    TFT_eSprite m = TFT_eSprite(&display);
    m.setColorDepth(8);
    m.createSprite(display.width(), 80);
    m.fillSprite(TFT_BLACK);

    //m.setTextFont(2);
    m.setFreeFont(FM12);
    m.setTextDatum(TL_DATUM);
    m.setTextColor(TFT_WHITE);
    m.setCursor(0, 0);
    m.println();
    b = digitalRead(BUTTON);
    //display.println("b="+String(b));
    if (b == 0 && bt == 1) {
      refresh = 1;
      dispTimeout = n;
    }
    bt = b;
    if (bt) statusDisplay(m);
    else networkDisplay();
    m.pushSprite(0, 0);
    m.deleteSprite();

     m.createSprite(display.width(), 128);
    m.fillSprite(TFT_BLACK);
    barplot(m);
    m.pushSprite(0, 200);
    m.fillSprite(TFT_BLUE);
    String s1 = String(Bms.vTot, 2) + "V ";
    String s2 = String(Bms.current, 2) + "A ";
    analogMeter(m,s1,s2,Bms.vTot);
    m.pushSprite(0,70);
    m.deleteSprite();
    delay(100);
  }

}

void analogMeter(TFT_eSprite &tft,String label1,String label2,float val1)
{

  // Meter outline
  //tft.fillRect(0, 0, M_SIZE*239, M_SIZE*131, TFT_BLACK);
  //tft.fillRect(1, M_SIZE*3, M_SIZE*234, M_SIZE*125, TFT_WHITE);

  tft.setTextColor(TFT_WHITE);  // Text colour

  
  
  #define SCALE_COLOR TFT_WHITE
  int arcStart=-1200;
  int arcEnd=120;
  int tickSpasing=10;
  
  for (int i = arcStart; i <= arcEnd; i += tickSpasing) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    uint16_t y0 = sy * (M_SIZE*100 + tl) + M_SIZE*150;
    uint16_t x1 = sx * M_SIZE*100 + M_SIZE*120;
    uint16_t y1 = sy * M_SIZE*100 + M_SIZE*150;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + tickSpasing - 90) * 0.0174532925);
    float sy2 = sin((i + tickSpasing - 90) * 0.0174532925);
    int x2 = sx2 * (M_SIZE*100 + tl) + M_SIZE*120;
    int y2 = sy2 * (M_SIZE*100 + tl) + M_SIZE*150;
    int x3 = sx2 * M_SIZE*100 + M_SIZE*120;
    int y3 = sy2 * M_SIZE*100 + M_SIZE*150;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}


  
    // Green zone limits
    /*if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
    }*/

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    y0 = sy * (M_SIZE*100 + tl) + M_SIZE*150;
    x1 = sx * M_SIZE*100 + M_SIZE*120;
    y1 = sy * M_SIZE*100 + M_SIZE*150;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, SCALE_COLOR);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sy * (M_SIZE*100 + tl + 10) + M_SIZE*150;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0+4, y0-4, 1); break;
        case -1: tft.drawCentreString("25", x0+2, y0, 1); break;
        case 0: tft.drawCentreString("50", x0, y0, 1); break;
        case 1: tft.drawCentreString("75", x0, y0, 1); break;
        case 2: tft.drawCentreString("100", x0-2, y0-4, 1); break;
      }
    }

    // Now draw the arc of the scale
    //sx = cos((i + tickSpasing - 90) * 0.0174532925);
    //sy = sin((i + tickSpasing - 90) * 0.0174532925);
    x0 = sx2 * M_SIZE*100 + M_SIZE*120;
    y0 = sy2 * M_SIZE*100 + M_SIZE*150;
    // Draw scale arc, don't draw the last part
    if (i < arcEnd) tft.drawLine(x0, y0, x1, y1, SCALE_COLOR);
  }
  TFTShape w=TFTShapeBuilder::buildAnnularWedge(32,80,M_SIZE*100,-100,300);
  w.fillDrawH(&tft,50,160,TFT_GREEN,TFT_GREEN,2);
  //drawarc(tft,M_SIZE*120,M_SIZE*150,M_SIZE*100, -100, 70, 8,TFT_GREEN);
 // tft.drawString("%RH", M_SIZE*(3 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right
  tft.drawCentreString(label1, M_SIZE*120, M_SIZE*120-5, 4); // Comment out to avoid font 4
  tft.drawCentreString(label2, M_SIZE*120, M_SIZE*120+20, 4); // Comment out to avoid font 4
  //tft.drawRect(1, M_SIZE*3, M_SIZE*236, M_SIZE*126, TFT_BLACK); // Draw bezel line

 // plotNeedle(tft,0, 0); // Put meter needle at 0
}

void drawarc(TFT_eSprite &tft,int x,int y, int r,int arcStart,int arcEnd,int w,uint16_t color)
{
  int a=arcStart;
  int a1=arcStart;
  int arcStep=5;
  int16_t x0 = 0;
  int16_t y0 = 0;
  int16_t x1 = 0;
  int16_t y1 = 0;
  int i=0;
  do {
    a=a1;
    int16_t x2 = x0;
    int16_t y2 = y0;
    int16_t x3 = x1;
    int16_t y3 = y1;
    float sx = cos((a - 90) * 0.0174532925);
    float sy = sin((a - 90) * 0.0174532925);
    x0 = x+(sx * r);
    y0 = y+(sy * r);
    x1 = x+(sx * (r+w));
    y1 = y+(sy * (r+w));
   // Serial.println("drawarc "+String(i)+" a="+String(a)+" x0="+String(x0)+":"+String (y0)+" x3="+String(x3)+":"+String (y3));
    if(x3!=0&&y3!=0) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
    }
    a1=a+arcStep>arcEnd?arcEnd:a+arcStep; 
    i++;
  } while(a<arcEnd);
  
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(TFT_eSprite &tft,int value, byte ms_delay)
{
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawRightString(buf, 33, M_SIZE*(119 - 20), 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle until new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calculate tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(M_SIZE*(120 + 24 * ltx) - 1, M_SIZE*(150 - 24), osx - 1, osy, TFT_WHITE);
    tft.drawLine(M_SIZE*(120 + 24 * ltx), M_SIZE*(150 - 24), osx, osy, TFT_WHITE);
    tft.drawLine(M_SIZE*(120 + 24 * ltx) + 1, M_SIZE*(150 - 24), osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString("%RH", M_SIZE*120, M_SIZE*75, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE*(sx * 98 + 120);
    osy = M_SIZE*(sy * 98 + 150);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(M_SIZE*(120 + 24 * ltx) - 1, M_SIZE*(150 - 24), osx - 1, osy, TFT_RED);
    tft.drawLine(M_SIZE*(120 + 24 * ltx), M_SIZE*(150 - 24), osx, osy, TFT_MAGENTA);
    tft.drawLine(M_SIZE*(120 + 24 * ltx) + 1, M_SIZE*(150 - 24), osx + 1, osy, TFT_RED);
    
    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}






#endif
