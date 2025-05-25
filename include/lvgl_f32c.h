#ifndef LVGL_F32C_H
#define LVGL_F32C_H

#include "lvgl/lvgl.h"

void lv_f32c_init();
void lv_f32c_register_display(lv_display_t *display);
lv_indev_t *lv_f32c_register_inputs();
void lv_f32c_show_fps(lv_obj_t *screen, bool en);
void lv_f32c_timer_handler();

#endif // LVGL_F32C_H