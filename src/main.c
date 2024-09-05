#include <stdlib.h>
#include "nvs_flash.h"

#include "util/wifi.h"
#include "util/websocket.h"
#include "util/display.h"

void websocket_data(char *data, int size) {
    data[size] = '\0';
    show_count(atoi(data));
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    init_wifi();
    init_display();
    init_websocket();
}
