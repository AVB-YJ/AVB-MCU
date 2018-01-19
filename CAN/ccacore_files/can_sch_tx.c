/******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS: Prakash, Sandeep                                                  *
 * File Name: can_sch_tx.c                                                    *
 * File Description:                                                          *
******************************************************************************/
#include "can_sch_tx.h"
#include "can_timer_mod.h"
#include "can_handler_config.h"
#include "can_aif_tx.h"
#include "can_handler_appl_notifier_functions.h"

/******************************************************************************
*****  TABLE DECLARATIONS AND DEFINITIONS TO STORE START AND END INDICES  *****
*****                     FOR EFFICIENT SEARCH                            *****
******************************************************************************/
// No Transmit messages for Tata program
//amit
// these table were defined twice
/*#ifdef CAN_CH0_SELECTED
static const Start_And_End_Index_Struct_T Start_And_End_Index_Ch0[];
#endif
#ifdef CAN_CH1_SELECTED
static const Start_And_End_Index_Struct_T Start_And_End_Index_Ch1[];
#endif
#ifdef CAN_CH2_SELECTED
static const Start_And_End_Index_Struct_T Start_And_End_Index_Ch2[];
#endif
*/

#ifdef CAN_CH0_SELECTED
static const Start_And_End_Index_Struct_T Start_And_End_Index_Ch0[] =
{
  #ifdef  ON_EVENT_MSG_SUPPORTED
  #if (0 < NUM_OF_ON_EVENT_MSG_CH0)
  {0, NUM_OF_ON_EVENT_MSG_CH0},
  #endif
  #endif
  #ifdef  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  #if (0 < NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0)
  {0, NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 },
  #endif
  #endif
  #ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
  #if (0 < NUM_OF_N_TIMES_ON_EVENT_MSG_CH0)
  {0, NUM_OF_N_TIMES_ON_EVENT_MSG_CH0},
  #endif
  #endif
  #ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  #if (0 < NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0)
  {0, NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0},
  #endif
  #endif
  #ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_ON_INIT_MSG_CH0)
  {0, NUM_OF_CYCLIC_ON_INIT_MSG_CH0},
  #endif
  #endif
  #ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0)
  {0, NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0 },
  #endif
  #endif
  #ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0)
  {0, NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0},
  #endif
  #endif
  #ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0)
  {0, NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0},
  #endif
  #endif
  #ifdef  BAF_MSG_SUPPORTED
  #if (0 < NUM_OF_BAF_MSG_CH0)
  {0, NUM_OF_BAF_MSG_CH0},
  #endif
  #endif
  #ifdef  FAST_MSG_SUPPORTED
  #if (0 < NUM_OF_FAST_MSG_CH0)
  {0, NUM_OF_FAST_MSG_CH0},
  #endif
  #endif
  {0, 0},
};
#endif
#ifdef CAN_CH1_SELECTED
static const Start_And_End_Index_Struct_T Start_And_End_Index_Ch1[] =
{
  #ifdef  ON_EVENT_MSG_SUPPORTED
  #if (0 < NUM_OF_ON_EVENT_MSG_CH1)
  {NUM_OF_ON_EVENT_MSG_CH0, 
    NUM_OF_ON_EVENT_MSG_CH0 + NUM_OF_ON_EVENT_MSG_CH1},
  #endif
  #endif
  #ifdef  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  #if (0 < NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1)
  {NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0, 
    NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 + 
    NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1},
  #endif
  #endif
  #ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
  #if (0 < NUM_OF_N_TIMES_ON_EVENT_MSG_CH1)
  {NUM_OF_N_TIMES_ON_EVENT_MSG_CH0, 
    NUM_OF_N_TIMES_ON_EVENT_MSG_CH0 + NUM_OF_N_TIMES_ON_EVENT_MSG_CH1},
  #endif
  #endif
  #ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  #if (0 < NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1)
  {NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0, 
    NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 +
    NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1},
  #endif
  #endif
  #ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_ON_INIT_MSG_CH1)
  {NUM_OF_CYCLIC_ON_INIT_MSG_CH0, 
    NUM_OF_CYCLIC_ON_INIT_MSG_CH0 + NUM_OF_CYCLIC_ON_INIT_MSG_CH1},
  #endif
  #endif
  #ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_ON_REQUEST_MSG_CH1)
  {NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0, 
    NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0 + NUM_OF_CYCLIC_ON_REQUEST_MSG_CH1},
  #endif
  #endif
  #ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH1)
  {NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0, 
    NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0 +NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH1},
  #endif
  #endif
  #ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  #if (0 < NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1)
  {NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0, 
    NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 +
    NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1},
  #endif
  #endif
  #ifdef  BAF_MSG_SUPPORTED
  #if (0 < NUM_OF_BAF_MSG_CH1)
  {NUM_OF_BAF_MSG_CH0, 
    NUM_OF_BAF_MSG_CH0 + NUM_OF_BAF_MSG_CH1},
  #endif
  #endif
  #ifdef  FAST_MSG_SUPPORTED
  #if (0 < NUM_OF_FAST_MSG_CH1)
  {NUM_OF_FAST_MSG_CH0, 
    NUM_OF_FAST_MSG_CH0 + NUM_OF_FAST_MSG_CH1}
  #endif
  #endif
};
#endif
#ifdef CAN_CH2_SELECTED
static const Start_And_End_Index_Struct_T Start_And_End_Index_Ch2[] =
{
  {NUM_OF_ON_EVENT_MSG_CH0 + NUM_OF_ON_EVENT_MSG_CH1, 
     NUM_OF_ON_EVENT_MSG_CH0 + NUM_OF_ON_EVENT_MSG_CH1 +
     NUM_OF_ON_EVENT_MSG_CH2},
  {NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 + 
   NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1, 
     NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 + 
     NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 +
     NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2},
  {NUM_OF_N_TIMES_ON_EVENT_MSG_CH0 + NUM_OF_N_TIMES_ON_EVENT_MSG_CH1, 
     NUM_OF_N_TIMES_ON_EVENT_MSG_CH0 + NUM_OF_N_TIMES_ON_EVENT_MSG_CH1 +
     NUM_OF_N_TIMES_ON_EVENT_MSG_CH2},
  {NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 +
   NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1, 
     NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 +
     NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 +
     NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2},
  {NUM_OF_CYCLIC_ON_INIT_MSG_CH0 + NUM_OF_CYCLIC_ON_INIT_MSG_CH1, 
     NUM_OF_CYCLIC_ON_INIT_MSG_CH0 + NUM_OF_CYCLIC_ON_INIT_MSG_CH1 +
     NUM_OF_CYCLIC_ON_INIT_MSG_CH2},
  {NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0 + NUM_OF_CYCLIC_ON_REQUEST_MSG_CH1, 
     NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0 + NUM_OF_CYCLIC_ON_REQUEST_MSG_CH1 +
     NUM_OF_CYCLIC_ON_REQUEST_MSG_CH2},
  {NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0 + NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH1, 
     NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0 + NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH1 +
     NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH2},
  {NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 +
   NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1, 
     NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 +
     NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 +
     NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2},
  {NUM_OF_BAF_MSG_CH0 + NUM_OF_BAF_MSG_CH1, 
     NUM_OF_BAF_MSG_CH0 + NUM_OF_BAF_MSG_CH1 + NUM_OF_BAF_MSG_CH2},
  {NUM_OF_FAST_MSG_CH0 + NUM_OF_FAST_MSG_CH1, 
     NUM_OF_FAST_MSG_CH0 + NUM_OF_FAST_MSG_CH1 + NUM_OF_FAST_MSG_CH2}
};
#endif

static const Start_And_End_Index_Struct_T* Tx_Ch_Index[] =
{
  #ifdef CAN_CH0_SELECTED
  Start_And_End_Index_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  Start_And_End_Index_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  Start_And_End_Index_Ch2
  #endif
};

/******************************************************************************
*****                            MACROS                                   *****
******************************************************************************/
#define SCH_INVALID_REQUEST                                               0xFF 

/******************************************************************************
*****                           STATIC VARIABLES                          *****
******************************************************************************/
static canbool8_t Periodic_Tx_Enabled[NUMBER_OF_CHANNELS_SUPPORTED];
static canbool8_t Tx_State_Activated[NUMBER_OF_CHANNELS_SUPPORTED];

#ifdef ON_EVENT_MSG_SUPPORTED
ON_EVENT_MSG_Runtime_Info_T ON_EVENT_MSG_Runtime_Info
[TOTAL_NUM_OF_ON_EVENT_MSG];
#endif

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T
ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info
[TOTAL_NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG];
#endif

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
N_TIMES_ON_EVENT_MSG_Runtime_Info_T  
N_TIMES_ON_EVENT_MSG_Runtime_Info[TOTAL_NUM_OF_N_TIMES_ON_EVENT_MSG];
#endif

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T 
N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info
[TOTAL_NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG];
#endif

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
CYCLIC_ON_INIT_MSG_Runtime_Info_T 
CYCLIC_ON_INIT_MSG_Runtime_Info[TOTAL_NUM_OF_CYCLIC_ON_INIT_MSG];
#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
CYCLIC_ON_REQUEST_MSG_Runtime_Info_T 
CYCLIC_ON_REQUEST_MSG_Runtime_Info[TOTAL_NUM_OF_CYCLIC_ON_REQUEST_MSG];
#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
CYCLIC_AND_ON_EVENT_MSG_Runtime_Info_T 
CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[TOTAL_NUM_OF_CYCLIC_AND_ON_EVENT_MSG];
#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T 
CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info
[TOTAL_NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG];
#endif

#ifdef BAF_MSG_SUPPORTED
BAF_MSG_Runtime_Info_T BAF_MSG_Runtime_Info[TOTAL_NUM_OF_BAF_MSG];
#endif

#ifdef FAST_MSG_SUPPORTED
FAST_MSG_Runtime_Info_T FAST_MSG_Runtime_Info[TOTAL_NUM_OF_FAST_MSG];
#endif

/******************************************************************************
*****           PROTOTYPE DECLARATION FOR STATIC FUNCTIONS                *****
******************************************************************************/
void SCH_Tx_Periodic_Task_For_Channel(canuint8_t channel_number);
 canuint8_t SCH_Get_Index_From_Msg_Handle(Message_Transmission_Mode_T 
                                             msg_type, canuint8_t msg_handle);
 void Start_All_Tx_Timers(canuint8_t channel_number);
 void Cancel_All_Tx_Timers(canuint8_t channel_number);
 void Start_Cyclic_MinDelay_And_Timeout_Timers(canuint8_t channel_number);
 void Cancel_Cyclic_MinDelay_And_Timeout_Timers(canuint8_t channel_number);

#ifdef ON_EVENT_MSG_SUPPORTED
 void Cold_Init_For_On_Event_Msg(canuint8_t channel_number);
 canuint8_t SCH_Get_Index_From_Msg_Handle_On_Event(canuint8_t msg_handle);
 void Periodic_Task_For_On_Event_Msg(canuint8_t channel_number);
 void Check_And_Queue_For_Tx_On_Event_Msg(canuint8_t index);
 void Set_Event_Flag_For_On_Event_Msg(canuint8_t index);
//static void SCH_Queue_For_Tx_On_Event_Msg(canuint8_t index);
 void SCH_Timeout_Expiry_Notifier_Function_On_Event_Msg(canuint8_t index);
 void SCH_Set_Startup_Delay_Expiry_Flag_On_Event_Msg(canuint8_t index);
#endif

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
static void Cold_Init_For_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                               channel_number);
static canuint8_t SCH_Get_Index_From_Msg_Handle_On_Event_With_Min_Update_Time(
                                                           canuint8_t msg_handle);
static void Periodic_Task_For_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                                channel_number);
static void Check_And_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void Set_Event_Flag_For_On_Event_With_Min_Update_Time_Msg(canuint8_t index);
static void SCH_Set_Min_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void SCH_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(canuint8_t index);
static void 
SCH_Timeout_Expiry_Notifier_Function_On_Event_With_Min_Update_Time_Msg(canuint8_t
                                                                        index);
static void 
SCH_Set_Startup_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                                        index);
#endif

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
static void Cold_Init_For_N_Times_On_Event_Msg(canuint8_t channel_number);
static canuint8_t SCH_Get_Index_From_Msg_Handle_N_Times_On_Event(canuint8_t 
                                                                   msg_handle);
static void Periodic_Task_For_N_Times_On_Event_Msg(canuint8_t channel_number);
static void Check_And_Queue_For_Tx_N_Times_On_Event_Msg(canuint8_t index);
static void Set_Event_Flag_For_N_Times_On_Event_Msg(canuint8_t index);
static void SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_Msg(canuint8_t
                                                                       index);
