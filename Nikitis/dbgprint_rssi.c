#include "taskFlyport.h"
#include "Hilo.h"
#include "HWlib.h"
#include "HILOlib.h"

void	dbgprint_rssi(void)
{
	char dbgMsg[50];
	
	sprintf(dbgMsg,"RSSI: %ddBm\n", LastSignalRssi());
	_dbgwrite(dbgMsg);
	
}
