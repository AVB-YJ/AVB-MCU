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
* Creation date:	2015/4/2
* Created By:       Henson.li
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "Dio.h"
#include "UART.h"
#include "Port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
UCHAR  *gpUart2TxAddress;	/* uart2 transmit buffer address */
USHORT gUart2TxCnt;		/* uart2 transmit data number */
UCHAR  *gpUart2RxAddress;	/* uart2 receive buffer address */
USHORT gUart2RxCnt;		/* uart2 receive data number */
USHORT gUart2RxLen;		/* uart2 receive data length */
UCHAR  *gpUARTF0TxAddress;	/* UARTF0 transmit data address */
UCHAR  *gpUARTF0TxBfAddress;	/* UARTF0 transmit buffer address in buffer mode */
USHORT gUARTF0Quotient;		/* UARTF0 transmit buffer data count */
USHORT gUARTF0Remainder;	/* UARTF0 transmit buffer data remainer */
USHORT gUARTF0TxCnt;		/* UARTF0 transmit data number */
UCHAR  *gpUARTF0RxAddress;	/* UARTF0 receive data address */
USHORT gUARTF0RxCnt;		/* UARTF0 receive data number */
USHORT gUARTF0RxLen;		/* UARTF0 receive data length */
UCHAR  *gpUARTF1TxAddress;	/* UARTF1 transmit data address */
UCHAR  *gpUARTF1TxBfAddress;	/* UARTF1 transmit buffer address in buffer mode */
USHORT gUARTF1Quotient;		/* UARTF1 transmit buffer data count */
USHORT gUARTF1Remainder;	/* UARTF1 transmit buffer data remainer */
USHORT gUARTF1TxCnt;		/* UARTF1 transmit data number */
UCHAR  *gpUARTF1RxAddress;	/* UARTF1 receive data address */
USHORT gUARTF1RxCnt;		/* UARTF1 receive data number */
USHORT gUARTF1RxLen;		/* UARTF1 receive data length */
/* Start user code for global. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes UART2.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_Init(void)
{
	SAU2EN = 1U;	/* supply SAU2 clock */
	NOP();
	NOP();
	NOP();
	NOP();
	SPS2 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
	
	ST2 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;	/* disable UART2 */
	SRMK2 = 1U;	/* disable INTSR2 interrupt */
	SRIF2 = 0U;	/* clear INTSR2 interrupt flag */
	STMK2 = 1U;	/* disable INTST2 interrupt */
	STIF2 = 0U;	/* clear INTST2 interrupt flag */
	/* Set INTSR2 low priority */
	SRPR12 = 1U;
	SRPR02 = 1U;
	/* Set INTST2 low priority */
	STPR12 = 1U;
	STPR02 = 1U;
	SIR21 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
	NFEN0 |= _10_SAU_RXD2_FILTER_ON;
	SMR21 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_EDGE_FALL | _0100_SAU_TRIGGER_RXD | _0002_SAU_UART | _0000_SAU_TRANSFER_END;
	SCR21 = _4000_SAU_RECEPTION | _0400_SAU_INTSRE_ENABLE | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
	SDR21 = _CE00_UART2_RECEIVE_DIVISOR;
	SMR20 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_TRIGGER_SOFTWARE | _0002_SAU_UART | _0000_SAU_TRANSFER_END;
	SCR20 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
	SDR20 = _CE00_UART2_TRANSMIT_DIVISOR;
	SOL2 = _0000_SAU_CHANNEL0_NORMAL;
	SO2 |= _0001_SAU_CH0_DATA_OUTPUT_1;	/* output level normal */
	SOE2 |= _0001_SAU_CH0_OUTPUT_ENABLE;	/* enable UART2 output */
	/* Set RxD2 pin */
	PM4 |=0x08U;
	/* Set TxD2 pin */
	P4 |= 0x04U;
	PM4 &= 0xFBU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the UART2 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_Start(void)
{
	SRIF2 = 0U;	/* clear INTSR2 interrupt flag  */
	SRMK2 = 0U;	/* enable INTSR2 interrupt */
	STIF2 = 0U;	/* INTST2 IF clear */
	STMK2 = 0U;	/* INTST2 enable */
	SOE2 |= _0001_SAU_CH0_OUTPUT_ENABLE;	/* enable UART2 output */
	SS2 |= _0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON;	/* enable UART2 */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the UART2 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_Stop(void)
{
	ST2 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;	/* disable UART2 */
	SOE2 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;	/* disable UART2 output */
	SRMK2 = 1U;	/* disable INTSR2 interrupt */
	SRIF2 = 0U;	/* clear INTSR2 interrupt flag */
	STMK2 = 1U;	/* disable INTST2 interrupt */
	STIF2 = 0U;	/* clear INTST2 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function receives UART2 data.
**
**  Parameters:
**	rxbuf: receive buffer pointer
**	rxnum: buffer size
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS UART2_ReceiveData(UCHAR *rxbuf, USHORT rxnum)
{
	MD_STATUS status = MD_OK;

	/* The receive number should be greater than 0, and in 9-16bit transfer mode, it should be even */
	if ((rxnum < 1U) || (((SCR21 & 0x000FU) > _0007_SAU_LENGTH_8) && ((rxnum & 0x1U) == 1U)))
	{
		status = MD_ARGERROR;
	}
	else
	{
		gUart2RxCnt = 0U;
		gUart2RxLen = rxnum;
		gpUart2RxAddress = rxbuf;
	}

	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function sends UART2 data.
**
**  Parameters:
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS UART2_SendData(UCHAR* txbuf, USHORT txnum)
{
	MD_STATUS status = MD_OK;

	if (txnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		static struct ipc_data *encode_data;
	
		encode_data = encode(txbuf, txnum);
		txbuf =  (uint8_t*)encode_data->data; 
		
		gpUart2TxAddress = txbuf;
		gUart2TxCnt = encode_data->len;
		
        if ((SCR20 & 0x000FU) > _0007_SAU_LENGTH_8)
        {
            /* Transfer data length is more than 8 bit */
            /* The data number should be even */
            if ((txnum & 0x1U) == 1U)
            {
                status = MD_ARGERROR;
            }
            else
            {
                STMK2 = 1U;	/* disable INTST2 interrupt */
                SDR20 = *(USHORT*)gpUart2TxAddress;
                gpUart2TxAddress += 2U;
                gUart2TxCnt -= 2U;
                STMK2 = 0U;	/* enable INTST2 interrupt */
            }
        }
        else
        {
            STMK2 = 1U;	/* disable INTST2 interrupt */
            SDR20L = *gpUart2TxAddress;	/* started by writing data to SDR[7:0] */
            gpUart2TxAddress++;
            gUart2TxCnt--;
            STMK2 = 0U;	/* enable INTST2 interrupt */
        }
	}

	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the UARTF0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_Init(void)
{
	LIN0EN = 1U;
	UF0CTL0 &= (UCHAR)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);	/* disable UARTF0 operation */
	LTMK0 = 1U;	/* disable INTLT0 interrupt */
	LTIF0 = 0U;	/* clear INTLT0 interrupt flag */
	LRMK0 = 1U;	/* disable INTLR0 interrupt */
	LRIF0 = 0U;	/* clear INTLR0 interrupt flag */
	LSMK0 = 1U;	/* disable INTLS0 interrupt */
	LSIF0 = 0U;	/* clear INTLS0 interrupt flag */
	/* Set INTLT0 low priority */
	LTPR10 = 1U;
	LTPR00 = 1U;
	/* Set INTLR0 low priority */
	LRPR10 = 1U;
	LRPR00 = 1U;
	/* Set INTLS0 high priority */
	LSPR10 = 0U;
	LSPR00 = 0U;
	UF0CTL1 = _6000_UARTF_BASECLK_8 | _000D_UARTF0_K_VALUE;
	UF0OPT0 = _14_UARTF_UFNOPT0_INITIALVALUE | _00_UARTF_TRAN_DATALEVEL_NORMAL | _00_UARTF_REC_DATALEVEL_NORMAL;
	UF0OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _00_UARTF_NORMAL_MODE;
	UF0OPT2 = _00_UARTF_LT_INT_GENTIME_0 | _02_UARTF_DATA_NOISE_FILTER_UNUSED;
	UF0CTL0 = _10_UARTF_TRANSFDIR_LSB | _00_UARTF_PARITY_NONE | _02_UARTF_DATALENGTH_8BIT | _00_UARTF_STOPLENGTH_1BIT;
	/* Set LTXD0 pin */
	P1 |= 0x08U;
	PM1 &= 0xF7U;
	/* Set LRXD0 pin */
	PM1 |= 0x10U;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the UARTF0 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_Start(void)
{
	LTIF0 = 0U;	/* clear INTLT0 interrupt flag */
	LTMK0 = 0U;	/* enable INTLT0 interrupt */
	LRIF0 = 0U;	/* clear INTLR0 interrupt flag */
	LRMK0 = 0U;	/* enable INTLR0 interrupt */
	LSIF0 = 0U;	/* clear INTLS0 interrupt flag */
	LSMK0 = 0U;	/* enable INTLS0 interrupt */
	UF0CTL0 |= _40_UARTF_TRANSMISSION_ENABLE | _20_UARTF_RECEPTION_ENABLE;	/* enable UARTF0 operation */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the UARTF0 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_Stop(void)
{
	UF0CTL0 &= (UCHAR)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);	/* disable UARTF0 operation */
	LTMK0 = 1U;	/* disable INTLT0 interrupt */
	LTIF0 = 0U;	/* clear INTLT0 interrupt flag */
	LRMK0 = 1U;	/* disable INTLR0 interrupt */
	LRIF0 = 0U;	/* clear INTLR0 interrupt flag */
	LSMK0 = 1U;	/* disable INTLS0 interrupt */
	LSIF0 = 0U;	/* clear INTLS0 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function receives UARTF0 data.
**
**  Parameters:
**	rxbuf: receive buffer pointer
**	rxnum: buffer size
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS UARTF0_ReceiveData(UCHAR *rxbuf, USHORT rxnum)
{
	MD_STATUS status = MD_OK;

	if (rxnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		if ((UF0STR & 0x0040U) == 0U)
		{
			gUARTF0RxCnt = 0U;
			gUARTF0RxLen = rxnum;
			gpUARTF0RxAddress = rxbuf;
		}
	}

	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function sends UARTF0 data.
**
**  Parameters:
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**	MD_DATAEXISTS
**
**-----------------------------------------------------------------------------
*/
MD_STATUS UARTF0_SendData(UCHAR *txbuf, USHORT txnum)
{
	MD_STATUS status = MD_OK;

	if (txnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gpUARTF0TxAddress = txbuf;
		gUARTF0TxCnt = txnum;
		
        if ((UF0STR & 0x0080U) == 0U)
        {
            LTMK0 = 1U;	/* disable INTLT0 interrupt */
            UF0TXB = *gpUARTF0TxAddress;
            gpUARTF0TxAddress++;
            gUARTF0TxCnt--;
            LTMK0 = 0U;	/* enable INTLT0 interrupt */
        }
        else
        {
            status = MD_DATAEXISTS;
        }
	}

	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the UARTF1 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_Init(void)
{
	LIN1EN = 1U;
	UF1CTL0 &= (UCHAR)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);	/* disable UARTF1 operation */
	LTMK1 = 1U;	/* disable INTLT1 interrupt */
	LTIF1 = 0U;	/* clear INTLT1 interrupt flag */
	LRMK1 = 1U;	/* disable INTLR1 interrupt */
	LRIF1 = 0U;	/* clear INTLR1 interrupt flag */
	LSMK1 = 1U;	/* disable INTLS1 interrupt */
	LSIF1 = 0U;	/* clear INTLS1 interrupt flag */
	/* Set INTLT1 low priority */
	LTPR11 = 1U;
	LTPR01 = 1U;
	/* Set INTLR1 low priority */
	LRPR11 = 1U;
	LRPR01 = 1U;
	/* Set INTLS1 low priority */
	LSPR11 = 1U;
	LSPR01 = 1U;
	UF1CTL1 = _6000_UARTF_BASECLK_8 | _000D_UARTF1_K_VALUE;
	UF1OPT0 = _14_UARTF_UFNOPT0_INITIALVALUE | _00_UARTF_TRAN_DATALEVEL_NORMAL | _00_UARTF_REC_DATALEVEL_NORMAL;
	UF1OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _00_UARTF_NORMAL_MODE;
	UF1OPT2 = _00_UARTF_LT_INT_GENTIME_0 | _02_UARTF_DATA_NOISE_FILTER_UNUSED;
	UF1CTL0 = _10_UARTF_TRANSFDIR_LSB | _00_UARTF_PARITY_NONE | _02_UARTF_DATALENGTH_8BIT | _00_UARTF_STOPLENGTH_1BIT;
	STSEL &= 0x7FU;
	/* Set LTXD1 pin */
	P1 |= 0x01U;
	PM1 &= 0xFEU;
	/* Set LRXD1 pin */
	PM1 |= 0x02U;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the UARTF1 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_Start(void)
{
	LTIF1 = 0U;	/* clear INTLT1 interrupt flag */
	LTMK1 = 0U;	/* enable INTLT1 interrupt */
	LRIF1 = 0U;	/* clear INTLR1 interrupt flag */
	LRMK1 = 0U;	/* enable INTLR1 interrupt */
	LSIF1 = 0U;	/* clear INTLS1 interrupt flag */
	LSMK1 = 0U;	/* enable INTLS1 interrupt */
	UF1CTL0 |= _40_UARTF_TRANSMISSION_ENABLE | _20_UARTF_RECEPTION_ENABLE;	/* enable UARTF1 operation */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the UARTF1 operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_Stop(void)
{
	UF1CTL0 &= (UCHAR)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);	/* disable UARTF1 operation */
	LTMK1 = 1U;	/* disable INTLT1 interrupt */
	LTIF1 = 0U;	/* clear INTLT1 interrupt flag */
	LRMK1 = 1U;	/* disable INTLR1 interrupt */
	LRIF1 = 0U;	/* clear INTLR1 interrupt flag */
	LSMK1 = 1U;	/* disable INTLS1 interrupt */
	LSIF1 = 0U;	/* clear INTLS1 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function receives UARTF1 data.
**
**  Parameters:
**	rxbuf: receive buffer pointer
**	rxnum: buffer size
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS UARTF1_ReceiveData(UCHAR *rxbuf, USHORT rxnum)
{
	MD_STATUS status = MD_OK;

	if (rxnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		if ((UF1STR & 0x0040U) == 0U)
		{
			gUARTF1RxCnt = 0U;
			gUARTF1RxLen = rxnum;
			gpUARTF1RxAddress = rxbuf;
		}
	}

	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function sends UARTF1 data.
**
**  Parameters:
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**	MD_DATAEXISTS
**
**-----------------------------------------------------------------------------
*/
MD_STATUS UARTF1_SendData(UCHAR *txbuf, USHORT txnum)
{
	MD_STATUS status = MD_OK;

	if (txnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gpUARTF1TxAddress = txbuf;
		gUARTF1TxCnt = txnum;

        if ((UF1STR & 0x0080U) == 0U)
        {
            LTMK1 = 1U;	/* disable INTLT1 interrupt */
            UF1TXB = *gpUARTF1TxAddress;
            gpUARTF1TxAddress++;
            gUARTF1TxCnt--;
            LTMK1 = 0U;	/* enable INTLT1 interrupt */
        }
        else
        {
            status = MD_DATAEXISTS;
        }
	}

	return (status);
}

/* Start user code for adding. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