static void SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_Msg(canuint8_t 
                                                                     index);
#endif

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
static void Cold_Init_For_N_Times_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                             channel_number);
static canuint8_t 
SCH_Get_Index_From_Msg_Handle_N_Times_On_Event_With_Min_Update_Time(canuint8_t 
                                                                  msg_handle);
static void Periodic_Task_For_N_Times_On_Event_With_Min_Update_Time_Msg(canuint8_t
                                                                channel_number);
static void Check_And_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void Set_Event_Flag_For_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                           canuint8_t index);
static void 
SCH_Set_Min_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                         canuint8_t index);
static void SCH_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                         canuint8_t index);
static void 
SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void 
SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
#endif

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
 void Cold_Init_For_Cyclic_On_Init_Msg(canuint8_t channel_number);
 canuint8_t SCH_Get_Index_From_Msg_Handle_Cyclic_On_Init(canuint8_t msg_handle);
 void Start_Cyclic_And_Timeout_Timers_Cyclic_On_Init(canuint8_t 
                                                               channel_number);
 void Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Init(canuint8_t 
                                                               channel_number);
 void Periodic_Task_For_Cyclic_On_Init_Msg(canuint8_t channel_number);
 void Check_And_Queue_For_Tx_Cyclic_On_Init_Msg(canuint8_t index);
 void SCH_Set_Timer_Expiry_Flag_Cyclic_On_Init_Msg(canuint8_t index);
 void SCH_Queue_For_Tx_Cyclic_On_Init_Msg(canuint8_t index);
 void SCH_Timeout_Notifier_Function_Cyclic_On_Init_Msg(canuint8_t index);
 void SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_On_Init_Msg(canuint8_t index);
#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
static void Cold_Init_For_Cyclic_On_Request_Msg(canuint8_t channel_number);
static canuint8_t SCH_Get_Index_From_Msg_Handle_Cyclic_On_Request(canuint8_t 
                                                                   msg_handle);
static void Start_Cyclic_And_Timeout_Timers_Cyclic_On_Request(canuint8_t 
                                                               channel_number);
static void Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Request(canuint8_t 
                                                               channel_number);
static void Periodic_Task_For_Cyclic_On_Request_Msg(canuint8_t channel_number);
static void Check_And_Queue_For_Tx_Cyclic_On_Request_Msg(canuint8_t index);
static void SCH_Set_Timer_Expiry_Flag_Cyclic_On_Request_Msg(canuint8_t index);
static void SCH_Queue_For_Tx_Cyclic_On_Request_Msg(canuint8_t index);
static void SCH_Timeout_Notifier_Function_Cyclic_On_Request_Msg(canuint8_t index);
#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
static void Cold_Init_For_Cyclic_And_On_Event_Msg(canuint8_t channel_number);
static canuint8_t SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event(canuint8_t 
                                                                   msg_handle);
static void Start_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event(
                                                       canuint8_t channel_number);
static void Cancel_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event(
                                                       canuint8_t channel_number);
static void Periodic_Task_For_Cyclic_And_On_Event_Msg(canuint8_t channel_number);
static void Check_And_Queue_For_Tx_Cyclic_And_On_Event_Msg(canuint8_t index);
static void Set_Event_Flag_For_Cyclic_And_On_Event_Msg(canuint8_t index);
static void SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_Msg(canuint8_t index);
static void SCH_Queue_For_Tx_Cyclic_And_On_Event_Msg(canuint8_t index);
static void SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_Msg(canuint8_t 
                                                                   index);
static void SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_Msg(canuint8_t 
                                                                       index);
#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
static void Cold_Init_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                               channel_number);
static canuint8_t 
SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event_With_Min_Update_Time(canuint8_t 
                                                                   msg_handle);
static void
Start_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time(canuint8_t channel_number);
static void
Cancel_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time(canuint8_t channel_number);
static void Periodic_Task_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                       canuint8_t channel_number);
static void Check_And_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void Set_Event_Flag_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void 
SCH_Set_Min_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void 
SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                                        index);
static void SCH_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void 
SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
static void 
SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index);
#endif

#ifdef BAF_MSG_SUPPORTED
static void Cold_Init_For_BAF_Msg(canuint8_t channel_number);
static canuint8_t SCH_Get_Index_From_Msg_Handle_BAF(canuint8_t msg_handle);
static void Start_Cyclic_And_Timeout_Timers_BAF(canuint8_t channel_number);
static void Cancel_Cyclic_And_Timeout_Timers_BAF(canuint8_t channel_number);
static void Periodic_Task_For_BAF_Msg(canuint8_t channel_number);
static void Check_And_Queue_For_Tx_BAF_Msg(canuint8_t index);
static void SCH_Set_Timer_Expiry_Flag_BAF_Msg(canuint8_t index);
static void SCH_Queue_For_Tx_BAF_Msg(canuint8_t index);
static void SCH_Timeout_Expiry_Notifier_Function_BAF_Msg(canuint8_t index);
static void  SCH_Set_Startup_Delay_Expiry_Flag_BAF_Msg(canuint8_t index);
#endif

#ifdef FAST_MSG_SUPPORTED
static void Cold_Init_For_FAST_Msg(canuint8_t channel_number);
static canuint8_t SCH_Get_Index_From_Msg_Handle_FAST(canuint8_t msg_handle);
static void Start_Cyclic_And_Timeout_Timers_FAST(canuint8_t channel_number);
static void Cancel_Cyclic_And_Timeout_Timers_FAST(canuint8_t channel_number);
static void Periodic_Task_For_FAST_Msg(canuint8_t channel_number);
static void Check_And_Queue_For_Tx_FAST_Msg(canuint8_t index);
static void SCH_Set_Timer_Expiry_Flag_FAST_Msg_Slow_Timer(canuint8_t index);
static void SCH_Set_Timer_Expiry_Flag_FAST_Msg_Fast_Timer(canuint8_t index);
static void SCH_Queue_For_Tx_FAST_Msg(canuint8_t index);
static void SCH_Timeout_Expiry_Notifier_Function_FAST_Msg(canuint8_t index);
static void SCH_Set_Startup_Delay_Expiry_Flag_FAST_Msg(canuint8_t index);
#endif

/******************************************************************************
*Prototype: SCH_Tx_Cold_Initialization                                        *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This function would be called by application during power ON  *
* reset (cold initialization) as a part of 'DCH_Cold_Initialization' function.*
* This function initializes all the control variables and flags to their      *
* respective default values related to all the supported transmission modes.  *
******************************************************************************/
void SCH_Tx_Cold_Initialization(canuint8_t channel_number)
{
  Periodic_Tx_Enabled[channel_number] = cbTRUE;
  Tx_State_Activated[channel_number] = cbTRUE;
  
  #ifdef ON_EVENT_MSG_SUPPORTED
  Cold_Init_For_On_Event_Msg(channel_number);
  #endif
  #ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  Cold_Init_For_On_Event_With_Min_Update_Time_Msg(channel_number);
  #endif
  #ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
  Cold_Init_For_N_Times_On_Event_Msg(channel_number);
  #endif
  #ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  Cold_Init_For_N_Times_On_Event_With_Min_Update_Time_Msg(channel_number);
  #endif
  #ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
  Cold_Init_For_Cyclic_On_Init_Msg(channel_number);
  #endif
  #ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
  Cold_Init_For_Cyclic_On_Request_Msg(channel_number);
  #endif
  #ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  Cold_Init_For_Cyclic_And_On_Event_Msg(channel_number);
  #endif
  #ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  Cold_Init_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(channel_number);
  #endif
  #ifdef BAF_MSG_SUPPORTED
  Cold_Init_For_BAF_Msg(channel_number);
  #endif
  #ifdef FAST_MSG_SUPPORTED
  Cold_Init_For_FAST_Msg(channel_number);
  #endif
}

/******************************************************************************
*Prototype: SCH_Tx_Periodic_Task                                              *
*Arguments passed: none                                                       *
*Return value: none                                                           *
*Functionality: This is the periodic task for the Scheduler. In this periodic *
*task, the Scheduler notifies respective upper layer to queue messages for    *
*transmission, and also about time-out of messages.                           *
******************************************************************************/
void SCH_Tx_Periodic_Task()
{
  #ifdef CAN_CH0_SELECTED
  if(cbTRUE == Tx_State_Activated[0])
  {
    SCH_Tx_Periodic_Task_For_Channel(0);
  }
  #endif
  #ifdef CAN_CH1_SELECTED
  if(cbTRUE == Tx_State_Activated[1])
  {
    SCH_Tx_Periodic_Task_For_Channel(1);
  }
  #endif
  #ifdef CAN_CH2_SELECTED
  if(cbTRUE == Tx_State_Activated[2])
  {
    SCH_Tx_Periodic_Task_For_Channel(2);
  }
  #endif
}

/******************************************************************************
*Prototype: SCH_Tx_Periodic_Task_For_Channel                                  *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This is the channel wise periodic task for the Scheduler.     *
*In this periodic task, the Scheduler notifies respective upper layer to queue*
*messages for transmission, and also about time-out of messages.              *
******************************************************************************/
void SCH_Tx_Periodic_Task_For_Channel(canuint8_t channel_number)
{
 #ifdef ON_EVENT_MSG_SUPPORTED
 Periodic_Task_For_On_Event_Msg(channel_number);
 #endif
 #ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
 Periodic_Task_For_On_Event_With_Min_Update_Time_Msg(channel_number);
 #endif
 #ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
 Periodic_Task_For_N_Times_On_Event_Msg(channel_number);
 #endif
 #ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
 Periodic_Task_For_N_Times_On_Event_With_Min_Update_Time_Msg(channel_number);
 #endif
 
 if(cbTRUE == Periodic_Tx_Enabled[channel_number])
 {
 #ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
 Periodic_Task_For_Cyclic_On_Init_Msg(channel_number);
 #endif
 #ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
 Periodic_Task_For_Cyclic_On_Request_Msg(channel_number);
 #endif
 #ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
 Periodic_Task_For_Cyclic_And_On_Event_Msg(channel_number);
 #endif
 #ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
 Periodic_Task_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(channel_number);
 #endif
 #ifdef BAF_MSG_SUPPORTED
 Periodic_Task_For_BAF_Msg(channel_number);
 #endif
 #ifdef FAST_MSG_SUPPORTED
 Periodic_Task_For_FAST_Msg(channel_number);
 #endif
 }
}

/******************************************************************************
*Prototype: SCH_Enable_Periodic_Tx                                            *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This API sets the periodic transmission enabled flag of the   *
*respective channel to True                                                   *
******************************************************************************/
void SCH_Enable_Periodic_Tx_Messages(canuint8_t channel_number)
{
  Periodic_Tx_Enabled[channel_number] = cbTRUE;
  Start_Cyclic_MinDelay_And_Timeout_Timers(channel_number);
}

/******************************************************************************
*Prototype: SCH_Disable_Periodic_Tx                                           *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This API sets the periodic transmission enabled flag of the   *
*respective channel to False                                                  *
******************************************************************************/
void SCH_Disable_Periodic_Tx_Messages(canuint8_t channel_number)
{
  Periodic_Tx_Enabled[channel_number] = cbFALSE;
  Cancel_Cyclic_MinDelay_And_Timeout_Timers(channel_number);
}

/******************************************************************************
*Prototype: SCH_Set_Tx_Active                                                 *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This API sets the transmission state activated flag of the    *
*respective channel to True                                                   *
******************************************************************************/
void SCH_Set_Tx_Active(canuint8_t channel_number)
{
  if( Tx_State_Activated[channel_number] != cbTRUE)
  {
    Tx_State_Activated[channel_number] = cbTRUE;
    Start_All_Tx_Timers(channel_number);
  }
}

/******************************************************************************
*Prototype: SCH_Set_Tx_Inactive                                               *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This API sets the transmission state activated flag of the    *
*respective channel to False                                                  *
******************************************************************************/
void SCH_Set_Tx_Inactive(canuint8_t channel_number)
{
  if(Tx_State_Activated[channel_number] == cbTRUE)
  {
    Tx_State_Activated[channel_number] = cbFALSE;
    Cancel_All_Tx_Timers(channel_number);
  }
}

void SCH_Set_Tx_Inactive_By_Appl(canuint8_t channel_number)
{
  Tx_State_Activated[channel_number] = cbFALSE;
 // Cancel_All_Tx_Timers(channel_number);
}

void SCH_Set_Tx_Active_By_Appl(canuint8_t channel_number)
{
  Tx_State_Activated[channel_number] = cbTRUE;
 // Cancel_All_Tx_Timers(channel_number);
}

