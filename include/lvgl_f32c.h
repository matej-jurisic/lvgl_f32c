#ifndef LVGL_F32C_H
#define LVGL_F32C_H

#include "lvgl/lvgl.h"

void lv_f32c_init();
void lv_f32c_register_display(struct lv_display_t *display);
uint32_t get_elapsed_ms(void);
lv_display_t *lv_f32c_display_create(int32_t hor_res, int32_t ver_res);
lv_indev_t *lv_f32c_register_inputs();

#endif // LVGL_F32C_H