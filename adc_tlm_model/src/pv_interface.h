//Created by Sebastian Lee
// Programmers view interface, contains ADC system wrapper instance
// plus three PV functions available to use in FW development:

#include <systemc.h>
#include <systemc-ams.h>
#include "../src/adc_system.cpp"
#include "../src/wave_sine.cpp"
#include "../src/wave_saw_tooth.cpp"


class pv_interface : public sc_module {

 public:
  sca_tdf::sca_signal<double> sine;
  sca_tdf::sca_signal<double> cosine;
  sca_tdf::sca_signal<double> saw;
  
  sc_clock *sys_clk;

  wave_sine *wave_sine_i;
  wave_sine *wave_cosine_i;
  saw_tooth  *wave_saw_i;

  adc_system *adc_system_i;

  pv_interface(sc_core::sc_module_name name){
    
    adc_system_i = new adc_system("adc_system_i");
    wave_sine_i = new wave_sine("wave_sine", 1000 , 1 , 0 , 1 , false , false , 1);
    wave_cosine_i  = new wave_sine  ("wave_cosine", 1000 , 1 , 0 , 1 , false , false , 1);
    wave_saw_i = new saw_tooth("wave_saw" , 2.0 , 1000  , 0 , 0 ,1);
    sys_clk = new sc_clock("sys_clk" , 10 ,SC_NS ,  0.5 , 10 , SC_NS);

    
    wave_sine_i->out(sine);
    wave_cosine_i->out(cosine);
    wave_saw_i->out(saw);

    adc_system_i->ad3(sine);
    adc_system_i->ad5(cosine);
    adc_system_i->ad7(saw);
    adc_system_i->sys_clk(*sys_clk);
    
  }

  void ADC_Configuration(unsigned int MODE_REGISTER , unsigned int CHGR , unsigned int COR , unsigned int ch_en);

  void ADC_GetStatus (unsigned int &MODE_REGISTER , unsigned int &CHGR , unsigned int &COR , unsigned int &ch_en);

  unsigned int ADC_GetData (unsigned int channel);

  
};

void pv_interface::ADC_Configuration(unsigned int MODE_REGISTER , unsigned int CHGR , unsigned int COR , unsigned int ch_en){

  cout << "@ " << sc_time_stamp() << " ADC Configuration started!!" << endl;

  cout << "@ " << sc_time_stamp() << " Writing 0x" << std::hex << MODE_REGISTER << "  on Mode Register " << endl;

sc_start(MCLK_PERIOD, SC_NS);

adc_system_i->tlm_initiator_i->write_register(ADC_MR , MODE_REGISTER);

  cout << "@ " << sc_time_stamp() << " Writing 0x" << std::hex << CHGR << "  on Channel Gain Register " << endl;

sc_start(MCLK_PERIOD, SC_NS);

adc_system_i->tlm_initiator_i->write_register(ADC_CGR , CHGR);

  cout << "@ " << sc_time_stamp() << " Writing 0x" << std::hex << COR << "  on Channel offset Register " << endl;

sc_start(MCLK_PERIOD, SC_NS);

adc_system_i->tlm_initiator_i->write_register(ADC_COR , COR);

cout << "@ " << sc_time_stamp() << " Enabling channel " << std::hex << ch_en  << endl << "Warning: Channel enable is encoded as a binary value, meaning that 0x08 will enable channel 3 , 0x020 channel 5 and 0x80 channel 7, only this channels are supported!!" << endl;

sc_start(MCLK_PERIOD, SC_NS);

adc_system_i->tlm_initiator_i->write_register(ADC_CHER , ch_en);

sc_start(MCLK_PERIOD, SC_NS);

adc_system_i->tlm_initiator_i->write_register(ADC_CR , 0x02);

cout << "@ " << sc_time_stamp() << " ADC Configuration finished succesfully!! Conversion started and data available in channel data register ... " << endl; 
}

unsigned int pv_interface::ADC_GetData (unsigned int channel){
if(channel == 3)
  return adc_system_i->tlm_initiator_i->read_register(ADC_CDR3);
if(channel == 5)
  return adc_system_i->tlm_initiator_i->read_register(ADC_CDR5);
if(channel == 7)
  return adc_system_i->tlm_initiator_i->read_register(ADC_CDR7);
 else
   cout << "ERROR: Channel " << channel << " not supported!" << endl;
return -10;    
}

void pv_interface::ADC_GetStatus (unsigned int &MODE_REGISTER , unsigned int &CHGR , unsigned int &COR , unsigned int &ch_en){
MODE_REGISTER = adc_system_i->tlm_initiator_i->read_register(ADC_MR);
CHGR = adc_system_i->tlm_initiator_i->read_register(ADC_CGR);
COR = adc_system_i->tlm_initiator_i->read_register(ADC_COR);
ch_en = adc_system_i->tlm_initiator_i->read_register(ADC_CHER);
#ifdef DEBUG
cout << "@ " << sc_time_stamp() << " Returning status : " << endl;
cout << "@ " << sc_time_stamp() << " MODE_REGISTER : 0x" << std::hex << MODE_REGISTER << endl;
cout << "@ " << sc_time_stamp() << " CHANEL GAIN : 0x" << std::hex <<  CHGR << endl;
cout << "@ " << sc_time_stamp() << " CHANEL OFFSET : 0x" << std::hex <<  COR << endl;
cout << "@ " << sc_time_stamp() << " CHANEL CHANNEL ENABLE : 0x" << std::hex <<  ch_en << endl;
#endif
cout << "@ " << sc_time_stamp() << " ADC status returned ! " << endl;
}

int sc_main(int argc, char* argv[])
{  sc_set_time_resolution (10.0 , SC_NS);}




