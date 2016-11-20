#include "taskFlyport.h"
#include "user_config.h"
 
void init_meas_report(MEAS_REPORT_T* measReport)
{ 

	measReport->numDetections 	= 0;
	measReport->numDetectedCars = 0;
	measReport->minRssi = MIN_RSSI;
	measReport->maxRssi = 0;

	strcpy(measReport->deviceId,DEVICE_ID);

	strcpy(measReport->operatorName, "UNKNOWN");
		
	strcpy(measReport->imeiNumber, "UNKNOWN");
	
	measReport->batteryLevel = MAX_BATTERY_LVL;
	
}
