#include "lever.h"
#include "hardware/adc.h"
#include "board_defs.h"

void lever_init() {
    adc_init();
    adc_gpio_init(LEVER_GPIO);
    adc_select_input(LEVER_ADC);
}

uint8_t lever_read() {
    return adc_read() >> 4;
}
