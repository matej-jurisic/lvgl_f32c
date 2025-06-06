// LVGL F32C framework headers
#include "perf_monitor.h"
#include "system_tick.h"
#include "lvgl_f32c.h"

#define LV_F32C_PERF_MON_LABEL_OFFSET_X 5
#define LV_F32C_PERF_MON_LABEL_OFFSET_Y 5
#define LV_F32C_PERF_MON_UPDATE_INTERVAL_MS 1000
#define LV_F32C_PERF_MON_LABEL_BUF_SIZE 128

static uint32_t s_frame_count = 0;
static uint32_t s_last_time_between_flushes = 0;
static uint32_t s_last_flush_time = 0;
static uint32_t s_time_until_first_flush = 0;

static uint32_t s_last_perf_mon_update_time = 0;
static lv_obj_t *s_perf_mon_label_timing = NULL;
static lv_obj_t *s_perf_mon_label_memory = NULL;

static lv_mem_monitor_t mon;
static lv_style_t s_perf_mon_label_style;

void lv_f32c_perf_monitor_init(void)
{
    uint32_t current_time = lv_f32c_get_elapsed_ms();
    lv_obj_t *parent = lv_layer_sys();

    lv_style_init(&s_perf_mon_label_style);
    lv_style_set_text_font(&s_perf_mon_label_style, &lv_font_montserrat_10);

    // Timing monitor label setup
    s_perf_mon_label_timing = lv_label_create(parent);
    lv_obj_align(s_perf_mon_label_timing, LV_ALIGN_TOP_LEFT, LV_F32C_PERF_MON_LABEL_OFFSET_X, LV_F32C_PERF_MON_LABEL_OFFSET_Y);
    lv_label_set_text(s_perf_mon_label_timing, "");
    lv_obj_add_style(s_perf_mon_label_timing, &s_perf_mon_label_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Memory monitor label setup
    s_perf_mon_label_memory = lv_label_create(parent);
    lv_obj_align(s_perf_mon_label_memory, LV_ALIGN_BOTTOM_LEFT, LV_F32C_PERF_MON_LABEL_OFFSET_X, -LV_F32C_PERF_MON_LABEL_OFFSET_Y);
    lv_label_set_text(s_perf_mon_label_memory, "");
    lv_obj_add_style(s_perf_mon_label_memory, &s_perf_mon_label_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Initialize performance monitor state
    s_last_perf_mon_update_time = current_time;
    s_frame_count = 0;
    s_last_flush_time = current_time;
    s_time_until_first_flush = 0;
}

void lv_f32c_perf_monitor_flush_update(lv_display_t *display)
{
    if (lv_display_flush_is_last(display))
    {
        uint32_t current_time = lv_f32c_get_elapsed_ms();
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
    uint32_t current_time = lv_f32c_get_elapsed_ms();
    char buf_timing[LV_F32C_PERF_MON_LABEL_BUF_SIZE];
    char buf_memory[LV_F32C_PERF_MON_LABEL_BUF_SIZE];

    s_frame_count++;

    if (current_time - s_last_perf_mon_update_time >= LV_F32C_PERF_MON_UPDATE_INTERVAL_MS)
    {
        const float actual_elapsed_seconds = (float)(current_time - s_last_perf_mon_update_time) / 1000.0f;
        const int fps = (actual_elapsed_seconds > 0) ? (int)((float)s_frame_count / actual_elapsed_seconds) : 0;

        snprintf(buf_timing, sizeof(buf_timing), "FPS: %d\nTIME BETWEEN FLUSHES: %dms\nFIRST FLUSH: %dms", fps, s_last_time_between_flushes, s_time_until_first_flush);
        lv_label_set_text(s_perf_mon_label_timing, buf_timing);

        lv_mem_monitor(&mon);
        snprintf(buf_memory, sizeof(buf_memory),
                 "MEMORY USED: %u bytes\nMEMORY FREE: %u bytes\nMEMORY FRAGMENTATION: %u%%",
                 mon.total_size - mon.free_size, mon.free_size, mon.frag_pct);
        lv_label_set_text(s_perf_mon_label_memory, buf_memory);

        s_frame_count = 0;
        s_last_perf_mon_update_time = current_time;
    }
}