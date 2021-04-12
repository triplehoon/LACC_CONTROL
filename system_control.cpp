#include "system_control.h"


SystemControl::SystemControl(){
    Serial.begin(9600);
    setting_LED_pinmode();
    dac.begin(0x60);

    for (int i = 0; i < STRING_BUFFER_SIZE; ++i) {
        s_StringBuffer[i] = '\0';
    }
    for (int i = 0; i < 6; ++i) {
        TurnOnOffSwitch(false, i);
    }

    pinMode(PIN_FPGA_CONTROL, OUTPUT);
    pinMode(PIN_5V_CONTROL0, OUTPUT);
    pinMode(PIN_5V_CONTROL1, OUTPUT);
    pinMode(PIN_5V_CONTROL2, OUTPUT);
    pinMode(PIN_5V_CONTROL3, OUTPUT);
    pinMode(PIN_5V_CONTROL4, OUTPUT);
    pinMode(PIN_5V_CONTROL5, OUTPUT);

    if (GetHVModuleVoltage() > 500) {
        IsHVOn = true;
    } else {
        IsHVOn = false;
    }
}

void SystemControl::WaitForCommand()
{
    int i = 0;
    while (true) {
        if (Serial.available() > 0) {
            s_StringBuffer[i] = (char)Serial.read();
            //Serial.write(s_StringBuffer[i]);
            if (s_StringBuffer[i] == '\n') {
                s_StringBuffer[i] = '\0';
                //Serial.write("check\n");
                break;
            }
            ++i;
            if (i == STRING_BUFFER_SIZE) {
                i = 0;
            }
        }
    }
    char* check = strtok(s_StringBuffer, ":");
    if (strcmp(check, "check") == 0) {       
        SerialWriteAllCurrentValues();
        return;
    }
    
    if (strcmp(check, "sethv") == 0) {
        check = strtok(NULL, ":");
        if (strcmp(check, "on") == 0) {
            SerialWriteTurnOnHV(20);
        }
        if (strcmp(check, "off") == 0) {
            SerialWriteTurnOffHV(20);
        }
        SerialWriteAllCurrentValues();
        return;
    }
    if (strcmp(check, "setfpga") == 0) {
        check = strtok(NULL, ":");
        if (strcmp(check, "on") == 0) {
            TurnOnOffFPGA(true);
        }
        if (strcmp(check, "off") == 0) {
            TurnOnOffFPGA(false);
        }
        SerialWriteAllCurrentValues();
        return;
    }
    if (strcmp(check, "setswitch") == 0) {
        char num = strtok(NULL, ":")[0];
        check = strtok(NULL, ":");
        if (strcmp(check, "on") == 0) {
            switch (num) {
            case '0':
                TurnOnOffSwitch(true, 0);
                break;
            case '1':
                TurnOnOffSwitch(true, 1);
                break;
            case '2':
                TurnOnOffSwitch(true, 2);
                break;
            case '3':
                TurnOnOffSwitch(true, 3);
                break;
            case '4':
                TurnOnOffSwitch(true, 4);
                break;
            case '5':
                TurnOnOffSwitch(true, 5);
                break;
            default:
                break;
            }
        }
        if (strcmp(check, "off") == 0) {
            switch (num) {
            case '0':
                TurnOnOffSwitch(false, 0);
                break;
            case '1':
                TurnOnOffSwitch(false, 1);
                break;
            case '2':
                TurnOnOffSwitch(false, 2);
                break;
            case '3':
                TurnOnOffSwitch(false, 3);
                break;
            case '4':
                TurnOnOffSwitch(false, 4);
                break;
            case '5':
                TurnOnOffSwitch(false, 5);
                break;
            default:
                break;
            }
        }

        SerialWriteAllCurrentValues();
        return;
    }

    

}

