#include "system_control.h"


SystemControl::SystemControl(){
    Serial.begin(9600);
    setting_LED_pinmode();
    HVCon = new HvControl();
    pinMode(PIN_FPGA_CONTROL, OUTPUT);
    pinMode(PIN_5V_CONTROL0, OUTPUT);
    pinMode(PIN_5V_CONTROL1, OUTPUT);
    pinMode(PIN_5V_CONTROL2, OUTPUT);
    pinMode(PIN_5V_CONTROL3, OUTPUT);
    pinMode(PIN_5V_CONTROL4, OUTPUT);
    pinMode(PIN_5V_CONTROL5, OUTPUT);
}

