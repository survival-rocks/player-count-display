#pragma once
#include <driver/gpio.h>
#include <driver/gptimer.h>
#include <esp_attr.h>
#include "../config.h"

void display_init(void);
void display_send_byte(uint8_t data);
void display_show(const char *data, uint8_t length);
void display_task(void);
void display_loading(void);
