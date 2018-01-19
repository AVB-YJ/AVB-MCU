/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - VBM                                                        *
 * File Name:  can_vbm_rx.h                                                  *
 * File Description:                                                         *
 * This file contains declarations and prototypes used by can_vbm_rx.c       *
 *****************************************************************************/
#ifndef CAN_VBM_RX_H
#define CAN_VBM_RX_H

#include "can_drv_config.h"
#include "can_vbm_config.h"
#include "can_handler_config.h"
#include "can_handler_datatypes.h"

#define INVALID_REQUEST_RX                                                  0xFF
#define RX_VARIABLE_DLC                                                        9

/*******************************************************************************
 STRUCTURE TEMPLATE AND ARRAY DECLARATIONS FOR RX PARAMETER TABLE
 ******************************************************************************/
typedef enum
{
RX_REALTIME_MESSAGE,
RX_FIFO_MESSAGE
} Rx_message_type_T;

typedef struct VBM_Receive_Msg_Parameter_T
{
   Msg_ID_T message_ID;
   Msg_ID_Type_T Msg_ID_Type;
   canuint8_t message_length_dlc;
   function_pointer_T notifier_function_ptr;
   function_pointer_T notifier_msg_overwritten;
  #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
   Rx_message_type_T Rx_Msg_Type_Realtime_or_FIFO;
   canuint8_t buffer_depth;
  #endif
} VBM_Receive_Msg_Parameter_T;

#ifdef CAN_CH0_SELECTED
extern const VBM_Receive_Msg_Parameter_T VBM_Rx_Msg_Parameter_Table_Ch0[];
extern const canuint8_t Size_of_Rx_Param_Tbl_Ch0;
#endif

#ifdef CAN_CH1_SELECTED
extern const VBM_Receive_Msg_Parameter_T VBM_Rx_Msg_Parameter_Table_Ch1[];
extern const canuint8_t Size_of_Rx_Param_Tbl_Ch1;
#endif

#ifdef CAN_CH2_SELECTED
extern const VBM_Receive_Msg_Parameter_T VBM_Rx_Msg_Parameter_Table_Ch2[];
extern const canuint8_t Size_of_Rx_Param_Tbl_Ch2;
#endif

extern const VBM_Receive_Msg_Parameter_T *VBM_Rx_Msg_Parameter_Tables[];

extern const canuint8_t Size_Of_Receive_Param_Tables[];

/*******************************************************************************
 STRUCTURE TEMPLATE FOR RX RUN TIME TABLE
 ******************************************************************************/
typedef struct
{
   canuint32_t message_ID;
   canuint8_t * data_base_address;
   #ifdef CCA_HMI
   canbool16_t new_message:1;
   #else
   canbool8_t new_message :1;
   #endif
#ifdef FIFO_BUFFERS_NEEDED_FOR_RX
  canuint8_t in_index:  7;
  canuint8_t out_index: 7;
  canbool8_t buffer_status: 1;
#endif
} receive_buffer_T;

typedef enum
{
RX_BUFFER_EMPTY =0,
RX_BUFFER_FULL
}RX_BUFFER_FULL_OR_EMPTY;

typedef enum
{
NO_NEW_MESSAGE_AVAILABLE =0,
NEW_MESSAGE_AVAILABLE
}RX_NEW_MESSAGE_STATUS;

/******************************************************************************
******************      I N I T I A L I Z A T I O N     ***********************
******************************************************************************/
extern void VBM_Cold_Initialization_Rx (canuint8_t channel_num);
extern void VBM_Warm_Initialization_Rx (canuint8_t channel_num);

/******************************************************************************
*************************      R E C E I V E       ****************************
******************************************************************************/
#ifdef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
#define VBM_Get_Rx_Msg_Handle                 VBM_Validate_Rx_Msg_With_Mask
#define VBM_Get_Rx_Msg_Handle_Ch0             VBM_Validate_Rx_Msg_With_Mask_Ch0
#define VBM_Get_Rx_Msg_Handle_Ch1             VBM_Validate_Rx_Msg_With_Mask_Ch1
#define VBM_Get_Rx_Msg_Handle_Ch2             VBM_Validate_Rx_Msg_With_Mask_Ch2
#endif

#ifdef J1939_PROTOCOL_IS_USED
extern canbool8_t VBM_Validate_J1939_Rx_Msg (canuint8_t channel_num, canuint32_t
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc);
#ifdef CAN_CH0_SELECTED
extern canbool8_t VBM_Validate_J1939_Rx_Msg_Ch0(canuint32_t
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc);
#endif
#ifdef CAN_CH1_SELECTED
extern canbool8_t VBM_Validate_J1939_Rx_Msg_Ch1(canuint32_t
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc);
#endif
#ifdef CAN_CH2_SELECTED
extern canbool8_t VBM_Validate_J1939_Rx_Msg_Ch2(canuint32_t
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc);
#endif

#else
extern canuint8_t VBM_Validate_Rx_Msg_With_Mask(canuint8_t channel_num,  Msg_ID_T ID,
              Msg_ID_Type_T ID_Type, canuint8_t dlc);
