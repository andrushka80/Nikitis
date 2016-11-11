//common.h
#include "DATAlib.h"

//Debug printing 
#define 	DEBUG_PRINT_LEVEL0 //errors
#define 	DEBUG_PRINT_LEVEL1 //states
//#define		DEBUG_PRINT_LEVEL2 //measurements
//#define		DEBUG_PRINT_AT_CMD

#define		DEVICE_ID				"0000000001"

#define		PHONE_NUMBER			"0040722745715"

#define		APN_NAME				"live.vodafone.com"
#define		APN_USERNAME			"live"
#define		APN_PASSWORD			"vodafone"
#define		APN_MODEM_IP			DYNAMIC_IP
#define		APN_PRIMARY_DNS			DYNAMIC_IP
#define		APN_SECONDARY_DNS		DYNAMIC_IP


#define		HTTP_SERVER_NAME		"vicosh.ro"//"www.google.com" //
#define		HTTP_SERVER_PORT		"8080"//"80"//
#define		HTTP_REQUEST_GET_URL	"/"
#define		HTTP_REQUEST_URL		"/"

//#define		SEND_SMS_IS_ENABLED
#define		SEND_HTTP_IS_ENABLED
//#define		SENSOR_IS_ATTACHED

#define		FIELD_DETECTION_THSD	(float) 300000

#define		SERVER_REPORT_PERIOD	TCP_TIMER_DIV64K_30SEC

///////////////////////////////////////////


