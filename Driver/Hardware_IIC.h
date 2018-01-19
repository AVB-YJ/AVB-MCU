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
* Filename:	CG_serial.h
* Abstract:	This file implements device driver for Serial module.
* APIlib:	Applilet3 for 78K0R/Fx3 V2.01 [22 Oct 2010]
* Device:	uPD78F1840_80
* Compiler:	IAR Systems icc78k0r
* Creation date:	2015/3/27
* Created By:       Henson.li
*******************************************************************************
*/

#ifndef _HARDWARE_IIC_H_
#define _HARDWARE_IIC_H_

#include "CG_macrodriver.h"
#include "Port.h"

/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
	Peripheral Enable Register 0 (PER0)
*/
/* Control of serial array unit 1 input clock (SAU1EN) */
#define _00_SAU1_CLOCK_STOP					0x00U	/* stops supply of input clock */
#define _10_SAU1_CLOCK_SUPPLY				0x10U	/* supplies input clock */

/*
	Peripheral Enable Register 0 (PER1)
*/
/* Control of serial array unit 1 input clock (SAU2EN) */
#define _00_SAU2_CLOCK_STOP					0x00U	/* stops supply of input clock */
#define _08_SAU2_CLOCK_SUPPLY				0x08U	/* supplies input clock */

/*
	Serial Clock Select Register m (SPSm)
*/
/* Operating mode and clear mode selection (PRSm03 - PRSm00) */
#define _0000_SAU_CK00_FCLK_0				0x0000U	/* CK00-fCLK */
#define _0001_SAU_CK00_FCLK_1				0x0001U	/* CK00-fCLK/2^1 */
#define _0002_SAU_CK00_FCLK_2				0x0002U	/* CK00-fCLK/2^2 */
#define _0003_SAU_CK00_FCLK_3				0x0003U	/* CK00-fCLK/2^3 */
#define _0004_SAU_CK00_FCLK_4				0x0004U	/* CK00-fCLK/2^4 */
#define _0005_SAU_CK00_FCLK_5				0x0005U	/* CK00-fCLK/2^5 */
#define _0006_SAU_CK00_FCLK_6				0x0006U	/* CK00-fCLK/2^6 */
#define _0007_SAU_CK00_FCLK_7				0x0007U	/* CK00-fCLK/2^7 */
#define _0008_SAU_CK00_FCLK_8				0x0008U	/* CK00-fCLK/2^8 */
#define _0009_SAU_CK00_FCLK_9				0x0009U	/* CK00-fCLK/2^9 */
#define _000A_SAU_CK00_FCLK_10				0x000AU	/* CK00-fCLK/2^10 */
#define _000B_SAU_CK00_FCLK_11				0x000BU	/* CK00-fCLK/2^11 */
#define _000F_SAU_CK00_INTTM23				0x000FU	/* CK00-INTTM23 */
/* Operating mode and clear mode selection (PRSm13 - PRSm10) */
#define _0000_SAU_CK01_FCLK_0				0x0000U	/* CK01-fCLK */
#define _0010_SAU_CK01_FCLK_1				0x0010U	/* CK01-fCLK/2^1 */
#define _0020_SAU_CK01_FCLK_2				0x0020U	/* CK01-fCLK/2^2 */
#define _0030_SAU_CK01_FCLK_3				0x0030U	/* CK01-fCLK/2^3 */
#define _0040_SAU_CK01_FCLK_4				0x0040U	/* CK01-fCLK/2^4 */
#define _0050_SAU_CK01_FCLK_5				0x0050U	/* CK01-fCLK/2^5 */
#define _0060_SAU_CK01_FCLK_6				0x0060U	/* CK01-fCLK/2^6 */
#define _0070_SAU_CK01_FCLK_7				0x0070U	/* CK01-fCLK/2^7 */
#define _0080_SAU_CK01_FCLK_8				0x0080U	/* CK01-fCLK/2^8 */
#define _0090_SAU_CK01_FCLK_9				0x0090U	/* CK01-fCLK/2^9 */
#define _00A0_SAU_CK01_FCLK_10				0x00A0U	/* CK01-fCLK/2^10 */
#define _00B0_SAU_CK01_FCLK_11				0x00B0U	/* CK01-fCLK/2^11 */
#define _00F0_SAU_CK01_INTTM23				0x00F0U	/* CK01-INTTM23 */

/*
	Serial Mode Register mn (SMRmn)
*/

