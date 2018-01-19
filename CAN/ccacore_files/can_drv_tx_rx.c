/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - Driver                                                     *
 * File Name:  can_drv_tx_rx.c                                               *
 * File Description:                                                         *
 * This file contains routines for transission and reception of a message    *
 *****************************************************************************/

/*******************************************************************************
*                           Header File Inclusions                             *
*******************************************************************************/
//#include "config.h"
#include "Std_Types.h"
#include "can_drv_tx_rx.h"
#include "can_drv_init_misc.h"
#include "can_drv_config.h"
#include "can_vbm_rx.h"
#include "can_vbm_tx.h"
#include "can_handler_config.h"
#include "can_handler_appl_notifier_functions.h"
#include "ivn_faw_nm.h"
#include "hwcan_tx_rx_nec_v850.h"

/*******************************************************************************
*                            LOCAL MACRO DEFINITIONS                           *
*******************************************************************************/
#define NUMBER_OF_HW_TX_BUF_PER_CHANNEL                                       1
#define MSG_NOT_PENDING                                                    0xFF

typedef enum
{
 CAN_ISR_OFF=0,
 CAN_ISR_ON
}CAN_ISR_State_T;
/*******************************************************************************
*                            STATIC FUNCTION DECLARATIONS                      *
*******************************************************************************/
 canuint8_t Is_Message_Valid(canuint8_t channel_number, canuint8_t hw_rx_buf,
          Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc);
#ifdef CAN_CH0_SELECTED
 canuint8_t Is_Message_Valid_Ch0(canuint8_t hw_rx_buf,
          Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc);
#endif
#ifdef CAN_CH1_SELECTED
 canuint8_t Is_Message_Valid_Ch1(canuint8_t hw_rx_buf,
          Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc);
#endif
#ifdef CAN_CH2_SELECTED
 canuint8_t Is_Message_Valid_Ch2(canuint8_t hw_rx_buf,
          Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc);
#endif
/*******************************************************************************
*                       STATIC VARIABLE DECLARATIONS                           *
*******************************************************************************/
#ifndef TRANSMIT_INTERRUPT_MODE
static canuint8_t Transmit_Message_Is_Loaded[NUMBER_OF_CHANNELS_SUPPORTED];
#endif

static canbool8_t CD_Transmit_Status[NUMBER_OF_CHANNELS_SUPPORTED];
static canbool8_t CD_Receive_Status[NUMBER_OF_CHANNELS_SUPPORTED];
static canbool8_t CAN_Tx_ISR_Status[NUMBER_OF_CHANNELS_SUPPORTED];

 void CD_Transmit_ISR(canuint8_t channel_number);
#ifdef RECEIVE_INTERRUPT_MODE
 void CD_Receive_ISR(canuint8_t channel_number);
#else
 void CD_Receive_Poll(canuint8_t channel_number, RX_Msg_Info_T *rx_msg_info);
#endif

volatile uint8 temp_stop_rx;

/*******************************************************************************
*                    START OF TRANSMISSION                                     *
*******************************************************************************/

/*******************************************************************************
 * Function Name : CD_Transmit_Message                                         *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *                N - Number of maximum channels present in the CAN controller *
 *                tx_message_handle -  index of the transmit message in the    *
 *                transmit message paramater table                             *
 *                data_ptr - a pointer to teh transmit dat array               *
 * Return Value : Transmit result, TRANSMIT_FAILURE - Transmission is failed   *
 *                                 TRANSMIT_SUCCESS - Transmission is success  *
 * Description :This function is an API that is used to transmit a CAN message *
 *              over the CAN bus.                                              *
 ******************************************************************************/
canbool8_t CD_Tx_Message(canuint8_t channel_number, canuint8_t tx_message_handle,
                                           canuint8_t *data_ptr)
{
   Msg_ID_T tx_msg_id;
   Msg_ID_Type_T tx_msg_id_type;
   canuint8_t tx_msg_dlc;
   canbool8_t tx_status, Load_CAN_Msg_Obj;
   //static canuint8_t data[8] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

    tx_status =  TRANSMIT_FAILURE;


   if(CAN_ISR_OFF == CAN_Tx_ISR_Status[channel_number])
   {
      Load_CAN_Msg_Obj = CAN_cbFALSE;

      if((cbTRUE == HWCAN_Is_Tx_Buffer_Available(channel_number)) &&
        (MSG_NOT_PENDING == VBM_Get_Next_Tx_Msg_Num_If_Pending(channel_number)))
      {
         Load_CAN_Msg_Obj = CAN_cbTRUE;
      }
   }
   else
   {
      Load_CAN_Msg_Obj = CAN_cbTRUE;
   }
   if (CAN_cbTRUE == Load_CAN_Msg_Obj)
   {
      tx_msg_id = VBM_Get_Tx_Message_ID(tx_message_handle);
      tx_msg_id_type = VBM_Get_Tx_Message_ID_Type(tx_message_handle);
      tx_msg_dlc = VBM_Get_Tx_Message_DLC(tx_message_handle);

      HWCAN_Load_Tx_ID(channel_number, tx_msg_id_type, tx_msg_id);

      HWCAN_Load_Tx_Data(channel_number, tx_msg_dlc, data_ptr);
        
      VBM_Update_Tx_Msg_Handle_Info(channel_number,tx_message_handle);

      HWCAN_Initiate_Transmission(channel_number);

      #ifndef TRANSMIT_INTERRUPT_MODE
      Transmit_Message_Is_Loaded[channel_number] = CAN_cbTRUE;
      #endif
      tx_status =  TRANSMIT_SUCCESS;
   }
   
   return(tx_status);
}



