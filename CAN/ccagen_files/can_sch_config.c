/*******************************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_sch_config.c                                         
  File Description:
  It contains all the Transmit Message Types Configuration  
  Tables.            

*******************************************************************************/


#include "can_sch_config.h"
#include "can_sch_tx.h"
#include "can_sch_rx.h"
#include "can_handler_config.h"
#include "can_timer_mod_config.h"


#ifdef ON_EVENT_MSG_SUPPORTED
const ON_EVENT_MSG_CONFIG_T ON_EVENT_MSG_CONFIG_Table[]=
{/* msg_handle, ifdef)timeout_timer, (ifdef)startup_delay_timer */
 
   { 1 }
};

const canuint8_t Size_Of_On_Event_Table = 
(sizeof(ON_EVENT_MSG_CONFIG_Table)/
sizeof(ON_EVENT_MSG_CONFIG_Table[0]));

#endif /* ON_EVENT_MSG_SUPPORTED */

#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
const ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T 
ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[]=
{/*msg_handle, min_delay_timer, (ifdef)timeout_timer, (ifdef)startup_delay_timer*/
   
};

const canuint8_t Size_Of_On_Event_With_Min_Update_Table = 
(sizeof(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table)/
sizeof(ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[0]));

#endif /* ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED */

#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
const N_TIMES_ON_EVENT_MSG_CONFIG_T N_TIMES_ON_EVENT_MSG_CONFIG_Table[]=
{/*msg_handle, transmit_count, (ifdef)timeout_timer, (ifdef)startup_delay_timer*/
  
};

const canuint8_t Size_Of_N_Times_On_Event_Table = 
(sizeof(N_TIMES_ON_EVENT_MSG_CONFIG_Table)/
sizeof(N_TIMES_ON_EVENT_MSG_CONFIG_Table[0]));

#endif /* N_TIMES_ON_EVENT_MSG_SUPPORTED */

#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
const N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T 
N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[]=
{/*msg_handle, min_delay_timer, transmit_count, (if)timeout_timer, 
                                                      (if)startup_delay_timer*/
 
};

const canuint8_t Size_Of_N_Times_On_Event_With_Min_Update_Table = 
(sizeof(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table)/
sizeof(N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[0]));

#endif /* N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED */

#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
const CYCLIC_ON_INIT_MSG_CONFIG_T CYCLIC_ON_INIT_MSG_CONFIG_Table[]=
{/*msg_handle, cyclic_timer, (ifdef)timeout_timer, (ifdef)startup_delay_timer*/
  
   { 0, CYCLIC_TIMER_DVD_Ch0 },
   { 1, CYCLIC_TIMER_AC_Ch0 }
};

const canuint8_t Size_Of_Cyclic_On_Init_Msg_Table = 
(sizeof(CYCLIC_ON_INIT_MSG_CONFIG_Table)/
sizeof(CYCLIC_ON_INIT_MSG_CONFIG_Table[0]));

#endif /* CYCLIC_ON_INIT_MSG_SUPPORTED */

#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
const CYCLIC_ON_REQUEST_MSG_CONFIG_T CYCLIC_ON_REQUEST_MSG_CONFIG_Table[]=
{/*msg_handle, cyclic_timer, (ifdef)timeout_timer, (ifdef)startup_delay_timer*/
  
};

const canuint8_t Size_Of_Cyclic_On_Request_Msg_Table = 
(sizeof(CYCLIC_ON_REQUEST_MSG_CONFIG_Table)/
sizeof(CYCLIC_ON_REQUEST_MSG_CONFIG_Table[0]));

#endif /* CYCLIC_ON_REQUEST_MSG_SUPPORTED */

#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
const CYCLIC_AND_ON_EVENT_MSG_CONFIG_T CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[]=
{/*msg_handle, cyclic_timer, (ifdef)timeout_timer, (ifdef)startup_delay_timer*/

};

