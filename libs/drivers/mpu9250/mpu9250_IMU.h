/*
	MPU9250 IMU Driver 
*/

#ifndef MPU_9250_H
#define MPU_9250_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Device Addresses
//
	
#define MPU9250_ADDRESS 					(0x68)
#define AK8963_ADDRESS						(0x0C)

//
// Device Definitions
//

#define MPU9250_WHOAMI_VALUE				(0x71)
#define MPU9250_A_RES_2G					(2.0f / 32768.0f)
#define MPU9250_G_RES_250DPS				(250.0f / 32768.0f)
#define MPU9250_M_RES_16B					(10.0f * 4912.0f / 32760.0f)
#define AK8963_WHOAMI_VALUE					(0x48)

// 
// MPU9250 Register Addresses
//	

#define MPU9250_SMPLRT_DIV					(0x19)
#define MPU9250_CONFIG						(0x1A)
#define MPU9250_GYRO_CONFIG					(0x1B)
#define MPU9250_ACCEL_CONFIG				(0x1C)
#define MPU9250_ACCEL_CONFIG2				(0x1D)
#define MPU9250_FIFO_EN						(0x23)
#define MPU9250_I2C_MST_CTRL				(0x24)
#define MPU9250_INT_STATUS					(0x3A)
#define MPU9250_ACCEL_XOUT_H				(0x3B)
#define MPU9250_INT_PIN_CFG					(0x37)
#define MPU9250_INT_ENABLE					(0x38)
#define MPU9250_TEMP_OUT_H					(0x41)
#define MPU9250_GYRO_XOUT_H					(0x43)
#define MPU9250_USER_CTRL					(0x6A)
#define MPU9250_PWR_MGMT_1					(0x6B)
#define MPU9250_PWR_MGMT_2					(0x6C)
#define MPU9250_FIFO_COUNT_H				(0x72)
#define MPU9250_FIFO_R_W					(0x74)
#define MPU9250_WHO_AM_I					(0x75)	
#define MPU9250_XA_OFFSET_H					(0x77)
#define MPU9250_YA_OFFSET_H					(0x7A)
#define MPU9250_ZA_OFFSET_H					(0x7D)

#define AK8963_WHO_AM_I						(0x00)
#define AK8963_ST1							(0x02)
#define AK8963_XOUT_L						(0x03)
#define AK8963_ST2							(0x09)
#define AK8963_CNTL1						(0x0A)
#define AK8963_ASAX							(0x10)

//
// MPU9250 Register Values
//

#define MPU9250_H_RESET_SHIFT				(7)
#define MPU9250_H_RESET_MASK				(1 << MPU9250_H_RESET_SHIFT)
#define MPU9250_H_RESET_RESET				(1)

#define MPU9250_CLK_SRC_SHIFT				(0)
#define MPU9250_CLK_SRC_MASK				(7 << MPU9250_CLK_SRC_SHIFT)
#define MPU9250_CLK_SRC_INTERNAL_OSC		(0x00)
#define MPU9250_CLK_SRC_PLL					(0x01)

#define MPU9250_FIFO_MODE_SHIFT				(6)
#define MPU9250_FIFO_MODE_MASK				(1 << MPU9250_FIFO_MODE_SHIFT)
#define MPU9250_FIFO_MODE_OVERWRITE			(0x00)
#define MPU9250_FIFO_MODE_BLOCK				(0x01)

#define MPU9250_FSYNC_SHIFT					(3)
#define MPU9250_FSYNC_MASK					(7 << MPU9250_FSYNC_SHIFT)
#define MPU9250_FSYNC_DISABLED				(0x00)

#define MPU9250_DLPF_CFG_SHIFT				(0)
#define MPU9250_DLPF_CFG_MASK				(7 << MPU9250_DLPF_CFG_SHIFT)

#define MPU9250_GYRO_FS_SEL_SHIFT			(3)
#define MPU9250_GYRO_FS_SEL_MASK			(3 << MPU9250_GYRO_FS_SEL_SHIFT)
#define MPU9250_GYRO_FS_SEL_250DPS			(0)
#define MPU9250_GYRO_FS_SEL_500DPS			(1)	
#define MPU9250_GYRO_FS_SEL_1000DPS			(2)
#define MPU9250_GYRO_FS_SEL_2000DPS			(3)

