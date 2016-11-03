#include "taskFlyport.h"
#include "user_config.h"
 
void init_http_params(HTTP_PARAMS_T* httpParams)
{ 

	httpParams->sockHttp->number = INVALID_SOCKET;
	
	strcpy(httpParams->httpServName,HTTP_SERVER_NAME);
	strcpy(httpParams->httpServPort,HTTP_SERVER_PORT);
	strcpy(httpParams->requestGetURL,HTTP_REQUEST_GET_URL);
	strcpy(httpParams->requestURL,HTTP_REQUEST_URL);
	
}
