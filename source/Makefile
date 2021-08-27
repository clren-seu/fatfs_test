ifdef BUILDDIR
override BUILDDIR := $(BUILDDIR)/
$(shell mkdir -p $(BUILDDIR))
endif

# 输出程序名
TARGET := fatfs_test
TARGET := $(addprefix $(BUILDDIR), $(TARGET))

# 编译相关工具
BUILD_PREFIX :=
CC   := $(BUILD_PREFIX)gcc
SIZE := $(BUILD_PREFIX)size
NM   := $(BUILD_PREFIX)nm

export CC

SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=$(BUILDDIR)%.o)
DEP := $(SRC:%.c=$(BUILDDIR)%.d)

CFLAGS := -I.

.PHONY: all
all: $(TARGET)

# rules
-include $(DEP)
.SUFFIXES:

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

$(BUILDDIR)%.o: %.c
	$(CC) -c -MMD $(CFLAGS) $< -o $@

$(BUILDDIR)%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -fr $(TARGET) $(OBJ) $(DEP)