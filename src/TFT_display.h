#ifndef _TFT_DISPLAY_H_
#define _TFT_DISPLAY_H_
#include "TFT_eSPI.h"
#include "TFTShape.h"

class analogGauge {
    public:
    analogGauge();
    void drawGauge(TFT_eSprite &tft,String label1,String label2,float val1);
    void drawarc(TFT_eSprite &tft,int x,int y, int r,int arcStart,int arcEnd,int w,uint16_t color);
    void plotNeedle(TFT_eSprite &tft,int value, byte ms_delay);

    int old_analog;// Value last displayed
    int arcStart;
    int arcEnd;
    int tickSpasing;
    float m_size;
    int xpos;
    int ypos;

};

#endif // _TFT_DISPLAY_H_
