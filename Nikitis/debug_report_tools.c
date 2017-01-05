#include "debug_report_tools.h"
#include "user_config.h"
#include "sd_manager.h"
#include "timer.h"

char                txtmsg[256];
int                 dbg_sd_configured = 0;
unsigned long       timer_val;
	
void init_dbg_sd()
{
	SDDirCreate(DEBUG_SD_DIR);
	SDDirChange(DEBUG_SD_DIR);
	if (!SDFileCheck(DEBUG_SD_FNAME))
	{
		SDFileCreate(DEBUG_SD_FNAME);
	}
	sprintf(txtmsg,"Debug session initiated\r\n************************************************************************\r\n");
	SDFileAppend(DEBUG_SD_FNAME, txtmsg, strlen(txtmsg));
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
		
		case DBG_SD :
			// write on SD
			if (dbg_sd_configured)
			{
				SDFileAppend(DEBUG_SD_FNAME, dbgstr, strlen(dbgstr));
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
				SDFileAppend(DEBUG_SD_FNAME, txtmsg, strlen(txtmsg));
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
				SDFileAppend(DEBUG_SD_FNAME, dbgstr, strlen(dbgstr));
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

				SDFileAppend(DEBUG_SD_FNAME, txtmsg, strlen(txtmsg));
			}
			else
			{
				sprintf(txtmsg,"ERROR! DEBUG file on SD card not configured!\n");
			}
			break;
	}
}

