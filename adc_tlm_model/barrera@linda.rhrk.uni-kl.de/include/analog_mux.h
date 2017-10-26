//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// Analog MUX.
// Front end module, takes three analog inputs (only three channels supported on
// this project) and muxes it depending on which channel is enabled. Also detects
// a channel enable change and if that happens must disable input for settling time
// This module is connected to S/H module. 
//
//////////////////////////////////////////////////////////////////////////////////

#ifndef ANALOG_MUX
#define ANALOG_MUX

#include <systemc-ams.h>

class analog_mux : sca_tdf::sca_module {
 public:
  sca_tdf::sca_in<bool> start; // coming from UI
  sca_tdf::sca_in<bool> swrst; // soft reset...
  sca_tdf::sca_in<unsigned int> settling_time; //from UI
  sca_tdf::sca_in<double> analog_in_3; 
  sca_tdf::sca_in<double> analog_in_5;
  sca_tdf::sca_in<double> analog_in_7;
  sca_tdf::sca_in<unsigned int> ch_sel; // coming from UI.
  //Output to offset
  sca_tdf::sca_out<bool> valid; //data valid for sample and hold
  sca_tdf::sca_out<double> analog_out; // muxed data ...

  analog_mux(sc_module_name name){
    prev_ch = 0; // only ch1 2 and 3 so the first conversion MUST wait for settling time anyway...
    counter = 0;
    state = IDLE;
  }

 private:
  enum state_t {IDLE , WAITING , ACTIVE};
  state_t state;
  unsigned int counter;
  unsigned int prev_ch; //used to track channel changes to wait settle time ...
  void processing();
  // void set_attributes();
};

#endif
