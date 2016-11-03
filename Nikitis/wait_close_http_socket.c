// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_close_http_socket(void)
{ 

	switch (LastExecStat())
	{
		case OP_SUCCESS	:
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("CLOSE SOCKET OK!\n");
			#endif
			
			return(HTTP_SESSION_END);
			
		case OP_EXECUTION :
			return(WAIT_CLOSE_SOCKET);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR CLOSE SOCKET!\r\n");
			#endif
			
			return(HTTP_SESSION_END);


	}
}
