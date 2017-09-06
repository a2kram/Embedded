/*
	Generic GPIO Driver
*/

#include <stdbool.h>
#include <stdint.h>
#include "facility.h"
#include "statuscodes.h"
#include "board.h"
#include "HAL_GPIO.h"

#ifdef SOC_ARDUINO
#include "arduino/arduino_GPIO.h"
#endif

//
//	Setup GPIO pin as input and enable/disable internal pullups
//	

inline uint16_t GPIO_SetupInput(const uint16_t pinnumber, bool pullup)
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

inline uint16_t GPIO_SetupOutput(const uint16_t pinnumber, pinstate state)
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

inline uint16_t GPIO_DigitalWrite(const uint16_t pinnumber, pinstate state)
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

inline uint16_t GPIO_DigitalRead(const uint16_t pinnumber, uint16_t* value)
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

inline uint16_t GPIO_AnalogRead(const uint16_t pinnumber, uint16_t* value)
{
	#ifdef SOC_ARDUINO
		return Arduino_GPIO_AnalogRead(pinnumber, value);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}