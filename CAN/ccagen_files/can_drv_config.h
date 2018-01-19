/***************************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_drv_config.h                                          
  File Description:
  This file contains configuration information             
  related to CAN features and vector table                 

***************************************************************************/

#ifndef CAN_DRV_CONFIG_H
#define CAN_DRV_CONFIG_H 

#include "hwcan_init_misc_nec_v850.h"
#include "hwcan_tx_rx_nec_v850.h"
#include "hwcan_nec_v850_config.h"
#include "can_handler_config.h"


/***************************************************************************

Refer CAN Driver Layer Configuration Section in the User Manual for details

***************************************************************************/

/***************************************************************************

                      START OF CONFIGURATION FOR POLLING

***************************************************************************/

#ifndef TRANSMIT_INTERRUPT_MODE

#define MAX_TX_MSG_PER_LOOP_FOR_POLL    1

#endif /* End of Polling ifndef CAN_INTERRUPT_MODE */

/***************************************************************************

                      START OF CONFIGURATION FOR INTERRUPTS

***************************************************************************/

#ifdef CAN_INTERRUPT_MODE

#undef  CAN_COMMON_VECTOR
#define  TRANSMIT_INTERRUPT_MODE
#define  RECEIVE_INTERRUPT_MODE
#define  ERROR_INTERRUPT_MODE
#undef  WAKEUP_INTERRUPT_MODE
#undef  CAN_INTERRUPTS_SEPARATE_ENABLING

/* NOTE: LEAVE ALL THE UNUSED INTERRUPT MACRO'S DEFINED AS BLANK*/

#define   BLANK

/***************************************************************************

                      START OF CONFIGURATION FOR COMMON VECTOR

***************************************************************************/

#define CAN_INTERRUPT_0    BLANK
#define CAN_INTERRUPT_1    BLANK
#define CAN_INTERRUPT_2    BLANK
/***************************************************************************

                      START OF CONFIGURATION FOR MULTIPLE VECTOR

***************************************************************************/

#define  CAN_INTERRUPT_TRANSMIT_0   BLANK
#define  CAN_INTERRUPT_TRANSMIT_1   BLANK 
#define  CAN_INTERRUPT_TRANSMIT_2   BLANK 

#define  CAN_INTERRUPT_RECEIVE_0    BLANK
#define  CAN_INTERRUPT_RECEIVE_1    BLANK 
#define  CAN_INTERRUPT_RECEIVE_2    BLANK 

#define  CAN_INTERRUPT_ERROR_0      BLANK
#define  CAN_INTERRUPT_ERROR_1      BLANK 
#define  CAN_INTERRUPT_ERROR_2      BLANK 

#define  CAN_INTERRUPT_WAKEUP_0     BLANK
#define  CAN_INTERRUPT_WAKEUP_1     BLANK 
#define  CAN_INTERRUPT_WAKEUP_2     BLANK 

#endif   /* End #ifdef CAN_INTERRUPT_MODE  */
/***************************************************************************

                      START OF CONFIGURATION FOR MESSAGE ID TYPE

***************************************************************************/

#undef MESSAGE_ID_TYPE_MIXED

#define MESSAGE_ID_TYPE_STANDARD

#undef MESSAGE_ID_TYPE_EXTENDED

/***************************************************************************

              START OF CONFIGURATION FOR IGNORING BITS IN MESSAGE ID

***************************************************************************/

#undef IGNORE_MSG_ID_BITS

#endif   /* End #ifndef CAN_DRV_CONFIG_H */


 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

