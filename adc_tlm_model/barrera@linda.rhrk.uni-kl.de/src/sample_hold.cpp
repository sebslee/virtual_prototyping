//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// This file simulates the sample/hold stage on the ADC cell.
// Input: Coming from input mux that takes settling time into account.
// Two parameters are set:
// Tracking time: Input coming from the user interface, time ADC must see the
// input voltage to provide specified accuracy. Here is modelled as a time the  sample
// is held before writing to the next stage.
// Transfer time: Time that it takes to transfer to input of cyclic pipeline. 
// Output : Analog sample passed to cycle pipe ADC model at the sample time.
//
//////////////////////////////////////////////////////////////////////////////////


#include "../include/sample_hold.h"

void sample_hold::processing(){
  //If sample_hold_time == 0 we sample mux input , then we must hold that input for tracking + transfer time and then write it to the cyclic pipeline input and reset counter, read next sample and so on. 
  //double s_h_value;
  switch(state){
  case SAMPLING:
    //cout << "SAMPLING " << endl;
    if(valid_in.read()){
      s_h_value = analog_in.read();
      state = WAITING;
      wait_sample_hold_time = 0;
      wait_time = tracking_time.read() + transfer_time.read();
      valid_out.write(false);
    }
    break;
  case WAITING:
    if(wait_sample_hold_time > wait_time){
      state = SAMPLING;
      out.write(s_h_value);
      valid_out.write(true);      
    }
    else
      wait_sample_hold_time++;
    break;
  default:
    SC_REPORT_ERROR("Sample and Hold:", "Invalid state ...");          
  }

}
