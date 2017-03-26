/*
	Generic UART Driver
*/

#ifndef HAL_UART_H
#define HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif


//
// UART Types and Definitions
//

typedef enum _uart_databits
{
	DBITS_5 = 0,
	DBITS_6,
	DBITS_7,
	DBITS_8,
	MAX_DBITS
} uart_databits;

typedef enum _uart_stopbits
{
	SBITS_1 = 0,
	SBITS_2,
	MAX_SBITS
} uart_stopbits;

typedef enum _uart_parity
{
	PARITY_NONE = 0,
	PARITY_ODD,
	PARITY_EVEN,
	MAX_PARITY
} uart_parity;


//
// Function Prototypes
//

uint16_t UART_Setup(const uint8_t numport, const uint32_t speed, uart_databits dbits, uart_stopbits sbits, uart_parity parity);
uint16_t UART_End(const uint8_t numport);
uint16_t UART_Available(const uint8_t numport, uint8_t* numbytes);
uint16_t UART_Read(const uint8_t numport, uint8_t* data);
uint16_t UART_Flush(const uint8_t numport);
uint16_t UART_Print(const uint8_t numport, const char* data);

#ifdef __cplusplus
}
#endif

#endif 