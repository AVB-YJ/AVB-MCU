/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - Driver                                                     *
 * File Name:  can_drv_init_misc.h                                           *
 * File Description:                                                         *
 * This file contains macro definitions related to initializing the on-chip  *
 * CAN controller,error handling, sleep-wakeup handling and interuupt control*
 *****************************************************************************/
#ifndef CAN_DRV_INIT_MISC_H
#define CAN_DRV_INIT_MISC_H

#include "can_drv_config.h"


extern Boolean_Returnvalue_T Buss_Off_Channel0;
extern canuint8_t Buss_Off_Channel0_Count;

/*******************************************************************************
*              EXTERN FUNCTION DECLARATIONS  FOR CAN HANDLER                   *
*******************************************************************************/
#ifdef ERROR_INTERRUPT_MODE

#ifdef CAN_CH0_SELECTED
extern /*CAN_INTERRUPT_ERROR_0*/ void CD_Error_ISR_Channel_0(void);
#endif

#ifdef CAN_CH1_SELECTED
extern CAN_INTERRUPT_ERROR_1 void CD_Error_ISR_Channel_1(void);
#endif

#ifdef CAN_CH2_SELECTED
extern CAN_INTERRUPT_ERROR_2 void CD_Error_ISR_Channel_2(void);
#endif

#endif

#ifdef WAKEUP_INTERRUPT_MODE

#ifdef CAN_CH0_SELECTED
extern CAN_INTERRUPT_WAKEUP_0 void CD_Wakeup_ISR_Channel_0(void);
#endif

#ifdef CAN_CH1_SELECTED
extern CAN_INTERRUPT_WAKEUP_1 void CD_Wakeup_ISR_Channel_1(void);
#endif

#ifdef CAN_CH2_SELECTED
extern CAN_INTERRUPT_WAKEUP_2 void CD_Wakeup_ISR_Channel_2(void);
#endif

#endif

extern void CD_Shut_Communication_Down(canuint8_t channel_number);


/*******************************************************************************
*          EXTERN FUNCTION DECLARATIONS FOR APPLICATION                       *
*******************************************************************************/
extern Boolean_Returnvalue_T CD_Cold_Initialization(canuint8_t channel_number);
extern Boolean_Returnvalue_T CD_BusOff_Initialization(canuint8_t channel_number);
extern Boolean_Returnvalue_T CD_Wakeup_Initialization(canuint8_t channel_number);
extern void CD_Warm_Initialization(canuint8_t channel_number);
extern void CD_Init_Misc(void);
extern void CD_Disable_All_Interrupts(canuint8_t channel_number);
extern void CD_Enable_All_Interrupts(canuint8_t channel_number);
#ifdef CAN_INTERRUPTS_SEPARATE_ENABLING
extern void CD_Enable_Interrupt(canuint8_t channel_num, canuint8_t CAN_Int_Type);
extern void CD_Disable_Interrupt(canuint8_t channel_num, canuint8_t CAN_Int_Type);
#endif

#ifndef ERROR_INTERRUPT_MODE
extern void CD_Poll_Error(canuint8_t channel_number);
#endif

#ifndef WAKEUP_INTERRUPT_MODE
extern void CD_Poll_Wakeup(canuint8_t channel_number);
#endif

/*******************************************************************************
*          EXTERN FUNCTION DECLARATIONS FOR APPLICATION / NM                   *
*******************************************************************************/
#ifdef CAN_SLEEP_MODE_AVAILABLE
extern Sleep_Result_T CD_Go_To_Sleep(canuint8_t channel_number);
extern Sleep_Result_T CD_Cancel_Sleep_State(canuint8_t channel_number);
#endif

extern Boolean_Returnvalue_T CD_Get_Buss_Off_Status_Channel0(void);
extern void CD_Set_Buss_Off_Status_Channel0(Boolean_Returnvalue_T  bus_off_value);
extern void CD_Increment_Buss_Off_Channel0_Count(void);
extern void CD_Reset_Buss_Off_Channel0_Count(void);
extern canuint8_t CD_Get_Buss_Off_Channel0_Count(void);
#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
