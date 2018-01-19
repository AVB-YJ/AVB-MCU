/***************************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_drv_config.c                                         
  File Description:
  This file contains configuration tables related to CAN features            
  and vector table.                               

***************************************************************************/


#include "can_drv_config.h"
#include "can_drv_init_misc.h"
#include "can_drv_tx_rx.h"
 


/******************************************************************************
 Refer CAN Driver Layer Configuration Section in the User Manual for details
 *****************************************************************************/
#ifdef CAN_COMMON_VECTOR
const CAN_ISR_Table_T CAN_ISR_Table[NUMBER_OF_INTERRUPTS_SUPPORTED]
                                       [NUMBER_OF_CHANNELS_SUPPORTED] =
{

#ifdef ERROR_INTERRUPT_MODE
   {CD_Error_ISR_Channel_0   , HWCAN_ERROR}      ,
#endif  /* ERROR_INTERRUPT_MODE */ 

#ifdef WAKEUP_INTERRUPT_MODE
   {CD_Wakeup_ISR_Channel_0  , HWCAN_WAKEUP}    ,
#endif  /* WAKEUP_INTERRUPT_MODE */

#ifdef RECEIVE_INTERRUPT_MODE
   {CD_Receive_ISR_Channel_0 , HWCAN_RECEIVE}  ,
#endif  /* RECEIVE_INTERRUPT_MODE */

#ifdef TRANSMIT_INTERRUPT_MODE
   {CD_Transmit_ISR_Channel_0, HWCAN_TRANSMIT}
#endif  /* TRANSMIT_INTERRUPT_MODE */

};
#endif /* CAN_COMMON_VECTOR */

#ifdef  IGNORE_MSG_ID_BITS  

const Bit_Ignore_Patterns_T Bit_Ignore_Patterns[][] ={

             
};
#endif /* IGNORE_MSG_ID_BITS */




 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

