PROG = lvgl_f32c
LIBS = -lulx3s -lm -lc

LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk
CFLAGS += -I$(LVGL_DIR)

CFILES = src/lvgl_f32c.c src/ffssi2.c example.c $(CSRCS)

CFLAGS += -D__F32C__ -Iinclude

include ${POST_MK}