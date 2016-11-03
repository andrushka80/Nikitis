// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_update_http_socket_status(void)
{ 

	switch (LastExecStat())
	{
		case OP_SUCCESS	:
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("UPDATE SOCK STS OK!\n");
			#endif
			
			return(READ_RSP);
						
		case OP_EXECUTION :
			return(WAIT_UPDATE_SOCK_STS);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR UPDATE SOCK STS!\r\n");
			#endif
			
			return(CLOSE_SOCKET);
	}

}
