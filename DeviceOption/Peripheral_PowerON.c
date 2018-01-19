/**********************************************************************
***********************************************************************
* Sources Description: Power On All Peripheral
* Module Name:     	TDA75610.c
* Created By:      	Henson Li
* Created Date:    	2015-04-01
* %version:        	1 %
***********************************************************************
***********************************************************************/

#include "global.h"
#include "Peripheral_PowerON.h"
#include "Dio.h"
#include "TIMER.h"
#include "PM100.h"

void MCU_Power_EN(void)
{
	Dio_WriteChannel(DIO_PIN_P44, DIO_HIGH);	//VCC_3V3
	Dio_WriteChannel(DIO_PIN_P30, DIO_HIGH);	//VCC_5V
}

void LCD_Enable()
{
	Dio_WriteChannel(DIO_PIN_P01, DIO_HIGH);
	Dio_WriteChannel(DIO_PIN_P17, DIO_HIGH);
}

void __89501_Enable()
{
	Dio_WriteChannel(DIO_PIN_P71, DIO_HIGH);	//VCC_89501
}

void V3P3_LAN_Enable()
{
	Dio_WriteChannel(DIO_PIN_P10, DIO_HIGH);	//V3P3_LAN_EN
}

void All_Power_Init()
{
	PM100_PowerOn();	//PM100 Power On
	MCU_Power_EN();
	Delay_ms(20);
	__89501_Enable();
	V3P3_LAN_Enable();
	
	Delay_ms(10);
	IMX6_Reset();		//IMX6 Reset
	Delay_ms(10);
	PM100_Output_Ctl();
	
	
	LCD_Enable();
}