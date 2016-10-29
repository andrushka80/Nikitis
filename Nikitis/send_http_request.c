// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void send_http_request(HTTP_PARAMS_T *httpParams, HTTP_REQ_T requestType){ 

	char data[200];
	char paramsHttp[120];
	
	if(inExecution == FALSE)
	{
		inExecution = TRUE;
		_dbgwrite("Sending request to server...\r\n");

		// Choose the type of request:
		switch(requestType)
		{
			case GET: // GET
				// Launch the request
				HTTPRequest(&httpParams->sockHttp, HTTP_GET, httpParams->requestGetURL, "", HTTP_NO_PARAM);
				break;

			case POST_NO_ADD: // HTTP POST without additional params
				// Prepare Data Content:
				sprintf(data, "This is my standard data!\r\n\r\n");

				// Launch the request
				HTTPRequest(&httpParams->sockHttp, HTTP_POST, httpParams->requestURL, data, HTTP_NO_PARAM);
				break;

			case POST_ADD:    // HTTP POST with additional params
				// Prepare Data Content:
				sprintf(data, "This is my data!\r\nAdditional params are included using HTTPRequest function!\r\n\r\n");

				// Fill additional params:
				sprintf(paramsHttp, "Content-Type: application/json\r\nContent-Length: %d", strlen(data));

				// Launch the request
				HTTPRequest(&httpParams->sockHttp, HTTP_POST, httpParams->requestURL, data, paramsHttp);
				break;
				
			case IDLE:
				break;
				
			default:
				break;
		}
	}
	else
	{
		inExecution = FALSE;
		if(LastExecStat() == OP_SUCCESS)
		{
			_dbgwrite("HTTP Request correctly set!\n");
			_dbgwrite("wait for a while for response...");
			vTaskDelay(DELAY_1SEC);
			nextState = UPDATE_SOCK_STS;
		}
		else
		{
			_dbgwrite("Problems on HTTPRequest...\r\n");
			nextState = CLOSE_SOCKET;
		}
	}
}
