/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - VBM                                                        *
 * File Name:  can_vbm_tx.h                                                  *
 * File Description:                                                         *
 * This file contains declarations and prototypes used by can_vbm_tx.c       *
 *****************************************************************************/
#ifndef CAN_VBM_TX_H
#define CAN_VBM_TX_H

#include "can_vbm_config.h"

#include "can_handler_datatypes.h"

#define INVALID_REQUEST_TX                                                  0xFF
#define TX_VARIABLE_DLC                                                        9

#define TOTAL_NUMBER_OF_TX_MSG   ( NUMBER_OF_TX_MSG_SUPPORTED_CH0 +\
                                   NUMBER_OF_TX_MSG_SUPPORTED_CH1 +\
                                   NUMBER_OF_TX_MSG_SUPPORTED_CH2 )

/*******************************************************************************
 STRUCTURE TEMPLATE AND ARRAY DECLARATIONS FOR TX PARAMETER TABLE
 ******************************************************************************/
typedef enum
{
TX_REALTIME_MESSAGE,
TX_FIFO_MESSAGE
} Tx_Msg_Type_T;

typedef struct VBM_Transmit_Message_Parameter_T
{
   canuint8_t channel_number;
  Msg_ID_T message_ID;
  Msg_ID_Type_T message_ID_Type;
   canuint8_t message_length_dlc;
   function_pointer_T notifier_function_ptr;
  #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
   Tx_Msg_Type_T Tx_Msg_Type_Realtime_or_FIFO;
   canuint8_t buffer_depth;
  #endif
} VBM_Transmit_Msg_Parameter_T;

extern const VBM_Transmit_Msg_Parameter_T VBM_Tx_Msg_Parameter_Table[];
extern const canuint8_t Size_Of_Transmit_Param_Table;

/*******************************************************************************
 STRUCTURE TEMPLATE FOR TX RUN TIME TABLE
 ******************************************************************************/
typedef struct
{
  canuint32_t message_ID;
  canuint8_t * data_base_address;
#ifdef FIFO_BUFFERS_NEEDED_FOR_TX
   canuint8_t in_index:7;
   canuint8_t out_index:7;
   canbool8_t buffer_status:1;
#endif
   #ifdef CCA_HMI
   canbool16_t message_pending : 1;
   #else
   canbool8_t message_pending  : 1;
   #endif
   #ifdef CCA_HMI
   canbool16_t partially_offline : 1;
   #else
   canbool8_t partially_offline  : 1;
   #endif
} transmit_buffer_T;

typedef enum
{
TX_BUFFER_NOT_FULL =0,
TX_BUFFER_FULL
}TX_BUFFER_FULL_OR_EMPTY;

typedef enum
{
NO_NEW_MESSAGE_PENDING =0,
NEW_MESSAGE_PENDING
}TX_MESSAGE_PENDING;

typedef enum
{
PARTIALLY_NOT_OFFLINE =0,
PARTIALLY_OFFLINE
}PARTIALLY_OFFLINE_STATUS;

/*******************************************************************************
******************      I N I T I A L I Z A T I O N     ***********************
*******************************************************************************/
extern void VBM_Cold_Initialization_Tx (canuint8_t channel_num);
extern void VBM_Warm_Initialization_Tx (canuint8_t channel_num);

/*******************************************************************************
*************************     T R A N S M I T      ****************************
*******************************************************************************/
#ifndef J1939_PROTOCOL_IS_USED
extern canuint8_t VBM_Get_Tx_Msg_Handle_From_Message_ID (canuint8_t channel_num,
                                                    Msg_ID_T Message_ID);
#endif
extern canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending(canuint8_t channel_num);
#ifdef CAN_CH0_SELECTED
extern canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch0(void);
#endif
#ifdef CAN_CH1_SELECTED
extern canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch1(void);
#endif
#ifdef CAN_CH2_SELECTED
extern canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch2(void);
#endif

extern void VBM_Execute_Tx_Notifier_Functions(canuint8_t channel_num);
#ifdef CAN_CH0_SELECTED
extern void VBM_Execute_Tx_Notifier_Functions_Ch0(void);
#endif
#ifdef CAN_CH1_SELECTED
extern void VBM_Execute_Tx_Notifier_Functions_Ch1(void);
#endif
#ifdef CAN_CH2_SELECTED
extern void VBM_Execute_Tx_Notifier_Functions_Ch2(void);
#endif

extern void VBM_Update_Tx_Msg_Handle_Info(canuint8_t channel_num,
                                          canuint8_t tx_message_handle);

extern canuint8_t VBM_Get_Tx_Channel_num_From_Msg_Handle(
                                        canuint8_t tx_message_handle);
extern canbool8_t VBM_Set_Tx_Message_DLC(canuint8_t msg_handle, canuint8_t dlc);
extern void VBM_Set_Partial_Offline_Mode (canuint8_t msg_handle);
extern void VBM_Clear_Partial_Offline_Mode (canuint8_t msg_handle);
//#ifdef J1939_PROTOCOL_IS_USED
//extern canbool8_t VBM_Tx_J1939_Message (canuint8_t msg_handle, canuint32_t msg_ID,
//                                                 canuint8_t *appl_data_ptr);
//#else
extern canbool8_t VBM_Tx_Message (canuint8_t msg_handle, canuint8_t * message_address);
extern canuint8_t* VBM_Get_Tx_Buffer_Address_For_Appl(canuint8_t msg_handle);
extern canbool8_t VBM_Tx_Request(canuint8_t msg_handle);
//#endif

extern canuint8_t* VBM_Get_Tx_Buffer_Address_For_Driver(canuint8_t msg_handle);
extern Msg_ID_T VBM_Get_Tx_Message_ID(canuint8_t msg_handle);
extern Msg_ID_Type_T VBM_Get_Tx_Message_ID_Type(canuint8_t msg_handle);
extern canuint8_t VBM_Get_Tx_Message_DLC(canuint8_t msg_handle);
extern void VBM_Tx_Message_Loaded (canuint8_t msg_handle);
extern void VBM_Set_Msg_Pending(canuint8_t msg_handle);
extern canbool8_t VBM_Check_if_All_Mess_Are_Pending_Ch0(void);
#ifdef CHECK_PENDING_Tx_MSGS_FOR_SLEEP_STATE
Boolean_Returnvalue_T VBM_Is_Any_Message_Pending(canuint8_t channel_number);
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
