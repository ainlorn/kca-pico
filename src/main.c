#include <stdint.h>
#include <stdbool.h>

#include "bsp/board.h"
#include "pico/multicore.h"
#include "pico/stdio.h"
#include "pico/bootrom.h"

#include "tusb.h"
#include "usb_descriptors.h"

#include "btn.h"
#include "encoder.h"
#include "lever.h"

struct {
    uint8_t buttons;
    uint8_t joy[2];
} hid_report;

void report_usb_hid()
{
    if (tud_hid_ready()) {
        tud_hid_n_report(0x00, REPORT_ID_JOYSTICK, &hid_report, sizeof(hid_report));
    }
}

void check_reboot_bootsel() {
    uint8_t btns = btn_read();
    if (((btns >> BTN_TEST) & 1) && ((btns >> BTN_SERVICE) & 1)) {
        reset_usb_boot(0, 1);
    }
}

static void loop() {
    absolute_time_t next_frame = {0};

    while (true)
    {
        tud_task();

        uint8_t btns = btn_read();
        uint8_t encoder = encoder_read();
        uint8_t lever = lever_read();

        hid_report.buttons = btns;
        hid_report.joy[0] = encoder;
        hid_report.joy[1] = lever;

        report_usb_hid();

        sleep_until(next_frame);
        next_frame = make_timeout_time_us(1000);
    }
}

static void init() {
    board_init();
    tusb_init();
    stdio_init_all();

    btn_init();
    encoder_init();
    lever_init();

    check_reboot_bootsel();
}

void main() {
    init();
    loop();
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen)
{
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize)
{
}
