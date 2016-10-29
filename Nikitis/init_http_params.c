#include "taskFlyport.h"
#include "user_config.h"
 
void init_http_params(HTTP_PARAMS_T *httpParams){ 

	httpParams->sockHttp.number =INVALID_SOCKET;
	
	sprintf(httpParams->httpServName,"%s",HTTP_SERVER_NAME);
	sprintf(httpParams->httpServPort,"%s",HTTP_SERVER_PORT);
	sprintf(httpParams->requestGetURL,"%s",HTTP_REQUEST_GET_URL);
	sprintf(httpParams->requestURL,"%s",HTTP_REQUEST_URL);
	
	
}
