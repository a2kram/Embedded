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
#include "../arduino/arduino_GPIO.h"
#endif

//
//	Setup GPIO pin as input and enable/disable internal pullups
//	

uint16_t GPIO_SetupInput(const uint16_t pinnumber, bool pullup)
{
	#ifdef SOC_ARDUINO
		return Arduino_GPIO_SetupInput(pinnumber, pullup);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Setup GPIO pin as output, initialize it as state
//	

uint16_t GPIO_SetupOutput(const uint16_t pinnumber, pinstate state)
{
	#ifdef SOC_ARDUINO
		return Arduino_GPIO_SetupOutput(pinnumber, state);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Change GPIO state
//	

uint16_t GPIO_DigitalWrite(const uint16_t pinnumber, pinstate state)
{
	#ifdef SOC_ARDUINO
		return Arduino_GPIO_DigitalWrite(pinnumber, state);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Read from digital GPIO pin
//	

uint16_t GPIO_DigitalRead(const uint16_t pinnumber, uint16_t* value)
{
	#ifdef SOC_ARDUINO
		return Arduino_GPIO_DigitalRead(pinnumber, value);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Read from analog GPIO pin
//	

uint16_t GPIO_AnalogRead(const uint16_t pinnumber, uint16_t* value)
{
	#ifdef SOC_ARDUINO
		return Arduino_GPIO_AnalogRead(pinnumber, value);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}