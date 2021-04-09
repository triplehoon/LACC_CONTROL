#include "led_control.h"


void setting_LED_pinmode()
{
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);
    pinMode(LED_5, OUTPUT);
}

void trun_on_off_LED(const int led_num, const bool on_off) 
{
    switch (led_num)
    {
    case 1:
        digitalWrite(LED_1, on_off);
        break;
    case 2:
        digitalWrite(LED_2, on_off);
        break;
    case 3:
        digitalWrite(LED_3, on_off);
        break;
    case 4:
        digitalWrite(LED_4, on_off);
        break;
    case 5:
        digitalWrite(LED_5, on_off);
        break;    
    default:
        break;
    }
}
void blink_LED(const int led_num, const int delay_time)
{
    trun_on_off_LED(led_num, 1);
    delay(delay_time);
    trun_on_off_LED(led_num, 0);
    delay(delay_time);
}
