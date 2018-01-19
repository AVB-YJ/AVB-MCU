/**********************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved
  Project Name : cca
  ECU :  HMI
  File Name:  can_handler_config.h
  File Description:
  This file contains macro's and configuration items
  for  CAN Handler (DCH)

*************************************************************************/

#ifndef CAN_HANDLER_CONFIG_H
#define CAN_HANDLER_CONFIG_H

#include "can_handler_datatypes.h"
#include "can_handler.h"


/**********************************************************************

MACRO FOR SELECTION OF J1939 PROTOCOL (#undef if J1939 is not to be used)

*************************************************************************/

#undef  J1939_PROTOCOL_IS_USED

/**********************************************************************

START OF COMPILE MACRO'S FOR LAYER SELECTION

*************************************************************************/

#define CAN_HANDLER_DRIVER_LAYER_SUPPORTED
#define CAN_HANDLER_VIRTUAL_BUFFER_MANAGEMENT_LAYER_SUPPORTED
#define CAN_HANDLER_TIMER_MODULE_SUPPORTED
#define CAN_HANDLER_SCHEDULER_MODULE_SUPPORTED
#define CAN_HANDLER_AIF_LAYER_SUPPORTED
#undef  CAN_HANDLER_DIAGNOSTICS_LAYER_SUPPORTED
#define CAN_HANDLER_NM_LAYER_SUPPORTED
//#undef CAN_HANDLER_NM_LAYER_SUPPORTED
#undef  CAN_HANDLER_TRANSPORT_PROTOCOL_SUPPORTED

#undef  CAN_WAKEUP_MODE_AVAILABLE
#undef  CAN_SLEEP_MODE_AVAILABLE

/**********************************************************************

START OF CONFIGURATION FOR NUMBER OF CHANNELS SUPPORTED

*************************************************************************/

#define NUMBER_OF_CHANNELS_SUPPORTED    1

/**********************************************************************

START OF COMPILE MACRO'S FOR CHANNEL SELECTION

*************************************************************************/

#define CAN_CH0_SELECTED
#undef  CAN_CH1_SELECTED
#undef  CAN_CH2_SELECTED

/**********************************************************************

START OF CONFIGURATION FOR NUMBER OF MESSAGES

VVI NOTE : FOR UNUSED CHANNEL(S) DEFINE THE TX AND RX MACRO'S TO ZERO

*************************************************************************/


#define NUMBER_OF_TX_MSG_SUPPORTED_CH0  2
#define NUMBER_OF_RX_MSG_SUPPORTED_CH0  4

#define NUMBER_OF_TX_MSG_SUPPORTED_CH1  0
#define NUMBER_OF_RX_MSG_SUPPORTED_CH1  0

#define NUMBER_OF_TX_MSG_SUPPORTED_CH2  0
#define NUMBER_OF_RX_MSG_SUPPORTED_CH2  0

/**********************************************************************

START OF CONFIGURATION FOR INTERRUPT OR POLLING MODE

*************************************************************************/

#define CAN_INTERRUPT_MODE

/**********************************************************************

START OF COMPILE MACRO'S FOR CONFIFURATION SEQUENCE OF RECEIVE BUFFERS

*************************************************************************/

#undef  RX_BUFFERS_CONFIGURED_IN_RANDOM_SEQUENCE

/**********************************************************************

START OF COMPILE MACRO'S FOR SEARCH TYPE SELECTION

*************************************************************************/

 /*Note: Binary and Hash Search not used when J1939_PROTOCOL_IS_USED */

#undef  HASH_SEARCH
#define BINARY_SEARCH

#define CAN_CH0_BINARY_SEARCH
#undef  CAN_CH1_BINARY_SEARCH
#undef  CAN_CH2_BINARY_SEARCH

/**********************************************************************

START OF COMPILE MACRO'S FOR DISABLING GLOBAL INTERRUPTS THROUGH CAN HANDLER

*************************************************************************/

#undef  DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER

/**********************************************************************

START OF OEM SPECIFIC COMPILE MACRO'S

*************************************************************************/

#define CCA_HMI

/**********************************************************************

define this macro if Transmission is supported by the node

*************************************************************************/

#define CAN_TX_MSG_SUPPORTED

#endif       /* End #ifndef CAN_HANDLER_CONFIG_H */

 /*******************************************************************************
                           REVISION HISTORY
 *******************************************************************************
  Rev      Date            S/W Engineer                Description
 *******************************************************************************
   1      15/10/2014
 ********************************************************************************/

