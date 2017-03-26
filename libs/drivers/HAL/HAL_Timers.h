/*
	Generic Timers Driver 
*/

#ifndef HAL_TIMERS_H
#define HAL_TIMERS_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes
//

uint16_t Timers_Init();
uint16_t Timers_DelayMs(uint64_t ms);
uint32_t Timers_Micros();

#ifdef __cplusplus
}
#endif

#endif