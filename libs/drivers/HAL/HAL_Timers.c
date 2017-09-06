/*
	Generic Timers Driver
*/

#include <stdint.h>
#include "facility.h"
#include "statuscodes.h"
#include "board.h"
#include "HAL_Timers.h"

#ifdef SOC_ARDUINO
#include "arduino/SOC/Arduino.h"
#endif


//
//	Initialize Timers driver
//	

inline uint16_t Timers_Init()
{
	return STATUS_UNIMPLEMENTED;
}


//
//	Delay by ms milliseconds
//

inline uint16_t Timers_DelayMs(uint64_t ms)
{
	#ifdef SOC_ARDUINO
		delay(ms);

		return STATUS_SUCCESS;
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Return time since program started running in milliseconds
//

inline uint32_t Timers_Micros()
{
	#ifdef SOC_ARDUINO
		return micros();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}