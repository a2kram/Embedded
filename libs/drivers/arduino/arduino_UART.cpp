/*
	Arduino I2C Driver
*/

#include <stdint.h>
#include <stdbool.h>
#include "facility.h"
#include "statuscodes.h"
#include "SOC/Arduino.h"
#include "HAL/HAL_UART.h"
#include "arduino_UART.h"


static bool sInitialized = false;

//
//	Setup UART communication
//	

uint16_t Arduino_UART_Setup(const uint8_t numport, const uint32_t speed, uart_databits dbits, uart_stopbits sbits, uart_parity parity)
{
	uint8_t config;

	switch(parity)
	{
		case(PARITY_NONE):
		{
			config = 0x0;
			break;
		}
		case(PARITY_EVEN):
		{
			config = 0x20;
			break;
		}
		case(PARITY_ODD):
		{
			config = 0x30;
			break;
		}
		default:
		{
			return E_DRV_UART_INVALID_PARITY;
		}
	}

	switch(sbits)
	{
		case(SBITS_1):
		{
			config += 0x00;
			break;
		}
		case(SBITS_2):
		{
			config += 0x08;
			break;
		}
		default:
		{
			return E_DRV_UART_INVALID_SBITS;
		}
	}

	switch(dbits)
	{
		case(DBITS_5):
		{
			config += 0x00;
			break;
		}
		case(DBITS_6):
		{
			config += 0x02;
			break;
		}
		case(DBITS_7):
		{
			config += 0x04;
			break;
		}
		case(DBITS_8):
		{
			config += 0x06;
			break;
		}
		default:
		{
			return E_DRV_UART_INVALID_DBITS;
		}
	}

	Serial.begin(speed, config);

	sInitialized = true;

	return STATUS_SUCCESS;
}


//
//	End UART communication
//	

uint16_t Arduino_UART_End(const uint8_t numport)
{
	if(sInitialized)
	{
		Serial.end();
	}

	return STATUS_SUCCESS;
}


//
//	Check for available data in UART buffer
//	

uint16_t Arduino_UART_Available(const uint8_t numport, uint8_t* numbytes)
{
	if(!sInitialized)
	{
		return E_DRV_UART_NOT_INITIALIZED;
	}

	if(numbytes == NULL)
	{
		return E_DRV_UART_INVALID_INPUT;
	}

	*numbytes = Serial.available();

	return STATUS_SUCCESS;
}


//
//	Read from UART buffer
//	

uint16_t Arduino_UART_Read(const uint8_t numport, uint8_t* data)
{
	if(!sInitialized)
	{
		return E_DRV_UART_NOT_INITIALIZED;
	}

	if(data == NULL)
	{
		return E_DRV_UART_INVALID_INPUT;
	}

	*data = Serial.read();

	return STATUS_SUCCESS;
}


//
//	Flush UART output buffer
//	

uint16_t Arduino_UART_Flush(const uint8_t numport)
{
	if(!sInitialized)
	{
		return E_DRV_UART_NOT_INITIALIZED;
	}

	Serial.flush();

	return STATUS_SUCCESS;
}


//
//	Write buffer to UART buffer
//	

uint16_t Arduino_UART_Print(const uint8_t numport, const char *buffer)
{
	if(!sInitialized)
	{
		return E_DRV_UART_NOT_INITIALIZED;
	}
	
	if(buffer == NULL)
	{
		return E_DRV_UART_INVALID_INPUT;
	}

	Serial.write(buffer);

	return STATUS_SUCCESS;
}


//
//	Send buffer to UART buffer
//	

uint16_t Arduino_UART_Send(const uint8_t numport, const uint8_t *buffer, int len)
{
	if(!sInitialized)
	{
		return E_DRV_UART_NOT_INITIALIZED;
	}
	
	if(buffer == NULL || len <= 0)
	{
		return E_DRV_UART_INVALID_INPUT;
	}

	Serial.write(buffer, len);

	return STATUS_SUCCESS;
}