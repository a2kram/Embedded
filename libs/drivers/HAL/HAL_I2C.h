/*
	Generic I2C Driver
*/

#ifndef HAL_I2C_H
#define HAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

//
// I2C Types and Definitions
//

#define I2C_TIMEOUT 1000


//
// Function Prototypes
//

uint16_t I2C_Init();
uint16_t I2C_Read(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, uint8_t* data);
uint16_t I2C_Write(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, const uint8_t* data, bool end_transmission);

#ifdef __cplusplus
}
#endif

#endif 