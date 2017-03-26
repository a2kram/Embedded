/*
	Arduino I2C Driver
*/

#include <stdint.h>
#include <stdbool.h>
#include "common/facility.h"
#include "common/statuscodes.h"
#include "SOC/Wire.h"
#include "../HAL/HAL_I2C.h"
#include "../HAL/HAL_Timers.h"
#include "arduino_I2C.h"


static bool sInitialized = false;

//
// I2C driver initialization
//

uint16_t Arduino_I2C_Init()
{
	if(sInitialized)
	{
		return STATUS_SUCCESS;
	}

	// Initiate Wire library and join bus as master
	Wire.begin();

	sInitialized = true;

	return STATUS_SUCCESS;
}


//
// Read from device using I2C as master
//

uint16_t Arduino_I2C_Read(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, uint8_t* data)
{
	uint32_t start;
	uint16_t status;	

	// Input checking
	if(data == NULL || count == 0)
	{
		return E_DRV_I2C_INVALID_INPUT;
	}

	// If I2C driver is not initialized, call initialization function
	if(!sInitialized)
	{
		STATUS_CHECKED_CALL(Arduino_I2C_Init());
	}

	// Being transmission to I2C slave device
	Wire.beginTransmission(device_addr);
	Wire.write(reg_addr);

	// End transmission by sending STOP message
	status = Wire.endTransmission((uint8_t)true);

	// Check transmission status
	switch (status)
	{
		case 1:
			return E_DRV_I2C_DATA_TOO_LONG;
		case 2:
			return E_DRV_I2C_NACK_ON_ADDR;
		case 3:
			return E_DRV_I2C_NACK_ON_DATA;
	}


	// Request data from device, send STOP message after request
	Wire.requestFrom(device_addr, count, (uint8_t)true);

	for(uint8_t i = 0; i < count; ++i)
	{
		// Check if data is available
		if(Wire.available())
		{
			// Read in byte
			data[i] = Wire.read();
		}
		else
		{
			// Wait till timeout or data available
			start = Timers_Micros();

			while(((Timers_Micros() - start) < I2C_TIMEOUT) && !Wire.available());
			
			// Check if data is available
			if(Wire.available())
			{
				// Read in byte
				data[i] = Wire.read();
			}
			else
			{
				return E_DRV_I2C_TIMEOUT;
			}	
		}
	}

	return STATUS_SUCCESS;
}


//
// Write to device using I2C as master
//

uint16_t Arduino_I2C_Write(const uint8_t device_addr, const uint8_t reg_addr, const uint8_t count, const uint8_t* data, bool end_transmission)
{
	uint16_t status;

	// Input checking
	if(data == NULL || count == 0)
	{
		return E_DRV_I2C_INVALID_INPUT;
	}

	// If I2C driver is not initialized, call initialization function
	if(!sInitialized)
	{
		STATUS_CHECKED_CALL(Arduino_I2C_Init());
	}

	// Being transmission to I2C slave device
	Wire.beginTransmission(device_addr);
	Wire.write(reg_addr);
	Wire.write(data, count);

	// End transmission
	status = Wire.endTransmission((uint8_t)end_transmission);

	// Check transmission status
	switch (status)
	{
		case 1:
			return E_DRV_I2C_DATA_TOO_LONG;
		case 2:
			return E_DRV_I2C_NACK_ON_ADDR;
		case 3:
			return E_DRV_I2C_NACK_ON_DATA;
	}

	return STATUS_SUCCESS;
}