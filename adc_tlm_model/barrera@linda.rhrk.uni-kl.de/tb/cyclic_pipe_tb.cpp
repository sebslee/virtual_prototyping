//Created by Sebastian Lee


//TODO: Move wave generators to this repo ..
#include "../src/cyclic_pipeline.cpp"
#include "../../exercise_2/src/wave_sine.cpp"
#include <systemc-ams.h>

class parallelizer :  sca_tdf::sca_module{
  
public:
  
  sca_tdf::sca_de::sca_in<bool> bit_in[12];
  sca_tdf::sca_out<double> real_value;
  //sca_tdf::sca_out<bool> start;
  
  parallelizer(sc_module_name name){}
  void set_attributes(){
    real_value.set_timestep(1200, SC_NS);
    //or(
  }
  void processing(){
      double to_int;
      to_int =0;
      for(int i = 0; i < 12 ; i++){
	if(bit_in[i].read())
	  to_int += pow(2, i);
      }
      real_value.write(to_int);
  }
};

//class start : sca_tdf::sca_module {
  //public:
  // sca_tdf::sca_out<bool> start;
  
  //}


int sc_main (int argc , char *argv[]){

  sc_set_time_resolution (10.0 , SC_NS);

  sca_tdf::sca_signal<double> adc_in;
  sca_tdf::sca_signal<double> result;
  //  sca_tdf::sca
  sc_signal<bool> bit_output_sig[12];
  sc_signal<sc_bv<12>> adc_plot;
  //sc_signal<bool> convert;
  wave_sine wave_sine_i ("wave_sine", 1000
			 , 1 , 0 , 1  , false , false , 1);
  cyclic_pipeline cyclic_pipeline_i("cyclic_pipeline_i" , 3.3);
  parallelizer parallelizer_i("parallelizer");
  wave_sine_i.out(adc_in);
  // cyclic_pipeline_i.convert(true);
  cyclic_pipeline_i.analog_in(adc_in);
  //cyclic_pipeline_i.convert(convert);
     for(int i = 0 ; i < 12 ; i ++){
       cyclic_pipeline_i.bit_output[i](bit_output_sig[i]);
        parallelizer_i.bit_in[i](bit_output_sig[i]);
       //cout << bit_output_sig[i] << endl;
   }
       parallelizer_i.real_value(result);
  //cyclic_pipeline_i.bit_output[1](bit_output_sig[1]);
     sca_trace_file *wf = sca_create_vcd_trace_file("waves");
    sca_trace( wf , adc_in , "adc_in");
      sca_trace( wf , result , "adc_out");
    //   sca_trace( wf , bit_output_sig , "bits");
    //sc_start(10 , SC_NS);
	//convert.write(true);
 sc_start(10 , SC_MS);
 return 0;
}


