#ifndef LVGL_F32C_IMAGE
#define LVGL_F32C_IMAGE

#include "lvgl.h"

int lv_f32c_init_sd_card();
void lv_f32c_init_image_desc(lv_image_dsc_t *img_dsc, int width, int height);
void lv_f32c_free_image_dsc(lv_image_dsc_t *img_dsc);
lv_obj_t *lv_f32c_load_image(lv_obj_t *screen, lv_image_dsc_t *image_desc, const char *filename);

#endif // LVGL_F32C_IMAGE