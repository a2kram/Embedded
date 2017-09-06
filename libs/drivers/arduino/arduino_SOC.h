/*
	Arduino SOC Driver
*/

#ifndef ARDUINO_SOC_H
#define ARDUINO_SOC_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes
//

uint16_t Arduino_SOC_Initialize();
uint16_t Arduino_SOC_crc16(uint8_t* buf, uint8_t start, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif 