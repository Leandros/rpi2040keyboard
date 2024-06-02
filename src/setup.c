#include "setup.h"
#include "log.h"
#include "matrix.h"
#include "pico/cyw43_arch.h"
#include "pico/stdio.h"
#include "pico/stdio_uart.h"
#include "usb/usb.h"

int
init_board()
{
	LOGD("\n== Initializing Board ...\n");
	stdio_init_all();
	stdio_uart_init();

	/* Initialization required for accessing the LED */
	LOGD("Initializing Wi-Fi System ...\n");
	if (cyw43_arch_init()) {
		LOGE("!!! Wi-Fi init failed");
		return -1;
	}

	/* Initialize GPIOs. */
	LOGD("Initializing GPIOs ...\n");
	gpio_init(COL0_PIN);
	gpio_set_dir(COL0_PIN, GPIO_OUT);
	gpio_pull_down(COL0_PIN);

	gpio_init(COL1_PIN);
	gpio_set_dir(COL1_PIN, GPIO_OUT);
	gpio_pull_down(COL1_PIN);

	gpio_init(ROW0_PIN);
	gpio_set_dir(ROW0_PIN, GPIO_IN);
	gpio_pull_down(ROW0_PIN);

	gpio_init(ROW1_PIN);
	gpio_set_dir(ROW1_PIN, GPIO_IN);
	gpio_pull_down(ROW1_PIN);

	/* Initialize USB. */
	if (usb_init()) {
		LOGE("!!! USB init failed!");
	    return -1;
    }

	LOGD("\n=== Board Initialized! ===\n");
	return 0;
}