#define MPU9250_ACCEL_FS_SEL_SHIFT			(3)
#define MPU9250_ACCEL_FS_SEL_MASK			(3 << MPU9250_ACCEL_FS_SEL_SHIFT)
#define MPU9250_ACCEL_FS_SEL_2G				(0)
#define MPU9250_ACCEL_FS_SEL_4G				(1)	
#define MPU9250_ACCEL_FS_SEL_8G				(2)
#define MPU9250_ACCEL_FS_SEL_16G			(3)

#define MPU9250_A_DLPF_CFG_SHIFT			(0)
#define MPU9250_A_DLPF_CFG_MASK				(7 << MPU9250_DLPF_CFG_SHIFT)

#define MPU9250_LATCH_INT_EN_SHIFT			(5)
#define MPU9250_LATCH_INT_EN_MASK			(1 << MPU9250_LATCH_INT_EN_SHIFT)
#define MPU9250_LATCH_INT_EN_HOLD			(0x01)

#define MPU9250_INT_BYPASS_EN_SHIFT			(1)
#define MPU9250_INT_BYPASS_EN_MASK			(1 << MPU9250_INT_BYPASS_EN_SHIFT)
#define MPU9250_INT_BYPASS_EN_ENABLED		(0x01)

#define MPU9250_INT_RAW_RDY_EN_SHIFT		(0)
#define MPU9250_INT_RAW_RDY_EN_MASK			(1 << MPU9250_INT_RAW_RDY_EN_SHIFT)
#define MPU9250_INT_RAW_RDY_EN_ENABLED		(0x01)

//
// AK8963 Register Values
//

#define AK8963_CNTL1_MODE_SHIFT				(0)
#define AK8963_CNTL1_MODE_MASK				(7 << AK8963_CNTL1_MODE_SHIFT)
#define AK8963_CNTL1_MODE_PWR_DN			(0x0000)
#define AK8963_CNTL1_MODE_SNGL_MEAS			(0x0001)
#define AK8963_CNTL1_MODE_CNT_MEAS_8HZ		(0x0010)
#define AK8963_CNTL1_MODE_CNT_MEAS_100HZ	(0x0110)
#define AK8963_CNTL1_MODE_FUSE_ROM_ACCESS	(0x0F)

#define AK8963_CNTL1_BIT_SHIFT				(4)
#define AK8963_CNTL1_BIT_MASK				(1 << AK8963_CNTL1_BIT_SHIFT)
#define AK8963_CNTL1_BIT_14B				(0x00)
#define AK8963_CNTL1_BIT_16B				(0x01)

#define AK8963_ST1_DRDY_SHIFT				(0)
#define AK8963_ST1_DRDY_MASK				(1 << AK8963_ST1_DRDY_SHIFT)
#define AK8963_ST1_DRDY_RDY					(0x01)

#define AK8963_ST2_HOFL_SHIFT				(3)
#define AK8963_ST2_HOFL_MASK				(1 << AK8963_ST2_HOFL_SHIFT)
#define AK8963_ST2_HOFL_OVERFLOW			(0x01)


//
// Function Prototypes
//

uint16_t MPU9250_Initialize();
uint16_t MPU9250_Reset();
uint16_t AK8963_Reset();
uint16_t MPU9250_SelfTest();
uint16_t MPU9250_SensorReading(SensorType sensor, uint8_t* data);
uint16_t MPU9250_AccelToG(int16_t x, int16_t y, int16_t z, float* xG, float* yG, float* zG);
uint16_t MPU9250_GyroToDPS(int16_t x, int16_t y, int16_t z, float* xG, float* yG, float* zG);
uint16_t MPU9250_MagTomG(int16_t x, int16_t y, int16_t z, float* xmG, float* ymG, float* zmG);

#ifdef __cplusplus
}
#endif

#endif