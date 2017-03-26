SRC_DIR := 
INC_DIR := ../../../
OBJ_DIR := obj/
DRV_DIR := ../
OUT_DIR := $(DRV_DIR)out/

LIB_NAME := libHAL_$(BOARD)
LIB_OUT := $(OUT_DIR)$(LIB_NAME).a
LIB_SRCS_C := $(wildcard $(SRC_DIR)*.c)
LIB_SRCS_CXX := $(wildcard $(SRC_DIR)*.cpp)
LIB_OBJS := $(addprefix $(OBJ_DIR), $(LIB_SRCS_C:%.c=%.o) \
			$(LIB_SRCS_CXX:%.cpp=%.o))
LIB_DEPLIB := DRIVERS_ARDUINO \
			  DRIVERS_MPU9250

ifeq ($(BOARD),ARDUINO)
	CC := avr-gcc
	CXX := avr-g++
	MCU := -mmcu=atmega328p
	CPU_SPEED := -DF_CPU=16000000UL
	AR_TOOL := avr-ar
else
    $(error Please specify board name, options: BOARD=ARDUINO)
endif

CFLAGS := -Os -Wall -ffunction-sections -fdata-sections $(MCU) $(CPU_SPEED) -MMD 
LFLAGS := -L $(OUT_DIR) 

#define these as special targets, meaning run even if a "all" file exists and is update to date
.PHONY: $(LIB_DEPLIB) clean

# rule to make target, depend on objects 
# (make will run rule to make objects since dependency)
default: DRIVERS_HAL

DRIVERS_HAL: $(OUT_DIR) $(OBJ_DIR) $(LIB_DEPLIB) $(LIB_OBJS)
	cp $(OBJ_DIR)* $(OUT_DIR)
	$(AR_TOOL) rcs $(LIB_OUT) $(OUT_DIR)*.o
	rm $(OUT_DIR)*.o

#rule to clean library
clean:
	rm $(OBJ_DIR)*
	rm $(OUT_DIR)*

# rule to make objects
$(OBJ_DIR)%.o : %.c
	$(CC) $< $(CFLAGS) -I $(INC_DIR) $(LFLAGS) -c -o $@

$(OBJ_DIR)%.o : %.cpp
	$(CXX) $< $(CFLAGS) -I $(INC_DIR) $(LFLAGS) -c -o $@

$(LIB_DEPLIB):
    # split the target into directory and file path. This assumes that all
    # targets directory/filename are built with $(MAKE) -C directory filename
	$(MAKE) -C $(DRV_DIR) $@ BOARD=$(BOARD)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)