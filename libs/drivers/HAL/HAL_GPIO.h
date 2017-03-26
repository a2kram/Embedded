/*
	Generic GPIO Driver
*/

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

//
// GPIO Types and Definitions
//

typedef enum _pinstate
{
	STATE_LOW = 0,
	STATE_HIGH,
	MAX_STATES
} pinstate;


//
// Function Prototypes
//

uint16_t GPIO_SetupInput(const uint16_t pinnumber, bool pullup);
uint16_t GPIO_SetupOutput(const uint16_t pinnumber, pinstate state);
uint16_t GPIO_DigitalWrite(const uint16_t pinnumber, pinstate state);
uint16_t GPIO_DigitalRead(const uint16_t pinnumber, uint16_t* value);
uint16_t GPIO_AnalogRead(const uint16_t pinnumber, uint16_t* value);

#ifdef __cplusplus
}
#endif

#endif 