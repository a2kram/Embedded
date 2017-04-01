/*
	Generic IMU Driver
*/

#include <stdint.h>
#include "common/facility.h"
#include "common/statuscodes.h"
#include "common/board.h"
#include "HAL_IMU.h"

#ifdef IMU_MPU9250
#include "../mpu9250/mpu9250_IMU.h"
#endif


//
// Initialize IMU
//

uint16_t IMU_Initialize()
{
	#ifdef IMU_MPU9250
		return MPU9250_Initialize();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
// Reset IMU
//

uint16_t IMU_Reset()
{
	#ifdef IMU_MPU9250
		return MPU9250_Reset();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}
//
// Get sensor reading
//

uint16_t IMU_SensorReading(SensorType sensor, uint8_t* data)
{
	#ifdef IMU_MPU9250
		return MPU9250_SensorReading(sensor, data);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}

//
// Convert ADC output to gs
//

uint16_t IMU_AccelToG(int16_t x, int16_t y, int16_t z, float* xG, float* yG, float* zG)
{
	#ifdef IMU_MPU9250
		return MPU9250_AccelToG(x, y, z, xG, yG, zG);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}

//
// Convert ADC output to degrees per second
//

uint16_t IMU_GyroToDPS(int16_t x, int16_t y, int16_t z, float* xDPS, float* yDPS, float* zDPS)
{
	#ifdef IMU_MPU9250
		return MPU9250_GyroToDPS(x, y, z, xDPS, yDPS, zDPS);
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}


//
// Run IMU self-test
//

uint16_t IMU_SelfTest()
{
	#ifdef IMU_MPU9250
		return MPU9250_SelfTest();
	#else
		return STATUS_UNIMPLEMENTED;
	#endif
}