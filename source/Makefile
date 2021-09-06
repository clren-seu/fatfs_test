TOP_DIR := $(shell pwd)

# 配置输出文件位置
BUILD_DIR := $(TOP_DIR)/out/
# 配置目标
TARGET := fatfs
# 编译的目录名
SUBDIRS := test fatfs_src easylogger
# 全局包含的头文件
GLOBAL_INCLUDE := $(TOP_DIR)/easylogger/inc
# gdb
CFLAGS := -g

CC := gcc
LD := ld

NO_ECHO := @

ifeq ($(BUILD_DIR),)
BUILD_DIR := $(TOP_DIR)/
endif
LIB_MODS := $(foreach n,$(SUBDIRS),$(BUILD_DIR)$(n)/lib_$(n)_mod.o)
TARGET := $(BUILD_DIR)$(TARGET)
GLOBAL_INCLUDE := $(addprefix -I,$(GLOBAL_INCLUDE))

export NO_ECHO GLOBAL_INCLUDE TOP_DIR BUILD_DIR CC LD CFLAGS

.PHONY: all $(SUBDIRS) clean
all: $(SUBDIRS)
	$(NO_ECHO)mkdir -p $(dir $(TARGET))
	$(NO_ECHO)$(CC) -o $(TARGET) $(LIB_MODS)

$(SUBDIRS):
	$(NO_ECHO)make -C $@ $(MAKECMDGOALS)

clean: $(SUBDIRS)
	$(NO_ECHO)rm -fr $(TARGET)
