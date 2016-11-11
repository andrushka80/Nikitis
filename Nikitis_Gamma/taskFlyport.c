#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "common.h"


void FlyportTask()
{	
	vTaskDelay(DELAY_1SEC);
	
	// GROVE board
	void *board = new(Board);
 
	// Wait for GSM Connection successfull
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
 
	vTaskDelay(DELAY_1SEC);
 
	// GROVE devices	
	void *compass = new(Compass, HMC5883_ADDR,SCALE8,46320);
	attachToBoard(board, compass, I2C);
 
	if(!configure(compass))
		UARTWrite(1,"3 axis Compass initialized properly\n\r");
	else
		UARTWrite(1,"ERROR!3 axis Compass not initialized!!\n\r");
 
	char msg[45];
	float x_axis,y_axis,z_axis;
	float totalf;
	float heading;
	while(1)
	{
		
		x_axis = get(compass,AXIS_X);
		if(readError()) {_dbgwrite("Error reading X\n");}
	
		y_axis = get(compass,AXIS_Y);
		if(readError()) {_dbgwrite("Error reading Y\n");}
		
		z_axis = get(compass,AXIS_Z);
		if(readError()) {_dbgwrite("Error reading Z\n");}
		
		vTaskDelay(DELAY_1SEC);
		
		totalf = x_axis * x_axis + y_axis * y_axis + z_axis * z_axis;
		
		sprintf(msg,"X %.2f milli-Gauss\n\r",x_axis);
		_dbgwrite(msg);
		
		sprintf(msg,"Y %.2f milli-Gauss\n\r",y_axis);
		_dbgwrite(msg);
		
		sprintf(msg,"Z %.2f milli-Gauss\n\r",z_axis);
		_dbgwrite(msg);
		
		sprintf(msg,"Total %.2f milli-Gauss^2\n\r",totalf);
		_dbgwrite(msg);
		
		if (totalf > FIELD_DETECTION_THSD){
			_dbgwrite("Detection\n");
			
			vTaskDelay(DELAY_200MSEC);
			
			SMSSend(PHONE_NUMBER,"Detection!",FALSE);
			while(LastExecStat() == OP_EXECUTION);
			if(LastExecStat() == OP_SUCCESS)
				_dbgwrite("SMS Sent!\n");
			else
				_dbgwrite("Error sending SMS\n");
		}
		
	}
}
