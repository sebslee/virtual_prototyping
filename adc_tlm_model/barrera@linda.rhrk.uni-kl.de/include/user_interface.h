//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// User interface, this is the boundary between the ADC and
// the register interface (TLM).
//
//////////////////////////////////////////////////////////////////////////////////


#ifndef USER_INTERFACE
#define USER_INTERFACE

#include "systemc-ams.h"
#include "defines.h"

class user_interface : sca_tdf::sca_module {
 public:
  user_interface(sc_module_name name , double _vref_in=3.3){
    vref_in = _vref_in;
  };
  //Interface to Register TLM 
  sca_tdf::sca_de::sca_in<bool> start;
  sca_tdf::sca_de::sca_in<bool> swrst;

  sca_tdf::sca_de::sca_in<bool> transfer[2];
  sca_tdf::sca_de::sca_in<bool> settling[2];
  sca_tdf::sca_de::sca_in<bool> lowres;
  sca_tdf::sca_de::sca_in<bool> tracking_time[4];
  //ADC CHER
  sca_tdf::sca_de::sca_in<bool> ch_3_en;
  sca_tdf::sca_de::sca_in<bool> ch_5_en;
  sca_tdf::sca_de::sca_in<bool> ch_7_en;
  //ADC CHDR
  sca_tdf::sca_de::sca_in<bool> ch_3_dis;
  sca_tdf::sca_de::sca_in<bool> ch_5_dis;
  sca_tdf::sca_de::sca_in<bool> ch_7_dis;
  //ADC CHSR R/O
  //ADC CHGR //use gain 0 only ...
  sca_tdf::sca_de::sca_in<bool> gain_in[2];
  //ADC COR //use offset 0 only..
  sca_tdf::sca_de::sca_in<bool> offset[2];
  //ADC CDR3 converted data...  to register bank
  sca_tdf::sca_de::sca_out<bool> data_ch3[12];
  sca_tdf::sca_de::sca_out<bool> data_ch5[12];  
  sca_tdf::sca_de::sca_out<bool> data_ch7[12];  
  //ADC CHSR Register status
  sca_tdf::sca_de::sca_out<bool> ch3_en;
  sca_tdf::sca_de::sca_out<bool> ch5_en;
  sca_tdf::sca_de::sca_out<bool> ch7_en;

  
  //Interface to ADC
  //MUX
  sca_tdf::sca_out<bool> start_mux;
  sca_tdf::sca_out<bool> swrst_mux;
  sca_tdf::sca_out<unsigned int> ch_sel_out_mux;
  sca_tdf::sca_out<unsigned int> settling_time_mux;
  //Offset
  sca_tdf::sca_out<double> offset_value;
  //Sample and hold
  sca_tdf::sca_out<unsigned int> transfer_time_ui;
  sca_tdf::sca_out<unsigned int> tracking_time_ui;
  //PGA
  sca_tdf::sca_out<double> gain_out;
  //Cyclic pipe input
  sca_tdf::sca_de::sca_in<bool> cyclic_in[RESOLUTION];
  sca_tdf::sca_de::sca_in<bool> drdy; //data ready
 private:
  double vref_in;
  void processing();
  void set_attributes();
  
};


#endif
