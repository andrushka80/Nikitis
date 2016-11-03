// Returns the name of the state as a string	
#include "taskFlyport.h"
#include "user_config.h"
 
char* get_http_state_name(int nextState){ 

	switch(nextState)
		{
			case SETUP_APN :
				return("SETUP_APN");
			
			case WAIT_SETUP_APN :
				return("WAIT_SETUP_APN");
			
			case CHECK_CONNECTION :
				return("CHECK_CONNECTION");
			
			case WAIT_CHECK_CONNECTION :
				return("WAIT_CHECK_CONNECTION");
			
			case OPEN_SOCKET :
				return("OPEN_SOCKET");
			
			case WAIT_OPEN_SOCKET :
				return("WAIT_OPEN_SOCKET");
			
			case SEND_HTTP_REQ :
				return("SEND_HTTP_REQ");
			
			case WAIT_SEND_HTTP_REQ :
				return("WAIT_SEND_HTTP_REQ");
			
			case UPDATE_SOCK_STS :
				return("UPDATE_SOCK_STS");
			
			case WAIT_UPDATE_SOCK_STS :
				return("WAIT_UPDATE_SOCK_STS");
			
			case READ_RSP :
				return("READ_RSP");
			
			case WAIT_READ_RSP :
				return("WAIT_READ_RSP");
			
			case CLOSE_SOCKET :
				return("CLOSE_SOCKET");
			
			case WAIT_CLOSE_SOCKET :
				return("WAIT_CLOSE_SOCKET");
			
			case HTTP_IDLE :
				return("HTTP_IDLE");
			
			case HTTP_SESSION_END :
				return("HTTP_SESSION_END");
			
			default	:
				return("UNKNOWN");
			
	}
	
}
