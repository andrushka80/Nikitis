//Initialized and configures the 3-axis compass

#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"

void* config_compass(void *board){

	void	*compass;
	
	// GROVE devices	
	compass = new(Compass, HMC5883_ADDR,SCALE8,46320);
	attachToBoard(board, compass, I2C);
	
	if(!configure(compass)){
		_dbgwrite("3 axis Compass initialized properly\n\r");
	}
	else{
		_dbgwrite("ERROR!3 axis Compass not initialized!!\n\r");
	}
	
	return compass;
	
}
