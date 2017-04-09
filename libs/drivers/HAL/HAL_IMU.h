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
uint16_t IMU_AccelToG(int16_t x, int16_t y, int16_t z, float* xG, float* yG, float* zG);
uint16_t IMU_GyroToDPS(int16_t x, int16_t y, int16_t z, float* xDPS, float* yDPS, float* zDPS);
uint16_t IMU_MagTomG(int16_t x, int16_t y, int16_t z, float* xmG, float* ymG, float* zmG);

#ifdef __cplusplus
}
#endif

#endif