/*
	Generic SOC Driver
*/

#ifndef HAL_SOC_H
#define HAL_SOC_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes
//

uint16_t SOC_Initialize();
uint16_t SOC_crc16(uint8_t* buf, uint8_t start, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif 