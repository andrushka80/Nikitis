#include "taskFlyport.h"
#include "grovelib.h"
#include "oled.h"
#include "3axiscompass.h"
#include "user_config.h"
#include "Hilo.h"
#include "sd_manager.h"

#define USE_AND_OR
#include "timer.h"

#include "debug_report_tools.h"

char		jsonReport[MAX_JSON_PAYLOAD_LENGTH];
char		inBuff[MAX_INBUFF_LENGTH];

void	check_if_sd_present();

BOOL 	repeatInit = TRUE;
BOOL 	initRes = FALSE;
BOOL 	resultSD = FALSE;
BOOL    reset_modem = FALSE;
int     report_count = 0;
int 	sdError = 0;
int     rssi_decimation = RSSI_DECIMATION_STEP;

#ifdef SENSOR_IS_ATTACHED
int     compass_dbg_count = 0;
#endif

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
	
	char dbgMsg[100];

	
	HTTP_PARAMS_T	*httpParams = NULL;
	httpParams = malloc(sizeof(HTTP_PARAMS_T));
	
	APN_PARAMS_T	*apnParams = NULL;
	apnParams = malloc(sizeof(APN_PARAMS_T));

	MEAS_REPORT_T	*measReport = NULL;
	measReport = malloc(sizeof(MEAS_REPORT_T));
	
	CFG_PARAMS_T	*cfgParams = NULL;
	cfgParams = malloc(sizeof(CFG_PARAMS_T));


/////////////////////////////////

	// Disable all Analog channels
	int i;
	for(i = 0; i < 9; i++)
		ADCDetach(i);
	ADCAttach(2);	// Enable only Analog 2 channel (pin p5)
	
	// Enable onboard LEDs output
	IOInit(p31, out);
	IOInit(p32, out);
	IOPut(p32, off);
	IOPut(p31, off);
	
	// Enable switches with internal pullup resistors)
	IOInit(p9, inup);	// SW1
	IOInit(p11, inup);	// SW2
	
	vTaskDelay(DELAY_1SEC);
	check_if_sd_present();
	vTaskDelay(DELAY_1SEC);
	
	#ifdef SEND_HTTP_IS_ENABLED
	httpParams->sockHttp = &sockHttp;
	
	// read config data
	read_cfg_data(cfgParams);
	
	// init HTTP profiles
	init_http_profiles(httpProfiles, cfgParams);
	
	// init APN profiles
	init_apn_profiles(apnProfiles);
	
	// init MEASUREMENTS report
	init_meas_report(measReport, cfgParams);
	
	// init DEBUG on SD card
	init_dbg_sd();
	
	// print debug file size
	print_dbg_file_size();
	
	apnParams = &apnProfiles[cfgParams->apnProfile];
	
	httpParams = &httpProfiles[cfgParams->httpServerProfile];
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
	DBG_WRITE("Starting measurement...\n", DBG_UART);
	#endif
	
	tick = TickGetDiv64K();
	
	while(1)
	{
		if (reset_modem)
		{
			reset_modem = 0;
			sprintf(dbgMsg,"DBG: Resetting the modem. Pause 20 sec...\r\n");
			DBG_WRITE(dbgMsg, DBG_UART_SD);
			vTaskDelay(DELAY_1MIN);
			sprintf(dbgMsg,"DBG: Configuring APN...\r\n");
			DBG_WRITE(dbgMsg, DBG_UART_SD);
			config_apn(apnParams);
			while (LastExecStat() == OP_EXECUTION)
			{
				apnSuccess = wait_config_apn();
			}
			sprintf(dbgMsg,"DBG: APN Configured. Wait until registered...\r\n");
			DBG_WRITE(dbgMsg, DBG_UART_SD);
			wait_until_registered(measReport);
			sprintf(dbgMsg,"DBG: Registered!\r\n");
			DBG_WRITE(dbgMsg, DBG_UART_SD);
		}
		
		#ifdef SENSOR_IS_ATTACHED
		if (compass_dbg_count == (DEBUG_COMPASS_MEAS_PERIOD-1))
		{
			compass_dbg_count = 0;
			measBx = get_compass_measurement(compass, AXIS_X, 1);
			measBy = get_compass_measurement(compass, AXIS_Y, 1);
			measBz = get_compass_measurement(compass, AXIS_Z, 1);
		}
		else
		{
			compass_dbg_count++;
			measBx = get_compass_measurement(compass, AXIS_X, 0);
			measBy = get_compass_measurement(compass, AXIS_Y, 0);
			measBz = get_compass_measurement(compass, AXIS_Z, 0);
		}
		#endif
		
		//vTaskDelay(DELAY_200MSEC);
		
		#ifdef SENSOR_IS_ATTACHED
		process_measurements(measReport, measBx, measBy, measBz);
		if (httpNextState == HTTP_IDLE)
		{
			rssi_decimation--;
			if (rssi_decimation==0)
			{
				rssi_decimation = RSSI_DECIMATION_STEP;
				//process_rssi(measReport);
			}
		}
			
		#endif
		
		tock = TickGetDiv64K();
		
		timeToSendReport = (tock - tick >= SERVER_REPORT_PERIOD);
		
		if ((timeToSendReport) && (httpNextState == HTTP_IDLE))
		{
			report_count++; // increment report count
			
			sprintf(dbgMsg,"Sending the measurements report #%d. It contains %d detections and covers %d RSSI measurements.\r\n",report_count,measReport->numDetections,get_num_RSSI_checks());
			DBG_WRITE(dbgMsg, DBG_UART_SD_TS);
			
			//if ((get_num_RSSI_checks() == 0) || (report_count == 2))
			//if (get_num_RSSI_checks() == 0)
			if (0)
			{
				// Modem failure! Reset the modem.
				reset_modem = TRUE;
				sprintf(dbgMsg,"No RSSI detections during this reporting period. Reset the modem!\r\n");
				DBG_WRITE(dbgMsg, DBG_UART_SD_TS);
				HiloReset();
			}
			else
			{
				// Modem is OK. Send the report.
				sendHttpMsg = TRUE;
				jsonReportLength = build_json_report(jsonReport, measReport, httpParams);

				#ifdef SEND_SMS_IS_ENABLED
				send_meas_over_sms();
				vTaskDelay(DELAY_200MSEC);
				#endif
			
				DBG_WRITE(jsonReport, DBG_UART_SD);
				
				// Check if we should create another dbg file
				//if (dbg_file_size_exceeded())
				//{
					set_new_dbg_file();
				//}
					
			}
			
			reset_meas_report(measReport);//Need to restart measurement cycle
			tick = tock;
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
				
				DBG_WRITE(inBuff, DBG_UART);
				
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
						// httpNextState = CHECK_CONNECTION;
						httpNextState = SETUP_APN; // DBG: setup apn each time, in order to properly react to network disconnects
					}
				}
				
				httpPrevState = HTTP_IDLE;
				
				break;
			
			default :
			
				break;
		}
		
}

void check_if_sd_present()
{
    // Check for SD-Card detect signal
    if(IOGet(p11) == TRUE)
    {
        if(repeatInit == FALSE)
        {
            DBG_WRITE("SDUnMount()...\n", DBG_UART);
            resultSD = SDUnMount();
            repeatInit = TRUE;
        }   
		else
		{
			DBG_WRITE("We are here\n", DBG_UART);
		}
			
    }
    else
    {
        if(repeatInit == TRUE)
        {
            DBG_WRITE("SDInit()...", DBG_UART);
 
            // Init uSD Card on Eval Board
			// SDInit(int pin_sck, int pin_si, int pin_so, int pin_cs, int pin_cd, BYTE timeout);
			initRes = SDInit(p7, p3, p1, p5, p11, 15);
	
 
            if (initRes)
            {
                repeatInit = FALSE;
                DBG_WRITE("Initialized\n", DBG_UART);
            }
            else
            {
                sdError = SDGetErr();
                if (sdError == SD_NOT_PRESENT)
                {
                    DBG_WRITE("SD Card Not Present\n", DBG_UART);
                }   
                else if (sdError == SD_FS_NOT_INIT)
                {
                    DBG_WRITE("Generic error\n", DBG_UART);
                    while (1); // Lock here for generic error!
                }   
            }   
        }
	}
}
