/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - VBM                                                        *
 * File Name:  can_vbm_tx.c                                                  *
 * File Description:                                                         *
 * This file contains: get and set functions to access Transmit Parameter    *
 * table and Transmit Run-time table, and store transmit messages in         *
 * circular buffers to support FIFO messages                                 *
 *****************************************************************************/

#include "can_vbm_tx.h"
#include "can_vbm_config.h"
#include "can_drv_init_misc.h"
#include "can_drv_tx_rx.h"
#include "can_handler.h"
#include "can_handler_config.h"
#include "can_aif_config.h"


transmit_buffer_T transmit_buffer[TOTAL_NUMBER_OF_TX_MSG];

canuint8_t Tx_Buffer_Block[TOTAL_BYTES_FOR_TX_DATA_BUFFER_CH0];

#ifdef TRANSMIT_INTERRUPT_MODE
static canuint8_t Previous_Tx_Message_Int[NUMBER_OF_CHANNELS_SUPPORTED];
#else
static canuint8_t Previous_Tx_Message_Poll[NUMBER_OF_CHANNELS_SUPPORTED]
                                       [MAX_TX_MSG_PER_LOOP_FOR_POLL];
static canuint8_t tx_msg_handle_index[NUMBER_OF_CHANNELS_SUPPORTED];
#endif

static canuint8_t *buffer_pointer =(canuint8_t *) Tx_Buffer_Block;

/*******************************************************************************
*******              STATIC FUNCTION DECLARATIONS                        *******
*******************************************************************************/
 canuint8_t* Get_Tx_Msg_Data_Base_Ptr(canuint16_t requested_allocation_in_bytes);
 canbool8_t VBM_Get_Tx_Virtual_Buffer_Status (canuint8_t msg_handle);
 void VBM_Update_Tx_Virtual_Buffer_Status (canuint8_t msg_handle);

/*******************************************************************************
*******              I N I T I A L I Z A T I O N                        *******
*******************************************************************************/

/******************************************************************************
* Prototype:  VBM_Cold_Initialization_Tx                                      *
* Arguments passed: channel number                                            *
* Return type: void                                                           *
* Functionality: This API initializes the transmit software buffers           *
* defined in the Virtual Buffer Management Layer.                             *
******************************************************************************/
void VBM_Cold_Initialization_Tx (canuint8_t channel_num)
{
   canuint8_t msg_handle;
   const VBM_Transmit_Msg_Parameter_T * Pointer_to_Tx_Parameter_Struct;
   transmit_buffer_T * Pointer_to_Tx_Buffer;
   buffer_pointer =(canuint8_t *) Tx_Buffer_Block;
   
  for(msg_handle = 0; msg_handle < Size_Of_Transmit_Param_Table; msg_handle++)
  {
     Pointer_to_Tx_Parameter_Struct = &VBM_Tx_Msg_Parameter_Table[msg_handle];
     if(channel_num == Pointer_to_Tx_Parameter_Struct->channel_number)
     {
        Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];

        #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
        if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
        {
          Pointer_to_Tx_Buffer->data_base_address = 
          Get_Tx_Msg_Data_Base_Ptr( (Pointer_to_Tx_Parameter_Struct->message_length_dlc) * 
                                    (Pointer_to_Tx_Parameter_Struct->buffer_depth) );
        }
        else
        {
          Pointer_to_Tx_Buffer->data_base_address =             
          Get_Tx_Msg_Data_Base_Ptr(Pointer_to_Tx_Parameter_Struct->message_length_dlc);
        }   
        #else
        Pointer_to_Tx_Buffer->data_base_address = 
        Get_Tx_Msg_Data_Base_Ptr(Pointer_to_Tx_Parameter_Struct->message_length_dlc);
        #endif       

        Pointer_to_Tx_Buffer->message_pending = NO_NEW_MESSAGE_PENDING;
        Pointer_to_Tx_Buffer->partially_offline = PARTIALLY_NOT_OFFLINE;

        #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
        Pointer_to_Tx_Buffer->in_index = 0;
        Pointer_to_Tx_Buffer->out_index = 0;
        Pointer_to_Tx_Buffer->buffer_status = TX_BUFFER_NOT_FULL;
        #endif
     }
  }
}
/******************************************************************************
* Prototype: Get_Tx_Msg_Data_Base_Ptr                                         *
* Arguments passed:  requested_allocation_in_bytes                            *
* Return type:  data_base_address (allocation pointer)                        *
* Functionality: This function allocates memory to the transmit buffers and   *
*  returns the base_address for every transmit message virtual buffer.        *
*******************************************************************************/
 canuint8_t* Get_Tx_Msg_Data_Base_Ptr(canuint16_t requested_allocation_in_bytes)
{
  canuint8_t *allocation_pointer = buffer_pointer;
  buffer_pointer = ( canuint8_t * ) ( buffer_pointer + requested_allocation_in_bytes );
  return( allocation_pointer );
}

