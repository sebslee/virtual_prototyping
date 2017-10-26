//Created by Sebastian Lee

#include "../include/wave_saw_tooth.h"

void saw_tooth::set_attributes(){
  out.set_rate(rate);
}

void saw_tooth::processing(){
  double res;
  double cot;
  cot =1/tan(actval);
  res = -1 * ((2 * amp)/PI)*atan(cot);
  out.write(res);
  //res = offset+(2*amp/M_PI*asin(sin(actval)));
  actval+=stepsize;
  //if(res < floor)
  //  res = floor;
  
  // out.write(res);
}

void saw_tooth::initialize(){
  stepsize = out.get_timestep().to_seconds()*2.0*PI*freq;
}

