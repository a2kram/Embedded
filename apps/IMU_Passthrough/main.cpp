/*
	IMU UART Passthrough Arduino Application
*/

#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "facility.h"
#include "statuscodes.h"
#include "Debug/debug.h"
#include "HCI/hci.h"
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
	imu9data IMUData = {0};

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
		for(sensor = 0; sensor < SENSOR_LEN; ++sensor)
		{
			STATUS_REPORT_CALL(IMU_SensorReading((SensorType)sensor, (uint8_t*)data), "IMU_SensorReading");

			switch(sensor)
			{
				case SENSOR_ACCEL:
				{
					STATUS_REPORT_CALL(IMU_AccelToG(data[0], data[1], data[2], &x, &y, &z), "IMU_AccelToG");
					IMUData.accelX = x;
					IMUData.accelY = y;
					IMUData.accelZ = z;
					break;
				}
				case SENSOR_GYRO:
				{
					STATUS_REPORT_CALL(IMU_GyroToDPS(data[0], data[1], data[2], &x, &y, &z), "IMU_GyroToDPS");
					IMUData.gyroX = x;
					IMUData.gyroY = y;
					IMUData.gyroZ = z;
					break;
				}
				case SENSOR_COMPASS:
				{
					STATUS_REPORT_CALL(IMU_MagTomG(data[0], data[1], data[2], &x, &y, &z), "IMU_MagTomG");
					IMUData.magX = x;
					IMUData.magY = y;
					IMUData.magZ = z;
					break;
				}
			}
		}

		STATUS_REPORT_CALL(HCI_Broadcast((uint8_t*)&IMUData, sizeof(IMUData), HCI_IMU_9DOF_DATA), "HCI_Broadcast");
	}

	return STATUS_SUCCESS;
}