/******************************************************************************
* Prototype:  VBM_Warm_Initialization_Tx                                      *
* Arguments passed:  channel number                                           *
* Return type: None                                                           *
* Functionality: This API initializes the transmit software buffers defined in*
* the Virtual Buffer Management Layer.                                        *
*******************************************************************************/
void VBM_Warm_Initialization_Tx (canuint8_t channel_num)
{
   canuint8_t msg_handle;
   transmit_buffer_T * Pointer_to_Tx_Buffer;

  for(msg_handle = 0; msg_handle < Size_Of_Transmit_Param_Table; msg_handle++)
   {
     if(channel_num == VBM_Tx_Msg_Parameter_Table[msg_handle].channel_number)
     {
        Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
        Pointer_to_Tx_Buffer->message_pending = NO_NEW_MESSAGE_PENDING;
        Pointer_to_Tx_Buffer->partially_offline = PARTIALLY_NOT_OFFLINE;

        #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
        Pointer_to_Tx_Buffer->in_index = 0;
        Pointer_to_Tx_Buffer->out_index = 0;
        Pointer_to_Tx_Buffer->buffer_status = TX_BUFFER_NOT_FULL;
        #endif
     }
   }
}

/*******************************************************************************
*******                        T R A N S M I T                           *******
*******************************************************************************/
/******************************************************************************
* Prototype:  VBM_Get_Tx_Msg_Handle_From_Message_ID                           *
* Arguments passed: channel number, Message_ID                                *
* Return type: msg handle                                                     *
* Functionality: This function finds the Message Number corresponding to the  *
* Message ID to be transmitted from the VBM_Tx_Msg_Parameter_Table[]          *
* by performing Binary Search. Message Number is the array index in the table *
* for the particular Message ID. The contents of VBM_Tx_Msg_Parameter_Table   *
* must be arranged in decreasing priority.                                    *
*******************************************************************************/
#ifndef J1939_PROTOCOL_IS_USED
canuint8_t VBM_Get_Tx_Msg_Handle_From_Message_ID (canuint8_t channel_num,
                                               Msg_ID_T ID_passed)
{
   return(CAN_Binary_Search(channel_num, ID_passed, HWCAN_TRANSMIT));
}
#endif
/******************************************************************************
* Prototype:  VBM_Get_Tx_Channel_num_From_Msg_Handle                          *
* Arguments passed: tx_message_handle                                         *
* Return type: channel num                                                    *
* Functionality: This function finds the channel Number corresponding to the  *
* Message Handle from the VBM_Tx_Msg_Parameter_Table[]                        *
*******************************************************************************/
canuint8_t VBM_Get_Tx_Channel_num_From_Msg_Handle(canuint8_t tx_message_handle)
{
   return (VBM_Tx_Msg_Parameter_Table[tx_message_handle].channel_number);
}

/******************************************************************************
* Prototype:  VBM_Set_Tx_Message_DLC                                          *
* Arguments passed: message handle, dlc of the transmit message               *
* Return type: true if valid req else Invalid request                         *
* Functionality: For messages with variable message length, upper layers must *
* call this function before calling VBM_Tx_Message / VBM_Tx_Request.          *
* VBM_Set_Tx_Message_DLC updates the dlc that is used by                      *
* VBM_Get_Tx_Message_DLC function.                                            *
*******************************************************************************/
canbool8_t VBM_Set_Tx_Message_DLC(canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t dlc_set_status; 
  const VBM_Transmit_Msg_Parameter_T * Pointer_to_Tx_Parameter_Struct;
  transmit_buffer_T * Pointer_to_Tx_Buffer;

  Pointer_to_Tx_Parameter_Struct = &VBM_Tx_Msg_Parameter_Table[msg_handle];
  Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
  dlc_set_status = INVALID_REQUEST_TX;
  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
    if(TX_VARIABLE_DLC == Pointer_to_Tx_Parameter_Struct->message_length_dlc)
    {
       #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
       if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
       {
         *(Pointer_to_Tx_Buffer->data_base_address       
         + (Pointer_to_Tx_Buffer->in_index * TX_VARIABLE_DLC + 8)) = dlc;
       }
       else
       {
         *(Pointer_to_Tx_Buffer->data_base_address + 8) = dlc;
       }
       #else
       *(Pointer_to_Tx_Buffer->data_base_address + 8) = dlc;
       #endif
       dlc_set_status = cbTRUE;
    }
  }
  return (dlc_set_status);
}

/******************************************************************************
* Prototype:  VBM_Set_Partial_Offline_Mode                                    *
* Arguments passed: message handle                                            *
* Return type: none                                                           *
* Functionality: This function sets the partial offline flag for the given    *
* message handle.During the time a message is made partially offline a request*
* to transmit that message will not be honored.                               *
*******************************************************************************/
void VBM_Set_Partial_Offline_Mode (canuint8_t msg_handle)
{
  transmit_buffer[msg_handle].partially_offline = PARTIALLY_OFFLINE;
}

