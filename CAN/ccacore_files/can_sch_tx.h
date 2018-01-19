/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * File Name: can_sch_tx.h                                                   *
 * File Description:                                                         *
******************************************************************************/

#ifndef CAN_SCHEDULER_TX_H
#define CAN_SCHEDULER_TX_H

#include "can_handler_datatypes.h"
#include "can_sch_config.h"
#include "can_timer_mod_config.h"

/*typedef enum
{
   #ifdef ON_EVENT_MSG_SUPPORTED
   ON_EVENT,
   #endif
   #ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   ON_EVENT_WITH_MIN_UPDATE_TIME,
   #endif
   #ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
   N_TIMES_ON_EVENT,
   #endif
   #ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME,
   #endif
   #ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
   CYCLIC_ON_INIT,
   #endif
   #ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
   CYCLIC_ON_REQUEST,
   #endif
   #ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
   CYCLIC_AND_ON_EVENT,
   #endif
   #ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME,
   #endif
   #ifdef  BAF_MSG_SUPPORTED
   BAF,
   #endif
   #ifdef  FAST_MSG_SUPPORTED
   FAST
   #endif
} Message_Transmission_Mode_T; moved to can_sch_config.h*/

typedef enum
{
   CAN_SCH_MESSAGE_PASSIVE,
   CAN_SCH_MESSAGE_ACTIVE
}Signal_State_T;

typedef struct Start_And_End_Index_Struct_Tag
{
  canuint8_t start_index;
  canuint8_t end_index;
}Start_And_End_Index_Struct_T;

/******************************************************************************
******          STRUCTURE TEMPLATES FOR CONFIG TABLES- TX               *******
******************************************************************************/
#ifdef ON_EVENT_MSG_SUPPORTED
typedef struct ON_EVENT_CONFIG_TAG
{
   canuint8_t msg_handle;
   #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} ON_EVENT_MSG_CONFIG_T;

extern const ON_EVENT_MSG_CONFIG_T ON_EVENT_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_On_Event_Table;
#endif

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
typedef struct ON_EVENT_WITH_MIN_UPDATE_TIME_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T min_delay_timer;
   #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T;

extern const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T
ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_On_Event_With_Min_Update_Table;
#endif

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
typedef struct N_TIMES_ON_EVENT_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   canuint8_t transmit_count; /* transmit count on event is restricted to 255 */
   #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} N_TIMES_ON_EVENT_MSG_CONFIG_T;

extern const N_TIMES_ON_EVENT_MSG_CONFIG_T N_TIMES_ON_EVENT_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_N_Times_On_Event_Table;
#endif

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
typedef struct N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T min_delay_timer;
   canuint8_t transmit_count; /* transmit count on event is restricted to 255 */
   #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T;

extern const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T
N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_N_Times_On_Event_With_Min_Update_Table;
#endif

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
typedef struct CYCLIC_ON_INIT_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T cyclic_timer;
   #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} CYCLIC_ON_INIT_MSG_CONFIG_T;

extern const CYCLIC_ON_INIT_MSG_CONFIG_T CYCLIC_ON_INIT_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_Cyclic_On_Init_Msg_Table;
#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
typedef struct CYCLIC_ON_REQUEST_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T cyclic_timer;
   #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} CYCLIC_ON_REQUEST_MSG_CONFIG_T;

extern const CYCLIC_ON_REQUEST_MSG_CONFIG_T
CYCLIC_ON_REQUEST_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_Cyclic_On_Request_Msg_Table;
#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
typedef struct CYCLIC_AND_ON_EVENT_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T cyclic_timer;
   #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} CYCLIC_AND_ON_EVENT_MSG_CONFIG_T;

extern const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T
                                        CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_Cyclic_And_On_Event_Msg_Table;
#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
typedef struct CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T cyclic_timer;
   CAN_Timer_Names_T min_delay_timer;
   #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
 #endif
} CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T;

extern const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T
CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_Cyclic_And_On_Event_With_Min_Update_Time_Msg_Table;
#endif

#ifdef BAF_MSG_SUPPORTED
typedef struct BAF_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T cyclic_timer;
   #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} BAF_MSG_CONFIG_T;

extern const BAF_MSG_CONFIG_T BAF_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_BAF_Msg_Table;
#endif

#ifdef FAST_MSG_SUPPORTED
typedef struct FAST_MSG_CONFIG_TAG
{
   canuint8_t msg_handle;
   CAN_Timer_Names_T fast_timer;
   CAN_Timer_Names_T slow_timer;
   #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
   CAN_Timer_Names_T timeout_timer;
   #endif
   #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
   CAN_Timer_Names_T startup_delay_timer;
   #endif
} FAST_MSG_CONFIG_T;

extern const FAST_MSG_CONFIG_T FAST_MSG_CONFIG_Table[];

extern const canuint8_t Size_Of_FAST_Msg_Table;
#endif

