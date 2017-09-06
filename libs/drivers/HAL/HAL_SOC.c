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
#include "arduino/arduino_SOC.h"
#endif

//
//	Setup GPIO pin as input and enable/disable internal pullups
//	

inline uint16_t SOC_Initialize()
{
	#ifdef SOC_ARDUINO
		return Arduino_SOC_Initialize();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}

//
// Compute 16-bit CRC
//

inline uint16_t SOC_crc16(uint8_t* buf, uint8_t start, uint16_t len)
{
	#ifdef SOC_ARDUINO
		return Arduino_SOC_crc16(buf, start, len);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}