/******************************************************************************
* Prototype:  VBM_Clear_Partial_Offline_Mode                                  *
* Arguments passed: message handle                                            *
* Return type: none                                                           *
* Functionality: This function clears the partial offline flag for the given  *
* message handle.During the time a message is made partially offline a request*
* to transmit that message will not be honored.                               *
*******************************************************************************/
void VBM_Clear_Partial_Offline_Mode (canuint8_t msg_handle)
{
  transmit_buffer[msg_handle].partially_offline = PARTIALLY_NOT_OFFLINE;
}

//#ifdef J1939_PROTOCOL_IS_USED
/******************************************************************************
* Prototype:  VBM_Tx_J1939_Message                                            *
* Arguments passed:  message handle, msg_ID, address of appl data byte array  *
* Return type: transmit status                                                *
* Functionality: The upper layer, to transmit a message, invokes              *
* VBM_Tx_Message(). ID, DLC and data bytes of the message are loaded to       *
* the hardware transmit buffer. If the hardware buffer is not available, the  *
* data bytes are copied to the virtual software buffer for later transmission *
* (when the buffer becomes available). For messages with variable message-    *
* length, upper layers must call the function VBM_Set_Tx_Message_DLC          *
* before calling VBM_Tx_Message.                                              *
*******************************************************************************/
//canbool8_t VBM_Tx_J1939_Message (canuint8_t msg_handle, canuint32_t msg_ID,
//                                           canuint8_t *appl_data_ptr)
//#else
/******************************************************************************
* Prototype:  VBM_Tx_Message                                                  *
* Arguments passed:  message handle, address of appl data byte array          *
* Return type: transmit status                                                *
* Functionality: The upper layer, to transmit a message, invokes              *
* VBM_Tx_Message(). ID, DLC and data bytes of the message are loaded to       *
* the hardware transmit buffer. If the hardware buffer is not available, the  *
* data bytes are copied to the virtual software buffer for later transmission *
* (when the buffer becomes available). For messages with variable message-    *
* length, upper layers must call the function VBM_Set_Tx_Message_DLC          *
* before calling VBM_Tx_Message.                                              *
*******************************************************************************/
canbool8_t VBM_Tx_Message (canuint8_t msg_handle, canuint8_t * appl_data_ptr)
//#endif
{
  canuint8_t* vbm_tx_data_ptr_to_copy_from_appl;
  canuint8_t* vbm_tx_data_ptr_to_copy_to_driver;
  canuint8_t channel_num, dlc;
  transmit_buffer_T * Pointer_to_Tx_Buffer;
  const VBM_Transmit_Msg_Parameter_T * Pointer_to_Tx_Parameter_Struct;

  canbool8_t transmit_status = TRANSMIT_FAILURE;

  channel_num = VBM_Tx_Msg_Parameter_Table[msg_handle].channel_number;

  if(INITIALIZED == Is_CAN_Handler_Initialized(channel_num))
  {
       Pointer_to_Tx_Parameter_Struct = &VBM_Tx_Msg_Parameter_Table[msg_handle];
       Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
      
       if((Size_Of_Transmit_Param_Table > msg_handle)
          &&(PARTIALLY_NOT_OFFLINE==Pointer_to_Tx_Buffer->partially_offline)
          #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
          &&(TX_BUFFER_NOT_FULL== VBM_Get_Tx_Virtual_Buffer_Status(msg_handle)))
          #else
          )
          #endif
       {
           if(TX_VARIABLE_DLC == Pointer_to_Tx_Parameter_Struct->message_length_dlc)
           {
              #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
              if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
              {
                dlc = *(Pointer_to_Tx_Buffer->data_base_address + 
                       (Pointer_to_Tx_Buffer->in_index * TX_VARIABLE_DLC + 8));
              }
              else
              {
                dlc = *(Pointer_to_Tx_Buffer->data_base_address + 8);
              }
              #else
              dlc = *(Pointer_to_Tx_Buffer->data_base_address + 8);
              #endif
           }
           else
           {
              dlc = Pointer_to_Tx_Parameter_Struct->message_length_dlc;
           }
           #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
           if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
           {
             vbm_tx_data_ptr_to_copy_from_appl = (canuint8_t*)(Pointer_to_Tx_Buffer->data_base_address) + 
                                                              ((Pointer_to_Tx_Buffer->in_index)* 
                                                               (Pointer_to_Tx_Parameter_Struct->message_length_dlc));
             
             vbm_tx_data_ptr_to_copy_to_driver = (canuint8_t*)(Pointer_to_Tx_Buffer->data_base_address) + 
                                                              ((Pointer_to_Tx_Buffer->out_index)* 
                                                               (Pointer_to_Tx_Parameter_Struct->message_length_dlc));

           }
           else
           {
           vbm_tx_data_ptr_to_copy_from_appl = Pointer_to_Tx_Buffer->data_base_address;
           vbm_tx_data_ptr_to_copy_to_driver = vbm_tx_data_ptr_to_copy_from_appl;

           }
           #else
           vbm_tx_data_ptr_to_copy_from_appl = Pointer_to_Tx_Buffer->data_base_address;
           vbm_tx_data_ptr_to_copy_to_driver = vbm_tx_data_ptr_to_copy_from_appl;
           #endif
           

           #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
           CAN_Handler_Disable_Global_Interrupts();
           #endif

          // CAN_Handler_Disable_Interrupts();
            HWCAN_Disable_TX_CAN_Interrupts(0);
        
           switch(dlc)  
           {
             case (8):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++; 
             case (7):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++; 
             case (6):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++; 
             case (5):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++; 
             case (4):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++; 
             case (3):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++; 
             case (2):
                     *vbm_tx_data_ptr_to_copy_from_appl++ = *appl_data_ptr++;
             case (1):
                     *vbm_tx_data_ptr_to_copy_from_appl = *appl_data_ptr; 
             default :
                     break;
           }
           
           #ifdef J1939_PROTOCOL_IS_USED
           Pointer_to_Tx_Buffer->message_ID = msg_ID;
           #endif

           VBM_Update_Tx_Virtual_Buffer_Status(msg_handle);

           transmit_status = CD_Tx_Message(channel_num, msg_handle, vbm_tx_data_ptr_to_copy_to_driver);

           if(TRANSMIT_SUCCESS == transmit_status)
           {
             //test_tx = 1;
             VBM_Tx_Message_Loaded(msg_handle);
           }
           else
           {
             VBM_Set_Msg_Pending(msg_handle);
           }

           CAN_Handler_Enable_Interrupts();
//           HWCAN_Enable_TX_CAN_Interrupts(0); 
		   
           #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
           CAN_Handler_Enable_Global_Interrupts();
           #endif                             
       }
  }
  else
  {
     Appl_CAN_Handler_Channel_Not_Initialized(channel_num);
  }
  return(transmit_status);
}

