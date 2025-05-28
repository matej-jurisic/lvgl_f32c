#include <stdio.h>
#include <time.h>

#include <dev/io.h>
#include <dev/fb.h>

#include "lvgl.h"
#include "include/lvgl_f32c.h"
#include "examples/lv_examples.h"

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();

    // Create a display and register it
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Get the active screen
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_make(0x00, 0x70, 0x70), LV_STATE_DEFAULT);

    lv_f32c_show_fps(screen, true);

    lv_example_arc_2();

    while (1)
    {
        lv_f32c_timer_handler();
        msleep(5);
    }

    return 0;
}