#define	_0020_SAU_SMRMN_INITIALVALUE		0x0020U
/* Selection of macro clock (MCK) of channel n (CKSmn) */
#define _0000_SAU_CLOCK_SELECT_CK00			0x0000U	/* operation clock CK0 set by PRS register */ 
#define _8000_SAU_CLOCK_SELECT_CK01			0x8000U	/* operation clock CK1 set by PRS register */
/* Selection of transfer clock (TCLK) of channel n (CCSmn) */
#define _0000_SAU_CLOCK_MODE_CKS			0x0000U	/* divided operation clock MCK specified by CKSmn bit */  
#define _4000_SAU_CLOCK_MODE_TI0N			0x4000U	/* clock input from SCK pin (slave transfer in CSI mode) */
/* Selection of start trigger source (STSmn) */
#define _0000_SAU_TRIGGER_SOFTWARE			0x0000U	/* only software trigger is valid */
#define _0100_SAU_TRIGGER_RXD				0x0100U	/* valid edge of RXD pin */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SAU_EDGE_FALL					0x0000U	/* falling edge is detected as the start bit */
#define _0040_SAU_EDGE_RISING				0x0040U	/* rising edge is detected as the start bit */
/* Setting of operation mode of channel n (MDmn2, MDmn1) */
#define _0000_SAU_CSI						0x0000U	/* CSI mode */
#define _0002_SAU_UART						0x0002U	/* UART mode */
#define _0004_SAU_IIC						0x0004U	/* simplified IIC mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SAU_TRANSFER_END				0x0000U	/* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY				0x0001U	/* buffer empty interrupt */

/*
	Serial Communication Operation Setting Register mn (SCRmn)
*/
/* Setting of operation mode of channel n (TXEmn, RXEmn) */
#define _0000_SAU_NOT_COMMUNICATION			0x0000U	/* does not start communication */
#define _4000_SAU_RECEPTION					0x4000U	/* reception only */
#define _8000_SAU_TRANSMISSION				0x8000U	/* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION	0xC000U	/* reception and transmission */
/* Selection of data and clock phase in CSI mode (DAPmn, CKPmn) */
#define _0000_SAU_TIMING_1					0x0000U	/* type 1 */
#define _1000_SAU_TIMING_2					0x1000U	/* type 2 */
#define _2000_SAU_TIMING_3					0x2000U	/* type 3 */
#define _3000_SAU_TIMING_4					0x3000U	/* type 4 */
/* Selection of masking of error interrupt signal (EOCmn) */
#define _0000_SAU_INTSRE_MASK				0x0000U	/* masks error interrupt INTSREx */
#define _0400_SAU_INTSRE_ENABLE				0x0400U	/* enables generation of error interrupt INTSREx */
/* Setting of parity bit in UART mode (PTCmn1, PTCmn0) */
#define _0000_SAU_PARITY_NONE				0x0000U	/* none parity */
#define _0100_SAU_PARITY_ZERO				0x0100U	/* zero parity */
#define _0200_SAU_PARITY_EVEN				0x0200U	/* even parity */
#define _0300_SAU_PARITY_ODD				0x0300U	/* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIRmn) */
#define _0000_SAU_MSB						0x0000U	/* MSB */
#define _0080_SAU_LSB						0x0080U	/* LSB */
/* Setting of stop bit in UART mode (SLCmn1, SLCmn0) */
#define _0000_SAU_STOP_NONE					0x0000U	/* none stop bit */
#define _0010_SAU_STOP_1					0x0010U	/* 1 stop bit */
#define _0020_SAU_STOP_2					0x0020U	/* 2 stop bits */
/* Setting of data length in CSI and UART modes (DLSmn3 - DLSmn0) */
#define _0006_SAU_LENGTH_7					0x0006U	/* 7-bit data length */
#define _0007_SAU_LENGTH_8					0x0007U	/* 8-bit data length */
#define _0008_SAU_LENGTH_9					0x0008U	/* 9-bit data length */
#define _0009_SAU_LENGTH_10					0x0009U	/* 10-bit data length */
#define _000A_SAU_LENGTH_11					0x000AU	/* 11-bit data length */
#define _000B_SAU_LENGTH_12					0x000BU	/* 12-bit data length */
#define _000C_SAU_LENGTH_13					0x000CU	/* 13-bit data length */
#define _000D_SAU_LENGTH_14					0x000DU	/* 14-bit data length */
#define _000E_SAU_LENGTH_15					0x000EU	/* 15-bit data length */
#define _000F_SAU_LENGTH_16					0x000FU	/* 16-bit data length */

/*
	Serial Output Level Register m (SOLm)
*/
/* Selects inversion of the level of the transmit data of channel n in UART mode */
#define _0000_SAU_CHANNEL0_NORMAL			0x0000U	/* normal bit level */
#define _0001_SAU_CHANNEL0_INVERTED			0x0001U	/* inverted bit level */
#define _0000_SAU_CHANNEL1_NORMAL			0x0000U	/* normal bit level */  
#define _0004_SAU_CHANNEL1_INVERTED			0x0004U	/* inverted bit level */

/*
	Noise Filter Enable Register 0 (NFEN0)
*/
/* Use of noise filter of RXD2/P43 pin (UNFEN2) */
#define _00_SAU_RXD2_FILTER_OFF				0x00U	/* noise filter off */
#define _10_SAU_RXD2_FILTER_ON				0x10U	/* noise filter on */
/* Use of noise filter of SSI01/P77 pin (SNFEN01) */
#define _00_SAU_SSI01_FILTER_OFF			0x00U	/* noise filter off */
#define _02_SAU_SSI01_FILTER_ON				0x02U	/* noise filter on */
/* Use of noise filter of SSI00/P30 or SSI00/P63 pin (SNFEN00) */
#define _00_SAU_SSI00_FILTER_OFF			0x00U	/* noise filter off */
#define _01_SAU_SSI00_FILTER_ON				0x01U	/* noise filter on */

