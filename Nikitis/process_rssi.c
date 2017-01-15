// Processes raw measurements	
#include "taskFlyport.h"
#include "user_config.h"
#include "debug_report_tools.h"

int first_rssi_check = 0;
int num_rssi_checks = 0;
char dbgMsg[32];

void process_rssi(MEAS_REPORT_T*  measReport)
{
	int currRssi;
	
	if (first_rssi_check)
	{
		GSMSignalQualityUpdate(); // first measurement
		first_rssi_check = 0;
	}
	else
	{
		if (CheckRSSIAvailable())
		{
			ResetRSSIAvailable();
			currRssi = LastSignalRssi();
			sprintf(dbgMsg,"RSSI=%d dBm\r\n",currRssi);
			DBG_WRITE(dbgMsg, DBG_UART);
			num_rssi_checks++;
			GSMSignalQualityUpdate(); // new measurement
			if (currRssi < measReport->minRssi)
			{
				measReport->minRssi = currRssi;
				sprintf(dbgMsg,"Min RSSI updated to: %d dBm\r\n",currRssi);
				DBG_WRITE(dbgMsg, DBG_UART_SD_TS);
			}
		
			if (currRssi > measReport->maxRssi)
			{
				measReport->maxRssi = currRssi;
				sprintf(dbgMsg,"Max RSSI updated to: %d dBm\r\n",currRssi);
				DBG_WRITE(dbgMsg, DBG_UART_SD_TS);
			}
		}
	}
}

void init_RSSI_measurements(MEAS_REPORT_T*  measReport)
{
	ResetRSSIAvailable();
	num_rssi_checks = 0;
	first_rssi_check = 1;
	measReport->minRssi = 0;
	measReport->maxRssi = -113;
}

int get_num_RSSI_checks()
{
	return num_rssi_checks;
}
