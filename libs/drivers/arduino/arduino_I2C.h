/*
	Arduino I2C Driver
*/

#ifndef ARDUINO_I2C_H
#define ARDUINO_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes
//

uint16_t Arduino_I2C_Init();
uint16_t Arduino_I2C_Read(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, uint8_t* data);
uint16_t Arduino_I2C_Write(const uint8_t device_addr, const uint8_t reg_addr, uint8_t count, const uint8_t* data, bool end_transmission);

#ifdef __cplusplus
}
#endif

#endif 