/*
	Format of Serial Status Register mn (SSRmn)
*/
/* Communication status indication flag of channel n (TSFmn) */
#define _0040_SAU_UNDER_EXECUTE				0x0040U	/* communication is under execution */
/* Buffer register status indication flag of channel n (BFFmn) */
#define _0020_SAU_VALID_STORED				0x0020U	/* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEFmn) */
#define _0004_SAU_FRAM_ERROR				0x0004U	/* a framing error occurs during UART reception */
/* Parity error detection flag of channel n (PEFmn) */
#define _0002_SAU_PARITY_ERROR				0x0002U	/* a parity error occurs during UART reception or ACK is not detected during I2C transmission */
/* Overrun error detection flag of channel n (OVFmn) */
#define _0001_SAU_OVERRUN_ERROR				0x0001U	/* an overrun error occurs */

/*
	Serial Channel Start Register m (SSm)
*/
/* Operation start trigger of channel 0 (SSm0) */
#define _0000_SAU_CH0_START_TRG_OFF			0x0000U	/* no trigger operation */
#define _0001_SAU_CH0_START_TRG_ON			0x0001U	/* sets SEm0 to 1 and enters the communication wait status */
/* Operation start trigger of channel 1 (SSm1) */
#define _0000_SAU_CH1_START_TRG_OFF			0x0000U	/* no trigger operation */
#define _0002_SAU_CH1_START_TRG_ON			0x0002U	/* sets SEm1 to 1 and enters the communication wait status */

/*
	Serial Channel Stop Register m (STm)
*/
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SAU_CH0_STOP_TRG_OFF			0x0000U	/* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON			0x0001U	/* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SAU_CH1_STOP_TRG_OFF			0x0000U	/* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON			0x0002U	/* operation is stopped (stop trigger is generated) */

/*
	Format of Serial Flag Clear Trigger Register mn (SIRmn)
*/
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define	_0001_SAU_SIRMN_OVCTMN				0x0001U
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define	_0002_SAU_SIRMN_PECTMN				0x0002U
/* Clear trigger of framing error of channel n (FECTmn) */
#define	_0004_SAU_SIRMN_FECTMN				0x0004U

/*
	Serial Output Enable Register m (SOEm)
*/
/* Serial output enable/disable of channel 0 (SOEm0) */
#define _0000_SAU_CH0_OUTPUT_DISABLE		0x0000U	/* disable output by serial communication operation */
#define _0001_SAU_CH0_OUTPUT_ENABLE			0x0001U	/* enables output by serial communication operation */
/* Serial output enable/disable of channel 1 (SOEm1) */
#define _0000_SAU_CH1_OUTPUT_DISABLE		0x0000U	/* disable output by serial communication operation */
#define _0002_SAU_CH1_OUTPUT_ENABLE			0x0002U	/* enables output by serial communication operation */

/*
	Serial Output Register m (SOm)
*/
/* Serial data output of channel 0 (SOm0) */
#define _0000_SAU_CH0_DATA_OUTPUT_0			0x0000U	/* serial data output value is "0" */
#define _0001_SAU_CH0_DATA_OUTPUT_1			0x0001U	/* serial data output value is "1" */
/* Serial data output of channel 1 (SOm1) */
#define _0000_SAU_CH1_DATA_OUTPUT_0			0x0000U	/* serial data output value is "0" */
#define _0002_SAU_CH1_DATA_OUTPUT_1			0x0002U	/* serial data output value is "1" */
/* Serial clock output of channel 0 (CKOm0) */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0		0x0000U	/* serial clock output value is "0" */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1		0x0100U	/* serial clock output value is "1" */
/* Serial clock output of channel 1 (CKOm1) */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0		0x0000U	/* serial clock output value is "0" */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1		0x0200U	/* serial clock output value is "1" */

/*
	Serial Slave Select Function Enable Register (SSE0)
*/
/* Simple IIC used flag */
#define _00_SAU_IIC_MASTER_FLAG_CLEAR		0x00U
#define _01_SAU_IIC_SEND_FLAG				0x01U
#define _02_SAU_IIC_RECEIVE_FLAG			0x02U
#define _04_SAU_IIC_SENDED_ADDRESS_FLAG		0x04U

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	_EE00_IIC11_DIVISOR					0xEE00U
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
//public
void IIC11_Init(void);
void IIC11_MasterSendStart(UCHAR adr, UCHAR *txbuf, USHORT txnum);
void IIC11_MasterReceiveStart(UCHAR adr, UCHAR *rxbuf, USHORT rxnum);
__interrupt void MD_INTIIC11(void);
//private
void IIC11_Stop(void);
void IIC11_StartCondition(void);
void IIC11_StopCondition(void);
void IIC11_MasterErrorCallback(MD_STATUS flag);
void IIC11_MasterReceiveEndCallback(void);
void IIC11_MasterSendEndCallback(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
