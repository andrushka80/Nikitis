#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"
#include "Hilo.h"

#define USE_AND_OR
#include "timer.h"

char		jsonReport[MAX_JSON_PAYLOAD_LENGTH];
char		inBuff[MAX_INBUFF_LENGTH];

APN_PARAMS_T	apnProfiles[3];
HTTP_PARAMS_T	httpProfiles[3];

HTTP_ACTION_T	httpNextState 		= HTTP_IDLE;
HTTP_ACTION_T	httpPrevState 		= HTTP_IDLE;
BOOL			sendHttpMsg 		= FALSE;

void FlyportTask()
{	
	void			*compass	= NULL;
	
	float 			measBx = 0, measBy = 0, measBz = 0;

	int 			apnSuccess = 0;
	TCP_SOCKET 		sockHttp;
	
	long int		tick = 0, tock = 0;
	BOOL			timeToSendReport 	= FALSE;
	

	int				jsonReportLength;
	
	#ifdef DEBUG_PRINT_LEVEL1
	char dbgMsg[100];
	#endif
	
	HTTP_PARAMS_T	*httpParams = NULL;
	httpParams = malloc(sizeof(HTTP_PARAMS_T));
	
	APN_PARAMS_T	*apnParams = NULL;
	apnParams = malloc(sizeof(APN_PARAMS_T));

	MEAS_REPORT_T	*measReport = NULL;
	measReport = malloc(sizeof(MEAS_REPORT_T));

/////////////////////////////////
	
	vTaskDelay(DELAY_1SEC);
	
	init_meas_report(measReport);
	
	#ifdef SEND_HTTP_IS_ENABLED
	httpParams->sockHttp = &sockHttp;
	
	init_http_profiles(httpProfiles);
	init_apn_profiles(apnProfiles);
	
	apnParams = &apnProfiles[APN_PROFILE];
	
	httpParams = &httpProfiles[HTTP_SERVER_PROFILE];
	httpParams->sockHttp = &sockHttp;
	httpParams->sockHttp->number = INVALID_SOCKET;
	
	config_apn(apnParams);
	
	while (LastExecStat() == OP_EXECUTION)
	{
		apnSuccess = wait_config_apn();
	}

	#endif
	
	// GROVE board
	void *board = new(Board);
 
	//Wait for registration and get operator name & IMEI
	wait_until_registered(measReport);
	
	vTaskDelay(DELAY_1SEC);
 
	#ifdef SENSOR_IS_ATTACHED
	compass = config_compass(board);
	#endif
	
	#ifdef DEBUG_PRINT_LEVEL0
	_dbgwrite("Starting measurement...\n");
	#endif
	
	tick = TickGetDiv64K();
	
	while(1)
	{
		
		#ifdef SENSOR_IS_ATTACHED
		measBx = get_compass_measurement(compass, AXIS_X);
		measBy = get_compass_measurement(compass, AXIS_Y);
		measBz = get_compass_measurement(compass, AXIS_Z);
		#endif
		
		vTaskDelay(DELAY_200MSEC);
		
		#ifdef SENSOR_IS_ATTACHED
		process_measurements(measReport, measBx, measBy, measBz);
		#endif
		
		tock = TickGetDiv64K();
		
		timeToSendReport = (tock - tick >= SERVER_REPORT_PERIOD);
		
		if (timeToSendReport)
		{
			sendHttpMsg = TRUE;
			process_rssi(measReport);
			jsonReportLength = build_json_report(jsonReport, measReport, httpParams);
			reset_meas_report(measReport);//Need to restart measurement cycle
			tick = tock;
			
			#ifdef SEND_SMS_IS_ENABLED
			send_meas_over_sms();
			vTaskDelay(DELAY_200MSEC);
			#endif
			
			_dbgwrite(jsonReport);
			
		}

		#ifdef SEND_HTTP_IS_ENABLED
		// Run the HTTP state machine
		run_http_state_machine(apnParams,httpParams);
		#endif	
		
	}
}

