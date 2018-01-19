/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Sandeep,Prakash                                                  *
 * Project: CCA - AIF                                                        *
 * File Name:  can_aif_tx.h                                                  *
 * File Description:                                                         *
 * This module contains Transmit interfaces with the Application,Scheduler   *
 * and CAN Handler                                                           *
 *****************************************************************************/
#ifndef CAN_AIF_TX_H
#define CAN_AIF_TX_H

#include "can_aif_config.h"
#include "can_sch_tx.h"
#include "can_vbm_tx.h"

typedef struct AIF_Tx_Msg_Parameters_Tag
{
  Message_Transmission_Mode_T    Tx_Message_Type;
  canuint8_t                        *Msg_Buffer_Address;
  //const canuint8_t               *Msg_Default_Values;
  #ifdef TX_APPLICATION_SIGNAL_CONFIRMATION
  canuint8_t   *AIF_Tx_Sig_Conf_Array;
  canuint8_t   *AIF_Tx_Sig_Timeout_Array;
  canuint8_t   Total_Flag_Bytes;
  #endif

}AIF_Tx_Msg_Parameters_T;

/* Transmit message PARAMETER TABLE */
extern const AIF_Tx_Msg_Parameters_T AIF_Tx_Msg_Parameters[TOTAL_NUMBER_OF_TX_MSG];

/**********************************************************************
*                  API's requirred for CAN Handler                    *
**********************************************************************/
extern void AIF_Tx_Cold_Initialization(canuint8_t channel_num);
extern void AIF_Tx_Periodic_Task(void);

/**********************************************************************
* API's requirred for Application                                     *
**********************************************************************/
extern void AIF_Set_Tx_Inactive(canuint8_t channel_num);
extern void AIF_Set_Tx_Active(canuint8_t channel_num);
extern void AIF_Set_Event(canuint8_t msg_handle);
extern void AIF_Disable_Periodic_Tx_Messages(canuint8_t channel_num);
extern void AIF_Enable_Periodic_Tx_Messages(canuint8_t channel_num);

extern void AIF_Clr_Tx_Msg_Conf(canuint8_t msg_handle);
extern void AIF_Clr_Tx_Msg_Timeout(canuint8_t msg_handle);
extern canbool8_t AIF_Get_Tx_Msg_Conf(canuint8_t msg_handle);
extern canbool8_t AIF_Get_Tx_Msg_Timeout(canuint8_t msg_handle);

#ifdef TX_APPLICATION_SIGNAL_CONFIRMATION
extern void AIF_Clr_Tx_AllSignalConf(canuint8_t channel_num);
extern void AIF_Clr_Tx_SignalConfsInMsg(canuint8_t msg_handle);
extern void AIF_Clr_Tx_AllTimeouts(canuint8_t channel_num);
extern void AIF_Clr_Tx_SignalTimeoutsInMsg( canuint8_t msg_handle );
#endif

/**********************************************************************
*                  API's requirred for SCHEDULER                      *
**********************************************************************/

extern void AIF_Queue_For_Tx(canuint8_t msg_handle);
extern void AIF_Set_Msg_Transmitted(canuint8_t msg_handle);
extern void AIF_Set_Tx_Msg_Timeout(canuint8_t msg_handle);

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
extern void AIF_Stop_Tx_Cyclic_On_Init_Msg(canuint8_t msg_handle);
#endif

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
extern void AIF_Set_or_Clr_Req_For_Cyclic_On_Req_Msg(
                                      canuint8_t msg_handle,canbool8_t req_enable);
#endif

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
extern void AIF_Stop_Tx_Cyclic_And_On_Event_Msg(canuint8_t msg_handle);
extern void AIF_Start_Tx_Cyclic_And_On_Event_Msg(uint8_t msg_handle);
#endif

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
extern void AIF_Stop_Tx_Cyclic_And_On_Event_With_Min_Update_Time_Msg(
                                                        canuint8_t msg_handle);
#endif

#ifdef BAF_MSG_SUPPORTED
extern void AIF_Update_Msg_Status_For_BAF_Msg(
                                      canuint8_t msg_handle,canbool8_t msg_active);
#endif

#ifdef FAST_MSG_SUPPORTED
extern void AIF_Update_Msg_Status_For_FAST_Msg(
                                      canuint8_t msg_handle,canbool8_t msg_active);
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
