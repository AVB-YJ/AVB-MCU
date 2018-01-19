/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - Driver                                                     *
 * File Name:  can_drv_tx_rx.h                                               *
 * File Description:                                                         *
 * This file contains function ptrototypes and structure templates           *
 * related to CAN message transmission and CAN message reception             *
 *****************************************************************************/
#ifndef CAN_DRV_TX_RX_H
#define CAN_DRV_TX_RX_H

#include "can_drv_config.h"

/*******************************************************************************
*                       TYPE DEFINITIONS                                       *
*******************************************************************************/
#define INVALID_RECEIVE_MESSAGE_CODE                                        0xFF

extern volatile unsigned char temp_stop_rx;

typedef enum
{
   TRANSMIT_FAILURE,
   TRANSMIT_SUCCESS
}Transmit_Result_T;

typedef struct Transmitted_Msg_Info_Type
{
   canuint8_t tx_msg_handle;
   Transmit_Result_T transmit_result;

}Transmitted_Msg_Info_T;


typedef struct Tx_Pending_Msg_Info_Type
{
   canuint8_t handle_for_pending_tx_msg;
   canuint8_t * tx_data_ptr;
}Tx_Pending_Msg_Info_T;

typedef struct Virtual_RX_Buffer_Info_Type
{
   canuint8_t rx_message_handle;
   canuint8_t * rx_data_ptr;

}Virtual_RX_Buffer_Info_T;

#ifdef CAN_COMMON_VECTOR

typedef struct CAN_ISR_table_Tag
{
 function_pointer_T isr;
 Interrupt_Type_T interrupt_type;
}CAN_ISR_Table_T;

#endif

#ifdef  IGNORE_MSG_ID_BITS  

typedef struct  Bit_Ignore_Patterns_Tag
{
#ifdef MESSAGE_ID_TYPE_MIXED
   canuint16_t do_not_care_bit_pattern_for_standard_id;
   canuint32_t do_not_care_bit_pattern_for_extended_id;
#else
   #ifdef MESSAGE_ID_TYPE_STANDARD
   canuint16_t do_not_care_bit_pattern_for_standard_id;
   #endif
   #ifdef MESSAGE_ID_TYPE_EXTENDED
   canuint32_t do_not_care_bit_pattern_for_extended_id;
   #endif
#endif
}Bit_Ignore_Patterns_T;

#endif

#ifdef CAN_COMMON_VECTOR

extern const CAN_ISR_Table_T CAN_ISR_Table[NUMBER_OF_INTERRUPTS_SUPPORTED]
                                          [NUMBER_OF_CHANNELS_SUPPORTED];
#endif


/*******************************************************************************
*              EXTERN FUNCTION DECLARATIONS  FOR CAN HANDLER                   *
*******************************************************************************/
#ifdef CAN_COMMON_VECTOR

#ifdef CAN_CH0_SELECTED
extern CAN_INTERRUPT_0 void CD_ISR_Channel_0(void);
#endif

#ifdef CAN_CH1_SELECTED
extern CAN_INTERRUPT_1 void CD_ISR_Channel_1(void);
#endif

#ifdef CAN_CH2_SELECTED
extern CAN_INTERRUPT_2 void CD_ISR_Channel_2(void);
#endif

#endif

#ifdef TRANSMIT_INTERRUPT_MODE
#ifdef CAN_CH0_SELECTED
extern CAN_INTERRUPT_TRANSMIT_0 void CD_Transmit_ISR_Channel_0(void);
#endif

#ifdef CAN_CH1_SELECTED
extern CAN_INTERRUPT_TRANSMIT_1 void CD_Transmit_ISR_Channel_1(void);
#endif

#ifdef CAN_CH2_SELECTED
extern CAN_INTERRUPT_TRANSMIT_2 void CD_Transmit_ISR_Channel_2(void);
#endif

#endif

#ifdef RECEIVE_INTERRUPT_MODE

#ifdef CAN_CH0_SELECTED
extern /*CAN_INTERRUPT_RECEIVE_0*/ void CD_Receive_ISR_Channel_0(void);
#endif

#ifdef CAN_CH1_SELECTED
extern CAN_INTERRUPT_RECEIVE_1 void CD_Receive_ISR_Channel_1(void);
#endif

#ifdef CAN_CH2_SELECTED
extern CAN_INTERRUPT_RECEIVE_2 void CD_Receive_ISR_Channel_2(void);
#endif

#endif

extern canbool8_t CD_Tx_Message(canuint8_t channel_number, 
                                canuint8_t tx_message_handle, canuint8_t *data_ptr);
extern void CD_Clear_Transmit_Status(canuint8_t channel_number);
extern void CD_Clear_Receive_Status(canuint8_t channel_number);

#ifdef  IGNORE_MSG_ID_BITS  

extern Msg_ID_T Get_Rx_ID_After_Ignoring_Bits(Msg_ID_T rx_msg_id, Msg_ID_Type_T
                rx_msg_id_type);
#endif
 
/*******************************************************************************
*          EXTERN FUNCTION DECLARATIONS FOR APPLICATION                       *
*******************************************************************************/
#ifndef TRANSMIT_INTERRUPT_MODE
extern Boolean_Returnvalue_T CD_Poll_Transmit_Success(canuint8_t channel_number);
#endif

#ifndef RECEIVE_INTERRUPT_MODE
extern void CD_Poll_Received_Messages(canuint8_t channel_number);
#endif

/*******************************************************************************
*          EXTERN FUNCTION DECLARATIONS FOR APPLICATION/NM                     *
*******************************************************************************/
extern canbool8_t CD_Get_Transmit_Status(canuint8_t channel_number);
extern canbool8_t CD_Get_Receive_Status(canuint8_t channel_number);


#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
