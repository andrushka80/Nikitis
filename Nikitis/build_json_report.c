#include "taskFlyport.h"
#include "user_config.h"
 
int build_json_report(char* jsonReport, MEAS_REPORT_T* measReport, HTTP_PARAMS_T* httpParams)
{ 

	char 	strToWrite[50];
	int		index = 0;

	strcpy(strToWrite,"{\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"protocol\":\"v1\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"at\":\"now\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"device\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(&jsonReport[index],httpParams->devId);
	index += strlen(httpParams->devId);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"data\":{\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	strcpy(strToWrite,"\"0\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	strcpy(&jsonReport[index],measReport->deviceId);
	index += strlen(measReport->deviceId);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);

	strcpy(strToWrite,"\"1\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	strcpy(&jsonReport[index],measReport->imeiNumber);
	index += strlen(measReport->imeiNumber);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"16\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	sprintf(strToWrite,"%d",measReport->batteryLevel);
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"32\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	sprintf(strToWrite,"%d",measReport->numDetections);
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"64\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	sprintf(strToWrite,"%d",measReport->minRssi);
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"65\":\"");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	sprintf(strToWrite,"%d",measReport->maxRssi);
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\",\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"\"66\":");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);	
	
	strcpy(&jsonReport[index],measReport->operatorName);
	index += strlen(measReport->operatorName);
	
	strcpy(strToWrite,"\n");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);
	
	strcpy(strToWrite,"},\n\"checksum\":\"\"\n}\n\0");
	strcpy(&jsonReport[index],strToWrite);
	index += strlen(strToWrite);

	return(index);
	
}
