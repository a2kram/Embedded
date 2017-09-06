/*
	HCI Layer Library 
*/

#ifndef HCI_H
#define HCI_H

#ifdef __cplusplus
extern "C" {
#endif

//
// HCI Definitions
//

#define HCI_UART_NUM              0
#define HCI_HEADER_LEN            4
#define HCI_CRC_LEN               2 
#define HCI_START_STOP_LEN        1
#define HCI_CMD_LEN               1
#define HCI_OVERHEAD_LEN          (HCI_HEADER_LEN + HCI_CRC_LEN + HCI_START_STOP_LEN * 2)
#define HCI_MAX_PAYLOAD           512
#define HCI_MAX_TX_LEN            (HCI_OVERHEAD_LEN + HCI_MAX_PAYLOAD)

#define HCI_BROADCAST_PACKET      0
#define HCI_DATA_INTEGRITY_CHECK  1
#define HCI_PACKET_TYPE           14

#define HCI_SLIP_CHAR             0xC0
#define HCI_SLIP_ESC_CHAR         0xDB
#define HCI_SLIP_ESC_END_CHAR     0xDC
#define HCI_SLIP_ESC_ESC_CHAR     0xDD

//
// HCI Commands
//

typedef enum _hcicommands
{
    HCI_IMU_9DOF_DATA = 0,
    NUM_HCI_COMMANDS
} hcicommands;

//
// HCI Message Types
//

typedef struct _imu9data
{
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
    float magX;
    float magY;
    float magZ;
} imu9data;

//
// Function Prototypes
//

uint16_t HCI_Broadcast(uint8_t* MsgBuffer, uint8_t MsgLen, uint8_t Command);

#ifdef __cplusplus
}
#endif

#endif