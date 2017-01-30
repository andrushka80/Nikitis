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
	DBG_UART_TS        = 1,
	DBG_SD             = 2,     // Write dbg info on SD
	DBG_SD_TS          = 3,     // Write dbg info on SD and add timestamp
	DBG_UART_SD        = 4,     // Write dbg info on UART and on SD
	DBG_UART_SD_TS     = 5      // Write dbg info on SD and on UART and add timestamp
} DBG_TARGET_T;

// *****************************************
//       Public functions definition
// *****************************************
void DBG_WRITE(char* dbgstr, DBG_TARGET_T mode);
void init_dbg_sd();
void set_new_dbg_file();
void print_dbg_file_size();
int dbg_file_size_exceeded();
void goto_new_debug_dir();