#ifdef CAN_CH0_SELECTED
extern canuint8_t VBM_Validate_Rx_Msg_With_Mask_Ch0(Msg_ID_T ID,
              Msg_ID_Type_T ID_Type, canuint8_t dlc);
#endif
#ifdef CAN_CH1_SELECTED
extern canuint8_t VBM_Validate_Rx_Msg_With_Mask_Ch1(Msg_ID_T ID,
              Msg_ID_Type_T ID_Type, canuint8_t dlc);
#endif
#ifdef CAN_CH2_SELECTED
extern canuint8_t VBM_Validate_Rx_Msg_With_Mask_Ch2(Msg_ID_T ID,
              Msg_ID_Type_T ID_Type, canuint8_t dlc);
#endif

#endif

extern canbool8_t VBM_Validate_Rx_Msg_With_No_Mask(canuint8_t channel_num,
                                       canuint8_t msg_handle, canuint8_t dlc);
#ifdef CAN_CH0_SELECTED
extern canbool8_t VBM_Validate_Rx_Msg_With_No_Mask_Ch0(
                                       canuint8_t msg_handle, canuint8_t dlc);
#endif
#ifdef CAN_CH1_SELECTED
extern canbool8_t VBM_Validate_Rx_Msg_With_No_Mask_Ch1(
                                       canuint8_t msg_handle, canuint8_t dlc);
#endif
#ifdef CAN_CH2_SELECTED
extern canbool8_t VBM_Validate_Rx_Msg_With_No_Mask_Ch2(
                                       canuint8_t msg_handle, canuint8_t dlc);
#endif

#ifdef  IGNORE_MSG_ID_BITS
extern void VBM_Copy_Rx_Message (canuint8_t channel_num, canuint8_t msg_handle,
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr);
#ifdef CAN_CH0_SELECTED
extern void VBM_Copy_Rx_Message_Ch0 (canuint8_t msg_handle,
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr);
#endif
#ifdef CAN_CH1_SELECTED
extern void VBM_Copy_Rx_Message_Ch1 (canuint8_t msg_handle,
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr);
#endif
#ifdef CAN_CH2_SELECTED
extern void VBM_Copy_Rx_Message_Ch2 (canuint8_t msg_handle,
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr);
#endif

#else
extern void VBM_Copy_Rx_Message (canuint8_t channel_num, canuint8_t msg_handle,
                                 canuint8_t dlc, canuint8_t * hw_data_ptr);
#ifdef CAN_CH0_SELECTED
extern void VBM_Copy_Rx_Message_Ch0 (canuint8_t msg_handle,
                                 canuint8_t dlc, canuint8_t * hw_data_ptr);
#endif
#ifdef CAN_CH1_SELECTED
extern void VBM_Copy_Rx_Message_Ch1 (canuint8_t msg_handle,
                                 canuint8_t dlc, canuint8_t * hw_data_ptr);
#endif
#ifdef CAN_CH2_SELECTED
extern void VBM_Copy_Rx_Message_Ch2 (canuint8_t msg_handle,
                                 canuint8_t dlc, canuint8_t * hw_data_ptr);
#endif

#endif
extern canbool8_t VBM_Is_New_Message_Received (canuint8_t channel_num,
                                            canuint8_t msg_handle);

#ifdef J1939_PROTOCOL_IS_USED
extern Msg_ID_T VBM_Get_J1939_Rx_ID (canuint8_t channel_num, canuint8_t msg_handle);
#else
extern Msg_ID_T VBM_Get_Rx_Message_ID (canuint8_t channel_num,
                                             canuint8_t msg_handle);
extern Msg_ID_Type_T VBM_Get_Rx_Msg_ID_Type(canuint8_t channel_num,
                                      canuint8_t msg_handle);
#endif

#ifdef  IGNORE_MSG_ID_BITS
extern Msg_ID_T VBM_Get_Rx_ID_After_Ignoring_Bits(canuint8_t channel_num,
                                           canuint8_t msg_handle);
#endif

extern canuint8_t VBM_Get_Rx_Message_DLC_From_Param_Table (canuint8_t channel_num,
                                                        canuint8_t msg_handle);

extern canuint8_t VBM_Get_Rx_Message_Variable_DLC (canuint8_t channel_num,
                                                canuint8_t msg_handle);

extern void VBM_Get_Rx_Message_Data(canuint8_t channel_num,
                        canuint8_t msg_handle, canuint8_t* appl_data_pointer);

extern void VBM_Execute_Rx_Notifier_Function(canuint8_t channel_num,
                                              canuint8_t msg_handle);
#ifdef CAN_CH0_SELECTED
extern void VBM_Execute_Rx_Notifier_Function_Ch0(
                                              canuint8_t msg_handle);
#endif
#ifdef CAN_CH1_SELECTED
extern void VBM_Execute_Rx_Notifier_Function_Ch1(
                                              canuint8_t msg_handle);
#endif
#ifdef CAN_CH2_SELECTED
extern void VBM_Execute_Rx_Notifier_Function_Ch2(
                                              canuint8_t msg_handle);
#endif

#ifndef J1939_PROTOCOL_IS_USED

extern canuint8_t VBM_Get_Rx_Msg_Handle_From_Message_ID (canuint8_t channel_num,
                                              Msg_ID_T ID_passed);

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
