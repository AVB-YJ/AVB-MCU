/**************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_timer_mod_config.h                                          
  File Description:
  This file contains timer related  configuration parameters    

**************************************************************/

#ifndef CAN_TIMER_MOD_CONFIG_H
#define CAN_TIMER_MOD_CONFIG_H

#include "can_handler_config.h"


#define OS_PERIODIC_CALL_RATE_OF_CAN_TIMER_TASK                               10 

typedef enum
{

CYCLIC_TIMER_DVD_Ch0 =0,
CYCLIC_TIMER_AC_Ch0,
TOTAL_NUMBER_OF_SUPPORTED_TIMERS,
DUMMY_TIMER
}CAN_Timer_Names_T;

/**************************************************************

******       CONFIGURATION FOR NUMBER OF TIMERS ON EACH CHANNEL        ******

**************************************************************/

#define NUM_OF_TIMERS_CH0    2
#define NUM_OF_TIMERS_CH1    0
#define NUM_OF_TIMERS_CH2    0
/**************************************************************

START OF PROTOTYPE DECLARATION FOR CAN TIMER EXPIRY NOTIFIER FUNCTIONS

**************************************************************/

extern void CAN_Timer_Exp_Notifier0(void);
extern void CAN_Timer_Exp_Notifier1(void);
#endif         /*CAN_TIMER_MOD_CONFIG_H*/

 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

