#include "lvgl_f32c.h"
#include "lvgl.h"
#include <dev/io.h>
#include <dev/fb.h>

int main(void)
{
    fb_set_mode(FB_MODE_720p60, FB_BPP_8);

    lv_f32c_init();

    lv_display_t *display = lv_f32c_display_create(fb_hdisp, fb_vdisp);

    lv_f32c_register_display(display);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello, LVGL!");
    lv_obj_center(label);

    while (1)
    {
        lv_timer_handler();
    }

    return 0;
}