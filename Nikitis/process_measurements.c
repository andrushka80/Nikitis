// Processes raw measurements	
#include "taskFlyport.h"
#include "user_config.h"
 
void process_measurements(MEAS_REPORT_T*  measReport, float measBx, float measBy, float measBz)
{ 

	float 	totalB2 = 0;
	BOOL	carIsDetected = FALSE;
	//int 	currRssi = 0;

	//GSMSignalQualityUpdate();
	
	totalB2 = VEC3D_MAG2(measBx,measBy,measBz);
	carIsDetected = (totalB2 > FIELD_DETECTION_THSD);
	
	if (carIsDetected)
	{
		#ifdef DEBUG_PRINT_LEVEL0
		_dbgwrite("Detection\n");
		#endif
		
		measReport->numDetections++;

	}
	
	//currRssi = LastSignalRssi();
	//if (currRssi < measReport->minRssi)
	//{
	//	measReport->minRssi = currRssi;
	//}
	//
	//if (currRssi > measReport->maxRssi)
	//{
	//	measReport->maxRssi = currRssi;
	//}

}
