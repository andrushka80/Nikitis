#include "taskFlyport.h"
#include "user_config.h"
	
void	read_new_line();

char 	line[20];
int		cfg_file_start;
int 	readInt;	
char	configData[MAX_CONFIG_FILE_SIZE];
//char    msg[64];

void read_cfg_data(CFG_PARAMS_T* cfgParams)

{ 

	int configDataLen = SDFileRead(CONFIG_SD_FILE,configData,MAX_CONFIG_FILE_SIZE);
	
	//If error reading SD, use default parameters
	if (configDataLen == 0)
	{
		_dbgwrite("Config file not present\n");
		
		strcpy(cfgParams -> deviceId, DEVICE_ID);	
		cfgParams -> apnProfile = APN_PROFILE;
		cfgParams -> httpServerProfile = HTTP_SERVER_PROFILE;
	}
	
	//if SD config file has been successfully read
	else 
	{
		_dbgwrite("Config file present\n");
		//sprintf(msg,"Read: %d characters\n",configDataLen);
		//_dbgwrite(msg);
		
		//_dbgwrite("Will print the entire content of the file: \n");
		//_dbgwrite(configData);
		
		cfg_file_start = 0;
		
		read_new_line();

		strcpy(cfgParams -> deviceId, line);
		// DBG
		//sprintf(msg,"Device ID is: %s\n",cfgParams -> deviceId);
		//_dbgwrite(msg);
		
		
		read_new_line();
		
		sscanf(line,"%d",&readInt);
		cfgParams -> apnProfile = readInt;
		// DBG
		//sprintf(msg,"APN profile is: %d\n",cfgParams -> apnProfile);
		//_dbgwrite(msg);
		
		
		read_new_line();
		
		sscanf(line,"%d",&readInt);
		cfgParams -> httpServerProfile = readInt;	
		// DBG
		//sprintf(msg,"HTTP profile is: %d\n",cfgParams -> httpServerProfile);
		//_dbgwrite(msg);
	}
	
	
}

void	read_new_line()
{
	
	int length = 0;	
	
	while (configData[cfg_file_start + length] != '\n'){
		//line[length] = configData[cfg_file_start + length];
		length++;
	}
	
	strncpy(line, &configData[cfg_file_start], length);
	line[length] = '\0';
	
	cfg_file_start += length + 1;//jump over '\n'

	
}
