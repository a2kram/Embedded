SRC_DIR := 
OBJ_DIR := obj/
LIB_DIR := ../
DRV_DIR := ../../drivers
OUT_DIR := $(LIB_DIR)out/
INC_DIR := ../../../common
CMN_DIR := ../../../../common

LIB_SRCS_C := $(wildcard $(SRC_DIR)*.c)
LIB_SRCS_CXX := $(wildcard $(SRC_DIR)*.cpp)
LIB_OBJS := $(addprefix $(OBJ_DIR), $(LIB_SRCS_C:%.c=%.o) \
			$(LIB_SRCS_CXX:%.cpp=%.o))

ifeq ($(BOARD),ARDUINO)
	CC := avr-gcc
	CXX := avr-g++
	MCU := -mmcu=atmega328p
	CPU_SPEED := -DF_CPU=16000000UL
else
    $(error Please specify board name, options: BOARD=ARDUINO)
endif

CFLAGS := -Os -Wall -ffunction-sections -fdata-sections $(MCU) $(CPU_SPEED) -MMD 

#define these as special targets, meaning run even if a "all" file exists and is update to date
.PHONY: clean

# rule to make target, depend on objects 
# (make will run rule to make objects since dependency)
default: LIB_HCI

LIB_HCI: $(OUT_DIR) $(OBJ_DIR) $(LIB_OBJS)
	cp $(OBJ_DIR)* $(OUT_DIR)

#rule to clean output
clean:
	rm $(OBJ_DIR)*

# rule to make objects
$(OBJ_DIR)%.o : %.c
	$(CC) $< $(CFLAGS) -I $(INC_DIR) -I $(CMN_DIR) -I $(LIB_DIR) -I $(DRV_DIR) -c -o $@

$(OBJ_DIR)%.o : %.cpp
	$(CXX) $< $(CFLAGS) -I $(INC_DIR) -I $(CMN_DIR) -I $(LIB_DIR) -I $(DRV_DIR) -c -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)