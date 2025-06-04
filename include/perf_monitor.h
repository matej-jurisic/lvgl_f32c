#ifndef LV_F32C_PERF_MONITOR_H
#define LV_F32C_PERF_MONITOR_H

// LVGL header
#include "lvgl.h"

/**
 * @brief Initializes the LVGL performance monitor display.
 */
void lv_f32c_perf_monitor_init(void);

/**
 * @brief Updates performance data after a display flush.
 * @param display Pointer to the `lv_display_t` object that was flushed.
 */
void lv_f32c_perf_monitor_flush_update(lv_display_t *display);

/**
 * @brief Refreshes the performance monitor's displayed metrics.
 */
void lv_f32c_perf_monitor_refresh(void);

#endif // LV_F32C_PERF_MONITOR_H