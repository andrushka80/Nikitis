// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_send_http_request(void)
{ 

	switch (LastExecStat())
	{
		case OP_SUCCESS	:
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("SEND HTTP REQ OK!\n");
			#endif
			
			return(UPDATE_SOCK_STS);
			
		case OP_EXECUTION :
			return(WAIT_SEND_HTTP_REQ);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR SEND HTTP REQ!\r\n");
			#endif
			
			return(CLOSE_SOCKET);
			
	}
}
