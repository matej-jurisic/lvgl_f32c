PROG = example
LIBS = -lulx3s -lm

LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk
CFLAGS += -I$(LVGL_DIR)

CFILES = src/lvgl_f32c.c src/input.c example.c $(CSRCS)

include ${POST_MK}