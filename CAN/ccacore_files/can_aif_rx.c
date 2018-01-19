/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Sandeep, Prakash                                                 *
 * Project: CCA - AIF                                                        *
 * File Name:  can_aif_rx.c                                                  *
 * File Description:                                                         *
 * This module contains interfaces with the Application and Scheduler        *
 *****************************************************************************/
#include "can_aif_rx.h"
#include "can_sch_rx.h"
#include "can_vbm_rx.h"

typedef struct AIF_Rx_Msg_Info_Tag
{

 #ifdef CCA_HMI
 canbool8_t     Is_Message_Recieved       :1;
 canbool8_t     Timeout_Flag                     :1;
 canbool8_t     Indication_Flag                  :1;
 canbool8_t     NM_Indication_Flag           :1;
 canbool8_t     unused                                :4;
 #else
 canbool8_t      Is_Message_Recieved       :1;
 canbool8_t      Timeout_Flag              :1;
 canbool8_t      Indication_Flag           :1;
 #endif

} AIF_Rx_Msg_Info_T;

//Array of pointers to receive parameter table
const AIF_Rx_Msg_Parameters_T
               *AIF_Rx_Msg_Parameters[NUMBER_OF_CHANNELS_SUPPORTED]=
{
 #ifdef CAN_CH0_SELECTED
 AIF_Rx_Msg_Parameters_Ch0,
 #endif
 #ifdef CAN_CH1_SELECTED
 AIF_Rx_Msg_Parameters_Ch1,
 #endif
 #ifdef CAN_CH2_SELECTED
 AIF_Rx_Msg_Parameters_Ch2
 #endif
};

#ifdef CAN_CH0_SELECTED
AIF_Rx_Msg_Info_T  AIF_Rx_Msg_Info_Ch0[NUMBER_OF_RX_MSG_SUPPORTED_CH0];
#endif

#ifdef CAN_CH1_SELECTED
AIF_Rx_Msg_Info_T  AIF_Rx_Msg_Info_Ch1[NUMBER_OF_RX_MSG_SUPPORTED_CH1];
#endif

#ifdef CAN_CH2_SELECTED
AIF_Rx_Msg_Info_T  AIF_Rx_Msg_Info_Ch2[NUMBER_OF_RX_MSG_SUPPORTED_CH2];
#endif

// Receive message indication and Timeout array
AIF_Rx_Msg_Info_T  *AIF_Rx_Msg_Info[NUMBER_OF_CHANNELS_SUPPORTED]=
{
  #ifdef CAN_CH0_SELECTED
  AIF_Rx_Msg_Info_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  AIF_Rx_Msg_Info_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  AIF_Rx_Msg_Info_Ch2
  #endif
};

static can_boolean_t Aif_Rx_ActiveFlag;

// Static function declaration
 void AIF_Rx_Processing(canuint8_t channel_num);

#ifdef RX_APPLICATION_SIGNAL_INDICATION
static void AIF_Set_Rx_SignalIndsInMsg(canuint8_t channel_num,canuint8_t msg_handle);
static void AIF_Set_Rx_SignalTimeoutsInMsg(canuint8_t channel_num,
                                                           canuint8_t msg_handle);
#endif


#ifdef RX_APPLICATION_SIGNAL_INDICATION
/**********************************************************************
* Function Name:  AIF_Set_Rx_SignalIndsInMsg                          *
* Arguments passed: channel_num,msg_handle                            *
* Return type: void                                                   *
* Functionality: Sets the signal indication flags of a message        *
**********************************************************************/
static void AIF_Set_Rx_SignalIndsInMsg(canuint8_t channel_num,canuint8_t msg_handle)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  canuint8_t byte_index,byte_size;

  Pointer_to_AIF_Rx_Msg_Parameters =
                                &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
  byte_size = Pointer_to_AIF_Rx_Msg_Parameters->Total_Flag_Bytes;
  for( byte_index=0; byte_index< byte_size; byte_index++ )
  {
    Pointer_to_AIF_Rx_Msg_Parameters->AIF_Rx_Sig_Ind_Array[byte_index] = 0xFF;
  }
}

