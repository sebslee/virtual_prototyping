//Created by Sebastian Lee
// Top level module wraps all ADC SystemC-AMS and TLM target/initiator
//This class should be instantiated on the PV SW to simulate the microcontroller transactions...


#include "systemc.h"
#include "systemc-ams.h"


#include "../src/offset.cpp"
#include "../src/user_interface.cpp"
#include "../src/analog_mux.cpp"
#include "../src/sample_hold.cpp"
#include "../src/gain_stage.cpp"
#include "../src/adc_simple.cpp"
#include "../src/tlm_initiator.cpp"
#include "../src/register_file_tlm_target.cpp"

class adc_system : public sc_module {
public:
  //Primary inputs
  sca_tdf::sca_in<double> ad3;
  sca_tdf::sca_in<double> ad5;
  sca_tdf::sca_in<double> ad7;

  sc_in_clk sys_clk; //Primary clock, ADC clock fixed, prescaling possible?

  //Connect signals  ..
  sc_signal<bool> start;
  sc_signal<bool> swrst;

  sc_signal<bool> transfer[2];
  sc_signal<bool> settling[2];
  sc_signal<bool> lowres;
  //sc_signal<unsigned int> tracking_time;
  //ADC CHER
  sc_signal<bool> ch_3_en;
  sc_signal<bool> ch_5_en;
  sc_signal<bool> ch_7_en;
  //ADC CHDR
  sc_signal<bool> ch_3_dis;
  sc_signal<bool> ch_5_dis;
  sc_signal<bool> ch_7_dis;
  //ADC CHSR R/O
  //ADC CHGR //use gain 0 only ...
  sc_signal<bool> gain_ui[2];
  //ADC COR //use offset 0 only..
  sc_signal<bool> offset_ui[2];
  //ADC CDR3 converted data...  to register bank
  sc_signal<bool> data_ch3[12];
  sc_signal<bool> data_ch5[12];  
  sc_signal<bool> data_ch7[12];
  //Tracking time
  sc_signal<bool> tracking_time[4];
  //From UI to MUX
  sca_tdf::sca_signal<bool> start_mux;
  sca_tdf::sca_signal<bool> swrst_mux;
  sca_tdf::sca_signal<unsigned int> ch_sel_out_mux;
  sca_tdf::sca_signal<unsigned int> settling_time_mux;
  //From UI to Offset
   sca_tdf::sca_signal<double> offset_value;  
  //From MUX to Offset
  sca_tdf::sca_signal<bool> valid_mux;
  sca_tdf::sca_signal<double> analog_mux_out;  
  //From Offset to S/H
  sca_tdf::sca_signal<bool> valid_offset;
  sca_tdf::sca_signal<double> offset_out;
  //From UI to S/H
  sca_tdf::sca_signal<unsigned int> tracking_time_ui;
  sca_tdf::sca_signal<unsigned int> transfer_time_ui;
  // From UI to PGA
  sca_tdf::sca_signal<double> gain;  
  //Ftom S/H to PGA
  sca_tdf::sca_signal<double> sh_out;  
  sca_tdf::sca_signal<bool> sh_valid;
  //From PGA to Cyclic pipe
  sca_tdf::sca_signal<bool> pga_valid;
  sca_tdf::sca_signal<double> pga_out;  
  //From Cyclic pipe to UI
  sc_signal<bool> cyclic_out[12];
  sc_signal<bool> bit_output[RESOLUTION];
  sc_signal<bool> adc_drdy;
  //Channel staus register enables
  sc_signal<bool> ch3_en;
  sc_signal<bool> ch5_en;
  sc_signal<bool> ch7_en;   
  //Channe data outputs
  //sc_signal<bool> data_ch3, data_ch5 , data_ch7 [12];

  

  //INSTANCES
  user_interface *user_interface_i;
  analog_mux *analog_mux_i;
  offset *offset_i;
  sample_hold *sample_hold_i;
  pga *pga_i;
 //cyclic_pipeline cyclic_pipeline_i("cyclic_i");
  simple_adc *simple_adc_i;

  //TLM
  reg_file_target *reg_file_target_i;
  tlm_initiator *tlm_initiator_i;

