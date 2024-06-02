#include "usb/usb.h"
#include "hardware/gpio.h"
#include "log.h"
#include "matrix.h"
#include "tusb.h"
#include "usb/hid.h"
#include "utils/timer.h"

static void
scan_tick(uint32_t *row_state);
static void
usb_hid_tick(uint32_t const *row_state);
static void
debounce_row(
    uint32_t(*row_state)[],
    uint32_t *row_debounced,
    uint32_t *row_raw,
    uint8_t *index);

static uint32_t rows_debounced[COLUMN_COUNT] = {};
static uint32_t rows_state[COLUMN_COUNT][DEBOUNCE_CHECKS] = {};
static uint8_t state_index[COLUMN_COUNT] = {};

int
usb_init()
{
    LOGD("\n=== Initializing USB ...\n");
    tusb_init();

    LOGD("\n=== USB Initialized! ===\n");
    return 0;
}

void
usb_tick()
{
    /* This needs to be called first. */
    tud_task();

    /* Poll every 1ms */
    static uint32_t start_ms = 0;
    if (time_since_boot_ms() - start_ms < POLLING_RATE_IN_MS) {
        /* interval not exceeded. */
        return;
    }

    start_ms += POLLING_RATE_IN_MS;

    uint32_t row_state[COLUMN_COUNT] = { 0 };

    scan_tick(row_state);
    usb_hid_tick(row_state);

    /* for (int i = 0; i < COLUMN_COUNT; ++i) { */
    /*     LOGD("[%d]: %08lx  ", i, row_state[i]); */
    /* } */
    /* LOGD(" | "); */
    /* for (int i = 0; i < COLUMN_COUNT; ++i) { */
    /*     LOGD("[%d]: %08lx  ", i, rows_debounced[i]); */
    /* } */
    /* LOGD("\n"); */
}

static void
scan_tick(uint32_t *row_state)
{
    for (int col = 0; col < COLUMN_COUNT; ++col) {
        gpio_put(COLUMNS[col], 1);

        /* We need to sleep here to account for the propagation delay. */
        sleep_us(10);

        uint32_t row = NORMALIZE_ROW(gpio_get_all());
        debounce_row(
            &rows_state[col], &rows_debounced[col], &row,
            &state_index[col]);
        row_state[col] = row;

        gpio_put(COLUMNS[col], 0);
    }
}

static void
usb_hid_tick(uint32_t const *row_state)
{
    int has_pressed_keys = 0;
    for (int col = 0; col < COLUMN_COUNT; ++col) {
        has_pressed_keys |= row_state[col];
    }

    /* Remote wakeup */
    if (tud_suspended() && has_pressed_keys) {
        /*
         * Wake up host if we are in suspend mode
         * and REMOTE_WAKEUP feature is enabled by host
         */
        tud_remote_wakeup();
    }
    else {
        /* Send the 1st of report chain, the rest will be sent by
         * tud_hid_report_complete_cb() */

        report_send_keypresses(rows_debounced);
    }
}

/**
 * Params:
 *  - row_state (inout)
 *  - row_debounced (out)
 *  - row_raw (in)
 *  - index (inout)
 */
static void
debounce_row(
    uint32_t(*row_state)[],
    uint32_t *row_debounced,
    uint32_t *row_raw,
    uint8_t *index)
{

    (*row_state)[*index] = *row_raw;
    ++(*index);

    uint32_t row = 0xFFFFFFFF;
    for (int i = 0; i < DEBOUNCE_CHECKS; ++i) {
        row = row & (*row_state)[i];
    }

    *row_debounced = row;

    if (*index >= DEBOUNCE_CHECKS) {
        *index = 0;
    }
}

