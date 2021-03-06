//Created by Sebastian Lee

#include "../include/cyclic_pipeline.h"

void cyclic_pipeline::set_attributes(){
  //analog_in.set_timestep(100, SC_NS);
  //analog_in.set_rate(1);
  //for(int i = 0; i < RESOLUTION ; i ++)
    //  bit_output[i].set_rate(1);
  // convert.set_rate(1);
}

void cyclic_pipeline::processing(){
  
  bool out_value_int [RESOLUTION];
  //if(valid.read()){
  vx[0] = analog_in.read(); // sample new value
  
  #ifdef DEBUG
  //double sample_save;
  if(counter == 0)
    sample_save = vx[0];
  //cout << "@ " << sca_get_time() << " Cyclic pipeline sample value " << vx[0] << endl;
  #endif
 
  for ( int i = 0 ; i < RESOLUTION  ; i ++){
    if(vx[i] <= advref/2){
      vo[i] = 2 * vx[i];
      out_value_int[i] = false;
    }
    else{
      vo[i] = 2 * (vx[i] - advref/2);
      out_value_int[i] = true;
    }
    
    //  bit_output[i].write(out_value_int[i]); 
  }

  curr_conversion[RESOLUTION - counter -1] =  out_value_int[counter]; // value just resolved ...
  
  // if(start == 1){
        for(int i = 0 ; i < RESOLUTION ; i++)
	bit_output[i].write(curr_conversion[i]);
	// }
  //cycle pipe
  for (int i =  1 ; i < RESOLUTION ; i ++)
    vx[i] = vo[i-1]; 
   if(counter + 1 < RESOLUTION )
      counter++;
    else{
            #ifdef DEBUG
      // cout << "DONE" ;
      double sampled_value;
      double to_int , err;
      to_int =0;
      for(int i = 0; i < RESOLUTION ; i++){
	if(curr_conversion[i])
	  to_int += pow(2, i);
      }
      sampled_value = (to_int * advref)/ 4095;
      err = (sampled_value - sample_save) ;
      if(err > 0.001)
      cout << "@ " << sca_get_time() << " Error " << err <<  endl;
      
      #endif
      // conversion valid
   counter = 0;
       }
   //}
}


