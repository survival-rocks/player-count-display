#pragma once
#include <esp_wifi.h>
#include "../config.h"

void wifi_ready(void);
void wifi_disconnected(void);
void wifi_init(void);
