#include "led.h"

const uint8_t LED_PIN = 6;

void led_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1 << LED_PIN,
        .pull_down_en = 0,
        .pull_up_en = 0
    };
    gpio_config(&io_conf);
    led_turn_off();
}

void led_turn_on(void) {
    gpio_set_level(LED_PIN, 0);
}

void led_turn_off(void) {
    gpio_set_level(LED_PIN, 1);
}

bool led_toggle(char state) {
    switch (state) {
        case '+':
            led_turn_on();
            return true;
        case '-':
            led_turn_off();
            return true;
        default:
            return false;
    }
}