void run_http_state_machine(APN_PARAMS_T  * apnParams, HTTP_PARAMS_T * httpParams)
{
	switch(httpNextState)
		{
			case SETUP_APN :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
				
				config_apn(apnParams);
				
				httpNextState = WAIT_SETUP_APN;
				httpPrevState = SETUP_APN;
				
				break;
				
			case WAIT_SETUP_APN :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				httpNextState = wait_config_apn();
				httpPrevState = WAIT_SETUP_APN;
				
				break;
			
			case CHECK_CONNECTION :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				UpdateConnStatus();
				
				httpNextState = WAIT_CHECK_CONNECTION;
				httpPrevState = CHECK_CONNECTION;
				
				break;
			
			case WAIT_CHECK_CONNECTION :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				httpNextState = wait_check_network_connection();
				httpPrevState = WAIT_CHECK_CONNECTION;
				
				//dbgprint_rssi();
				
				break;
			
			case OPEN_SOCKET :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				HTTPOpen(httpParams -> sockHttp, httpParams -> httpServName, httpParams -> httpServPort);
				
				httpNextState = WAIT_OPEN_SOCKET;
				httpPrevState = OPEN_SOCKET;
				
				break;
				
			case WAIT_OPEN_SOCKET	:
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				httpNextState = wait_open_http_socket();
				httpPrevState = WAIT_OPEN_SOCKET;
				
				break;
			
			case SEND_HTTP_REQ :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
				
				send_http_request(httpParams, HTTP_POST, jsonReport);
				
				httpNextState = WAIT_SEND_HTTP_REQ;
				httpPrevState = SEND_HTTP_REQ;
				
				break;
				
			case WAIT_SEND_HTTP_REQ :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				httpNextState = wait_send_http_request();
				httpPrevState = WAIT_SEND_HTTP_REQ;
				
				break;
				
			case UPDATE_SOCK_STS :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				HTTPStatus(httpParams->sockHttp);
				
				httpNextState = WAIT_UPDATE_SOCK_STS;
				httpPrevState = UPDATE_SOCK_STS;
				
				break;
				
			case WAIT_UPDATE_SOCK_STS :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				httpNextState = wait_update_http_socket_status();
				httpPrevState = WAIT_UPDATE_SOCK_STS;
				
				break;
			
			case READ_RSP :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				read_http_response(httpParams, inBuff);
				
				httpNextState = WAIT_READ_RSP;
				httpPrevState = READ_RSP;
				
				break;
				
			case WAIT_READ_RSP :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif

				httpNextState = wait_read_http_response();
				httpPrevState = WAIT_READ_RSP;
				
				break;
			
			case CLOSE_SOCKET :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
				
				HTTPClose(httpParams->sockHttp);
				
				httpNextState = WAIT_CLOSE_SOCKET;
				httpPrevState = CLOSE_SOCKET;
				
				break;
			
			case WAIT_CLOSE_SOCKET :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				httpNextState = wait_close_http_socket();
				httpPrevState = WAIT_CLOSE_SOCKET;
				
				break;

			case HTTP_SESSION_END :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
			
				sendHttpMsg = FALSE;
				
				httpNextState = HTTP_IDLE;
				httpPrevState = HTTP_SESSION_END;
				
				_dbgwrite(inBuff);
				
				break;
				
			case HTTP_IDLE 	:
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(httpNextState, httpPrevState);
				#endif
				
				if ((sendHttpMsg == TRUE) && (LastExecStat() != OP_EXECUTION))
				{
					
					if(LastExecStat() == OP_TIMEOUT)
					{
						// Restart state machine since GSM Task restarted GPRS Module!
						httpNextState = SETUP_APN;
					}
					else
					{
						httpNextState = CHECK_CONNECTION;
					}
				}
				
				httpPrevState = HTTP_IDLE;
				
				break;
			
			default :
			
				break;
		}
		
}
