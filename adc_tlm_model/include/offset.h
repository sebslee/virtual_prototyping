//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// Offset  implementation.
// Offset controlled via register on TLM interface.
//
//////////////////////////////////////////////////////////////////////////////////


//#ifndef OFFSET_H
//#define OFFSET_H

#include <systemc-ams.h>
//#include "defines.h"

class offset : sca_tdf::sca_module{

 public:
  sca_tdf::sca_in<double> input;
  sca_tdf::sca_in<double> offset_in;
  sca_tdf::sca_in<bool> valid_in; //coming from analog mux..
  sca_tdf::sca_out<double> output;
  sca_tdf::sca_out<bool> valid_out;
  offset(sc_module_name name){}
 private:
  double result;
  void set_attributes();
  void processing();    
};

//#endif
