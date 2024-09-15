#pragma once
#include <driver/gpio.h>

void led_init(void);
void led_turn_on(void);
void led_turn_off(void);
bool led_toggle(char state);
