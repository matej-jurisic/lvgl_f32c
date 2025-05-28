#ifndef LVGL_F32C_INPUT
#define LVGL_F32C_INPUT

#include "lvgl.h"

bool ulx3s_button_pressed(uint32_t *key);
void keypad_read(lv_indev_t *indev, lv_indev_data_t *data);

#endif // LVGL_F32C_INPUT