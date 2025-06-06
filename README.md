# LVGL for F32C + ULX3S

This repository contains an adaptation of the [LVGL](https://lvgl.io/) graphics library for the [ULX3S FPGA](https://radiona.org/ulx3s/) using the [F32C softcore CPU](https://github.com/f32c/f32c).

## Features
- LVGL GUI output via HDMI on ULX3S
- Performance monitoring (timing and memory)
- Image loading from SD card
- Script to convert `.png` images to `.bin` RGB565 format
- Input controls using onboard ULX3S buttons
- Non-blocking `tick` and `sleep` functions
- Double buffering

## Requirements
- ULX3S board
- F32C setup with MIPS toolchain
- `ujprog` for flashing binaries to the board
- SD card (optional, required for image loading)

## Minimal example
```C
#include <dev/fb.h>

#include "include/lvgl_f32c.h"
#include "examples/lv_examples.h"

int main(void)
{
    // Initialize LVGL for f32c
    lv_f32c_init();

    // Create and register a LVGL display
    lv_display_t *display = lv_display_create(fb_hdisp, fb_vdisp);
    lv_f32c_register_display(display);

    // Run a built-in LVGL example
    lv_example_arc_2();

    while (1)
    {
        // Periodically call lv_f32c_timer_handler()
        lv_f32c_timer_handler();
        lv_f32c_msleep(5);
    }

    return 0;
}
```

## How to Use (with example)
- Clone the repository
- Make setup.sh executable (if needed) and run it to clone LVGL v9.2.2 and build the project
- Flash the generated example.bin file using ```ujprog -t -e example.bin```
- Connect the HDMI output to a display
