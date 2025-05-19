#include "lvgl_f32c.h"
#include <time.h>
#include <string.h>
#include <dev/fb.h>
#include <dev/io.h>

static struct timespec start;

long elapsed_ms(struct timespec *start, struct timespec *current)
{
    clock_gettime(CLOCK_MONOTONIC, current);
    long seconds = current->tv_sec - start->tv_sec;
    long nanoseconds = current->tv_nsec - start->tv_nsec;
    return seconds * 1000 + nanoseconds / 1000000;
}

uint32_t custom_tick_cb(void)
{
    struct timespec current;
    return (uint32_t)elapsed_ms(&start, &current);
}

void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    int width = area->x2 - area->x1 + 1;
    int height = area->y2 - area->y1 + 1;

    for (int y = 0; y < height; y++)
    {
        int fb_index = (area->y1 + y) * fb_hdisp + area->x1;
        int px_index = y * width;
        memcpy(&fb_active[fb_index], &px_map[px_index], width);
    }

    lv_display_flush_ready(display);
}

void lv_f32c_init()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
    lv_init();
    lv_tick_set_cb(custom_tick_cb);
}

void lv_f32c_register_display(lv_display_t *display)
{
    lv_display_set_buffers(display, fb_active, &fb_visible, fb_hdisp * fb_vdisp, LV_DISPLAY_RENDER_MODE_DIRECT);
    lv_display_set_flush_cb(display, flush_cb);
}

lv_display_t *lv_f32c_display_create(int32_t hor_res, int32_t ver_res)
{
    return lv_display_create(hor_res, ver_res);
}