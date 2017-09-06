/*
	Generic I2C Driver
*/

#include <stdbool.h>
#include <stdint.h>
#include "facility.h"
#include "statuscodes.h"
#include "board.h"
#include "HAL_I2C.h"

#ifdef SOC_ARDUINO
#include "arduino/arduino_I2C.h"
#endif

//
//	Initialize I2C driver
//	

inline uint16_t I2C_Init()
{
	#ifdef SOC_ARDUINO
		return Arduino_I2C_Init();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Read from device using I2C
//

inline uint16_t I2C_Read(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, uint8_t* data)
{
	#ifdef SOC_ARDUINO
		return Arduino_I2C_Read(device_addr, reg_addr, count, data);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}

//
// Write to device using I2C
//

inline uint16_t I2C_Write(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, const uint8_t* data, bool end_tranmission)
{
	#ifdef SOC_ARDUINO
		return Arduino_I2C_Write(device_addr, reg_addr, count, data, end_tranmission);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}