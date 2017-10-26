//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// Programmable Gain Amplifier implementation.
// Gain controlled via register on TLM interface.
//
//////////////////////////////////////////////////////////////////////////////////
#include "../include/gain_stage.h"
#include "../include/defines.h"
void pga::set_attributes(){
  //input.set_timestep(100, SC_NS);
}

void pga::processing(){
  if(valid_in.read()){
  result = gain.read() * input.read();  
  output.write(result);
  valid_out.write(true);
  }
  else
    valid_out.write(false);
}
