#include "taskFlyport.h"
#include "Hilo.h"
#include "HWlib.h"
#include "HILOlib.h"
#include "debug_report_tools.h"

void	dbgprint_rssi(void)
{
	char dbgMsg[50];
	
	sprintf(dbgMsg,"RSSI: %ddBm\n", LastSignalRssi());
	DBG_WRITE(dbgMsg, DBG_UART);
	
}
