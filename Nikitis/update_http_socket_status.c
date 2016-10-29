// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void update_http_socket_status(HTTP_PARAMS_T *httpParams){ 

	if(inExecution == FALSE)
	{
		inExecution = TRUE;
		_dbgwrite("Updating HTTP Socket...\r\n");
		HTTPStatus(&httpParams->sockHttp);
	}
	else
	{
		inExecution = FALSE;
		if(LastExecStat() == OP_SUCCESS)
		{
			_dbgwrite("Socket Status updated!\n");
			nextState = READ_RSP;
		}
		else
		{
			_dbgwrite("Problems on HTTPStatus...\r\n");
			nextState = CLOSE_SOCKET;
		}
	}

}
