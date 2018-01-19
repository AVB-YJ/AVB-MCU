/**********************************************************************
***********************************************************************
* Sources Description: Control of Amplifier(Type:TDA75610LV) 
* Module Name:     	TDA75610.c
* Created By:      	Henson Li
* Created Date:    	2015-05-06
* %version:        	1 %
***********************************************************************
***********************************************************************/

#ifndef __PM100_H_
#define __PM100_H_

#include "global.h"
#include "Dio.h"
#include "Hardware_IIC.h"

//public
void PM100_PowerOn();
void PM100_Output_Ctl();
void IMX6_Reset();

#endif