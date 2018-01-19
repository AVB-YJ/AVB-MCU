/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Sandeep,Prakash                                                  *
 * Project: CCA - AIF                                                        *
 * File Name:  can_aif_tx.c                                                  *
 * File Description:                                                         *
 * This module contains Tx Confirmation,Timeouts and signal handling of the  *
 * message                                                                   *
 *****************************************************************************/

#include "can_aif_tx.h"

typedef struct AIF_Tx_Msg_Info_Tag
{
 #ifdef CCA_HMI
  canbool16_t  Is_Message_Transmitted    :1;
  canbool16_t  Timeout_Flag              :1;
  canbool16_t  Confirmation_Flag         :1;
  canbool16_t  unused                             :13;
  #else
  canbool8_t   Is_Message_Transmitted    :1;
  canbool8_t   Timeout_Flag              :1;
  canbool8_t   Confirmation_Flag         :1;
  #endif
}AIF_Tx_Msg_Info_T;

typedef struct AIF_Tx_Parameter_Index_Tag
{
  canuint8_t start_index;
  canuint8_t end_index;
}AIF_Tx_Parameter_Index_T;

// Transmit message confirmation and Timeout array
AIF_Tx_Msg_Info_T  AIF_Tx_Msg_Info[TOTAL_NUMBER_OF_TX_MSG];

// Static function definition
#ifdef TX_APPLICATION_SIGNAL_CONFIRMATION
 void AIF_Set_Tx_SignalConfsInMsg(canuint8_t msg_handle);
 void AIF_Set_Tx_SignalTimeoutsInMsg(canuint8_t msg_handle);