/**********************************************************************
* Function Name:  AIF_Set_Rx_SignalTimeoutsInMsg                      *
* Arguments passed: channel_num,msg_handle                            *
* Return type: void                                                   *
* Functionality: Sets the signal Timeout flags of a message in        *
*                selected channel                                     *
**********************************************************************/
static void AIF_Set_Rx_SignalTimeoutsInMsg(canuint8_t channel_num,
                                                            canuint8_t msg_handle)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  canuint8_t byte_index,byte_size;

  Pointer_to_AIF_Rx_Msg_Parameters =
                                &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
  byte_size = Pointer_to_AIF_Rx_Msg_Parameters->Total_Flag_Bytes;
  for( byte_index=0; byte_index< byte_size; byte_index++ )
  {
   Pointer_to_AIF_Rx_Msg_Parameters->AIF_Rx_Sig_Timeout_Array[byte_index]= 0xFF;
  }
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_AllSignalInds                            *
* Arguments passed: channel_num                                       *
* Return type: void                                                   *
* Functionality: Clears the signal indication flags of all the        *
* messages on selected Channel                                        *
**********************************************************************/
void AIF_Clr_Rx_AllSignalInds(canuint8_t channel_num)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  canuint8_t msg_handle;

  Pointer_to_AIF_Rx_Msg_Parameters = AIF_Rx_Msg_Parameters[channel_num];
  for( msg_handle=0;msg_handle<Size_Of_Receive_Param_Tables[channel_num];
                                                           msg_handle++ )
  {
    if( NULL != Pointer_to_AIF_Rx_Msg_Parameters->Msg_Buffer_Address )
    {
      AIF_Clr_Rx_SignalIndsInMsg( channel_num,msg_handle );
    }
  }
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_SignalIndsInMsg                          *
* Arguments passed: channel_num,msg_handle                            *
* Return type: void                                                   *
* Functionality: Clears the signal indication flags of a message in   *
*                selected channel                                     *
**********************************************************************/
void AIF_Clr_Rx_SignalIndsInMsg(canuint8_t channel_num,canuint8_t msg_handle)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  canuint8_t byte_index,byte_size;

  Pointer_to_AIF_Rx_Msg_Parameters =
                                &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
  byte_size = Pointer_to_AIF_Rx_Msg_Parameters->Total_Flag_Bytes;
  for( byte_index=0; byte_index< byte_size; byte_index++ )
  {
    Pointer_to_AIF_Rx_Msg_Parameters->AIF_Rx_Sig_Ind_Array[byte_index] = 0x00;
  }
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_AllSignalTimeouts                        *
* Arguments passed: channel_num                                       *
* Return type: void                                                   *
* Functionality: Clears the signal indication flags of all the        *
* messages on on selected Channel                                     *
**********************************************************************/
void AIF_Clr_Rx_AllSignalTimeouts(canuint8_t channel_num)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  canuint8_t msg_handle;

  Pointer_to_AIF_Rx_Msg_Parameters = AIF_Rx_Msg_Parameters[channel_num];
  for( msg_handle=0;msg_handle<Size_Of_Receive_Param_Tables[channel_num];
                                                           msg_handle++ )
  {
    if( NULL != Pointer_to_AIF_Rx_Msg_Parameters->Msg_Buffer_Address )
    {
      AIF_Clr_Rx_SignalTimeoutsInMsg( channel_num,msg_handle );
    }
  }
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_SignalTimeoutsInMsg                      *
* Arguments passed: channel_num,msg_handle                            *
* Return type: void                                                   *
* Functionality: Clears the signal indication flags of a message in   *
*                selected channel                                     *
**********************************************************************/
void AIF_Clr_Rx_SignalTimeoutsInMsg(canuint8_t channel_num,canuint8_t msg_handle)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  canuint8_t byte_index,byte_size;

  Pointer_to_AIF_Rx_Msg_Parameters =
                                &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
  byte_size = Pointer_to_AIF_Rx_Msg_Parameters->Total_Flag_Bytes;
  for( byte_index=0; byte_index< byte_size; byte_index++ )
  {
   Pointer_to_AIF_Rx_Msg_Parameters->AIF_Rx_Sig_Timeout_Array[byte_index]= 0x00;
  }
}
#endif

