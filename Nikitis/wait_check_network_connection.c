// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
int wait_check_network_connection(void)
{ 

	char	dbgMsg[50];
	int		connStatus;
	int		execStatus;

	execStatus = LastExecStat();
	connStatus = LastConnStatus();
	
	switch (execStatus)
	{
		case OP_SUCCESS		:
			
			if ((connStatus == REG_SUCCESS) || (connStatus == ROAMING))
			{
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("CHECK CONNECTION OK!\n");
			#endif
			
			return(OPEN_SOCKET);	
			}
			else
			{
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR CHECK CONNECTION!\r\n");
			sprintf(dbgMsg,"Connection Error code = %d\n",connStatus);
			_dbgwrite(dbgMsg);
			#endif
			
			return(CHECK_CONNECTION);		
			}
			
		case OP_EXECUTION :
			return(WAIT_CHECK_CONNECTION);
		
		//ERROR	
		default :
			
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("ERROR CHECK CONNECTION!\r\n");
			sprintf(dbgMsg,"Operation Error code = %d\n",execStatus);
			_dbgwrite(dbgMsg);
			#endif
			
			return(SETUP_APN);
			
	}

}
