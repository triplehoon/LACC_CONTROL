#pragma once
#define PIN_FPGA_CONTROL (2)
#define ANAL_PIN_BATREF (2)
#define PIN_5V_CONTROL0 (48)
#define PIN_5V_CONTROL1 (49)
#define PIN_5V_CONTROL2 (50)
#define PIN_5V_CONTROL3 (51)
#define PIN_5V_CONTROL4 (52)
#define PIN_5V_CONTROL5 (53)

#include "HV_control.h"
#include "led_control.h"


enum class eSettingValue
{
    HighVoltage,
    FPGA,
    LED,
    Switch_5V
};

class SystemControl
{
private:
    HvControl* HVCon;
    double HVModuleVoltage;
    double HVModuleCurrent;    
    double BatteryVoltage;
    bool IsFPGAOn;
    bool IsSwitchOn[6];

    void SerialWriteAllCurrentValues();
    double GetBatteryVoltage();
    double GetHVModuleVoltage();
    double GetHVModuleCurrent();
    void TurnOnOffFPGA(const bool onoff);
    void TurnOnOffSwitch(const bool onoff, const int pinNum);
    void SerialWriteTurnOnHV(int segmentMillisecond);
    void SerialWriteTurnOffHV(int segmentMillisecond);
public:
    void WaitForCommand();
    SystemControl();
    
};

