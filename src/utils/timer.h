#ifndef KB_TIMER_H_
#define KB_TIMER_H_

#include "pico/time.h"
#include <stdint.h>

/**
 * Returns the milliseconds since boot.
 */
inline static uint32_t
time_since_boot_ms()
{
    return to_ms_since_boot(get_absolute_time());
}

#endif /* KB_TIMER_H_ */

