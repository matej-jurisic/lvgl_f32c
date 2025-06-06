// Device and hardware-specific headers
#include <dev/io.h>

// LVGL F32C framework headers
#include "lvgl_f32c.h"

static bool ulx3s_button_pressed(uint32_t *key)
{
    uint32_t btn_state;
    INB(btn_state, IO_PUSHBTN);

#ifdef LV_F32C_BTN_CENTER
    if (btn_state & BTN_CENTER)
    {
        *key = LV_F32C_BTN_CENTER;
        return true;
    }
#endif

#ifdef LV_F32C_BTN_ROT_A
    if (btn_state & ROT_A)
    {
        *key = LV_F32C_BTN_ROT_A;
        return true;
    }
#endif

#ifdef LV_F32C_BTN_ROT_B
    if (btn_state & ROT_B)
    {
        *key = LV_F32C_BTN_ROT_B;
        return true;
    }
#endif

#ifdef LV_F32C_BTN_LEFT
    if (btn_state & BTN_LEFT)
    {
        *key = LV_F32C_BTN_LEFT;
        return true;
    }
#endif

#ifdef LV_F32C_BTN_RIGHT
    if (btn_state & BTN_RIGHT)
    {
        *key = LV_F32C_BTN_RIGHT;
        return true;
    }
#endif

#ifdef LV_F32C_BTN_UP
    if (btn_state & BTN_UP)
    {
        *key = LV_F32C_BTN_UP;
        return true;
    }
#endif

#ifdef LV_F32C_BTN_DOWN
    if (btn_state & BTN_DOWN)
    {
        *key = LV_F32C_BTN_DOWN;
        return true;
    }
#endif

    return false;
}

void keypad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    bool key_pressed = ulx3s_button_pressed(&data->key);
    if (key_pressed)
    {
        LV_F32C_LOG_INFO("LVGL F32C: Key pressed: %u", data->key);
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

lv_indev_t *lv_f32c_register_inputs(void)
{
    lv_indev_t *indev_keypad = lv_indev_create();
    if (indev_keypad == NULL)
    {
        LV_F32C_LOG_ERR("LVGL F32C: Failed to create LVGL input device.");
        return NULL;
    }

    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);

    return indev_keypad;
}