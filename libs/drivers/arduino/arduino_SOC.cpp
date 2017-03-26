/*
	Arduino I2C Driver
*/

#include <stdint.h>
#include <stdbool.h>
#include "common/facility.h"
#include "common/statuscodes.h"
#include "SOC/Arduino.h"
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