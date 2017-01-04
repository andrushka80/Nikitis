// File name: debug_report_tools.h

// *****************************************
//               DEFINES
// *****************************************

#define MAX_DEBUG_FILE_SIZE   65535

// *****************************************
//          New types definition
// *****************************************
typedef enum 
{
	DBG_UART           = 0,     // Print dbg info on UART
	DBG_SD             = 1,     // Write dbg info on SD
	DBG_SD_TS          = 2,     // Write dbg info on SD and add timestamp
	DBG_UART_SD        = 3,     // Write dbg info on UART and on SD
	DBG_UART_SD_TS     = 4      // Write dbg info on SD and on UART and add timestamp
} DBG_TARGET_T;

// *****************************************
//       Public functions definition
// *****************************************
void DBG_WRITE(char* dbgstr, DBG_TARGET_T mode);
void init_dbg_sd();
