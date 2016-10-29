// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void check_network_connection(void){ 

BYTE regStat = NO_REG;
 
	if(inExecution == FALSE)
	{
		inExecution = TRUE;
		UpdateConnStatus();
	}
	else
	{
		inExecution = FALSE;
		if(LastExecStat() == OP_SUCCESS)
		{
			if(LastConnStatus() != regStat)
				regStat = LastConnStatus();

			if((regStat == REG_SUCCESS) || (regStat == ROAMING))
			{
				// Start with new action!
				nextState = OPEN_SOCKET;
			}
		}
		else
		{
			_dbgwrite("Problems on UpdateConnStatus...\r\n");
			nextState = SETUP_APN;
		}
	}

}
