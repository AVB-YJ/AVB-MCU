/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * File Name: can_sch_rx.h                                                   *
 * File Description:                                                         *
******************************************************************************/

#ifndef CAN_SCHEDULER_RX_H
#define CAN_SCHEDULER_RX_H

#include "can_handler_config.h"
#include "can_handler_datatypes.h"
#include "can_sch_config.h"
#include "can_timer_mod_config.h"

/******************************************************************************
******           STRUCTURE TEMPLATE FOR CONFIG TABLE- RX                *******
******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
typedef struct SCH_Rx_Msg_Timeout_Config_Tag
{
  CAN_Timer_Names_T timeout_timer;
  //notifier_function_ptr_t timeout_notifier_function;
} SCH_Rx_Msg_Timeout_Config_T;

#ifdef CAN_CH0_SELECTED
extern const SCH_Rx_Msg_Timeout_Config_T SCH_Rx_Msg_Timeout_Config_Table_Ch0[];
#endif
#ifdef CAN_CH1_SELECTED
extern const SCH_Rx_Msg_Timeout_Config_T SCH_Rx_Msg_Timeout_Config_Table_Ch1[];
#endif
#ifdef CAN_CH2_SELECTED
extern const SCH_Rx_Msg_Timeout_Config_T SCH_Rx_Msg_Timeout_Config_Table_Ch2[];
#endif

extern const canuint8_t Size_Of_Rx_Timeout_Monitor_Tables[];

#endif
/******************************************************************************
******          STRUCTURE TEMPLATE FOR RUN-TIME TABLE- RX               *******
******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
typedef struct SCH_Rx_Msg_Timeout_Runtime_Info_Tag
{
  #ifdef CCA_HMI
  canbool16_t timeout_timer_expired      : 1;
  #else
  canbool8_t timeout_timer_expired       : 1;
  #endif
} SCH_Rx_Msg_Timeout_Runtime_Info_T;
#endif

/******************************************************************************
           START OF PROTOTYPE DECLARATION FOR EXTERN FUNCTIONS - RX
******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
extern void SCH_Rx_Cold_Initialization(canuint8_t channel_number);
extern void SCH_Rx_Periodic_Task(void);
#endif
extern void SCH_Set_Rx_Inactive(canuint8_t channel_number);
extern void SCH_Set_Rx_Active(canuint8_t channel_number);

#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED

/******************************************************************************
*****      START OF PROTOTYPE DECLARATION FOR EXTERN FUNCTIONS            *****
*****       TO BE CALLED BY THE TIMER MODULE (CAN HANDLER)                *****
******************************************************************************/
extern void SCH_Immediate_Process_Rx_Msg_Ch0(CAN_Timer_Names_T timer_name);
extern void SCH_Immediate_Process_Rx_Msg_Ch1(CAN_Timer_Names_T timer_name);
extern void SCH_Immediate_Process_Rx_Msg_Ch2(CAN_Timer_Names_T timer_name);

extern void SCH_Set_Flag_Rx_Msg_Ch0(CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_Rx_Msg_Ch1(CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_Rx_Msg_Ch2(CAN_Timer_Names_T timer_name);

#endif
/******************************************************************************
*****      START OF PROTOTYPE DECLARATION FOR EXTERN FUNCTIONS            *****
*****        TO BE CALLED BY THE VBM MODULE (CAN HANDLER)                 *****
******************************************************************************/
extern void SCH_Rx_Message_Indication_Ch0(canuint8_t msg_handle);
extern void SCH_Rx_Message_Indication_Ch1(canuint8_t msg_handle);
extern void SCH_Rx_Message_Indication_Ch2(canuint8_t msg_handle);


#endif
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
