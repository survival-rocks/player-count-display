#pragma once
#include "../config.h"

#if defined(DISPLAY_3631AS)
#include "display/3631as.h"
#elif defined(DISPLAY_3461BS_74HC595)
#include "display/3461bs_74hc595.h"
#else
#error "No display method defined"
#endif

#ifndef SEGMENTS
#error "No amount of segments defined in display type"
#endif

void display_init(void);
void display_show(const char *data, uint8_t length);
void display_task(void);
void display_loading(void);
