/** \file 3axiscompass.c
 *  \brief Grove devices support library 
 */

/**
\addtogroup Grove devices
@{
*/
/* **************************************************************************																					
 *                                OpenPicus                 www.openpicus.com
 *                                                            italian concept
 * 
 *            openSource wireless Platform for sensors and Internet of Things	
 * **************************************************************************
 *  FileName:        3axisCompass.c
 *  Module:          FlyPort WI-FI - FlyPort ETH
 *  Compiler:        Microchip C30 v3.12 or higher
 *
 *  Author               Rev.    Date              Comment
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Vicca Davide	     1.0     2/09/2012		   First release  
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  Software License Agreement
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  This is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License (version 2) as published by 
 *  the Free Software Foundation AND MODIFIED BY OpenPicus team.
 *  
 *  ***NOTE*** The exception to the GPL is included to allow you to distribute
 *  a combined work that includes OpenPicus code without being obliged to 
 *  provide the source code for proprietary components outside of the OpenPicus
 *  code. 
 *  OpenPicus software is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details. 
 * 
 * 
 * Warranty
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * WE ARE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 **************************************************************************/
#include <math.h>
#include "taskFlyport.h"
#include "grovelib.h"
#include "3axisCompass.h"


struct Interface *attachSensorToI2CBus(void *,int,int);
int set_register(BYTE,BYTE, BYTE);
BYTE read_register(BYTE,BYTE);

static float scaling_factor = 1.3;
/**
 * struct Compass - Struct Compass Grove Sensor Device
 */
struct Compass
{
	const void *class;
	BYTE devaddress;
	BYTE scale;
	float declination;
	struct Interface *inter;	
};


/**
 * static int Compass_status(struct Compass *dev) - Read status register
 * \param *_self - pointer to the Compass grove device class.
* \return - The status of the operation
 <UL>
	<LI><Breturn = 0:</B> the operation was successful (the last measurement was successful) .</LI> 
	<LI><B>return = -1:</B> the operation was unsuccessful (the last measurement was unsuccessful).</LI> 
 </UL>
*/
static int Compass_status(struct Compass *dev)
{
	BYTE status;
	if(set_register(dev->devaddress,MODE_REG,0x01))
		return -1;
	vTaskDelay(2);
	status = read_register(dev->devaddress, STAT_REG);
	vTaskDelay(2);
	if(!(status & 0x01))
		return -1;
	else
		return 0;
}	


/**
 * static void *Compass_ctor (void * _self, va_list *app) -Compass grove device Constructor  
 * \param *_self - pointer to the Compass grove device class.
 * \param *app 
 * \		1- i2c device address
 * \		2- Configure the scale for the device
 * \		3- Configure the local magnetic diclination
* \return - Pointer to the Compass devices instantiated
*/
static void *Compass_ctor (void * _self, va_list *app)
{
	struct Compass *self = _self;
	self->devaddress =  (va_arg(*app, const BYTE)<<1);
	self->scale = (va_arg(*app, const BYTE)<<4);
	switch(self->scale)
	{
		case SCALE1:
			scaling_factor = 1.3;
		break;	
		case SCALE2:
			scaling_factor = 1.024;
		break;	
		case SCALE3:
			scaling_factor = 0.768;
		break;	
		case SCALE4:
			scaling_factor = 0.614;
		break;	
		case SCALE5:
			scaling_factor = 0.415;
		break;	
		case SCALE6:
			scaling_factor = 0.361;
		break;	
		case SCALE7:
			scaling_factor = 0.307;
		break;	
		case SCALE8:
			scaling_factor = 0.214;
	}
	self->declination = va_arg(*app, const float)/10E6;
	self->inter = NULL;
	return self;
}	

/**
 * static void Compass_dtor (void * _sensor)- Compass grove device Destructor  
 * \param *_sensor - pointer to the Compass grove device class.
 * \return - None
*/
static void Compass_dtor (void * _sensor)
{
	
}	


