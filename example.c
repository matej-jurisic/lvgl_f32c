#include <dev/fb.h>

#include "include/lvgl_f32c.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"

#define IMAGE_WIDTH 407
#define IMAGE_HEIGHT 246

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();

    // Create a display and register it
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    lv_demo_widgets();

    while (1)
    {
        lv_f32c_timer_handler();
        lv_f32c_msleep(5);
    }

    return 0;
}