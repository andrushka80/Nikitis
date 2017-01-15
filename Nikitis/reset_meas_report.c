#include "taskFlyport.h"
#include "user_config.h"
 
void reset_meas_report(MEAS_REPORT_T* measReport)
{ 
	
	measReport->numDetections 	= 0;
	measReport->numDetectedCars = 0;
	measReport->minRssi = 0;//initialize minimum value with maximum possible
	measReport->maxRssi = 0;//initialize maximum value with minimum possible
	
	measReport->batteryLevel = MAX_BATTERY_LVL;
	
	#ifdef SENSOR_IS_ATTACHED
	init_RSSI_measurements(measReport);
	#endif
	
}
