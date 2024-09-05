#include "websocket.h"

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t*) event_data;
    if (event_id != WEBSOCKET_EVENT_DATA || data -> data_len == 0) {
        return;
    }

    websocket_data(data -> data_ptr, data -> data_len);
}

void init_websocket(void) {
    esp_websocket_client_config_t websocket_cfg = {
        .uri = "ws://count.survival.rocks",
        .disable_auto_reconnect = false,
        .network_timeout_ms = 30000,
        .reconnect_timeout_ms = 500,
    };

    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void*) client);
    esp_websocket_client_start(client);
}
