#pragma once
#include <driver/gpio.h>
#include <driver/gptimer.h>
#include <esp_attr.h>
#include "../../config.h"

void display_send_byte(uint8_t byte);
void display_digit(uint8_t digit, uint8_t position);
void display_init_gpio(void);
