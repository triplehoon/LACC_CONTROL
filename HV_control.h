#ifndef HV_CONTROL_H
#define HV_CONTROL_H

#define HV_AMON_ANAL (0)
#define HV_VMON_ANAL (1)
#define ADC_To_HV (200)

#include <Arduino.h>
#include <Wire.h>
#include "MCP4725.h"

class HvControl{
private:
    MCP4725 dac;
    /* data */
public:
    HvControl();
    void TestMCP4725();
    void SetHighVoltage(const double voltage);    
    void SerialReadVoltage();
};





#endif
