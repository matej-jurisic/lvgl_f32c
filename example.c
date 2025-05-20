#include "include/lvgl_f32c.h"
#include "lvgl.h"
#include <dev/io.h>
#include <dev/fb.h>
#include <stdio.h>

int main(void)
{
    // Initialize framebuffer
    fb_set_mode(FB_MODE_1080i60, FB_BPP_8);

    // Initialize LVGL
    lv_f32c_init();

    // Create a display and register it
    lv_display_t *display = lv_f32c_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Get the active screen
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_make(0x00, 0x00, 0x88), LV_STATE_DEFAULT);

    // Common style for text
    lv_style_t my_style;
    lv_style_init(&my_style);
    lv_style_set_text_font(&my_style, &lv_font_montserrat_32);
    lv_style_set_text_color(&my_style, lv_color_make(0xFF, 0xFF, 0xFF));

    // --- Title Label ---
    lv_obj_t *title_label = lv_label_create(screen);
    lv_label_set_text(title_label, "Hello lvgl_f32c!");
    lv_obj_add_style(title_label, &my_style, LV_STATE_DEFAULT);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 30);

    // --- Progress Bar ---
    lv_obj_t *bar = lv_bar_create(screen);
    lv_obj_set_size(bar, 800, 30);
    // Position progress bar below the title with 20px gap
    lv_obj_align_to(bar, title_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_bar_set_value(bar, 70, LV_ANIM_OFF);

    // --- Checkbox ---
    lv_obj_t *checkbox = lv_checkbox_create(screen);
    lv_checkbox_set_text(checkbox, "Enable Feature");
    lv_obj_add_style(checkbox, &my_style, LV_STATE_DEFAULT);
    // Align checkbox near left side below progress bar with some margin
    lv_obj_align_to(checkbox, bar, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 30);

    // --- Switch ---
    lv_obj_t *sw = lv_switch_create(screen);
    // Align switch near right side at same vertical level as checkbox
    lv_obj_align_to(sw, bar, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 30);

    // --- Button ---
    lv_obj_t *btn = lv_btn_create(screen);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -30); // Centered at bottom with margin
    lv_style_t btn_style;
    lv_style_init(&btn_style);
    lv_style_set_bg_color(&btn_style, lv_color_make(0x00, 0x66, 0x00));
    lv_obj_add_style(btn, &btn_style, LV_STATE_DEFAULT);
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_obj_add_style(btn_label, &my_style, LV_STATE_DEFAULT);
    lv_label_set_text(btn_label, "Click");

    while (1)
    {
        lv_timer_handler();
    }

    return 0;
}
