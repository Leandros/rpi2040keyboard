#include "setup.h"
#include "usb/usb.h"

/* Configuration: */
#define SWITCH_PIN 5

/* static void */
/* send_keyboard_report(uint32_t const btn_pressed); */

int
main()
{
    /* Initialization ... */
    if (init_board()) {
        return -1;
    }

    /* Main Loop */
    while (1) {
        usb_tick();
    }

    return 0;
}


/* /1* --- *1/ */
/* void led_blinking_task(void) */
/* { */
/*  static uint32_t start_ms = 0; */
/*  static bool led_state = false; */

/*  // blink is disabled */
/*  if (!blink_interval_ms) return; */

/*  // Blink every interval ms */
/*  if (to_ms_since_boot(get_absolute_time()) - start_ms < blink_interval_ms)
 * return; // not enough time */
/*  start_ms += blink_interval_ms; */

/*  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state); */
/*  led_state = 1 - led_state; // toggle */
/* } */

