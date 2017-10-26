//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// This file models the TLM-Target for the Programmers view. Contains a sc_bv<32>
// for each register modeled. 
//
//////////////////////////////////////////////////////////////////////////////////


#ifndef TLM_INITIATOR
#define TLM_INITIATOR

#include <tlm.h>
#include "tlm_utils/simple_initiator_socket.h"
#include "systemc.h"
#include "defines.h"

class tlm_initiator : sc_module {
 public:
  
 tlm_utils::simple_initiator_socket<tlm_initiator> socket;
 //bool read_en, write_en;
 //sc_in_clk  clk;
 unsigned int read_register(unsigned int address );
 void write_register ( unsigned int address , unsigned int data); //only 32 bit writes supported ...
 
 //void set_enable(bool read_en , bool write_en);
 //void thread(){};
 
 SC_CTOR(tlm_initiator): socket("socket"){
   //read_en = false;
   // write_en = false;
   // SC_CTHREAD(thread, clk.pos());
   //SC_THREAD(write_register)
   
    // SC_CTHREAD(write_register, clk.pos());
   //SC_CTHREAD(read_register, clk.pos());
   //SC_THREAD(read_register);
   //SC_THREAD(write_register);
   //empty constructor...   
 }
};

#endif
