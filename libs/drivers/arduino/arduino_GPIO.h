/*
	Arduino GPIO Driver
*/

#ifndef ARDUINO_GPIO_H
#define ARDUINO_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Driver types and defintions
//

#define NUM_GPIO_PINS 19

//
// Function Prototypes
//

uint16_t Arduino_GPIO_SetupInput(const uint16_t pinnumber, bool pullup);
uint16_t Arduino_GPIO_SetupOutput(const uint16_t pinnumber, pinstate state);
uint16_t Arduino_GPIO_DigitalWrite(const uint16_t pinnumber, pinstate state);
uint16_t Arduino_GPIO_DigitalRead(const uint16_t pinnumber, uint16_t* value);
uint16_t Arduino_GPIO_AnalogRead(const uint16_t pinnumber, uint16_t* value);

#ifdef __cplusplus
}
#endif

#endif 