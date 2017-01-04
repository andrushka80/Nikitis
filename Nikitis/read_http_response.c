// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
#include "debug_report_tools.h"
 
void read_http_response(HTTP_PARAMS_T *httpParams, char *inBuff){ 

	int lenTemp = httpParams->sockHttp->rxLen;
	if(lenTemp == 0)
		DBG_WRITE("No data to Read!\r\n", DBG_UART);
	else
	{
		if(lenTemp > 1500)
			lenTemp = 1500;
		HTTPReadData(httpParams->sockHttp, inBuff, lenTemp);
		inBuff[lenTemp] = '\0';
	}

}
