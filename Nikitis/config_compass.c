//Initialized and configures the 3-axis compass

#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"
#include "debug_report_tools.h"

void* config_compass(void *board){

	void	*compass;
	
	// GROVE devices	
	compass = new(Compass, HMC5883_ADDR,SCALE8,46320);
	attachToBoard(board, compass, I2C);
	
	if(!configure(compass)){
		DBG_WRITE("3 axis Compass initialized properly\n\r", DBG_UART);
	}
	else{
		DBG_WRITE("ERROR!3 axis Compass not initialized!!\n\r", DBG_UART);
	}
	
	return compass;
	
}
