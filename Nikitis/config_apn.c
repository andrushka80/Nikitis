#include "taskFlyport.h"
#include "user_config.h"
#include "DATAlib.h"

void	config_apn(APN_PARAMS_T* apnParams)

{
	APNConfig(apnParams->apnName,apnParams->apnUsername,apnParams->apnPassword,apnParams->modemIpAddr,apnParams->primaryDns,apnParams->secondaryDns);
	
}
