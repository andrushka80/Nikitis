// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_open_http_socket(void)
{ 

	switch (LastExecStat())
	{
		case OP_SUCCESS	:
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("OPEN SOCKET OK!\n");
			#endif
			
			return(SEND_HTTP_REQ);
			
		case OP_EXECUTION :
			return(WAIT_OPEN_SOCKET);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR OPEN SOCKET!\r\n");
			#endif
			
			//return(HTTP_SESSION_END);
			//return(OPEN_SOCKET);
			return(SETUP_APN);
			
	}
}
