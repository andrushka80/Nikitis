// Processes raw measurements	
#include "taskFlyport.h"
#include "user_config.h"
#include "debug_report_tools.h"
 
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
		DBG_WRITE("Detection\r\n", DBG_UART_SD_TS);
		//DBG_WRITE("Detection\r\n", DBG_UART_SD);
		#endif
		
		measReport->numDetections++;

	}
}


