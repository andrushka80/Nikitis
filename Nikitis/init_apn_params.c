#include "taskFlyport.h"
#include "user_config.h"
 
void init_apn_params(APN_PARAMS_T* apnParams)
{ 

	strcpy(apnParams->apnName,APN_NAME);
	strcpy(apnParams->apnUsername,APN_USERNAME);
	strcpy(apnParams->apnPassword,APN_PASSWORD);
	strcpy(apnParams->modemIpAddr,APN_MODEM_IP);
	strcpy(apnParams->primaryDns,APN_PRIMARY_DNS);
	strcpy(apnParams->secondaryDns,APN_SECONDARY_DNS);
	
}
