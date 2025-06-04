#ifndef LVGL_F32C_H
#define LVGL_F32C_H

// Standard library headers
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// LVGL header
#include "lvgl.h"

// Enable or disable logging
// Set to 1 to enable logs, 0 to disable
#define LV_F32C_ENABLE_LOGS 1

// Use performance monitor to show FPS and time since last flush
#define LV_F32C_SHOW_PERFORMANCE_MONITOR 1

// Define which ulx3s buttons are mapped to which LVGL keys.
// Uncomment/comment the lines below to enable/disable specific buttons.
#define LV_F32C_BTN_ROT_B LV_KEY_ESC
#define LV_F32C_BTN_CENTER LV_KEY_ENTER
#define LV_F32C_BTN_UP LV_KEY_PREV
#define LV_F32C_BTN_DOWN LV_KEY_NEXT
#define LV_F32C_BTN_LEFT LV_KEY_LEFT
#define LV_F32C_BTN_RIGHT LV_KEY_RIGHT
// #define LV_F32C_BTN_ROT_A LV_KEY_ENTER

#define LV_F32C_LOG_ERR(fmt, ...) fprintf(stderr, "LVGL F32C (Error): " fmt "\n", ##__VA_ARGS__)
#define LV_F32C_LOG_INFO(fmt, ...) fprintf(stderr, "LVGL F32C (Info): " fmt "\n", ##__VA_ARGS__)
#define LV_F32C_LOG_WARNING(fmt, ...) fprintf(stderr, "LVGL F32C (Warning): " fmt "\n", ##__VA_ARGS__)

/**
 * @brief Initializes LVGL for f32c.
 */
void lv_f32c_init(void);

/**
 * @brief Registers a display.
 * @param display Pointer to the LVGL display object.
 * @return 0 on success, -1 on failure.
 */
int lv_f32c_register_display(lv_display_t *display);

/**
 * @brief Handles LVGL timer processing.
 */
void lv_f32c_timer_handler(void);

/**
 * @brief Delays execution for a specified number of milliseconds.
 * @param ms The delay duration in milliseconds.
 */
void msleep(uint32_t ms);

/**
 * @brief Registers input devices (currently only the keypad) with LVGL.
 * @return Pointer to the LVGL input device object.
 */
lv_indev_t *lv_f32c_register_inputs(void);

/**
 * @brief Initializes SD card functionality for LVGL F32C.
 * @return 0 on success, -1 on failure.
 */
int lv_f32c_init_sd_card();

/**
 * @brief Initializes an LVGL image descriptor with specified dimensions.
 * @param img_dsc Pointer to the (static) image descriptor to initialize.
 * @param width Width of the image.
 * @param height Height of the image.
 */
void lv_f32c_init_image_dsc(lv_image_dsc_t *img_dsc, int width, int height);

/**
 * @brief Frees resources associated with an LVGL image descriptor.
 * @param img_dsc Pointer to the image descriptor to free.
 */
void lv_f32c_free_image_dsc(lv_image_dsc_t *img_dsc);

/**
 * @brief Loads an image from a file onto an LVGL screen.
 * @param screen Pointer to the LVGL screen object.
 * @param image_dsc Pointer to the image descriptor.
 * @param filename Path to the image file.
 * @return Pointer to the created LVGL image object, or NULL on failure.
 */
lv_obj_t *lv_f32c_load_image(lv_obj_t *screen, lv_image_dsc_t *image_dsc, const char *filename);

#endif // LVGL_F32C_H