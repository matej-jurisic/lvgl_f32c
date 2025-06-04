// Device and hardware-specific headers
#include <dev/io.h>
#include <dev/fb.h>

// LVGL F32C framework headers
#include "system_tick.h"
#include "perf_monitor.h"
#include "lvgl_f32c.h"

#define LV_F32C_FB_BUFFER_SIZE ((size_t)fb_hdisp * fb_vdisp * fb_bpp / 8)

static void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    if (lv_display_flush_is_last(display))
    {
        OUTW(IO_DV_DMA_BASE, px_map);

#if LV_F32C_SHOW_PERFORMANCE_MONITOR
        lv_f32c_perf_monitor_flush_update(display);
#endif
    }
    lv_display_flush_ready(display);
}

void lv_f32c_init(void)
{
    init_system_tick();

    fb_set_mode(FB_MODE_720p60, FB_BPP_16 | FB_DOUBLEPIX);

    lv_init();

    lv_tick_set_cb(get_elapsed_ms);

#if LV_F32C_ENABLE_LOGS
    LV_F32C_LOG_INFO("Initialized with framebuffer size %dx%d (mode %s), bpp %d, buffer size %zu bytes.",
                     fb_hdisp, fb_vdisp,
                     (fb_bpp & FB_DOUBLEPIX) ? "double pixel" : "normal",
                     fb_bpp,
                     LV_F32C_FB_BUFFER_SIZE);
#endif
}

int lv_f32c_register_display(lv_display_t *display)
{
    if (display == NULL)
    {
        LV_F32C_LOG_ERR("Provided NULL display pointer to lv_f32c_register_display.");
        return -1;
    }

    fb_set_drawable(1);

    if (fb[0] == NULL || fb[1] == NULL)
    {
        LV_F32C_LOG_ERR("Framebuffer pointers (fb[0]/fb[1]) are NULL.");
        return -1;
    }

    lv_display_set_buffers(display, fb[0], fb[1], LV_F32C_FB_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_DIRECT);
    lv_display_set_flush_cb(display, flush_cb);

    // Initialize the performance monitor
#if LV_F32C_SHOW_PERFORMANCE_MONITOR
    lv_f32c_perf_monitor_init();
#endif

    return 0;
}

void lv_f32c_timer_handler(void)
{
    lv_timer_handler();

#if LV_F32C_SHOW_PERFORMANCE_MONITOR
    lv_f32c_perf_monitor_refresh();
#endif
}