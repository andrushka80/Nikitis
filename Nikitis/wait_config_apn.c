// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_config_apn(void)
{ 
 
	switch (LastExecStat())
	{
		case OP_SUCCESS	:
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("SETUP APN OK!\n");
			#endif
			
			return(CHECK_CONNECTION);
			
		case OP_EXECUTION :
			return(WAIT_SETUP_APN);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR SETUP APN!\r\n");
			#endif
			
			return(SETUP_APN);
	}

}
