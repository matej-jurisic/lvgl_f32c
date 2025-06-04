// LVGL F32C framework headers
#include "perf_monitor.h"
#include "system_tick.h"
#include "lvgl_f32c.h"

#define LV_F32C_PERF_MON_LABEL_OFFSET_X 5
#define LV_F32C_PERF_MON_LABEL_OFFSET_Y 5
#define LV_F32C_PERF_MON_UPDATE_INTERVAL_MS 1000
#define LV_F32C_PERF_MON_LABEL_BUF_SIZE 80

static uint32_t s_frame_count = 0;
static uint32_t s_last_time_between_flushes = 0;
static uint32_t s_last_flush_time = 0;
static uint32_t s_time_until_first_flush = 0;

static uint32_t s_last_perf_mon_update_time = 0;
static lv_obj_t *s_perf_mon_label = NULL;

void lv_f32c_perf_monitor_init(void)
{
    // Initialize the performance monitor label
    s_perf_mon_label = lv_label_create(lv_screen_active());
    lv_obj_align(s_perf_mon_label, LV_ALIGN_TOP_LEFT, LV_F32C_PERF_MON_LABEL_OFFSET_X, LV_F32C_PERF_MON_LABEL_OFFSET_Y);
    lv_obj_move_foreground(s_perf_mon_label);
    lv_label_set_text(s_perf_mon_label, "FPS: --");

    s_last_perf_mon_update_time = get_elapsed_ms();
    s_frame_count = 0;
    s_last_flush_time = get_elapsed_ms(); // Initialize to current time to avoid large initial 'LAST FLUSH' value
    s_time_until_first_flush = 0;
}

void lv_f32c_perf_monitor_flush_update(lv_display_t *display)
{
    if (lv_display_flush_is_last(display))
    {
        uint32_t current_time = get_elapsed_ms();
        s_last_time_between_flushes = current_time - s_last_flush_time;
        s_last_flush_time = current_time;

        if (s_time_until_first_flush == 0)
        {
            s_time_until_first_flush = current_time;
        }
    }
}

void lv_f32c_perf_monitor_refresh(void)
{
    uint32_t current_time = get_elapsed_ms();
    char buf[LV_F32C_PERF_MON_LABEL_BUF_SIZE];

    s_frame_count++;

    if (current_time - s_last_perf_mon_update_time >= LV_F32C_PERF_MON_UPDATE_INTERVAL_MS)
    {
        const float actual_elapsed_seconds = (float)(current_time - s_last_perf_mon_update_time) / 1000.0f;
        const int fps = (actual_elapsed_seconds > 0) ? (int)((float)s_frame_count / actual_elapsed_seconds) : 0;

        snprintf(buf, sizeof(buf), "FPS: %d\nTIME BETWEEN FLUSHES: %dms\nFIRST FLUSH: %dms", fps, s_last_time_between_flushes, s_time_until_first_flush);
        lv_label_set_text(s_perf_mon_label, buf);

        s_frame_count = 0;
        s_last_perf_mon_update_time = current_time;
    }
}