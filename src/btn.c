#include "btn.h"
#include "hardware/gpio.h"
#include "board_defs.h"

static const uint8_t BUTTON_GPIOS[] = BUTTON_DEF;
#define BUTTON_NUM (sizeof(BUTTON_GPIOS))

void btn_init()
{
    for (int i = 0; i < BUTTON_NUM; i++) {
        uint8_t gpio = BUTTON_GPIOS[i];
        gpio_init(gpio);
        gpio_set_function(gpio, GPIO_FUNC_SIO);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);
    }
}

uint8_t btn_num()
{
    return BUTTON_NUM;
}

uint8_t btn_gpio(uint8_t id)
{
    return BUTTON_GPIOS[id];
}

uint8_t btn_read()
{
    uint8_t buttons = 0;

    for (int i = BUTTON_NUM - 1; i >= 0; i--) {
        buttons <<= 1;
        buttons |= !gpio_get(BUTTON_GPIOS[i]);
    }

    return buttons;
}