#ifdef CAN_CH0_SELECTED
/**********************************************************************
* Function Name:  AIF_Set_Msg_Received_Ch0                            *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by scheduler to indicate message received to  *
*                AIF                                                  *
**********************************************************************/
void AIF_Set_Msg_Received_Ch0(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch0[msg_handle].Is_Message_Recieved = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_Msg_Ind_Ch0                              *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appln to clear message Indication flag     *
**********************************************************************/
void AIF_Clr_Rx_Msg_Ind_Ch0(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch0[msg_handle].Indication_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_NM_Clr_Rx_Msg_Ind_Ch0                           *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by NM to clear message Indication flag        *
**********************************************************************/
 #ifdef CCA_HMI
void AIF_NM_Clr_Rx_Msg_Ind_Ch0(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch0[msg_handle].NM_Indication_Flag = cbFALSE;
}
#endif
/**********************************************************************
* Function Name:  AIF_Get_Rx_Msg_Ind_Ch0                              *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appln to read message Indication flag      *
**********************************************************************/
canbool8_t AIF_Get_Rx_Msg_Ind_Ch0(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch0[msg_handle].Indication_Flag);

}

/**********************************************************************
* Function Name:  AIF_NM_Get_Rx_Msg_Ind_Ch0                           *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by NM to read message Indication flag         *
**********************************************************************/
 #ifdef CCA_HMI
canbool8_t AIF_NM_Get_Rx_Msg_Ind_Ch0(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch0[msg_handle].NM_Indication_Flag);
}
#endif