/******************************************************************************
*Prototype: Start_All_Tx_Timers                                               *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API starts the timers (other than startup delay timer)for *
*all the supported messages on the given channel                              *
******************************************************************************/
 void Start_All_Tx_Timers(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;

#ifdef  ON_EVENT_MSG_SUPPORTED
  start_index = Tx_Ch_Index[channel_number][ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][ON_EVENT].end_index;

  for(index = start_index; index < end_index; index ++)
  {
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
    if(cbTRUE == ON_EVENT_MSG_Runtime_Info[index].startup_delay_timer_expired)
    {
    #endif
    #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
    if(DUMMY_TIMER !=ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
    {
      CAN_TIMER_Start(ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
    }
    #endif
  }
#endif
#ifdef  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  start_index = 
         Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = 
           Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for(index = start_index; index < end_index; index ++)
  {
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(cbTRUE == ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
       startup_delay_timer_expired)
    {
    #endif
    CAN_TIMER_Start(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                              min_delay_timer);
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER !=ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                 timeout_timer)
    {
      CAN_TIMER_Start(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                timeout_timer);
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    }
    #endif
  }
#endif
#ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
  start_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].end_index;

  for(index = start_index; index < end_index; index++)
  {
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
    if(cbTRUE == N_TIMES_ON_EVENT_MSG_Runtime_Info[index].
       startup_delay_timer_expired)
    {
    #endif
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER != N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
    {
      CAN_TIMER_Start(N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
    }
    #endif
  }
#endif
#ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  start_index = 
  Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = 
  Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for(index = start_index; index < end_index; index++)
  {
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(cbTRUE == N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
       startup_delay_timer_expired)
    {
    #endif
    CAN_TIMER_Start(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                                                      [index].min_delay_timer);
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER != N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                                                         [index].timeout_timer)
    {
      CAN_TIMER_Start(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                                                         [index].timeout_timer);
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    }
    #endif
  }
#endif
  
  Start_Cyclic_MinDelay_And_Timeout_Timers(channel_number);
}

/******************************************************************************
*Prototype: Cancel_All_Tx_Timers                                               *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API starts the timers (other than startup delay timer)for *
*all the supported messages on the given channel                              *
******************************************************************************/
 void Cancel_All_Tx_Timers(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;

#ifdef  ON_EVENT_MSG_SUPPORTED
  start_index = Tx_Ch_Index[channel_number][ON_EVENT].start_index;
  end_index =  Tx_Ch_Index[channel_number][ON_EVENT].end_index;

  #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
  for(index = start_index; index < end_index; index ++)
  {
    if(DUMMY_TIMER !=ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
    {
      CAN_TIMER_Cancel(ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
    }
  }
  #endif
#endif
#ifdef  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  start_index = 
         Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = 
           Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for(index = start_index; index < end_index; index ++)
  {
    CAN_TIMER_Cancel(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                              min_delay_timer);
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER !=ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                 timeout_timer)
    {
      CAN_TIMER_Cancel(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                timeout_timer);
    }
    #endif
  }
#endif
#ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
  start_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].end_index;

  for(index = start_index; index < end_index; index++)
  {
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER != N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
    {
      CAN_TIMER_Cancel(N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
    }
    #endif
  }
#endif
#ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  start_index = Tx_Ch_Index[channel_number]
                           [N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = 
  Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for(index = start_index; index < end_index; index++)
  {
    CAN_TIMER_Cancel(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                                                      [index].min_delay_timer);
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER != N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                                                         [index].timeout_timer)
    {
      CAN_TIMER_Cancel(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                                                         [index].timeout_timer);
    }
    #endif
  }
#endif

  Cancel_Cyclic_MinDelay_And_Timeout_Timers(channel_number);
}

/******************************************************************************
*Prototype: Start_Cyclic_MinDelay_And_Timeout_Timers                          *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API starts the timers (other than startup delay timer)for *
*the perodic messages on the given channel                                    *
******************************************************************************/
 void Start_Cyclic_MinDelay_And_Timeout_Timers(canuint8_t channel_number)
{
#ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
  Start_Cyclic_And_Timeout_Timers_Cyclic_On_Init(channel_number);
#endif
#ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
  Start_Cyclic_And_Timeout_Timers_Cyclic_On_Request(channel_number);
#endif
#ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  Start_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event(channel_number);
#endif
#ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  Start_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time(channel_number);
#endif
#ifdef  BAF_MSG_SUPPORTED
  Start_Cyclic_And_Timeout_Timers_BAF(channel_number);
#endif
#ifdef  FAST_MSG_SUPPORTED
  Start_Cyclic_And_Timeout_Timers_FAST(channel_number);
#endif
}

/******************************************************************************
*Prototype: Cancel_Cyclic_MinDelay_And_Timeout_Timers                         *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API cancels the timers (other than startup delay timer)for*
*the perodic messages on the given channel                                    *
******************************************************************************/
 void Cancel_Cyclic_MinDelay_And_Timeout_Timers(canuint8_t channel_number)
{
#ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
  Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Init(channel_number);
#endif
#ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
  Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Request(channel_number);
#endif
#ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  Cancel_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event(channel_number);
#endif
#ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  Cancel_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time(channel_number);
#endif
#ifdef  BAF_MSG_SUPPORTED
  Cancel_Cyclic_And_Timeout_Timers_BAF(channel_number);
#endif
#ifdef  FAST_MSG_SUPPORTED
  Cancel_Cyclic_And_Timeout_Timers_FAST(channel_number);
#endif
}

/******************************************************************************
*Prototype: SCH_Set_Event_Flag                                                *
*Arguments passed: msg handle, msg type                                       *
*Return value: none                                                           *
*Functionality: This API updates the event status and starts the corresponding*
*timers for the respective message. This API handles the following msg types: *
*ON_EVENT_WITH_MIN_UPDATE_TIME                                                *
*N_TIMES_ON_EVENT                                                             *
*N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME                                        *
*CYCLIC_AND_ON_EVENT                                                          *
*CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME                                     *
******************************************************************************/
void SCH_Set_Event_Flag(canuint8_t msg_handle, Message_Transmission_Mode_T 
                                                               msg_type)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(msg_type, msg_handle);
  
  switch(msg_type)
  {
  #ifdef ON_EVENT_MSG_SUPPORTED
    case (ON_EVENT):
         Set_Event_Flag_For_On_Event_Msg(index);
         break; 
  #endif
  #ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    case (ON_EVENT_WITH_MIN_UPDATE_TIME):
         Set_Event_Flag_For_On_Event_With_Min_Update_Time_Msg(index);
         break; 
  #endif
  #ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
    case (N_TIMES_ON_EVENT):
         Set_Event_Flag_For_N_Times_On_Event_Msg(index);
         break; 
  #endif
  #ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    case (N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME):
         Set_Event_Flag_For_N_Times_On_Event_With_Min_Update_Time_Msg(index);
         break; 
  #endif
  #ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
    case (CYCLIC_AND_ON_EVENT):
         Set_Event_Flag_For_Cyclic_And_On_Event_Msg(index);
         break; 
  #endif
  #ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    case (CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME):
         Set_Event_Flag_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
         break; 
  #endif
  default :
         Appl_Invalid_Msg_Type_Request();
         break;
  }
}

/******************************************************************************
*Prototype: SCH_Tx_Message_Confirmation                                       *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality:This function is called by VBM after successful tx of a        *
*functional message. It notifies the same to the upper layer.                 *
******************************************************************************/
void SCH_Tx_Message_Confirmation(canuint8_t msg_handle)
{
  AIF_Set_Msg_Transmitted(msg_handle);
}

/******************************************************************************
*Prototype: SCH_Cancel_Timeout_Timer_For_Event_Msg                            *
*Arguments passed: msg handle, msg type                                       *
*Return value: none                                                           *
*Functionality:                                                               *
******************************************************************************/
void SCH_Cancel_Timeout_Timer_For_Event_Msg(canuint8_t msg_handle,
                                          Message_Transmission_Mode_T msg_type)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(msg_type, msg_handle);
  
  switch(msg_type)
  {
  #ifdef ON_EVENT_MSG_SUPPORTED
    case (ON_EVENT):
		#ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
              CAN_TIMER_Cancel(ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
              #endif
         
         break; 
  #endif
  #ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    case (ON_EVENT_WITH_MIN_UPDATE_TIME):
         CAN_TIMER_Cancel(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                          timeout_timer);
         break; 
  #endif
  #ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
    case (N_TIMES_ON_EVENT):
      #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
         CAN_TIMER_Cancel(N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
      #endif
         break; 
  #endif
  #ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    case (N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME):
	  #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
         CAN_TIMER_Cancel(
         N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].timeout_timer);
	  #endif
         break; 
  #endif
  #ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
    case (CYCLIC_AND_ON_EVENT):
		#ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
         CAN_TIMER_Cancel(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
		#endif
         break; 
  #endif
  #ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    case (CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME):
         CAN_TIMER_Cancel(
         CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].timeout_timer);
         break; 
  #endif
  default :
         Appl_Invalid_Msg_Type_Request();
         break;
  }
}

#ifdef ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_On_Event_Msg                                         *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to ON_EVENT messages                        *
*******************************************************************************/
 void Cold_Init_For_On_Event_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 

  ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_runtime_table = &ON_EVENT_MSG_Runtime_Info[index];

     ptr_to_runtime_table->event_occurred = cbFALSE;
     #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
     if(DUMMY_TIMER !=ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
     {
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     }
     #endif
     #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_On_Event                            *
*Arguments passed: msg_handle                                                 *
*Return value: index                                                          *
*Functionality:This function gets the index of the ON_EVENT message           *
*corresponding to msg_handle passed                                           *
******************************************************************************/
 canuint8_t SCH_Get_Index_From_Msg_Handle_On_Event(canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index = 0; index < Size_Of_On_Event_Table; index++)
  {
    if(ON_EVENT_MSG_CONFIG_Table[index].msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Set_Event_Flag_For_On_Event_Msg                                   *
*Arguments passed: index, event_status                                        *
*Return value: none                                                           *
*Functionality:This function updates the event flag with the status passed by *
*the user layer                                                               *
*******************************************************************************/
 void Set_Event_Flag_For_On_Event_Msg(canuint8_t index)
{
  ON_EVENT_MSG_Runtime_Info[index].event_occurred = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_On_Event_Msg                                *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Immediate_Process_On_Event_Msg(CAN_Timer_Names_T timer_name)
{
  SCH_Set_Flag_On_Event_Msg(timer_name);
}

/******************************************************************************
*Prototype: SCH_Set_Flag_On_Event_Msg                                         *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Set_Flag_On_Event_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_On_Event_Table; index ++)
  {
    ptr_to_config_table= &ON_EVENT_MSG_CONFIG_Table[index];
    #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Expiry_Notifier_Function_On_Event_Msg(index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_On_Event_Msg(index);
        break;
      }
    #endif
  }
}

#ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Timeout_Expiry_Notifier_Function_On_Event_Msg                  *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality: This function is called in Timer module once the timeout      *
*timer expires. It calls the upper layer API to notify the same               *
******************************************************************************/
static void 
SCH_Timeout_Expiry_Notifier_Function_On_Event_Msg(canuint8_t index)
{
  ON_EVENT_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(ON_EVENT_MSG_CONFIG_Table[index].msg_handle);
}

#endif

#ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Set_Startup_Delay_Expiry_Flag_On_Event_Msg                     *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_On_Event_Msg(canuint8_t index)
{
  ON_EVENT_MSG_Runtime_Info[index].startup_delay_timer_expired = cbTRUE;
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_On_Event_Msg                                    *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This function lets the application know that message is ready *
*to be queued for transmission if event has occurred and min update timer has *
*expired. This function also notifies transmit time-out.                      *
******************************************************************************/
void Periodic_Task_For_On_Event_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_runtime_table = &ON_EVENT_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_On_Event_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_On_Event_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_On_Event_Msg                               *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality: This function lets the application know that message is ready *
*to be queued for transmission if event has occurred and min update timer has *
*expired.                                                                     *
******************************************************************************/
void Check_And_Queue_For_Tx_On_Event_Msg(canuint8_t index)
{  
  const ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;
    
  ptr_to_config_table= &ON_EVENT_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &ON_EVENT_MSG_Runtime_Info[index];

   #ifdef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED
   if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
      (cbTRUE == ptr_to_runtime_table->event_occurred))
   #else
   if(cbTRUE == ptr_to_runtime_table->event_occurred)
   #endif
   {
     AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
     ptr_to_runtime_table->event_occurred = cbFALSE;
     #ifdef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
     if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
     }
     #endif
   }
}
#endif

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_On_Event_With_Min_Update_Time_Msg                    *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to ON_EVENT_WITH_MIN_UPDATE_TIME messages   *
*******************************************************************************/
static void Cold_Init_For_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                      channel_number)
{
  canuint8_t index, start_index, end_index; 
  const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = 
         Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = 
         Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_runtime_table = 
                        &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
     ptr_to_config_table = 
                        &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];

     ptr_to_runtime_table->event_occurred = cbFALSE;
     ptr_to_runtime_table->min_delay_timer_expired = cbTRUE;
     #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     #endif
     #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_On_Event_With_Min_Update_Time       *
*Arguments passed: msg_handle                                                 *
*Return value: index                                                          *
*Functionality:This function gets the index of the ON_EVENT_WITH_MIN_UPDATE_TIME
*message corresponding to msg_handle passed                                   *
******************************************************************************/
static canuint8_t SCH_Get_Index_From_Msg_Handle_On_Event_With_Min_Update_Time(
                                                            canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_On_Event_With_Min_Update_Table; index++)
  {
    if(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].msg_handle == 
       msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Set_Event_Flag_For_On_Event_With_Min_Update_Time_Msg              *
*Arguments passed: index, event_status                                        *
*Return value: none                                                           *
*Functionality:This function updates the event flag with the status passed by *
*the user layer                                                               *
*******************************************************************************/
static void Set_Event_Flag_For_On_Event_With_Min_Update_Time_Msg(canuint8_t
                                                                  index)
{
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].event_occurred = 
                                                                cbTRUE;
/*  #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  if(DUMMY_TIMER != ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
     timeout_timer)
  {
    CAN_TIMER_Start(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
    timeout_timer);
  }
  #endif*/
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_On_Event_With_Min_Update_Time_Msg           *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Immediate_Process_On_Event_With_Min_Update_Time_Msg(CAN_Timer_Names_T 
                                                                    timer_name)
{
  canuint8_t index;
  const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_On_Event_With_Min_Update_Table; index ++)
  {
    ptr_to_config_table= &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    if(ptr_to_config_table->min_delay_timer == timer_name)
    {
      SCH_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Expiry_Notifier_Function_On_Event_With_Min_Update_Time_Msg(
        index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(
        index);
        break;
      }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_On_Event_With_Min_Update_Time_Msg                    *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Set_Flag_On_Event_With_Min_Update_Time_Msg(CAN_Timer_Names_T 
                                                           timer_name)
{
  canuint8_t index;
  const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_On_Event_With_Min_Update_Table; index ++)
  {
    ptr_to_config_table= &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    if(ptr_to_config_table->min_delay_timer == timer_name)
    {
      SCH_Set_Min_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Expiry_Notifier_Function_On_Event_With_Min_Update_Time_Msg(
        index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(
        index);
        break;
      }
    #endif
    }
  }
}
/******************************************************************************
*Prototype:SCH_Set_Min_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg    *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void SCH_Set_Min_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(
                                                              canuint8_t index)
{
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].min_delay_timer_expired
                                                                      = cbTRUE;
}

/******************************************************************************
*Prototype:SCH_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg                 *
*Arguments passed: inedx                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag ,checks and queues critical msgs*
*for transmission                                                             *
******************************************************************************/
static void SCH_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(canuint8_t index)
{

  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  min_delay_timer_expired = cbTRUE;
  
  Check_And_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(index);
}

#ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Timeout_Expiry_Notifier_Function_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality: This function is called in Timer module once the timeout      *
*timer expires. It calls the upper layer API to notify the same               *
******************************************************************************/
static void 
SCH_Timeout_Expiry_Notifier_Function_On_Event_With_Min_Update_Time_Msg(
                                                         canuint8_t index)
{
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                     msg_handle);
}

#endif

#ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Set_Startup_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg(
                                                                  canuint8_t index)
{
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  startup_delay_timer_expired = cbTRUE;
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_On_Event_With_Min_Update_Time_Msg               *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This function lets the application know that message is ready *
*to be queued for transmission if event has occurred and min update timer has *
*expired. This function also notifies transmit time-out.                      *
******************************************************************************/
static void Periodic_Task_For_On_Event_With_Min_Update_Time_Msg(
                                         canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = 
        Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = 
        Tx_Ch_Index[channel_number][ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table= &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = 
    &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg          *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality: This function lets the application know that message is ready *
*to be queued for transmission if event has occurred and min update timer has *
*expired.                                                                     *
******************************************************************************/
static void Check_And_Queue_For_Tx_On_Event_With_Min_Update_Time_Msg(
                                                       canuint8_t index)
{  
  const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* ptr_to_runtime_table;
    
  ptr_to_config_table= &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];

   #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
   if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
      (cbTRUE == ptr_to_runtime_table->min_delay_timer_expired)&&
      (cbTRUE == ptr_to_runtime_table->event_occurred))
   #else
   if((cbTRUE == ptr_to_runtime_table->min_delay_timer_expired)&&
      (cbTRUE == ptr_to_runtime_table->event_occurred))
   #endif
   {
     AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
     ptr_to_runtime_table->event_occurred = cbFALSE;
     ptr_to_runtime_table->min_delay_timer_expired = cbFALSE;
     CAN_TIMER_Start(ptr_to_config_table->min_delay_timer);
     #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
     }
     #endif
   }
}
#endif

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_N_Times_On_Event_Msg                                 *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to N_TIMES_ON_EVENT messages                *
*******************************************************************************/
static void Cold_Init_For_N_Times_On_Event_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  const N_TIMES_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  N_TIMES_ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_config_table = &N_TIMES_ON_EVENT_MSG_CONFIG_Table[index];
     ptr_to_runtime_table = &N_TIMES_ON_EVENT_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->event_occurred = cbFALSE;
     ptr_to_runtime_table->transmit_count = 0;
     #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     #endif
     #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_N_Times_On_Event                    *
*Arguments passed: msg_handle                                                 *
*Return value: index                                                          *
*Functionality:This function gets the index of the N_Times_On_Event           *
*message corresponding to msg_handle passed                                   *
******************************************************************************/
static canuint8_t SCH_Get_Index_From_Msg_Handle_N_Times_On_Event(
                                                            canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_N_Times_On_Event_Table; index++)
  {
    if(N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Update_On_Event_Flag_For_N_Times_On_Event_Msg                     *
*Arguments passed: index, event_status                                        *
*Return value: none                                                           *
*Functionality:This function updates the event flag with the status passed by *
*the application and loads the transmit count                                 *
******************************************************************************/
static void Set_Event_Flag_For_N_Times_On_Event_Msg(canuint8_t index)
{
  if(cbFALSE == N_TIMES_ON_EVENT_MSG_Runtime_Info[index].event_occurred )
  {N_TIMES_ON_EVENT_MSG_Runtime_Info[index].event_occurred = cbTRUE;
   N_TIMES_ON_EVENT_MSG_Runtime_Info[index].transmit_count = 
   N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].transmit_count;
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_N_Times_On_Event_Msg                        *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Immediate_Process_N_Times_On_Event_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const N_TIMES_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_N_Times_On_Event_Table; index ++)
  {
    ptr_to_config_table= &N_TIMES_ON_EVENT_MSG_CONFIG_Table[index];
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
      SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_Msg(index);
      break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_Msg(index);
      break;
    }
    #endif
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_N_Times_On_Event_Msg                                 *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Set_Flag_N_Times_On_Event_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const N_TIMES_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_N_Times_On_Event_Table; index ++)
  {
    ptr_to_config_table= &N_TIMES_ON_EVENT_MSG_CONFIG_Table[index];
    #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
      SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_Msg(index);
      break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_Msg(index);
      break;
    }
    #endif
  }
}

#ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_Msg          *
*Arguments passed: none                                                       *
*Return value: none                                                           *
*Functionality: This function is called in Timer module once the timeout      *
*timer expires. It calls the upper layer API to notify the same.              *
******************************************************************************/
static void SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_Msg(canuint8_t
                                                                       index)
{
  N_TIMES_ON_EVENT_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(N_TIMES_ON_EVENT_MSG_CONFIG_Table[index].msg_handle);
}
#endif

#ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Set_Startup_Delay_Expiry_Flag_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_Msg(canuint8_t 
                                                                     index)
{
  N_TIMES_ON_EVENT_MSG_Runtime_Info[index].startup_delay_timer_expired = cbTRUE;
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_N_Times_On_Event_Msg                             *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function handles transmission and time out functionality of*
*N_Times_On_Event messages                                                     *
*******************************************************************************/
static void Periodic_Task_For_N_Times_On_Event_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  const N_TIMES_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  N_TIMES_ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][N_TIMES_ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = &N_TIMES_ON_EVENT_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &N_TIMES_ON_EVENT_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_N_Times_On_Event_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_N_Times_On_Event_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_N_Times_On_Event_Msg                       *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function checks if messages need to be queued for         *
*transmission                                                                 *
*******************************************************************************/
static void Check_And_Queue_For_Tx_N_Times_On_Event_Msg(canuint8_t index)
{
  const N_TIMES_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  N_TIMES_ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  ptr_to_config_table = &N_TIMES_ON_EVENT_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &N_TIMES_ON_EVENT_MSG_Runtime_Info[index];
  
  #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
  if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
     (0 < ptr_to_runtime_table->transmit_count)&&
     (cbTRUE == ptr_to_runtime_table->event_occurred))
  #else
  if((0 < ptr_to_runtime_table->transmit_count)&&
  (cbTRUE == ptr_to_runtime_table->event_occurred))
  #endif
  {
     AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
     ptr_to_runtime_table->transmit_count--;
     #ifdef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     if((DUMMY_TIMER != ptr_to_config_table->timeout_timer)
       &&(0 < ptr_to_runtime_table->transmit_count))
       {
          CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
       }
     #endif
  }
  else if(0 == ptr_to_runtime_table->transmit_count)
  {
    ptr_to_runtime_table->event_occurred = cbFALSE;
  }
}
#endif

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_N_Times_On_Event_With_Min_Update_Time_Msg            *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to ON_EVENT_WITH_MIN_UPDATE_TIME messages   *
*******************************************************************************/
static void Cold_Init_For_N_Times_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                              channel_number)
{
  canuint8_t index, start_index, end_index;
  const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* 
  ptr_to_runtime_table;

  
  start_index = Tx_Ch_Index[channel_number]
                [N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = Tx_Ch_Index[channel_number]
                [N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_config_table = 
     &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
     ptr_to_runtime_table = 
     &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->event_occurred = cbFALSE;
     ptr_to_runtime_table->transmit_count = 0;
     ptr_to_runtime_table->min_delay_timer_expired = cbTRUE;
     #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     #endif
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
    #endif
  }
}

/******************************************************************************
*Prototype:SCH_Get_Index_From_Msg_Handle_N_Times_On_Event_With_Min_Update_Time*
*Arguments passed: msg_handle                                                 *
*Return value: index                                                          *
*Functionality:This function gets the index of the N_Times_On_Event_With_Min_ *
*Update_Time message corresponding to msg_handle passed                       *
******************************************************************************/
static canuint8_t 
SCH_Get_Index_From_Msg_Handle_N_Times_On_Event_With_Min_Update_Time(
                                                            canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0;index<Size_Of_N_Times_On_Event_With_Min_Update_Table;index++)
  {
    if(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
       msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Set_Event_Flag_For_N_Times_On_Event_With_Min_Update_Time_Msg      *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function sets the event occurred  flag to True            *
******************************************************************************/
static void Set_Event_Flag_For_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                      canuint8_t index)
{
  if((cbFALSE == N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
     event_occurred) || 
     (0 != N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
    transmit_count ))
  {
    N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
    event_occurred = cbTRUE;
  
    N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
    transmit_count = N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
    [index].transmit_count;
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_N_Times_On_Event_With_Min_Update_Time_Msg   *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Immediate_Process_N_Times_On_Event_With_Min_Update_Time_Msg(
                                        CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0;index < Size_Of_N_Times_On_Event_With_Min_Update_Table;index ++)
  {
    ptr_to_config_table = 
    &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->min_delay_timer == timer_name)
    {
      SCH_Set_Min_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                       index);
      SCH_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
    SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_With_Min_Update_Time_Msg(index);
    break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
    SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
    index);
    break;
    }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_N_Times_On_Event_With_Min_Update_Time_Msg            *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires.                                                               *
******************************************************************************/
void SCH_Set_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(CAN_Timer_Names_T
                                                                  timer_name)
{
  canuint8_t index;
  const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0;index < Size_Of_N_Times_On_Event_With_Min_Update_Table;index ++)
  {
    ptr_to_config_table = 
    &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->min_delay_timer == timer_name)
    {
      SCH_Set_Min_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                       index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
    SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_With_Min_Update_Time_Msg(index);
    break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
    SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
    index);
    break;
    }
    #endif
    }
  }
}

