#include "taskFlyport.h"
#include "user_config.h"
 
void reset_meas_report(MEAS_REPORT_T* measReport)
{ 
	
	measReport->numDetections 	= 0;
	measReport->numDetectedCars = 0;
	measReport->minRssi = MAX_RSSI;//initialize minimum value with maximum possible
	measReport->maxRssi = MIN_RSSI;//initialize maximum value with minimum possible
	
	measReport->batteryLevel = MAX_BATTERY_LVL;
	
}
