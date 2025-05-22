#include "include/input.h"
#include <stdio.h>
#include <dev/io.h>

bool ulx3s_button_pressed(uint32_t *key)
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