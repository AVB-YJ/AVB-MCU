/******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS:  Prakash, Sandeep                                                 *
 * File Name: can_sch_rx.c                                                    *
 * File Description:                                                          *
******************************************************************************/
#include "can_sch_rx.h"
#include "can_timer_mod.h"
#include "can_aif_rx.h"
#include "can_handler_appl_notifier_functions.h"
#include "can_aif_rx.h"
#include "can_sch_rx.h"
#include "can_vbm_rx.h"
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
static const SCH_Rx_Msg_Timeout_Config_T *SCH_Rx_Msg_Timeout_Config_Tables[]=
{
  #ifdef CAN_CH0_SELECTED
  SCH_Rx_Msg_Timeout_Config_Table_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  SCH_Rx_Msg_Timeout_Config_Table_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  SCH_Rx_Msg_Timeout_Config_Table_Ch2
  #endif
};

#ifdef CAN_CH0_SELECTED
SCH_Rx_Msg_Timeout_Runtime_Info_T SCH_Rx_Msg_Timeout_Runtime_Info_Ch0
                                  [NUMBER_OF_RX_MSG_SUPPORTED_CH0];
#endif
#ifdef CAN_CH1_SELECTED
SCH_Rx_Msg_Timeout_Runtime_Info_T SCH_Rx_Msg_Timeout_Runtime_Info_Ch1
                                  [NUMBER_OF_RX_MSG_SUPPORTED_CH1];
#endif
#ifdef CAN_CH2_SELECTED
SCH_Rx_Msg_Timeout_Runtime_Info_T SCH_Rx_Msg_Timeout_Runtime_Info_Ch2
                                  [NUMBER_OF_RX_MSG_SUPPORTED_CH2];
#endif

static SCH_Rx_Msg_Timeout_Runtime_Info_T * SCH_Rx_Msg_Timeout_Runtime_Info[]=
{
  #ifdef CAN_CH0_SELECTED
  SCH_Rx_Msg_Timeout_Runtime_Info_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  SCH_Rx_Msg_Timeout_Runtime_Info_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  SCH_Rx_Msg_Timeout_Runtime_Info_Ch2
  #endif
};
#endif

/******************************************************************************
*****                           STATIC VARIABLES                          *****
******************************************************************************/
static canbool8_t Rx_State_Activated[NUMBER_OF_CHANNELS_SUPPORTED];

/******************************************************************************
*****           PROTOTYPE DECLARATION FOR STATIC FUNCTIONS                *****
******************************************************************************/
 void SCH_Rx_Periodic_Task_For_Channel(canuint8_t channel_number);

#ifdef CAN_CH0_SELECTED
 void SCH_Timeout_Notifier_Function_Rx_Msg_Ch0(canuint8_t msg_handle);
 void SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch0(canuint8_t msg_handle);
#endif
#ifdef CAN_CH1_SELECTED
static void SCH_Timeout_Notifier_Function_Rx_Msg_Ch1(canuint8_t msg_handle);
static void SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch1(canuint8_t msg_handle);
#endif
#ifdef CAN_CH2_SELECTED
static void SCH_Timeout_Notifier_Function_Rx_Msg_Ch2(canuint8_t msg_handle);
static void SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch2(canuint8_t msg_handle);
#endif

/******************************************************************************
*Prototype: SCH_Rx_Cold_Initialization                                        *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This is the cold initialization routine for Rx functionality  *
*of Scheduler. This API initializes all runtime flags to default(cbFALSE) values*
******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
void SCH_Rx_Cold_Initialization(canuint8_t channel_number)
{
  canuint8_t index;
  
  for(index=0;index<Size_Of_Rx_Timeout_Monitor_Tables[channel_number];index ++)
  {
    SCH_Rx_Msg_Timeout_Runtime_Info[channel_number][index].timeout_timer_expired
                                                                     = cbFALSE;
    if(DUMMY_TIMER != SCH_Rx_Msg_Timeout_Config_Tables[channel_number][index].
       timeout_timer)
    {
      CAN_TIMER_Start(SCH_Rx_Msg_Timeout_Config_Tables[channel_number][index].
      timeout_timer);
    }
  }
}

/******************************************************************************
*Prototype: SCH_Rx_Periodic_Task                                              *
*Arguments passed: none                                                       *
*Return value: none                                                           *
*Functionality: This is the receive periodic task for the Scheduler.          *
*It handle the time out of all the receive functional messages                *
******************************************************************************/
void SCH_Rx_Periodic_Task()
{
  #ifdef CAN_CH0_SELECTED
  if(cbTRUE == Rx_State_Activated[0])
  {
    SCH_Rx_Periodic_Task_For_Channel(0);
  }
  #endif
  #ifdef CAN_CH1_SELECTED
  if(cbTRUE == Rx_State_Activated[1])
  {
    SCH_Rx_Periodic_Task_For_Channel(1);
  }
  #endif
  #ifdef CAN_CH2_SELECTED
  if(cbTRUE == Rx_State_Activated[2])
  {
    SCH_Rx_Periodic_Task_For_Channel(2);
  }
  #endif
}
#endif