#ifndef TRANSMIT_INTERRUPT_MODE
/*******************************************************************************
 * Function Name : CD_Transmit_ISR                                             *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *                N - Number of maximum channels present in the CAN controller *
 * Return Value : None                                                         *
 * Description : This function shall be called by CD_Transmit_ISR_Channel_n()  *
 * function, which is the interrupt service routine for CAN transmit interrupt *
 * for channel 'n'. This function can also be called by the user application   *
 * when the application wants to poll for transmit confirmation (when          *
 * transmit interrupt is not enabled).                                         *
 ******************************************************************************/
 void CD_Transmit_ISR(canuint8_t channel_number)
{

   canuint8_t msg_handle;
   canuint8_t *tx_msg_ptr;

   CAN_Tx_ISR_Status[channel_number] = CAN_ISR_ON;
   CD_Transmit_Status[channel_number] = CAN_cbTRUE;

   HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt(channel_number);

   VBM_Execute_Tx_Notifier_Functions(channel_number);

   msg_handle = VBM_Get_Next_Tx_Msg_Num_If_Pending(channel_number);

   if(MSG_NOT_PENDING != msg_handle)
   {
      tx_msg_ptr = VBM_Get_Tx_Buffer_Address_For_Driver(msg_handle);
      (void)CD_Tx_Message(channel_number, msg_handle, tx_msg_ptr);
      VBM_Tx_Message_Loaded(msg_handle);
   }

   CAN_Tx_ISR_Status[channel_number] = CAN_ISR_OFF;
}
#endif

#ifdef TRANSMIT_INTERRUPT_MODE
#ifdef CAN_CH0_SELECTED
/*******************************************************************************
 * Function Name : CD_Transmit_ISR_Channel_0                                   *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN transmit   *
 * interrupt for channel '0'.                                                  *
 ******************************************************************************/
//sg #pragma interrupt INTC0TRX CD_Transmit_ISR_Channel_0



CAN_INTERRUPT_TRANSMIT_0 void CD_Transmit_ISR_Channel_0(void)
{
   canuint8_t msg_handle;
   canuint8_t *tx_msg_ptr;

    
   #if 0
   //Isr time testing
   unsigned int *address;

   CAN_Handler_Disable_Global_Interrupts();
   address = (unsigned int *) 0xFFC4;
   *address = (unsigned int)(*address & ~0x400);
   #endif
   Tx_Passive_Err_Detected=false;
   //Performing_Ack_Recovery = false;
   CAN_Tx_ISR_Status[0]  = CAN_ISR_ON;
   CD_Transmit_Status[0] = CAN_cbTRUE;


   HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch0();

   if (Get_NM_Busoff_Indication())
   {
      NM_Bus_Off_Recovered();
   }

   VBM_Execute_Tx_Notifier_Functions_Ch0();

   msg_handle = VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch0();

   if(MSG_NOT_PENDING != msg_handle)
   {
      tx_msg_ptr = VBM_Get_Tx_Buffer_Address_For_Driver(msg_handle);
      CD_Tx_Message(0, msg_handle, tx_msg_ptr);
      VBM_Tx_Message_Loaded(msg_handle);
   }
   
   CAN_Tx_ISR_Status[0] = CAN_ISR_OFF;

   #if 0
   //Isr time testing
   address = (unsigned int *) 0xFFC4;
   *address = (unsigned int)(*address | 0x400);
   CAN_Handler_Enable_Global_Interrupts();
   #endif
}
#endif
#ifdef CAN_CH1_SELECTED
/*******************************************************************************
 * Function Name : CD_Transmit_ISR_Channel_1                                   *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN transmit   *
 * interrupt for channel '0'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_TRANSMIT_1 void CD_Transmit_ISR_Channel_1(void)
{
   //CD_Transmit_ISR(1);
   canuint8_t msg_handle;
   canuint8_t *tx_msg_ptr;

   CAN_Tx_ISR_Status[1] = CAN_ISR_ON;
   CD_Transmit_Status[1] = CAN_cbTRUE;

   HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch1();

   VBM_Execute_Tx_Notifier_Functions_Ch1();

   msg_handle = VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch1();

   if(MSG_NOT_PENDING != msg_handle)
   {
      tx_msg_ptr = VBM_Get_Tx_Buffer_Address_For_Driver(msg_handle);
      CD_Tx_Message(1, msg_handle, tx_msg_ptr);
      VBM_Tx_Message_Loaded(msg_handle);
   }

   CAN_Tx_ISR_Status[1] = CAN_ISR_OFF;

}
#endif
#ifdef CAN_CH2_SELECTED
/*******************************************************************************
 * Function Name : CD_Transmit_ISR_Channel_2                                   *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN transmit   *
 * interrupt for channel '0'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_TRANSMIT_2 void CD_Transmit_ISR_Channel_2(void)
{
   //CD_Transmit_ISR(2);
   canuint8_t msg_handle;
   canuint8_t *tx_msg_ptr;
   
   CAN_Tx_ISR_Status[2] = CAN_ISR_ON;
   CD_Transmit_Status[2] = cbTRUE;

   HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch2();

   VBM_Execute_Tx_Notifier_Functions_Ch2();

   msg_handle = VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch2();

   if(MSG_NOT_PENDING != msg_handle)
   {
      tx_msg_ptr = VBM_Get_Tx_Buffer_Address_For_Driver(msg_handle);
      CD_Tx_Message(2, msg_handle, tx_msg_ptr);
      VBM_Tx_Message_Loaded(msg_handle);
   }

   CAN_Tx_ISR_Status[2] = CAN_ISR_OFF;

}
#endif
#endif
#ifndef TRANSMIT_INTERRUPT_MODE

/*******************************************************************************
 * Function Name :  CD_Poll_Transmit_Success                                   *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *                N - Number of maximum channels present in the CAN controller *
 * Return Value : cbTRUE - If a message was transmitted successfully           *
 *                cbFALSE - If none of the messages was transmitted            *
 * Description :This routine can be called by application software to query    *
 * about the confirmation of a successfully transmitted message.               *
 ******************************************************************************/
