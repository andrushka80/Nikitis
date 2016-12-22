#include "taskFlyport.h"
#include "user_config.h"
	
void	read_new_line();

char 	line[20];
int		start;
int 	readInt;	
char	configData[MAX_CONFIG_FILE_SIZE];

void read_cfg_data(CFG_PARAMS_T* cfgParams)

{ 

	int configDataLen = SDFileRead(CONFIG_SD_FILE,configData,MAX_CONFIG_FILE_SIZE);
	
	//If error reading SD, use default parameters
	if (configDataLen == 0)
	{
		strcpy(cfgParams -> deviceId, DEVICE_ID);	
		cfgParams -> apnProfile = APN_PROFILE;
		cfgParams -> httpServerProfile = HTTP_SERVER_PROFILE;
	}
	
	//if SD config file has been successfully read
	else 
	{
		start = 0;
		
		read_new_line();
		
		strcpy(cfgParams -> deviceId, line);
		
		read_new_line();
		
		sscanf(line,"%d",&readInt);
		cfgParams -> apnProfile = readInt;

		read_new_line();
		
		sscanf(line,"%d",&readInt);
		cfgParams -> httpServerProfile = readInt;	
	}
	
	
}

void	read_new_line()
{
	
	int length = 0;	
	
	while (configData[start + length] != '\n'){
		length++;
	}
	
	strncpy(line, configData[start], length);
	line[length] = '\0';
	
	start += length + 1;//jump over '\n'

	
}