/******************************************************************************
* Prototype:  VBM_Get_Tx_Virtual_Buffer_Status                                *
* Arguments passed: message handle                                            *
* Return type: BUFFER_NOT_FULL/ BUFFER_FULL                                   *
* Functionality:This function is called by VBM_Tx_Message before writing txdata*
* This function shall return BUFFER_NOT_FULL if transmit buffer is available  *
* for storing message data bytes.Otherwise  function shall return BUFFER_FULL *
*******************************************************************************/
 canbool8_t VBM_Get_Tx_Virtual_Buffer_Status(canuint8_t msg_handle)
{
  canbool8_t virtual_buffer_status;

  virtual_buffer_status = INVALID_REQUEST_TX;

  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
     #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
     if(TX_FIFO_MESSAGE == VBM_Tx_Msg_Parameter_Table[msg_handle].Tx_Msg_Type_Realtime_or_FIFO)
     {
        virtual_buffer_status = transmit_buffer[msg_handle].buffer_status;
     }
     else
     {
       virtual_buffer_status = TX_BUFFER_NOT_FULL;
     }
     #else
     virtual_buffer_status = TX_BUFFER_NOT_FULL;
     #endif
   }
   return(virtual_buffer_status); 
}

/*******************************************************************************
* Prototype: VBM_Get_Tx_Buffer_Address_For_Driver                              *
* Arguments passed:  message handle                                            *
* Return type: Buffer address for tx                                           *
* Functionality: The driver layer  invokes this function in the Transmit ISR   *
* to copy tx message data bytes of pending message(s). This API returns base   *
* address of the data bytes of pending message(s) in the Tx virtual buffer     *
*******************************************************************************/
#define INVALID_ADDRESS 0xFFFF;
canuint8_t* VBM_Get_Tx_Buffer_Address_For_Driver(canuint8_t msg_handle)
{
  transmit_buffer_T * Pointer_to_Tx_Buffer;
  const VBM_Transmit_Msg_Parameter_T * Pointer_to_Tx_Parameter_Struct;
  canuint8_t* buffer_address;

  buffer_address = (canuint8_t*)INVALID_ADDRESS;

  Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
  Pointer_to_Tx_Parameter_Struct = &VBM_Tx_Msg_Parameter_Table[msg_handle];

  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
     #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
     if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
     {
        buffer_address = (canuint8_t*)(Pointer_to_Tx_Buffer->data_base_address + 
                                       Pointer_to_Tx_Buffer->out_index * 
                                       Pointer_to_Tx_Parameter_Struct->message_length_dlc);
     }
     else
     {
        buffer_address = (canuint8_t*)Pointer_to_Tx_Buffer->data_base_address;
     }
     #else
        buffer_address =(canuint8_t*)Pointer_to_Tx_Buffer->data_base_address;
     #endif
     }
     return(buffer_address); 
}

