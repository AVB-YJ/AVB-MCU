/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - VBM                                                        *
 * File Name:  can_vbm_rx.c                                                  *
 * File Description:                                                         *
 * This file contains: get and set functions to access Receive Parameter     *
 * tables, validate received message and execute notifier functions on       *
 * successful reception of messages                                          *
 *****************************************************************************/
#include "can_handler.h"
#include "can_vbm_rx.h"
#include "can_vbm_config.h"
#include "can_drv_init_misc.h"
#ifdef CAN_CH0_SELECTED
static receive_buffer_T receive_buffer_Ch0[NUMBER_OF_RX_MSG_SUPPORTED_CH0];
#endif
#ifdef CAN_CH1_SELECTED
static receive_buffer_T receive_buffer_Ch1[NUMBER_OF_RX_MSG_SUPPORTED_CH1];
#endif
#ifdef CAN_CH2_SELECTED
static receive_buffer_T receive_buffer_Ch2[NUMBER_OF_RX_MSG_SUPPORTED_CH2];
#endif

receive_buffer_T * receive_buffers[]=
{
  #ifdef CAN_CH0_SELECTED
  receive_buffer_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  receive_buffer_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  receive_buffer_Ch2
  #endif
};

#ifdef CAN_CH0_SELECTED
static canuint8_t Rx_Buffer_Block_Ch0 [TOTAL_BYTES_FOR_RX_DATA_BUFFER_CH0];
#endif
#ifdef CAN_CH1_SELECTED
static canuint8_t Rx_Buffer_Block_Ch1 [TOTAL_BYTES_FOR_RX_DATA_BUFFER_CH1];
#endif
#ifdef CAN_CH2_SELECTED
static canuint8_t Rx_Buffer_Block_Ch2 [TOTAL_BYTES_FOR_RX_DATA_BUFFER_CH2];
#endif

static canuint8_t * Rx_Buffer_Pointers[]=
{
  #ifdef CAN_CH0_SELECTED
  Rx_Buffer_Block_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  Rx_Buffer_Block_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  Rx_Buffer_Block_Ch2
  #endif
};    

const VBM_Receive_Msg_Parameter_T *VBM_Rx_Msg_Parameter_Tables[]=
{
  #ifdef CAN_CH0_SELECTED
  VBM_Rx_Msg_Parameter_Table_Ch0,
  #endif
  #ifdef CAN_CH1_SELECTED
  VBM_Rx_Msg_Parameter_Table_Ch1,
  #endif
  #ifdef CAN_CH2_SELECTED
  VBM_Rx_Msg_Parameter_Table_Ch2
  #endif
};


/*******************************************************************************
*******              STATIC FUNCTION DECLARATIONS                        *******
*******************************************************************************/
 canuint8_t* Get_Rx_Msg_Data_Base_Ptr(canuint8_t channel_number, 
                                       canuint16_t requested_allocation_in_bytes);
 function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer(
                          canuint8_t channel_num, canuint8_t msg_handle);
#ifdef CAN_CH0_SELECTED
 function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer_Ch0(
                          canuint8_t msg_handle);
#endif
#ifdef CAN_CH1_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer_Ch1(
                          canuint8_t msg_handle);
#endif
#ifdef CAN_CH2_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer_Ch2(
                          canuint8_t msg_handle);
#endif

 function_pointer_T VBM_Get_Rx_Notifier_Overrun(canuint8_t channel_num,
                                                      canuint8_t msg_handle);
#ifdef CAN_CH0_SELECTED
 function_pointer_T VBM_Get_Rx_Notifier_Overrun_Ch0(
                                                      canuint8_t msg_handle);
#endif
#ifdef CAN_CH1_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Overrun_Ch1(
                                                      canuint8_t msg_handle);
#endif
#ifdef CAN_CH2_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Overrun_Ch2(
                                                      canuint8_t msg_handle);
#endif


/*******************************************************************************
*******              I N I T I A L I Z A T I O N                        *******
*******************************************************************************/

/*******************************************************************************
* Prototype: VBM_Cold_Initialization_Rx                                        *
* Arguments:  channel number                                                   *
* Return type: void                                                            *
* Functionality: This function initializes the receive software buffers defined*
* in the Virtual Buffer Management Layer for the requested channel, by clearing*
* flags in the receive buffer and getting the base address of Rx data buffers  *
* of all Rx messages on the given channel                                      *
*******************************************************************************/
void VBM_Cold_Initialization_Rx (canuint8_t channel_number)
{
   canuint8_t msg_handle;


   const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;
   receive_buffer_T * Pointer_to_Rx_Buffer;

   msg_handle = Size_Of_Receive_Param_Tables[channel_number]-1;
   if(receive_buffers[channel_number][msg_handle].data_base_address == 
       (Rx_Buffer_Pointers[channel_number] - TOTAL_BYTES_FOR_LAST_RX_DATA_BUFFER))
   {
      Rx_Buffer_Pointers[channel_number] = receive_buffers[channel_number][0].data_base_address;
   }
   for(msg_handle=0;msg_handle<Size_Of_Receive_Param_Tables[channel_number];
       msg_handle++)
   {

	 Pointer_to_Rx_Buffer = &receive_buffers[channel_number][msg_handle];
	 Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables	
	                                    [channel_number][msg_handle]; 		
     #ifdef FIFO_BUFFERS_NEEDED_FOR_RX 
     if(RX_FIFO_MESSAGE == Pointer_to_Rx_Parameter_Struct->
                              Rx_Msg_Type_Realtime_or_FIFO)
     {
	   Pointer_to_Rx_Buffer->data_base_address =
       Get_Rx_Msg_Data_Base_Ptr(channel_number,
       (Pointer_to_Rx_Parameter_Struct->message_length_dlc)
        *(Pointer_to_Rx_Parameter_Struct->buffer_depth));
     }
     else
     {
	   Pointer_to_Rx_Buffer->data_base_address =
       Get_Rx_Msg_Data_Base_Ptr(channel_number,
       (Pointer_to_Rx_Parameter_Struct->message_length_dlc));
     }
     #else
	 Pointer_to_Rx_Buffer->data_base_address =
     Get_Rx_Msg_Data_Base_Ptr(channel_number,
     (Pointer_to_Rx_Parameter_Struct->message_length_dlc));
     #endif

     Pointer_to_Rx_Buffer->new_message = NO_NEW_MESSAGE_AVAILABLE;

     #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
       Pointer_to_Rx_Buffer->in_index  = 0;
       Pointer_to_Rx_Buffer->out_index  = 0;
       Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_EMPTY;
     #endif
   }
}

