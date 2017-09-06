#include <stdint.h>
#include <string.h>
#include "facility.h"
#include "statuscodes.h"
#include "Debug/debug.h"
#include "HAL/HAL_SOC.h"
#include "HAL/HAL_UART.h"
#include "hci.h"

static uint8_t sTxTempBuf[HCI_MAX_TX_LEN];
static uint8_t sTxBuf[HCI_MAX_TX_LEN];
static uint8_t sSeqNumber = 1;
static uint8_t sAckNumber = 2;
static uint8_t sTxLen = 0;


uint16_t HCI_Broadcast(uint8_t* MsgBuffer, uint8_t MsgLen, uint8_t Command)
{
    uint16_t Checksum;
    uint8_t PayloadSize = MsgLen + HCI_CMD_LEN;
    uint8_t BufIndex = 0;
    uint8_t TempIndex = 0;

    // Input checking
    if(MsgBuffer == NULL || MsgLen == 0)
    {
        return E_LIB_HCI_INVALID_INPUT;
    }

    // Check if message length is beyond limit
    if(MsgLen > HCI_MAX_PAYLOAD)
    {
        return E_LIB_HCI_TX_PACKET_TOO_LARGE;
    }

    // Check if command is valid
    if(Command >= NUM_HCI_COMMANDS)
    {
        return E_LIB_HCI_INVALID_COMMAND;
    }

    //
    // Construct HCI message loosely based on following packet format
    // https://developer.nordicsemi.com/nRF5_SDK/nRF51_SDK_v8.x.x/doc/8.0.0/s110/html/a00102.html
    //

    sTxTempBuf[0] = (HCI_BROADCAST_PACKET << 7) | (HCI_DATA_INTEGRITY_CHECK << 6) | ((sAckNumber & 0x07) << 3) | (sSeqNumber & 0x07);
    sTxTempBuf[1] = (PayloadSize & (0x000F) << 4) | HCI_PACKET_TYPE;
    sTxTempBuf[2] = ((PayloadSize & 0x0FF0) >> 4);
    sTxTempBuf[3] = (~(sTxTempBuf[0] + sTxTempBuf[1] + sTxTempBuf[2]) + 1) & 0xFF;
    sTxTempBuf[4] = Command;

    if(MsgLen > 0)
    {
        memcpy(&sTxTempBuf[5], MsgBuffer, MsgLen);
    }

    Checksum = SOC_crc16(&sTxTempBuf[0], 0, HCI_HEADER_LEN + PayloadSize);

    sTxTempBuf[5 + MsgLen] = (uint8_t)(Checksum & 0xFF);
    sTxTempBuf[6 + MsgLen] = (uint8_t)((Checksum & 0xFF00) >> 8);

    sTxLen = PayloadSize + HCI_OVERHEAD_LEN;

    // Add SLIP start
    sTxBuf[BufIndex++] = HCI_SLIP_CHAR;

    // Inject excape characters
    while(TempIndex <= (6 + MsgLen))
    {
        switch(sTxTempBuf[TempIndex])
        {
            case(HCI_SLIP_CHAR):
            {
                sTxBuf[BufIndex++] = HCI_SLIP_ESC_CHAR;
                sTxBuf[BufIndex++] = HCI_SLIP_ESC_END_CHAR;
                ++sTxLen;
                ++TempIndex;
                break;
            }
            case(HCI_SLIP_ESC_CHAR):
            {
                sTxBuf[BufIndex++] = HCI_SLIP_ESC_CHAR;
                sTxBuf[BufIndex++] = HCI_SLIP_ESC_ESC_CHAR;
                ++sTxLen;
                ++TempIndex;
                break;
            }
            default:
            {
                sTxBuf[BufIndex++] = sTxTempBuf[TempIndex++];
            }
        }
    }

    // Add SLIP stop
    sTxBuf[BufIndex] = HCI_SLIP_CHAR;

    STATUS_CHECKED_CALL(UART_Send(HCI_UART_NUM, sTxBuf, sTxLen))
    
    sSeqNumber = (sSeqNumber + 1) & 0x7;
    sAckNumber = (sSeqNumber + 1) & 0x7;

    return STATUS_SUCCESS;
}