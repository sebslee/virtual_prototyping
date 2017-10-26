//Created by Sebastian Lee

#include "../include/cyclic_adc_pipe_stage.h"


void adc_cyclic_pipe_stage::set_attributes(){
  vx_in.set_timestep(100 , SC_NS);
  vx_in.set_rate(1);
  vo_out.set_rate(1);
}

void adc_cyclic_pipe_stage::processing(){
  //cout << "doing something" << endl;
  vx = vx_in.read();
  if(vx <= advref/2){
    bit_o = 0;
    vo = 2 * vx;
  }
  else{
    bit_o = 1 ;
    vo = 2 * (vx - advref/2);
  }
  vo_out.write(vo);
  bit_out.write(bit_o);
}