/*******************************************************************************
* Prototype: Get_Rx_Msg_Data_Base_Ptr                                          *
* Arguments passed: channel no, requested_allocation_in_bytes                  *
* Return type: Data Base Address                                               *
* Functionality: This function allocates memory to the receive buffers and     *
   returns the base_address for every receive message virtual buffer.          *
*******************************************************************************/
 canuint8_t* Get_Rx_Msg_Data_Base_Ptr(canuint8_t channel_number,
                              canuint16_t requested_allocation_in_bytes)
{
  canuint8_t *allocation_pointer = ( canuint8_t * )Rx_Buffer_Pointers[channel_number];
  Rx_Buffer_Pointers[channel_number] = ( canuint8_t * )
  (Rx_Buffer_Pointers[channel_number] + requested_allocation_in_bytes);
  return(allocation_pointer);
}

/*******************************************************************************
* Prototype: VBM_Warm_Initialization_Rx                                        *
* Arguments passed:  channel number                                            *
* Return type: None                                                            *
* Functionality: This function should be called in the warm initialization     *
* routine of the application. This function clears the 'new_message' flag,     *
* in_index, out_index (if FIFO Rx messages supported), of all receive buffers  *
*******************************************************************************/
void VBM_Warm_Initialization_Rx (canuint8_t channel_number)
{
   canuint8_t msg_handle;
   receive_buffer_T * Pointer_to_Rx_Buffer;

  for(msg_handle=0;msg_handle<Size_Of_Receive_Param_Tables[channel_number];
      msg_handle++)
   {
     Pointer_to_Rx_Buffer = &receive_buffers[channel_number][msg_handle];
     Pointer_to_Rx_Buffer->new_message = NO_NEW_MESSAGE_AVAILABLE;

     #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
     Pointer_to_Rx_Buffer->in_index  = 0;
     Pointer_to_Rx_Buffer->out_index  = 0;
     Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_EMPTY;
     #endif
   }
}

/*******************************************************************************
*******                        R E C E I V E                             *******
*******************************************************************************/
#ifdef J1939_PROTOCOL_IS_USED
canbool8_t VBM_Validate_J1939_Rx_Msg (canuint8_t channel_num, canuint32_t Msg_ID,
                                       canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity = MESSAGE_INVALID;
  canuint8_t count;
  canuint32_t temp_ID;
  canuint32_t* Valid_IDs_Address;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = 
               &VBM_Rx_Msg_Parameter_Tables[channel_num][msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
    {
      Valid_IDs_Address = Pointer_to_Rx_Parameter_Struct->ID_array; 
      for(count = 0; count < Pointer_to_Rx_Parameter_Struct->
          no_of_valid_IDs_for_PGN; count++)
         {      
            temp_ID = Msg_ID & (Pointer_to_Rx_Parameter_Struct->mask);
            if(temp_ID != (*Valid_IDs_Address))
              {
                Valid_IDs_Address++;
              }
            else
              {
                message_validity = MESSAGE_VALID;
                receive_buffers[channel_num][msg_handle].message_ID = 
                                                                   Msg_ID;
                break;
              }
         }
     }
return(message_validity);
}
/*                 Separate APIs to reduce ISR Timing                      */
#ifdef CAN_CH0_SELECTED
canbool8_t VBM_Validate_J1939_Rx_Msg_Ch0(canuint32_t 
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity = MESSAGE_INVALID;
  canuint8_t count;
  canuint32_t temp_ID;
  canuint32_t* Valid_IDs_Address;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = 
               &VBM_Rx_Msg_Parameter_Tables[0][msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc >= Pointer_to_Rx_Parameter_Struct->message_length_dlc))
    {
      Valid_IDs_Address = Pointer_to_Rx_Parameter_Struct->ID_array; 
      for(count = 0; count < Pointer_to_Rx_Parameter_Struct->
          no_of_valid_IDs_for_PGN; count++)
         {      
            temp_ID = Msg_ID & (Pointer_to_Rx_Parameter_Struct->mask);
            if(temp_ID != (*Valid_IDs_Address))
              {
                Valid_IDs_Address++;
              }
            else
              {
                message_validity = MESSAGE_VALID;
                receive_buffer_Ch0[msg_handle].message_ID = Msg_ID;
                break;
              }
         }
     }
return(message_validity);
}
#endif
#ifdef CAN_CH1_SELECTED
canbool8_t VBM_Validate_J1939_Rx_Msg_Ch1(canuint32_t 
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity = MESSAGE_INVALID;
  canuint8_t count;
  canuint32_t temp_ID;
  canuint32_t* Valid_IDs_Address;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = 
               &VBM_Rx_Msg_Parameter_Tables[1][msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
    {
      Valid_IDs_Address = Pointer_to_Rx_Parameter_Struct->ID_array; 
      for(count = 0; count < Pointer_to_Rx_Parameter_Struct->
          no_of_valid_IDs_for_PGN; count++)
         {      
            temp_ID = Msg_ID & (Pointer_to_Rx_Parameter_Struct->mask);
            if(temp_ID != (*Valid_IDs_Address))
              {
                Valid_IDs_Address++;
              }
            else
              {
                message_validity = MESSAGE_VALID;
                receive_buffer_Ch1[msg_handle].message_ID = Msg_ID;
                break;
              }
         }
     }
return(message_validity);
}
#endif
#ifdef CAN_CH2_SELECTED
canbool8_t VBM_Validate_J1939_Rx_Msg_Ch2(canuint32_t 
                               Msg_ID, canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity = MESSAGE_INVALID;
  canuint8_t count;
  canuint32_t temp_ID;
  canuint32_t* Valid_IDs_Address;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = 
               &VBM_Rx_Msg_Parameter_Tables[2][msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
    {
      Valid_IDs_Address = Pointer_to_Rx_Parameter_Struct->ID_array; 
      for(count = 0; count < Pointer_to_Rx_Parameter_Struct->
          no_of_valid_IDs_for_PGN; count++)
         {      
            temp_ID = Msg_ID & (Pointer_to_Rx_Parameter_Struct->mask);
            if(temp_ID != (*Valid_IDs_Address))
              {
                Valid_IDs_Address++;
              }
            else
              {
                message_validity = MESSAGE_VALID;
                receive_buffer_Ch2[msg_handle].message_ID = Msg_ID;
                break;
              }
         }
     }
return(message_validity);
}
#endif

#else
/*******************************************************************************
* Prototype:  VBM_Validate_Rx_Msg_With_Mask                                    *
* Arguments passed:channel number, Id of message, IDtype, DLC                  *
* Return type: msg handle                                                      *
* Functionality: This function validates the received message with respect to  *
* ID, ID type and DLC. If the message is a valid message, the corresponding    *
* message number shall be returned. For invalid message, the return value      *
* shall be INVALID_RX_MSG_ID, INVALID_RX_MSG_ID_TYPE, and INVALID_RX_MSG_DLC   *
* depending on the unmatched parameter.                                        *
*******************************************************************************/
canuint8_t VBM_Validate_Rx_Msg_With_Mask(canuint8_t channel_num, Msg_ID_T ID, 
              Msg_ID_Type_T ID_Type, canuint8_t dlc)
{
  canuint8_t msg_handle;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  if(0 == channel_num)
  {
    #ifdef CAN_CH0_HASH_SEARCH
      msg_handle = CAN_Hash_Search(channel_num, ID);
    #else 
       #ifdef CAN_CH0_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(channel_num, ID, HWCAN_RECEIVE);
       #endif
    #endif
  }
  else if(1 == channel_num)
  {
    #ifdef CAN_CH1_HASH_SEARCH
      msg_handle = CAN_Hash_Search(channel_num, ID);
    #else 
       #ifdef CAN_CH1_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(channel_num, ID, HWCAN_RECEIVE);
       #endif
    #endif
  }
  else if(2 == channel_num)
  {
    #ifdef CAN_CH2_HASH_SEARCH
      msg_handle = CAN_Hash_Search(channel_num, ID);
    #else
       #ifdef CAN_CH2_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(channel_num, ID, HWCAN_RECEIVE);
       #endif
    #endif
  }
  else
  {
    #ifdef CAN_CH0_HASH_SEARCH
      msg_handle = CAN_Hash_Search(channel_num, ID);
    #else 
       #ifdef CAN_CH0_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(channel_num, ID, HWCAN_RECEIVE);
       #endif
    #endif
  }

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[channel_num]
                                     [msg_handle];
  if(ID_NOT_FOUND != msg_handle)
  {
      if (ID_Type == Pointer_to_Rx_Parameter_Struct->Msg_ID_Type)
      {
         if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->
             message_length_dlc)
           ||(dlc >= Pointer_to_Rx_Parameter_Struct->message_length_dlc))
         {
           
         }
        else
         {
           msg_handle = DLC_MISMATCH;
         }
      }
      else
      {
         msg_handle = ID_TYPE_MISMATCH;
      }
  }
  else 
  {
   msg_handle =ID_NOT_FOUND;
  }	   
  return(msg_handle);
}

