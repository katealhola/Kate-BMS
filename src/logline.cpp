#include "logline.h"


LogLine::LogLine() {
      sync=0xfeedc0de;
    };
    
LogLine::LogLine(float _v,float _a,float _ah,uint32_t _status,    uint16_t *_cellVoltages,long int _ms) {
    sync=0xfeedc0de;
    a=_a;
    v=_v;
    ah=_ah;
    status=_status;
     memcpy(cellVoltages,_cellVoltages,sizeof(cellVoltages));
    ms=_ms;
  };

  void LogLine::awgSum(LogLine ll)
  {
    status|=ll.status;
    a+=ll.a;
    v+=ll.v;
    ah=ll.ah;
    for (int i = 0; i < NUMOFCELL; i++) {
      cellVoltages[i]+=ll.cellVoltages[i];
    };
    ms=ll.ms;
  }

  void LogLine::awgDiv(int n)
  {
    a/=n;
    v+=n;
    for (int i = 0; i < NUMOFCELL; i++) {
      cellVoltages[i]/=n;
    };
  }
  
  String LogLine::toJson() {
      String s="{";
      if(sync!=(uint32_t)0xfeedc0de) s+="\"sync\":\""+String(sync,16)+"\",";
      s+="\"V\":"+String(v, 3)+",";
      s+="\"A\":"+String(a, 3)+",";
      s+="\"Ah\":"+String(ah, 3)+",\"cell\":[";
      for (int i = 0; i < NUMOFCELL; i++) {
          s += String((cellVoltages[i]) / 1000.0, 3);
          if(i<(NUMOFCELL-1)) s+=",";
      };
      s+="],";
      s+="\"es\":"+String(status)+",";
      s+="\"ms\":"+String(ms)+"}";
    return s;
  ;}
  
  String LogLine::toString() {
    String s=" V="+String(v,2)+" A="+String(a,3)+" Ah="+String(ah,3)+" time="+String(ms)+
    " sd="+String(status,16);
    for (int i = 0; i < 13; i++) {
      s += "V[ " + String(i + 1) + "]=" + String((cellVoltages[i]) / 1000.0, 3);
    };
    if(sync!=0xfeedc0de) s+="\"sync\":"+String(sync,16);
    return s;
  }

  #define VALIDCELL(n) (cellVoltages[n]<10000)
  
  bool LogLine::isValid() {
    return (sync==0xfeedc0de && fabs(a)<100.0 && v>0 && v<100 && VALIDCELL(0) &&  VALIDCELL(1) &&  VALIDCELL(2) &&  VALIDCELL(3) &&  VALIDCELL(4) && VALIDCELL(5) && 
    VALIDCELL(6) && VALIDCELL(7) && VALIDCELL(8) && VALIDCELL(9) && VALIDCELL(10) && VALIDCELL(11) && VALIDCELL(12) );
  };
 
