/*
	Arduino UART Driver
*/

#ifndef ARDUINO_UART_H
#define ARDUINO_UART_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes
//

uint16_t Arduino_UART_Setup(const uint8_t numport, const uint32_t speed, uart_databits dbits, uart_stopbits sbits, uart_parity parity);
uint16_t Arduino_UART_End(const uint8_t numport);
uint16_t Arduino_UART_Available(const uint8_t numport, uint8_t* numbytes);
uint16_t Arduino_UART_Read(const uint8_t numport, uint8_t* data);
uint16_t Arduino_UART_Flush(const uint8_t numport);
uint16_t Arduino_UART_Print(const uint8_t numport, const char *buffer);
uint16_t Arduino_UART_Send(const uint8_t numport, const uint8_t *buffer, int len);

#ifdef __cplusplus
}
#endif

#endif 