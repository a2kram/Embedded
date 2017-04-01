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


//
// Initialize debug library
//

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


//
// Output floating point number
//

void Debug_PrintFloat(float value, int places) 
{
  int digit;
  int tenscount = 0;
  int i;
  float tens = 0.1;
  float tempfloat = value;
  float d = 0.5;

  // Calculate rounding term d: 0.5 / pow(10, places)  
  if(value < 0)
  {
    d *= -1.0;
  }
    
  // Divide by ten for each decimal place
  for(i = 0; i < places; ++i)
  {
    d /= 10.0;
  }

  // This small addition, combined with truncation will round our values properly 
  tempfloat +=  d;

  // First get value tens to be the large power of ten less than value
  // Tenscount isn't necessary but it would be useful if you wanted to know after this how many chars the number will take

  if(value < 0)
  {
    tempfloat *= -1.0;
  }
    
  while((tens * 10.0) <= tempfloat) 
  {
    tens *= 10.0;
    tenscount += 1;
  }
  
  // Write out the negative if needed
  if(value < 0)
  {
    Debug_Print("-");
  }
    
  if(tenscount == 0)
  {
    Debug_Print("%i", 0);
  }

  for(i = 0; i < tenscount; ++i)
  {
    digit = (int) (tempfloat/tens);
    Debug_Print("%i", digit);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }

  // If no places after decimal, stop now and return
  if(places <= 0)
  {
    return;
  }

  // Otherwise, write the point and continue on
  Debug_Print(".");  

  // Write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
  for(i = 0; i < places; ++i) 
  {
    tempfloat *= 10.0; 
    digit = (int) tempfloat;
    Debug_Print("%i", digit);

    // once written, subtract off that digit
    tempfloat = tempfloat - (float) digit; 
  }
}