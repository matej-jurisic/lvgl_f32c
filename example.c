#include "include/lvgl_f32c.h"
#include "lvgl.h"
#include <dev/io.h>
#include <dev/fb.h>
#include <stdio.h>
#include <time.h>

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
    lv_obj_set_style_bg_color(screen, lv_color_make(0x00, 0x70, 0x00), LV_STATE_DEFAULT);

    // Register inputs
    lv_indev_t *input_keypad = lv_f32c_register_inputs();

    // Create a group for navigation
    lv_group_t *g = lv_group_create();
    lv_indev_set_group(input_keypad, g);

    // Create widgets
    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Input Test");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t *btn1 = lv_btn_create(screen);
    lv_obj_set_size(btn1, 200, 50);
    lv_obj_align(btn1, LV_ALIGN_TOP_MID, 0, 80);
    lv_obj_t *btn1_label = lv_label_create(btn1);
    lv_label_set_text(btn1_label, "Click Me!");
    lv_group_add_obj(g, btn1);

    lv_obj_t *sw = lv_switch_create(screen);
    lv_obj_align(sw, LV_ALIGN_TOP_MID, 0, 150);
    lv_group_add_obj(g, sw);

    lv_obj_t *slider = lv_slider_create(screen);
    lv_obj_set_size(slider, 200, 20);
    lv_obj_align(slider, LV_ALIGN_TOP_MID, 0, 200);
    lv_group_add_obj(g, slider);

    lv_obj_t *dropdown = lv_dropdown_create(screen);
    lv_dropdown_set_options(dropdown, "Option 1\nOption 2\nOption 3");
    lv_obj_align(dropdown, LV_ALIGN_TOP_MID, 0, 250);
    lv_group_add_obj(g, dropdown);

    lv_group_focus_obj(btn1);

    while (1)
    {
        lv_timer_handler();
    }

    return 0;
}