#ifndef __DEFINE_H
#define __DEFINE_H

#include "OS.h"

//TDA75610LV
#define     TDA75610_WRITE_ADDR     0xD8
#define     TDA75610_READ_ADDR      0xD9

//PM100
//#define		PM100_WRITE_ADDR		0x08
//#define		PM100_READ_ADDR			0x09
#define		PM100_WRITE_ADDR		0x10
#define		PM100_READ_ADDR			0x11

//UART Config

//--Channels
#define 	UART_CHANNEL_0		0
#define 	UART_CHANNEL_1		1
#define 	UART_CHANNEL_2		2

//BoudRate
#define 	BOUD_RATE_9600		9600
#define 	BOUD_RATE_19200		19200
#define 	BOUD_RATE_31250		31250
#define 	BOUD_RATE_38400		38400
#define 	BOUD_RATE_76800		76800
#define 	BOUD_RATE_153600	153600
#define 	BOUD_RATE_312500	312500

#define 	UART0_BOUD_RATE		BOUD_RATE_115200
#define 	UART1_BOUD_RATE		BOUD_RATE_115200
#define 	UART2_BOUD_RATE		BOUD_RATE_115200

#endif