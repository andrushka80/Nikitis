#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"

HTTP_REQ_T 		requestType = IDLE; 
BOOL			inExecution = TRUE;	
HTTP_ACTION_T	nextState = SETUP_APN;

	
void FlyportTask()
{	
	 
	float 			measBx, measBy, measBz, totalB2;
	void			*compass;
	
	#ifdef DEBUG_PRINT_LEVEL1
	char dbgMsg[100];
	#endif
	
	#ifdef SEND_HTTP_IS_ENABLED
	char 			apnName[] = APN_NAME;
	HTTP_PARAMS_T	*httpParams;
	char 			inBuff[MAX_INBUFF_LENGTH];
	init_http_params(httpParams);
	#endif
	
	vTaskDelay(DELAY_1SEC);
	
	// GROVE board
	void *board = new(Board);
 
	wait_until_registered();
 
	vTaskDelay(DELAY_1SEC);
 
	compass = config_compass(board);
	
	while(1)
	{
		
		#ifdef DEBUG_PRINT_LEVEL1
		sprintf(dbgMsg,"HTTP State: %d\n",nextState);
		_dbgwrite(dbgMsg);
		#endif
		
		measBx = get_compass_measurement(compass, AXIS_X);
		measBy = get_compass_measurement(compass, AXIS_Y);
		measBz = get_compass_measurement(compass, AXIS_Z);
		
		vTaskDelay(DELAY_200MSEC);
		
		totalB2 = VEC3D_MAG2(measBx,measBy,measBz);
		
		if (totalB2 > FIELD_DETECTION_THSD){
			_dbgwrite("Detection\n");
		
			vTaskDelay(DELAY_200MSEC);
			
			#ifdef SEND_SMS_IS_ENABLED
			send_meas_over_sms();
			vTaskDelay(DELAY_200MSEC);
			#endif
			
			#ifdef SEND_HTTP_IS_ENABLED
			if(LastExecStat() == OP_TIMEOUT)
			{
				// Something gone wrong! 
				// Restart state machine since GSM Task restarted GPRS Module!
				nextState = SETUP_APN;
			}
			
			switch(nextState)
            {
				
				case SETUP_APN :
				
					config_apn(apnName);
					break;
				
				case CHECK_CONNECTION :
				
					check_network_connection();
					break;
				
				case OPEN_SOCKET :
				
					open_http_socket(httpParams);
					break;
				
				case SEND_HTTP_REQ :
					
					send_http_request(httpParams, GET);
					break;
					
				case UPDATE_SOCK_STS :
				
					update_http_socket_status(httpParams);
					break;
				
				case READ_RSP :
				
					read_http_response(httpParams, inBuff);
					
					#ifdef DEBUG_PRINT_LEVEL1
					_dbgwrite(inBuff);
					#endif
					
					break;
				
				case CLOSE_SOCKET :
				
					close_http_socket(httpParams);
					break;
				
				default :
				
					break;
			}
			#endif	
		
			
		}
		
	}
}
