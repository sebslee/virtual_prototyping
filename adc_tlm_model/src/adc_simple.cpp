//Created by Sebastian Lee

#include <systemc-ams.h>
#include <math.h>
//#define DEBUG

class simple_adc : sca_tdf::sca_module {
public:

  //  sca_tdf::sca_in<double> advref;
  sca_tdf::sca_in<double> analog_in;
  // sca_tdf::sca_in<double> gnd;
  sca_tdf::sca_de::sca_out<bool> bit_output[12]; //Interface to discrete event time domain...
  sca_tdf::sca_de::sca_out<bool> drdy; // data ready ...
  sca_tdf::sca_in<bool> start; // trigger to start conversion...

  simple_adc(sc_module_name name , int _resolution , double _advref){
    advref = _advref;
    resolution = _resolution;
    //bit_output_int = new bool[resolution];
    state = IDLE;
  }

  ~simple_adc(){
    // delete bit_output_int;
  }

private:
  enum state_t {IDLE , WORKING , DONE}; //FSM for internal modelling...
  int iteration; //current adc iteration..
  double advref;
  int  resolution;
  bool bit_output_int[12]; //internal buffer.. write whole chunk of bits at the end of conversion...
  state_t state;
  double vx;
    void set_attributes (){
    analog_in.set_timestep(100 , SC_NS); //period of 100 ns...
  }

  void processing(){

    // double vref; //fixed for each conversion cycle...
      #ifdef DEBUG
    //  cout << "@ " << sca_get_time() << " ADC_SIMPLE: Module activated ..." << endl;
      #endif    
    //FSM Modelling
    switch(state){
    case  IDLE: // acts like hold stage ...
      if(start.read()){
	state = WORKING;
	iteration = 0;
	drdy.write(false);
	vx = analog_in.read();
	//vref = advref.read();
      #ifdef DEBUG
	//cout << "@ " << sca_get_time() << " ADC_SIMPLE: Start triggered! Sample value ..." << vx <<  endl;
      #endif	
      }
      break;
    case  WORKING:
      #ifdef DEBUG
      //	cout << "@ " << sca_get_time() << " ADC_SIMPLE: Vx in Working  ..." << vx <<  endl;
      #endif  
      if(iteration >= resolution) // we are done
	state = DONE;
      else {
	
	if(vx <= advref/2){
	  bit_output_int[resolution - iteration -1 ] = 0;
	  vx = 2 * vx;
	}
	else {
	  bit_output_int[resolution - iteration -1 ] = 1;
	  vx = 2 * (vx - advref/2);	  	  
	}
	        #ifdef DEBUG
	//	  cout << "@ " << sca_get_time() << " Iteration " << iteration << " VX "  << vx << " Bit out " << bit_output_int[resolution - iteration -1] <<  endl;
      #endif		
	iteration++;

      }
      break;
    case  DONE:
      #ifdef DEBUG
      // cout << "DONE" ;
      double sampled_value;
      double to_int;
      to_int =0;
      for(int i = 0; i < resolution ; i++){
	if(bit_output_int[i])
	  to_int += pow(2, i);
      }
      sampled_value = (to_int * advref)/ 4095;
      //cout << "@ " << sca_get_time() << " ADC_SIMPLE: Conversion finished .." << sampled_value <<  endl;
      #endif
      for(int i = 0 ; i < resolution ; i++)
      bit_output[i].write(bit_output_int[i]);
      drdy.write(true);
      state = IDLE;
      break;
    }
  }
  

};
