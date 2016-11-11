/* **************************************************************************																					
 *                                OpenPicus                 www.openpicus.com
 *                                                            italian concept
 * 
 *            openSource wireless Platform for sensors and Internet of Things	
 * **************************************************************************
 *  FileName:        basicdevices-pro.c
 *  Module:          FlyPort PRO WI-FI, ETH, GPRS
 *  Compiler:        Microchip C30 v3.24 or higher
 *
 *  Author               Rev.    Date              Comment
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Simone Marra	     1.0     05/16/2014		   First release  
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
 
#ifndef BASICDEVICES_PRO_H
#define BASICDEVICES_PRO_H

extern const void *I2C;
extern const void *Sensor;
extern const void *Dig_io;
extern const void *An_i;

extern unsigned char flag;

//Ports
#define DIG1	  	0
#define DIG2	  	1
#define AN1		  	0
#define AN2		  	1
#define I2C		  	0


//PWM sensor type
#define PWM		  	4
#define FREQUENCY	2
#define DUTY		3

#define GROVE_TIMEOUT		65500

#endif


