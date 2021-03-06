#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define LED_1 (7)
#define LED_2 (6)
#define LED_3 (5)
#define LED_4 (4)
#define LED_5 (3)

#include <stdbool.h>
#include <Arduino.h>
#include <stddef.h>

void setting_LED_pinmode();
void trun_on_off_LED(const int led_num, const bool on_off);
void blink_LED(const int led_num, const int delay_time);




#endif
