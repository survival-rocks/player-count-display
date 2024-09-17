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
    display_init_gpio();

    // interrupt timer
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 10000 // 10kHz
    };

    gptimer_handle_t gptimer = NULL;
    gptimer_new_timer(&timer_config, &gptimer);

    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 167. / SEGMENTS, // 60Hz per segment
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