#ifndef J1939_PROTOCOL_IS_USED
/******************************************************************************
* Prototype:  VBM_Get_Tx_Buffer_Address_For_Appl                              *
* Arguments passed:  message handle                                           *
* Return type: Buffer address for tx                                          *
* Functionality: The upper layer, to write tx message data bytes, invokes     *
* VBM_Get_Tx_Buffer_Address (). This API returns buffer_base address for      *
* REALTIME_MESSAGE                                                            *
*******************************************************************************/
#define INVALID_ADDRESS 0xFFFF;
canuint8_t* VBM_Get_Tx_Buffer_Address_For_Appl(canuint8_t msg_handle)
{
  canuint8_t* buffer_address;

  buffer_address = (canuint8_t*)INVALID_ADDRESS;

  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
     buffer_address =(canuint8_t*)transmit_buffer[msg_handle].data_base_address;
  }
     return((canuint8_t*)buffer_address); 
}
#endif
/*****************************************************************************
* Prototype:  VBM_Set_Msg_Pending                                            *
* Arguments passed:  message handle                                          *
* Return type:none                                                           *
* Functionality: The upper layer, after writing into the VBM buffer using    *
* VBM_Get_Tx_Buffer_Address_For_Appl (only for REALTIME messages), should set*
* the new_message pending flag for transmitting the message using this API   *
*******************************************************************************/
void VBM_Set_Msg_Pending(canuint8_t msg_handle)
{
  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
   transmit_buffer[msg_handle].message_pending = NEW_MESSAGE_PENDING;
  }
}

#ifndef J1939_PROTOCOL_IS_USED
/******************************************************************************
* Prototype:  VBM_Tx_Request                                                  *
* Arguments passed:  message handle                                           *
* Return type: transmit status                                                *
* Functionality:The upper layer, to transmit a message, can copy data bytes   *
* in the vbm buffer by calling VBM_Get_Tx_Buffer_Address_For_Appl.Then set the*
* message_pending flag using VBM_Set_Msg_Pending(), and initiate Tx by calling*
* VBM_Tx_Request(). (Ths feature is applicable to REALTIME messages only)     *
*******************************************************************************/
canbool8_t VBM_Tx_Request(canuint8_t msg_handle)
{
  canuint8_t channel_num;
  transmit_buffer_T * Pointer_to_Tx_Buffer;
  canuint8_t* vbm_tx_data_ptr;
   
  canbool8_t transmit_status = TRANSMIT_FAILURE;

  channel_num = VBM_Tx_Msg_Parameter_Table[msg_handle].channel_number;

  if(INITIALIZED == Is_CAN_Handler_Initialized(channel_num))
  {
       Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
      
       if((Size_Of_Transmit_Param_Table > msg_handle)
          ||(PARTIALLY_NOT_OFFLINE==Pointer_to_Tx_Buffer->partially_offline))
       {   
           #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
           CAN_Handler_Disable_Global_Interrupts();
           #endif

           vbm_tx_data_ptr = VBM_Get_Tx_Buffer_Address_For_Appl(msg_handle);
           
           VBM_Update_Tx_Virtual_Buffer_Status(msg_handle);
           transmit_status = CD_Tx_Message(channel_num, msg_handle,vbm_tx_data_ptr);

           if(TRANSMIT_SUCCESS == transmit_status)
           {
             VBM_Tx_Message_Loaded(msg_handle);
           }
           else
           {
             VBM_Set_Msg_Pending(msg_handle);
           }

           #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
           CAN_Handler_Enable_Global_Interrupts();
           #endif       
       }
  }
  else
  {
     Appl_CAN_Handler_Channel_Not_Initialized(channel_num);
  }
  return(transmit_status);
}
#endif
/******************************************************************************
* Prototype:  VBM_Update_Tx_Virtual_Buffer_Status                             *
* Arguments passed:  message handle                                           *
* Return type: none                                                           *
* Functionality: This function is called by VBM_Tx_Message/VBM_Tx_Request.This*
* function sets message_pending and (if FIFO)update in_index of the msg buffer*
*******************************************************************************/
 void VBM_Update_Tx_Virtual_Buffer_Status(canuint8_t msg_handle)
{
  transmit_buffer_T * Pointer_to_Tx_Buffer;
  const VBM_Transmit_Msg_Parameter_T * Pointer_to_Tx_Parameter_Struct;

  Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
  Pointer_to_Tx_Parameter_Struct = &VBM_Tx_Msg_Parameter_Table[msg_handle];

  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
     #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
     if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
     {
        Pointer_to_Tx_Buffer->in_index++; 
        if(Pointer_to_Tx_Buffer->in_index == Pointer_to_Tx_Parameter_Struct->buffer_depth)
        {
           Pointer_to_Tx_Buffer->in_index =0;
        }
        if(Pointer_to_Tx_Buffer->in_index == Pointer_to_Tx_Buffer->out_index)
        {
           Pointer_to_Tx_Buffer->buffer_status = TX_BUFFER_FULL;
        }
     }
     #endif
  }
}