/**********************************************************************
* Function Name:  AIF_Set_Rx_Msg_Timeout_Ch0                          *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to set message Timeout flag      *
**********************************************************************/
void AIF_Set_Rx_Msg_Timeout_Ch0(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch0[msg_handle].Timeout_Flag = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_Msg_Timeout_Ch0                          *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appl to clear message Timeout flag         *
**********************************************************************/
void AIF_Clr_Rx_Msg_Timeout_Ch0(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch0[msg_handle].Timeout_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_Msg_Timeout_Ch0                          *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appl to read message Timeout flag          *
**********************************************************************/
canbool8_t AIF_Get_Rx_Msg_Timeout_Ch0(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch0[msg_handle].Timeout_Flag);

}
#endif

#ifdef CAN_CH1_SELECTED
/**********************************************************************
* Function Name:  AIF_Set_Msg_Received_Ch1                            *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to indicate Received message to  *
*                AIF                                                  *
**********************************************************************/
void AIF_Set_Msg_Received_Ch1(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch1[msg_handle].Is_Message_Recieved = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_Msg_Ind_Ch1                              *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appln to clear message Indication flag     *
**********************************************************************/
void AIF_Clr_Rx_Msg_Ind_Ch1(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch1[msg_handle].Indication_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Get_Rx_Msg_Ind_Ch1                              *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appln to read message Indication flag      *
**********************************************************************/
canbool8_t AIF_Get_Rx_Msg_Ind_Ch1(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch1[msg_handle].Indication_Flag);

}

/**********************************************************************
* Function Name:  AIF_Set_Rx_Msg_Timeout_Ch1                          *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to set message Timeout flag      *
**********************************************************************/
void AIF_Set_Rx_Msg_Timeout_Ch1(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch1[msg_handle].Timeout_Flag = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Set_Rx_Msg_Timeout_Ch1                          *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appl to clear message Timeout flag         *
**********************************************************************/
void AIF_Clr_Rx_Msg_Timeout_Ch1(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch1[msg_handle].Timeout_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Get_Rx_Msg_Timeout_Ch1                          *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appl to read message Timeout flag          *
**********************************************************************/
canbool8_t AIF_Get_Rx_Msg_Timeout_Ch1(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch1[msg_handle].Timeout_Flag);

}
#endif

#ifdef CAN_CH2_SELECTED
/**********************************************************************
* Function Name:  AIF_Set_Msg_Received_Ch2                            *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to indicate Received message to  *
*                AIF                                                  *
**********************************************************************/
void AIF_Set_Msg_Received_Ch2(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch2[msg_handle].Is_Message_Recieved = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_Msg_Ind_Ch2                              *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appln to clear message Indication flag     *
**********************************************************************/
void AIF_Clr_Rx_Msg_Ind_Ch2(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch2[msg_handle].Indication_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Get_Rx_Msg_Ind_Ch2                              *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appln to read message Indication flag      *
**********************************************************************/
canbool8_t AIF_Get_Rx_Msg_Ind_Ch2(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch2[msg_handle].Indication_Flag);

}

/**********************************************************************
* Function Name:  AIF_Set_Rx_Msg_Timeout_Ch2                          *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Scheduler to set message Timeout flag      *
**********************************************************************/
void AIF_Set_Rx_Msg_Timeout_Ch2(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch2[msg_handle].Timeout_Flag = cbTRUE;
}

/**********************************************************************
* Function Name:  AIF_Clr_Rx_Msg_Timeout_Ch2                          *
* Arguments passed: msg_handle                                        *
* Return type: void                                                   *
* Functionality: Called by Appl to clear message Timeout flag         *
**********************************************************************/
void AIF_Clr_Rx_Msg_Timeout_Ch2(canuint8_t msg_handle)
{
 AIF_Rx_Msg_Info_Ch2[msg_handle].Timeout_Flag = cbFALSE;
}

/**********************************************************************
* Function Name:  AIF_Get_Rx_Msg_Timeout_Ch2                          *
* Arguments passed: msg_handle                                        *
* Return type: boolean                                                *
* Functionality: Called by Appl to read message Timeout flag          *
**********************************************************************/
canbool8_t AIF_Get_Rx_Msg_Timeout_Ch2(canuint8_t msg_handle)
{
 return(AIF_Rx_Msg_Info_Ch2[msg_handle].Timeout_Flag);

}
#endif

/**********************************************************************
* Function Name : AIF_Set_Rx_Inactive                                 *
* Arguments passed : channel number                                   *
* Return value : None                                                 *
* Functionality : The application calls this API to deactivate        *
* reception on requirred channel                                      *
**********************************************************************/
void AIF_Set_Rx_Inactive(canuint8_t channel_num)
{
  AIF_Rx_Cold_Initialization(channel_num);
  SCH_Set_Rx_Inactive(channel_num);
}

/**********************************************************************
* Function Name : AIF_Set_Rx_Active                                   *
* Arguments passed : channel number                                   *
* Return value : None                                                 *
* Functionality : The application calls this API to activate reception*
* on requirred channel                                               *
**********************************************************************/
void AIF_Set_Rx_Active(canuint8_t channel_num)
{
  Aif_Rx_ActiveFlag = CAN_cbTRUE;
  SCH_Set_Rx_Active(channel_num);
}

/**********************************************************************
* Function Name : AIF_Rx_Cold_Initialization                          *
* Arguments passed : channel_num                                      *
* Return value : None                                                 *
* Functionality : To intialize the AIF reception Flags and buffers    *
**********************************************************************/
void AIF_Rx_Cold_Initialization(canuint8_t channel_num)
{
  canuint8_t msg_handle,byte_index,dlc;
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;

  Aif_Rx_ActiveFlag = CAN_cbFALSE;
  for(msg_handle = 0;msg_handle < Size_Of_Receive_Param_Tables[channel_num];
                                                               msg_handle++)
  {
     // clear message level indication and timeout flags
     AIF_Rx_Msg_Info[channel_num][msg_handle].Is_Message_Recieved = cbFALSE;
     AIF_Rx_Msg_Info[channel_num][msg_handle].Timeout_Flag = cbFALSE;
     AIF_Rx_Msg_Info[channel_num][msg_handle].Indication_Flag = cbFALSE;
     AIF_Rx_Msg_Info[channel_num][msg_handle].NM_Indication_Flag = cbFALSE;

     Pointer_to_AIF_Rx_Msg_Parameters =
                               &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
     // clear the AIF Rx buffers
     if( NULL != Pointer_to_AIF_Rx_Msg_Parameters->Msg_Buffer_Address )
                               // buffer not allocated for diagnostic messages
     {
       dlc = VBM_Get_Rx_Message_DLC_From_Param_Table(channel_num,msg_handle);
       for( byte_index = 0;byte_index<dlc;byte_index++)
       {
          AIF_Rx_Msg_Parameters[channel_num][msg_handle].
                                           Msg_Buffer_Address[byte_index]=0x00;
       }
       #ifdef RX_APPLICATION_SIGNAL_INDICATION
       AIF_Clr_Rx_SignalIndsInMsg(channel_num,msg_handle);
       AIF_Clr_Rx_SignalTimeoutsInMsg(channel_num,msg_handle);
       #endif
     }
  }
}

/**********************************************************************
* Function Name : AIF_Rx_Cold_Initialization                          *
* Arguments passed : channel_num                                      *
* Return value : None                                                 *
* Functionality : To intialize the AIF reception Flags and buffers    *
**********************************************************************/
void AIF_Rx_Cold_Initialization_1(canuint8_t channel_num)
{
  canuint8_t msg_handle,byte_index,dlc;
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;

  for(msg_handle = 0;msg_handle < Size_Of_Receive_Param_Tables[channel_num];
                                                               msg_handle++)
  {
     // clear message level indication and timeout flags
     AIF_Rx_Msg_Info[channel_num][msg_handle].Is_Message_Recieved = cbFALSE;
     AIF_Rx_Msg_Info[channel_num][msg_handle].Timeout_Flag = cbFALSE;
     AIF_Rx_Msg_Info[channel_num][msg_handle].Indication_Flag = cbFALSE;
     AIF_Rx_Msg_Info[channel_num][msg_handle].NM_Indication_Flag = cbFALSE;

     Pointer_to_AIF_Rx_Msg_Parameters =
                               &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
     // clear the AIF Rx buffers
     if( NULL != Pointer_to_AIF_Rx_Msg_Parameters->Msg_Buffer_Address )
                               // buffer not allocated for diagnostic messages
     {
       dlc = VBM_Get_Rx_Message_DLC_From_Param_Table(channel_num,msg_handle);
       for( byte_index = 0;byte_index<dlc;byte_index++)
       {
          AIF_Rx_Msg_Parameters[channel_num][msg_handle].
                                           Msg_Buffer_Address[byte_index]=0x00;
       }
       #ifdef RX_APPLICATION_SIGNAL_INDICATION
       AIF_Clr_Rx_SignalIndsInMsg(channel_num,msg_handle);
       AIF_Clr_Rx_SignalTimeoutsInMsg(channel_num,msg_handle);
       #endif
     }
  }
}

/**********************************************************************
* Function Name : AIF_Rx_Periodic_Task                                *
* Arguments passed :  none                                            *
* Return value : None                                                 *
* Functionality : Called at the periodic rate of the CAN Handler      *
**********************************************************************/
void AIF_Rx_Periodic_Task(void)
{
  #ifdef CAN_CH0_SELECTED
  AIF_Rx_Processing(0);
  #endif

  #ifdef CAN_CH1_SELECTED
  AIF_Rx_Processing(1);
  #endif

  #ifdef CAN_CH2_SELECTED
  AIF_Rx_Processing(2);
  #endif
}

/**********************************************************************
* Function Name : AIF_Rx_Processing                                   *
* Arguments passed :  channel_num                                     *
* Return value : None                                                 *
* Functionality : Called by AIF Rx periodic Task to process the Rx    *
* messages,Indication and Timeout status                              *
**********************************************************************/
void AIF_Rx_Processing(canuint8_t channel_num)
{
  const AIF_Rx_Msg_Parameters_T *Pointer_to_AIF_Rx_Msg_Parameters;
  AIF_Rx_Msg_Info_T *Pointer_to_AIF_Rx_Msg_Info;
  canuint8_t msg_handle;

  if( CAN_cbFALSE != Aif_Rx_ActiveFlag)
  {
    for(msg_handle = 0; msg_handle < Size_Of_Receive_Param_Tables[channel_num];
                                                                  msg_handle++)
    {
      Pointer_to_AIF_Rx_Msg_Parameters =
                               &AIF_Rx_Msg_Parameters[channel_num][msg_handle];
      Pointer_to_AIF_Rx_Msg_Info =
                               &AIF_Rx_Msg_Info[channel_num][msg_handle];

      if( NULL != Pointer_to_AIF_Rx_Msg_Parameters->Msg_Buffer_Address )
      {
        if(cbFALSE==Pointer_to_AIF_Rx_Msg_Info->Timeout_Flag)
        {
          if(cbTRUE== Pointer_to_AIF_Rx_Msg_Info->Is_Message_Recieved)
          {
             // copy received message from VBM buffer to AIF Rx message buffer
                VBM_Get_Rx_Message_Data(channel_num,msg_handle,
                  Pointer_to_AIF_Rx_Msg_Parameters->Msg_Buffer_Address);
                    Pointer_to_AIF_Rx_Msg_Info->Indication_Flag = cbTRUE;
                   Pointer_to_AIF_Rx_Msg_Info->NM_Indication_Flag = cbTRUE;
             Pointer_to_AIF_Rx_Msg_Info->Is_Message_Recieved = cbFALSE;
             #ifdef RX_APPLICATION_SIGNAL_INDICATION
             AIF_Set_Rx_SignalIndsInMsg(channel_num,msg_handle);
             #endif
          }
        }
        #ifdef RX_APPLICATION_SIGNAL_INDICATION
        else
        {
          AIF_Set_Rx_SignalTimeoutsInMsg(channel_num,msg_handle);
        }
        #endif
      }
    }
  }
  else
  {
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