/******************************************************************************
*Prototype:SCH_Set_Min_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time*
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void 
SCH_Set_Min_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                          canuint8_t index)
{
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  min_delay_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype:SCH_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg         *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function                                                  *
******************************************************************************/
static void SCH_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                         canuint8_t index)
{
  Check_And_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(index);
}

#ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void 
SCH_Timeout_Expiry_Notifier_Function_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                 canuint8_t index)
{
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].msg_handle);
}
#endif

#ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype:SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets the timer expiry flag which will be checked and       *
*processed in the Periodic task                                               *
******************************************************************************/
static void 
SCH_Set_Startup_Delay_Expiry_Flag_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                              canuint8_t index)
{
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  startup_delay_timer_expired = cbTRUE;
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_N_Times_On_Event_With_Min_Update_Time_Msg       *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This function handles transmission and time out functionality  *
* of N_Times_On_Event_With_Min_Update_Time messages                           *
******************************************************************************/
static void Periodic_Task_For_N_Times_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                                 channel_number)
{
  canuint8_t index, start_index, end_index;
  const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* 
  ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number]
                [N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = Tx_Ch_Index[channel_number]
              [N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = 
    &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = 
    &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg  *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function checks if messages need to be queued for         *
*transmission                                                                 *
******************************************************************************/
static void Check_And_Queue_For_Tx_N_Times_On_Event_With_Min_Update_Time_Msg(
                                                                canuint8_t index)
{
  const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* ptr_to_config_table;
  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* 
  ptr_to_runtime_table;

  ptr_to_config_table = 
                &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = 
                &N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
  
  #ifdef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
     (cbTRUE == ptr_to_runtime_table->min_delay_timer_expired)&&
     (0 < ptr_to_runtime_table->transmit_count)&&
     (cbTRUE == ptr_to_runtime_table->event_occurred))
  #else
  if((cbTRUE == ptr_to_runtime_table->min_delay_timer_expired)&&
     (0 < ptr_to_runtime_table->transmit_count)&&
     (cbTRUE == ptr_to_runtime_table->event_occurred))
  #endif
    {
       AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
       ptr_to_runtime_table->transmit_count--;
       ptr_to_runtime_table->min_delay_timer_expired = cbFALSE;
       CAN_TIMER_Start(ptr_to_config_table->min_delay_timer);
       #ifdef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
       if((DUMMY_TIMER != ptr_to_config_table->timeout_timer)
           &&(0 < ptr_to_runtime_table->transmit_count))
         {
            CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
         }
       #endif
    }
    else if(0 == ptr_to_runtime_table->transmit_count)
    {
      ptr_to_runtime_table->event_occurred = cbFALSE;
    }
}
#endif

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_Cyclic_On_Init_Msg                                   *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to CYCLIC messages                          *
******************************************************************************/
 void Cold_Init_For_Cyclic_On_Init_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_ON_INIT_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_INIT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_config_table = &CYCLIC_ON_INIT_MSG_CONFIG_Table[index];
     ptr_to_runtime_table = &CYCLIC_ON_INIT_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->cyclic_timer_expired = cbTRUE;
     #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
     else
     {
       CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
       #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
       ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
       #endif
     }
     #else
       CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
       #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
       ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
       #endif
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Stop_Tx_Cyclic_On_Init_Msg                                    *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Stop_Tx_Cyclic_On_Init_Msg(canuint8_t msg_handle)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(CYCLIC_ON_INIT, msg_handle);
  
  if(SCH_INVALID_REQUEST != index)
  {
    CYCLIC_ON_INIT_MSG_Runtime_Info[index].cyclic_timer_expired = cbFALSE;
    CAN_TIMER_Cancel(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].cyclic_timer);
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_Cyclic_On_Init                      *
*Arguments passed: msg handle                                                 *
*Return value: index of table                                                 *
*Functionality: This API gets the index of the Cyclic on init table           *
******************************************************************************/
 canuint8_t SCH_Get_Index_From_Msg_Handle_Cyclic_On_Init(canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_Cyclic_On_Init_Msg_Table; index++)
  {
    if(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Start_Cyclic_And_Timeout_Timers_Cyclic_On_Init                    *
*Arguments passed: channel_number                                             *
*Return value: none                                                           *
*Functionality: This API starts the cyclic and timeout timers of Cyclic on init*
*messages                                                                     *
******************************************************************************/
 void Start_Cyclic_And_Timeout_Timers_Cyclic_On_Init(
                                                        canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;

  CYCLIC_ON_INIT_MSG_Runtime_Info_T* ptr_to_runtime_table;
  
  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_runtime_table = &CYCLIC_ON_INIT_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->cyclic_timer_expired = cbTRUE;
     #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
     if(cbTRUE == 
        CYCLIC_ON_INIT_MSG_Runtime_Info[index].startup_delay_timer_expired)
     {
     #endif
     CAN_TIMER_Start(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].cyclic_timer);
/*     #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
     if(DUMMY_TIMER != CYCLIC_ON_INIT_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Start(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif*/
     #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
     }
     #endif
  }
}

/******************************************************************************
*Prototype: Start_Cyclic_And_Timeout_Timers_Cyclic_On_Init                    *
*Arguments passed: channel_number                                             *
*Return value: none                                                           *
*Functionality: This API cancels the cyclic and timeout timers of Cyclic on   *
*init messages                                                                *
******************************************************************************/
 void Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Init(canuint8_t 
                                                                channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     CAN_TIMER_Cancel(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].cyclic_timer);
     #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
     if(DUMMY_TIMER != CYCLIC_ON_INIT_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Cancel(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_Cyclic_On_Init_Msg                          *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Immediate_Process_Cyclic_On_Init_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_ON_INIT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_Cyclic_On_Init_Msg_Table; index ++)
  {
    ptr_to_config_table = &CYCLIC_ON_INIT_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Queue_For_Tx_Cyclic_On_Init_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Notifier_Function_Cyclic_On_Init_Msg(index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_On_Init_Msg(index);
        break;
      }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Cyclic_On_Init_Msg                                   *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Set_Flag_Cyclic_On_Init_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_ON_INIT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_Cyclic_On_Init_Msg_Table; index ++)
  {
    ptr_to_config_table = &CYCLIC_ON_INIT_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_Cyclic_On_Init_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Notifier_Function_Cyclic_On_Init_Msg(index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_On_Init_Msg(index);
        break;
      }
    #endif
    }
  }
}
/******************************************************************************
*Prototype: SCH_Set_Timer_Expiry_Flag_Cyclic_On_Init_Msg                      *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
 void SCH_Set_Timer_Expiry_Flag_Cyclic_On_Init_Msg(canuint8_t index)
{
  CYCLIC_ON_INIT_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Queue_For_Tx_Cyclic_On_Init_Msg                               *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets cyclic timer expired- flag to cbTRUE and checks if the  *
*critical msg needs to be queued for transmission                             *
******************************************************************************/
 void SCH_Queue_For_Tx_Cyclic_On_Init_Msg(canuint8_t index)
{
  CYCLIC_ON_INIT_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
  Check_And_Queue_For_Tx_Cyclic_On_Init_Msg(index);
}

#ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Cyclic_On_Init_Msg                  *
*Arguments passed: none                                                       *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It notifies the upper layer about the same.                   *
******************************************************************************/
static void SCH_Timeout_Notifier_Function_Cyclic_On_Init_Msg(canuint8_t index)
{
  CYCLIC_ON_INIT_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].msg_handle);
}
#endif

#ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_On_Init_Msg              *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_On_Init_Msg(canuint8_t index)
{
  CYCLIC_ON_INIT_MSG_Runtime_Info[index].startup_delay_timer_expired = cbTRUE;
  CAN_TIMER_Start(CYCLIC_ON_INIT_MSG_CONFIG_Table[index].cyclic_timer);
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_Cyclic_On_Init_Msg                              *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This function                                                  *
******************************************************************************/
 void Periodic_Task_For_Cyclic_On_Init_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_ON_INIT_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_INIT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_INIT].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = &CYCLIC_ON_INIT_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &CYCLIC_ON_INIT_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_Cyclic_On_Init_Msg(index);
    }
    #else
    if(cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)
    {
    Check_And_Queue_For_Tx_Cyclic_On_Init_Msg(index);
    }
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_Cyclic_On_Init_Msg                         *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function checks if msg needs to be queued for tx          *
******************************************************************************/
 void Check_And_Queue_For_Tx_Cyclic_On_Init_Msg(canuint8_t index)
{
  const CYCLIC_ON_INIT_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_INIT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  ptr_to_config_table = &CYCLIC_ON_INIT_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &CYCLIC_ON_INIT_MSG_Runtime_Info[index];
  #ifdef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
  if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
     (cbTRUE == ptr_to_runtime_table->cyclic_timer_expired))
  #else
  if((cbTRUE == ptr_to_runtime_table->cyclic_timer_expired))
  #endif
   {
     AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
     ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
     #ifdef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
     if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
     }
     #endif
  }
}
#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_Cyclic_On_Request_Msg                                *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to CYCLIC_ON_REQUEST messages               *
******************************************************************************/
static void Cold_Init_For_Cyclic_On_Request_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_ON_REQUEST_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_REQUEST_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_config_table = &CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index];
     ptr_to_runtime_table = &CYCLIC_ON_REQUEST_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->tx_requested = cbFALSE;
     ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
     #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Set_or_Clr_Req_For_Cyclic_On_Request_Msg                      *