const canuint8_t Size_Of_Cyclic_And_On_Event_Msg_Table = 
(sizeof(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table)/
sizeof(CYCLIC_AND_ON_EVENT_MSG_CONFIG_Table[0]));

#endif /* CYCLIC_AND_ON_EVENT_MSG_SUPPORTED */

#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
const CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_T 
CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[]=
{/*msg_handle, cyclic_timer,min_delay_timer, (ifdef)timeout_timer, 
                                                    (ifdef)startup_delay_timer*/
  

};

const canuint8_t Size_Of_Cyclic_And_On_Event_With_Min_Update_Time_Msg_Table = 
(sizeof(CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table)/
sizeof(CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CONFIG_Table[0]));

#endif /* CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED */

#ifdef BAF_MSG_SUPPORTED
const BAF_MSG_CONFIG_T BAF_MSG_CONFIG_Table[]=
{/*msg_handle, cyclic_timer, (ifdef)timeout_timer, (ifdef)startup_delay_timer*/


};

const canuint8_t Size_Of_BAF_Msg_Table = 
(sizeof(BAF_MSG_CONFIG_Table)/sizeof(BAF_MSG_CONFIG_Table[0]));

#endif /* BAF_MSG_SUPPORTED */

#ifdef FAST_MSG_SUPPORTED
const FAST_MSG_CONFIG_T FAST_MSG_CONFIG_Table[]=
{/*msg_handle,  fast_timer,   slow_timer,  (ifdef)timeout_timer, 
                                                   (ifdef)startup_delay_timer*/

};

const canuint8_t Size_Of_FAST_Msg_Table = 
(sizeof(FAST_MSG_CONFIG_Table)/sizeof(FAST_MSG_CONFIG_Table[0]));

#endif /*  FAST_MSG_SUPPORTED */ 


/******************************************************************************
*******    CONFIGURATION OF RX TABLES FOR TIMEOUT MONITORING       ************
******************************************************************************/
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED

#ifdef CAN_CH0_SELECTED
const SCH_Rx_Msg_Timeout_Config_T SCH_Rx_Msg_Timeout_Config_Table_Ch0[] = 
{ /*timeout_timer_0*/
    
};
#endif /* Timeout timers for Rx messages in Channel 0 if CAN_CH0_SELECTED */

#ifdef CAN_CH1_SELECTED
const SCH_Rx_Msg_Timeout_Config_T SCH_Rx_Msg_Timeout_Config_Table_Ch1[] = 
{ /*timeout_timer_1*/
};
#endif /* Timeout timers for Rx messages in Channel 1 if CAN_CH1_SELECTED */

#ifdef CAN_CH2_SELECTED
const SCH_Rx_Msg_Timeout_Config_T SCH_Rx_Msg_Timeout_Config_Table_Ch2[] = 
{ /*timeout_timer_2*/
  
};
#endif /* Timeout timers for Rx messages in Channel 2 if CAN_CH2_SELECTED */




const canuint8_t Size_Of_Rx_Timeout_Monitor_Tables[]= 
{
  #ifdef CAN_CH0_SELECTED
  (sizeof(SCH_Rx_Msg_Timeout_Config_Table_Ch0)/
   sizeof(SCH_Rx_Msg_Timeout_Config_Table_Ch0[0])),
  #endif 
  #ifdef CAN_CH1_SELECTED
  (sizeof(SCH_Rx_Msg_Timeout_Config_Table_Ch1)/
   sizeof(SCH_Rx_Msg_Timeout_Config_Table_Ch1[0])),
  #endif 
  #ifdef CAN_CH2_SELECTED
  (sizeof(SCH_Rx_Msg_Timeout_Config_Table_Ch2)/
   sizeof(SCH_Rx_Msg_Timeout_Config_Table_Ch2[0]))
  #endif 
};

#endif /* End of TIMEOUT_FOR_RX_MSG_SUPPORTED */



 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