Boolean_Returnvalue_T CD_Poll_Transmit_Success(canuint8_t channel_number)
{
   Boolean_Returnvalue_T transmit_success_flag;

   transmit_success_flag = cbFALSE;

   if( cbTRUE == Transmit_Message_Is_Loaded[channel_number] )
   {
      if( HWCAN_Has_Transmit_Confirmation_Been_Received(channel_number) )
      {
           Transmit_Message_Is_Loaded[channel_number] = cbFALSE;

           CD_Transmit_ISR(channel_number);

           transmit_success_flag = cbTRUE;
      }
   }
   return(transmit_success_flag);
}

#endif


/*******************************************************************************
*                    END OF TRANSMISSION                                       *
*******************************************************************************/

/*******************************************************************************
*                       START OF RECEPTION                                     *
 *******************************************************************************/

/*******************************************************************************
 * Function Name : CD_Receive_ISR                                              *
 * Function Parameters : channel number, 0 - (N-1)                             *
                  N - Number of maximum channels present in the CAN controlle  *
 * Return Value : None                                                         *
 * Description : This function shall be called by CD_Receive_ISR_Channel_n()   *
 * function, which is the interrupt service routine for CAN receive interrupt  *
 * for channel 'n'. This function can also be called by the user application   *
 * when the application wants to poll for newly received messages (when        *
 * receive interrupt is not enabled).                                          *
*******************************************************************************/
#if 1
#ifdef RECEIVE_INTERRUPT_MODE
 void CD_Receive_ISR(canuint8_t channel_number)
{
   RX_Msg_Info_T *rx_msg_info;
#else
 void CD_Receive_Poll(canuint8_t channel_number, RX_Msg_Info_T *rx_msg_info)
{
#endif
   Msg_ID_T rx_msg_id_to_validate;

   Virtual_RX_Buffer_Info_T virtual_rx_buffer_info;

   canuint8_t *CAN_Hw_Rx_Data_Ptr;

   CD_Receive_Status[channel_number] = cbTRUE;

   #ifdef RECEIVE_INTERRUPT_MODE
   rx_msg_info = HWCAN_Get_Rx_Msg_Info(channel_number);
   while( CAN_INVALID_MSG_NUMBER != rx_msg_info->hw_rx_buf_num)
   {
   #endif

      HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt(channel_number,
                                           rx_msg_info->hw_rx_buf_num); /* Only in interrupt..should be tested ?? */

      #ifdef  IGNORE_MSG_ID_BITS
      rx_msg_id_to_validate = Get_Rx_ID_After_Ignoring_Bits(channel_number,
      rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_id_type);
      #else
      rx_msg_id_to_validate = rx_msg_info->rx_msg_id;
      #endif
      if( INVALID_RECEIVE_MESSAGE_CODE != (
          virtual_rx_buffer_info.rx_message_handle =
          Is_Message_Valid(channel_number, rx_msg_info->hw_rx_buf_num, rx_msg_id_to_validate,
          rx_msg_info->rx_msg_id_type, rx_msg_info->rx_msg_dlc)))
      {

         CAN_Hw_Rx_Data_Ptr = HWCAN_Get_Rx_Data_Pointer(channel_number,
                              rx_msg_info->hw_rx_buf_num);

         #ifdef IGNORE_MSG_ID_BITS
         VBM_Copy_Rx_Message (channel_number, virtual_rx_buffer_info.
         rx_message_handle, rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_dlc,
         CAN_Hw_Rx_Data_Ptr);
         #else
         VBM_Copy_Rx_Message (channel_number, virtual_rx_buffer_info.
         rx_message_handle, rx_msg_info->rx_msg_dlc, CAN_Hw_Rx_Data_Ptr);
         #endif
         VBM_Execute_Rx_Notifier_Function(channel_number,
         virtual_rx_buffer_info.rx_message_handle);
      }
   #ifdef RECEIVE_INTERRUPT_MODE
     rx_msg_info = HWCAN_Get_Rx_Msg_Info(channel_number);
   }
   #endif
}

/*******************************************************************************
 * Function Name : Is_Message_Valid                                            *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 *               rx_msg_id - received message ID                               *
 *               rx_msg_id_type - received message ID type                     *
 *               rx_msg_dlc - data length code of the received message         *
 * Return Value :rx_msg_handle - index of the receive message parameter table  *
 *                               corresponding to the received message         *
 * Description : This function validates the receive message ID if it is       *
 * associated with any acceptance mask and the DLC. This function also looks   *
 * for errors like receive buffer overflow/overrun.                            *
*******************************************************************************/
 canuint8_t Is_Message_Valid(canuint8_t channel_number, canuint8_t hw_rx_buf,
           Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc)
{

   canuint8_t rx_msg_handle;
   #ifndef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   canuint8_t rx_msg_offset;
   #endif

   if( CAN_cbTRUE == HWCAN_Is_Message_OverWritten(channel_number, hw_rx_buf) )
   {
      Appl_Hardware_Rx_Buffer_Overrun(channel_number);
   }
   #ifdef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   rx_msg_handle = VBM_Get_Rx_Msg_Handle(channel_number, rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
   #else

   rx_msg_offset = HWCAN_Get_First_Rx_Buf_Number(channel_number);

   if(hw_rx_buf > HWCAN_Get_Tx_Buf_Number(channel_number))
   {
     if(rx_msg_offset > HWCAN_Get_Tx_Buf_Number(channel_number))
     {
       rx_msg_handle = hw_rx_buf - rx_msg_offset;
     }
     else
     {
      rx_msg_handle = hw_rx_buf-rx_msg_offset- NUMBER_OF_HW_TX_BUF_PER_CHANNEL;
     }
   }
   else
   {
     rx_msg_handle = hw_rx_buf- rx_msg_offset;
   }
   if(HWCAN_Is_Mask_Used_For_Rx_Buffer(channel_number, rx_msg_handle))
   {
    #ifndef J1939_PROTOCOL_IS_USED

     rx_msg_handle = VBM_Validate_Rx_Msg_With_Mask(channel_number, rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
    #else
     message_validity = VBM_Validate_J1939_Rx_Msg(channel_number, rx_msg_id,
                   rx_msg_handle, rx_msg_dlc);
     if( MESSAGE_INVALID == message_validity )
     {
        rx_msg_handle = DLC_MISMATCH;
     }
    #endif
   }
   else
   {
     if(MESSAGE_INVALID == VBM_Validate_Rx_Msg_With_No_Mask(
                           channel_number, rx_msg_handle, rx_msg_dlc))
     {
       rx_msg_handle = DLC_MISMATCH;
     }
     else
     {
     }
   }
   #endif
   return(rx_msg_handle);
}
#endif
//              Separate Channel wise APIs to reduce ISR Timing
#ifdef CAN_CH0_SELECTED
 canuint8_t Is_Message_Valid_Ch0(canuint8_t hw_rx_buf,
          Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc)
{
   canuint8_t rx_msg_handle;
   #ifndef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   canuint8_t rx_msg_offset;
   #endif

   if( CAN_cbTRUE == HWCAN_Is_Message_OverWritten_Ch0(hw_rx_buf) )
   {
      Appl_Hardware_Rx_Buffer_Overrun(0);
   }
   #ifdef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   rx_msg_handle = VBM_Get_Rx_Msg_Handle_Ch0(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
   #else

   rx_msg_offset = HWCAN_Get_First_Rx_Buf_Number_Ch0();

   if(hw_rx_buf > HWCAN_Get_Tx_Buf_Number_Ch0())
   {
     if(rx_msg_offset > HWCAN_Get_Tx_Buf_Number_Ch0())
     {
       rx_msg_handle = hw_rx_buf - rx_msg_offset;
     }
     else
     {
      rx_msg_handle = hw_rx_buf-rx_msg_offset- NUMBER_OF_HW_TX_BUF_PER_CHANNEL;
     }
   }
   else
   {
     rx_msg_handle = hw_rx_buf- rx_msg_offset;
   }
   if(HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch0(rx_msg_handle))
   {
    #ifndef J1939_PROTOCOL_IS_USED

     rx_msg_handle = VBM_Validate_Rx_Msg_With_Mask_Ch0(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
    #else
     message_validity = VBM_Validate_J1939_Rx_Msg_Ch0(rx_msg_id,
                   rx_msg_handle, rx_msg_dlc);
     if( MESSAGE_INVALID == message_validity )
     {
        rx_msg_handle = DLC_MISMATCH;
     }
    #endif
   }
   else
   {
  #ifndef HWCAN_MASK_USED
     if(MESSAGE_INVALID == VBM_Validate_Rx_Msg_With_No_Mask_Ch0(
                           rx_msg_handle, rx_msg_dlc))
     {
       rx_msg_handle = DLC_MISMATCH;
     }
     else
     {
     }
 #else
     #ifndef J1939_PROTOCOL_IS_USED

     rx_msg_handle = VBM_Validate_Rx_Msg_With_Mask_Ch0(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
    #else
     message_validity = VBM_Validate_J1939_Rx_Msg_Ch0(rx_msg_id,
                   rx_msg_handle, rx_msg_dlc);
     if( MESSAGE_INVALID == message_validity )
     {
        rx_msg_handle = DLC_MISMATCH;
     }
    #endif
 #endif
     
   }
   #endif
   return(rx_msg_handle);
}
#endif
#ifdef CAN_CH1_SELECTED
 canuint8_t Is_Message_Valid_Ch1(canuint8_t hw_rx_buf,
                                       Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc)
{
   canuint8_t rx_msg_handle;
   canbool8_t message_validity;
   #ifndef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   canuint8_t rx_msg_offset;
   #endif

   if( cbTRUE == HWCAN_Is_Message_OverWritten_Ch1(hw_rx_buf) )
   {
      Appl_Hardware_Rx_Buffer_Overrun(1);
   }
   #ifdef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   rx_msg_handle = VBM_Get_Rx_Msg_Handle_Ch1(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
   #else

   rx_msg_offset = HWCAN_Get_First_Rx_Buf_Number_Ch1();

   if(hw_rx_buf > HWCAN_Get_Tx_Buf_Number_Ch1())
   {
     if(rx_msg_offset > HWCAN_Get_Tx_Buf_Number_Ch1())
     {
       rx_msg_handle = hw_rx_buf - rx_msg_offset;
     }
     else
     {
      rx_msg_handle = hw_rx_buf-rx_msg_offset- NUMBER_OF_HW_TX_BUF_PER_CHANNEL;
     }
   }
   else
   {
     rx_msg_handle = hw_rx_buf- rx_msg_offset;
   }
   if(HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch1(rx_msg_handle))
   {
    #ifndef J1939_PROTOCOL_IS_USED

     rx_msg_handle = VBM_Validate_Rx_Msg_With_Mask_Ch1(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
    #else
     message_validity = VBM_Validate_J1939_Rx_Msg_Ch1(rx_msg_id,
                   rx_msg_handle, rx_msg_dlc);
     if( MESSAGE_INVALID == message_validity )
     {
        rx_msg_handle = DLC_MISMATCH;
     }
    #endif
   }
   else
   {
     if(MESSAGE_INVALID == VBM_Validate_Rx_Msg_With_No_Mask_Ch1(
                           rx_msg_handle, rx_msg_dlc))
     {
       rx_msg_handle = DLC_MISMATCH;
     }
     else
     {
     }
   }
   #endif
   return(rx_msg_handle);
}
#endif
#ifdef CAN_CH2_SELECTED
 canuint8_t Is_Message_Valid_Ch2(canuint8_t hw_rx_buf,
                                       Msg_ID_T rx_msg_id, Msg_ID_Type_T rx_msg_id_type, canuint8_t rx_msg_dlc)
{
   canuint8_t rx_msg_handle;
   canbool8_t message_validity;
   #ifndef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   canuint8_t rx_msg_offset;
   #endif

   if( cbTRUE == HWCAN_Is_Message_OverWritten_Ch2(hw_rx_buf) )
   {
      Appl_Hardware_Rx_Buffer_Overrun(2);
   }
   #ifdef RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE
   rx_msg_handle = VBM_Get_Rx_Msg_Handle_Ch2(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
   #else

   rx_msg_offset = HWCAN_Get_First_Rx_Buf_Number_Ch2();

   if(hw_rx_buf > HWCAN_Get_Tx_Buf_Number_Ch2())
   {
     if(rx_msg_offset > HWCAN_Get_Tx_Buf_Number_Ch2())
     {
       rx_msg_handle = hw_rx_buf - rx_msg_offset;
     }
     else
     {
      rx_msg_handle = hw_rx_buf-rx_msg_offset- NUMBER_OF_HW_TX_BUF_PER_CHANNEL;
     }
   }
   else
   {
     rx_msg_handle = hw_rx_buf- rx_msg_offset;
   }
   if(HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch2(rx_msg_handle))
   {
    #ifndef J1939_PROTOCOL_IS_USED

     rx_msg_handle = VBM_Validate_Rx_Msg_With_Mask_Ch2(rx_msg_id,
                   rx_msg_id_type, rx_msg_dlc);
    #else
     message_validity = VBM_Validate_J1939_Rx_Msg_Ch2(rx_msg_id,
                   rx_msg_handle, rx_msg_dlc);
     if( MESSAGE_INVALID == message_validity )
     {
        rx_msg_handle = DLC_MISMATCH;
     }
    #endif
   }
   else
   {
     if(MESSAGE_INVALID == VBM_Validate_Rx_Msg_With_No_Mask_Ch2(
                           rx_msg_handle, rx_msg_dlc))
     {
       rx_msg_handle = DLC_MISMATCH;
     }
     else
     {
     }
   }
   #endif
   return(rx_msg_handle);
}
#endif


#ifdef RECEIVE_INTERRUPT_MODE
#ifdef CAN_CH0_SELECTED
/*******************************************************************************
 * Function Name : CD_Receive_ISR_Channel_0                                    *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN receive    *
 * interrupt for channel '0'.                                                  *
 ******************************************************************************/
//#pragma interrupt INTC0REC CD_Receive_ISR_Channel_0

/*CAN_INTERRUPT_RECEIVE_0*/ void CD_Receive_ISR_Channel_0(void)
{
   RX_Msg_Info_T *rx_msg_info;
   Msg_ID_T rx_msg_id_to_validate;

   Virtual_RX_Buffer_Info_T virtual_rx_buffer_info;

   canuint8_t *CAN_Hw_Rx_Data_Ptr;

   #if 0
   //Isr time testing
   unsigned int *address;
   CAN_Handler_Disable_Global_Interrupts();
   address = (unsigned int *) 0xFFC4;
   *address = (unsigned int)(*address & ~0x400);
   #endif

   CD_Receive_Status[0] = CAN_cbTRUE;

   rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch0();

   while( CAN_INVALID_MSG_NUMBER != rx_msg_info->hw_rx_buf_num)
   {
      HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch0(rx_msg_info->hw_rx_buf_num);
      #ifdef  IGNORE_MSG_ID_BITS
      rx_msg_id_to_validate = Get_Rx_ID_After_Ignoring_Bits(0,rx_msg_info->rx_msg_id,rx_msg_info->rx_msg_id_type);
      #else
      rx_msg_id_to_validate = rx_msg_info->rx_msg_id;
      #endif

      if( INVALID_RECEIVE_MESSAGE_CODE != (virtual_rx_buffer_info.rx_message_handle =
          Is_Message_Valid_Ch0( rx_msg_info->hw_rx_buf_num, rx_msg_id_to_validate,
          rx_msg_info->rx_msg_id_type, rx_msg_info->rx_msg_dlc)))
      {
         CAN_Hw_Rx_Data_Ptr = HWCAN_Get_Rx_Data_Pointer_Ch0(rx_msg_info->hw_rx_buf_num);
         #ifdef IGNORE_MSG_ID_BITS
         VBM_Copy_Rx_Message_Ch0(virtual_rx_buffer_info.rx_message_handle,
                                                         rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_dlc,
                                                         CAN_Hw_Rx_Data_Ptr);
         #else
         VBM_Copy_Rx_Message_Ch0( virtual_rx_buffer_info.rx_message_handle, 
                                                          rx_msg_info->rx_msg_dlc, CAN_Hw_Rx_Data_Ptr);
	 #endif
         VBM_Execute_Rx_Notifier_Function_Ch0(virtual_rx_buffer_info.rx_message_handle);
      }
     rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch0();
   }
   #if 0
   //Isr time testing
   address = (unsigned int *) 0xFFC4;
   *address = (unsigned int)(*address | 0x400);
   CAN_Handler_Enable_Global_Interrupts();
   #endif
}
#endif
#ifdef CAN_CH1_SELECTED
/*******************************************************************************
 * Function Name : CD_Receive_ISR_Channel_1                                    *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN receive    *
 * interrupt for channel '1'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_RECEIVE_1 void CD_Receive_ISR_Channel_1(void)
{
   //CD_Receive_ISR(1);

   RX_Msg_Info_T *rx_msg_info;
   Msg_ID_T rx_msg_id_to_validate;

   Virtual_RX_Buffer_Info_T virtual_rx_buffer_info;

   canuint8_t *CAN_Hw_Rx_Data_Ptr;

   CD_Receive_Status[1] = cbTRUE;

   rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch1();
   while( CAN_INVALID_MSG_NUMBER != rx_msg_info->hw_rx_buf_num)
   {

      HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch1(
                                           rx_msg_info->hw_rx_buf_num);

      #ifdef  IGNORE_MSG_ID_BITS
      rx_msg_id_to_validate = Get_Rx_ID_After_Ignoring_Bits(1,
      rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_id_type);
      #else
      rx_msg_id_to_validate = rx_msg_info->rx_msg_id;
      #endif
      if( INVALID_RECEIVE_MESSAGE_CODE != (
          virtual_rx_buffer_info.rx_message_handle =
          Is_Message_Valid_Ch1( rx_msg_info->hw_rx_buf_num, rx_msg_id_to_validate,
          rx_msg_info->rx_msg_id_type, rx_msg_info->rx_msg_dlc)))
      {

         CAN_Hw_Rx_Data_Ptr = HWCAN_Get_Rx_Data_Pointer_Ch1(
                              rx_msg_info->hw_rx_buf_num);

         #ifdef IGNORE_MSG_ID_BITS
         VBM_Copy_Rx_Message_Ch1(virtual_rx_buffer_info.
         rx_message_handle, rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_dlc,
         CAN_Hw_Rx_Data_Ptr);
         #else
         VBM_Copy_Rx_Message_Ch1( virtual_rx_buffer_info.
         rx_message_handle, rx_msg_info->rx_msg_dlc, CAN_Hw_Rx_Data_Ptr);
         #endif
         VBM_Execute_Rx_Notifier_Function_Ch1(
         virtual_rx_buffer_info.rx_message_handle);
      }
     rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch1();
   }
}
#endif
#ifdef CAN_CH2_SELECTED
/*******************************************************************************
 * Function Name : CD_Receive_ISR_Channel_1                                    *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN receive    *
 * interrupt for channel '2'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_RECEIVE_2 void CD_Receive_ISR_Channel_2(void)
{
   //CD_Receive_ISR(2);
   RX_Msg_Info_T *rx_msg_info;
   Msg_ID_T rx_msg_id_to_validate;

   Virtual_RX_Buffer_Info_T virtual_rx_buffer_info;

   canuint8_t *CAN_Hw_Rx_Data_Ptr;

   CD_Receive_Status[2] = cbTRUE;

   rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch2();
   while( CAN_INVALID_MSG_NUMBER != rx_msg_info->hw_rx_buf_num)
   {

      HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch2(
                                           rx_msg_info->hw_rx_buf_num);

      #ifdef  IGNORE_MSG_ID_BITS
      rx_msg_id_to_validate = Get_Rx_ID_After_Ignoring_Bits(2,
      rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_id_type);
      #else
      rx_msg_id_to_validate = rx_msg_info->rx_msg_id;
      #endif
      if( INVALID_RECEIVE_MESSAGE_CODE != (
          virtual_rx_buffer_info.rx_message_handle =
          Is_Message_Valid_Ch2( rx_msg_info->hw_rx_buf_num, rx_msg_id_to_validate,
          rx_msg_info->rx_msg_id_type, rx_msg_info->rx_msg_dlc)))
      {

         CAN_Hw_Rx_Data_Ptr = HWCAN_Get_Rx_Data_Pointer_Ch2(
                              rx_msg_info->hw_rx_buf_num);

         #ifdef IGNORE_MSG_ID_BITS
         VBM_Copy_Rx_Message_Ch2(virtual_rx_buffer_info.
         rx_message_handle, rx_msg_info->rx_msg_id, rx_msg_info->rx_msg_dlc,
         CAN_Hw_Rx_Data_Ptr);
         #else
         VBM_Copy_Rx_Message_Ch2( virtual_rx_buffer_info.
         rx_message_handle, rx_msg_info->rx_msg_dlc, CAN_Hw_Rx_Data_Ptr);
         #endif
         VBM_Execute_Rx_Notifier_Function_Ch2(
         virtual_rx_buffer_info.rx_message_handle);
      }
     rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch2();
   }
}
#endif
#endif

#ifdef  IGNORE_MSG_ID_BITS

/*******************************************************************************
 * Function Name : Get_Rx_ID_After_Ignoring_Bits                               *
 * Function Parameters : channel number, 0 - (N-1)                             *
                  N - Number of maximum channels present in the CAN controller *
 * Return Value : None                                                         *
 * Description : This function would be called by CD_ISR_Receive() function    *
 *               to mask the ignore bits,if any,of the received message ID     *
*******************************************************************************/
Msg_ID_T Get_Rx_ID_After_Ignoring_Bits(canuint8_t channel_number, Msg_ID_T
                                 rx_msg_id, Msg_ID_Type_T rx_msg_id_type)
{
     rx_msg_id =  rx_msg_id & Bit_Ignore_Patterns[channel_number]
                  [rx_msg_id_type];
     return(rx_msg_id);
}

#endif

#ifndef RECEIVE_INTERRUPT_MODE
/*******************************************************************************
 * Function Name : CD_Poll_Received_Messages                                   *
 * Function Parameters : channel number, 0 - (N-1)                             *
                  N - Number of maximum channels present in the CAN controlle  *
 * Return Value : None                                                         *
 * Description : This function can also be called by the user application      *
 * when the application wants to poll for newly received messages (when        *
 * receive interrupt is not enabled).                                          *
*******************************************************************************/
void CD_Poll_Received_Messages(canuint8_t channel_number)
{
  RX_Msg_Info_T *rx_msg_info;

  rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch0();

  while(CAN_INVALID_MSG_NUMBER != rx_msg_info->hw_rx_buf_num)
  {
     CD_Receive_Poll(channel_number, rx_msg_info);
     rx_msg_info = HWCAN_Get_Rx_Msg_Info_Ch0();
  }
}
#endif

/*******************************************************************************
*                       END OF RECEPTION                                       *
 *******************************************************************************/

#ifdef CAN_COMMON_VECTOR
/*******************************************************************************
 * Function Name : CD_ISR                                                      *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description :This is the interrupt service routine for all CAN related      *
 * interrupts. If in case all CAN related interrupts have been triggered on    *
 * only one interrupt line towards CPU, then this would be an interrupt        *
 * service routine for all CAN interrupts. Once this function is called,       *
 * corresponding interrupt service routine will be called based on the         *
 * corresponding interrupt pending flag. This function shall be defined in     *
 * configurable section of CAN driver layer and shall be used only if          *
 * application wants to use it.                                                *
 ******************************************************************************/
void CD_ISR(canuint8_t channel_number)
{
   canuint8_t interrupt_number;

   interrupt_number = ZERO;

   while( NUMBER_OF_INTERRUPTS_SUPPORTED > interrupt_number)
   {
       if( cbTRUE == HWCAN_Get_IntPnd_Status(channel_number,
           CAN_ISR_Table[interrupt_number][channel_number].interrupt_type) )
       {
          (*CAN_ISR_Table[interrupt_number][channel_number].isr)();
       }
       interrupt_number++;
    }
}
#ifdef CAN_CH0_SELECTED
/*******************************************************************************
 * Function Name : CD_ISR_Channel_0                                            *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN common     *
 * vector for channel '0'.                                                     *
 ******************************************************************************/
CAN_INTERRUPT_0 void CD_ISR_Channel_0(void)
{
   CD_ISR(0);
}
#endif
#ifdef CAN_CH1_SELECTED
/*******************************************************************************
 * Function Name : CD_ISR_Channel_1                                            *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN common     *
 * vector for channel '1'.                                                     *
 ******************************************************************************/
CAN_INTERRUPT_1 void CD_ISR_Channel_1(void)
{
   CD_ISR(1);
}
#endif
#ifdef CAN_CH2_SELECTED
/*******************************************************************************
 * Function Name : CD_ISR_Channel_2                                            *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is interrupt service routine for CAN common     *
 * vector for channel '2'.                                                     *
 ******************************************************************************/
CAN_INTERRUPT_2 void CD_ISR_Channel_2(void)
{
   CD_ISR(2);
}
#endif

#endif

/*******************************************************************************
 * Function Name : CD_Clear_Transmit_Status                                    *
 * Function Parameters : channel_number                                        *
 * Return Value : None                                                         *
 * Description : This function is called by init function of driver to clear   *
 * the status of transmission                                                  *
 ******************************************************************************/
void CD_Clear_Transmit_Status(canuint8_t channel_number)
{
   CD_Transmit_Status[channel_number] = cbFALSE;
   CAN_Tx_ISR_Status[channel_number] = CAN_ISR_OFF;
}

/*******************************************************************************
 * Function Name : CD_Clear_Receive_Status                                     *
 * Function Parameters : channel_number                                        *
 * Return Value : None                                                         *
 * Description : This function is called by init function of driver to clear   *
 * the status of reception                                                     *
 ******************************************************************************/
void CD_Clear_Receive_Status(canuint8_t channel_number)
{
   CD_Receive_Status[channel_number] = CAN_cbFALSE;
}

/*******************************************************************************
 * Function Name : CD_Get_Transmit_Status                                      *
 * Function Parameters : channel_number                                        *
 * Return Value : Transmit Status True/False                                   *
 * Description : This function is called by appl/NM to know the status of      *
 * transmission                                                                *
 ******************************************************************************/
canbool8_t CD_Get_Transmit_Status(canuint8_t channel_number)
{
  return(CD_Transmit_Status[channel_number]);
}

/*******************************************************************************
 * Function Name : CD_Get_Receive_Status                                       *
 * Function Parameters : channel_number                                        *
 * Return Value : Receive Status True/False                                    *
 * Description : This function is called by appl/NM to know the status of      *
 * reception                                                                   *
 ******************************************************************************/
canbool8_t CD_Get_Receive_Status(canuint8_t channel_number)
{
  return(CD_Receive_Status[channel_number]);
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
