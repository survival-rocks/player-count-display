#include "util/wifi.h"
#include "util/websocket.h"
#include "util/display.h"

void websocket_data(const char *data, uint8_t length) {
    display_show(data, length);
}

void wifi_disconnected(void) {
    display_loading();
}

void wifi_ready(void) {
    websocket_connect();
}

void app_main(void) {
    display_init();
    display_loading();
    wifi_init();
    websocket_init();
}
