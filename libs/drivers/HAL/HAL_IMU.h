/*
	Generic IMU Driver 
*/

#ifndef HAL_IMU_H
#define HAL_IMU_H

#ifdef __cplusplus
extern "C" {
#endif

//
// HAL IMU Types
//

typedef enum _SensorType
{
	SENSOR_ACCEL = 0,
	SENSOR_GYRO,
	SENSOR_COMPASS,
	SENSOR_LEN
} SensorType;

//
// Function Prototypes
//

uint16_t IMU_Initialize();
uint16_t IMU_Reset();
uint16_t IMU_SelfTest();
uint16_t IMU_SensorReading(SensorType sensor, uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif