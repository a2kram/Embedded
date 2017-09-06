/*
	Generic UART Driver
*/

#include <stdbool.h>
#include <stdint.h>
#include "facility.h"
#include "statuscodes.h"
#include "board.h"
#include "HAL_UART.h"

#ifdef SOC_ARDUINO
#include "../arduino/arduino_UART.h"
#endif


//
//	Setup UART communication
//	

inline uint16_t UART_Setup(const uint8_t numport, const uint32_t speed, uart_databits dbits, uart_stopbits sbits, uart_parity parity)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_Setup(numport, speed, dbits, sbits, parity);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	End UART communication
//	

inline uint16_t UART_End(const uint8_t numport)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_End(numport);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Check for available data in UART buffer
//	

inline uint16_t UART_Available(const uint8_t numport, uint8_t* numbytes)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_Available(numport, numbytes);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Read from UART buffer
//	

inline uint16_t UART_Read(const uint8_t numport, uint8_t* data)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_Read(numport, data);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
//	Flush UART output buffer
//	

inline uint16_t UART_Flush(const uint8_t numport)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_Flush(numport);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}

//
//	Write string to UART buffer
//	

inline uint16_t UART_Print(const uint8_t numport, const char* buffer)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_Print(numport, buffer);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}

//
// Send buffer to UART buffer
//

inline uint16_t UART_Send(const uint8_t numport, const uint8_t *buffer, int len)
{
	#ifdef SOC_ARDUINO
		return Arduino_UART_Send(numport, buffer, len);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}