/*                      Separate APIs to reduce ISR Timing                   */
#ifdef CAN_CH0_SELECTED
canuint8_t VBM_Validate_Rx_Msg_With_Mask_Ch0(Msg_ID_T ID, 
              Msg_ID_Type_T ID_Type, canuint8_t dlc)
{
  canuint8_t msg_handle;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

    #ifdef CAN_CH0_HASH_SEARCH
      msg_handle = CAN_Hash_Search(0, ID);
    #else 
       #ifdef CAN_CH0_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(0, ID, HWCAN_RECEIVE);
       #endif
    #endif

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[0]
                                     [msg_handle];
  if(ID_NOT_FOUND != msg_handle)
  {
      if (ID_Type == Pointer_to_Rx_Parameter_Struct->Msg_ID_Type)
      {
         if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->
             message_length_dlc)
           ||(dlc >= Pointer_to_Rx_Parameter_Struct->message_length_dlc))
         {
           
         }
        else
         {
           msg_handle = DLC_MISMATCH;
         }
      }
      else
      {
         msg_handle = ID_TYPE_MISMATCH;
      }
  }
  else 
  {
   msg_handle =ID_NOT_FOUND;
  }	   
  return(msg_handle);
}
#endif
#ifdef CAN_CH1_SELECTED
canuint8_t VBM_Validate_Rx_Msg_With_Mask_Ch1(Msg_ID_T ID, 
              Msg_ID_Type_T ID_Type, canuint8_t dlc)
{
  canuint8_t msg_handle;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

    #ifdef CAN_CH1_HASH_SEARCH
      msg_handle = CAN_Hash_Search(1, ID);
    #else 
       #ifdef CAN_CH1_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(1, ID, HWCAN_RECEIVE);
       #endif
    #endif

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[1]
                                     [msg_handle];
  if(ID_NOT_FOUND != msg_handle)
  {
      if (ID_Type == Pointer_to_Rx_Parameter_Struct->Msg_ID_Type)
      {
         if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->
             message_length_dlc)
           ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
         {
           
         }
        else
         {
           msg_handle = DLC_MISMATCH;
         }
      }
      else
      {
         msg_handle = ID_TYPE_MISMATCH;
      }
  }
  else 
  {
   msg_handle =ID_NOT_FOUND;
  }	   
  return(msg_handle);
}
#endif
#ifdef CAN_CH2_SELECTED
canuint8_t VBM_Validate_Rx_Msg_With_Mask_Ch2(Msg_ID_T ID, 
              Msg_ID_Type_T ID_Type, canuint8_t dlc)
{
  canuint8_t msg_handle;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

    #ifdef CAN_CH2_HASH_SEARCH
      msg_handle = CAN_Hash_Search(2, ID);
    #else
       #ifdef CAN_CH2_BINARY_SEARCH
          msg_handle = CAN_Binary_Search(2, ID, HWCAN_RECEIVE);
       #endif
    #endif

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[2]
                                     [msg_handle];
  if(ID_NOT_FOUND != msg_handle)
  {
      if (ID_Type == Pointer_to_Rx_Parameter_Struct->Msg_ID_Type)
      {
         if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->
             message_length_dlc)
           ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
         {
           
         }
        else
         {
           msg_handle = DLC_MISMATCH;
         }
      }
      else
      {
         msg_handle = ID_TYPE_MISMATCH;
      }
  }
  else 
  {
   msg_handle =ID_NOT_FOUND;
  }	   
  return(msg_handle);
}
#endif

