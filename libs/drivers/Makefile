OUT_DIR := out/
HAL_DIR := HAL/
ARD_DIR := arduino/
MPU_DIR := mpu9250/

ifneq ($(BOARD),ARDUINO)
    $(error Please specify board name, options: BOARD=ARDUINO)
endif

#define these as special targets, meaning run even if a "all" file exists and is update to date
.PHONY: DRIVERS_HAL DRIVERS_ARDUINO DRIVERS_MPU9250 clean all

all: clean default

default: $(OUT_DIR) DRIVERS_MPU9250 DRIVERS_ARDUINO DRIVERS_HAL

DRIVERS_HAL:
	$(MAKE) -C $(HAL_DIR) $@ BOARD=$(BOARD)

DRIVERS_ARDUINO:
	$(MAKE) -C $(ARD_DIR) $@

DRIVERS_MPU9250:
	$(MAKE) -C $(MPU_DIR) $@ BOARD=$(BOARD)

clean:
	$(shell rm $(OUT_DIR)* 2> /dev/null)