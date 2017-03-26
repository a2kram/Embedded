SRC_DIR := 
INC_DIR := ../../common
OBJ_DIR := obj/
BIN_DIR := bin/
DRV_DIR := ../../libs/drivers
LIB_DIR := ../../libs/libraries
OUT_DRV_DIR := $(DRV_DIR)/out/
OUT_LIB_DIR := $(LIB_DIR)/out/
LIBS_LIB := LIBS_$(BOARD)
HAL_LIB := HAL_$(BOARD)

APP_HEX := $(BIN_DIR)IMU_Passthrough_$(BOARD).hex
APP_ELF := $(BIN_DIR)IMU_Passthrough_$(BOARD).elf
APP_SRCS_C := $(wildcard $(SRC_DIR)*.c)
APP_SRCS_CXX := $(wildcard $(SRC_DIR)*.cpp)
APP_OBJS := $(addprefix $(OBJ_DIR), $(APP_SRCS_C:%.c=%.o) \
			$(APP_SRCS_CXX:%.cpp=%.o))
APP_DRV_DEPLIB := DRIVERS_HAL 
APP_LIB_DEPLIB := LIBRARIES

ifeq ($(BOARD),ARDUINO)
	CC := avr-gcc
	CXX := avr-g++
	MCU := -mmcu=atmega328p
	CPU_SPEED := -DF_CPU=16000000UL
	OBJ_CPY := avr-objcopy
	UPD_TOOL := avrdude
	PORT := /dev/ttyACM0
else
    $(error Please specify board name, options: BOARD=ARDUINO)
endif

CFLAGS := $(MCU) $(CPU_SPEED) -w -Wl,--gc-sections -ffunction-sections -fdata-sections
LFLAGS := -L $(OUT_DRV_DIR) -L $(OUT_LIB_DIR) -l$(LIBS_LIB) -l$(HAL_LIB)
IFLAGS := -I $(INC_DIR) -I $(DRV_DIR) -I $(LIB_DIR)

#define these as special targets, meaning run even if a "all" file exists and is update to date
.PHONY: $(APP_DEPLIB) clean upload

## RULES ##

# rule to make target, depend on objects 
# (make will run rule to make objects since dependency)
default: $(APP_HEX)

$(APP_HEX): $(APP_ELF)
	$(OBJ_CPY) -O ihex $< $@

$(APP_ELF): $(OBJ_DIR) $(BIN_DIR) $(APP_DRV_DEPLIB) $(APP_LIB_DEPLIB) $(APP_OBJS)
	$(CXX) $(CFLAGS) $(IFLAGS) -o $@ $(APP_OBJS) $(LFLAGS) 
	$(shell rm *.o 2> /dev/null)

upload: $(APP_HEX)
	$(UPD_TOOL) -V -F -p m328p -c arduino -b 115200 -Uflash:w:$(APP_HEX) -P$(PORT)

#rule to clean library
clean:
	rm $(OBJ_DIR)*
	rm $(APP_HEX)
	rm $(APP_ELF)


## DEPENDENCIES ##

# rule to make objects
$(OBJ_DIR)%.o : %.c
	$(CC) $< $(CFLAGS) $(IFLAGS) -c -o $@

$(OBJ_DIR)%.o : %.cpp
	$(CXX) $< $(CFLAGS) $(IFLAGS) -c -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# rule to make HAL library
$(APP_DRV_DEPLIB):
	$(MAKE) -C $(DRV_DIR) $@ BOARD=$(BOARD)

# rule to make libraries
$(APP_LIB_DEPLIB):
	$(MAKE) -C $(LIB_DIR) $@ BOARD=$(BOARD)