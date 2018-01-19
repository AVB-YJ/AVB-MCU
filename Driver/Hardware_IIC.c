/*
*******************************************************************************
* Copyright(C) 2008, 2010 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by Applilet3 for 78K0R/Fx3
* Filename:	CG_serial.c
* Abstract:	This file implements device driver for Serial module.
* APIlib:	Applilet3 for 78K0R/Fx3 V2.01 [22 Oct 2010]
* Device:	uPD78F1840_80
* Compiler:	IAR Systems icc78k0r
* Creation date:	2015/3/27
* Created By:       Henson.li
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "Hardware_IIC.h"


/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
UCHAR  gIic11MasterStatusFlag;	/* iic11 start flag for send address check by master mode */
UCHAR  *gpIic11TxAddress;		/* iic11 send data pointer by master mode */
USHORT gIic11TxCnt;				/* iic11 send data size by master mode */
UCHAR  *gpIic11RxAddress;		/* iic11 receive data pointer by master mode */
USHORT gIic11RxCnt;				/* iic11 receive data size by master mode */
USHORT gIic11RxLen;				/* iic11 receive data length by master mode */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes IIC11.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_Init(void)
{
	SAU1EN = 1U;	/* supply SAU1 clock */
	NOP();
	NOP();
	NOP();
	NOP();
	SPS1 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
	
	ST1 |= _0002_SAU_CH1_STOP_TRG_ON;	/* disable IIC11 */
	IICMK11 = 1U;						/* disable INTIIC11 interrupt */
	IICIF11 = 0U;						/* clear INTIIC11 interrupt flag */
	/* Set INTIIC11 level2 priority */
	IICPR111 = 1U;
	IICPR011 = 0U;
	SIR11 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;	/* error flag clear */
	SMR11 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_EDGE_FALL | _0004_SAU_IIC | _0000_SAU_TRANSFER_END;
	SCR11 = _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0000_SAU_MSB | _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
	SDR11 = _EE00_IIC11_DIVISOR;
	SO1 |= _0200_SAU_CH1_CLOCK_OUTPUT_1 | _0002_SAU_CH1_DATA_OUTPUT_1;
	STSEL |= 0x20U;						/* IIC11 communication pin selection */
	/* Set SCL11, SDA11 pin */
	P6 |= 0x03U;
	PM6 &= 0xFCU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts transferring data for IIC11 in master mode.
**
**  Parameters:
**	adr: set address for select slave
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_MasterSendStart(UCHAR adr, UCHAR *txbuf, USHORT txnum)
{	
	gIic11MasterStatusFlag = _00_SAU_IIC_MASTER_FLAG_CLEAR;	/* clear IIC11 master status flag */
	adr &= 0xFEU;											/* send mode */
	gIic11MasterStatusFlag = _01_SAU_IIC_SEND_FLAG;			/* set master status flag */
	SCR11 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
	SCR11 |= _8000_SAU_TRANSMISSION;
	IICMK11 = 0U;											/* enable INTIIC11 */
	/* Set paramater */
 	gIic11TxCnt = txnum;
	gpIic11TxAddress = txbuf; 
	/* Start condition */
	IIC11_StartCondition();
	SDR11L = adr;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts receiving data for IIC11 in master mode.
**
**  Parameters:
**	adr: set address for select slave
**	rxbuf: receive buffer pointer
**	rxnum: buffer size
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_MasterReceiveStart(UCHAR adr, UCHAR *rxbuf, USHORT rxnum)
{
	gIic11MasterStatusFlag = _00_SAU_IIC_MASTER_FLAG_CLEAR;	/* clear master status flag */
	adr |= 0x01U;											/* receive mode */
	gIic11MasterStatusFlag = _02_SAU_IIC_RECEIVE_FLAG;		/* set master status flag */
	SCR11 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
	SCR11 |= _8000_SAU_TRANSMISSION;	
	IICMK11 = 0U;											/* enable INTIIC11 */
	/* Set parameter */
	gIic11RxLen = rxnum;
	gIic11RxCnt = 0U;
	gpIic11RxAddress = rxbuf;
	/* Start condition */
	IIC11_StartCondition();
	SDR11L = adr;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the IIC11 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_Stop(void)
{
	/* Stop transfer */
	ST1 |= _0002_SAU_CH1_STOP_TRG_ON;		/* disable IIC11 */
	IICMK11 = 1U;							/* disable INTIIC11 */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts IIC11 condition.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_StartCondition(void)
{
	SO1 &= ~_0002_SAU_CH1_DATA_OUTPUT_1;	/* clear IIC11 SDA */
	SOE1 |= _0002_SAU_CH1_OUTPUT_ENABLE;	/* enable IIC11 out */
	SO1 &= ~_0200_SAU_CH1_CLOCK_OUTPUT_1;	/* clear IIC11 SCL */
	SS1 |= _0002_SAU_CH1_START_TRG_ON;		/* enable IIC11 */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops IIC11 condition.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_StopCondition(void)
{
	ST1 |= _0002_SAU_CH1_STOP_TRG_ON;		/* disable IIC11 */
	SOE1 &= ~_0002_SAU_CH1_OUTPUT_ENABLE;	/* disable IIC11 out */
	SO1 &= ~_0002_SAU_CH1_DATA_OUTPUT_1;	/* clear IIC11 SDA */
	SO1 |= _0200_SAU_CH1_CLOCK_OUTPUT_1;	/* set IIC11 SCL */
	SO1 |= _0002_SAU_CH1_DATA_OUTPUT_1;		/* set IIC11 SDA */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