#endif
/*******************************************************************************
* Prototype: VBM_Validate_Rx_Msg_With_No_Mask                                  *
* Arguments passed:channel number, msg_handle, DLC                             *
* Return type: message validity                                                *
* Functionality: This function validates the received message with respect to  *
* DLC. If the message handle of the Rx message without mask is passed, this API*
* checks the received dlc against the dlc in Parameter Table.If the DLCs match *
* or if DLC in Parameter Table is VARIAVBLE_DLC,the message is VALID.          *
* Else it is INVALID                                                           *
*******************************************************************************/
canbool8_t VBM_Validate_Rx_Msg_With_No_Mask(canuint8_t channel_num,
                             canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[channel_num]
                                     [msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
  {
    message_validity = MESSAGE_VALID;
  }
  else
  {
    message_validity = MESSAGE_INVALID;
  }
return(message_validity);
}

/*                   Separate APIs to reduce ISR Timing                       */
#ifdef CAN_CH0_SELECTED
canbool8_t VBM_Validate_Rx_Msg_With_No_Mask_Ch0(
                                       canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[0]
                                     [msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
  {
    message_validity = MESSAGE_VALID;
  }
  else
  {
    message_validity = MESSAGE_INVALID;
  }
return(message_validity);
}
#endif
#ifdef CAN_CH1_SELECTED
canbool8_t VBM_Validate_Rx_Msg_With_No_Mask_Ch1(
                                       canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[1]
                                     [msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
  {
    message_validity = MESSAGE_VALID;
  }
  else
  {
    message_validity = MESSAGE_INVALID;
  }
return(message_validity);
}
#endif
#ifdef CAN_CH2_SELECTED
canbool8_t VBM_Validate_Rx_Msg_With_No_Mask_Ch2(
                                       canuint8_t msg_handle, canuint8_t dlc)
{
  canbool8_t message_validity;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[2]
                                     [msg_handle];

  if((RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    ||(dlc == Pointer_to_Rx_Parameter_Struct->message_length_dlc))
  {
    message_validity = MESSAGE_VALID;
  }
  else
  {
    message_validity = MESSAGE_INVALID;
  }
return(message_validity);
}
#endif

/*******************************************************************************
* Prototype:  VBM_Copy_Rx_Message                                              *
* Arguments:channel number, msg handle, id, dlc, pointer to hardware rx buffer *
* Return type: None                                                            *
* Functionality: If new message flag is set to cbTRUE or if FIFO buffers are     *
* supported and buffers are full, calls application notifier function to       *
* indicate overwrite. Updates message_id , dlc of virtual receive buffer, and  *
* copies the data from CAN hardware to virtual receive data buffer.Then sets   *
* new message flag to cbTRUE.In case of FIFO messages, increments in_index       *
* appropriately                                                                *
*******************************************************************************/
#ifdef  IGNORE_MSG_ID_BITS  
void VBM_Copy_Rx_Message (canuint8_t channel_num, canuint8_t msg_handle, Msg_ID_T ID,
                          canuint8_t dlc, canuint8_t * hw_data_ptr)
#else
void VBM_Copy_Rx_Message (canuint8_t channel_num, canuint8_t msg_handle, canuint8_t dlc,
                          canuint8_t * hw_data_ptr)
#endif
{
  function_pointer_T notifier_fn_ptr_for_Rx_Overwrite;
  canuint8_t* vbm_rx_data_ptr;
  receive_buffer_T * Pointer_to_Rx_Buffer;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  notifier_fn_ptr_for_Rx_Overwrite = NULL_NOTIFIER_FUNCTION_POINTER;
   
  if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
  {
    Pointer_to_Rx_Buffer = &receive_buffers[channel_num][msg_handle];
    Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[channel_num]
                                     [msg_handle];

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      if(RX_BUFFER_FULL == Pointer_to_Rx_Buffer->buffer_status)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun(
                                          channel_num, msg_handle);
      }
    }
    else
    {
      if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun(
                                          channel_num, msg_handle);
      }
    }
    #else
    if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
    {
       notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun(
                                          channel_num, msg_handle);
    }
    #endif
    if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Overwrite)
    {
      (*notifier_fn_ptr_for_Rx_Overwrite)();
    }
    #ifdef  IGNORE_MSG_ID_BITS    
    Pointer_to_Rx_Buffer->message_ID = ID;
    #endif

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Disable_Global_Interrupts();		
     #endif

     //CAN_Handler_Disable_Interrupts();
     HWCAN_Disable_RX_CAN_Interrupts(0);	

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      vbm_rx_data_ptr = (canuint8_t*) (Pointer_to_Rx_Buffer->
      data_base_address+ (Pointer_to_Rx_Buffer->in_index * 
      Pointer_to_Rx_Parameter_Struct->message_length_dlc));
    }
    else
    {
      vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    }
    #else
    vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    #endif

    if(RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    {
      *(vbm_rx_data_ptr + 8) = dlc;
    }
	else
   {
       dlc = Pointer_to_Rx_Parameter_Struct->message_length_dlc;
   }

    switch(dlc) 
    {
      case (8):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (7):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (6):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (5):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (4):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (3):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (2):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (1):
              *vbm_rx_data_ptr = *hw_data_ptr; 
      default :
              break;
    }
    Pointer_to_Rx_Buffer->new_message = NEW_MESSAGE_AVAILABLE;

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      Pointer_to_Rx_Buffer->in_index++;
    
      if (Pointer_to_Rx_Buffer->in_index == 
          Pointer_to_Rx_Parameter_Struct->buffer_depth)
      {
        Pointer_to_Rx_Buffer->in_index = 0;
      }
    
      if(Pointer_to_Rx_Buffer->in_index == Pointer_to_Rx_Buffer->out_index)
      {
        Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_FULL;
      }
    }
    else
    {
    }
    #endif

     CAN_Handler_Enable_Interrupts();
     //HWCAN_Enable_RX_CAN_Interrupts(0);		 

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Enable_Global_Interrupts();
     #endif
  }
}

