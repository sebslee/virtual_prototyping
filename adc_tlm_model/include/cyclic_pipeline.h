//Created by Sebastian Lee

#ifndef ADC_PIPELINE
#define ADC_PIPELINE


#define RESOLUTION 12 // nice to add controllability of resolution

#include <systemc-ams.h>
//#include "../src/cyclic_adc_pipe_stage.cpp"

class cyclic_pipeline : sca_tdf::sca_module {
 public:
  sca_tdf::sca_in<double> analog_in; //coming from pga
  sca_tdf::sca_de::sca_out<bool> bit_output[RESOLUTION];
  sca_tdf::sca_in<bool> valid;
  //sca_tdf::sca_de::sca_in<bool> start; 
  //sca_tdf::sca_de::sc_in<sc_bit> convert; // input to enable write, for sim purposes converter is always active ..
  
  cyclic_pipeline(sc_module_name name , double _advref = 3.3){
    advref = _advref;
    counter = 0;
    //initialize pipe with empty values..
    for(int i = 0 ; i < RESOLUTION ; i ++){
      vo[i] = 0;
      vx[i] = 0;
    }    
  }

 private:
  double advref;
  bool curr_conversion[RESOLUTION];
  double vo [RESOLUTION];
  double vx [RESOLUTION];
  int counter;
  #ifdef DEBUG
  double sample_save;
  #endif
  // sca_tdf::sca_signal<bool> bit_out_int[RESOLUTION];

  void set_attributes();
  void processing();
};

#endif
