// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void send_http_request(HTTP_PARAMS_T *httpParams, HTTP_REQ_T requestType, char* jsonReport){ 

	char data[200];
	char paramsHttp[120];
	
	_dbgwrite("Sending request to server...\r\n");

	// Choose the type of request:
	switch(requestType)
	{
		case GET: // GET
			// Launch the request
			HTTPRequest(httpParams->sockHttp, HTTP_GET, httpParams->requestGetURL, "", HTTP_NO_PARAM);
			break;

		case POST_NO_ADD: // HTTP POST without additional params
			// Prepare Data Content:
			sprintf(data, "This is my standard data!\r\n\r\n");

			// Launch the request
			HTTPRequest(httpParams->sockHttp, HTTP_POST, httpParams->requestURL, data, HTTP_NO_PARAM);
			break;

		case POST_ADD:    // HTTP POST with additional params
			
			// Fill additional params:
			sprintf(paramsHttp, "Content-Type: application/json\r\nContent-Length: %d", strlen(jsonReport));

			// Launch the request
			HTTPRequest(httpParams->sockHttp, HTTP_POST, httpParams->requestURL, jsonReport, paramsHttp);
			break;
			
		case IDLE:
			break;
			
		default:
			break;
	}
	
}
