#include "include/lvgl_f32c.h"
#include "lvgl.h"
#include <dev/io.h>
#include <dev/fb.h>
#include <stdio.h>
#include "examples/lv_examples.h"

int main(void)
{
    // Initialize framebuffer
    fb_set_mode(FB_MODE_1080i60, FB_BPP_16 | FB_DOUBLEPIX);

    // Initialize LVGL
    lv_f32c_init();

    // Create a display and register it
    lv_display_t *display = lv_f32c_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Get the active screen
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_make(0x00, 0x00, 0x88), LV_STATE_DEFAULT);

    lv_example_arc_2();

    while (1)
    {
        lv_timer_handler();
    }

    return 0;
}
