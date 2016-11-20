// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"

void send_http_request(HTTP_PARAMS_T *httpParams, HTTP_REQ_T requestType, char* jsonReport){ 

	char data[MAX_HTTP_HEADER_LEN];
	static char paramsHttp[MAX_HTTP_HEADER_LEN];
	
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
			sprintf(paramsHttp, httpParams->postHeader, httpParams->apikey, strlen(jsonReport));
			
			_dbgwrite("Request URL: ");_dbgwrite(httpParams->requestURL);_dbgwrite("\n");
			_dbgwrite("JSON: ");_dbgwrite(jsonReport);_dbgwrite("\n");
			_dbgwrite("Header format: ");_dbgwrite(httpParams->postHeader);_dbgwrite("\n");
			_dbgwrite("HTTP Parameters: ");_dbgwrite(paramsHttp);_dbgwrite("\n");

			// Launch the request
			HTTPRequest(httpParams->sockHttp, HTTP_POST, httpParams->requestURL, jsonReport, paramsHttp);
			break;
			
		case IDLE:
			break;
			
		default:
			break;
	}
	
}
