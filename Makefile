PROG = lvgl_f32c
LIBS = -lulx3s -lm -lc

LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk

CFILES = lvgl_f32c.c ffssi2.c example.c $(CSRCS)

CFLAGS += -D__F32C__
LDFLAGS += -G 0

include ${POST_MK}