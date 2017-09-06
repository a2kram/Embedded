/*
	Arduino I2C Driver
*/

#include <stdint.h>
#include <stdbool.h>
#include "facility.h"
#include "statuscodes.h"
#include "SOC/Arduino.h"
#include "SOC/Crc16.h"
#include "arduino_SOC.h"

static bool sInitialized = false;

//
//	Initialize SOC
//	

uint16_t Arduino_SOC_Initialize()
{
	if(sInitialized)
	{
		return STATUS_SUCCESS;
	}

	init();

	sInitialized = true;

	return STATUS_SUCCESS;
}


//
// Compute 16-bit CRC
//

uint16_t Arduino_SOC_crc16(uint8_t* buf, uint8_t start, uint16_t len)
{
	Crc16 crc;

	// Input checking
	if(buf == NULL || len <= 0 || start >= len)
	{
		return E_DRV_SOC_INVALID_INPUT;
	}

	crc.clearCrc();

	return crc.XModemCrc(buf, start, len);
}