#pragma once
#include <esp_websocket_client.h>
#include "../config.h"

void websocket_init(void);
void websocket_data(const char*, uint8_t);
void websocket_connect(void);
void websocket_disconnected(void);
