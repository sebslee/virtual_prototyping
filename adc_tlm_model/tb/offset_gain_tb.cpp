//Created by Sebastian Lee
// Simple test bench for offset and gain modules..

#include "systemc-ams.h"

#include "../../exercise_2/src/wave_sine.cpp"
#include "../src/gain_stage.cpp"
#include "../src/offset.cpp"

class dummy : public sca_tdf::sca_module{
public :
  sca_tdf::sca_out<double> offset_out;
  sca_tdf::sca_out<double> gain;
  
  dummy(sc_core::sc_module_name name){}
  void set_attributes(){
    gain.set_timestep(100, SC_NS);
  }
  void processing(){
    gain.write(3);
    offset_out.write(2);
  }
};


int sc_main (int argc , char *argv[]){

  sc_set_time_resolution (10.0 , SC_NS);
  
  //signals..
  sca_tdf::sca_signal<double> sine_source("sine_source");
  sca_tdf::sca_signal<double> sine_gain("sine_amp");
  sca_tdf::sca_signal<double> sine_offset("sine_offset");
  sca_tdf::sca_signal<double> offset_s("offset");
  sca_tdf::sca_signal<double> gain_s("gain");

  wave_sine sine1("source" , 1000);
  dummy dummy_i("dummy");
  pga pga_i("pga");
  offset offset_i("offset_i");
  
  sine1.out(sine_source);
  dummy_i.gain(gain_s);
  dummy_i.offset_out(offset_s);
  offset_i.input(sine_source);
  offset_i.output(sine_offset);
  offset_i.offset_in(offset_s);
  pga_i.input(sine_source);
  pga_i.output(sine_gain);
  pga_i.gain(gain_s);

    //wave dumping...
  sca_trace_file* tfp = sca_create_tabular_trace_file("test");
  sca_trace(tfp , sine_source , "sine_source");
  sca_trace(tfp , sine_gain , "sine_pga");
  sca_trace(tfp , sine_offset, "sine_offset");

  sc_start(10 , SC_MS);
  sca_close_tabular_trace_file(tfp);
  return 0;
}
