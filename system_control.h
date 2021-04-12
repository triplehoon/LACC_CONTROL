#pragma once
#define PIN_FPGA_CONTROL (2)
#define ANAL_PIN_BATREF (2)
#define PIN_5V_CONTROL0 (48)
#define PIN_5V_CONTROL1 (49)
#define PIN_5V_CONTROL2 (50)
#define PIN_5V_CONTROL3 (51)
#define PIN_5V_CONTROL4 (52)
#define PIN_5V_CONTROL5 (53)
#define STRING_BUFFER_SIZE (1024)
#define HV_AMON_ANAL (0)
#define HV_VMON_ANAL (1)
#define ADC_RESOLUTION (0.0049)
#define ADC_To_HV (200)
#define ADC_To_CURR (2)

#include <Arduino.h>
#include <Wire.h>
#include "MCP4725.h"
#include "HV_control.h"
#include "led_control.h"

static char s_StringBuffer[STRING_BUFFER_SIZE];

class SystemControl
{
private:
    HvControl* HVCon;
    double HVModuleVoltage;
    double HVModuleCurrent;    
    double BatteryVoltage;
    bool IsFPGAOn = false;
    bool IsSwitchOn[6];
    MCP4725 dac;
    void SerialWriteAllCurrentValues();
    double GetBatteryVoltage();
    double GetHVModuleVoltage();
    double GetHVModuleCurrent();
    void TurnOnOffFPGA(const bool onoff);
    void TurnOnOffSwitch(const bool onoff, const int pinNum);
    void SerialWriteTurnOnHV(int segmentMillisecond);
    void SerialWriteTurnOffHV(int segmentMillisecond);
    bool IsHVOn;
public:
    void WaitForCommand();
    SystemControl();
    
};

