#include "logline.h"

LogLine::LogLine()
{
  sync=0xfeedc0de;
  //sync = 0; // Not valid
};

LogLine::LogLine(const LogLine &ll)
{
  sync = ll.sync;
  a = ll.a;
  v = ll.v;
  ah = ll.ah;
  remainingCapacity = ll.remainingCapacity;
  chargePersentage=ll.chargePersentage;
  capacityEstimate=ll.capacityEstimate;
  numCell = ll.numCell;
  status = ll.status;
  ms = ll.ms;
  t = ll.t;
  ;
  memcpy(cellVoltages, ll.cellVoltages, sizeof(cellVoltages));
};

LogLine::LogLine(float _v,float _a,float _ah,float _remainingCapacity,float _chargePersentage,float _capacityEst,uint32_t _status,uint16_t _numcell, uint16_t *_cellVoltages,long int _ms,uint32_t _t)   
{
  sync = 0xfeedc0de;
  a = _a;
  v = _v;
  ah = _ah;
  remainingCapacity = _remainingCapacity;
  capacityEstimate=_capacityEst;
  chargePersentage=_chargePersentage;
  

  numCell = _numcell;
  status = _status;
  memcpy(cellVoltages, _cellVoltages, sizeof(cellVoltages));
  ms = _ms;
  t = _t;
};

void LogLine::awgSum(LogLine ll)
{
  status |= ll.status;
  a += ll.a;
  v += ll.v;
  ah = ll.ah;
  for (int i = 0; i < NUMOFCELL; i++)
  {
    cellVoltages[i] += ll.cellVoltages[i];
  };
  ms = ll.ms;
  t = ll.t;
}

void LogLine::combine(LogLine ll)
{
  status |= ll.status;
  ah = ll.ah;
  ms = ll.ms;
  t = ll.t;
  chargePersentage=ll.chargePersentage;
  remainingCapacity=ll.remainingCapacity;
  capacityEstimate=ll.capacityEstimate;
  if (ll.a > 0.2)
  {
    a = ll.a > a ? ll.a : a;
    v = ll.v < v ? ll.v : v;
    for (int i = 0; i < NUMOFCELL; i++)
    {
      cellVoltages[i] = cellVoltages[i] < ll.cellVoltages[i] ? ll.cellVoltages[i] : cellVoltages[i];
    };
  }
  if (ll.a < -0.2)
  {
    a = ll.a < a ? ll.a : a;
    v = ll.v > v ? ll.v : v;
    for (int i = 0; i < NUMOFCELL; i++)
    {
      cellVoltages[i] = cellVoltages[i] > ll.cellVoltages[i] ? ll.cellVoltages[i] : cellVoltages[i];
    };
  }
}

void LogLine::awgDiv(int n)
{
  a /= n;
  v += n;
  for (int i = 0; i < NUMOFCELL; i++)
  {
    cellVoltages[i] /= n;
  };
}

String LogLine::toJson()
{
  String s = "{";
  if (sync != (uint32_t)0xfeedc0de)
    s += "\"sync\":\"" + String(sync, 16) + "\",";
  s += "\"V\":" + String(v, 3) + ",";
  s += "\"A\":" + String(a, 3) + ",";
  s += "\"Ah\":" + String(ah, 3) + ",";
  s += "\"remCap\":" + String(remainingCapacity) + ",";
  s += "\"chrgP\":" + String(chargePersentage, 0) + ",";
  s += "\"capEst\":" + String(capacityEstimate) + ",";
  s += "\"ncell\":" + String(numCell) + ",";
  s + "\"cell\":[";
  int n=numCell<NUMOFCELL && numCell>0?numCell:NUMOFCELL;
  for (int i = 0; i < n; i++)
  {
    s += String((cellVoltages[i]) / 1000.0, 3);
    if (i < (numCell - 1))
      s += ",";
  };
  s += "],";
  s += "\"es\":" + String(status) + ",";
  s += "\"t\":" + String(t) + ",";
  s += "\"ms\":" + String(ms) + "}";
  return s;
  ;
}

String LogLine::toString()
{
  String s = " V=" + String(v, 2) + " A=" + String(a, 3) + " Ah=" + String(ah, 3) + " time=" + String(ms) +
             " sd=" + String(status, 16);
  int n=numCell<NUMOFCELL && numCell>0?numCell:NUMOFCELL;
  for (int i = 0; i < n; i++)
  {
    s += "V[ " + String(i + 1) + "]=" + String((cellVoltages[i]) / 1000.0, 3);
  };
  if (sync != 0xfeedc0de)
    s += "\"sync\":" + String(sync, 16);
  return s;
}

#define VALIDCELL(n) (cellVoltages[n] < 10000)

bool LogLine::isValid()
{
  return (sync == 0xfeedc0de && fabs(a) < 100.0 && v > 0 && v < 100 && numCell>0 && numCell<NUMOFCELL &&
          VALIDCELL(0) && VALIDCELL(1) && VALIDCELL(2) && VALIDCELL(3) && VALIDCELL(4) && VALIDCELL(5) &&
          VALIDCELL(6) && VALIDCELL(7) && VALIDCELL(8) && VALIDCELL(9) && VALIDCELL(10) && VALIDCELL(11) && VALIDCELL(12));
};
