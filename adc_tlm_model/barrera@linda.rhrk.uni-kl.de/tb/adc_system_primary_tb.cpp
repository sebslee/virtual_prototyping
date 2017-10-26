//Created by Sebastian Lee

#include "../src/adc_system.cpp"
//#include "../src/wave_sine.cpp"
#include "../src/wave_sine.cpp"

int sc_main(int argc, char* argv[])
{
  sca_tdf::sca_signal<double> sine;
  
  sc_clock sys_clk("sys_clk" , 10 ,SC_NS ,  0.5 , 10 , SC_NS);
  adc_system adc_system_i("adc");
  wave_sine wave_sine_i ("wave_sine", 1000 , 1 , 0 , 1 , false , false , 1);
  sc_signal<bool> ch_3_en_spy;
  wave_sine_i.out(sine);
  adc_system_i.ad3(sine);
  adc_system_i.ad5(sine);
  adc_system_i.ad7(sine);
  adc_system_i.sys_clk(sys_clk);
  // adc_system_i.user_interface_i->start(ch_3_en_spy);
  unsigned int write_data;
  unsigned int read_data;
  cout << "Simulation started!!" << endl;
  write_data = 0x22300010;
  adc_system_i.tlm_initiator_i->write_register(ADC_MR , write_data);
  sc_start(10 , SC_NS);
  read_data = adc_system_i.tlm_initiator_i->read_register(ADC_MR);
  sc_start(10 , SC_NS);
  //cout << "@ " << sc_time_stamp() << " ADC MR " << read_data << endl ;
  sc_start(200 , SC_NS);
  sc_stop();
  return 0;
}
