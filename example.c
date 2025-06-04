#include <dev/io.h>
#include <dev/fb.h>

#include "include/lvgl_f32c.h"
#include "examples/lv_examples.h"

#define IMAGE_WIDTH 407
#define IMAGE_HEIGHT 246

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();

    // Initialize the SD card
    if (lv_f32c_init_sd_card() != 0)
    {
        return -1;
    }

    // Create a display and register it
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Get the active screen
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_make(0x00, 0x70, 0x70), LV_STATE_DEFAULT);

    lv_indev_t *indev_keypad = lv_f32c_register_inputs();
    if (indev_keypad == NULL)
    {
        return -1;
    }

    lv_group_t *g = lv_group_create();
    lv_indev_set_group(indev_keypad, g);

    // Create widgets
    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Input Test");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    static lv_img_dsc_t img_dsc;
    lv_f32c_init_image_dsc(&img_dsc, IMAGE_WIDTH, IMAGE_HEIGHT);
    lv_obj_t *img = lv_f32c_load_image(screen, &img_dsc, "image.bin");
    lv_obj_set_size(img, 200, 125);
    lv_obj_align(img, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_group_add_obj(g, img);

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
        lv_f32c_timer_handler();
        msleep(5);
    }

    return 0;
}