/******************************************************************************
*Prototype: SCH_Set_Rx_Inactive                                               *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This API sets the Rx_State_Activated flag to cbFALSE            *
******************************************************************************/
void SCH_Set_Rx_Inactive(canuint8_t channel_number)
{
  Rx_State_Activated[channel_number] = cbFALSE;
}

/******************************************************************************
*Prototype: SCH_Set_Rx_Active                                                 *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This API sets the Rx_State_Activated flag to cbTRUE             *
******************************************************************************/
void SCH_Set_Rx_Active(canuint8_t channel_number)
{
  Rx_State_Activated[channel_number] = cbTRUE;
}

/******************************************************************************
*Prototype: SCH_Rx_Periodic_Task_For_Channel                                  *
*Arguments passed: channel number                                             *
*Return value: none                                                           *
*Functionality: This is the receive periodic task for the Scheduler.          *
*It handle the time out of all the receive functional messages channel wise   *
******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
static void SCH_Rx_Periodic_Task_For_Channel(canuint8_t channel_number)
{
  canuint8_t index;
  //const SCH_Rx_Msg_Timeout_Config_T* ptr_to_config_table;
  SCH_Rx_Msg_Timeout_Runtime_Info_T* ptr_to_runtime_table;
  
  for(index=0;index<Size_Of_Rx_Timeout_Monitor_Tables[channel_number];index ++)
  {
  //  ptr_to_config_table = 
  //                    &SCH_Rx_Msg_Timeout_Config_Tables[channel_number][index];
    ptr_to_runtime_table = 
                       &SCH_Rx_Msg_Timeout_Runtime_Info[channel_number][index];
    if(cbTRUE == ptr_to_runtime_table->timeout_timer_expired)
      {
        #ifdef CAN_CH0_SELECTED
        if(0 == channel_number)
        {
          AIF_Set_Rx_Msg_Timeout_Ch0(index);
        }
        #endif
        #ifdef CAN_CH1_SELECTED
        if(1 == channel_number)
        {
          AIF_Set_Rx_Msg_Timeout_Ch1(index);
        }
        #endif
        #ifdef CAN_CH2_SELECTED
        if(2 == channel_number)
        {
          AIF_Set_Rx_Msg_Timeout_Ch2(index);
        }
        #endif
        ptr_to_runtime_table->timeout_timer_expired = cbFALSE;
      }
   }
}
#endif

#ifdef CAN_CH0_SELECTED
/******************************************************************************
*Prototype: SCH_Rx_Message_Indication_Ch0                                     *
*Arguments passed: msg  handle                                                *
*Return value: none                                                           *
*Functionality:This function is called by VBM after reception of the          *
*corresponding Rx msg on channel 0 to handle timeout monitoring               *
*Since there is one-to-one mapping between Rx table of VBM, Scheduler and AIF,*
*the msg handle can be directly used as index of the table                    *
******************************************************************************/
void SCH_Rx_Message_Indication_Ch0(canuint8_t msg_handle)
{
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
 CAN_TIMER_Start(SCH_Rx_Msg_Timeout_Config_Tables[0][msg_handle].timeout_timer);
#endif
 AIF_Set_Msg_Received_Ch0(msg_handle);
}
#endif

#ifdef CAN_CH1_SELECTED
/******************************************************************************
*Prototype: SCH_Rx_Message_Indication_Ch1                                     *
*Arguments passed: msg  handle                                                *
*Return value: none                                                           *
*Functionality:This function is called by VBM after reception of the          *
*corresponding Rx msg on channel 1 to handle timeout monitoring               *
*Since there is one-to-one mapping between Rx table of VBM, Scheduler and AIF,*
*the msg handle can be directly used as index of the table                    *
******************************************************************************/
void SCH_Rx_Message_Indication_Ch1(canuint8_t msg_handle)
{
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
 CAN_TIMER_Start(SCH_Rx_Msg_Timeout_Config_Tables[1][msg_handle].timeout_timer);
#endif
 AIF_Set_Msg_Received_Ch1(msg_handle);
}
#endif

#ifdef CAN_CH2_SELECTED
/******************************************************************************
*Prototype: SCH_Rx_Message_Indication_Ch2                                     *
*Arguments passed: msg  handle                                                *
*Return value: none                                                           *
*Functionality:This function is called by VBM after reception of the          *
*corresponding Rx msg on channel 2 to handle timeout monitoring               *
*Since there is one-to-one mapping between Rx table of VBM, Scheduler and AIF,*
*the msg handle can be directly used as index of the table                    *
******************************************************************************/
void SCH_Rx_Message_Indication_Ch2(canuint8_t msg_handle)
{
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
 CAN_TIMER_Start(SCH_Rx_Msg_Timeout_Config_Tables[2][msg_handle].timeout_timer);
#endif
 AIF_Set_Msg_Received_Ch2(msg_handle);
}
#endif

