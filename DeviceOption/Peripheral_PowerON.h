/**********************************************************************
***********************************************************************
* Sources Description: Power On All Peripheral
* Module Name:     	TDA75610.c
* Created By:      	Henson Li
* Created Date:    	2015-04-01
* %version:        	1 %
***********************************************************************
***********************************************************************/


#ifndef __PERIPHERAL_POWERON_H
#define __PERIPHERAL_POWERON_H

#include "Port.h"
#include "OS.h"

//private
void MCU_Power_EN(void);
void __89501_Enable();
void V3P3_LAN_Enable();

//public
void All_Power_Init();

#endif