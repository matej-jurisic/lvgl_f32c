#include "lvgl_f32c.h"
#include <dev/io.h>
#include <dev/fb.h>

int main(void)
{
    fb_set_mode(FB_MODE_720p60, FB_BPP_8);

    lv_f32c_init();

    lv_display_t *display = lv_f32c_display_create(fb_hdisp, fb_vdisp);

    lv_f32c_register_display(display);

    return 0;
}