/*                  Separate APIs to reduce ISR Timing                       */
#ifdef CAN_CH0_SELECTED

#ifdef  IGNORE_MSG_ID_BITS  
void VBM_Copy_Rx_Message_Ch0 (canuint8_t msg_handle, 
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr)
#else
void VBM_Copy_Rx_Message_Ch0 (canuint8_t msg_handle, 
                                 canuint8_t dlc, canuint8_t * hw_data_ptr)
#endif
{
  function_pointer_T notifier_fn_ptr_for_Rx_Overwrite;
  canuint8_t* vbm_rx_data_ptr;
  receive_buffer_T * Pointer_to_Rx_Buffer;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  notifier_fn_ptr_for_Rx_Overwrite = NULL_NOTIFIER_FUNCTION_POINTER;
   
  if(Size_Of_Receive_Param_Tables[0] > msg_handle)
  {
    Pointer_to_Rx_Buffer = &receive_buffers[0][msg_handle];
    Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[0]
                                     [msg_handle];

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      if(RX_BUFFER_FULL == Pointer_to_Rx_Buffer->buffer_status)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch0(
                                           msg_handle);
      }
    }
    else
    {
      if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch0(
                                           msg_handle);
      }
    }
    #else
    if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
    {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch0(
                                           msg_handle);
    }
    #endif
    if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Overwrite)
    {
      (*notifier_fn_ptr_for_Rx_Overwrite)();
    }
    #ifdef  IGNORE_MSG_ID_BITS    
    Pointer_to_Rx_Buffer->message_ID = ID;
    #endif

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Disable_Global_Interrupts();		
     #endif

     //CAN_Handler_Disable_Interrupts();
     HWCAN_Disable_RX_CAN_Interrupts(0);	

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      vbm_rx_data_ptr = (canuint8_t*) (Pointer_to_Rx_Buffer->
      data_base_address+ (Pointer_to_Rx_Buffer->in_index * 
      Pointer_to_Rx_Parameter_Struct->message_length_dlc));
    }
    else
    {
      vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    }
    #else
    vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    #endif

    if(RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    {
      *(vbm_rx_data_ptr + 8) = dlc;
    }
	else
		{
		  dlc = Pointer_to_Rx_Parameter_Struct->message_length_dlc;
		}

    switch(dlc) 
    {
      case (8):
				  *vbm_rx_data_ptr++ = *hw_data_ptr++;
      case (7):
      		  *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (6):
      		  *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (5):
     			  *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (4):
      		  *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (3):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (2):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (1):
              *vbm_rx_data_ptr = *hw_data_ptr; 
      default :
              break;
    }
    Pointer_to_Rx_Buffer->new_message = NEW_MESSAGE_AVAILABLE;

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      Pointer_to_Rx_Buffer->in_index++;
    
      if (Pointer_to_Rx_Buffer->in_index == 
          Pointer_to_Rx_Parameter_Struct->buffer_depth)
      {
        Pointer_to_Rx_Buffer->in_index = 0;
      }
    
      if(Pointer_to_Rx_Buffer->in_index == Pointer_to_Rx_Buffer->out_index)
      {
        Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_FULL;
      }
    }
    else
    {
    }
    #endif

     CAN_Handler_Enable_Interrupts();
    //HWCAN_Enable_RX_CAN_Interrupts(0);		 
     
     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Enable_Global_Interrupts();
     #endif
  }
}

#endif

#ifdef CAN_CH1_SELECTED

#ifdef  IGNORE_MSG_ID_BITS  
void VBM_Copy_Rx_Message_Ch1 (canuint8_t msg_handle, 
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr)
#else
void VBM_Copy_Rx_Message_Ch1 (canuint8_t msg_handle, 
                                 canuint8_t dlc, canuint8_t * hw_data_ptr)
#endif
{
  function_pointer_T notifier_fn_ptr_for_Rx_Overwrite;
  canuint8_t* vbm_rx_data_ptr;
  receive_buffer_T * Pointer_to_Rx_Buffer;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  notifier_fn_ptr_for_Rx_Overwrite = NULL_NOTIFIER_FUNCTION_POINTER;
   
  if(Size_Of_Receive_Param_Tables[1] > msg_handle)
  {
    Pointer_to_Rx_Buffer = &receive_buffers[1][msg_handle];
    Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[1]
                                     [msg_handle];

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      if(RX_BUFFER_FULL == Pointer_to_Rx_Buffer->buffer_status)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch1(
                                           msg_handle);
      }
    }
    else
    {
      if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch1(
                                           msg_handle);
      }
    }
    #else
    if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
    {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch1(
                                           msg_handle);
    }
    #endif
    if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Overwrite)
    {
      (*notifier_fn_ptr_for_Rx_Overwrite)();
    }
    #ifdef  IGNORE_MSG_ID_BITS    
    Pointer_to_Rx_Buffer->message_ID = ID;
    #endif

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Disable_Global_Interrupts();		
     #endif

     CAN_Handler_Disable_Interrupts();	

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      vbm_rx_data_ptr = (canuint8_t*) (Pointer_to_Rx_Buffer->
      data_base_address+ (Pointer_to_Rx_Buffer->in_index * 
      Pointer_to_Rx_Parameter_Struct->message_length_dlc));
    }
    else
    {
      vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    }
    #else
    vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    #endif

    if(RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    {
      *(vbm_rx_data_ptr + 8) = dlc;
    }

    switch(dlc) 
    {
      case (8):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (7):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (6):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (5):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (4):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (3):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (2):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (1):
              *vbm_rx_data_ptr = *hw_data_ptr; 
      default :
              break;
    }
    Pointer_to_Rx_Buffer->new_message = NEW_MESSAGE_AVAILABLE;

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      Pointer_to_Rx_Buffer->in_index++;
    
      if (Pointer_to_Rx_Buffer->in_index == 
          Pointer_to_Rx_Parameter_Struct->buffer_depth)
      {
        Pointer_to_Rx_Buffer->in_index = 0;
      }
    
      if(Pointer_to_Rx_Buffer->in_index == Pointer_to_Rx_Buffer->out_index)
      {
        Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_FULL;
      }
    }
    else
    {
    }
    #endif

     CAN_Handler_Enable_Interrupts();		 

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Enable_Global_Interrupts();
     #endif
  }
}

