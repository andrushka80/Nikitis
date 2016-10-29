// Wait for GSM Connection successful	
#include "taskFlyport.h"
#include "user_config.h"
#include "grovelib.h"
 
void wait_until_registered(){ 
 
	_dbgwrite("Waiting network connection...");

	while((LastConnStatus() != REG_SUCCESS) && (LastConnStatus() != ROAMING))
	{
		vTaskDelay(DELAY_200MSEC);

		IOPut(LED1_Pin, toggle);
		do
		{
			UpdateConnStatus();
			while(LastExecStat() == OP_EXECUTION)
				vTaskDelay(1);
			
		}while(LastExecStat() != OP_SUCCESS);
	}
	vTaskDelay(DELAY_200MSEC);
	IOPut(LED1_Pin, on);

	_dbgwrite("Flyport registered on network!\r\n");
	_dbgwrite("Connected to :");
	_dbgwrite(GSMGetOperatorName());
	_dbgwrite("\r\n");

}
