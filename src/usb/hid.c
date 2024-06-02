#include "class/hid/hid.h"
#include "class/hid/hid_device.h"
#include "log.h"
#include "matrix.h"
#include <stdint.h>
#include <string.h>

static int keymap[COLUMN_COUNT][ROW_COUNT] = {
    { HID_KEY_1, HID_KEY_2 },
    { HID_KEY_3, HID_KEY_4 },
};

static uint8_t keycode_prev[6] = { 0 };

void
report_send_keypresses(uint32_t const *rows)
{
    if (!tud_hid_ready()) {
        return;
    }

    /* Our keycodes adhere to the boot protocol. */
    uint8_t keycode[6] = { 0 };
    uint8_t index = 0;

    for (int icol = 0; icol < COLUMN_COUNT; ++icol) {
        int row = rows[icol];
        for (int irow = 0; irow < ROW_COUNT; ++irow) {
            int pressed = row & (0x1 << irow);
            if (index >= 6)
                break;

            if (pressed) {
                keycode[index++] = keymap[icol][irow];
            }
        }
    }

    /* If the keycodes compare completely equal, we don't resend them. */
    if (memcmp(keycode, keycode_prev, 6) == 0) {
        return;
    }

    /* The keycodes don't compare equal, save them and send a new report. */
    memcpy(keycode_prev, keycode, 6);

    tud_hid_keyboard_report(1, 0, keycode);


    /* LOGD("SEND KEYPRESSES: "); */
    /* for (int i = 0; i < 6; ++i) { */
    /*     LOGD("%02x ", keycode[i]); */
    /* } */
    /* LOGD("\n"); */
}


/*
 * Invoked when sent REPORT successfully to host
 * Application can use this to send the next report
 * Note: For composite reports, report[0] is report ID
 */
void
tud_hid_report_complete_cb(
    uint8_t instance,
    uint8_t const *report,
    uint16_t len)
{
    (void)instance;
    (void)report;
    (void)len;

    /* LOGD("!! REPORT (complete)\n"); */

    /* Unused! */
    /* uint8_t next_report_id = report[0] + 1; */
}


/*
 * Invoked when received GET_REPORT control request
 * Application must fill buffer report's content and return its length.
 * Return zero will cause the stack to STALL request
 */
uint16_t
tud_hid_get_report_cb(
    uint8_t itf,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t *buffer,
    uint16_t reqlen)
{
    /* TODO not Implemented */
    (void) itf;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    LOGD("!! GET_REPORT\n");

    return 0;
}

/*
 * Invoked when received SET_REPORT control request or
 * received data on OUT endpoint ( Report ID = 0, Type = 0 )
 */
void
tud_hid_set_report_cb(
    uint8_t itf,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t const *buffer,
    uint16_t bufsize)
{
    (void) itf;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;

    LOGD("!! SET_REPORT\n");
}