#endif
#ifdef CAN_CH2_SELECTED

#ifdef  IGNORE_MSG_ID_BITS  
void VBM_Copy_Rx_Message_Ch2 (canuint8_t msg_handle, 
                               Msg_ID_T ID, canuint8_t dlc, canuint8_t * hw_data_ptr)
#else
void VBM_Copy_Rx_Message_Ch2 (canuint8_t msg_handle, 
                                 canuint8_t dlc, canuint8_t * hw_data_ptr)
#endif
{
  function_pointer_T notifier_fn_ptr_for_Rx_Overwrite;
  canuint8_t* vbm_rx_data_ptr;
  receive_buffer_T * Pointer_to_Rx_Buffer;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  notifier_fn_ptr_for_Rx_Overwrite = NULL_NOTIFIER_FUNCTION_POINTER;
   
  if(Size_Of_Receive_Param_Tables[2] > msg_handle)
  {
    Pointer_to_Rx_Buffer = &receive_buffers[2][msg_handle];
    Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[2]
                                     [msg_handle];

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      if(RX_BUFFER_FULL == Pointer_to_Rx_Buffer->buffer_status)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch2(
                                           msg_handle);
      }
    }
    else
    {
      if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
      {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch2(
                                           msg_handle);
      }
    }
    #else
    if(NEW_MESSAGE_AVAILABLE == Pointer_to_Rx_Buffer->new_message)
    {
        notifier_fn_ptr_for_Rx_Overwrite = VBM_Get_Rx_Notifier_Overrun_Ch2(
                                           msg_handle);
    }
    #endif
    if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Overwrite)
    {
      (*notifier_fn_ptr_for_Rx_Overwrite)();
    }
    #ifdef  IGNORE_MSG_ID_BITS    
    Pointer_to_Rx_Buffer->message_ID = ID;
    #endif

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Disable_Global_Interrupts();		
     #endif

     CAN_Handler_Disable_Interrupts();	

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      vbm_rx_data_ptr = (canuint8_t*) (Pointer_to_Rx_Buffer->
      data_base_address+ (Pointer_to_Rx_Buffer->in_index * 
      Pointer_to_Rx_Parameter_Struct->message_length_dlc));
    }
    else
    {
      vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    }
    #else
    vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address; 
    #endif

    if(RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
    {
      *(vbm_rx_data_ptr + 8) = dlc;
    }

    switch(dlc) 
    {
      case (8):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (7):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (6):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (5):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (4):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (3):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (2):
              *vbm_rx_data_ptr++ = *hw_data_ptr++; 
      case (1):
              *vbm_rx_data_ptr = *hw_data_ptr; 
      default :
              break;
    }
    Pointer_to_Rx_Buffer->new_message = NEW_MESSAGE_AVAILABLE;

    #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
    if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                            Rx_Msg_Type_Realtime_or_FIFO)
    {
      Pointer_to_Rx_Buffer->in_index++;
    
      if (Pointer_to_Rx_Buffer->in_index == 
          Pointer_to_Rx_Parameter_Struct->buffer_depth)
      {
        Pointer_to_Rx_Buffer->in_index = 0;
      }
    
      if(Pointer_to_Rx_Buffer->in_index == Pointer_to_Rx_Buffer->out_index)
      {
        Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_FULL;
      }
    }
    else
    {
    }
    #endif

     CAN_Handler_Enable_Interrupts();		 

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Enable_Global_Interrupts();
     #endif
  }
}

#endif


/*******************************************************************************
* Prototype:  VBM_Is_New_Message_Received                                      *
* Arguments: channel_number, receive message handle                            *
* Return type: None                                                            *
* Functionality: This API shall return cbTRUE if a new message flag is set to    *
* cbTRUE. Otherwise it returns cbFALSE. Upper layers should invoke this function   *
* to check if a message of their interest has been received. If the return     *
* value is cbTRUE, the upper layer should call the routine VBM_Get_Message_Data  *
*******************************************************************************/
canbool8_t VBM_Is_New_Message_Received (canuint8_t channel_num, canuint8_t msg_handle)
{
 canbool8_t new_message_status;
 new_message_status = INVALID_REQUEST_RX;
   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
     new_message_status = receive_buffers[channel_num][msg_handle].new_message;
   }
   return(new_message_status);
}

#ifdef J1939_PROTOCOL_IS_USED 
/*******************************************************************************
* Function Name : VBM_Get_Received_Message_ID                                  *
* Arguments passed: channel number, receive message handle                     *
* Return value : Message ID from the run-time table                           *
* Functionality : Returns the ID of the received message                       *
*******************************************************************************/
Msg_ID_T VBM_Get_J1939_Rx_ID(canuint8_t channel_num, canuint8_t msg_handle)
{
 Msg_ID_T rx_id;
 rx_id = INVALID_REQUEST_RX;

   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
     rx_id = receive_buffers[channel_num][msg_handle].message_ID;
   }
   return(rx_id);
}

#else
/*******************************************************************************
* Function Name : VBM_Get_Received_Message_ID                                  *
* Arguments passed: channel number, receive message handle                     *
* Return value : Message ID from the parameter table                           *
* Functionality : Returns the ID of the received message                       *
*******************************************************************************/
Msg_ID_T VBM_Get_Rx_Message_ID (canuint8_t channel_num, canuint8_t msg_handle)
{
   Msg_ID_T rx_msg_id;
   const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;		 

   rx_msg_id = INVALID_REQUEST_RX;
   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
      Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[channel_num]	 
                                     [msg_handle];
      rx_msg_id = Pointer_to_Rx_Parameter_Struct->message_ID;
   }
   return(rx_msg_id);
}
#endif

#ifdef  IGNORE_MSG_ID_BITS  
/*******************************************************************************
* Function Name : VBM_Get_Rx_ID_After_Ignoring_Bits                            *
* Arguments passed: channel number, receive message handle                     *
* Return value : Message ID from the receive buffer                            *
* Functionality : Returns ID of the received message to upper layer            *
*******************************************************************************/
Msg_ID_T VBM_Get_Rx_ID_After_Ignoring_Bits(canuint8_t channel_num, 
                                           canuint8_t msg_handle)
{
 Msg_ID_T rx_id_after_ignoring_bits;
 rx_id_after_ignoring_bits = INVALID_REQUEST_RX;

   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
     rx_id_after_ignoring_bits = receive_buffers[channel_num][msg_handle]
                                .message_ID;
   }
   return(rx_id_after_ignoring_bits);
}
#endif

