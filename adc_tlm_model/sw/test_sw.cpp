#include "../src/pv_interface.h"

int main (int argc, char* argv[]) {
  
  pv_interface pv_interface_i("pv_interface");
  //sc_set_time_resolution(10, SC_NS);
  unsigned int data , MODE , CHG , CO , CE ; 
  sc_signal<double> sig;
  sc_signal<bool> ch3_en;
  sc_signal<bool> ch5_en;
  sc_trace_file *wf = sc_create_vcd_trace_file("wave_system");
  sc_trace( wf , sig , "signal");
  
  sc_start(5 * MCLK_PERIOD , SC_NS); //Wait some clock cycles.. nice to have implemented reset on registers! (may lose AT approach? )
  
  // sig.write(3);
  pv_interface_i.ADC_Configuration(0x22300000 , 0 , 0 , 0x08);
  pv_interface_i.ADC_GetStatus(MODE, CHG , CO , CE);
  cout << "@ " << sc_time_stamp() << " Simulation started enabling channel 3  " << endl;

  double adc_conv;
  for(int i = 0 ; i < 1000000 ; i ++){
  data = pv_interface_i.ADC_GetData(3);
  adc_conv = (data * 3.3) / 4095;
  sc_start(5, SC_NS);
  sig.write(data);  
  }
  cout << "@ " << sc_time_stamp() << " Changing configuration to channel 5 " << endl;  
  pv_interface_i.ADC_Configuration(0x22300000 , 0 , 0 , 0x20);
  pv_interface_i.ADC_GetStatus(MODE, CHG , CO , CE);
  for(int i = 0 ; i < 1000000 ; i ++){
  data = pv_interface_i.ADC_GetData(5);
  adc_conv = (data * 3.3) / 4095;
  sc_start(5, SC_NS);
  sig.write(data);  
  }
  cout << "@ " << sc_time_stamp() << " Changing configuration to channel 7 " << endl;
  pv_interface_i.ADC_Configuration(0x22300000 , 0 , 0 , 0x80);
  pv_interface_i.ADC_GetStatus(MODE, CHG , CO , CE);  
  for(int i = 0 ; i < 1000000 ; i ++){
  data = pv_interface_i.ADC_GetData(7);
  adc_conv = (data * 3.3) / 4095;
  sc_start(5, SC_NS);
  sig.write(data);  
  } 
  sc_close_vcd_trace_file(wf);
  cout << "@ " << sc_time_stamp() << " Simulation finished! " << endl;
  //cout << data << endl;
  return 0;

}
