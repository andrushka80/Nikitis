// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
 
void config_apn(char *apnName){ 
 
	if(inExecution == FALSE)
	{
		inExecution = TRUE;
		APNConfig(apnName,"","",DYNAMIC_IP,DYNAMIC_IP,DYNAMIC_IP);
	}
	else
	{
		inExecution = FALSE;
		if(LastExecStat() == OP_SUCCESS)
		{
			_dbgwrite("APN correctly set!\n");
			nextState = CHECK_CONNECTION;
		}
		else
		{
			_dbgwrite("Problems on APNConfig...\r\n");
			nextState = SETUP_APN;
		}
	}

}