*Arguments passed: msg handle, request                                        *
*Return value: none                                                           *
*Functionality:This API sets the stop transmission requested flag to the value*
*passed as request by the user layer                                          *
******************************************************************************/
void SCH_Set_or_Clr_Req_For_Cyclic_On_Request_Msg(canuint8_t msg_handle,
                                                    canbool8_t request)
{
  canuint8_t index;
  const CYCLIC_ON_REQUEST_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_REQUEST_MSG_Runtime_Info_T* ptr_to_runtime_table;
  
  index = SCH_Get_Index_From_Msg_Handle(CYCLIC_ON_REQUEST, msg_handle);
  if(SCH_INVALID_REQUEST != index)
  {
    ptr_to_config_table = &CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &CYCLIC_ON_REQUEST_MSG_Runtime_Info[index];
    ptr_to_runtime_table->tx_requested = request;
    if(cbTRUE == request) // request to start cyclic transmission
    {
      CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
    }
    else // request to stop cyclic transmission
    {
      CAN_TIMER_Cancel(ptr_to_config_table->cyclic_timer);
      #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
      if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
      {
        CAN_TIMER_Cancel(ptr_to_config_table->timeout_timer);
      }
      #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_Cyclic_On_Request                   *
*Arguments passed: msg handle                                                 *
*Return value: index of table                                                 *
*Functionality: This API gets the index of the Cyclic on Request table        *
******************************************************************************/
static canuint8_t SCH_Get_Index_From_Msg_Handle_Cyclic_On_Request(
                                                            canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_Cyclic_On_Request_Msg_Table; index++)
  {
    if(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Start_Cyclic_And_Timeout_Timers_Cyclic_On_Request                 *
*Arguments passed: channel_number                                             *
*Return value: none                                                           *
*Functionality: This API starts the cyclic and timeout timers of Cyclic on    *
*Request messages                                                             *
******************************************************************************/
static void Start_Cyclic_And_Timeout_Timers_Cyclic_On_Request(
                                                        canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].end_index;

  for (index = start_index; index < end_index; index++)
  {
     CAN_TIMER_Start(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].cyclic_timer);
/*     #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
     if(DUMMY_TIMER != CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].timeout_timer)
     {
      CAN_TIMER_Start(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif*/
  }
}

/******************************************************************************
*Prototype: Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Request                *
*Arguments passed: channel_number                                             *
*Return value: none                                                           *
*Functionality: This API cancels the cyclic and timeout timers of Cyclic on   *
*Request messages                                                             *
******************************************************************************/
static void Cancel_Cyclic_And_Timeout_Timers_Cyclic_On_Request(canuint8_t 
                                                                channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].end_index;

  for (index = start_index; index < end_index; index++)
  {
     CAN_TIMER_Cancel(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].cyclic_timer);
     #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
     if(DUMMY_TIMER != CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].timeout_timer)
     {
      CAN_TIMER_Cancel(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_Cyclic_On_Request_Msg                       *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Immediate_Process_Cyclic_On_Request_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_ON_REQUEST_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_Cyclic_On_Request_Msg_Table; index ++)
  {
    ptr_to_config_table = &CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Queue_For_Tx_Cyclic_On_Request_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Notifier_Function_Cyclic_On_Request_Msg(index);
        break;
      }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Cyclic_On_Request_Msg                                *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Set_Flag_Cyclic_On_Request_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_ON_REQUEST_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_Cyclic_On_Request_Msg_Table; index ++)
  {
    ptr_to_config_table = &CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_Cyclic_On_Request_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Notifier_Function_Cyclic_On_Request_Msg(index);
        break;
      }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Timer_Expiry_Flag_Cyclic_On_Request_Msg                   *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Timer_Expiry_Flag_Cyclic_On_Request_Msg(canuint8_t index)
{
  CYCLIC_ON_REQUEST_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Queue_For_Tx_Cyclic_On_Request_Msg                            *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets cyclic timer expired- flag to cbTRUE and checks if the  *
*critical msg needs to be queued for transmission                             *
******************************************************************************/
static void SCH_Queue_For_Tx_Cyclic_On_Request_Msg(canuint8_t index)
{
  CYCLIC_ON_REQUEST_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
  Check_And_Queue_For_Tx_Cyclic_On_Request_Msg(index);
}

#ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Cyclic_On_Request_Msg               *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Timeout_Notifier_Function_Cyclic_On_Request_Msg(canuint8_t index)
{
  CYCLIC_ON_REQUEST_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index].msg_handle);
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_Cyclic_On_Request_Msg                            *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function                                                   *
******************************************************************************/
static void Periodic_Task_For_Cyclic_On_Request_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_ON_REQUEST_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_REQUEST_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_ON_REQUEST].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = &CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &CYCLIC_ON_REQUEST_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_Cyclic_On_Request_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_Cyclic_On_Request_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_Cyclic_On_Request_Msg                      *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function checks if msg needs to be queued for tx          *
******************************************************************************/
static void Check_And_Queue_For_Tx_Cyclic_On_Request_Msg(canuint8_t index)
{
  const CYCLIC_ON_REQUEST_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_ON_REQUEST_MSG_Runtime_Info_T* ptr_to_runtime_table;

  ptr_to_config_table = &CYCLIC_ON_REQUEST_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &CYCLIC_ON_REQUEST_MSG_Runtime_Info[index];
  
  if((cbTRUE == ptr_to_runtime_table->tx_requested)&&
     (cbTRUE == ptr_to_runtime_table->cyclic_timer_expired))
  {
     AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
     ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
     #ifdef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
     if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
     }
     #endif
  }
}
#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_Cyclic_And_On_Event_Msg                              *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to CYCLIC_AND_ON_EVENT messages             *
******************************************************************************/
static void Cold_Init_For_Cyclic_And_On_Event_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_config_table = &CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index];
     ptr_to_runtime_table = &CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->event_occurred = cbFALSE;
     ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     #endif
     #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
     else
     {
       CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
     }
     #else
     CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
     #endif
  }
}

/******************************************************************************
*Prototype: Set_Event_Flag_For_Cyclic_And_On_Event_Msg                        *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality: This API sets the event occurred flag to True                 *
******************************************************************************/
static void Set_Event_Flag_For_Cyclic_And_On_Event_Msg(canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].event_occurred = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Stop_Tx_Cyclic_And_On_Event_Msg                               *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Stop_Tx_Cyclic_And_On_Event_Msg(canuint8_t msg_handle)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(CYCLIC_AND_ON_EVENT, msg_handle);
  if(SCH_INVALID_REQUEST != index)
  {
    CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].cyclic_timer_expired = cbFALSE;
    CAN_TIMER_Cancel(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].cyclic_timer);
  }
}
 
/******************************************************************************
*Prototype: SCH_Start_Tx_Cyclic_And_On_Event_Msg                               *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality: This API sets the start transmission flag to True              *
******************************************************************************/
void SCH_Start_Tx_Cyclic_And_On_Event_Msg(canuint8_t msg_handle)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(CYCLIC_AND_ON_EVENT, msg_handle);
  if(SCH_INVALID_REQUEST != index)
  {
    CAN_TIMER_Start(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].cyclic_timer);
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event                 *
*Arguments passed: msg handle                                                 *
*Return value: index                                                          *
*Functionality: This API gets the index of the Cyclic And On Event Msg fron   *
*the msg handle passed                                                        *
******************************************************************************/
static canuint8_t SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event(
                                                            canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_Cyclic_And_On_Event_Msg_Table; index++)
  {
    if(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].msg_handle == 
       msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Start_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event               *
*Arguments passed: msg handle                                                 *
*Return value: index                                                          *
*Functionality:This API starts the cyclic and timeout timers of the Cyclic And*
* On Event messages on the given channel                                      *
******************************************************************************/
static void Start_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event(
                                                        canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     if(cbTRUE == 
       CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].startup_delay_timer_expired)
     {
     #endif
     CAN_TIMER_Start(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].cyclic_timer);
/*     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     if(DUMMY_TIMER!=CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Start(
                    CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif*/
     #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     }
     #endif
  }
}

/******************************************************************************
*Prototype: Cancel_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event              *
*Arguments passed: msg handle                                                 *
*Return value: index                                                          *
*Functionality:This API cancels the cyclic and timeout timers of the Cyclic And*
* On Event messages on the given channel                                      *
******************************************************************************/
static void Cancel_Cyclic_And_Timeout_Timers_Cyclic_And_On_Event(
                                                        canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
     CAN_TIMER_Cancel(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].cyclic_timer);
     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     if(DUMMY_TIMER!=CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Cancel(
                    CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_Cyclic_And_On_Event_Msg                     *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Immediate_Process_Cyclic_And_On_Event_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_Cyclic_And_On_Event_Msg_Table; index ++)
  {
    ptr_to_config_table = &CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Queue_For_Tx_Cyclic_And_On_Event_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_Msg(index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_Msg(index);
        break;
      }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Cyclic_And_On_Event_Msg                              *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Set_Flag_Cyclic_And_On_Event_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_Cyclic_And_On_Event_Msg_Table; index ++)
  {
    ptr_to_config_table = &CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
      if(ptr_to_config_table->timeout_timer == timer_name)
      {
        SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_Msg(index);
        break;
      }
    #endif
    #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
      if(ptr_to_config_table->startup_delay_timer == timer_name)
      {
        SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_Msg(index);
        break;
      }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_Msg                 *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_Msg(canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Queue_For_Tx_Cyclic_And_On_Event_Msg                          *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets cyclic timer expired- flag to cbTRUE and checks if the  *
*critical msg needs to be queued for transmission                             *
******************************************************************************/
static void SCH_Queue_For_Tx_Cyclic_And_On_Event_Msg(canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
  Check_And_Queue_For_Tx_Cyclic_And_On_Event_Msg(index);
}

#ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Cyclic_On_Init_Msg                  *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_Msg(canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].msg_handle);
}
#endif

#ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_On_Init_Msg              *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_Msg(canuint8_t 
                                                                       index)
{
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index].startup_delay_timer_expired 
  = cbTRUE;
  CAN_TIMER_Start(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index].cyclic_timer);
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_Cyclic_And_On_Event_Msg                         *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This function                                                  *
******************************************************************************/
static void Periodic_Task_For_Cyclic_And_On_Event_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].start_index;
  end_index = Tx_Ch_Index[channel_number][CYCLIC_AND_ON_EVENT].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = &CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_Cyclic_And_On_Event_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_Cyclic_And_On_Event_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_Cyclic_And_On_Event_Msg                    *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function checks if msg needs to be queued for tx          *
******************************************************************************/
static void Check_And_Queue_For_Tx_Cyclic_And_On_Event_Msg(canuint8_t index)
{
  const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T* ptr_to_config_table;
  CYCLIC_AND_ON_EVENT_MSG_Runtime_Info_T* ptr_to_runtime_table;

  ptr_to_config_table = &CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &CYCLIC_AND_ON_EVENT_MSG_Runtime_Info[index];
  
  #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
     ((cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)||
      (cbTRUE == ptr_to_runtime_table->event_occurred)))
  #else
  if((cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)||
     (cbTRUE == ptr_to_runtime_table->event_occurred))
  #endif
  {
     AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
     if(cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)
     {
       ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
     }
     if(cbTRUE == ptr_to_runtime_table->event_occurred)
     {
       ptr_to_runtime_table->event_occurred = cbFALSE;
     }
     CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
     if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
     }
     #endif
  }
}
#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg         *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME *
* messages                                                                     *
******************************************************************************/
static void Cold_Init_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(canuint8_t 
                                                                channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* 
                                           ptr_to_config_table;
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* 
                                          ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number]
                [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = Tx_Ch_Index[channel_number]
              [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
     ptr_to_config_table = 
     &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
     ptr_to_runtime_table = 
     &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
     
     ptr_to_runtime_table->event_occurred = cbFALSE;
     ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
     ptr_to_runtime_table->min_delay_timer_expired = cbTRUE;
     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
     #endif
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     ptr_to_runtime_table->startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != ptr_to_config_table->startup_delay_timer)
     {
       CAN_TIMER_Start(ptr_to_config_table->startup_delay_timer);
     }
     else
     {
       CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
     }
  #else
     CAN_TIMER_Start(ptr_to_config_table->cyclic_timer);
  #endif
  }
}

/******************************************************************************
*Prototype: Set_Event_Flag_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg   *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality: This API sets the event occurred flag to True                 *
******************************************************************************/
static void Set_Event_Flag_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                              canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  event_occurred = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg          *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality: This API stops the transmission of this type of message by    *
*cancelling the timer corresponding to that message                           *
******************************************************************************/
void SCH_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(canuint8_t
                                                                    msg_handle)
{
  canuint8_t index;

  index =SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event_With_Min_Update_Time(
         msg_handle);
  if(SCH_INVALID_REQUEST != index)
  {
    CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
    cyclic_timer_expired = cbFALSE;
    CAN_TIMER_Cancel(CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table
                     [index].cyclic_timer);
  }
}

/******************************************************************************
Prototype:SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event_With_Min_Update_Time
*Arguments passed: msg handle                                                 *
*Return value: index                                                          *
*Functionality: This API gets the index of the Cyclic And On Event With Min   *
*Update Time msg from the msg handle passed                                   *
******************************************************************************/
static canuint8_t 
SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event_With_Min_Update_Time(
                                                            canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < 
      Size_Of_Cyclic_And_On_Event_With_Min_Update_Time_Msg_Table; index++)
  {
    if(CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
       msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype:Start_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API starts the cyclic, min_delay and timeout timers of the*
*Cyclic And On Event With Min Update Time messages on the given channel       *
******************************************************************************/
static void 
Start_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time(canuint8_t channel_number)
{  
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number]
                [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = Tx_Ch_Index[channel_number]
              [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     if(cbTRUE == 
        CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
        startup_delay_timer_expired)
     {
 #endif
     CAN_TIMER_Start(
     CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                 cyclic_timer);
/*     CAN_TIMER_Start(
     CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                             min_delay_timer);*/
/*     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     if(DUMMY_TIMER != 
      CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                 timeout_timer)
     {
       CAN_TIMER_Start(
       CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                timeout_timer);
     }
     #endif*/
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     }
 #endif
  }
}

/******************************************************************************
*Prototype:Cancel_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API cancels the cyclic, min_delay and timeout timers of the*
*Cyclic And On Event With Min Update Time messages on the given channel       *
******************************************************************************/
static void
Cancel_Cyclic_MinDelay_And_Timeout_Timers_Cyclic_And_On_Event_With_Min_Update_Time(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number]
                [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = Tx_Ch_Index[channel_number]
              [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
     CAN_TIMER_Cancel(
     CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                 cyclic_timer);
     CAN_TIMER_Cancel(
     CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                              min_delay_timer);
     #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
     if(DUMMY_TIMER != 
      CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                 timeout_timer)
     {
       CAN_TIMER_Cancel(
       CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].
                                                                timeout_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_Cyclic_And_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Immediate_Process_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                           CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* 
  ptr_to_config_table;
  
  for(index=0;index<Size_Of_Cyclic_And_On_Event_With_Min_Update_Time_Msg_Table;
      index ++)
  {
    ptr_to_config_table = 
    &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
      break;
    }
    else if(ptr_to_config_table->min_delay_timer == timer_name)
    {
     SCH_Set_Min_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
      index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
     SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
     index);
     break;
    }
    #endif
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
    }
 #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg         *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Set_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                         CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* 
  ptr_to_config_table;
  
  for(index=0;index<Size_Of_Cyclic_And_On_Event_With_Min_Update_Time_Msg_Table;
      index ++)
  {
    ptr_to_config_table = 
    &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->min_delay_timer == timer_name)
    {
     SCH_Set_Min_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
     index);
      break;
    }
    else if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
      index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
     SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
      index);
      break;
    }
    #endif
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
      break;
    }
 #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Min_Delay_Expiry_Notifier_Function_Cyclic_And_On_Event_With_Min_Update_Time_Msg        *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void 
