//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// Offset  implementation.
// Offset controlled via register on TLM interface.
//
//////////////////////////////////////////////////////////////////////////////////

#include "../include/offset.h"

void offset::set_attributes(){
  //input.set_timestep(100 , SC_NS);
}

void offset::processing(){

  if(valid_in.read()){
  result = offset_in.read() + input.read();
  output.write(result);
  valid_out.write(true);
  }
}
