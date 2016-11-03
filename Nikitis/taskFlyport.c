#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"
#include "Hilo.h"

void FlyportTask()
{	
	 
	float 			measBx, measBy, measBz, totalB2;
	void			*compass	= NULL;
	int 			apnSuccess;
	TCP_SOCKET 		sockHttp;
	
	#ifdef DEBUG_PRINT_LEVEL1
	char dbgMsg[100];
	#endif

	BOOL			sendHttpMsg 	= FALSE;
	HTTP_ACTION_T	nextState 		= HTTP_IDLE;
	HTTP_ACTION_T	prevState 		= HTTP_IDLE;
	
	HTTP_PARAMS_T	*httpParams = NULL;
	httpParams = malloc(sizeof(HTTP_PARAMS_T));

	APN_PARAMS_T	*apnParams = NULL;
	apnParams = malloc(sizeof(APN_PARAMS_T));
	
	char 			inBuff[MAX_INBUFF_LENGTH];
	
	vTaskDelay(DELAY_1SEC);
	
	#ifdef SEND_HTTP_IS_ENABLED
	httpParams->sockHttp = &sockHttp;
	init_http_params(httpParams);
	init_apn_params(apnParams);
	
	config_apn(apnParams);
	
	while (LastExecStat() == OP_EXECUTION)
	{
		apnSuccess = wait_config_apn();
	}

	#endif
	
	// GROVE board
	void *board = new(Board);
 
	wait_until_registered();
 
	vTaskDelay(DELAY_1SEC);
 
	compass = config_compass(board);
	
	#ifdef DEBUG_PRINT_LEVEL0
	_dbgwrite("Starting measurement...\n");
	#endif
	
	//DEBUG!!!
	sendHttpMsg = TRUE;
		
	while(1)
	{
		
		measBx = get_compass_measurement(compass, AXIS_X);
		measBy = get_compass_measurement(compass, AXIS_Y);
		measBz = get_compass_measurement(compass, AXIS_Z);
		
		vTaskDelay(DELAY_200MSEC);
		
		totalB2 = VEC3D_MAG2(measBx,measBy,measBz);
		
		if (totalB2 > FIELD_DETECTION_THSD)
		{
			#ifdef DEBUG_PRINT_LEVEL0
			_dbgwrite("Detection\n");
			#endif
			
			vTaskDelay(DELAY_200MSEC);
			
			#ifdef SEND_SMS_IS_ENABLED
			send_meas_over_sms();
			vTaskDelay(DELAY_200MSEC);
			#endif
			
			#ifdef SEND_HTTP_IS_ENABLED
			//sendHttpMsg = TRUE;--uncomment this once HTTP debug is complete
			#endif
		}

		#ifdef SEND_HTTP_IS_ENABLED
		
		switch(nextState)
		{
			
			case SETUP_APN :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
				
				config_apn(apnParams);
				
				nextState = WAIT_SETUP_APN;
				prevState = SETUP_APN;
				
				break;
				
			case WAIT_SETUP_APN :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				nextState = wait_config_apn();
				prevState = WAIT_SETUP_APN;
				
				break;
			
			case CHECK_CONNECTION :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				UpdateConnStatus();
				GSMSignalQualityUpdate();
				
				nextState = WAIT_CHECK_CONNECTION;
				prevState = CHECK_CONNECTION;
				
				break;
			
			case WAIT_CHECK_CONNECTION :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				nextState = wait_check_network_connection();
				prevState = WAIT_CHECK_CONNECTION;
				
				dbgprint_ber_range();
				dbgprint_rssi();
				
				break;
			
			case OPEN_SOCKET :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				HTTPOpen(httpParams -> sockHttp, httpParams -> httpServName, httpParams -> httpServPort);
				
				nextState = WAIT_OPEN_SOCKET;
				prevState = OPEN_SOCKET;
				
				break;
				
			case WAIT_OPEN_SOCKET	:
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				nextState = wait_open_http_socket();
				prevState = WAIT_OPEN_SOCKET;
				
				break;
			
			case SEND_HTTP_REQ :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
				
				send_http_request(httpParams, GET);
				
				nextState = WAIT_SEND_HTTP_REQ;
				prevState = SEND_HTTP_REQ;
				
				break;
				
			case WAIT_SEND_HTTP_REQ :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				nextState = wait_send_http_request();
				prevState = WAIT_SEND_HTTP_REQ;
				
				break;
				
			case UPDATE_SOCK_STS :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				HTTPStatus(httpParams->sockHttp);
				
				nextState = WAIT_UPDATE_SOCK_STS;
				prevState = UPDATE_SOCK_STS;
				
				break;
				
			case WAIT_UPDATE_SOCK_STS :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				nextState = wait_update_http_socket_status();
				prevState = WAIT_UPDATE_SOCK_STS;
				
				break;
			
			case READ_RSP :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				read_http_response(httpParams, inBuff);
				
				nextState = WAIT_READ_RSP;
				prevState = READ_RSP;
				
				break;
				
			case WAIT_READ_RSP :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif

				nextState = wait_read_http_response();
				prevState = WAIT_READ_RSP;
				
				break;
			
			case CLOSE_SOCKET :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
				
				HTTPClose(httpParams->sockHttp);
				
				nextState = WAIT_CLOSE_SOCKET;
				prevState = CLOSE_SOCKET;
				
				break;
			
			case WAIT_CLOSE_SOCKET :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				nextState = wait_close_http_socket();
				prevState = WAIT_CLOSE_SOCKET;
				
				break;

			case HTTP_SESSION_END :
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
			
				//DEBUG ONLY
				//sendHttpMsg = FALSE;
				
				nextState = HTTP_IDLE;
				prevState = HTTP_SESSION_END;
				
				_dbgwrite(inBuff);
				
				break;
				
			case HTTP_IDLE 	:
				#ifdef DEBUG_PRINT_LEVEL1
				dbgprint_http_state(nextState, prevState);
				#endif
				
				if ((sendHttpMsg == TRUE) && (LastExecStat() != OP_EXECUTION))
				{
					
					if(LastExecStat() == OP_TIMEOUT)
					{
						// Restart state machine since GSM Task restarted GPRS Module!
						nextState = SETUP_APN;
					}
					else
					{
						nextState = CHECK_CONNECTION;
					}
				}
				
				prevState = HTTP_IDLE;
				
				break;
			
			default :
			
				break;
		}
		#endif	
		
	}
}
