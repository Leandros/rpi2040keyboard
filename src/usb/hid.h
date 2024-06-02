#ifndef KB_HID_H_
#define KB_HID_H_

#include <stdint.h>

/**
 * Sends a HID report for the key presses in the DWORD.
 */
void
report_send_keypresses(uint32_t const *rows);

#endif /* KB_HID_H_ */

