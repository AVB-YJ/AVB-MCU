/*******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved               *
 * REVISION: 1.0                                                               *
 * AUTHORS: Prakash, Sandeep                                                   *
 * Project: CCA - CAN Timer Module                                             *
 * File Name:  can_timer_mod.h                                                 *
 * Description: This file contains timer function prototypes                   *
 ******************************************************************************/
#ifndef CAN_TIMER_MOD_H
#define CAN_TIMER_MOD_H

#include "can_handler_datatypes.h"

typedef enum 
{
   ON_INIT = 0,
   ON_REQUEST
}Timer_Activation_Method_T;

typedef enum
{
   ONE_SHOT = 0,
   CONT_RUNNING
}Type_Of_Timers_T;

typedef enum 
{
   NOTIFY_EARLY = 0,
   NOTIFY_NORMAL
}Expiry_Notification_Method_T;

typedef enum 
{
   PROCESS_IN_NOTIFIER = 0,
   PROCESS_IN_PERIODIC_TASK
}Process_Method_T;

typedef struct CAN_Timer_Param_Tbl_Tag
{
   canuint16_t set_timer_value;
   Timer_Activation_Method_T timer_activation_method;
   Type_Of_Timers_T timer_type;
   Expiry_Notification_Method_T timer_expiry_condition;
   function_pointer_T expiry_notifier_function;
   Process_Method_T process_Status;
}CAN_Timer_Param_Tbl_T;

extern const CAN_Timer_Param_Tbl_T CAN_Timer_Parameter_Table[];
extern const canuint8_t Size_Of_Timer_Param_Table;

typedef enum 
{
   CAN_TIMER_INACTIVE = 0,
   CAN_TIMER_ACTIVE
}Timer_Status_T;


typedef struct CAN_Timer_Runtime_Tbl_Tag
{
   canuint16_t timer_count;
   Timer_Status_T timer_status;
}CAN_Timer_Runtime_Tbl_T;

extern void CAN_TIMER_Cold_Init(canuint8_t channel_num);
extern void CAN_TIMER_Task(void);
extern void CAN_TIMER_Start(canuint8_t CAN_Timer_Name);
extern void CAN_TIMER_Cancel(canuint8_t CAN_Timer_Name);
void CAN_TIMER_Warm_Init(canuint8_t channel_num);

#endif
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