SCH_Set_Min_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                 canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  min_delay_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg        *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void 
SCH_Set_Timer_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                         canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  cyclic_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg     *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets cyclic timer expired- flag to cbTRUE and checks if the  *
*critical msg needs to be queued for transmission                             *
******************************************************************************/
static void SCH_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                            canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  cyclic_timer_expired = cbTRUE;

  Check_And_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
}

#ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_With_Min_Update_Time_Msg                  *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void 
SCH_Timeout_Notifier_Function_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                             canuint8_t index)
{
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
  timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].msg_handle);
}

#endif

#ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg              *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_Cyclic_And_On_Event_With_Min_Update_Time_Msg(canuint8_t index)
{
 CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index].
 startup_delay_timer_expired = cbTRUE;
 CAN_TIMER_Start(
 CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index].cyclic_timer);
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg     *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME *
*messages                                                                      *
******************************************************************************/
static void Periodic_Task_For_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                    canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* 
                                           ptr_to_config_table;
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* 
                                          ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number]
                [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].start_index;
  end_index = Tx_Ch_Index[channel_number]
              [CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = 
    &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = 
    &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
     Check_And_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg*
*Arguments passed: index                                                       *
*Return value: none                                                            *
*Functionality:This function checks if msg needs to be queued for tx           *
******************************************************************************/
static void Check_And_Queue_For_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                                 canuint8_t index)
{
  const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T* 
                                           ptr_to_config_table;
  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info_T* 
                                          ptr_to_runtime_table;

  ptr_to_config_table = 
  &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = 
  &CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_Runtime_Info[index];
  
 #ifdef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
     (cbTRUE == ptr_to_runtime_table->min_delay_timer_expired)&&
     ((cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)||
     (cbTRUE == ptr_to_runtime_table->event_occurred)))
 #else
  if((cbTRUE == ptr_to_runtime_table->min_delay_timer_expired)&&
     ((cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)||
     (cbTRUE == ptr_to_runtime_table->event_occurred)))
 #endif
  {
    AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
    ptr_to_runtime_table->min_delay_timer_expired = cbFALSE;
    CAN_TIMER_Start(ptr_to_config_table->min_delay_timer);
    if(cbTRUE == ptr_to_runtime_table->cyclic_timer_expired)
    {
      ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
    }
    if(cbTRUE == ptr_to_runtime_table->event_occurred)
    {
      ptr_to_runtime_table->event_occurred = cbFALSE;
    }
    
    CAN_TIMER_Start(ptr_to_config_table->min_delay_timer);
    #ifdef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
    if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
    {
      CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
    }
    #endif
  }
}
#endif

#ifdef BAF_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_BAF_Msg                                              *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to BAF messages                             *
******************************************************************************/
static void Cold_Init_For_BAF_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 

  start_index = Tx_Ch_Index[channel_number][BAF].start_index;
  end_index = Tx_Ch_Index[channel_number][BAF].end_index;

  for (index = start_index; index < end_index; index++)
  {
     BAF_MSG_Runtime_Info[index].message_is_active = cbFALSE;
     BAF_MSG_Runtime_Info[index].cyclic_timer_expired = cbFALSE;
     #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
     BAF_MSG_Runtime_Info[index].timeout_timer_expired = cbFALSE;
     #endif
     #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
     BAF_MSG_Runtime_Info[index].startup_delay_timer_expired = cbFALSE;
     CAN_TIMER_Start(BAF_MSG_CONFIG_Table[index].startup_delay_timer);
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Update_Msg_Status_For_BAF_Msg                                 *
*Arguments passed: msg handle, msg status                                     *
*Return value: none                                                           *
*Functionality:This API sets the msg active flag to the value passed as request*
*by the user layer                                                            *
******************************************************************************/
void SCH_Update_Msg_Status_For_BAF_Msg(canuint8_t msg_handle,
                                       canbool8_t msg_status)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(BAF, msg_handle);
  if(SCH_INVALID_REQUEST != index)
  {
    BAF_MSG_Runtime_Info[index].message_is_active = msg_status;
    if(CAN_SCH_MESSAGE_ACTIVE == msg_status)
    {
      CAN_TIMER_Start(BAF_MSG_CONFIG_Table[index].cyclic_timer);
    }
    else
    {
      CAN_TIMER_Cancel(BAF_MSG_CONFIG_Table[index].cyclic_timer);
      #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
      if(DUMMY_TIMER != BAF_MSG_CONFIG_Table[index].timeout_timer)
      {
        CAN_TIMER_Cancel(BAF_MSG_CONFIG_Table[index].timeout_timer);
      }
      #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_BAF                                 *
*Arguments passed: msg handle                                                 *
*Return value: index                                                          *
*Functionality:This API gets the index of the BAF msg from the msg handle     *
*passed                                                                       *
******************************************************************************/
static canuint8_t SCH_Get_Index_From_Msg_Handle_BAF(canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_BAF_Msg_Table; index++)
  {
    if(BAF_MSG_CONFIG_Table[index].msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Start_Cyclic_And_Timeout_Timers_BAF                               *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API starts the cyclic and timeout timers of the BAF       *
* messages on the given channel                                               *
******************************************************************************/
static void Start_Cyclic_And_Timeout_Timers_BAF(canuint8_t channel_number)
{  
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][BAF].start_index;
  end_index = Tx_Ch_Index[channel_number][BAF].end_index;

  for (index = start_index; index < end_index; index++)
  {
     #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
     if(cbTRUE == BAF_MSG_Runtime_Info[index].startup_delay_timer_expired)
     {
     #endif
     CAN_TIMER_Start(BAF_MSG_CONFIG_Table[index].cyclic_timer);
     #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
     }
     #endif
  }
}

/******************************************************************************
*Prototype: Cancel_Cyclic_And_Timeout_Timers_BAF                              *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API cancels the cyclic and timeout timers of the BAF      *
* messages on the given channel                                               *
******************************************************************************/
static void Cancel_Cyclic_And_Timeout_Timers_BAF(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][BAF].start_index;
  end_index = Tx_Ch_Index[channel_number][BAF].end_index;

  for (index = start_index; index < end_index; index++)
  {
     CAN_TIMER_Cancel(BAF_MSG_CONFIG_Table[index].cyclic_timer);
     #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
     if(DUMMY_TIMER != BAF_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Cancel(BAF_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_BAF_Msg                                     *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Immediate_Process_BAF_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const BAF_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_BAF_Msg_Table; index ++)
  {
    ptr_to_config_table = &BAF_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Queue_For_Tx_BAF_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
      SCH_Timeout_Expiry_Notifier_Function_BAF_Msg(index);
      break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_BAF_Msg(index);
      break;
    }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_BAF_Msg                                              *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Set_Flag_BAF_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const BAF_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_BAF_Msg_Table; index ++)
  {
    ptr_to_config_table = &BAF_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->cyclic_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_BAF_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
      SCH_Timeout_Expiry_Notifier_Function_BAF_Msg(index);
      break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_BAF_Msg(index);
      break;
    }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Timer_Expiry_Flag_BAF_Msg                                 *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Timer_Expiry_Flag_BAF_Msg(canuint8_t index)
{
  BAF_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Queue_For_Tx_BAF_Msg                                          *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets cyclic timer expired- flag to cbTRUE and checks if the  *
*critical msg needs to be queued for transmission                             *
******************************************************************************/
static void SCH_Queue_For_Tx_BAF_Msg(canuint8_t index)
{
  BAF_MSG_Runtime_Info[index].cyclic_timer_expired = cbTRUE;
  Check_And_Queue_For_Tx_BAF_Msg(index);
}

#ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Timeout_Expiry_Notifier_Function_BAF_Msg                      *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Timeout_Expiry_Notifier_Function_BAF_Msg(canuint8_t index)
{
  BAF_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(BAF_MSG_CONFIG_Table[index].msg_handle);
}
#endif

#ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Set_Startup_Delay_Expiry_Flag_BAF_Msg                         *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void  SCH_Set_Startup_Delay_Expiry_Flag_BAF_Msg(canuint8_t index)
{
  BAF_MSG_Runtime_Info[index].startup_delay_timer_expired = cbTRUE;
  CAN_TIMER_Start(BAF_MSG_CONFIG_Table[index].cyclic_timer);
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_BAF_Msg                                         *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This function                                                  *
******************************************************************************/
static void Periodic_Task_For_BAF_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const BAF_MSG_CONFIG_T* ptr_to_config_table;
  BAF_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][BAF].start_index;
  end_index = Tx_Ch_Index[channel_number][BAF].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = &BAF_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &BAF_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_BAF_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_BAF_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_BAF_Msg                                    *
*Arguments passed: index                                                       *
*Return value: none                                                            *
*Functionality:This function checks if msg needs to be queued for tx           *
******************************************************************************/
static void Check_And_Queue_For_Tx_BAF_Msg(canuint8_t index)
{
  const BAF_MSG_CONFIG_T* ptr_to_config_table;
  BAF_MSG_Runtime_Info_T* ptr_to_runtime_table;

  ptr_to_config_table = &BAF_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &BAF_MSG_Runtime_Info[index];
   
   #ifdef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED
   if((cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)&&
      (cbTRUE == ptr_to_runtime_table->message_is_active)&&
      (cbTRUE == ptr_to_runtime_table->cyclic_timer_expired))
   #else
   if((cbTRUE == ptr_to_runtime_table->message_is_active)&&
      (cbTRUE == ptr_to_runtime_table->cyclic_timer_expired))
   #endif
   {
      AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
      ptr_to_runtime_table->cyclic_timer_expired = cbFALSE;
      #ifdef TIMEOUT_FOR_BAF_MSG_SUPPORTED
      if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
      {
        CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
      }
      #endif
   }
}
#endif

#ifdef FAST_MSG_SUPPORTED
/******************************************************************************
*Prototype: Cold_Init_For_FAST_Msg                                             *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to FAST messages                            *
******************************************************************************/
static void Cold_Init_For_FAST_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 

  start_index = Tx_Ch_Index[channel_number][FAST].start_index;
  end_index = Tx_Ch_Index[channel_number][FAST].end_index;

  for (index = start_index; index < end_index; index++)
  {
     FAST_MSG_Runtime_Info[index].message_is_active = cbFALSE;
     FAST_MSG_Runtime_Info[index].slow_timer_expired = cbFALSE;
     FAST_MSG_Runtime_Info[index].fast_timer_expired = cbFALSE;
     #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
     FAST_MSG_Runtime_Info[index].timeout_timer_expired = cbFALSE;
     #endif
     #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
     FAST_MSG_Runtime_Info[index].startup_delay_timer_expired = cbFALSE;
     if(DUMMY_TIMER != FAST_MSG_CONFIG_Table[index].startup_delay_timer)
     {
       CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].startup_delay_timer);
     }
     else
     {
       CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].slow_timer);
       /*#ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
       if(DUMMY_TIMER != FAST_MSG_CONFIG_Table[index].timeout_timer)
       {
         CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].timeout_timer);
       }
       #endif*/
     }
     #else
     CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].slow_timer);
     /*#ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
     if(DUMMY_TIMER != FAST_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif*/
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Update_Msg_Status_For_BAF_Msg                                 *
*Arguments passed: msg handle, msg status                                     *
*Return value: none                                                           *
*Functionality:This API sets the msg active flag to the value passed as request*
*by the user layer                                                            *
******************************************************************************/
void SCH_Update_Msg_Status_For_FAST_Msg(canuint8_t msg_handle,
                                        canbool8_t msg_status)
{
  canuint8_t index;

  index = SCH_Get_Index_From_Msg_Handle(FAST, msg_handle);
  if(SCH_INVALID_REQUEST != index)
  {
    FAST_MSG_Runtime_Info[index].message_is_active = msg_status;
    if(CAN_SCH_MESSAGE_ACTIVE == msg_status)//start fast timer,cancel slowtimer
    {
      CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].fast_timer);
      CAN_TIMER_Cancel(FAST_MSG_CONFIG_Table[index].slow_timer);
    }
    else //msg is not active: start slow timer, cancel fast timer
    {
      CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].slow_timer);
      CAN_TIMER_Cancel(FAST_MSG_CONFIG_Table[index].fast_timer);
    }
  }
}

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle_FAST                                *
*Arguments passed: msg handle                                                 *
*Return value: index                                                          *
*Functionality:This API gets the index of the FAST msg from the msg handle    *
*passed                                                                       *
******************************************************************************/
static canuint8_t SCH_Get_Index_From_Msg_Handle_FAST(canuint8_t msg_handle)
{
  canuint8_t index = SCH_INVALID_REQUEST;
  
  for(index=0; index < Size_Of_FAST_Msg_Table; index++)
  {
    if(FAST_MSG_CONFIG_Table[index].msg_handle == msg_handle)
    {
      break;
    }
  }
  return(index);
}

