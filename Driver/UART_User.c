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
* Creation date:	2015/4/2
* Created By:       Henson.li
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "CG_macrodriver.h"
#include "UART.h"
#include "CCA.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
extern UCHAR  *gpUart2TxAddress;	/* uart2 transmit buffer address */
extern USHORT gUart2TxCnt;		/* uart2 transmit data number */
extern UCHAR  *gpUart2RxAddress;	/* uart2 receive buffer address */
extern USHORT gUart2RxCnt;		/* uart2 receive data number */
extern USHORT gUart2RxLen;		/* uart2 receive data length */
extern UCHAR  *gpUARTF0TxAddress;	/* UARTF0 transmit buffer address */
extern UCHAR  *gpUARTF0TxBfAddress;	/* UARTF0 transmit buffer address in buffer mode */
extern USHORT gUARTF0Quotient;		/* UARTF0 transmit buffer data count */
extern USHORT gUARTF0Remainder;		/* UARTF0 transmit buffer data remainer */
extern USHORT gUARTF0TxCnt;		/* UARTF0 transmit data number */
extern UCHAR  *gpUARTF0RxAddress;	/* UARTF0 receive data address */
extern USHORT gUARTF0RxCnt;		/* UARTF0 receive data number */
extern USHORT gUARTF0RxLen;		/* UARTF0 receive data length */
extern UCHAR  *gpUARTF1TxAddress;	/* UARTF1 transmit buffer address */
extern UCHAR  *gpUARTF1TxBfAddress;	/* UARTF1 transmit buffer address in buffer mode */
extern USHORT gUARTF1Quotient;		/* UARTF1 transmit buffer data count */
extern USHORT gUARTF1Remainder;		/* UARTF1 transmit buffer data remainer */
extern USHORT gUARTF1TxCnt;		/* UARTF1 transmit data number */
extern UCHAR  *gpUARTF1RxAddress;	/* UARTF1 receive data address */
extern USHORT gUARTF1RxCnt;		/* UARTF1 receive data number */
extern USHORT gUARTF1RxLen;		/* UARTF1 receive data length */
/* Start user code for global. Do not edit comment generated here */

struct ipc_data *G_RxdecodeBuf = 0;
struct ipc_data *G_TxdecodeBuf = 0;

/* End user code. Do not edit comment generated here */


