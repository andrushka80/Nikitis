// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_read_http_response(void)
{ 

	switch (LastExecStat())
	{
		case OP_SUCCESS	:
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("READ HTTP RSP OK!\n");
			#endif
			
			return(CLOSE_SOCKET);
			
		case OP_EXECUTION :
			return(WAIT_READ_RSP);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR READ HTTP RSP!\r\n");
			#endif
			
			return(CLOSE_SOCKET);
	}

}
