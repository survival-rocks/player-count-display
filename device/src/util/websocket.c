#include "websocket.h"

static void websocket_message_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t*) event_data;

    uint8_t length = data -> data_len;
    if (length == 0) {
        return;
    }

    websocket_data(data -> data_ptr, length);
}

esp_websocket_client_handle_t client = NULL;

void websocket_init(void) {
    esp_websocket_client_config_t websocket_cfg = {
        .uri = WEBSOCKET_URL,
        .disable_auto_reconnect = false,
        .network_timeout_ms = 10000,
        .reconnect_timeout_ms = 200,
    };

    client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_DATA, websocket_message_handler, (void*) client);
}

void websocket_connect(void) {
    if (client == NULL) {
        websocket_init();
    }

    esp_websocket_client_start(client);
}
