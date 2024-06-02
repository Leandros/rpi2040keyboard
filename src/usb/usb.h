#ifndef KB_USB_H_
#define KB_USB_H_

/**
 * Initialize the USB subsystem.
 *
 * The USB subsystem is based on tinyusb.
 */
int
usb_init();

/**
 * Call this in your main loop.
 */
void
usb_tick();

#endif /* KB_USB_H_ */

