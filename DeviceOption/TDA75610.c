/**********************************************************************
***********************************************************************
* Sources Description: Control of Amplifier(Type:TDA75610LV) 
* Module Name:     	TDA75610.c
* Created By:      	Henson Li
* Created Date:    	2015-04-01
* %version:        	1 %
***********************************************************************
***********************************************************************/

#include "global.h"
#include "Dio.h"
#include "TDA75610.h"
#include "Hardware_IIC.h"

uint8_t iic_write_data[10];

void TDA75610_Open()
{
	//Disable WakeUp Pin
	Dio_WriteChannel(DIO_PIN_P64, DIO_HIGH);
	//Power On Amplifier
	iic_write_data[0] = 0x27;
	iic_write_data[1] = 0x93;
	IIC11_MasterSendStart(TDA75610_WRITE_ADDR, iic_write_data, 2);
}

void TDA_75610_Off()
{
	//Enable WakeUp Pin
	Dio_WriteChannel(DIO_PIN_P64, DIO_LOW);
	//Power Off Amplifier
	iic_write_data[0] = 0x00;
	iic_write_data[1] = 0x00;
	IIC11_MasterSendStart(TDA75610_WRITE_ADDR, iic_write_data, 2);
}