#endif

 AIF_Tx_Parameter_Index_T*
                       AIF_Calculate_Tx_Parameter_Index(canuint8_t channel_num);
 void AIF_Tx_Clear_Flags_and_Buffers(canuint8_t msg_handle);

  canuint8_t Test[8] = {0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/**********************************************************************
* Function Name:  AIF_Set_Msg_Transmitted                             *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to indicate sucessful message Tx *
*                to AIF                                               *
**********************************************************************/
void AIF_Set_Msg_Transmitted(canuint8_t msg_handle)
{
 AIF_Tx_Msg_Info[msg_handle].Is_Message_Transmitted = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_Msg_Conf                                 *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appl to clear Tx message Confirmation      *
**********************************************************************/
void AIF_Clr_Tx_Msg_Conf(canuint8_t msg_handle)
{
 AIF_Tx_Msg_Info[msg_handle].Confirmation_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Get_Tx_Msg_Conf                                 *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appl to read Tx message Confirmation flag  *
**********************************************************************/
canbool8_t AIF_Get_Tx_Msg_Conf(canuint8_t msg_handle)
{
 return(AIF_Tx_Msg_Info[msg_handle].Confirmation_Flag);
}

/**********************************************************************
* Function Name:  AIF_Set_Tx_Msg_Timeout                              *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to set Tx message Timeout flag   *
**********************************************************************/
void AIF_Set_Tx_Msg_Timeout(canuint8_t msg_handle)
{
 AIF_Tx_Msg_Info[msg_handle].Timeout_Flag = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_Msg_Conf                                 *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appl to clear Tx message Timeout flag      *
**********************************************************************/
void AIF_Clr_Tx_Msg_Timeout(canuint8_t msg_handle)
{
 AIF_Tx_Msg_Info[msg_handle].Timeout_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_Msg_Conf                                 *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appl to read Tx message Timeout flag       *
**********************************************************************/
canbool8_t AIF_Get_Tx_Msg_Timeout(canuint8_t msg_handle)
{
 return(AIF_Tx_Msg_Info[msg_handle].Timeout_Flag);
}

/**********************************************************************
* Function Name:  AIF_Calculate_Tx_Parameter_Index                    *
* Arguments passed: none                                              *
* Return type: AIF_Tx_Parameter_Index_T                               *
* Functionality: Calculate the Start and End index of the parameter   *
* table for the channel                                               *
**********************************************************************/
 AIF_Tx_Parameter_Index_T*
                AIF_Calculate_Tx_Parameter_Index(canuint8_t channel_num)
{
   static AIF_Tx_Parameter_Index_T AIF_Tx_Parameter_Index;
   AIF_Tx_Parameter_Index_T* Pointer_To_Tx_Parameter_Index;

   Pointer_To_Tx_Parameter_Index = &AIF_Tx_Parameter_Index;

   switch(channel_num)
   {
     #ifdef CAN_CH0_SELECTED
     case 0:  Pointer_To_Tx_Parameter_Index->start_index=0;
              Pointer_To_Tx_Parameter_Index->end_index=
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH0;
              break;
     #endif

     #ifdef CAN_CH1_SELECTED
     case 1:  Pointer_To_Tx_Parameter_Index->start_index=
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH0;
              Pointer_To_Tx_Parameter_Index->end_index =
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH0 +
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH1;
              break;
     #endif

     #ifdef CAN_CH2_SELECTED
     case 2:  Pointer_To_Tx_Parameter_Index->start_index=
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH0 +
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH1;
              Pointer_To_Tx_Parameter_Index->end_index =
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH0 +
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH1 +
                                    NUMBER_OF_TX_MSG_SUPPORTED_CH2;
              break;
    #endif

     default: Pointer_To_Tx_Parameter_Index->start_index=0;
              Pointer_To_Tx_Parameter_Index->end_index=0;
   }

   return(Pointer_To_Tx_Parameter_Index);
}

#ifdef TX_APPLICATION_SIGNAL_CONFIRMATION

/**********************************************************************
* Function Name:  AIF_Set_Tx_SignalConfsInMsg                         *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Sets the signal confirmation flags of a message      *
**********************************************************************/
 void AIF_Set_Tx_SignalConfsInMsg(canuint8_t msg_handle)
{
   canuint8_t byte_index,byte_size;

   byte_size = AIF_Tx_Msg_Parameters[msg_handle].Total_Flag_Bytes;
   for( byte_index=0; byte_index< byte_size; byte_index++ )
   {
     AIF_Tx_Msg_Parameters[msg_handle].
                          AIF_Tx_Sig_Conf_Array[byte_index] = 0xFF;
   }
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_AllSignalConf                            *
* Arguments passed: channel num                                       *
* Return type: void                                                   *
* Functionality: Clears the signal confirmation flags of all the      *
* messages on the channel                                             *
**********************************************************************/
void AIF_Clr_Tx_AllSignalConf(canuint8_t channel_num)
{
   canuint8_t msg_handle;
   AIF_Tx_Parameter_Index_T *Pointer_To_Tx_Parameter_Index;

   Pointer_To_Tx_Parameter_Index =
                    AIF_Calculate_Tx_Parameter_Index(channel_num);

   for( msg_handle=Pointer_To_Tx_Parameter_Index->start_index;
        msg_handle<Pointer_To_Tx_Parameter_Index->end_index;
        msg_handle++ )
   {
       if( NULL !=AIF_Tx_Msg_Parameters[msg_handle].Msg_Buffer_Address )
       {
          AIF_Clr_Tx_SignalConfsInMsg( msg_handle );
       }
   }
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_SignalConfsInMsg                         *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Clears the signal confirmation flags of a message    *
**********************************************************************/
void AIF_Clr_Tx_SignalConfsInMsg( canuint8_t msg_handle )
{
   canuint8_t byte_index,byte_size;

   byte_size = AIF_Tx_Msg_Parameters[msg_handle].Total_Flag_Bytes;
   for( byte_index=0; byte_index< byte_size; byte_index++ )
   {
     AIF_Tx_Msg_Parameters[msg_handle].AIF_Tx_Sig_Conf_Array[byte_index]
                                                              = cbFALSE;
   }
}

/**********************************************************************
* Function Name:  AIF_Set_Tx_SignalTimeoutsInMsg                      *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Sets the signal Timeout flags of a message           *
**********************************************************************/
 void AIF_Set_Tx_SignalTimeoutsInMsg( canuint8_t msg_handle )
{
   canuint8_t byte_index,byte_size;

   byte_size = AIF_Tx_Msg_Parameters[msg_handle].Total_Flag_Bytes;
   for( byte_index=0; byte_index< byte_size; byte_index++ )
   {
     AIF_Tx_Msg_Parameters[msg_handle].AIF_Tx_Sig_Timeout_Array[byte_index]
                                                                    = 0xFF;
   }
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_AllSignalTimeouts                        *
* Arguments passed: channel num                                       *
* Return type: void                                                   *
* Functionality: Clears the Timeout flags of all the messages on      *
* the channel                                                         *
**********************************************************************/
void AIF_Clr_Tx_AllSignalTimeouts(canuint8_t channel_num)
{
   canuint8_t msg_handle;
   AIF_Tx_Parameter_Index_T *Pointer_To_Tx_Parameter_Index;

   Pointer_To_Tx_Parameter_Index =
                    AIF_Calculate_Tx_Parameter_Index(channel_num);

   for( msg_handle=Pointer_To_Tx_Parameter_Index->start_index;
        msg_handle<Pointer_To_Tx_Parameter_Index->end_index;
        msg_handle++ )
   {
       if( NULL != AIF_Tx_Msg_Parameters[msg_handle].Msg_Buffer_Address )
       {
          AIF_Clr_Tx_SignalTimeoutsInMsg( msg_handle );
       }
   }
}

/**********************************************************************
* Function Name:  AIF_Clr_Tx_SignalTimeoutsInMsg                      *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Clears the signal Timeout flags of a message         *
**********************************************************************/
void AIF_Clr_Tx_SignalTimeoutsInMsg( canuint8_t msg_handle )
{
   canuint8_t byte_index,byte_size;

   byte_size = AIF_Tx_Msg_Parameters[msg_handle].Total_Flag_Bytes;
   for( byte_index=0; byte_index< byte_size; byte_index++ )
   {
     AIF_Tx_Msg_Parameters[msg_handle].AIF_Tx_Sig_Timeout_Array[byte_index]
                                                                 = cbFALSE;
   }
}

#endif

/**********************************************************************
* Function Name:  AIF_Set_Tx_Inactive                                 *
* Arguments passed: channel number                                    *
* Return type: void                                                   *
* Functionality: This Application calls this API to deactivate        *
* transmission on requirred channel                                   *
**********************************************************************/
void AIF_Set_Tx_Inactive(canuint8_t channel_num)
{
  AIF_Tx_Cold_Initialization(channel_num);
  SCH_Set_Tx_Inactive(channel_num);
}

/**********************************************************************
* Function Name:  AIF_Set_Tx_Active                                   *
* Arguments passed: channel number                                    *
* Return type: void                                                   *
* Functionality: This Application calls this API to activate          *
* transmission on requirred channel                                   *
**********************************************************************/
void AIF_Set_Tx_Active(canuint8_t channel_num)
{
  SCH_Set_Tx_Active(channel_num);
}

/**********************************************************************
* Function Name:  AIF_Disable_Periodic_Tx_Messages                    *
* Arguments passed: channel number                                    *
* Return type: void                                                   *
* Functionality: This Application calls this API to disable           *
* periodic transmission of messages on requirred channel              *
**********************************************************************/
void AIF_Disable_Periodic_Tx_Messages(canuint8_t channel_num)
{
  canuint8_t msg_handle;
  Message_Transmission_Mode_T Msg_type;
  AIF_Tx_Parameter_Index_T *Pointer_To_Tx_Parameter_Index;

  Pointer_To_Tx_Parameter_Index =
                    AIF_Calculate_Tx_Parameter_Index(channel_num);

  for( msg_handle=Pointer_To_Tx_Parameter_Index->start_index;
       msg_handle<Pointer_To_Tx_Parameter_Index->end_index;
       msg_handle++ )
  {
    Msg_type= AIF_Tx_Msg_Parameters[msg_handle].Tx_Message_Type;
    switch(Msg_type)
    {
      #ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
      case CYCLIC_ON_INIT:
      #endif
      #ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
      case CYCLIC_ON_REQUEST:
      #endif
      #ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
      case CYCLIC_AND_ON_EVENT:
      #endif
      #ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
      case CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME:
      #endif
      #ifdef  BAF_MSG_SUPPORTED
      case BAF:
      #endif
      #ifdef  FAST_MSG_SUPPORTED
      case FAST:
      #endif
     /* case CYCLIC_ON_INIT:
      case CYCLIC_ON_REQUEST:
      case CYCLIC_AND_ON_EVENT:
      case CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME:
      case BAF:
      case FAST: Macros defeined in can_sch_config.h*/
                AIF_Tx_Clear_Flags_and_Buffers(msg_handle);
      default : break;
    }
  }
  SCH_Disable_Periodic_Tx_Messages(channel_num);
}

/**********************************************************************
* Function Name:  AIF_Enable_Periodic_Tx_Messages                     *
* Arguments passed: channel number                                    *
* Return type: void                                                   *
* Functionality: This Application calls this API to enable            *
* periodic transmission of messages on requirred channel              *
**********************************************************************/
void AIF_Enable_Periodic_Tx_Messages(canuint8_t channel_num)
{
  SCH_Enable_Periodic_Tx_Messages(channel_num);
}

/**********************************************************************
* Function Name:  AIF_Set_Event                                       *
* Arguments passed: message handle                                    *
* Return type: void                                                   *
* Functionality: This Application calls this API to set the event flag*
* for Event type of messages                                          *
**********************************************************************/
void AIF_Set_Event(canuint8_t msg_handle)
{
  Message_Transmission_Mode_T Msg_type;
  Msg_type = AIF_Tx_Msg_Parameters[msg_handle].Tx_Message_Type;
  SCH_Set_Event_Flag(msg_handle,Msg_type);
}

/**********************************************************************
* Function Name:  AIF_Stop_Tx_Cyclic_On_Init_Msg                      *
* Arguments passed: message handle                                    *
* Return type: void                                                   *
* Functionality:                                                      *
* To be called by Application to stop cyclic on event type of messages*
**********************************************************************/
#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
void AIF_Stop_Tx_Cyclic_On_Init_Msg(canuint8_t msg_handle)
{
  AIF_Tx_Clear_Flags_and_Buffers(msg_handle);
  SCH_Stop_Tx_Cyclic_On_Init_Msg(msg_handle);
}
#endif

/**********************************************************************
* Function Name:  AIF_Set_or_Clr_Req_For_Cyclic_On_Req_Msg            *
* Arguments passed: message handle,request enable                     *
* Return type: void                                                   *
* Functionality: To be called by Application to start/stop cyclic on  *
* request type of messages                                            *
**********************************************************************/
#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
void AIF_Set_or_Clr_Req_For_Cyclic_On_Req_Msg(
                                canuint8_t msg_handle,canbool8_t req_enable)
{
  SCH_Set_or_Clr_Req_For_Cyclic_On_Request_Msg(msg_handle,req_enable);
}
#endif

/**********************************************************************
* Function Name:  AIF_Stop_Tx_Cyclic_And_On_Event_Msg                 *
* Arguments passed: message handle                                    *
* Return type: void                                                   *
* Functionality: To be called by Application to stop cyclic and on    *
* event type of messages                                              *
**********************************************************************/
#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
void AIF_Stop_Tx_Cyclic_And_On_Event_Msg(canuint8_t msg_handle)
{
  AIF_Tx_Clear_Flags_and_Buffers(msg_handle);
  SCH_Stop_Tx_Cyclic_And_On_Event_Msg(msg_handle);
}
#endif

/**********************************************************************
* Function Name:  AIF_Start_Tx_Cyclic_And_On_Event_Msg                 *
* Arguments passed: message handle                                    *
* Return type: void                                                   *
* Functionality: To be called by Application to start cyclic and on    *
* event type of messages                                              *
**********************************************************************/
#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
void AIF_Start_Tx_Cyclic_And_On_Event_Msg(uint8_t msg_handle)
{

     SCH_Start_Tx_Cyclic_And_On_Event_Msg(msg_handle);

}
#endif

/**********************************************************************
* Function Name:AIF_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg*
* Arguments passed: message handle                                    *
* Return type: void                                                   *
* Functionality: To be called by Application to stop cyclic and on    *
* event with min update time type of messages                         *
**********************************************************************/
#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
void AIF_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                     canuint8_t msg_handle)
{
  AIF_Tx_Clear_Flags_and_Buffers(msg_handle);
  SCH_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(msg_handle);
}
#endif

/**********************************************************************
* Function Name:  AIF_Update_Msg_Status_For_BAF_Msg                   *
* Arguments passed: message handle, message ACTIVE/PASSIVE            *
* Return type: void                                                   *
* Functionality: To be called by Application for BAF type of messages *
**********************************************************************/
#ifdef BAF_MSG_SUPPORTED
void AIF_Update_Msg_Status_For_BAF_Msg(canuint8_t msg_handle,canbool8_t msg_active)
{
  SCH_Update_Msg_Status_For_BAF_Msg(msg_handle,msg_active);
}
#endif

/**********************************************************************
* Function Name:  AIF_Update_Msg_Status_For_FAST_Msg                  *
* Arguments passed: message handle, message ACTIVE/PASSIVE            *
* Return type: void                                                   *
* Functionality: To be called by Application for FAST type of messages*
**********************************************************************/
#ifdef FAST_MSG_SUPPORTED
void AIF_Update_Msg_Status_For_FAST_Msg(canuint8_t msg_handle,canbool8_t msg_active)
{
  SCH_Update_Msg_Status_For_FAST_Msg(msg_handle,msg_active);
}
#endif

/**********************************************************************
* Function Name:  AIF_Queue_For_Tx                                    *
* Arguments passed: message handle                                    *
* Return type: void                                                   *
* Functionality: To be called by Scheduler for Transmission of all    *
* of all message types except for "ON_EVENT" message which is handled *
* by AIF                                                              *
**********************************************************************/
void AIF_Queue_For_Tx(canuint8_t msg_handle)
{
  canuint8_t *Pointer_to_Tx_Buffer;
  //Tata Test
  Pointer_to_Tx_Buffer=AIF_Tx_Msg_Parameters[msg_handle].Msg_Buffer_Address;
  VBM_Tx_Message(msg_handle,Pointer_to_Tx_Buffer);


  //VBM_Tx_Message(msg_handle,Test);
}

/**********************************************************************
* Function Name : AIF_Tx_Cold_Initialization                          *
* Arguments passed : channel number                                   *
* Return value : None                                                 *
* Functionality : To intialize the AIF transmit Flags and buffers     *
**********************************************************************/
void AIF_Tx_Cold_Initialization(canuint8_t channel_num)
{
   canuint8_t msg_handle;
   AIF_Tx_Parameter_Index_T *Pointer_To_Tx_Parameter_Index;

   Pointer_To_Tx_Parameter_Index =
                    AIF_Calculate_Tx_Parameter_Index(channel_num);

    for( msg_handle=Pointer_To_Tx_Parameter_Index->start_index;
        msg_handle<Pointer_To_Tx_Parameter_Index->end_index;
        msg_handle++ )
   {
       AIF_Tx_Clear_Flags_and_Buffers(msg_handle);
   }
}

/**********************************************************************
* Function Name : AIF_Tx_Clear_Flags_and_Buffers                      *
* Arguments passed : msg_handle                                       *
* Return value : None                                                 *
* Functionality : Resets transmit Flags and buffers                   *
**********************************************************************/
 void AIF_Tx_Clear_Flags_and_Buffers(canuint8_t msg_handle)
{
   canuint8_t byte_index,dlc;

   // clear message level confirmation and timeout flags
   AIF_Tx_Msg_Info[msg_handle].Is_Message_Transmitted = cbFALSE;
   AIF_Tx_Msg_Info[msg_handle].Confirmation_Flag = cbFALSE;
   AIF_Tx_Msg_Info[msg_handle].Timeout_Flag = cbFALSE;

   if( NULL != AIF_Tx_Msg_Parameters[msg_handle].Msg_Buffer_Address )
   {
      // clear signal level confirmation and timeout flags
      #ifdef TX_APPLICATION_SIGNAL_CONFIRMATION
      AIF_Clr_Tx_SignalConfsInMsg(msg_handle);
      AIF_Clr_Tx_SignalTimeoutsInMsg(msg_handle);
      #endif
      dlc = VBM_Get_Tx_Message_DLC(msg_handle);
      // clear the AIF Tx buffers
      for( byte_index = 0;byte_index<dlc;byte_index++ )
      {
        AIF_Tx_Msg_Parameters[msg_handle].Msg_Buffer_Address[byte_index]=0x00;
      }
   }
}

/**********************************************************************
* Function Name : AIF_Tx_Periodic_Task                                *
* Arguments passed : channel number                                   *
* Return value : None                                                 *
* Functionality : Called at the periodic rate of the CAN Handler      *
**********************************************************************/
void AIF_Tx_Periodic_Task(void)
{
  canuint8_t message_index;
  for(message_index = 0;message_index < TOTAL_NUMBER_OF_TX_MSG;message_index++)
  {
    if( NULL != AIF_Tx_Msg_Parameters[message_index].Msg_Buffer_Address )
                                       // to check functional messages
    {
       if(cbFALSE == AIF_Tx_Msg_Info[message_index].Timeout_Flag)
       {
          if(cbTRUE == AIF_Tx_Msg_Info[message_index].Is_Message_Transmitted)
          {
            AIF_Tx_Msg_Info[message_index].Confirmation_Flag = cbTRUE;
            AIF_Tx_Msg_Info[message_index].Is_Message_Transmitted = cbFALSE;
            #ifdef TX_APPLICATION_SIGNAL_CONFIRMATION
            AIF_Set_Tx_SignalConfsInMsg(message_index);
            #endif
          }
       }
       #ifdef TX_APPLICATION_SIGNAL_CONFIRMATION
       else
       {
         AIF_Set_Tx_SignalTimeoutsInMsg(message_index);
       }
       #endif
    }
  }
}
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
