/**************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_vbm_config.h                                          
  File Description:
  This module contains configuration macro's for tx and rx messages  

**************************************************************/

#ifndef CAN_VBM_CONFIG_H
#define CAN_VBM_CONFIG_H 

#include "can_handler_datatypes.h"
#include "can_handler_config.h"
#include "can_handler_appl_notifier_functions.h"


/**************************************************************

 START OF COMPILE MACRO'S FOR FIFO BUFFERS FOR TX AND RX

**************************************************************/

#define FIFO_BUFFERS_NEEDED_FOR_TX

#define FIFO_BUFFERS_NEEDED_FOR_RX

/**************************************************************

START OF CONFIGURATION FOR MAX BYTES ALLOCATION FOR RX AND TX BUFFERS

**************************************************************/

/**************************************************************

CONFIGURATION FOR MAX BYTES ALLOCATION FOR RX CHANNEL-0

**************************************************************/

#define  CAN_CH0_RX_MSG1_DLC    8
#define  CAN_CH0_RX_MSG2_DLC    8
#define  CAN_CH0_RX_MSG3_DLC    8
#define  CAN_CH0_RX_MSG4_DLC    8

#define  CAN_CH0_RX_MSG1_BUFFER_DEPTH     1
#define  CAN_CH0_RX_MSG2_BUFFER_DEPTH     1
#define  CAN_CH0_RX_MSG3_BUFFER_DEPTH     1
#define  CAN_CH0_RX_MSG4_BUFFER_DEPTH     1

#define TOTAL_BYTES_FOR_LAST_RX_DATA_BUFFER     \
     CAN_CH0_RX_MSG4_DLC * CAN_CH0_RX_MSG4_BUFFER_DEPTH

#define TOTAL_BYTES_FOR_RX_DATA_BUFFER_CH0                          \
((CAN_CH0_RX_MSG1_DLC * CAN_CH0_RX_MSG1_BUFFER_DEPTH) +            \
(CAN_CH0_RX_MSG2_DLC *CAN_CH0_RX_MSG2_BUFFER_DEPTH) +              \
(CAN_CH0_RX_MSG3_DLC *CAN_CH0_RX_MSG3_BUFFER_DEPTH) +              \
(CAN_CH0_RX_MSG4_DLC *CAN_CH0_RX_MSG4_BUFFER_DEPTH))
/**************************************************************

               CONFIGURATION FOR PHYSICAL ID 

**************************************************************/

#define  Transmit_User_ID_Physical       0x000

#define  Receive_User_ID_Physical       0x000

#define  Receive_User_ID_Functional       0x000

/**************************************************************

CONFIGURATION FOR MAX BYTES ALLOCATION FOR TX CHANNEL-0

**************************************************************/

#define  CAN_CH0_TX_MSG1_DLC              8
#define  CAN_CH0_TX_MSG1_BUFFER_DEPTH     1

#define  CAN_CH0_TX_MSG2_DLC              8
#define  CAN_CH0_TX_MSG2_BUFFER_DEPTH     1


#define TOTAL_BYTES_FOR_TX_DATA_BUFFER_CH0                 \
((CAN_CH0_TX_MSG1_DLC * CAN_CH0_TX_MSG1_BUFFER_DEPTH) +    \
(CAN_CH0_TX_MSG2_DLC *CAN_CH0_TX_MSG2_BUFFER_DEPTH))

/**************************************************************

 START OF PROTOTYPE DECLARATION FOR APPLICATION RX AND TX CALL BACK FUNCTIONS

**************************************************************/

/**************************************************************

CAN Receive Message Notifier Functions Prototype: Channel 0

**************************************************************/

extern void CAN_Rx_Msg_Notifier0_Ch0(void);
extern void CAN_Rx_Msg_Notifier1_Ch0(void);
extern void CAN_Rx_Msg_Notifier2_Ch0(void);
extern void CAN_Rx_Msg_Notifier3_Ch0(void);
/**************************************************************

CAN Receive Message Overrun Notifier Functions Prototype: Channel 0

**************************************************************/

extern void CAN_Rx_Msg_Overrun_Notifier0_Ch0(void);
extern void CAN_Rx_Msg_Overrun_Notifier1_Ch0(void);
extern void CAN_Rx_Msg_Overrun_Notifier2_Ch0(void);
extern void CAN_Rx_Msg_Overrun_Notifier3_Ch0(void);

/* CAN Transmit Message Notifier Functions Prototype: Channel 0*/
extern void CAN_Tx_Msg_Notifier0(void);
extern void CAN_Tx_Msg_Notifier1(void);
#endif   /*CAN_VBM_CONFIG_H*/

 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

