// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void close_http_socket(HTTP_PARAMS_T *httpParams){ 

	if(inExecution == FALSE)
	{
		inExecution = TRUE;
		_dbgwrite("Closing Socket...\r\n");
		HTTPClose(&httpParams->sockHttp);
	}
	else
	{
		nextState = SETUP_APN;
		inExecution = FALSE;
		if(LastExecStat() == OP_SUCCESS)
		{
			_dbgwrite("Socket Closed!\n");    
		}
		else
		{
			_dbgwrite("Problems on HTTPClose...\r\n");
		}
	}
}