/******************************************************************************
******         STRUCTURE TEMPLATES FOR RUN-TIME TABLES- TX              *******
******************************************************************************/
#ifdef ON_EVENT_MSG_SUPPORTED
typedef struct ON_EVENT_MSG_Runtime_Info_Tag
{
   canbool8_t event_occurred            : 1;
   #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
   canbool8_t timeout_timer_expired     : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} ON_EVENT_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_ON_EVENT_MSG (\
NUM_OF_ON_EVENT_MSG_CH0 + \
NUM_OF_ON_EVENT_MSG_CH1 + \
NUM_OF_ON_EVENT_MSG_CH2)

#endif

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
typedef struct ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_Tag
{
   canbool8_t event_occurred            : 1;
   canbool8_t min_delay_timer_expired   : 1;
   #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   canbool8_t timeout_timer_expired     : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG (\
NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 + \
NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 + \
NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2)

#endif

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
typedef struct N_TIMES_ON_EVENT_MSG_Runtime_Info_Tag
{
   canuint8_t transmit_count;
   canbool8_t event_occurred        : 1;
   #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
   canbool8_t timeout_timer_expired : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} N_TIMES_ON_EVENT_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_N_TIMES_ON_EVENT_MSG (\
NUM_OF_N_TIMES_ON_EVENT_MSG_CH0 + \
NUM_OF_N_TIMES_ON_EVENT_MSG_CH1 + \
NUM_OF_N_TIMES_ON_EVENT_MSG_CH2)

#endif

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
typedef struct N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_Tag
{
   canuint8_t transmit_count;
   canbool8_t event_occurred            : 1;
   canbool8_t min_delay_timer_expired   : 1;
   #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   canbool8_t timeout_timer_expired     : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG (\
NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 + \
NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 + \
NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2)

#endif

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
typedef struct CYCLIC_ON_INIT_MSG_Runtime_Info_Tag
{
   #ifdef CCA_HMI
   canbool16_t cyclic_timer_expired       : 1;
   #else
   canbool8_t cyclic_timer_expired        : 1;
   #endif
   #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
   #ifdef CCA_HMI
   canbool16_t timeout_timer_expired      : 1;
   #else
   canbool8_t timeout_timer_expired       : 1;
   #endif
   #endif
   #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
   #ifdef CCA_HMI
   canbool16_t startup_delay_timer_expired : 1;
   #else
   canbool8_t startup_delay_timer_expired  : 1;
   #endif
   #endif
} CYCLIC_ON_INIT_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_CYCLIC_ON_INIT_MSG (\
NUM_OF_CYCLIC_ON_INIT_MSG_CH0 + \
NUM_OF_CYCLIC_ON_INIT_MSG_CH1 + \
NUM_OF_CYCLIC_ON_INIT_MSG_CH2)

#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
typedef struct CYCLIC_ON_REQUEST_MSG_Runtime_Info_Tag
{
   canbool8_t tx_requested            :  1;
   canbool8_t cyclic_timer_expired    :  1;
   #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
   canbool8_t timeout_timer_expired   :  1;
   #endif
} CYCLIC_ON_REQUEST_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_CYCLIC_ON_REQUEST_MSG (\
NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0 + \
NUM_OF_CYCLIC_ON_REQUEST_MSG_CH1 + \
NUM_OF_CYCLIC_ON_REQUEST_MSG_CH2)

#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
typedef struct CYCLIC_AND_ON_EVENT_MSG_Runtime_Info_Tag
{
   canbool8_t event_occurred         : 1;
   canbool8_t cyclic_timer_expired   : 1;
   #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
   canbool8_t timeout_timer_expired  : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} CYCLIC_AND_ON_EVENT_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_CYCLIC_AND_ON_EVENT_MSG (\
NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0 + \
NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH1 + \
NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH2)

#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
typedef struct CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_Tag
{
   canbool8_t event_occurred           : 1;
   canbool8_t cyclic_timer_expired     : 1;
   canbool8_t min_delay_timer_expired  : 1;
   #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   canbool8_t timeout_timer_expired    : 1;
   #endif
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG (\
NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 + \
NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 + \
NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2)

#endif

#ifdef BAF_MSG_SUPPORTED
typedef struct BAF_MSG_Runtime_Info_Tag
{
   canbool8_t message_is_active       : 1;
   canbool8_t cyclic_timer_expired    : 1;
   #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
   canbool8_t timeout_timer_expired   : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} BAF_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_BAF_MSG (\
NUM_OF_BAF_MSG_CH0 + \
NUM_OF_BAF_MSG_CH1 + \
NUM_OF_BAF_MSG_CH2)

#endif

#ifdef FAST_MSG_SUPPORTED
typedef struct FAST_MSG_Runtime_Info_Tag
{
   canbool8_t message_is_active     : 1;
   canbool8_t slow_timer_expired    : 1;
   canbool8_t fast_timer_expired    : 1;
   #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
   canbool8_t timeout_timer_expired : 1;
   #endif
   #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
   canbool8_t startup_delay_timer_expired: 1;
   #endif
} FAST_MSG_Runtime_Info_T;

#define TOTAL_NUM_OF_FAST_MSG (\
NUM_OF_FAST_MSG_CH0 + \
NUM_OF_FAST_MSG_CH1 + \
NUM_OF_FAST_MSG_CH2)

