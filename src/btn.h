#pragma once

#include <stdint.h>

enum : uint8_t {BTN_FIRE, BTN_TEST, BTN_SERVICE, BTN_COIN};

void btn_init();
uint8_t btn_num();
uint8_t btn_gpio(uint8_t id);
uint8_t btn_read();