/******************************************************************************
* Prototype:  VBM_Get_Next_Tx_Msg_Num_If_Pending                              *
* Arguments passed: channel number                                            *
* Return type: msg handle                                                     *
* Functionality: Returns the transmit message number if a message to be       *
* transmitted is pending in the Virtual Buffer Management Layer.              *
*******************************************************************************/
canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending (canuint8_t channel_num)
{
  canuint8_t index, start_index, end_index, msg_num;

  msg_num = ID_NOT_FOUND;

  if(channel_num == 0)
  {
    start_index = 0;
    end_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;
  }
  else if(channel_num == 1)
  {
    start_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0;
    end_index = start_index + NUMBER_OF_TX_MSG_SUPPORTED_CH1 -1;
  }
  else if(channel_num == 2)
  {
    start_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 + 
                  NUMBER_OF_TX_MSG_SUPPORTED_CH1;
    end_index = start_index + NUMBER_OF_TX_MSG_SUPPORTED_CH2 - 1;
  }
  else 
  {
    start_index = 0;
    end_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;
  }
  
  for (index = start_index; index <= end_index; index++)
  {
    if(NEW_MESSAGE_PENDING == transmit_buffer[index].message_pending)
    {
       msg_num = index;
       break;
    }
  }
 
   return (msg_num);
}

#ifdef CHECK_PENDING_Tx_MSGS_FOR_SLEEP_STATE
   
Boolean_Returnvalue_T VBM_Is_Any_Message_Pending(canuint8_t channel_number)
{
      canuint8_t index, start_index, end_index, result;
   
     result = cbFALSE;
   
     if(channel_number == 0)
     {
       start_index = 0;
       end_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;
     }
     else if(channel_number == 1)
     {
       start_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0;
       end_index = start_index + NUMBER_OF_TX_MSG_SUPPORTED_CH1 -1;
     }
     else if(channel_number == 2)
     {
       start_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 + 
                     NUMBER_OF_TX_MSG_SUPPORTED_CH1;
       end_index = start_index + NUMBER_OF_TX_MSG_SUPPORTED_CH2 - 1;
     }
     else 
     {
       start_index = 0;
       end_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;
     }
     
     for (index = start_index; index <= end_index; index++)
     {
       if(NEW_MESSAGE_PENDING == transmit_buffer[index].message_pending)
       {
          result = cbTRUE;
          break;
       }
     }
 
   return (result);

}
   
#endif


/*            Separate Channel wise APIs to reduce ISR timing               */
#ifdef CAN_CH0_SELECTED
canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch0(void)
{
  canuint8_t index, start_index, end_index, msg_num;

  msg_num = ID_NOT_FOUND;

    start_index = 0;
    end_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;

  for (index = start_index; index <= end_index; index++)
  {
    if(NEW_MESSAGE_PENDING == transmit_buffer[index].message_pending)
    {
       msg_num = index;
       break;
    }
  }
  return (msg_num);
}

canbool8_t VBM_Check_if_All_Mess_Are_Pending_Ch0(void)
{
  canuint8_t index, start_index, end_index, result;

  result = cbFALSE;

    start_index = 0;
    end_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;

  for (index = start_index; index <= end_index; index++)
  {
    if(NEW_MESSAGE_PENDING != transmit_buffer[index].message_pending)
    {
       break;
    }
  }

  if(index == end_index+1)
  result = cbTRUE;


  return (result);
}

#endif
#ifdef CAN_CH1_SELECTED
canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch1(void)
{
  canuint8_t index, start_index, end_index, msg_num;

  msg_num = ID_NOT_FOUND;

    start_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0;
    end_index = start_index + NUMBER_OF_TX_MSG_SUPPORTED_CH1 -1;

  for (index = start_index; index <= end_index; index++)
  {
    if(NEW_MESSAGE_PENDING == transmit_buffer[index].message_pending)
    {
       msg_num = index;
       break;
    }
  }
  return (msg_num);
}
#endif
#ifdef CAN_CH2_SELECTED
canuint8_t VBM_Get_Next_Tx_Msg_Num_If_Pending_Ch2(void)
{
  canuint8_t index, start_index, end_index, msg_num;

  msg_num = ID_NOT_FOUND;

    start_index = NUMBER_OF_TX_MSG_SUPPORTED_CH0 + 
                  NUMBER_OF_TX_MSG_SUPPORTED_CH1;
    end_index = start_index + NUMBER_OF_TX_MSG_SUPPORTED_CH2 - 1;

  for (index = start_index; index <= end_index; index++)
  {
    if(NEW_MESSAGE_PENDING == transmit_buffer[index].message_pending)
    {
       msg_num = index;
       break;
    }
  }
  return (msg_num);
}
#endif


