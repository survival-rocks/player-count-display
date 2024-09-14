#include "3461bs_74hc595.h"

#if defined(DISPLAY_3461BS_74HC595)

const uint8_t SCLK_PIN = 4;
const uint8_t RCLK_PIN = 3;
const uint8_t DIO_PIN = 2;

void display_init_gpio(void) {
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1 << SCLK_PIN) | (1 << RCLK_PIN) | (1 << DIO_PIN),
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);
}

void display_send_byte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(SCLK_PIN, 0);
        gpio_set_level(DIO_PIN, byte & 0x80);
        gpio_set_level(SCLK_PIN, 1);
        byte <<= 1;
    }
}

void display_digit(uint8_t digit, uint8_t position) {
    // send data
    display_send_byte(digit);
    display_send_byte(1 << position);

    // latch data
    gpio_set_level(RCLK_PIN, 0);
    gpio_set_level(RCLK_PIN, 1);
    gpio_set_level(RCLK_PIN, 0);
}

#endif
