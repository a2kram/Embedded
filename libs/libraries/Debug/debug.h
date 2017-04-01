/*
	Debug functionality
*/

#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Debug definitions
//

#define MAX_DEBUG_MSG_LEN 									256
#define DEBUG_UART_NUM										0

#define STATUS_REPORT_CALL(code, str) 						if(FAILED(code)) {Debug_Print("%s - Error: 0x%04X\n", str, code);}

//
// Debug function prototypes
//	

void Debug_Print(const char* format, ...);
void Debug_PrintFloat(float value, int places);

#ifdef __cplusplus
}
#endif

#endif