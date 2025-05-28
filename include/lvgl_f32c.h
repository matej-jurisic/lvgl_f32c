#ifndef LVGL_F32C_H
#define LVGL_F32C_H

#include <stdint.h>
#include <stdbool.h>

#include "lvgl.h"

int lv_f32c_init(void);
int lv_f32c_register_display(lv_display_t *display);
lv_indev_t *lv_f32c_register_inputs(void);
void lv_f32c_show_fps(lv_obj_t *screen, bool show);
void lv_f32c_timer_handler(void);
void msleep(uint32_t ms);

#endif // LVGL_F32C_H