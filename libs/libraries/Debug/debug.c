/*
	Debug Functionality
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "facility.h"
#include "statuscodes.h"
#include "../../drivers/HAL/HAL_UART.h"
#include "debug.h"
 
static bool isInitialized = false;

void Debug_Initialize()
{
	if (isInitialized)
	{
		return;
	}

	UART_Setup(0, 115200, DBITS_8, SBITS_1, PARITY_NONE);

	isInitialized = true;
}

//
// Output formatted debug message using argument list
//

void Debug_Print(const char* format, ...)
{
	va_list varargs;
	char buffer[MAX_DEBUG_MSG_LEN];
	
	if(format == NULL)
	{
		return;
	}

	if(!isInitialized)
	{
		Debug_Initialize();
	}

	// Initialize variable argument list	
	va_start(varargs, format);

	// Write formatted data from variable argument list to sized buffer
	vsnprintf(buffer, MAX_DEBUG_MSG_LEN, format, varargs);

	// End using variable argument list
	va_end(varargs);

	UART_Print(DEBUG_UART_NUM, buffer);
}
