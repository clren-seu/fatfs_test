SRC_OBJS := $(SRC:%.c=%.o)

MODULE_INCLUDE := $(addprefix -I,$(MODULE_INCLUDE))

.PHONY: $(SUBDIRS)

OBJ_DIR := $(BUILD_DIR)$(subst $(TOP_DIR)/,,$(shell pwd))/

ifneq ($(SUBDIRS),)
LIB_MODS := $(addprefix $(OBJ_DIR),$(foreach n,$(SUBDIRS),$(n)/lib_$(n)_mod.o))
endif

MODULE := $(addprefix $(OBJ_DIR),$(patsubst %,lib_%_mod.o,$(shell basename $(shell pwd))))

$(shell mkdir -p $(OBJ_DIR))

ifneq ($(SRC_OBJS),)
SRC_OBJS := $(addprefix $(OBJ_DIR),$(SRC_OBJS))
endif

$(MODULE): $(SUBDIRS) $(SRC_OBJS)
	$(NO_ECHO)$(LD) -r $(SRC_OBJS) $(LIB_MODS) -o $@

$(SUBDIRS):
	$(NO_ECHO)make -C $@ $(MAKECMDGOALS)

$(OBJ_DIR)%.o:%.c
	$(NO_ECHO)$(CC) $(GLOBAL_INCLUDE) $(MODULE_INCLUDE) -c $< -o $@

clean: $(SUBDIRS)
	$(NO_ECHO)rm -fr $(SRC_OBJS) $(MODULE)
