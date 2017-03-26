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
		sensor = 0;//(++sensor) % SENSOR_LEN;
		STATUS_REPORT_CALL(IMU_SensorReading((SensorType)sensor, (uint8_t*)data), "IMU_SensorReading");

		Debug_Print("%s X: %d Y: %d Z: %d\n", SensorList[sensor], data[0], data[1], data[2]);
		Timers_DelayMs(1000);
	}

	return STATUS_SUCCESS;
}