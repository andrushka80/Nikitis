// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void open_http_socket(HTTP_PARAMS_T *httpParams){ 

TCP_SOCKET	sockHttpLocal;

	if(inExecution == FALSE)
	{
		inExecution = TRUE;
		_dbgwrite("Starting HTTP/TCP Connection...\r\n");
		HTTPOpen(&sockHttpLocal, httpParams -> httpServName, httpParams -> httpServPort);
		httpParams -> sockHttp = sockHttpLocal;
	}
	else
	{
		inExecution = FALSE;
		if(LastExecStat() == OP_SUCCESS)
		{
			_dbgwrite("HTTP Socket opened!\n");
			nextState = SEND_HTTP_REQ;
		}
		else
		{
			_dbgwrite("Problems on HTTPOpen...\r\n");
			nextState = SETUP_APN;
		}
	}
}
