#include "HV_control.h"

HvControl::HvControl() 
{
    dac.begin(0x60); //addres for the dac is 0x62 (default) or 0x63 (A0 pin tied to VCC)
}

 void HvControl::TestMCP4725() 
 {
      
 }