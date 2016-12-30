#include "taskFlyport.h"
#include "user_config.h"

typedef enum 
{
	CARRIOTS 		= 0,
	VICOSH_RO 		= 1,
	GOOGLE_COM 		= 2
} HTTP_PROFILE_IDX_T;

void init_http_profiles(HTTP_PARAMS_T* httpProfilesPtr, CFG_PARAMS_T* cfgParams)
{ 

	strcpy(httpProfilesPtr[CARRIOTS].httpServName, "api.carriots.com");
	strcpy(httpProfilesPtr[CARRIOTS].httpServPort, "80");
	strcpy(httpProfilesPtr[CARRIOTS].requestGetURL, "/");
	strcpy(httpProfilesPtr[CARRIOTS].requestURL, "api.carriots.com/streams");
	strcpy(httpProfilesPtr[CARRIOTS].apikey, "76b81a858602a65c55325b29ad2c43b31d15c51ef3963caa594e24ff804a59f6");
	sprintf(httpProfilesPtr[CARRIOTS].devId, "%s@EOS_Carriots_test.EOS_Carriots_test", cfgParams->deviceId);
	strcpy(httpProfilesPtr[CARRIOTS].postHeader, "Accept: */*\r\ncarriots.apikey:%s\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded");
	httpProfilesPtr[CARRIOTS].sockHttp = NULL;
	
	strcpy(httpProfilesPtr[VICOSH_RO].httpServName, "vicosh.ro");
	strcpy(httpProfilesPtr[VICOSH_RO].httpServPort, "8080");
	strcpy(httpProfilesPtr[VICOSH_RO].requestGetURL, "/");
	strcpy(httpProfilesPtr[VICOSH_RO].requestURL, "api.carriots.com/streams");
	strcpy(httpProfilesPtr[VICOSH_RO].apikey, "76b81a858602a65c55325b29ad2c43b31d15c51ef3963caa594e24ff804a59f6");
	sprintf(httpProfilesPtr[VICOSH_RO].devId, "%s@EOS_Carriots_test.EOS_Carriots_test", cfgParams->deviceId);
	strcpy(httpProfilesPtr[VICOSH_RO].postHeader, "Accept: */*\r\ncarriots.apikey:%s\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded");
	httpProfilesPtr[VICOSH_RO].sockHttp = NULL;

	strcpy(httpProfilesPtr[GOOGLE_COM].httpServName, "www.google.com");
	strcpy(httpProfilesPtr[GOOGLE_COM].httpServPort, "80");
	strcpy(httpProfilesPtr[GOOGLE_COM].requestGetURL, "/");
	strcpy(httpProfilesPtr[GOOGLE_COM].requestURL, "/");
	strcpy(httpProfilesPtr[GOOGLE_COM].apikey, "");
	strcpy(httpProfilesPtr[GOOGLE_COM].devId, cfgParams->deviceId);
	strcpy(httpProfilesPtr[GOOGLE_COM].postHeader, "");
	httpProfilesPtr[GOOGLE_COM].sockHttp = NULL;
}
