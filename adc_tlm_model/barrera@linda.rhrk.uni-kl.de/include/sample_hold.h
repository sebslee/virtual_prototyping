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

#ifndef SAMPLE_HOLD_H
#define SAMPLE_HOLD_H

#include <systemc-ams.h>

class sample_hold : sca_tdf::sca_module {
 public:
  sca_tdf::sca_in<double> analog_in; //coming from offset
  sca_tdf::sca_in<bool> valid_in; //sample valid...
  sca_tdf::sca_out<double> out;
  sca_tdf::sca_out<bool>valid_out; // tell cyclic core sample is valid...
  sca_tdf::sca_in<unsigned int> tracking_time; //coming from register file read ...
  sca_tdf::sca_in<unsigned int> transfer_time; //coming from register file read ...  

  sample_hold(sc_module_name name){
    wait_sample_hold_time = 0;
    state = SAMPLING;
  };
 private:
  enum state_t {SAMPLING , WAITING};
  state_t state;
  unsigned int wait_time;
  //int wait_sample_hold_time
  double s_h_value;
  unsigned int wait_sample_hold_time;
  void processing();
  //void set_attributes();
};

#endif

