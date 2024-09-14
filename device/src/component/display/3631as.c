#include "3631as.h"

#if defined(DISPLAY_3631AS)

const uint8_t POSITIONS[] = { 8, 9, 21 };
const uint8_t PINS[] = {
    20, // A
    7,  // B
    3,  // C
    1,  // D
    0,  // E
    10, // F
    4,  // G
    2,  // DP
};

void display_send_byte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(PINS[i], byte & (1 << i));
    }
}

void display_digit(uint8_t digit, uint8_t position) {
    for (uint8_t i = 0; i < SEGMENTS; i++) {
        gpio_set_level(POSITIONS[i], 1);
    }

    display_send_byte(~digit);
    gpio_set_level(POSITIONS[position], 0);
}

void display_init_gpio(void) {
    uint64_t mask = 0;
    for (uint8_t i = 0; i < 8; i++) {
        mask |= (1 << PINS[i]);
    }

    for (uint8_t i = 0; i < SEGMENTS; i++) {
        mask |= (1 << POSITIONS[i]);
    }

    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = mask,
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);
}

#endif