  adc_system(sc_core::sc_module_name name){

    user_interface_i = new user_interface("user_interface");
    analog_mux_i = new analog_mux("analog_mux");
    sample_hold_i = new sample_hold("sample_hold_i");
    pga_i = new pga ("pga");
    simple_adc_i = new  simple_adc ("simple_adc", 12 , 3.3);
    reg_file_target_i = new reg_file_target("reg_file_target");
    tlm_initiator_i = new tlm_initiator ("tlm_init");
    offset_i = new offset("offset");
       
   //User interface
 //Input
 user_interface_i->start(start);
 user_interface_i->swrst(swrst);
 user_interface_i->transfer[0](transfer[0]); 
 user_interface_i->transfer[1](transfer[1]);  
 user_interface_i->settling[0](settling[0]); 
 user_interface_i->settling[1](settling[1]);
 user_interface_i->lowres(lowres);
 user_interface_i->ch_3_en(ch_3_en); 
 user_interface_i->ch_5_en(ch_5_en);
 user_interface_i->ch_7_en(ch_7_en);
 user_interface_i->ch_3_dis(ch_3_dis); 
 user_interface_i->ch_5_dis(ch_5_dis);
 user_interface_i->ch_7_dis(ch_7_dis);
 user_interface_i->gain_in[0](gain_ui[0]); 
 user_interface_i->gain_in[1](gain_ui[1]);  
 user_interface_i->offset[0](offset_ui[0]); 
 user_interface_i->offset[1](offset_ui[1]);
 user_interface_i->tracking_time[0](tracking_time[0]);
 user_interface_i->tracking_time[1](tracking_time[1]);
 user_interface_i->tracking_time[2](tracking_time[2]);
 user_interface_i->tracking_time[3](tracking_time[3]);
 user_interface_i->ch3_en(ch3_en);
 user_interface_i->ch5_en(ch5_en);
 user_interface_i->ch7_en(ch7_en);
 user_interface_i->drdy(adc_drdy);

 //Output
 //To MUX
 user_interface_i->start_mux(start_mux);
 user_interface_i->swrst_mux(swrst_mux);
 user_interface_i->ch_sel_out_mux(ch_sel_out_mux);
 user_interface_i->settling_time_mux(settling_time_mux);
 //To Offset
 user_interface_i->offset_value(offset_value);
 //To Sample and hold
 user_interface_i->transfer_time_ui(transfer_time_ui);
 user_interface_i->tracking_time_ui(tracking_time_ui);
 //To PGA
 user_interface_i->gain_out(gain);
 //Analog mux
 //Input
 analog_mux_i->start(start_mux);
 analog_mux_i->swrst(swrst_mux);
 analog_mux_i->settling_time(settling_time_mux);

 analog_mux_i->analog_in_3(ad3); 
 analog_mux_i->analog_in_5(ad5);
 analog_mux_i->analog_in_7(ad7);

 analog_mux_i->ch_sel(ch_sel_out_mux);

 //Output to offset
 analog_mux_i->valid(valid_mux); 
 analog_mux_i->analog_out(analog_mux_out);

 //Offset
 //Input
 offset_i->input(analog_mux_out);
 offset_i->offset_in(offset_value);
 offset_i->valid_in(valid_mux);
 //offset_i->valid_out(valid_offset);

 //Output to S/H
 offset_i->output(offset_out);
 offset_i->valid_out(valid_offset);
 //Sample and Hold
 sample_hold_i->analog_in(offset_out);
 sample_hold_i->valid_in(valid_offset);
 sample_hold_i->out(sh_out);
 sample_hold_i->valid_out(sh_valid);
 sample_hold_i->tracking_time(tracking_time_ui); 
 sample_hold_i->transfer_time(transfer_time_ui);
 //PGA
 pga_i->input(sh_out);
 pga_i->gain(gain);
 pga_i->valid_in(sh_valid);
 pga_i->valid_out(pga_valid);
 pga_i->output(pga_out);

 //Cyclic pipe
 simple_adc_i->analog_in(pga_out);
 simple_adc_i->start(pga_valid);
 simple_adc_i->drdy(adc_drdy); 

 for(int i = 0 ; i < 12 ; i ++){
   simple_adc_i->bit_output[i](cyclic_out[i]);
   user_interface_i->data_ch3[i](data_ch3[i]);
   user_interface_i->data_ch5[i](data_ch5[i]);
   user_interface_i->data_ch7[i](data_ch7[i]);   
   user_interface_i->cyclic_in[i](cyclic_out[i]);
   
 }
 
  //Register file connections

  //reg_file_target_i->sys_clk(sys_clk);
  reg_file_target_i->start(start);
  reg_file_target_i->swrst(swrst);
  reg_file_target_i->transfer[0](transfer[0]);
  reg_file_target_i->transfer[1](transfer[1]);  
  reg_file_target_i->settling[0](settling[0]);
  reg_file_target_i->settling[1](settling[1]);  
  reg_file_target_i->lowres(lowres);
  reg_file_target_i->tracking_time[0](tracking_time[0]);
  reg_file_target_i->tracking_time[1](tracking_time[1]);
  reg_file_target_i->tracking_time[2](tracking_time[2]);
  reg_file_target_i->tracking_time[3](tracking_time[3]);  
  reg_file_target_i->ch_3_en(ch_3_en);
  reg_file_target_i->ch_5_en(ch_5_en);
  reg_file_target_i->ch_7_en(ch_7_en);
  reg_file_target_i->ch_3_dis(ch_3_dis);
  reg_file_target_i->ch_5_dis(ch_5_dis);
  reg_file_target_i->ch_7_dis(ch_7_dis);
  reg_file_target_i->gain[0](gain_ui[0]);
  reg_file_target_i->gain[1](gain_ui[1]);  
  reg_file_target_i->offset[0](offset_ui[0]);
  reg_file_target_i->offset[1](offset_ui[1]);

  reg_file_target_i->ch3_en(ch3_en);
  reg_file_target_i->ch5_en(ch5_en);
  reg_file_target_i->ch7_en(ch7_en);  

   for(int i = 0 ; i < 12 ; i ++ ){
  reg_file_target_i->data_ch3[i](data_ch3[i]);
  reg_file_target_i->data_ch5[i](data_ch5[i]);
  reg_file_target_i->data_ch7[i](data_ch7[i]);  
   }
   reg_file_target_i-> sys_clk(sys_clk);
  tlm_initiator_i->socket.bind(reg_file_target_i->socket);
  cout << "ADC System elaborated succesfully!" << endl;
  }
};
