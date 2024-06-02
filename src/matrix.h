#ifndef KB_MATRIX_H_
#define KB_MATRIX_H_

#include <stdint.h>

/* Polling Rate. */
#define POLLING_RATE_IN_MS (1)

/* Debounce algorithm configuration. */
#define DEBOUNCE_CHECKS (5)

/* Keyboard matrix configuration. */
#define COL0_PIN (4)
#define COL1_PIN (5)

#define ROW0_PIN (2)
#define ROW1_PIN (3)
#define ROW_MASK ((uint32_t)0x0000000c)
#define NORMALIZE_ROW(x) (((x)&ROW_MASK) >> 2)

#define COLUMN_COUNT  (2)
#define ROW_COUNT     (2)

extern uint32_t const COLUMNS[COLUMN_COUNT];
extern uint32_t const ROWS[ROW_COUNT];

#endif /* KB_MATRIX_H_ */