void TmpSend_UART_IPC_Data_To_CAN(uint8_t* DecodedData);

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTSR2 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTSR2_vect
__interrupt void MD_INTSR2(void)
{
	USHORT rx_data_16;
	UCHAR rx_data_8;
	UCHAR err_type;
	
	err_type = (UCHAR)(SSR21 & 0x0007U);
	SIR21 = (USHORT)err_type;
	if (err_type != 0)
	{
		UART2_ErrorCallback(err_type);
	}
	if ((SCR21 & 0x000FU) > _0007_SAU_LENGTH_8)
	{
		rx_data_16 = SDR21;
		if (gUart2RxLen > gUart2RxCnt)
		{
			*(USHORT*)gpUart2RxAddress = rx_data_16;
			gpUart2RxAddress += 2U ;
			gUart2RxCnt += 2U;
			if (gUart2RxLen == gUart2RxCnt)
			{
				UART2_ReceiveEndCallback();
			}
		}
		else
		{
			UART2_SoftOverRunCallback();
		}
	}
	else
	{
		rx_data_8 = SDR21L;
		if (gUart2RxLen > gUart2RxCnt)
		{
			*gpUart2RxAddress = rx_data_8;
			gpUart2RxAddress++;
			gUart2RxCnt++;
			if (gUart2RxLen == gUart2RxCnt)
			{
				UART2_ReceiveEndCallback();
			}
		}
		else
		{
			UART2_SoftOverRunCallback();
		}
		
		/*IPC protocal data Handle*/
		G_RxdecodeBuf = decode(rx_data_8);                //decode
		if(G_RxdecodeBuf) 								//Get the message 
		{ 
			if(G_RxdecodeBuf->len != 0 && G_RxdecodeBuf->len != 0xFF)
			{				
				//send data to CAN Bus
				TmpSend_UART_IPC_Data_To_CAN(G_RxdecodeBuf->data);
			}
		}
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTST2 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTST2_vect
__interrupt void MD_INTST2(void)
{
	if (gUart2TxCnt > 0U)
	{
		if ((SCR20 & 0x000FU) > _0007_SAU_LENGTH_8)
		{
			SDR20 = *(USHORT*)gpUart2TxAddress;
			gpUart2TxAddress += 2U;
			gUart2TxCnt -= 2U;
		}
		else
		{
			SDR20L = *gpUart2TxAddress;
			gpUart2TxAddress++;
			gUart2TxCnt--;
		}
	}
	else
	{
		UART2_SendEndCallback();
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UART2.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UART2.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_SoftOverRunCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UART2.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UART2.
**
**  Parameters:
**	err_type: error type value
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UART2_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTLR0 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTLR0_vect
__interrupt void MD_INTLR0(void)
{
	UCHAR rx_data_8;
	
	rx_data_8 = UF0RXB;
	if (gUARTF0RxLen > gUARTF0RxCnt)
	{
		*gpUARTF0RxAddress = rx_data_8;
		gpUARTF0RxAddress++;
		gUARTF0RxCnt++;
		if (gUARTF0RxLen == gUARTF0RxCnt)
		{
			UARTF0_ReceiveEndCallback();
		}
	}
	else
	{
		UARTF0_SoftOverRunCallback();
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTLT0 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTLT0_vect
__interrupt void MD_INTLT0(void)
{
	if (gUARTF0TxCnt > 0U)
	{
		LTMK0 = 1U; 
		UF0TXB = *gpUARTF0TxAddress;
		gpUARTF0TxAddress++;
		gUARTF0TxCnt--;
		LTMK0 = 0U; 
	}
	else
	{
		UARTF0_SendEndCallback();
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTLS0 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTLS0_vect
__interrupt void MD_INTLS0(void)
{
	USHORT rx_data_16;
	UCHAR  err_type;

	rx_data_16 = UF0RX;
	err_type = (UCHAR)(UF0STR & 0x07U);
	UF0STC |= _0007_UARTF_COMMONERROE_CLEAR;
	UARTF0_ErrorCallback(err_type);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF0.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF0.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF0.
**
**  Parameters:
**	err_type: error type
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF0.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF0_SoftOverRunCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTLR1 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTLR1_vect
__interrupt void MD_INTLR1(void)
{
	UCHAR rx_data_8;
	
	rx_data_8 = UF1RXB;
	if (gUARTF1RxLen > gUARTF1RxCnt)
	{
		*gpUARTF1RxAddress = rx_data_8;
		gpUARTF1RxAddress++;
		gUARTF1RxCnt++;
		if (gUARTF1RxLen == gUARTF1RxCnt)
		{
			UARTF1_ReceiveEndCallback();
		}
	}
	else
	{
		UARTF1_SoftOverRunCallback();
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTLT1 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTLT1_vect
__interrupt void MD_INTLT1(void)
{
	if (gUARTF1TxCnt > 0U)
	{
		LTMK1 = 1U; 
		UF1TXB = *gpUARTF1TxAddress;
		gpUARTF1TxAddress++;
		gUARTF1TxCnt--;
		LTMK1 = 0U; 
	}
	else
	{
		UARTF1_SendEndCallback();
	}
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTLS1 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTLS1_vect
__interrupt void MD_INTLS1(void)
{
	USHORT rx_data_16;
	UCHAR  err_type;

	rx_data_16 = UF1RX;
	err_type = (UCHAR)(UF1STR & 0x07U);
	UF1STC |= _0007_UARTF_COMMONERROE_CLEAR;
	UARTF1_ErrorCallback(err_type);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF1.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF1.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF1.
**
**  Parameters:
**	err_type: error type
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of UARTF1.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void UARTF1_SoftOverRunCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */


void TmpSend_UART_IPC_Data_To_CAN(uint8_t* DecodedData)
{
  	uint8_t mChannel = DecodedData[0];		//Type of Cmd
  	//uint8_t Tmpdata1 = DecodedData[1];
  	uint8_t Tmpdata2 = DecodedData[2];		//Option type of mChannel
  	uint8_t Tmpdata3 = DecodedData[3];		//Option code
		
	Received_IPC_Data = 1;					//enable data write to CAN register
	
	if(mChannel == 1)						//Air
	{
		switch(Tmpdata2)
		{
		case 0:								//Air On/Off
		  	if(Tmpdata3)						//Air On
			{
				Open_ACC_On_Request = true;
			}
			else								//Air Off
			{
			  	Open_ACC_Off_Request = true;
			}
		  	break;
		case 1:								//Air auto mode
		  	if(Tmpdata3 == 0)					
			{
				Air_AutoMode_Request = 0;
			}
			else								
			{
				Air_AutoMode_Request = 1;
			}
			break;
		case 2:							//Air defrost mode
			Air_DefrostMode_Request = Tmpdata3;
			break;
		case 3:							//Air Circulation mode
			Air_CircuationMode_Request = Tmpdata3;
			break;
		case 4:								//Air main temperature
		  	Air_TempOfMain = Tmpdata3;
			break;
		case 5:								//Air copilot temperature
			Air_TempOfCopilot = Tmpdata3;
			break;
		case 6:								//Air speed
			Air_Speed = Tmpdata3;
			break;
		case 7:								//Air direction
			Air_Direction = Tmpdata3;
			break;
		default:
			break;
		}
	}
	else if(mChannel == 2)					//Door
	{
		switch(Tmpdata2)
		{
		case 1:									//Front left door
		  	if(Tmpdata3)							//Door open
			{
			}
			else									//Door close
			{
			}
			break;
		case 2:									//Front right door
		  	if(Tmpdata3)							//Door open
			{
			}
			else									//Door close
			{
			}
			break;
		case 3:									//Back left door
		  	if(Tmpdata3)							//Door open
			{
			}
			else									//Door close
			{
			}
			break;
		case 4:									//Back right door
		  	if(Tmpdata3)							//Door open
			{
			}
			else									//Door close
			{
			}
			break;
		default:
			break;
		}
	}
}


void APP_IPC_Handler(void)
{
	if(G_RxdecodeBuf->len == 0xff) 
	{
		//error;
	}
	else 
	{
		if(G_RxdecodeBuf->data[CHANNEL] == 0)/*ack*/
		{
			//TxdecodeBuf->len = 3;
			//TxdecodeBuf->data[CHANNEL] = 0;
		}
		else if(G_RxdecodeBuf->data[CHANNEL] == 1)/*door control*/
		{
		}
		else if(G_RxdecodeBuf->data[CHANNEL] == 2)/*air condition*/
		{
		}
		else
		{
		}
	}  
}