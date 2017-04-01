/*
	IMU UART Passthrough Arduino Application
*/

#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "facility.h"
#include "statuscodes.h"
#include "Debug/debug.h"
#include "HAL/HAL_IMU.h"
#include "HAL/HAL_GPIO.h"
#include "HAL/HAL_Timers.h"
#include "HAL/HAL_SOC.h"
#include "HAL/HAL_UART.h"

char* SensorList[3] = {"Accelerometer", "Gyroscope", "Compass"};

int main()
{
	int16_t data[3] = {0};
	float x, y, z;
	uint32_t sensor = 0;

	// Initialize SOC
	SOC_Initialize();

	// Reset IMU and compass
	STATUS_REPORT_CALL(IMU_Reset(), "IMU_Reset");

	// Initialize IMU
	STATUS_REPORT_CALL(IMU_Initialize(), "IMU_Initialize");

	Timers_DelayMs(1000);

	// Read and output sensor data 
	while(1)
	{
		sensor = 1;//(++sensor) % SENSOR_LEN;
		STATUS_REPORT_CALL(IMU_SensorReading((SensorType)sensor, (uint8_t*)data), "IMU_SensorReading");

		switch(sensor)
		{
			case SENSOR_ACCEL:
			{
				IMU_AccelToG(data[0], data[1], data[2], &x, &y, &z);
				break;
			}
			case SENSOR_GYRO:
			{
				IMU_GyroToDPS(data[0], data[1], data[2], &x, &y, &z);
				break;
			}
			case SENSOR_COMPASS:
			{
				break;
			}
		}

		Debug_Print("%s X:", SensorList[sensor]);
		Debug_PrintFloat(x, 3);
		Debug_Print(" Y:");
		Debug_PrintFloat(y, 3);
		Debug_Print(" Z:");
		Debug_PrintFloat(z, 3);
		Debug_Print("\n");

		Timers_DelayMs(1000);
	}

	return STATUS_SUCCESS;
}