//Created by Sebastian Lee

#include "../src/wave_saw_tooth.cpp"

class drain  : public sca_tdf::sca_module {
  public:

  sca_tdf::sca_in <double> in;
  drain(sc_core::sc_module_name name){}
    void set_attributes (){
      in.set_timestep(100 , SC_NS);
      in.set_rate(1);
   }
  void processing(){
    #ifdef DEBUG
    //cout << "Sink processing.." ;
    #endif
  }
 
};

int sc_main (int argc , char *argv[]){

  sc_set_time_resolution (10.0 , SC_NS);
  //Signals
  sca_tdf::sca_signal<double> saw_source("sine_source");

  saw_tooth saw_tooth_i("saw", 1.0 , 1000 , 0.5 , 0, 1  );
  drain sink("sink");

  saw_tooth_i.out(saw_source);
  sink.in(saw_source);

  sca_trace_file* tfp = sca_create_tabular_trace_file("saw_tooth");
  sca_trace(tfp , saw_source , "saw");

  sc_start(10 , SC_MS);


  return 0;
}

  

