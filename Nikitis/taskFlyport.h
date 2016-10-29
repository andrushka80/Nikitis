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

#define		MAX_INBUFF_LENGTH		1500

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
	SETUP_APN 			= 0,
	CHECK_CONNECTION 	= 1,
	OPEN_SOCKET 		= 2,
	SEND_HTTP_REQ 		= 3,
	UPDATE_SOCK_STS 	= 4,
	READ_RSP			= 5,
	CLOSE_SOCKET		= 6
} HTTP_ACTION_T;

typedef struct {
   char  		httpServName[50];
   char  		httpServPort[5];
   char  		requestGetURL[50];
   char  		requestURL[50];
   TCP_SOCKET	sockHttp;
} HTTP_PARAMS_T;


//	RTOS components - Semaphore and queues
extern xQueueHandle xQueue;
extern xSemaphoreHandle xSemFrontEnd;
extern xSemaphoreHandle xSemHW;

//	FrontEnd variables
extern int xFrontEndStat;
extern int xErr;

extern BOOL inExecution;
extern HTTP_ACTION_T nextState;

void FlyportTask();

void wait_until_registered(void);
void* config_compass(void* board);
float get_compass_measurement(void* compass, char axis);
void send_meas_over_sms(void);

#ifdef SEND_HTTP_IS_ENABLED
void config_apn(char* apnName);
void check_network_connection(void);
void open_http_socket(HTTP_PARAMS_T *httpParams);
void send_http_request(HTTP_PARAMS_T *httpParams, HTTP_REQ_T requestType);
void update_http_socket_status(HTTP_PARAMS_T *httpParams);
void read_http_response(HTTP_PARAMS_T *httpParams, char* inBuff);
void close_http_socket(HTTP_PARAMS_T *httpParams);
void init_http_params(HTTP_PARAMS_T *httpParams);
#endif
