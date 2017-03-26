/*
	Generic GPIO Driver
*/

#include <stdbool.h>
#include <stdint.h>
#include "common/facility.h"
#include "common/statuscodes.h"
#include "common/board.h"
#include "HAL_GPIO.h"

#ifdef SOC_ARDUINO
#include "../arduino/arduino_SOC.h"
#endif

//
//	Setup GPIO pin as input and enable/disable internal pullups
//	

uint16_t SOC_Initialize()
{
	#ifdef SOC_ARDUINO
		return Arduino_SOC_Initialize();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}