/**
 * static void* Compass_attach (void * _board,void *_sensor,int n) - attach a Compass grove device to the GroveNest I2C port  
 * \param *_board - pointer to the GroveNest 
 * \param *_sensor - pointer to the Compass grove device class.
 * \param ic2bus -  which I2C bus the device is connected to
 * \return 
 <UL>
	<LI><Breturn = Pointer to the I2C interface created:</B> the operation was successful.</LI> 
	<LI><B>return = NULL:</B> the operation was unsuccessful.</LI> 
 </UL>
 */
static void *Compass_attach (void * _board,void *_sensor,int ic2bus)
{
	struct Compass *sensor = _sensor;
	int add = sensor->devaddress;
	sensor->inter = attachSensorToI2CBus(_board,ic2bus,add);
	return sensor->inter;
}	


/**
 *  static int Compass_configure (void * _self, va_list *app) -  Configure the Compass grove device
 * \param *_self - pointer to the device 
 * \param *app - none 
 * \return:
 	<LI><Breturn = 0:</B>when the Compass device is properly configured </LI> 
 	<LI><Breturn = -1:</B>when the operation was unsucceful (the Compass device will not work) </LI> 
 </UL>
 */
static int Compass_config (void * _self, va_list *app)
{
	struct Compass *self = _self;
	if(set_register(self->devaddress,CNTL_REGB,self->scale))
		return -1;
	return set_register(self->devaddress,MODE_REG,0x03);
}


/**
 * static float Compass_get(void * _self,va_list *app) -  Get the magnet field measured on the 3-axis (X-Y-Z)
 * \param *_self - pointer to the device 
 * \param *app - Which data to be got 
 *  - HEADING -Provides the heading pointed by x axis 
 *  - AXIS_X - Magnet field measured on x axis
 *  - AXIS_Y - Magnet field measured on y axis 
 *  - AXIS_Z - Magnet field measured on z axis 
 *\return - The 3-axis data (X,Y or Z) or the heading.
*/
static float Compass_get (void * _self, va_list *app)
{
	struct Compass *self = _self;
	BYTE regist = va_arg(*app, const BYTE);
	BYTE registh;
	int data;
	if(Compass_status(self))
		flag = 1;
	else
	{
		switch(regist)
		{
			case HEADING:
				regist = read_register(self->devaddress, DATA_REGXL);
				DelayMs(1);
				registh = read_register(self->devaddress, DATA_REGXH);
				data = ((int)(registh<<8))|regist;
				float datax = (float)data/scaling_factor;
				DelayMs(1);
				regist = read_register(self->devaddress, DATA_REGYL);
				DelayMs(1);
				registh = read_register(self->devaddress, DATA_REGYH);
				data = ((int)(registh<<8))|regist;
				float datay = (float)data/scaling_factor;
				float heading = atan2(datay,datax) + self->declination;
				if(heading < 0)
					heading += 6.283;
				if(heading > 6.283)
					heading -= 6.283;
				heading = heading * 57.297;
				return heading;
			case DATA_REGXH:
				regist = read_register(self->devaddress, DATA_REGXL);
				DelayMs(1);
				registh = read_register(self->devaddress, DATA_REGXH);
				data = ((int)(registh<<8))|regist;
			break;
			case DATA_REGYH:
				regist = read_register(self->devaddress, DATA_REGYL);
				DelayMs(1);
				registh = read_register(self->devaddress, DATA_REGYH);
				data = ((int)(registh<<8))|regist;
			break;
			case DATA_REGZH:
				regist = read_register(self->devaddress, DATA_REGZL);
				DelayMs(1);
				registh = read_register(self->devaddress, DATA_REGZH);
				data = ((int)(registh<<8))|regist;
		}
	}
	if(data == -4096)
		flag = 1;
	if(flag)
		return -1;
	else 
		return (float)(data/scaling_factor);
}

static const struct SensorClass _Compass =
{	
	sizeof(struct Compass),
	Compass_ctor,
	Compass_dtor,
	Compass_attach,
	Compass_config,
	0,
	Compass_get,
};

const void *Compass = &_Compass;





