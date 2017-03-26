/*
	Arduino I2C Driver
*/

#include <stdint.h>
#include <stdbool.h>
#include "common/facility.h"
#include "common/statuscodes.h"
#include "SOC/Arduino.h"
#include "../HAL/HAL_GPIO.h"
#include "../HAL/HAL_Timers.h"
#include "arduino_GPIO.h"

static uint8_t sPinReserved [NUM_GPIO_PINS]= {0};

//
//	Setup GPIO pin as input and enable/disable internal pullups
//	

uint16_t Arduino_GPIO_SetupInput(const uint16_t pinnumber, bool pullup)
{
	uint8_t mode = INPUT;

	if(pullup)
	{
		mode = INPUT_PULLUP;
	}

	if(pinnumber < 0 || pinnumber > NUM_GPIO_PINS)
	{
		return E_DRV_GPIO_PIN_INVALID_PIN;	
	}
	
	pinMode(pinnumber, mode);

	return STATUS_SUCCESS;
}


//
//	Setup GPIO pin as output, initialize it as state
//	

uint16_t Arduino_GPIO_SetupOutput(const uint16_t pinnumber, pinstate state)
{
	if(pinnumber < 0 || pinnumber > NUM_GPIO_PINS)
	{
		return E_DRV_GPIO_PIN_INVALID_PIN;	
	}
	
	pinMode(pinnumber, OUTPUT);
	digitalWrite(pinnumber, state);

	return STATUS_SUCCESS;
}


//
//	Change GPIO state
//	

uint16_t Arduino_GPIO_DigitalWrite(const uint16_t pinnumber, pinstate state)
{
	if(pinnumber < 0 || pinnumber > NUM_GPIO_PINS)
	{
		return E_DRV_GPIO_PIN_INVALID_PIN;	
	}
	
	digitalWrite(pinnumber, state);

	return STATUS_SUCCESS;
}


//
//	Read from digital GPIO pin
//	

uint16_t Arduino_GPIO_DigitalRead(const uint16_t pinnumber, uint16_t* value)
{
	if(value == NULL)
	{
		return E_DRV_GPIO_INVALID_INPUT;
	}

	if(pinnumber < 0 || pinnumber > NUM_GPIO_PINS)
	{
		return E_DRV_GPIO_PIN_INVALID_PIN;	
	}

	*value = digitalRead(pinnumber);

	return STATUS_SUCCESS;
}


//
//	Read from analog GPIO pin
//	

uint16_t Arduino_GPIO_AnalogRead(const uint16_t pinnumber, uint16_t* value)
{
	if(value == NULL)
	{
		return E_DRV_GPIO_INVALID_INPUT;
	}

	if(pinnumber < 14 || pinnumber > 19)
	{
		return E_DRV_GPIO_PIN_INVALID_PIN;	
	}

	*value = analogRead(pinnumber);

	return STATUS_SUCCESS;
}