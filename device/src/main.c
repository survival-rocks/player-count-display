#include "component/wifi.h"
#include "component/websocket.h"
#include "component/display.h"

// when websocket data is received
void websocket_data(const char *data, uint8_t length) {
    display_show(data, length);
}

// when wifi is disconnected
void wifi_disconnected(void) {
    display_loading();
}

// when websocket is disconnected
void websocket_disconnected(void) {
    display_loading();
}

// when wifi is ready
void wifi_ready(void) {
    websocket_connect();
}

void app_main(void) {
    display_init();
    display_loading();
    wifi_init();
    websocket_init();
}