#endif

/******************************************************************************
*****      START OF PROTOTYPE DECLARATION FOR EXTERN FUNCTIONS            *****
*****       TO BE CALLED BY THE AIF MODULE (CAN HANDLER)                  *****
******************************************************************************/
extern void SCH_Tx_Cold_Initialization(canuint8_t channel_number);
extern void SCH_Tx_Periodic_Task(void);
extern void SCH_Enable_Periodic_Tx_Messages(canuint8_t channel_number);
extern void SCH_Disable_Periodic_Tx_Messages(canuint8_t channel_number);
extern void SCH_Set_Tx_Active(canuint8_t channel_number);
extern void SCH_Set_Tx_Inactive(canuint8_t channel_number);

extern void SCH_Set_Event_Flag(canuint8_t msg_handle, Message_Transmission_Mode_T
                                                                     msg_type);

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
extern void SCH_Stop_Tx_Cyclic_On_Init_Msg(canuint8_t msg_handle);
#endif
#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
extern void SCH_Set_or_Clr_Req_For_Cyclic_On_Request_Msg(canuint8_t
                               msg_handle, canbool8_t request);
#endif
#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
extern void SCH_Stop_Tx_Cyclic_And_On_Event_Msg(canuint8_t msg_handle);
extern void SCH_Start_Tx_Cyclic_And_On_Event_Msg(canuint8_t msg_handle);
#endif
#ifdef BAF_MSG_SUPPORTED
extern void SCH_Update_Msg_Status_For_BAF_Msg(canuint8_t msg_handle,
                                             canbool8_t msg_status);
#endif
#ifdef FAST_MSG_SUPPORTED
extern void SCH_Update_Msg_Status_For_FAST_Msg(canuint8_t msg_handle,
                                              canbool8_t msg_status);
#endif

/******************************************************************************
*****      START OF PROTOTYPE DECLARATION FOR EXTERN FUNCTIONS            *****
*****      TO BE CALLED BY THE TIMER MODULE (CAN HANDLER)                 *****
******************************************************************************/
#ifdef ON_EVENT_MSG_SUPPORTED
extern void SCH_Immediate_Process_On_Event_Msg(CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_On_Event_Msg(CAN_Timer_Names_T timer_name);
#endif

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
extern void SCH_Immediate_Process_On_Event_With_Min_Update_Time_Msg(
                                      CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_On_Event_With_Min_Update_Time_Msg(CAN_Timer_Names_T
                                                                timer_name);
#endif

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
extern void SCH_Immediate_Process_N_Times_On_Event_Msg(CAN_Timer_Names_T
                                                             timer_name);
extern void SCH_Set_Flag_N_Times_On_Event_Msg(CAN_Timer_Names_T timer_name);
#endif

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
extern void
SCH_Immediate_Process_N_Times_On_Event_With_Min_Update_Time_Msg(
                                   CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                     CAN_Timer_Names_T timer_name);
#endif

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
extern void SCH_Immediate_Process_Cyclic_On_Init_Msg(CAN_Timer_Names_T
                                                           timer_name);
extern void SCH_Set_Flag_Cyclic_On_Init_Msg(CAN_Timer_Names_T timer_name);
#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
extern void SCH_Immediate_Process_Cyclic_On_Request_Msg(CAN_Timer_Names_T
                                                           timer_name);
extern void SCH_Set_Flag_Cyclic_On_Request_Msg(CAN_Timer_Names_T timer_name);
#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
extern void SCH_Immediate_Process_Cyclic_And_On_Event_Msg(CAN_Timer_Names_T
                                                               timer_name);
extern void SCH_Set_Flag_Cyclic_And_On_Event_Msg(CAN_Timer_Names_T timer_name);
#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
extern void
SCH_Immediate_Process_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                      CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                       CAN_Timer_Names_T timer_name);
extern void SCH_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(canuint8_t
                                                          msg_handle);
#endif

#ifdef BAF_MSG_SUPPORTED
extern void SCH_Immediate_Process_BAF_Msg(CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_BAF_Msg(CAN_Timer_Names_T timer_name);
#endif

#ifdef FAST_MSG_SUPPORTED
extern void SCH_Immediate_Process_FAST_Msg(CAN_Timer_Names_T timer_name);
extern void SCH_Set_Flag_FAST_Msg(CAN_Timer_Names_T timer_name);
#endif

/******************************************************************************
*****      START OF PROTOTYPE DECLARATION FOR EXTERN FUNCTIONS            *****
*****       TO BE CALLED BY THE VBM MODULE (CAN HANDLER)                 *****
******************************************************************************/
extern void SCH_Tx_Message_Confirmation(canuint8_t msg_handle);


#endif
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
