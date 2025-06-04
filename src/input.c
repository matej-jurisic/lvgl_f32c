// Device and hardware-specific headers
#include <dev/io.h>

// LVGL F32C framework headers
#include "lvgl_f32c.h"

static bool ulx3s_button_pressed(uint32_t *key)
{
    uint32_t btn_state;
    INB(btn_state, IO_PUSHBTN);

    if (btn_state & BTN_CENTER)
    {
        *key = LV_KEY_ENTER;
        return true;
    }
    if (btn_state & ROT_B)
    {
        *key = LV_KEY_ESC;
        return true;
    }
    if (btn_state & BTN_LEFT)
    {
        *key = LV_KEY_LEFT;
        return true;
    }
    if (btn_state & BTN_RIGHT)
    {
        *key = LV_KEY_RIGHT;
        return true;
    }
    if (btn_state & BTN_UP)
    {
        *key = LV_KEY_PREV;
        return true;
    }
    if (btn_state & BTN_DOWN)
    {
        *key = LV_KEY_NEXT;
        return true;
    }

    return false;
}

void keypad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    bool key_pressed = ulx3s_button_pressed(&data->key);
    if (key_pressed)
    {
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
        LVF32C_LOG_ERR("LVGL F32C: Failed to create LVGL input device.");
        return NULL;
    }

    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);

    return indev_keypad;
}