#ifndef J1939_PROTOCOL_IS_USED
/*******************************************************************************
* Function Name : VBM_Get_Rx_Msg_ID_Type                                       *
* Arguments passed: channel number, receive message handle                     *
* Return value : Message ID type from the receive buffer                       *
* Functionality : Returns the ID type of the received message                  *
*******************************************************************************/
Msg_ID_Type_T VBM_Get_Rx_Msg_ID_Type(canuint8_t channel_num, canuint8_t msg_handle)
{
   Msg_ID_Type_T rx_id_type;
   const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

   rx_id_type = ID_TYPE_NOT_FOUND;
   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
      Pointer_to_Rx_Parameter_Struct= 
                         &VBM_Rx_Msg_Parameter_Tables[channel_num][msg_handle];
      rx_id_type = Pointer_to_Rx_Parameter_Struct->Msg_ID_Type;
   }
   return(rx_id_type);
}
#endif
/*******************************************************************************
* Prototype:  VBM_Get_Rx_Message_DLC_From_Param_Table                          *
* Arguments passed: channel number, receive message handle                     *
* Return type: dlc from Rx Parameter Table                                     *
* Functionality: This API shall be called by upper layer.                      *
* It returns the data length of a received message                             *
*******************************************************************************/
canuint8_t VBM_Get_Rx_Message_DLC_From_Param_Table (canuint8_t channel_num,
                                                      canuint8_t msg_handle)
{
   canuint8_t rx_dlc;
   const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;		 

   rx_dlc = INVALID_REQUEST_RX;
   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
    Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[channel_num]	 
                                   [msg_handle];
    rx_dlc = Pointer_to_Rx_Parameter_Struct->message_length_dlc;
   }
   return(rx_dlc);
}

/*******************************************************************************
* Prototype:  VBM_Get_Rx_Message_Variable_DLC                                  *
* Arguments passed: channel number, receive message handle                     *
* Return type: dlc (canuint8_t) from Rx Run time Table                            *
* Functionality: This API shall be called by upper layer.                      *
* It returns the data length of a received message                             *
*******************************************************************************/
canuint8_t VBM_Get_Rx_Message_Variable_DLC(canuint8_t channel_num, canuint8_t msg_handle)
{
  canuint8_t rx_dlc;
  canuint8_t *vbm_rx_data_ptr;
  receive_buffer_T * Pointer_to_Rx_Buffer;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  rx_dlc = INVALID_REQUEST_RX;
  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[channel_num]
                                       [msg_handle];

   if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
   {
     if(RX_VARIABLE_DLC == Pointer_to_Rx_Parameter_Struct->message_length_dlc)
     {
       Pointer_to_Rx_Buffer = &receive_buffers[channel_num][msg_handle];
       #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
       if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                              Rx_Msg_Type_Realtime_or_FIFO)
       {
         vbm_rx_data_ptr = (canuint8_t*)(Pointer_to_Rx_Buffer->
         data_base_address+ (Pointer_to_Rx_Buffer->out_index * 
         Pointer_to_Rx_Parameter_Struct->message_length_dlc));
       }
       else
       {
         vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address;
       }
       #else
       vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address;
       #endif
       rx_dlc = *(vbm_rx_data_ptr + 8);
     }
   }
  return(rx_dlc);
}

/*******************************************************************************
* Prototype:  VBM_Get_Rx_Message_Data                                          *
* Arguments passed: channel number, message number,  data pointer              *
* Return type: none                                                            *
* Functionality: This API copies dlc number of databytes from VBM receive      *
* buffer to address pointed by upper layers (e.g: IL, NM).                     *
* Also it clears the new message flag for the receive buffer                   *
*******************************************************************************/
void VBM_Get_Rx_Message_Data(canuint8_t channel_num,
                             canuint8_t msg_handle, canuint8_t* appl_data_ptr)
{
  canuint8_t dlc;
  canuint8_t * vbm_rx_data_ptr;
  receive_buffer_T* Pointer_to_Rx_Buffer;
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[channel_num]
                                       [msg_handle];
  Pointer_to_Rx_Buffer = &receive_buffers[channel_num][msg_handle];

  #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
  if(RX_FIFO_MESSAGE == Pointer_to_Rx_Parameter_Struct->
                              Rx_Msg_Type_Realtime_or_FIFO)
  {
    vbm_rx_data_ptr = (canuint8_t*)(Pointer_to_Rx_Buffer->
    data_base_address + (Pointer_to_Rx_Buffer->out_index *
    Pointer_to_Rx_Parameter_Struct->message_length_dlc)); 	  
  }
  else
  {
    vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address;
  }
  #else
  vbm_rx_data_ptr = Pointer_to_Rx_Buffer->data_base_address;
  #endif
  if(Size_Of_Receive_Param_Tables[channel_num] > msg_handle)
  {
     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Disable_Global_Interrupts();
     #endif

     //CAN_Handler_Disable_Interrupts();
     HWCAN_Disable_RX_CAN_Interrupts(0);
   
     dlc = Pointer_to_Rx_Parameter_Struct->message_length_dlc;	
     if(RX_VARIABLE_DLC == dlc)
     {
       dlc = *(vbm_rx_data_ptr + 8);
     }
     switch(dlc)  
     {
        case (8):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (7):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (6):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (5):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (4):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (3):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (2):
                *appl_data_ptr++ = *vbm_rx_data_ptr++; 
        case (1):
                *appl_data_ptr = *vbm_rx_data_ptr; 
        default :
                break;
     }

     #ifdef FIFO_BUFFERS_NEEDED_FOR_RX
     if(RX_FIFO_MESSAGE== Pointer_to_Rx_Parameter_Struct->
                              Rx_Msg_Type_Realtime_or_FIFO)
     {
        Pointer_to_Rx_Buffer->out_index++;
     
       if (Pointer_to_Rx_Buffer->out_index == 
           Pointer_to_Rx_Parameter_Struct->buffer_depth)
       {
        Pointer_to_Rx_Buffer->out_index = 0;
       }
     
       if(Pointer_to_Rx_Buffer->out_index == Pointer_to_Rx_Buffer->in_index)
       {
       Pointer_to_Rx_Buffer->buffer_status = RX_BUFFER_EMPTY;
       Pointer_to_Rx_Buffer->new_message = NO_NEW_MESSAGE_AVAILABLE;
       }
     }
     else
     {
       Pointer_to_Rx_Buffer->new_message = NO_NEW_MESSAGE_AVAILABLE;
     }
     #else
     Pointer_to_Rx_Buffer->new_message = NO_NEW_MESSAGE_AVAILABLE;
     #endif

     CAN_Handler_Enable_Interrupts();
     //HWCAN_Enable_RX_CAN_Interrupts(0);

     #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
     CAN_Handler_Enable_Global_Interrupts();
     #endif

  }
}

