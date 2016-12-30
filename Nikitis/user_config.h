//common.h
#include "DATAlib.h"

//Debug printing 
#define 	DEBUG_PRINT_LEVEL0 //errors
#define 	DEBUG_PRINT_LEVEL1 //states
//#define		DEBUG_PRINT_LEVEL2 //measurements
//#define		DEBUG_PRINT_AT_CMD

#define 	CONFIG_SD_FILE		"Config.txt"
#define 	DEBUG_SD_DIR		"Debug"

#define		DEVICE_ID				"0000000001" //!! This is the default DEVICE_ID value to be set in case SD is not present

#define		PHONE_NUMBER			"0040722745715"

//0 - VODAFONE RO, 1 - ORANGE RO, 2 - TELEKOM RO
#define			APN_PROFILE				0        //!! This is the default APN_PROFILE value to be set in case SD is not present

//0 - CARRIOTS, 1 - VICOSH.RO, 2 - GOOGLE
#define		HTTP_SERVER_PROFILE			0        //!! This is the default HTTP_SERVER_PROFILE value to be set in case SD is not present

//#define		SEND_SMS_IS_ENABLED
#define		SEND_HTTP_IS_ENABLED
#define		SENSOR_IS_ATTACHED

#define		FIELD_DETECTION_THSD	(float) 300000

#define		SERVER_REPORT_PERIOD	TCP_TIMER_DIV64K_30SEC

///////////////////////////////////////////


