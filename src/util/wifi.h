#pragma once
#include <esp_wifi.h>
#include "../config.h"

void wifi_event_handler(void*, esp_event_base_t, int32_t, void*);
void wifi_init(void);