/*******************************************************************************
* Prototype:  VBM_Get_Rx_Notifier_Function_Pointer                             *
* Arguments passed: message handle, channel_num                                *
* Return type: Rx notifier function pointer                                    *
* Functionality: This API returns the notifier function pointer for the        *
* message corresponding to the message handle.                                 *
*******************************************************************************/
 function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer(
                          canuint8_t channel_num, canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;		 

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[channel_num]	 
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_function_ptr);	 
}

/*                      Separate APIs to reduce ISR Timing                    */
#ifdef CAN_CH0_SELECTED
 function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer_Ch0(
                          canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[0]
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_function_ptr);
}
#endif
#ifdef CAN_CH1_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer_Ch1(
                          canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[1]
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_function_ptr);
}
#endif
#ifdef CAN_CH2_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Function_Pointer_Ch2(
                          canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[2]
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_function_ptr);
}
#endif


/*******************************************************************************
* Prototype:  VBM_Get_Rx_Notifier_Overrun                                      *
* Arguments passed: message handle, channel_num                                *
* Return type: Rx notifier function pointer for overrun                        *
* Functionality: This API returns the overrun notifier function pointer for the*
* message corresponding to the message handle.                                 *
*******************************************************************************/
 function_pointer_T VBM_Get_Rx_Notifier_Overrun(canuint8_t channel_num,
                                               canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;		 

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[channel_num]	 
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_msg_overwritten);	 
}

/*                   Separate APIs to reduce ISR Timing                     */
#ifdef CAN_CH0_SELECTED
 function_pointer_T VBM_Get_Rx_Notifier_Overrun_Ch0(
                                                      canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[0]
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_msg_overwritten);
}
#endif
#ifdef CAN_CH1_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Overrun_Ch1(
                                                      canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[1]
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_msg_overwritten);

}
#endif
#ifdef CAN_CH2_SELECTED
static function_pointer_T VBM_Get_Rx_Notifier_Overrun_Ch2(
                                                      canuint8_t msg_handle)
{
  const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

  Pointer_to_Rx_Parameter_Struct= &VBM_Rx_Msg_Parameter_Tables[2]
                                   [msg_handle];

  return (Pointer_to_Rx_Parameter_Struct->notifier_msg_overwritten);

}
#endif


/*******************************************************************************
* Prototype:  VBM_Execute_Receive_Notifier_Function                            *
* Arguments passed: message handle, channel num                                *
* Return type: none                                                            *
* Functionality: This API executes the notifier function pointer for the       *
* message corresponding to the message handle.                                 *
*******************************************************************************/
void VBM_Execute_Rx_Notifier_Function(canuint8_t channel_num,
                                              canuint8_t msg_handle)
{
   function_pointer_T notifier_fn_ptr_for_Rx_Msg;
   notifier_fn_ptr_for_Rx_Msg = VBM_Get_Rx_Notifier_Function_Pointer(
                                channel_num,msg_handle);
   if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Msg)
    {
      (*notifier_fn_ptr_for_Rx_Msg)();
    }
}

/*                       Separate APIs to reduce ISR Timing                  */
#ifdef CAN_CH0_SELECTED
void VBM_Execute_Rx_Notifier_Function_Ch0(canuint8_t msg_handle)
{
   function_pointer_T notifier_fn_ptr_for_Rx_Msg;
   notifier_fn_ptr_for_Rx_Msg = VBM_Get_Rx_Notifier_Function_Pointer_Ch0(
                                msg_handle);
   if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Msg)
    {
      (*notifier_fn_ptr_for_Rx_Msg)();
    }
}
#endif
#ifdef CAN_CH1_SELECTED
void VBM_Execute_Rx_Notifier_Function_Ch1(canuint8_t msg_handle)
{
   function_pointer_T notifier_fn_ptr_for_Rx_Msg;
   notifier_fn_ptr_for_Rx_Msg = VBM_Get_Rx_Notifier_Function_Pointer_Ch1(
                                msg_handle);
   if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Msg)
    {
      (*notifier_fn_ptr_for_Rx_Msg)();
    }
}
#endif
#ifdef CAN_CH2_SELECTED
void VBM_Execute_Rx_Notifier_Function_Ch2(canuint8_t msg_handle)
{
   function_pointer_T notifier_fn_ptr_for_Rx_Msg;
   notifier_fn_ptr_for_Rx_Msg = VBM_Get_Rx_Notifier_Function_Pointer_Ch2(
                                msg_handle);
   if(NULL_NOTIFIER_FUNCTION_POINTER != notifier_fn_ptr_for_Rx_Msg)
    {
      (*notifier_fn_ptr_for_Rx_Msg)();
    }
}
#endif
/******************************************************************************
* Prototype:  VBM_Get_Rx_Msg_Handle_From_Message_ID                           *
* Arguments passed: channel number, Message_ID                                *
* Return type: msg handle                                                     *
* Functionality: This function finds the Message Number corresponding to the  *
* Message ID to be transmitted from the VBM_Rx_Msg_Parameter_Table[]          *
* by performing Binary Search. Message Number is the array index in the table *
* for the particular Message ID. The contents of VBM_Rx_Msg_Parameter_Table   *
* must be arranged in decreasing priority.                                    *
*******************************************************************************/
#ifndef J1939_PROTOCOL_IS_USED
canuint8_t VBM_Get_Rx_Msg_Handle_From_Message_ID (canuint8_t channel_num,
                                               Msg_ID_T ID_passed)
{
   return(CAN_Binary_Search(channel_num, ID_passed, HWCAN_RECEIVE));
}

#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
