//#ifndef __TASKFLY_H
//#define __TASKFLY_H
#include "HWlib.h"
#include "INTlib.h"
#include "string.h"
#include "RTCClib.h"
#include "HILOlib.h"
#include "SMSlib.h"
#include "CALLlib.h"
#include "LowLevelLib.h"
#include "DATAlib.h"
#include "TCPlib.h"
#include "HTTPlib.h"
#include "SMTPlib.h"
#include "FTPlib.h"
#include "FSlib.h"

#include "SPIFlash.h"

//one second equals 100 cycles
#define		DELAY_1SEC				100
#define		DELAY_200MSEC			20

//Various TCP timer values
#define		TCP_TIMER_DIV64K_1SEC			0x0001
#define		TCP_TIMER_DIV64K_10SEC			0x000A
#define		TCP_TIMER_DIV64K_30SEC			0x001F
#define		TCP_TIMER_DIV64K_1MIN			0x0039
#define		TCP_TIMER_DIV64K_2MIN			0x0072
#define		TCP_TIMER_DIV64K_5MIN			0x011E
#define		TCP_TIMER_DIV64K_10MIN			0x023C
#define		TCP_TIMER_DIV64K_15MIN			0x035A
#define		TCP_TIMER_DIV64K_30MIN			0x06B4
#define		TCP_TIMER_DIV64K_1HR			0x0D69
#define		TCP_TIMER_DIV64K_12HR			0xA0EE

#define		MAX_INBUFF_LENGTH			3000
#define		MAX_HTTP_SERVER_NAME_LEN	50
#define		MAX_HTTP_SERVER_PORT_LEN	6
#define		MAX_HTTP_HEADER_LEN         200
#define		MAX_JSON_PAYLOAD_LENGTH		3000
#define		MAX_OPERATOR_NAME_LEN		32
#define		MAX_IMEI_LEN				32
#define		MAX_APIKEY_LEN              100
#define     MAX_CARRIOTS_DEV_ID         64
#define		MAX_POST_HEADER_LEN			150

#define		MAX_DEVICE_ID_LENGTH		64

#define		MIN_RSSI					-113
#define		MAX_RSSI					-51

#define		MIN_BATTERY_LVL				0
#define		MAX_BATTERY_LVL				100


#define		VEC3D_MAG2(x,y,z) (x*x + y*y + z*z)

typedef enum 
{
	IDLE = -1,
	GET  = 0,
	POST_NO_ADD = 1,
	POST_ADD = 2
} HTTP_REQ_T;


typedef enum 
{
	SETUP_APN 				= 0,
	WAIT_SETUP_APN			= 1,
	CHECK_CONNECTION 		= 2,
	WAIT_CHECK_CONNECTION	= 3,
	OPEN_SOCKET 			= 4,
	WAIT_OPEN_SOCKET		= 5,
	SEND_HTTP_REQ 			= 6,
	WAIT_SEND_HTTP_REQ		= 7,
	UPDATE_SOCK_STS 		= 8,
	WAIT_UPDATE_SOCK_STS	= 9,
	READ_RSP				= 10,
	WAIT_READ_RSP			= 11,
	CLOSE_SOCKET			= 12,
	WAIT_CLOSE_SOCKET		= 13,
	HTTP_SESSION_END		= 14,
	HTTP_IDLE				= 15
} HTTP_ACTION_T;

typedef enum 
{
	APN_NAME 				= 0,
	APN_USERNAME			= 1,
	APN_PASSWORD	 		= 2,
	APN_MODEM_IP			= 3,
	APN_PRIMARY_DNS			= 4,
	APN_SECONDARY_DNS		= 5
} APN_CONFIG_T;

typedef struct {
   char  		httpServName[MAX_HTTP_SERVER_NAME_LEN];
   char  		httpServPort[MAX_HTTP_SERVER_PORT_LEN];
   char  		requestGetURL[MAX_HTTP_SERVER_NAME_LEN];
   char  		requestURL[MAX_HTTP_SERVER_NAME_LEN];
   char  		apikey[MAX_APIKEY_LEN];
   char         devId[MAX_CARRIOTS_DEV_ID];
   char			postHeader[MAX_POST_HEADER_LEN];
   TCP_SOCKET	*sockHttp;
} HTTP_PARAMS_T;

typedef struct {
   char  		apnName[MAX_HTTP_SERVER_NAME_LEN];
   char  		apnUsername[MAX_HTTP_SERVER_PORT_LEN];
   char  		apnPassword[MAX_HTTP_SERVER_NAME_LEN];
   char  		modemIpAddr[MAX_HTTP_SERVER_NAME_LEN];
   char  		primaryDns[MAX_HTTP_SERVER_NAME_LEN];
   char  		secondaryDns[MAX_HTTP_SERVER_NAME_LEN];
} APN_PARAMS_T;

typedef struct {
   int  		numDetections;
   int			numDetectedCars;
   int			minRssi;
   int			maxRssi;
   int			batteryLevel;
   char			deviceId[MAX_DEVICE_ID_LENGTH];
   char			operatorName[MAX_OPERATOR_NAME_LEN];
   char			imeiNumber[MAX_IMEI_LEN];
} MEAS_REPORT_T;

//	RTOS components - Semaphore and queues
extern xQueueHandle xQueue;
extern xSemaphoreHandle xSemFrontEnd;
extern xSemaphoreHandle xSemHW;

//	FrontEnd variables
extern int xFrontEndStat;
extern int xErr;

void FlyportTask();

void 	wait_until_registered(MEAS_REPORT_T*);
void* 	config_compass(void* board);
float 	get_compass_measurement(void* compass, char axis);
void 	send_meas_over_sms(void);
void 	process_measurements(MEAS_REPORT_T*, float, float, float);
void 	process_rssi(MEAS_REPORT_T*);
void 	init_meas_report(MEAS_REPORT_T*);
void 	reset_meas_report(MEAS_REPORT_T*);
int 	build_json_report(char*, MEAS_REPORT_T*, HTTP_PARAMS_T* httpParams);

//#ifdef SEND_HTTP_IS_ENABLED
int wait_config_apn(void);
int wait_check_network_connection(void);
int wait_open_http_socket(void);
int wait_send_http_request(void);
int wait_update_http_socket_status(void);
int wait_read_http_response(void);
int wait_close_http_socket(void);

void read_http_response(HTTP_PARAMS_T*, char*);
void send_http_request(HTTP_PARAMS_T*, HTTP_REQ_T, char*);

void dbgprint_http_state(int, int);
void init_http_profiles(HTTP_PARAMS_T* httpProfiles);
char* get_http_state_name(int);
void run_http_state_machine(APN_PARAMS_T  * apnParams, HTTP_PARAMS_T * httpParams);

void	dbgprint_ber_range(void);
void	dbgprint_rssi(void);

void 	init_apn_profiles(APN_PARAMS_T* apnProfiles);
void	config_apn(APN_PARAMS_T*);

//#endif
