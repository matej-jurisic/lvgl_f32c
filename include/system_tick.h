#ifndef LV_F32C_SYSTEM_TICK_H
#define LV_F32C_SYSTEM_TICK_H

// Standard library headers
#include <stdint.h>
#include <stdbool.h>

#define SYSTEM_TICK_FREQ_HZ 1000

/**
 * @brief Initializes the system tick timer.
 */
void lv_f32c_init_system_tick(void);

/**
 * @brief Delays execution (non blocking) for a specified number of milliseconds.
 * @param ms The delay duration in milliseconds.
 */
void lv_f32c_msleep(uint32_t ms);

/**
 * @brief Gets the elapsed time in milliseconds since the system tick was initialized.
 * @return The elapsed time in milliseconds.
 */
uint32_t lv_f32c_get_elapsed_ms(void);

#endif // LV_F32C_SYSTEM_TICK_H