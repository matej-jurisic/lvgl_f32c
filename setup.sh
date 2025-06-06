git clone https://github.com/lvgl/lvgl --branch v9.3.0
patch -p1 < patch/lv_example_style_19_logging_fix.patch
make