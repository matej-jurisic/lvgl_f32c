#ifndef SYSTEM_TICK_H
#define SYSTEM_TICK_H

// Standard library headers
#include <stdint.h>
#include <stdbool.h>

#define SYSTEM_TICK_FREQ_HZ 1000

/**
 * @brief Initializes the system tick timer.
 */
void init_system_tick(void);

/**
 * @brief Delays execution (non blocking) for a specified number of milliseconds.
 * @param ms The delay duration in milliseconds.
 */
void msleep(uint32_t ms);

/**
 * @brief Gets the elapsed time in milliseconds since the system tick was initialized.
 * @return The elapsed time in milliseconds.
 */
uint32_t get_elapsed_ms(void);

#endif // SYSTEM_TICK_H