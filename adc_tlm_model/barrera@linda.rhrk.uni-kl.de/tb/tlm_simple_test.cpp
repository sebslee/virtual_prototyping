//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// Simple initiator, target test_bench.
// 
//
//////////////////////////////////////////////////////////////////////////////////

#ifndef SIMPLE_TLM_TB
#define SIMPLE_TLM_TB

#include "../src/tlm_initiator.cpp"
#include "../src/register_file_tlm_target.cpp"

int sc_main(int argc, char* argv[])
{
  sc_clock sys_clk("sys_clk" , 10 ,SC_NS ,  0.5 , 10 , SC_NS);
  
  reg_file_target reg_file_target_i("reg_file_target_i");
  tlm_initiator tlm_initiator_i("tlm_initiator_i");
  sc_signal<bool> sig_0 , sig_1 , sig_2 , sig_3 , sig_4 , sig_5 , sig_6 , sig_7 , sig_8 , sig_9  ;
  sc_signal<bool> dummy_0[12];
  sc_signal<bool> dummy_1[12];
  sc_signal<bool> dummy_2[12];
  sc_signal<bool> dummy_3[2];
  sc_signal<bool> dummy_4[2];
  sc_signal<bool> dummy_5[2];
  sc_signal<bool> dummy_6[2];
  sc_signal<bool> dummy_7[4];
  sc_signal<bool> ch3_en, ch5_en , ch7_en;
  sc_signal<bool> data_ch3[12]; 
  sc_signal<bool> data_ch5[12];
  sc_signal<bool> data_ch7[12];  
  //  sc_signal<bool> dummy8
  //tlm_initiator_i.clk(sys_clk);
  reg_file_target_i.sys_clk(sys_clk);
  reg_file_target_i.start(sig_0);
  reg_file_target_i.swrst(sig_1);
  reg_file_target_i.transfer[0](dummy_4[0]);
  reg_file_target_i.transfer[1](dummy_4[1]);  
  reg_file_target_i.settling[0](dummy_5[0]);
  reg_file_target_i.settling[1](dummy_5[1]);  
  reg_file_target_i.lowres(sig_2);
  reg_file_target_i.tracking_time[0](dummy_7[0]);
  reg_file_target_i.tracking_time[1](dummy_7[1]);
  reg_file_target_i.tracking_time[2](dummy_7[2]);
  reg_file_target_i.tracking_time[3](dummy_7[3]);  
  reg_file_target_i.ch_3_en(sig_3);
  reg_file_target_i.ch_5_en(sig_4);
  reg_file_target_i.ch_7_en(sig_5);
  reg_file_target_i.ch_3_dis(sig_6);
  reg_file_target_i.ch_5_dis(sig_7);
  reg_file_target_i.ch_7_dis(sig_8);
  reg_file_target_i.gain[0](dummy_3[0]);
  reg_file_target_i.gain[1](dummy_3[1]);  
  reg_file_target_i.offset[0](dummy_6[0]);
  reg_file_target_i.offset[1](dummy_6[1]);
  
  reg_file_target_i.ch3_en(ch3_en);
  reg_file_target_i.ch5_en(ch5_en);
  reg_file_target_i.ch7_en(ch7_en);  

  for(int i = 0 ; i < 12 ; i ++ ){
  reg_file_target_i.data_ch3[i](data_ch3[i]);
  reg_file_target_i.data_ch5[i](data_ch5[i]);
  reg_file_target_i.data_ch7[i](data_ch7[i]);  
  }
    
  
  tlm_initiator_i.socket.bind(reg_file_target_i.socket);
  bool enable;
  unsigned int write_data;
  unsigned int read_data;
  cout << "Simulation started!!" << endl;

  sc_start(10, SC_NS); //run
  // write_data = 0xFFFFFFFF;
    write_data = 0x22300010;
  // wait(sys_clk.pos());
  //enable = true;
  tlm_initiator_i.write_register(ADC_MR , write_data);
  sc_start(10 , SC_NS);
  read_data = tlm_initiator_i.read_register(ADC_MR);
  sc_start(10 , SC_NS);
  cout << "@ " << sc_time_stamp() << " ADC MR " << read_data << endl ;
  sc_start(10 , SC_NS);  
  sc_stop();
}

#endif
