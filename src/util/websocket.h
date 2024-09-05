#pragma once
#include "esp_websocket_client.h"

void init_websocket(void);
void websocket_data(char*, int);
