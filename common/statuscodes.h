/*
	Return Types Header
*/

#ifndef STATUS_CODES_H
#define STATUS_CODES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Construct status code
// Status code is a 16 bit signed value, with the following format:
// + - + - - - - - - - + - - - - - - - - +
// | S |    Facility   |       Code      |
// + - + - - - - - - - + - - - - - - - - +
//
// S - 1 bit severity: 
// 		0 (success)
// 		1 (failure)
//
// Facility - 7 bit facility code
//
// Code - 8 bit facility status code
//
#define MAKE_STATUS_CODE(severity, facility, code) 			((((uint8_t)severity) << 15) | (((uint8_t)facility) << 8) | (uint8_t)code)

// Determine if code indicates failure or success, non-negative codes indicate success
#define SUCCEEDED(code) 						   			(((int16_t) code) >= 0)
#define FAILED(code)										(((int16_t) code) < 0)

// Extract severity, facility, or code from status code
#define STATUS_CODE_SEVERITY(code) 							(((uint16_t) code) >> 15)
#define STATUS_CODE_FACILITY(code) 							((((uint16_t) code) >> 14) & ~(1 << 8))
#define STATUS_CODE_CODE(code) 	   							((uint8_t) code)

// Severities
#define SEVERITY_SUCCESS 									(0)
#define SEVERITY_FAILURE									(1)

// Useful macros
#define STATUS_CHECKED_CALL(code) 							if(FAILED(code)) {return code;}

//
// Status Codes
//

// Generic status codes
#define STATUS_SUCCESS										(0)
#define STATUS_UNIMPLEMENTED								(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_GENERAL, 0))

// Drivers: I2C
#define E_DRV_I2C_INVALID_INPUT 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_I2C, 0))
#define E_DRV_I2C_DATA_TOO_LONG 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_I2C, 1))
#define E_DRV_I2C_NACK_ON_ADDR 								(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_I2C, 2))
#define E_DRV_I2C_NACK_ON_DATA 								(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_I2C, 3))
#define E_DRV_I2C_TIMEOUT 									(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_I2C, 4))

// Drivers: IMU
#define E_DRV_IMU_INVALID_WHOAMI							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_IMU, 0))
#define E_DRV_IMU_UNKNOWN_SENSOR							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_IMU, 1))
#define E_DRV_IMU_INVALID_INPUT 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_IMU, 2))
#define E_DRV_IMU_DATA_OVERFLOW 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_IMU, 3))
#define E_DRV_IMU_DATA_NOT_READY							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_IMU, 4))

// Drivers: GPIO
#define E_DRV_GPIO_PIN_INVALID_PIN							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_GPIO, 0))
#define E_DRV_GPIO_INVALID_INPUT 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_GPIO, 1))

// Drivers: UART
#define E_DRV_UART_INVALID_PARITY 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_UART, 0))
#define E_DRV_UART_INVALID_SBITS 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_UART, 1))
#define E_DRV_UART_INVALID_DBITS 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_UART, 2))
#define E_DRV_UART_INVALID_INPUT 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_UART, 3))
#define E_DRV_UART_WRITE_FAILED 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_UART, 4))
#define E_DRV_UART_NOT_INITIALIZED 							(MAKE_STATUS_CODE(SEVERITY_FAILURE, FACILITY_DRIVER_UART, 5))

#ifdef __cplusplus
}
#endif

#endif