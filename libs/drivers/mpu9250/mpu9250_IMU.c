/*
	MPU9250 IMU Driver
*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "facility.h"
#include "statuscodes.h"
#include "Debug/debug.h"
#include "HAL/HAL_Timers.h"
#include "HAL/HAL_I2C.h"
#include "HAL/HAL_IMU.h"
#include "mpu9250_IMU.h"

static bool sInitialized = false;
	
//
// Initalize IMU 
//
	
uint16_t MPU9250_Initialize()
{
	uint8_t data = 0;

	// Perform WhoAmI test
	STATUS_CHECKED_CALL(I2C_Read(MPU9250_ADDRESS, MPU9250_WHO_AM_I, 1, &data))

	if(data != MPU9250_WHOAMI_VALUE)
	{
		return E_DRV_IMU_INVALID_WHOAMI;
	}

	// Wakeup IMU and enable accelerometer and gyroscope
	data = 0;
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_PWR_MGMT_1, 1, &data, true))

	// Delay 100ms for PLL to get ready
	Timers_DelayMs(100);

	// Set clock source to be PLL if ready
	data = MPU9250_CLK_SRC_PLL << MPU9250_CLK_SRC_SHIFT;
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_PWR_MGMT_1, 1, &data, true))

	// Set FIFO to overwrite, disable FSYNC, and use DLPF CFG combination 3
	data = ((MPU9250_FIFO_MODE_OVERWRITE << MPU9250_FIFO_MODE_SHIFT) | 
		   (MPU9250_FSYNC_DISABLED << MPU9250_FSYNC_SHIFT) |
		   (0x3 << MPU9250_DLPF_CFG_SHIFT));
   	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_CONFIG, 1, &data, true))

   	// Set sample rate to 200Hz by setting sample rate divider to 4
   	// Despite the gyro and accel having 1 kHz sample rates, 
   	// the SMPLRT_DIV setting reduces rate to 200Hz
   	data = 0x04;
   	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_SMPLRT_DIV, 1, &data, true))

   	// Clear gyroscope self test bits and set full scale range
   	data = (MPU9250_GYRO_FS_SEL_250DPS << MPU9250_GYRO_FS_SEL_SHIFT);
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_GYRO_CONFIG, 1, &data, true))

	// Clear accelerometer self test bits and set full scale range
   	data = (MPU9250_ACCEL_FS_SEL_2G << MPU9250_ACCEL_FS_SEL_SHIFT);
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_ACCEL_CONFIG, 1, &data, true))

	// Clear DLPF bypass and set accelerometer low pass filter
   	data = (0x3 << MPU9250_A_DLPF_CFG_SHIFT);
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_ACCEL_CONFIG2, 1, &data, true))

	// Set INT pin active high, push-pull, clear on read of INT_STATUS, and bypass
	// master interface pins
	data = ((MPU9250_LATCH_INT_EN_HOLD << MPU9250_LATCH_INT_EN_SHIFT) | 
		   (MPU9250_INT_BYPASS_EN_ENABLED << MPU9250_INT_BYPASS_EN_SHIFT));
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_INT_PIN_CFG, 1, &data, true))

	// Enable data ready interrupt
	data = (MPU9250_INT_RAW_RDY_EN_ENABLED << MPU9250_INT_RAW_RDY_EN_SHIFT);
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_INT_ENABLE, 1, &data, true)) 

	Timers_DelayMs(10);

	// Reset compass
	STATUS_CHECKED_CALL(AK8963_Reset())

	Timers_DelayMs(10);

	// Compass WhoAmI Test
	STATUS_CHECKED_CALL(I2C_Read(AK8963_ADDRESS, AK8963_WHO_AM_I, 1, &data))

	if(data != AK8963_WHOAMI_VALUE)
	{
		return E_DRV_IMU_INVALID_WHOAMI;
	}
	
	// Set compass to 16 bit resolution and continuous mode data acquisition
	data = (uint8_t)((AK8963_CNTL1_BIT_16B << AK8963_CNTL1_BIT_SHIFT) | 
		   (AK8963_CNTL1_MODE_CNT_MEAS_100HZ << AK8963_CNTL1_MODE_SHIFT));
	STATUS_CHECKED_CALL(I2C_Write(AK8963_ADDRESS, AK8963_CNTL1, 1, &data, true))

	Timers_DelayMs(10);

	sInitialized = true;

	return STATUS_SUCCESS; 
}


//
// Reset IMU
//

uint16_t MPU9250_Reset()
{
	// Reset internal registers and restore default settings
	uint8_t data = (MPU9250_H_RESET_RESET << MPU9250_H_RESET_SHIFT);
	STATUS_CHECKED_CALL(I2C_Write(MPU9250_ADDRESS, MPU9250_PWR_MGMT_1, 1, &data, true))

	return STATUS_SUCCESS;
}


//
// Reset compass
//

uint16_t AK8963_Reset()
{
	// Power down compass
	uint8_t data = (AK8963_CNTL1_MODE_PWR_DN << AK8963_CNTL1_MODE_SHIFT);
	STATUS_CHECKED_CALL(I2C_Write(AK8963_ADDRESS, AK8963_CNTL1, 1, &data, true))

	// Delay 10ms for compass to come back up
	Timers_DelayMs(10);

	return STATUS_SUCCESS;
}


//
// Run self-test on IMU
//

uint16_t MPU9250_SelfTest()
{
	return STATUS_SUCCESS;
}


//
// Return 3-axis 16-bit sensor reading 
//

uint16_t MPU9250_SensorReading(SensorType sensor, uint8_t* data)
{
	uint8_t device_address;
	uint8_t reg_address;
	int16_t xData, yData, zData;

	// Check inputs
	if(data == NULL)
	{
		return E_DRV_IMU_INVALID_INPUT;
	}

	// Check if driver is initialized
	if(!sInitialized)
	{
		STATUS_CHECKED_CALL(MPU9250_Initialize())
	}

	switch(sensor)
	{
		case SENSOR_ACCEL:
		{
			device_address = MPU9250_ADDRESS;
			reg_address = MPU9250_ACCEL_XOUT_H;
			break;
		}
		case SENSOR_GYRO:
		{
			device_address = MPU9250_ADDRESS;
			reg_address = MPU9250_GYRO_XOUT_H;
			break;
		}
		case SENSOR_COMPASS:
		{
			// Check if data is ready
			STATUS_CHECKED_CALL(I2C_Read(AK8963_ADDRESS, AK8963_ST1, 1, data))

			Debug_Print("1 X: %d (%d)\n", data[0], (AK8963_ST1_DRDY_RDY << AK8963_ST1_DRDY_SHIFT));

			if((data[0] & AK8963_ST1_DRDY_MASK) != (AK8963_ST1_DRDY_RDY << AK8963_ST1_DRDY_SHIFT))
			{
				Debug_Print("just\n");
				return E_DRV_IMU_DATA_NOT_READY;
			}

			Debug_Print("incase\n");

			// Check if magnetic sensor overflow bit is set
			STATUS_CHECKED_CALL(I2C_Read(AK8963_ADDRESS, AK8963_ST2, 1, data))

			Debug_Print("2 X: %d (%d)\n", data[0], (AK8963_ST1_DRDY_RDY << AK8963_ST1_DRDY_SHIFT));

			if((data[0] & AK8963_ST2_HOFL_MASK) != (AK8963_ST2_HOFL_OVERFLOW << AK8963_ST2_HOFL_SHIFT))
			{
				return E_DRV_IMU_DATA_OVERFLOW;
			}

			device_address = AK8963_ADDRESS;
			reg_address = AK8963_XOUT_L;
			break;
		}
		default:
		{
			return E_DRV_IMU_UNKNOWN_SENSOR;
		}
	}

	// Read data
	STATUS_CHECKED_CALL(I2C_Read(device_address, reg_address, 6, data));

	if(sensor != SENSOR_COMPASS)
	{
		// Convert data
		xData = (((int16_t)data[0] << 8) | data[1]);
		yData = (((int16_t)data[2] << 8) | data[3]);
		zData = (((int16_t)data[4] << 8) | data[5]);
	
		memcpy(&data[0], &xData, sizeof(int16_t));
		memcpy(&data[2], &yData, sizeof(int16_t));
		memcpy(&data[4], &zData, sizeof(int16_t));
	}

	return STATUS_SUCCESS;
}

uint16_t MPU9250_AccelToG(int16_t x, int16_t y, int16_t z, float* xG, float* yG, float* zG)
{
	if(xG == NULL || yG == NULL || zG == NULL)
	{
		return E_DRV_IMU_INVALID_INPUT;
	}

	*xG = x * MPU9250_A_RES_2G;
	*yG = y * MPU9250_A_RES_2G;
	*zG = z * MPU9250_A_RES_2G;

	return STATUS_SUCCESS;
}

uint16_t MPU9250_GyroToDPS(int16_t x, int16_t y, int16_t z, float* xDPS, float* yDPS, float* zDPS)
{
	if(xDPS == NULL || yDPS == NULL || zDPS == NULL)
	{
		return E_DRV_IMU_INVALID_INPUT;
	}

	*xDPS = x * MPU9250_G_RES_250DPS;
	*yDPS = y * MPU9250_G_RES_250DPS;
	*zDPS = z * MPU9250_G_RES_250DPS;

	return STATUS_SUCCESS;
}

uint16_t MPU9250_MagTomG(int16_t x, int16_t y, int16_t z, float* xmG, float* ymG, float* zmG)
{
	if(xmG == NULL || ymG == NULL || zmG == NULL)
	{
		return E_DRV_IMU_INVALID_INPUT;
	}

	*xmG = x * MPU9250_M_RES_16B;
	*ymG = y * MPU9250_M_RES_16B;
	*zmG = z * MPU9250_M_RES_16B;

	return STATUS_SUCCESS;
}