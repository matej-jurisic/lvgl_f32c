// Device and hardware-specific headers
#include <dev/io.h>
#include <dev/fb.h>

// LVGL F32C framework headers
#include "system_tick.h"
#include "lvgl_f32c.h"

#define LV_F32C_FB_BUFFER_SIZE ((size_t)fb_hdisp * fb_vdisp * fb_bpp / 8)

#define LV_F32C_FPS_LABEL_OFFSET_X 5
#define LV_F32C_FPS_LABEL_OFFSET_Y 5
#define LV_F32C_FPS_UPDATE_INTERVAL_MS 1000
#define LV_F32C_FPS_LABEL_BUF_SIZE 32

static int s_frame_count = 0;
static uint32_t s_last_fps_update_time;
static bool s_show_fps_enabled = false;
static lv_obj_t *s_fps_label = NULL;

static void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    if (lv_display_flush_is_last(display))
    {
        OUTW(IO_DV_DMA_BASE, px_map);
    }
    lv_display_flush_ready(display);
}

static void refresh_fps(void)
{
    uint32_t current_time = get_elapsed_ms();
    char buf[LV_F32C_FPS_LABEL_BUF_SIZE];

    s_frame_count++;

    if (current_time - s_last_fps_update_time >= LV_F32C_FPS_UPDATE_INTERVAL_MS)
    {
        const float actual_elapsed_seconds = (float)(current_time - s_last_fps_update_time) / 1000.0f;
        const int fps = (actual_elapsed_seconds > 0) ? (int)((float)s_frame_count / actual_elapsed_seconds) : 0;

        snprintf(buf, sizeof(buf), "FPS: %d", fps);
        lv_label_set_text(s_fps_label, buf);

        s_frame_count = 0;
        s_last_fps_update_time = current_time;
    }
}

void lv_f32c_init(void)
{
    lv_init();

    init_system_tick();

    fb_set_mode(FB_MODE_720p60, FB_BPP_16 | FB_DOUBLEPIX);

    lv_tick_set_cb(get_elapsed_ms);

#if LV_F32C_ENABLE_LOGS
    LV_F32C_LOG_INFO("LVGL F32C: Initialized with framebuffer size %dx%d (mode %s), bpp %d, buffer size %zu bytes.",
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
        LV_F32C_LOG_ERR("LVGL F32C: Provided NULL display pointer to lv_f32c_register_display.");
        return 0;
    }

    fb_set_drawable(1);

    if (fb[0] == NULL || fb[1] == NULL)
    {
        LV_F32C_LOG_ERR("LVGL F32C: Framebuffer pointers (fb[0]/fb[1]) are NULL.");
        return 0;
    }

    lv_display_set_buffers(display, fb[0], fb[1], LV_F32C_FB_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_DIRECT);
    lv_display_set_flush_cb(display, flush_cb);

    return 1;
}

void lv_f32c_show_fps(lv_obj_t *screen, bool visible)
{
    if (screen == NULL)
    {
        LV_F32C_LOG_ERR("LVGL F32C: Cannot show FPS on a NULL screen object.");
        return;
    }

    if (s_fps_label == NULL)
    {
        s_fps_label = lv_label_create(screen);
        lv_obj_align(s_fps_label, LV_ALIGN_TOP_LEFT, LV_F32C_FPS_LABEL_OFFSET_X, LV_F32C_FPS_LABEL_OFFSET_Y);
        lv_obj_move_foreground(s_fps_label);
    }

    if (visible)
    {
        lv_label_set_text(s_fps_label, "FPS: --");
        lv_obj_clear_flag(s_fps_label, LV_OBJ_FLAG_HIDDEN);
        s_last_fps_update_time = get_elapsed_ms();
        s_frame_count = 0;
    }
    else
    {
        lv_obj_add_flag(s_fps_label, LV_OBJ_FLAG_HIDDEN);
    }
    s_show_fps_enabled = visible;
}

void lv_f32c_timer_handler(void)
{
    lv_timer_handler();

    if (s_show_fps_enabled)
    {
        refresh_fps();
    }
}