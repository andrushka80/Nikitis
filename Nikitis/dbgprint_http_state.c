// Prints the name of the new state (if changed from previous) or a dot "." if the same as previous	
#include "taskFlyport.h"
#include "user_config.h"
#include "debug_report_tools.h"
 
void dbgprint_http_state(int nextState, int prevState){ 

	char dbgMsg[50];

	if (prevState != nextState)
	{
		sprintf(dbgMsg,"\nHTTPState = %s\n",get_http_state_name(nextState));
	}

	else
	{
		sprintf(dbgMsg,".");
	}
	
	DBG_WRITE(dbgMsg, DBG_UART);
	
}
