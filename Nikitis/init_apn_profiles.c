#include "taskFlyport.h"

typedef enum 
{
	VODAFONE_RO 	= 0,
	ORANGE_RO  		= 1,
	TELEKOM_RO 		= 2
} APN_PROFILE_IDX_T;
 
void init_apn_profiles(APN_PARAMS_T* apnProfilesPtr)
{ 

	strcpy(apnProfilesPtr[VODAFONE_RO].apnName, "live.vodafone.com");
	strcpy(apnProfilesPtr[VODAFONE_RO].apnUsername, "live");
	strcpy(apnProfilesPtr[VODAFONE_RO].apnPassword, "vodafone");
	strcpy(apnProfilesPtr[VODAFONE_RO].modemIpAddr, DYNAMIC_IP);
	strcpy(apnProfilesPtr[VODAFONE_RO].primaryDns, DYNAMIC_IP);
	strcpy(apnProfilesPtr[VODAFONE_RO].secondaryDns, DYNAMIC_IP);

	strcpy(apnProfilesPtr[ORANGE_RO].apnName, "net");
	strcpy(apnProfilesPtr[ORANGE_RO].apnUsername, "");
	strcpy(apnProfilesPtr[ORANGE_RO].apnPassword, "");
	strcpy(apnProfilesPtr[ORANGE_RO].modemIpAddr, DYNAMIC_IP);
	strcpy(apnProfilesPtr[ORANGE_RO].primaryDns, DYNAMIC_IP);
	strcpy(apnProfilesPtr[ORANGE_RO].secondaryDns, DYNAMIC_IP);

	strcpy(apnProfilesPtr[TELEKOM_RO].apnName, "broadband");
	strcpy(apnProfilesPtr[TELEKOM_RO].apnUsername, "");
	strcpy(apnProfilesPtr[TELEKOM_RO].apnPassword, "");
	strcpy(apnProfilesPtr[TELEKOM_RO].modemIpAddr, DYNAMIC_IP);
	strcpy(apnProfilesPtr[TELEKOM_RO].primaryDns, DYNAMIC_IP);
	strcpy(apnProfilesPtr[TELEKOM_RO].secondaryDns,DYNAMIC_IP);

}
