#include "display.h"

const uint8_t DIGITS[] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
};

uint8_t on_display[SEGMENTS];
uint8_t position = 0;

uint8_t loading = 0;
uint8_t loading_position = 1;
uint8_t loading_counter = 0;

static bool IRAM_ATTR timer_on_alarm(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data) {
    if (loading && ++loading_counter == 100) {
        for (uint8_t i = 0; i < SEGMENTS; i++) {
            on_display[i] = loading_position == i? 0b01111111 : 0xFF;
        }

        if (++loading_position >= SEGMENTS) {
            loading_position = 1;
        }

        loading_counter = 0;
    }

    display_task();
    return false;
}

void display_init(void) {
    // clear display
    for (uint8_t i = 0; i < SEGMENTS; i++) {
        on_display[i] = 0xFF;
    }

    // gpio
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1 << SCLK_PIN) | (1 << RCLK_PIN) | (1 << DIO_PIN),
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);

    // interrupt timer
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000 // 1MHz
    };

    gptimer_handle_t gptimer = NULL;
    gptimer_new_timer(&timer_config, &gptimer);

    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 5000, // 5ms
        .reload_count = 0,
        .flags.auto_reload_on_alarm = true
    };

    gptimer_set_alarm_action(gptimer, &alarm_config);

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_on_alarm
    };

    gptimer_register_event_callbacks(gptimer, &cbs, NULL);
    gptimer_enable(gptimer);
    gptimer_start(gptimer);
}

void display_send_byte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(SCLK_PIN, 0);
        gpio_set_level(DIO_PIN, (byte & 0x80)? 1 : 0);
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

void display_show(const char *data, uint8_t length) {
    loading = 0;
    uint8_t len = length - 1;
    for (uint8_t i = 0; i < SEGMENTS; i++) {
        if (i < length) {
            on_display[len - i] = DIGITS[data[i] - '0'];
        }
        else {
            on_display[i] = 0xFF;
        }
    }
}

void display_task(void) {
    display_digit(on_display[position], position);

    if (++position >= SEGMENTS) {
        position = 0;
    }
}

void display_loading(void) {
    loading = 1;
}
