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
* This device driver was created by CodeGenerator for 78K0R/Fx3
* Filename:	CG_timer.c
* Abstract:	This file implements device driver for TAU module.
* APIlib:	CodeGenerator for 78K0R/Fx3 V2.01 [22 Oct 2010]
* Device:	uPD78F1804_30
* Compiler:	CA78K0R
* Creation date:	5/31/2012
* Created By:       Henson.li
*******************************************************************************
*/

/*
*******************************************************************************
** Pragma directive
*******************************************************************************
*/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "TIMER.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the TAU0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
static void TAU0_Init(void)
{
#ifndef QAC
	TAU0EN = 1U;		/* supply input clock */  //enable timer array unit 0
	TPS0 = _0004_TAU_CKM0_FCLK_4 | _0040_TAU_CKM1_FCLK_4 | _0800_TAU_CKM2_FCLK_8 | _F000_TAU_CKM3_FCLK_15;
	/* Stop all channels */
	TT0 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON | _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON | _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
	/* Mask channel 0 interrupt */
	TMMK00 = 1U;		/* disable INTTM00 interrupt */
	TMIF00 = 0U;		/* clear INTTM00 interrupt flag */
	/* Mask channel 2 interrupt */
	TMMK02 = 1U;		/* disable INTTM02 interrupt */
	TMIF02 = 0U;		/* clear INTTM02 interrupt flag */
	/* Mask channel 3 interrupt */
	TMMK03 = 1U;		/* disable INTTM03 interrupt */
	TMIF03 = 0U;		/* clear INTTM03 interrupt flag */
	/* Mask channel 6 interrupt */
	TMMK06 = 1U;		/* disable INTTM06 interrupt */
	TMIF06 = 0U;		/* clear INTTM06 interrupt flag */
	/* Mask channel 7 interrupt */
	TMMK07 = 1U;		/* disable INTTM07 interrupt */
	TMIF07 = 0U;		/* clear INTTM07 interrupt flag */
	/* Set INTTM00 low priority */
	TMPR100 = 1U;
	TMPR000 = 1U;
	/* Set INTTM03 low priority */
	TMPR103 = 1U;
	TMPR003 = 1U;
	/* Set INTTM07 low priority */
	TMPR107 = 1U;
	TMPR007 = 1U;
	/* Channel 0 used as interval timer */
	TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_MODE_INTERVAL_TIMER | _0001_TAU_START_INT_USED;
	TDR00 = 0x5DC;/*24000000/12/1000HZ=0x5DC*/
	TOM0 &= ~_0001_TAU_CH0_OUTPUT_COMBIN;
	TOL0 &= ~_0001_TAU_CH0_OUTPUT_LEVEL_L;
	TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
#endif
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU0 channel 0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
static void TAU0_Channel0_Start(void)
{
#ifndef QAC
	TMIF00 = 0U;		/* clear INTTM00 interrupt flag */
	TMMK00 = 0U;		/* enable INTTM00 interrupt */
	TS0 |= _0001_TAU_CH0_START_TRG_ON;
#endif
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU0 channel 0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
static void TAU0_Channel0_Stop(void)
{
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
	#ifndef QAC
	TMMK00 = 1U;		/* disable INTTM02 interrupt */
	TMIF00 = 0U;		/* clear INTTM02 interrupt flag */
	#endif
}

static uint16 CPULoad_Channel5_GetTimeRemaining(void)
{
    return (TCR05);
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the TAU1 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Init(void)
{
	TAU1EN = 1U;		/* supply input clock */
	TPS1 = _0000_TAU_CKM0_FCLK_0 | _0040_TAU_CKM1_FCLK_4 | _0800_TAU_CKM2_FCLK_8 | _F000_TAU_CKM3_FCLK_15;
	/* Stop all channels */
	TT1 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON | _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON | _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
	/* Mask channel 2 interrupt */
	TMMK12 = 1U;		/* disable INTTM12 interrupt */
	TMIF12 = 0U;		/* clear INTTM12 interrupt flag */
	/* Set INTTM12 low priority */
	TMPR112 = 1U;
	TMPR012 = 1U;
	/* Channel 2 used as square output function */
	TMR12 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_MODE_INTERVAL_TIMER | _0001_TAU_START_INT_USED;
	TDR12 = _095F_TAU_TDR12_VALUE;
	TOM1 &= ~_0004_TAU_CH2_OUTPUT_COMBIN;
	TOL1 &= ~_0004_TAU_CH2_OUTPUT_LEVEL_L;
	TO1 &= ~_0004_TAU_CH2_OUTPUT_VALUE_1;
	TOE1 |= _0004_TAU_CH2_OUTPUT_ENABLE;
	/* Set TO12 pin */
	P4 &= 0xEFU;	
	PM4 &= 0xEFU;
	TOS1 |= 0x04U;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU1 channel 2 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Channel2_Start(void)
{
	TMIF12 = 0U;		/* clear INTTM12 interrupt flag */
	TMMK12 = 0U;		/* enable INTTM12 interrupt */
	TOE1 |= _0004_TAU_CH2_OUTPUT_ENABLE;
	TS1 |= _0004_TAU_CH2_START_TRG_ON;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU1 channel 2 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Channel2_Stop(void)
{
	TT1 |= _0004_TAU_CH2_STOP_TRG_ON;
	TOE1 &= ~_0004_TAU_CH2_OUTPUT_ENABLE;
	TMMK12 = 1U;		/* disable INTTM12 interrupt */
	TMIF12 = 0U;		/* clear INTTM12 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TAU1 channel 2 register value.
**
**  Parameters:
**	regvalue: value for data register
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Channel2_ChangeTimerCondition(USHORT regvalue)
{
	TDR12 = regvalue;
}

void RCP_Tick_Start(void)
{
    TAU0_Channel0_Start();
}
void RCP_Tick_Stop(void)
{
    TAU0_Channel0_Stop();
}

void Timer_Array_Initialize(void)
{
   TAU0_Init();
   TAU1_Init();
}

void LCD_DIM_PWM_Backlighting_Start(void)
{
	 TAU1_Channel2_Start();
}
void LCD_DIM_PWM_Backlighting_Stop(void)
{
	TAU1_Channel2_Stop();
}

void Timer_Tick_Enable_Interrupt(void)
{
#ifndef QAC
    TMMK00 = 0U;		/* enable INTTM00 interrupt */
#endif
}
void Timer_Tick_Disable_Interrupt(void)
{
#ifndef QAC
    TMMK00 = 1U;		/* disable INTTM00 interrupt */
#endif
}

/*system throughput measure*/
uint16 RCP_CPU_Load_TimerRemain(void)
{
    return (CPULoad_Channel5_GetTimeRemaining());
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
