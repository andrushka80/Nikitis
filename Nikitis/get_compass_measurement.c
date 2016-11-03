//Gets one measurement from the 3-axis compass

#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"

float get_compass_measurement(void *compass, char axis){

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
		sprintf(msg, "Error reading %c\n", axisDisplay);
		_dbgwrite(msg);
	}
	else {
		#ifdef 	DEBUG_PRINT_LEVEL2
		sprintf(msg,"%c %.2f milli-Gauss\n\r",axisDisplay, output);
		_dbgwrite(msg);
		#endif
	}
	#endif

	return output;
	
}
