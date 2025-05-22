#include "include/lvgl_f32c.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <dev/fb.h>
#include <dev/io.h>
#include <stdio.h>

#define FB_BUFFER_SIZE ((size_t)fb_hdisp * fb_vdisp * fb_bpp / 8)

static struct timespec start;

uint32_t get_elapsed_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    long seconds = now.tv_sec - start.tv_sec;
    long nanoseconds = now.tv_nsec - start.tv_nsec;
    return (uint32_t)(seconds * 1000 + nanoseconds / 1000000);
}

void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    OUTW(IO_DV_DMA_BASE, px_map);
    lv_display_flush_ready(display);
}

void lv_f32c_init()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
    lv_init();
    lv_tick_set_cb(get_elapsed_ms);
}

void lv_f32c_register_display(lv_display_t *display)
{
    fb_set_drawable(1);
    lv_display_set_buffers(display, fb[0], fb[1], FB_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_FULL);
    lv_display_set_flush_cb(display, flush_cb);
}

lv_display_t *lv_f32c_display_create(int32_t hor_res, int32_t ver_res)
{
    return lv_display_create(hor_res, ver_res);
}