#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"


void FlyportTask()
{
	// GROVE board
	void *board = new(IoT_Board);
	vTaskDelay(40);
    _dbgwrite("Flyport Task Started...\r\n");
	
	// Wait for GSM Connection successfull
	_dbgwrite("Waiting network connection...");
	while((LastConnStatus() != REG_SUCCESS) && (LastConnStatus() != ROAMING))
	{
		vTaskDelay(20);
		IOPut(LED1_Pin, toggle);
		do
		{
			UpdateConnStatus();
			while(LastExecStat() == OP_EXECUTION)
				vTaskDelay(1);
		}while(LastExecStat() != OP_SUCCESS);
	}
	vTaskDelay(20);
	IOPut(LED1_Pin, on);
    _dbgwrite("Flyport registered on network!\r\n");
	_dbgwrite("Connected to :");
	_dbgwrite(GSMGetOperatorName());
	_dbgwrite("\r\n");
	
	// GROVE devices	
	// Digital Input
	void *button = new(Dig_io, INDown);
	attachToBoard(board, button, DIG1);
	
    while(1)
    {
		// Check pressure of button
		if(get(button) != 0)
		{
			_dbgwrite("Button Pressed!\r\n");
			vTaskDelay(50);
		}
	}
}