/******************************************************************************
* Prototype: VBM_Get_Tx_Message_ID                                            *
* Arguments passed:  message handle                                           *
* Return type: ID of the message                                              *
* Functionality : The driver should call this function to get message ID      *
* of the transmit message.                                                    *
******************************************************************************/
Msg_ID_T VBM_Get_Tx_Message_ID(canuint8_t msg_handle)
{
  Msg_ID_T tx_msg_id;

  tx_msg_id = ID_NOT_FOUND;
  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
    #ifdef J1939_PROTOCOL_IS_USED
    tx_msg_id = transmit_buffer[msg_handle].message_ID;
    #else
    tx_msg_id = VBM_Tx_Msg_Parameter_Table[msg_handle].message_ID;
    #endif
  }
  return(tx_msg_id);
}

/******************************************************************************
* Prototype: VBM_Get_Tx_Message_ID                                            *
* Arguments passed:  message handle                                           *
* Return type: ID of the message                                              *
* Functionality : The driver should call this function to get message ID      *
* of the transmit message.                                                    *
******************************************************************************/


  //tx_msg_id = ID_NOT_FOUND;
/******************************************************************************
* Prototype: VBM_Get_Tx_Message_ID_Type                                       *
* Arguments passed:  message handle                                           *
* Return type: ID Type of the message                                         *
* Functionality :The driver should call this function to get ID type of the   *
* transmit message.                                                           *
******************************************************************************/
Msg_ID_Type_T VBM_Get_Tx_Message_ID_Type(canuint8_t msg_handle)
{
  Msg_ID_Type_T tx_id_type;

  tx_id_type = ID_TYPE_NOT_FOUND;

  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
     #ifdef J1939_PROTOCOL_IS_USED
     tx_id_type = EXTENDED_ID;
     #else
     tx_id_type = VBM_Tx_Msg_Parameter_Table[msg_handle].message_ID_Type;
     #endif
  }
  return(tx_id_type);
}

/******************************************************************************
* Function Name : VBM_Get_Tx_Message_DLC                                      *
* Arguments passed :  message handle                                          *
* Return value : dlc of message                                               *
* Functionality : The driver should call this function to get the             *
* message length of the transmit message.                                     *
******************************************************************************/
canuint8_t VBM_Get_Tx_Message_DLC(canuint8_t msg_handle)
{
   canuint8_t tx_dlc;

   tx_dlc = VBM_Tx_Msg_Parameter_Table[msg_handle].message_length_dlc;

   if(TX_VARIABLE_DLC == tx_dlc)
   {
     #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
     if(TX_FIFO_MESSAGE == VBM_Tx_Msg_Parameter_Table[msg_handle].Tx_Msg_Type_Realtime_or_FIFO)
     {
        tx_dlc = *(transmit_buffer[msg_handle].data_base_address 
                +(transmit_buffer[msg_handle].out_index * TX_VARIABLE_DLC + 8));
     }
     else
     {
        tx_dlc = *(transmit_buffer[msg_handle].data_base_address + 8);
     }
     #else
     tx_dlc = *(transmit_buffer[msg_handle].data_base_address + 8);
     #endif
   }
   return(tx_dlc);
}

/******************************************************************************
* Prototype: VBM_Tx_Message_Loaded                                            *
* Arguments passed:  message_handle                                           *
* Return type: None                                                           *
* Functionality: This function shall be called after loading transmit message *
* to the hardware message buffer, so that out_index of the message is updated.*
******************************************************************************/
void VBM_Tx_Message_Loaded (canuint8_t msg_handle)
{
  transmit_buffer_T * Pointer_to_Tx_Buffer;
  const VBM_Transmit_Msg_Parameter_T * Pointer_to_Tx_Parameter_Struct;

  Pointer_to_Tx_Buffer = &transmit_buffer[msg_handle];
  Pointer_to_Tx_Parameter_Struct = &VBM_Tx_Msg_Parameter_Table[msg_handle];

  if (Size_Of_Transmit_Param_Table > msg_handle)
  {
     #ifdef FIFO_BUFFERS_NEEDED_FOR_TX
     if(TX_FIFO_MESSAGE == Pointer_to_Tx_Parameter_Struct->Tx_Msg_Type_Realtime_or_FIFO)
     {
        Pointer_to_Tx_Buffer->out_index++; 
        if(Pointer_to_Tx_Buffer->out_index == Pointer_to_Tx_Parameter_Struct->buffer_depth)
        {
           Pointer_to_Tx_Buffer->out_index =0;
        }
        if(TX_BUFFER_FULL == Pointer_to_Tx_Buffer->buffer_status)
        {
           Pointer_to_Tx_Buffer->buffer_status = TX_BUFFER_NOT_FULL;
        }
        if(Pointer_to_Tx_Buffer->out_index == Pointer_to_Tx_Buffer->in_index)
        {
           Pointer_to_Tx_Buffer->message_pending = NO_NEW_MESSAGE_PENDING;
        }
     }
     else
     {
       Pointer_to_Tx_Buffer->message_pending = NO_NEW_MESSAGE_PENDING;
     }
     #else
     Pointer_to_Tx_Buffer->message_pending = NO_NEW_MESSAGE_PENDING;
     #endif
  }
}

