// Processes raw measurements	
#include "taskFlyport.h"
#include "user_config.h"
 
void process_rssi(MEAS_REPORT_T*  measReport)
{ 

	int 	currRssi = 0;

	GSMSignalQualityUpdate();
	
	currRssi = LastSignalRssi();
	measReport->minRssi = currRssi;

}
