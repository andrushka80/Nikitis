// Prints the name of the new state (if changed from previous) or a dot "." if the same as previous	
#include "taskFlyport.h"
#include "user_config.h"
#include "debug_report_tools.h"
 
void dbgprint_http_state(int nextState, int prevState){ 

	char dbgMsg[50];
	DBG_TARGET_T dbg_type = 0;

	if (prevState != nextState)
	{
		sprintf(dbgMsg,"HTTPState = %s\r\n",get_http_state_name(nextState));
		dbg_type = DBG_UART_SD_TS;
	}

	else
	{
		sprintf(dbgMsg,".");
		dbg_type = DBG_UART;
	}
	
	DBG_WRITE(dbgMsg, dbg_type);
	
}