/******************************************************************************
* Prototype: VBM_Execute_Tx_Notifier_Functions                                *
* Arguments passed:  message handle                                           *
* Return type: void                                                           *
* Functionality : This function executes the notifier function pointer for    *
*the transmitted message(s).                                                  *
******************************************************************************/
void VBM_Execute_Tx_Notifier_Functions(canuint8_t channel_num) 
{
   canuint8_t msg_handle;
   
   #ifdef TRANSMIT_INTERRUPT_MODE
   msg_handle = Previous_Tx_Message_Int[channel_num];
   if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)
   {
       (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
   }
   #else
   canuint8_t temp_index;

   for(temp_index =0; temp_index < tx_msg_handle_index[channel_num]; 
       temp_index++)
   {
      msg_handle = Previous_Tx_Message_Poll[channel_num][temp_index];
      if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle]. notifier_function_ptr)
      {
         (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
       }  
   }
   tx_msg_handle_index[channel_num] =0;
   #endif
}
/*              Separate channel wise APIs to reduce ISR timing             */
#ifdef CAN_CH0_SELECTED
void VBM_Execute_Tx_Notifier_Functions_Ch0(void)
{
   canuint8_t msg_handle;
   
   #ifdef TRANSMIT_INTERRUPT_MODE
   msg_handle = Previous_Tx_Message_Int[0];
   if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)
   {
       (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
   }
   #else
   canuint8_t temp_index;

   for(temp_index =0; temp_index < tx_msg_handle_index[0]; 
       temp_index++)
   {
      msg_handle = Previous_Tx_Message_Poll[0][temp_index];
      if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle]. notifier_function_ptr)
      {
         (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
       }  
   }
   tx_msg_handle_index[0] =0;
   #endif
}
#endif

#ifdef CAN_CH1_SELECTED
void VBM_Execute_Tx_Notifier_Functions_Ch1(void)
{
   canuint8_t msg_handle;
   
   #ifdef TRANSMIT_INTERRUPT_MODE
   msg_handle = Previous_Tx_Message_Int[1];
   if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)
   {
       (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
   }
   #else
   canuint8_t temp_index;

   for(temp_index =0; temp_index < tx_msg_handle_index[1]; 
       temp_index++)
   {
      msg_handle = Previous_Tx_Message_Poll[1][temp_index];
      if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle]. notifier_function_ptr)
      {
         (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
       }  
   }
   tx_msg_handle_index[1] =0;
   #endif
}
#endif

#ifdef CAN_CH2_SELECTED
void VBM_Execute_Tx_Notifier_Functions_Ch2(void)
{
   canuint8_t msg_handle;
   
   #ifdef TRANSMIT_INTERRUPT_MODE
   msg_handle = Previous_Tx_Message_Int[2];
   if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)
   {
       (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
   }
   #else
   canuint8_t temp_index;

   for(temp_index =0; temp_index < tx_msg_handle_index[2]; 
       temp_index++)
   {
      msg_handle = Previous_Tx_Message_Poll[2][temp_index];
      if(NULL_NOTIFIER_FUNCTION_POINTER != VBM_Tx_Msg_Parameter_Table[msg_handle]. notifier_function_ptr)
      {
         (*VBM_Tx_Msg_Parameter_Table[msg_handle].notifier_function_ptr)();
       }  
   }
   tx_msg_handle_index[2] =0;
   #endif
}
#endif

/******************************************************************************
* Prototype: VBM_Update_Tx_Msg_Handle_Info                                    *
* Arguments passed:  channel_num, message handle                              *
* Return type: void                                                           *
* Functionality : This function updates msg handle info for notifier function *
******************************************************************************/
void VBM_Update_Tx_Msg_Handle_Info(canuint8_t channel_num, 
                                   canuint8_t tx_message_handle)
{
   #ifdef TRANSMIT_INTERRUPT_MODE
   Previous_Tx_Message_Int[channel_num] = tx_message_handle;
   #else
   if(tx_msg_handle_index[channel_num] <  MAX_TX_MSG_PER_LOOP_FOR_POLL)
   {
      Previous_Tx_Message_Poll[channel_num][tx_msg_handle_index[channel_num]] = tx_message_handle;
      tx_msg_handle_index[channel_num]++;
   }
   else
   {
      Appl_Poll_Tx_Msgs_Per_Loop_Overrun();
   }
   #endif
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/

