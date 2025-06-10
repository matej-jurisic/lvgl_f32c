#include <dev/fb.h>

#include "lvgl_f32c.h"

#define IMAGE_WIDTH 407
#define IMAGE_HEIGHT 246

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();

    // Initialize the SD card
    lv_f32c_init_sd_card();

    // Create a display and register it
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Load and display the image
    static lv_image_dsc_t image_dsc;
    lv_f32c_init_image_dsc(&image_dsc, IMAGE_WIDTH, IMAGE_HEIGHT);
    lv_obj_t *image = lv_f32c_load_image(lv_screen_active(), &image_dsc, "image.bin");
    lv_obj_center(image);

    while (1)
    {
        lv_f32c_timer_handler();
        lv_f32c_msleep(3);
    }

    lv_f32c_free_image_dsc(&image_dsc);

    return 0;
}