/******************************************************************************
*Prototype: Start_Cyclic_And_Timeout_Timers_FAST                              *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API starts the cyclic and timeout timers of the FAST      *
* messages on the given channel                                               *
******************************************************************************/
static void Start_Cyclic_And_Timeout_Timers_FAST(canuint8_t channel_number)
{  
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][FAST].start_index;
  end_index = Tx_Ch_Index[channel_number][FAST].end_index;

  for (index = start_index; index < end_index; index++)
  {
     #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
     if(cbTRUE == FAST_MSG_Runtime_Info[index].startup_delay_timer_expired)
     {
     #endif
     if(cbTRUE == FAST_MSG_Runtime_Info[index].message_is_active)
     {
       CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].fast_timer);
     }
     else
     {
       CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].slow_timer);
     }
     #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
     if(DUMMY_TIMER != FAST_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif
     #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
     }
     #endif
  }
}

/******************************************************************************
*Prototype: Cancel_Cyclic_And_Timeout_Timers_FAST                             *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality:This API cancels the cyclic and timeout timers of the FAST     *
* messages on the given channel                                               *
******************************************************************************/
static void Cancel_Cyclic_And_Timeout_Timers_FAST(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index;
  
  start_index = Tx_Ch_Index[channel_number][FAST].start_index;
  end_index = Tx_Ch_Index[channel_number][FAST].end_index;

  for (index = start_index; index < end_index; index++)
  {
     if(cbTRUE == FAST_MSG_Runtime_Info[index].message_is_active)
     {
       CAN_TIMER_Cancel(FAST_MSG_CONFIG_Table[index].fast_timer);
     }
     else
     {
       CAN_TIMER_Cancel(FAST_MSG_CONFIG_Table[index].slow_timer);
     }
     #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
     if(DUMMY_TIMER != FAST_MSG_CONFIG_Table[index].timeout_timer)
     {
       CAN_TIMER_Cancel(FAST_MSG_CONFIG_Table[index].timeout_timer);
     }
     #endif
  }
}

/******************************************************************************
*Prototype: SCH_Immediate_Process_FAST_Msg                                    *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Immediate_Process_FAST_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const FAST_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_FAST_Msg_Table; index ++)
  {
    ptr_to_config_table = &FAST_MSG_CONFIG_Table[index];
    
    if((ptr_to_config_table->fast_timer == timer_name)
       ||(ptr_to_config_table->slow_timer == timer_name))
    {
      SCH_Queue_For_Tx_FAST_Msg(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
      SCH_Timeout_Expiry_Notifier_Function_FAST_Msg(index);
      break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_FAST_Msg(index);
      break;
    }
    #endif
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_FAST_Msg                                             *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality: This API sets the stop transmission flag to True              *
******************************************************************************/
void SCH_Set_Flag_FAST_Msg(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;
  const FAST_MSG_CONFIG_T* ptr_to_config_table;
  
  for(index = 0; index < Size_Of_FAST_Msg_Table; index ++)
  {
    ptr_to_config_table = &FAST_MSG_CONFIG_Table[index];
    
    if(ptr_to_config_table->fast_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_FAST_Msg_Fast_Timer(index);
      break;
    }
    else if(ptr_to_config_table->slow_timer == timer_name)
    {
      SCH_Set_Timer_Expiry_Flag_FAST_Msg_Slow_Timer(index);
      break;
    }
    else
    {
    #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
    if(ptr_to_config_table->timeout_timer == timer_name)
    {
      SCH_Timeout_Expiry_Notifier_Function_FAST_Msg(index);
      break;
    }
    #endif
    #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
    if(ptr_to_config_table->startup_delay_timer == timer_name)
    {
      SCH_Set_Startup_Delay_Expiry_Flag_FAST_Msg(index);
      break;
    }
    #endif
    }
  }
}

/******************************************************************************
*Prototype:SCH_Set_Timer_Expiry_Flag_FAST_Msg_Slow_Timer                      *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Timer_Expiry_Flag_FAST_Msg_Slow_Timer(canuint8_t index)
{
  FAST_MSG_Runtime_Info[index].slow_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype:SCH_Set_Timer_Expiry_Flag_FAST_Msg_Fast_Timer                      *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Set_Timer_Expiry_Flag_FAST_Msg_Fast_Timer(canuint8_t index)
{
  FAST_MSG_Runtime_Info[index].fast_timer_expired = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Queue_For_Tx_FAST_Msg                                         *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires. It sets cyclic timer expired- flag to cbTRUE and checks if the  *
*critical msg needs to be queued for transmission                             *
******************************************************************************/
static void SCH_Queue_For_Tx_FAST_Msg(canuint8_t index)
{
  if(cbTRUE == FAST_MSG_Runtime_Info[index].message_is_active)
  {
    FAST_MSG_Runtime_Info[index].fast_timer_expired = cbTRUE;
  }
  else
  {
    FAST_MSG_Runtime_Info[index].slow_timer_expired = cbTRUE;
  }

  Check_And_Queue_For_Tx_FAST_Msg(index);
}

#ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Timeout_Expiry_Notifier_Function_FAST_Msg                     *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Timeout_Expiry_Notifier_Function_FAST_Msg(canuint8_t index)
{
  FAST_MSG_Runtime_Info[index].timeout_timer_expired = cbTRUE;
  AIF_Set_Tx_Msg_Timeout(FAST_MSG_CONFIG_Table[index].msg_handle);
}
#endif

#ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
/******************************************************************************
*Prototype: SCH_Set_Startup_Delay_Expiry_Flag_FAST_Msg                        *
*Arguments passed: index                                                      *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Startup_Delay_Expiry_Flag_FAST_Msg(canuint8_t index)
{
  FAST_MSG_Runtime_Info[index].startup_delay_timer_expired = cbTRUE;
  //CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].slow_timer);
  if(cbTRUE == FAST_MSG_Runtime_Info[index].message_is_active)
  {
    CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].fast_timer);
  }
  else
  {
    CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].slow_timer);
  }
  #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
  if(DUMMY_TIMER != FAST_MSG_CONFIG_Table[index].timeout_timer)
  {
    CAN_TIMER_Start(FAST_MSG_CONFIG_Table[index].timeout_timer);
  }
  #endif
}
#endif

/******************************************************************************
*Prototype: Periodic_Task_For_FAST_Msg                                         *
*Arguments passed: channel number                                              *
*Return value: none                                                            *
*Functionality:This function initializes all control variables & flags to their*
*respective default values related to FAST messages                            *
******************************************************************************/
static void Periodic_Task_For_FAST_Msg(canuint8_t channel_number)
{
  canuint8_t index, start_index, end_index; 
  const FAST_MSG_CONFIG_T* ptr_to_config_table;
  FAST_MSG_Runtime_Info_T* ptr_to_runtime_table;

  start_index = Tx_Ch_Index[channel_number][FAST].start_index;
  end_index = Tx_Ch_Index[channel_number][FAST].end_index;

  for (index = start_index; index < end_index; index++)
  {
    ptr_to_config_table = &FAST_MSG_CONFIG_Table[index];
    ptr_to_runtime_table = &FAST_MSG_Runtime_Info[index];
   
    #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
    if(cbFALSE == ptr_to_runtime_table->timeout_timer_expired)
    {
      Check_And_Queue_For_Tx_FAST_Msg(index);
    }
    #else
    Check_And_Queue_For_Tx_FAST_Msg(index);
    #endif
  }
}

/******************************************************************************
*Prototype: Check_And_Queue_For_Tx_FAST_Msg                                    *
*Arguments passed: index                                                       *
*Return value: none                                                            *
*Functionality:This function checks if msg needs to be queued for tx           *
******************************************************************************/
static void Check_And_Queue_For_Tx_FAST_Msg(canuint8_t index)
{
  const FAST_MSG_CONFIG_T* ptr_to_config_table;
  FAST_MSG_Runtime_Info_T* ptr_to_runtime_table;
  
  ptr_to_config_table = &FAST_MSG_CONFIG_Table[index];
  ptr_to_runtime_table = &FAST_MSG_Runtime_Info[index];

  #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
  if(cbTRUE == ptr_to_runtime_table->startup_delay_timer_expired)
  {
  #endif
    if(cbTRUE == ptr_to_runtime_table->message_is_active)
    {
      if(cbTRUE == ptr_to_runtime_table->fast_timer_expired)
      {
         AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
         ptr_to_runtime_table->fast_timer_expired = cbFALSE;
         #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
         if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
         {
           CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
         }
         #endif
      }
    }
    else // signal not active 
    {
       if(cbTRUE == ptr_to_runtime_table->slow_timer_expired)
       {
         AIF_Queue_For_Tx(ptr_to_config_table->msg_handle);
         ptr_to_runtime_table->slow_timer_expired = cbFALSE;
         #ifdef TIMEOUT_FOR_FAST_MSG_SUPPORTED
         if(DUMMY_TIMER != ptr_to_config_table->timeout_timer)
         {
           CAN_TIMER_Start(ptr_to_config_table->timeout_timer);
         }
         #endif
       }
    }
  #ifdef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED
  }
  #endif
}
#endif

/******************************************************************************
*Prototype: SCH_Get_Index_From_Msg_Handle                                     *
*Arguments passed: msg type, msg handle                                       *
*Return value: none                                                           *
*Functionality:This function is gets the index of the message whose msg handle*
*is passed by looking in the table corresponding to the message type          *
******************************************************************************/
 canuint8_t SCH_Get_Index_From_Msg_Handle(Message_Transmission_Mode_T 
                                                 msg_type, canuint8_t msg_handle)
{
  canuint8_t index;

  switch(msg_type)
  {
  #ifdef  ON_EVENT_MSG_SUPPORTED
  case (ON_EVENT):
       index = 
       SCH_Get_Index_From_Msg_Handle_On_Event(msg_handle);
       break;
  #endif
  #ifdef  ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  case (ON_EVENT_WITH_MIN_UPDATE_TIME):
       index = 
       SCH_Get_Index_From_Msg_Handle_On_Event_With_Min_Update_Time(msg_handle);
       break;
  #endif
  #ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
  case (N_TIMES_ON_EVENT):
       index = SCH_Get_Index_From_Msg_Handle_N_Times_On_Event(msg_handle);
       break;
  #endif
  #ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  case (N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME):
       index = 
       SCH_Get_Index_From_Msg_Handle_N_Times_On_Event_With_Min_Update_Time(
                                                                   msg_handle);
       break;
  #endif
  #ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
  case (CYCLIC_ON_INIT):
       index = SCH_Get_Index_From_Msg_Handle_Cyclic_On_Init(msg_handle);
       break;
  #endif
  #ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
  case (CYCLIC_ON_REQUEST):
       index = SCH_Get_Index_From_Msg_Handle_Cyclic_On_Request(msg_handle);
       break;
  #endif
  #ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
  case (CYCLIC_AND_ON_EVENT):
       index = SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event(msg_handle);
       break;
  #endif
  #ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
  case (CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME):
       index = 
       SCH_Get_Index_From_Msg_Handle_Cyclic_And_On_Event_With_Min_Update_Time(
                                                                  msg_handle);
       break;
  #endif
  #ifdef  BAF_MSG_SUPPORTED
  case (BAF):
       index = SCH_Get_Index_From_Msg_Handle_BAF(msg_handle);
       break;
  #endif
  #ifdef  FAST_MSG_SUPPORTED
  case (FAST):
       index = SCH_Get_Index_From_Msg_Handle_FAST(msg_handle);
       break;
  #endif
  default:
       Appl_Invalid_Msg_Type_Request();
       index = SCH_INVALID_REQUEST;
       break;
  }
  return(index);
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
