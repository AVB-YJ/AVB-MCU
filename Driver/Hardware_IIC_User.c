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
* Filename:	CG_serial_user.c
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
#include "CG_macrodriver.h"
#include "Hardware_IIC.h"
#include "Port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
extern UCHAR  gIic11MasterStatusFlag;	/* iic11 start flag for send address check by master mode */
extern UCHAR  *gpIic11TxAddress;		/* iic11 send data pointer by master mode */
extern USHORT gIic11TxCnt;				/* iic11 send data size by master mode */
extern UCHAR  *gpIic11RxAddress;		/* iic11 receive data pointer by master mode */
extern USHORT gIic11RxCnt;				/* iic11 receive data size by master mode */
extern USHORT gIic11RxLen;				/* iic11 receive data length by master mode */
extern UCHAR  *gpUart2TxAddress;		/* uart2 transmit buffer address */
extern USHORT gUart2TxCnt;				/* uart2 transmit data number */
extern UCHAR  *gpUart2RxAddress;		/* uart2 receive buffer address */
extern USHORT gUart2RxCnt;				/* uart2 receive data number */
extern USHORT gUart2RxLen;				/* uart2 receive data length */
extern UCHAR  *gpUARTF0TxAddress;		/* UARTF0 transmit buffer address */
extern UCHAR  *gpUARTF0TxBfAddress;		/* UARTF0 transmit buffer address in buffer mode */
extern USHORT gUARTF0Quotient;			/* UARTF0 transmit buffer data count */
extern USHORT gUARTF0Remainder;			/* UARTF0 transmit buffer data remainer */
extern USHORT gUARTF0TxCnt;				/* UARTF0 transmit data number */
extern UCHAR  *gpUARTF0RxAddress;		/* UARTF0 receive data address */
extern USHORT gUARTF0RxCnt;				/* UARTF0 receive data number */
extern USHORT gUARTF0RxLen;				/* UARTF0 receive data length */
extern UCHAR  *gpUARTF1TxAddress;		/* UARTF1 transmit buffer address */
extern UCHAR  *gpUARTF1TxBfAddress;		/* UARTF1 transmit buffer address in buffer mode */
extern USHORT gUARTF1Quotient;			/* UARTF1 transmit buffer data count */
extern USHORT gUARTF1Remainder;			/* UARTF1 transmit buffer data remainer */
extern USHORT gUARTF1TxCnt;				/* UARTF1 transmit data number */
extern UCHAR  *gpUARTF1RxAddress;		/* UARTF1 receive data address */
extern USHORT gUARTF1RxCnt;				/* UARTF1 receive data number */
extern USHORT gUARTF1RxLen;				/* UARTF1 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTIIC11 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTIIC11_vect
__interrupt void MD_INTIIC11(void)
{
	UCHAR rxadr;
	
	if ((SSR11 & _0002_SAU_PARITY_ERROR) == 0x0002U)
	{
		IIC11_MasterErrorCallback(MD_NACK);
	}
	else
	{
		/* Control for master send */
		if ((gIic11MasterStatusFlag & _01_SAU_IIC_SEND_FLAG) == 0x01U)
		{
			if (gIic11TxCnt > 0U)
			{
				SDR11L = *gpIic11TxAddress;
				gpIic11TxAddress++;
				gIic11TxCnt--;
			}
			else
			{
				IIC11_StopCondition();
				IIC11_MasterSendEndCallback();
			}
		}
		/* Control for master receive */
		else 
		{
			if ((gIic11MasterStatusFlag & _04_SAU_IIC_SENDED_ADDRESS_FLAG) == 0U)
			{
				rxadr = SDR11L;
				SCR11 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
				SCR11 |= _4000_SAU_RECEPTION;				
				gIic11MasterStatusFlag |= _04_SAU_IIC_SENDED_ADDRESS_FLAG;
				SDR11L = 0xFFU;
			}
			else
			{
				if (gIic11RxCnt < gIic11RxLen)
				{
					*gpIic11RxAddress = SDR11L;
					gpIic11RxAddress++;
					gIic11RxCnt++;
					if (gIic11RxCnt == (gIic11RxLen - 1U))
					{
						SOE1 &= ~_0002_SAU_CH1_OUTPUT_ENABLE;	/* disable IIC11 out */
						SDR11L = 0xFFU;
					}
					if (gIic11RxCnt == gIic11RxLen)
					{
						IIC11_StopCondition();
						IIC11_MasterReceiveEndCallback();
					}
					else
					{
						SDR11L = 0xFFU;
					}
				}
			}
		}
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function callback function open for users operation when IIC11 master error.
**
**  Parameters:
**	flag: status flag
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_MasterErrorCallback(MD_STATUS flag)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function callback function open for users operation when IIC11 master receive finish.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_MasterReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function callback function open for users operation when IIC11 master transmit finish.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IIC11_MasterSendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
