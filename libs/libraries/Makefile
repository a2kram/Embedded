OUT_DIR := out/
DBG_DIR := Debug/
HCI_DIR := HCI/
LIB_NAME := libLIBS_$(BOARD)
LIB_OUT := $(OUT_DIR)$(LIB_NAME).a
LIB_DEPLIB := LIB_DEBUG LIB_HCI

ifeq ($(BOARD),ARDUINO)
	AR_TOOL := avr-ar
else
    $(error Please specify board name, options: BOARD=ARDUINO)
endif

#define these as special targets, meaning run even if a "all" file exists and is update to date
.PHONY: $(LIB_DEPLIB) LIBRARIES clean all

all: clean default

default: $(OUT_DIR) LIBRARIES

LIBRARIES: $(LIB_DEPLIB)
	$(AR_TOOL) rcs $(LIB_OUT) $(OUT_DIR)*.o
	rm $(OUT_DIR)*.o

LIB_DEBUG:
	$(MAKE) -C $(DBG_DIR) $@ BOARD=$(BOARD)

LIB_HCI:
	$(MAKE) -C $(HCI_DIR) $@ BOARD=$(BOARD)

clean:
	$(shell rm $(OUT_DIR)* 2> /dev/null)