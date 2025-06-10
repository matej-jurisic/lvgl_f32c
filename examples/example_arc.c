#include <dev/fb.h>

#include "lvgl_f32c.h"
#include "examples/lv_examples.h"

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();

    // Create a display and register it
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    lv_example_arc_2();

    while (1)
    {
        lv_f32c_timer_handler();
        lv_f32c_msleep(3);
    }

    return 0;
}