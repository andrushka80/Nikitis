#include "debug_report_tools.h"
#include "user_config.h"
#include "sd_manager.h"
#include "timer.h"

char                txtmsg[256];
char                dbg_file_name[16];
int                 file_count = 0;
int                 dbg_sd_configured = 0;
unsigned long       timer_val;

	
void set_new_dbg_file()
{
	char  msg[64];
	sprintf(dbg_file_name,"Debug%d.txt",file_count);
	SDFileCreate(dbg_file_name);
	file_count++;
	sprintf(msg, "Created %s debug file\r\n", dbg_file_name);
	DBG_WRITE(msg, DBG_UART);
	
}
	
void print_dbg_file_size()
{
	unsigned long  file_size;
	char  msg[64];
	file_size = SDFileSize(dbg_file_name);
	sprintf(msg,"The debug file has the size of: %ld\r\n",file_size);
	DBG_WRITE(msg, DBG_UART);
}

int dbg_file_size_exceeded()
{
	unsigned long  file_size;
	file_size = SDFileSize(dbg_file_name);
	return (file_size > DEBUG_SD_FSIZE);
}

void goto_new_debug_dir()
{
	char dir_name[10];
	char msg[64];
	int dir_count = 0;
	do
	{
		if(dir_count)
		{
			SDDirBack();
		}
		sprintf(dir_name,"%d",dir_count);
		dir_count++;
	}while(SDDirChange(dir_name));
	
	SDDirCreate(dir_name);
	SDDirChange(dir_name);
	
	sprintf(msg,"Created dbg directory : %s\r\n",dir_name);
	DBG_WRITE(msg, DBG_UART);
	
}

void init_dbg_sd()
{
	SDDirCreate(DEBUG_SD_DIR);
	SDDirChange(DEBUG_SD_DIR);
	goto_new_debug_dir();
	set_new_dbg_file();
	sprintf(txtmsg,"Debug session initiated\r\n************************************************************************\r\n");
	SDFileAppend(dbg_file_name, txtmsg, strlen(txtmsg));
	dbg_sd_configured = 1;
}
	
void DBG_WRITE(char* dbgstr, DBG_TARGET_T mode)
{
	switch (mode)
	{
		case DBG_UART :
			// print on UART
			_dbgwrite(dbgstr);
			break;
		
		case DBG_UART_TS :
			// get Timer value
			timer_val = TickGet();
			//timer_val = TickGetDiv64K();
			sprintf(txtmsg, "%ld - %s", timer_val, dbgstr);
			
			// print on UART
			_dbgwrite(txtmsg);
			break;
		
		case DBG_SD :
			// write on SD
			if (dbg_sd_configured)
			{
				SDFileAppend(dbg_file_name, dbgstr, strlen(dbgstr));
			}
			else
			{
				sprintf(txtmsg,"ERROR! DEBUG file on SD card not configured!\n");
			}
			break;
			
		case DBG_SD_TS :
			// get Timer value
			timer_val = TickGet();
			//timer_val = TickGetDiv64K();
			sprintf(txtmsg, "%ld - %s", timer_val, dbgstr);
			
			// write on SD
			if (dbg_sd_configured)
			{
				SDFileAppend(dbg_file_name, txtmsg, strlen(txtmsg));
			}
			else
			{
				sprintf(txtmsg,"ERROR! DEBUG file on SD card not configured!\n");
			}
			break;
		
		case DBG_UART_SD :
			// print on UART
			_dbgwrite(dbgstr);
			
			// write on SD
			if (dbg_sd_configured)
			{
				SDFileAppend(dbg_file_name, dbgstr, strlen(dbgstr));
			}
			else
			{
				sprintf(txtmsg,"ERROR! DEBUG file on SD card not configured!\n");
			}
			break;
		
		case DBG_UART_SD_TS :
			// get Timer value
			timer_val = TickGet();
			//timer_val = TickGetDiv64K();
			sprintf(txtmsg, "%ld - %s", timer_val, dbgstr);
			
			// print on UART
			_dbgwrite(txtmsg);
			
			// write on SD
			if (dbg_sd_configured)
			{

				SDFileAppend(dbg_file_name, txtmsg, strlen(txtmsg));
			}
			else
			{
				sprintf(txtmsg,"ERROR! DEBUG file on SD card not configured!\n");
			}
			break;
	}
}
