#include "taskFlyport.h"
#include "Hilo.h"
#include "HILOlib.h"
#include "HWlib.h"

void	dbgprint_ber_range(void)

{
	char 			dbgMsg[50];
	BER_MINMAX_T	berRange;
	
	berRange = get_ber_measurement();	
	
	sprintf(dbgMsg,"BER: %.2f%% - %.2f%%\n", (double) berRange.minValue/100, (double) berRange.maxValue/100);
	
	_dbgwrite(dbgMsg);
	
}
