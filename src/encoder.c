#include "encoder.h"
#include "hardware/gpio.h"
#include "board_defs.h"

static const uint8_t ENCODER_GPIOS[] = ENCODER_DEF;
#define ENCODER_NUM (sizeof(ENCODER_GPIOS))

static uint8_t gray_decode(uint8_t num);

void encoder_init() {
    for (int i = 0; i < ENCODER_NUM; i++) {
        uint8_t gpio = ENCODER_GPIOS[i];
        gpio_init(gpio);
        gpio_set_function(gpio, GPIO_FUNC_SIO);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);
    }
}

uint8_t encoder_read() {
    uint8_t value = 0;

    for (int i = ENCODER_NUM - 1; i >= 0; i--) {
        value <<= 1;
        value |= !gpio_get(ENCODER_GPIOS[i]);
    }

    return gray_decode(value);
}

static uint8_t gray_decode(uint8_t num) {
    uint8_t mask = num;
    while (mask) {
        mask >>= 1;
        num ^= mask;
    }
    return num;
}
