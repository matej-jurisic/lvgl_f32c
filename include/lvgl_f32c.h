#ifndef LVGL_F32C_H
#define LVGL_F32C_H

#include <stdint.h>
#include <stdbool.h>

#include "lvgl.h"

#define LVF32C_ENABLE_LOGS 1
#define LVF32C_LOG_ERR(fmt, ...) fprintf(stderr, "LVGL F32C (Error): " fmt "\n", ##__VA_ARGS__)
#define LVF32C_LOG_INFO(fmt, ...) fprintf(stderr, "LVGL F32C (Info): " fmt "\n", ##__VA_ARGS__)
#define LVF32C_LOG_WARNING(fmt, ...) fprintf(stderr, "LVGL F32C (Warning): " fmt "\n", ##__VA_ARGS__)

int lv_f32c_init(void);
int lv_f32c_register_display(lv_display_t *display);
lv_indev_t *lv_f32c_register_inputs(void);
void lv_f32c_show_fps(lv_obj_t *screen, bool show);
void lv_f32c_timer_handler(void);
void msleep(uint32_t ms);

#endif // LVGL_F32C_H