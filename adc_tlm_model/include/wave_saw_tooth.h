//Created by Sebastian Lee


#ifndef WAVE_SAW
#define WAVE_SAW

#include "systemc-ams.h"
#include "math.h"

#define PI 3.14159265

class saw_tooth : public sca_tdf::sca_module{
 public:
  sca_tdf::sca_out<double> out;
  
  saw_tooth(sc_core::sc_module_name name , double _amp , double _freq , double _floor , double _offset , int _rate =1){
    offset  = _offset;
    amp = _amp;
    freq = _freq;
    rate = _rate;
    floor = _floor;
  }

 private:
  double offset;
  double amp;
  double actval;
  double freq;
  int rate;
  double floor;
  double stepsize;
  void set_attributes();
  void processing();
  void initialize();
};

#endif
