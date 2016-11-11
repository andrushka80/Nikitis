#include "taskFlyport.h"
#include "user_config.h"
 
void init_meas_report(MEAS_REPORT_T* measReport)
{ 

	measReport->numDetections 	= 0;
	measReport->numDetectedCars = 0;
	measReport->minRssi = MIN_RSSI;
	measReport->maxRssi = MAX_RSSI;

	strncpy(measReport->deviceId,DEVICE_ID,MAX_DEVICE_ID_LENGTH);
	measReport->deviceId[MAX_DEVICE_ID_LENGTH] = '\0';

	strncpy(measReport->operatorName, "UNKNOWN",MAX_OPERATOR_NAME_LEN);
	measReport->operatorName[MAX_OPERATOR_NAME_LEN] = '\0';
		
	strncpy(measReport->imeiNumber, "UNKNOWN",MAX_IMEI_LEN);
	measReport->imeiNumber[MAX_IMEI_LEN] = '\0';
	
	measReport->batteryLevel = MAX_BATTERY_LVL;
	
}
