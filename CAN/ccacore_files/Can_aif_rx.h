/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Sandeep,Prakash                                                  *
 * Project: CCA - AIF                                                        *
 * File Name:  can_aif_rx.h                                                  *
 * File Description:                                                         *
 * This module contains AIF Rx interfaces with the Application and           *
 * CAN Handler                                                               *
 *****************************************************************************/
#ifndef CAN_AIF_RX_H
#define CAN_AIF_RX_H

#include "can_aif_config.h"
#include "can_handler_datatypes.h"

typedef struct AIF_Rx_Msg_Parameters_Tag
{
 canuint8_t      *Msg_Buffer_Address;
 #ifdef RX_APPLICATION_SIGNAL_INDICATION
 canuint8_t   *AIF_Rx_Sig_Ind_Array;
 canuint8_t   *AIF_Rx_Sig_Timeout_Array;
 canuint8_t   Total_Flag_Bytes;
 #endif
}AIF_Rx_Msg_Parameters_T;

/**********************************************************************
*                  API's requirred for CAN Handler                    *
**********************************************************************/
extern void AIF_Rx_Cold_Initialization(canuint8_t channel_num);
extern void AIF_Rx_Cold_Initialization_1(canuint8_t channel_num);

extern void AIF_Rx_Periodic_Task(void);

/**********************************************************************
*                  API's requirred for application                    *
**********************************************************************/
extern void AIF_Set_Rx_Inactive(canuint8_t channel_num);
extern void AIF_Set_Rx_Active(canuint8_t channel_num);

#ifdef RX_APPLICATION_SIGNAL_INDICATION
extern void AIF_Clr_Rx_AllSignalInds(canuint8_t channel_num);
extern void AIF_Clr_Rx_SignalIndsInMsg(canuint8_t channel_num,canuint8_t msg_handle);
extern void AIF_Clr_Rx_AllSignalTimeouts(canuint8_t channel_num);
extern void AIF_Clr_Rx_SignalTimeoutsInMsg(canuint8_t channel_num,
                                                           canuint8_t msg_handle);
#endif

#ifdef CAN_CH0_SELECTED
/* Receive message PARAMETER TABLE */
extern const AIF_Rx_Msg_Parameters_T
              AIF_Rx_Msg_Parameters_Ch0[NUMBER_OF_RX_MSG_SUPPORTED_CH0];

/**********************************************************************
* API's requirred for Application                                     *
**********************************************************************/
extern void AIF_Clr_Rx_Msg_Ind_Ch0(canuint8_t msg_handle);
 #ifdef CCA_HMI
extern void AIF_NM_Clr_Rx_Msg_Ind_Ch0(canuint8_t msg_handle);
#endif
extern void AIF_Clr_Rx_Msg_Timeout_Ch0(canuint8_t msg_handle);

extern canbool8_t AIF_Get_Rx_Msg_Ind_Ch0(canuint8_t msg_handle);
 #ifdef CCA_HMI
extern canbool8_t AIF_NM_Get_Rx_Msg_Ind_Ch0(canuint8_t msg_handle);
#endif
extern canbool8_t AIF_Get_Rx_Msg_Timeout_Ch0(canuint8_t msg_handle);

/**********************************************************************
* API's requirred for Scheduler                                       *
**********************************************************************/
extern void AIF_Set_Msg_Received_Ch0(canuint8_t msg_handle);
extern void AIF_Set_Rx_Msg_Timeout_Ch0(canuint8_t msg_handle);

#endif

#ifdef CAN_CH1_SELECTED
extern const AIF_Rx_Msg_Parameters_T
              AIF_Rx_Msg_Parameters_Ch1[NUMBER_OF_RX_MSG_SUPPORTED_CH1];

/**********************************************************************
* API's requirred for Application                                     *
**********************************************************************/
void AIF_Clr_Rx_Msg_Ind_Ch1(canuint8_t msg_handle);
canuint8_t AIF_Get_Rx_Msg_Ind_Ch1(canuint8_t msg_handle);
void AIF_Clr_Rx_Msg_Timeout_Ch1(canuint8_t msg_handle);
canuint8_t AIF_Get_Rx_Msg_Timeout_Ch1(canuint8_t msg_handle);

/**********************************************************************
* API's requirred for Scheduler                                       *
**********************************************************************/
extern void AIF_Set_Msg_Received_Ch1(canuint8_t msg_handle);
extern void AIF_Set_Rx_Msg_Timeout_Ch1(canuint8_t msg_handle);
#endif

#ifdef CAN_CH2_SELECTED
extern const AIF_Rx_Msg_Parameters_T
              AIF_Rx_Msg_Parameters_Ch2[NUMBER_OF_RX_MSG_SUPPORTED_CH2];

/**********************************************************************
* API's requirred for Application                                     *
**********************************************************************/
void AIF_Clr_Rx_Msg_Ind_Ch2(canuint8_t msg_handle);
void AIF_Get_Rx_Msg_Ind_Ch2(canuint8_t msg_handle);
void AIF_Clr_Rx_Msg_Timeout_Ch2(canuint8_t msg_handle);
void AIF_Get_Rx_Msg_Timeout_Ch2(canuint8_t msg_handle);

/**********************************************************************
* API's requirred for Scheduler                                       *
**********************************************************************/
extern void AIF_Set_Msg_Received_Ch2(canuint8_t msg_handle);
extern void AIF_Set_Rx_Msg_Timeout_Ch2(canuint8_t msg_handle);

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
