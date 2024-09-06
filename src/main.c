#include <nvs_flash.h>

#include "util/wifi.h"
#include "util/websocket.h"
#include "util/display.h"

void websocket_data(const char *data, uint8_t length) {
    display_show(data, length);
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    wifi_init();
    websocket_init();
    display_init();
}