void SystemControl::SerialWriteAllCurrentValues()
{
    double hvVolt = GetHVModuleVoltage();
    double hvCurr = GetHVModuleCurrent();
    double batVolt = GetBatteryVoltage();
    Serial.print("hvvolt:");
    Serial.print(hvVolt, 4);
    Serial.print(",");

    Serial.print("hvcurr:");
    Serial.print(hvCurr, 4);
    Serial.print(",");

    Serial.print("batvolt:");
    Serial.print(batVolt, 4);
    Serial.print(",");

    Serial.print("fpga:");
    if (IsFPGAOn) {
        Serial.print("on");
    } else {
        Serial.print("off");
    }
    Serial.print(",");
    for (int i = 0; i < 6; ++i) {
        Serial.print("switch");
        Serial.print(i);
        Serial.print(":");
        if (IsSwitchOn[i]) {
            Serial.print("on");
        } else {
            Serial.print("off");
        }
        Serial.print(",");
    }
    Serial.println("");
}
double SystemControl::GetBatteryVoltage()
{   
    int volt = analogRead(ANAL_PIN_BATREF);
    return volt * ADC_RESOLUTION * 3;
}
double SystemControl::GetHVModuleVoltage()
{
    int volt = analogRead(HV_VMON_ANAL);
    return volt * ADC_RESOLUTION * ADC_To_HV;
}
double SystemControl::GetHVModuleCurrent()
{
    int volt = analogRead(HV_AMON_ANAL);
    return volt * ADC_RESOLUTION * ADC_To_CURR;
}
void SystemControl::TurnOnOffFPGA(const bool onoff)
{
    if (onoff) {
        digitalWrite(PIN_FPGA_CONTROL, HIGH);
        IsFPGAOn = true;
    } else {
        digitalWrite(PIN_FPGA_CONTROL, LOW);
        IsFPGAOn = false;
    }
}
void SystemControl::TurnOnOffSwitch(const bool onoff, const int pinNum)
{
    if (onoff) {
        digitalWrite(PIN_5V_CONTROL0 + pinNum, HIGH);
        IsSwitchOn[pinNum] = true;
    } else {
        digitalWrite(PIN_5V_CONTROL0 + pinNum, LOW);
        IsSwitchOn[pinNum] = false;
    }
}
void SystemControl::SerialWriteTurnOnHV(int segmentMillisecond)
{
    if (IsHVOn) {
        Serial.println("done");
        return;
    }
    
    
    double segement_by_volt = 4092 / 1000;
    for (int i = 0; i < 1000; ++i) {
        dac.setVoltage(round(i * segement_by_volt));
        Serial.println(GetHVModuleVoltage());
        if (GetHVModuleVoltage() > 200) {
            trun_on_off_LED(5, true);
        }
        if (GetHVModuleVoltage() > 400) {
            trun_on_off_LED(4, true);
        }
        if (GetHVModuleVoltage() > 600) {
            trun_on_off_LED(3, true);
        }
        if (GetHVModuleVoltage() > 800) {
            trun_on_off_LED(2, true);
        }
        if (GetHVModuleVoltage() > 950) {
            trun_on_off_LED(1, true);
        }
       
        delay(segmentMillisecond);
    }
    IsHVOn = true;
    Serial.println("done");

    

}
void SystemControl::SerialWriteTurnOffHV(int segmentMillisecond)
{
     if (!IsHVOn) {
        Serial.println("done");
        return;
    }
    double segement_by_volt = 4092 / 1000;
    trun_on_off_LED(5, true);
    trun_on_off_LED(4, true);
    trun_on_off_LED(3, true);
    trun_on_off_LED(2, true);
    trun_on_off_LED(1, true);
    for (int i = 0; i < 1000; ++i) {
        dac.setVoltage(round((1000 - i) * segement_by_volt));
        Serial.println(GetHVModuleVoltage());

        if (GetHVModuleVoltage() < 100){
            trun_on_off_LED(5, false);
        }
        if (GetHVModuleVoltage() < 200){
            trun_on_off_LED(4, false);
        }
        if (GetHVModuleVoltage() < 400){
            trun_on_off_LED(3, false);
        }
        if (GetHVModuleVoltage() < 600){
            trun_on_off_LED(2, false);
        }
        if (GetHVModuleVoltage() < 800){
            trun_on_off_LED(1, false);
        }

        delay(segmentMillisecond);
    }
    IsHVOn = false;

    Serial.println("done");
}
