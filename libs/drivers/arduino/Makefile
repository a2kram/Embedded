SRC_DIR := 
SOC_DIR := SOC/
INC_DIR := ../../../common
CMN_DIR := ../../../../common
OBJ_DIR := obj/
DRV_DIR := ../
LIB_DIR := ../../libraries
OUT_DIR := $(DRV_DIR)out/

DRV_SRCS_C := $(wildcard $(SRC_DIR)*.c $(SOC_DIR)*.c)
DRV_SRCS_CXX := $(wildcard $(SRC_DIR)*.cpp $(SOC_DIR)*.cpp)
DRV_OBJS := $(addprefix $(OBJ_DIR), $(DRV_SRCS_C:%.c=%.o) \
			$(DRV_SRCS_CXX:%.cpp=%.o))

CC := avr-gcc
CXX := avr-g++
MCU := -mmcu=atmega328p
CPU_SPEED := -DF_CPU=16000000UL
CFLAGS := -Os -Wall -ffunction-sections -fdata-sections $(MCU) $(CPU_SPEED) -MMD 

#define these as special targets, meaning run even if a "all" file exists and is update to date
.PHONY: clean

# rule to make target, depend on objects 
# (make will run rule to make objects since dependency)
default: DRIVERS_ARDUINO

DRIVERS_ARDUINO: $(OUT_DIR) $(OBJ_DIR) $(DRV_OBJS)
	cp $(OBJ_DIR)* $(OUT_DIR)

#rule to clean output
clean:
	rm $(OBJ_DIR)*

# rule to make objects
$(OBJ_DIR)%.o : %.c
	$(CC) $< -c $(CFLAGS) -I $(INC_DIR) -I $(CMN_DIR) -I $(LIB_DIR) -I $(DRV_DIR) -o $(OBJ_DIR)$(notdir $@)

$(OBJ_DIR)%.o : %.cpp
	$(CXX) $< -c $(CFLAGS) -I $(INC_DIR) -I $(CMN_DIR) -I $(LIB_DIR) -I $(DRV_DIR) -o $(OBJ_DIR)$(notdir $@)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)