#ifdef CAN_CH0_SELECTED
/******************************************************************************
*Prototype: SCH_Immediate_Process_Rx_Msg_Ch0                                  *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
void SCH_Immediate_Process_Rx_Msg_Ch0(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;

  for(index = 0; index < Size_Of_Rx_Timeout_Monitor_Tables[0]; index ++)
  {
    if(SCH_Rx_Msg_Timeout_Config_Tables[0][index].timeout_timer == timer_name)
    {
      SCH_Timeout_Notifier_Function_Rx_Msg_Ch0(index);
      break;
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Rx_Msg_Ch0                                           *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
void SCH_Set_Flag_Rx_Msg_Ch0(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;

  for(index = 0; index < Size_Of_Rx_Timeout_Monitor_Tables[0]; index ++)
  {
    if(SCH_Rx_Msg_Timeout_Config_Tables[0][index].timeout_timer == timer_name)
    {
      SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch0(index);
      break;
    }
  }
}

/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Rx_Msg_Ch0                          *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Timeout_Notifier_Function_Rx_Msg_Ch0(canuint8_t msg_handle)
{
  AIF_Set_Rx_Msg_Timeout_Ch0(msg_handle);
}

/******************************************************************************
*Prototype: SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch0                            *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch0(canuint8_t msg_handle)
{
  SCH_Rx_Msg_Timeout_Runtime_Info[0][msg_handle].timeout_timer_expired = cbTRUE;
}
#endif

#ifdef CAN_CH1_SELECTED
/******************************************************************************
*Prototype: SCH_Immediate_Process_Rx_Msg_Ch1                                  *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
void SCH_Immediate_Process_Rx_Msg_Ch1(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;

  for(index = 0; index < Size_Of_Rx_Timeout_Monitor_Tables[1]; index ++)
  {
    if(SCH_Rx_Msg_Timeout_Config_Tables[1][index].timeout_timer == timer_name)
    {
      SCH_Timeout_Notifier_Function_Rx_Msg_Ch1(index);
      break;
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Rx_Msg_Ch1                                           *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
void SCH_Set_Flag_Rx_Msg_Ch1(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;

  for(index = 0; index < Size_Of_Rx_Timeout_Monitor_Tables[1]; index ++)
  {
    if(SCH_Rx_Msg_Timeout_Config_Tables[1][index].timeout_timer == timer_name)
    {
      SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch1(index);
      break;
    }
  }
}

/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Rx_Msg_Ch1                          *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Timeout_Notifier_Function_Rx_Msg_Ch1(canuint8_t msg_handle)
{
  AIF_Set_Rx_Msg_Timeout_Ch1(msg_handle);
}

/******************************************************************************
*Prototype: SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch1                            *
*Arguments passed: none                                                       *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch1(canuint8_t msg_handle)
{
  SCH_Rx_Msg_Timeout_Runtime_Info[1][msg_handle].timeout_timer_expired = cbTRUE;
}
#endif

#ifdef CAN_CH2_SELECTED
/******************************************************************************
*Prototype: SCH_Immediate_Process_Rx_Msg_Ch2                                  *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
void SCH_Immediate_Process_Rx_Msg_Ch2(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;

  for(index = 0; index < Size_Of_Rx_Timeout_Monitor_Tables[2]; index ++)
  {
    if(SCH_Rx_Msg_Timeout_Config_Tables[2][index].timeout_timer == timer_name)
    {
      SCH_Timeout_Notifier_Function_Rx_Msg_Ch2(index);
      break;
    }
  }
}

/******************************************************************************
*Prototype: SCH_Set_Flag_Rx_Msg_Ch2                                           *
*Arguments passed: timer name                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
void SCH_Set_Flag_Rx_Msg_Ch2(CAN_Timer_Names_T timer_name)
{
  canuint8_t index;

  for(index = 0; index < Size_Of_Rx_Timeout_Monitor_Tables[2]; index ++)
  {
    if(SCH_Rx_Msg_Timeout_Config_Tables[2][index].timeout_timer == timer_name)
    {
      SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch2(index);
      break;
    }
  }
}

/******************************************************************************
*Prototype: SCH_Timeout_Notifier_Function_Rx_Msg_Ch2                          *
*Arguments passed: msg handle                                                 *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
******************************************************************************/
static void SCH_Timeout_Notifier_Function_Rx_Msg_Ch2(canuint8_t msg_handle)
{
  AIF_Set_Rx_Msg_Timeout_Ch2(msg_handle);
}

/******************************************************************************
*Prototype: SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch2                            *
*Arguments passed: none                                                       *
*Return value: none                                                           *
*Functionality:This function is called by Timer module once the respective    *
*timer expires                                                                *
*******************************************************************************/
static void SCH_Set_Timeout_Expiry_Flag_Rx_Msg_Ch2(canuint8_t msg_handle)
{
  SCH_Rx_Msg_Timeout_Runtime_Info[2][msg_handle].timeout_timer_expired = cbTRUE;
}
#endif

#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
