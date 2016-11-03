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

#define		MAX_INBUFF_LENGTH			1500
#define		MAX_HTTP_SERVER_NAME_LEN	50
#define		MAX_HTTP_SERVER_PORT_LEN	5


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
	HTTP_IDLE					= 15
} HTTP_ACTION_T;

typedef struct {
   char  		httpServName[MAX_HTTP_SERVER_NAME_LEN];
   char  		httpServPort[MAX_HTTP_SERVER_PORT_LEN];
   char  		requestGetURL[MAX_HTTP_SERVER_NAME_LEN];
   char  		requestURL[MAX_HTTP_SERVER_NAME_LEN];
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

//	RTOS components - Semaphore and queues
extern xQueueHandle xQueue;
extern xSemaphoreHandle xSemFrontEnd;
extern xSemaphoreHandle xSemHW;

//	FrontEnd variables
extern int xFrontEndStat;
extern int xErr;

void FlyportTask();

void wait_until_registered(void);
void* config_compass(void* board);
float get_compass_measurement(void* compass, char axis);
void send_meas_over_sms(void);

//#ifdef SEND_HTTP_IS_ENABLED
int wait_config_apn(void);
int wait_check_network_connection(void);
int wait_open_http_socket(void);
int wait_send_http_request(void);
int wait_update_http_socket_status(void);
int wait_read_http_response(void);
int wait_close_http_socket(void);

void read_http_response(HTTP_PARAMS_T*, char*);
void send_http_request(HTTP_PARAMS_T*, HTTP_REQ_T);

void dbgprint_http_state(int, int);
void init_http_params(HTTP_PARAMS_T*);
char* get_http_state_name(int);

void	dbgprint_ber_range(void);
void	dbgprint_rssi(void);

void 	init_apn_params(APN_PARAMS_T*);
void	config_apn(APN_PARAMS_T*);

//#endif
