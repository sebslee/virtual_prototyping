// User interface, this is the boundary between the ADC and
// the register interface (TLM).
//
//////////////////////////////////////////////////////////////////////////////////


#include "../include/user_interface.h"
#include "math.h"
void user_interface::processing(){

  unsigned int transfer_time_int, tracking_time_int;
  double offset_int , gain_int;
  unsigned int active_channel;
  swrst_mux.write(swrst.read());  
  start_mux.write(start.read());
  //Channel enable logic...
  if(ch_3_en.read() & !ch_3_dis.read()){
    ch_sel_out_mux.write(3);
    ch3_en.write(true);
    ch5_en.write(false);
    ch7_en.write(false);
    active_channel = 3 ;
  }
  else if(ch_5_en.read() & !ch_5_dis.read()){
    ch_sel_out_mux.write(5);
    ch3_en.write(false);
    ch5_en.write(true);
    ch7_en.write(false); 
    active_channel = 5;    
  }
  else  if(ch_7_en.read() & !ch_7_dis.read()){
    ch_sel_out_mux.write(7);
    ch3_en.write(true);
    ch5_en.write(false);
    ch7_en.write(false);
    active_channel = 7;     
  }  
  else{
    //cout << "disabled.." << ch_3_en.read() << !ch_3_dis.read()  << endl;
    ch_sel_out_mux.write(0);
    ch3_en.write(false);
    ch5_en.write(false);
    ch7_en.write(false);
    active_channel = 0;     
  }
  //Settling time
  if(settling[1].read() == false && settling[0].read() == false){
    settling_time_mux.write(3);
  }
  else if(settling[1].read() == false && settling[0].read() == true){
    settling_time_mux.write(5);
  }
  else if(settling[1].read() == true && settling[0].read() == false){
    settling_time_mux.write(9);
  }
  else if(settling[1].read() == true && settling[0].read() == true){
    settling_time_mux.write(17);
  }
  else
    settling_time_mux = 0;
  //Operation only in single ended mode
  
  if(offset[0].read() == true){
    offset_int = (gain_int -1) * vref_in/2;
    offset_value.write(offset_int);
  }
  else
    offset_value.write(0);
  
  if(!gain_in[1].read() && !gain_in[0].read()){
    gain_int = 1;
  }
  else if(!gain_in[1].read() && !gain_in[0].read()){
    gain_int = 1;
  }
  else if(!gain_in[1].read() && gain_in[0].read()){
    gain_int = 1;
  }
  else if(gain_in[1].read() && !gain_in[0].read()){
    gain_int = 2;
  }
  else if(gain_in[1].read() && gain_in[0].read()){
    gain_int = 4;
  }
  else
    gain_int = 1;

  gain_out.write(gain_int); 
  //Tracking and settling..
  tracking_time_int = 0;
  for (int i = 0 ; i < 4 ; i++)
    if(tracking_time[i].read())
      tracking_time_int += pow(2,i);
  tracking_time_int = (tracking_time_int + 1) ;
  tracking_time_ui.write(tracking_time_int);

  transfer_time_int = 0;
  for (int i = 0 ; i < 2 ; i++)
    if(transfer[i].read())
      transfer_time_int += pow(2,i);
  transfer_time_int = transfer_time_int  * 2 +3;
  transfer_time_ui.write(transfer_time_int);

  
    for (int i = 0 ; i < 12; i ++){
      if(active_channel == 3 && drdy.read()){
	if(!lowres.read()) // write 12 or 10 bits..
	data_ch3[i].write(cyclic_in[i].read());
	else if(i <10)
	  data_ch3[i].write(cyclic_in[i].read()); }	
      }

    for (int i = 0 ; i < 12; i ++){
      if(active_channel == 5 && drdy.read()){
	if(!lowres.read()) // write 12 or 10 bits..
	data_ch5[i].write(cyclic_in[i].read());
	else if(i <10)
	  data_ch5[i].write(cyclic_in[i].read());  }	
      }
      
    for (int i = 0 ; i < 12; i ++){
      if(active_channel == 7 && drdy.read()){
	if(!lowres.read()) // write 12 or 10 bits..
	data_ch7[i].write(cyclic_in[i].read());
	else if(i <10)
	  data_ch7[i].write(cyclic_in[i].read()); }	
      }
            
    if(ch_3_en.read() && !ch_3_dis.read())
      ch3_en.write(true);
    else
      ch3_en.write(false);

    if(ch_5_en.read() && !ch_5_dis.read())
      ch5_en.write(true);
    else
      ch5_en.write(false);    

    if(ch_7_en.read() && !ch_7_dis.read())
      ch7_en.write(true);
    else
      ch7_en.write(false);    
  
    //ch_sel_out_mux.write(3);
    //settling_time_mux.write(2);
    //offset_value.write(1);
    //transfer_time_ui.write(1);
    //tracking_time_ui.write(3);
    //gain_out.write(1.0);
}

void user_interface::set_attributes(){
  start.set_timestep(100 , SC_NS);
}

