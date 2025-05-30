PROG = example
LIBS = -lulx3s -lm

LVGL_DIR_NAME ?= lvgl
LVGL_ROOT_DIR ?= ${shell pwd}

include $(LVGL_ROOT_DIR)/$(LVGL_DIR_NAME)/lvgl.mk

APP_SRCS := $(wildcard src/*.c)

CFILES := example.c $(APP_SRCS) $(CSRCS)

CFLAGS += -Isrc
CFLAGS += -Iinclude
CFLAGS += -I$(LVGL_ROOT_DIR)/$(LVGL_DIR_NAME)

include ${POST_MK}