//Gets one measurement from the 3-axis compass

#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"
#include "debug_report_tools.h"

float 	get_compass_measurement(void* compass, char axis, BOOL log_meas){

	char  msg[45];
	char  axisDisplay;

	
	switch (axis) {
		
		case AXIS_X: 
			axisDisplay = 'x';
			break;
		
		case AXIS_Y:	
			axisDisplay = 'y';
			break;
			
		case AXIS_Z: 
			axisDisplay = 'z';
			break;
			
		default:
			axisDisplay = 't';
			break;
	}

	float output = get(compass,axis);
		
	#ifdef 	DEBUG_PRINT_LEVEL0
	if(readError()) {
		sprintf(msg, "Error reading %c\r\n", axisDisplay);
		DBG_WRITE(msg, DBG_UART_SD_TS);
		//DBG_WRITE(msg, DBG_UART_SD);
	}
	else {
		#ifdef 	DEBUG_PRINT_LEVEL2
		if (log_meas)
		{
			sprintf(msg,"%c %.2f milli-Gauss\r\n",axisDisplay, output);
			DBG_WRITE(msg, DBG_SD_TS);
			//DBG_WRITE(msg, DBG_SD);
		}
		#endif
	}
	#endif

	return output;
	
}
