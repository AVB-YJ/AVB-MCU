/**********************************************************************
***********************************************************************
* Sources Description: Control of Amplifier(Type:TDA75610LV) 
* Module Name:     	TDA75610.c
* Created By:      	Henson Li
* Created Date:    	2015-05-06
* %version:        	1 %
***********************************************************************
***********************************************************************/

#include "PM100.h"

uint8_t PM100_WriteData[2];

void PM100_PowerOn()
{
	Dio_WriteChannel(DIO_PIN_P11, DIO_HIGH);
}

void PM100_Output_Ctl()
{	
#if 0
		//1V
		PM100_WriteData[0] = 0x6C;		//VGEN1[3:0]
		PM100_WriteData[1] = 0x94;
		IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
		Delay_ms(2);
		
		//1V
		PM100_WriteData[0] = 0x6D;		//VGEN2[3:0]
		PM100_WriteData[1] = 0x94;
		IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
		Delay_ms(2);
#endif
		//2V
		PM100_WriteData[0] = 0x6E;		//VGEN3[3:0]
		PM100_WriteData[1] = 0x92;
		IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
		Delay_ms(2);	
		
		//2.5V
		PM100_WriteData[0] = 0x70;		//VGEN5[3:0]
		PM100_WriteData[1] = 0x97;
		IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
		Delay_ms(2);
	
	
#if 0
	//1.425V
	PM100_WriteData[0] = 0x20;		//SW1AB[5:0]
	PM100_WriteData[0] = 0x2D;
	IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
	
	PM100_WriteData[0] = 0x2E;		//SW1C[5:0]
	PM100_WriteData[0] = 0x2D;
	IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
	
	//3V
	PM100_WriteData[0] = 0x35;		//SW2[6:0]
	PM100_WriteData[0] = 0x6C;
	IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
	
	//1.375V
	PM100_WriteData[0] = 0x3A;		//SW3A[6:0]
	//PM100_WriteData[0] = 0x26;	//1.35
	PM100_WriteData[0] = 0x2C;		//1.5
	IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
	
	PM100_WriteData[0] = 0x3B;		//SW3B[6:0]
	//PM100_WriteData[0] = 0x26;	//1.35
	PM100_WriteData[0] = 0x2C;		//1.5
	IIC11_MasterSendStart(PM100_WRITE_ADDR, PM100_WriteData, 2);
	//IIC11_MasterSendStart(UCHAR adr, UCHAR *txbuf, USHORT txnum);
#endif
}

void IMX6_Reset()
{
	Dio_WriteChannel(DIO_PIN_P126, DIO_HIGH);
}
