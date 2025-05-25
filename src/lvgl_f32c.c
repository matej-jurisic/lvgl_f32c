#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <dev/io.h>
#include <dev/fb.h>

#include "include/lvgl_f32c.h"
#include "include/input.h"

#define FB_BUFFER_SIZE ((size_t)fb_hdisp * fb_vdisp * fb_bpp / 8)

static struct timespec start;
static int frame_count = 0;
static uint32_t last_fps_update_time;
static bool show_fps = false;
static lv_obj_t *fps_label;

static uint32_t get_elapsed_ms()
{
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint32_t)((now.tv_sec - start.tv_sec) * 1000 + (now.tv_nsec - start.tv_nsec) / 1000000);
}

void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    if (lv_display_flush_is_last(display))
    {
        OUTW(IO_DV_DMA_BASE, px_map);
    }
    lv_display_flush_ready(display);
}

void lv_f32c_init()
{
    lv_init();
    fb_set_mode(FB_MODE_1080i60, FB_BPP_16 | FB_DOUBLEPIX);
    clock_gettime(CLOCK_MONOTONIC, &start);
    lv_tick_set_cb(get_elapsed_ms);
}

void lv_f32c_register_display(lv_display_t *display)
{
    fb_set_drawable(1);
    lv_display_set_buffers(display, fb[0], fb[1], FB_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_DIRECT);
    lv_display_set_flush_cb(display, flush_cb);
}

lv_indev_t *lv_f32c_register_inputs()
{
    lv_indev_t *indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);
    return indev_keypad;
}

void lv_f32c_show_fps(lv_obj_t *screen, bool en)
{
    if (!fps_label)
    {
        fps_label = lv_label_create(screen);
        lv_obj_align(fps_label, LV_ALIGN_TOP_LEFT, 5, 5);
        lv_obj_move_foreground(fps_label);
    }

    if (en)
    {
        lv_label_set_text(fps_label, "FPS: --");
        lv_obj_clear_flag(fps_label, LV_OBJ_FLAG_HIDDEN);
        last_fps_update_time = get_elapsed_ms();
        frame_count = 0;
    }
    else
    {
        lv_obj_add_flag(fps_label, LV_OBJ_FLAG_HIDDEN);
    }
    show_fps = en;
}

static void refresh_fps()
{
    frame_count++;
    uint32_t current_time = get_elapsed_ms();
    if (current_time - last_fps_update_time >= 1000)
    {
        float actual_elapsed_seconds = (float)(current_time - last_fps_update_time) / 1000.0f;
        int fps = (int)((float)frame_count / actual_elapsed_seconds);

        char buf[32];
        snprintf(buf, sizeof(buf), "FPS: %d", fps);
        lv_label_set_text(fps_label, buf);

        frame_count = 0;
        last_fps_update_time = current_time;
    }
}

void lv_f32c_timer_handler()
{
    lv_timer_handler();

    if (show_fps)
    {
        refresh_fps();
    }
}