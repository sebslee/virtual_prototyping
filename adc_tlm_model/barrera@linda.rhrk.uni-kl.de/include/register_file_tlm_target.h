
//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// This file models the TLM-Target for the Programmers view
// Register bank modelled as a char array 
//
//////////////////////////////////////////////////////////////////////////////////


#ifndef REG_TLM_TARGET
#define REG_TLM_TARGET

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"


class reg_file_target : sc_module {
 public:
  sc_in_clk sys_clk; // system clock
  tlm_utils::simple_target_socket<reg_file_target> socket; // com socket...
  //R/W functions protocol interface , no debug interface provided... use DEBUG define, useful messages inserted in implementation.
  virtual void b_transport(tlm::tlm_generic_payload& trans , sc_time& delay);
  void update_regs();
  //AC_CR 
  sc_out<bool> start;
  sc_out<bool> swrst;
  //AC_MR
  sc_out<bool> transfer[2];
  sc_out<bool> settling[2];
  sc_out<bool> lowres;
  sc_out<bool> tracking_time[4];
  //ADC CHER
  sc_out<bool> ch_3_en;
  sc_out<bool> ch_5_en;
  sc_out<bool> ch_7_en;
  //ADC CHDR
  sc_out<bool> ch_3_dis;
  sc_out<bool> ch_5_dis;
  sc_out<bool> ch_7_dis;
  //ADC CHSR R/O
  sc_in<bool> ch3_en;
  sc_in<bool> ch5_en;
  sc_in<bool> ch7_en;  
  //ADC CHGR //use gain 0 only ...
  sc_out<bool> gain[2];
  //ADC COR //use offset 0 only..
  sc_out<bool> offset[2];
  //ADC CDR3 converted data...
  sc_in<bool> data_ch3[12];
  sc_in<bool> data_ch5[12];  
  sc_in<bool> data_ch7[12];  

  
  
 SC_CTOR(reg_file_target) : socket("socket") {
    //register callback...
    socket.register_b_transport(this , &reg_file_target::b_transport);
    SC_CTHREAD(update_regs , sys_clk.pos());// clocked thread will update the visible registers to the analog part of the model..
  }
  
 private:
  //register definition ...
  unsigned char reg_array[MAX_OFFSET]; // All registers bundled in a single char array...

  
};

#endif

