//Created by Sebastian Lee

#ifndef ADC_PIPE_STAGE
#define ADC_PIPE_STAGE

#include <systemc-ams.h>

class adc_cyclic_pipe_stage : sca_tdf::sca_module {
 public: 
  //sca_tdf::sca_in<double> advref;
  //vx_in.set_timestep(100 , SC_NS);
  sca_tdf::sca_in<double> vx_in;
  sca_tdf::sca_out<double> vo_out;
  sca_tdf::sca_de::sca_out<bool> bit_out;

  adc_cyclic_pipe_stage(sc_module_name name , double _advref){
    advref = _advref;
  }

 private:
  double advref;
  double vx;
  double vo;
  bool bit_o;

  void processing();
  void set_attributes();
  
};

#endif
