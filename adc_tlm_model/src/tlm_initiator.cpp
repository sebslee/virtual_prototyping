//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// This file models the TLM-Target for the Programmers view. Contains a sc_bv<32>
// for each register modeled. 
//
//////////////////////////////////////////////////////////////////////////////////

#include "../include/tlm_initiator.h"
/*
void tlm_initiator::set_enable(bool _read_en , bool _write_en){
  write_en = _write_en;
  read_en = _read_en;
}

void tlm_initiator::thread(){
  while(true){
    
    wait();
  }
  }*/



void tlm_initiator::write_register(unsigned int address , unsigned int data){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(MCLK_PERIOD , SC_NS); //takes 1 clock cycle..
  trans -> set_command(tlm::TLM_WRITE_COMMAND);
  trans -> set_address(address);
  trans -> set_data_ptr(reinterpret_cast<unsigned char*>(&data));
  trans -> set_data_length(4);  
  trans -> set_streaming_width(1);
  trans -> set_byte_enable_ptr(0);
  trans -> set_dmi_allowed(false);
  trans -> set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  socket -> b_transport(*trans , delay); //blocks..

  //Now check response!

  if(trans -> is_response_error())
    {
          char txt[100];
          sprintf(txt, "Error from b_transport, response status = %s",
                       trans->get_response_string().c_str());
          SC_REPORT_ERROR("TLM-2", txt);
    }

    #ifdef DEBUG_VERBOSE
   else {
    cout << "@ " << sc_time_stamp() << " tlm_initiator: Write completed succesfully!! Addr " << hex << address << "  Data " << data << endl ;    
  }
  
 #endif
  
}



unsigned int tlm_initiator::read_register(unsigned int address){
  unsigned int data;
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(MCLK_PERIOD , SC_NS); //takes 1 clock cycle..
  trans -> set_command(tlm::TLM_READ_COMMAND);
  trans -> set_address(address);
  trans -> set_data_ptr(reinterpret_cast<unsigned char*>(&data));
  trans -> set_data_length(4);  
  trans -> set_streaming_width(1);
  trans -> set_byte_enable_ptr(0);
  trans -> set_dmi_allowed(false);
  trans -> set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  socket -> b_transport(*trans , delay); //blocks..

   if(trans -> is_response_error())
    {
          char txt[100];
          sprintf(txt, "Error from b_transport, response status = %s",
                       trans->get_response_string().c_str());
          SC_REPORT_ERROR("TLM-2", txt);
    }

   else{
     #ifdef DEBUG_VERBOSE
    cout << "@ " << sc_time_stamp() << " tlm_initiator: Read completed succesfully!! Addr " << hex << address << "  Data " << data << endl ;     
     #endif
    //wait(delay);
     return data;
   }
}






 
    
