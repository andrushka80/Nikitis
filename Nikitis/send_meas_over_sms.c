//Sends an SMS with the detection

#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"
#include "debug_report_tools.h"

void send_meas_over_sms(){

	SMSSend(PHONE_NUMBER,"Detection!",FALSE);
	while(LastExecStat() == OP_EXECUTION);
	if(LastExecStat() == OP_SUCCESS)
		DBG_WRITE("SMS Sent!\n", DBG_UART);
	else
		DBG_WRITE("Error sending SMS\n", DBG_UART);

}
