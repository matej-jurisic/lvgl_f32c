#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dev/io.h>
#include <dev/fb.h>

#include "lvgl.h"
#include "include/lvgl_f32c.h"
#include "include/image.h"
#include "examples/lv_examples.h"

#define IMAGE_WIDTH 407
#define IMAGE_HEIGHT 246

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();
    // Sd card initialization
    if (!lv_f32c_init_sd_card())
    {
        return -1;
    }
    // Create a display and register it
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Get the active screen
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_make(0x00, 0x70, 0x70), LV_STATE_DEFAULT);

    lv_f32c_show_fps(screen, true);

    static lv_image_dsc_t image_desc;
    lv_f32c_init_image_desc(&image_desc, IMAGE_WIDTH, IMAGE_HEIGHT);
    lv_obj_t *image = lv_f32c_load_image(screen, &image_desc, "image.bin");
    lv_obj_center(image);

    while (1)
    {
        lv_f32c_timer_handler();
        msleep(5);
    }

    lv_f32c_free_image_dsc(&image_desc);
    return 0;
}