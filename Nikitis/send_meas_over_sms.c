//Sends an SMS with the detection

#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"

void send_meas_over_sms(){

	SMSSend(PHONE_NUMBER,"Detection!",FALSE);
	while(LastExecStat() == OP_EXECUTION);
	if(LastExecStat() == OP_SUCCESS)
		_dbgwrite("SMS Sent!\n");
	else
		_dbgwrite("Error sending SMS\n");

}
