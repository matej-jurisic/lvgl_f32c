// Standard library headers
#include <stdlib.h>

// Device and hardware-specific headers
#include <dev/io.h>
#include <fatfs/ff.h>
#include <fatfs/diskio.h>

// LVGL F32C framework headers
#include "lvgl_f32c.h"

static struct diskio_inst sd0_di;
static FATFS fs;

int lv_f32c_init_sd_card()
{
    diskio_attach_sdcard(&sd0_di, IO_SPI_SDCARD, 0);

    FRESULT fr;

    fr = f_mount(&fs, "", 1);
    if (fr != FR_OK)
    {
        LVF32C_LOG_ERR("Mount failed! Error: %d", fr);
        if (fr != FR_OK)
        {
            return 0;
        }
    }
#if LVF32C_ENABLE_LOGS
    LVF32C_LOG_INFO("SD card mounted successfully!");
#endif
    return 1;
}

void lv_f32c_init_image_desc(lv_image_dsc_t *img_desc, int width, int height)
{
    lv_color_t *pixel_buffer = malloc(width * height * sizeof(lv_color_t));
    img_desc->header.cf = LV_COLOR_FORMAT_RGB565;
    img_desc->header.w = width;
    img_desc->header.h = height;
    img_desc->data_size = width * height * (LV_COLOR_DEPTH / 8);
    img_desc->data = (const uint8_t *)pixel_buffer;
}

lv_obj_t *lv_f32c_load_image(lv_obj_t *screen, lv_image_dsc_t *image_desc, const char *filename)
{
    FIL fp;
    FRESULT fr;
    UINT br;
    lv_obj_t *img;

    const uint8_t *image_pixel_buffer = image_desc->data;

    image_desc->data = (const uint8_t *)image_pixel_buffer;

    fr = f_open(&fp, filename, FA_READ);
    if (fr != FR_OK)
    {
        LVF32C_LOG_ERR("Error opening %s.", filename);
        return NULL;
    }

    fr = f_read(&fp, (void *)image_pixel_buffer, image_desc->data_size, &br);
    if (fr != FR_OK)
    {
        LVF32C_LOG_ERR("f_read failed! FRESULT: %d", fr);
        f_close(&fp);
        return NULL;
    }

    if (br != image_desc->data_size)
    {
        LVF32C_LOG_WARNING("Incomplete read! Expected %u bytes, read %u bytes.",
                           image_desc->data_size, br);
    }

#if LVF32C_ENABLE_LOGS
    LVF32C_LOG_INFO("Image %s loaded successfully! Read %u bytes.", filename, br);
#endif

    f_close(&fp);

    img = lv_image_create(screen);
    lv_image_set_src(img, image_desc);

    return img;
}

void lv_f32c_free_image_dsc(lv_image_dsc_t *img_dsc)
{
    free((void *)img_dsc->data);
    img_dsc->data = NULL;
}