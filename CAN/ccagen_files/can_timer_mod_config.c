/**************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_timer_mod_config.c                                          
  File Description:
  This file contains timer related constant tables for    
  configuration     

**************************************************************/

#include "can_timer_mod.h"
#include "can_timer_mod_config.h"


/**************************************************************

Include layer specific header files to call APIs inside timer notifier function

**************************************************************/

#include "can_vbm_tx.h"
#include "can_sch_tx.h"
#include "can_sch_rx.h"

const CAN_Timer_Param_Tbl_T 
CAN_Timer_Parameter_Table [] =
{
   /*set_timer_value; timer_activation_method; timer_type; timer_expiry_condition
   expiry_notifier_function; process status */
   {1000, ON_INIT, CONT_RUNNING, NOTIFY_NORMAL, CAN_Timer_Exp_Notifier0, PROCESS_IN_PERIODIC_TASK},
   {1000, ON_INIT, CONT_RUNNING, NOTIFY_NORMAL, CAN_Timer_Exp_Notifier1, PROCESS_IN_PERIODIC_TASK},
};

const canuint8_t Size_Of_Timer_Param_Table =
(sizeof(CAN_Timer_Parameter_Table)/sizeof(CAN_Timer_Parameter_Table[0]));

/**************************************************************

START OF TIMER EXPIRY NOTIFIER FUNCTION PROCESSING

**************************************************************/

/**************************************************************

 Prototype:  CAN_Timer_Exp_Notifier0
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: CAN Timer-0 Notify processing     
**************************************************************/

void CAN_Timer_Exp_Notifier0(void)
{
   if(CAN_Timer_Parameter_Table[CYCLIC_TIMER_DVD_Ch0].process_Status == PROCESS_IN_NOTIFIER)
    {
          /* Call Layer specific API to process inside this notifier function */
     SCH_Immediate_Process_Cyclic_On_Init_Msg(CYCLIC_TIMER_DVD_Ch0);
    }
   else
    {
         /* Call Layer specific API to set flag and do the process later in periodic task */
     SCH_Set_Flag_Cyclic_On_Init_Msg(CYCLIC_TIMER_DVD_Ch0);
    }
}

/**************************************************************

 Prototype:  CAN_Timer_Exp_Notifier1
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: CAN Timer-1 Notify processing     
**************************************************************/

void CAN_Timer_Exp_Notifier1(void)
{
   if(CAN_Timer_Parameter_Table[CYCLIC_TIMER_AC_Ch0].process_Status == PROCESS_IN_NOTIFIER)
    {
          /* Call Layer specific API to process inside this notifier function */
     SCH_Immediate_Process_Cyclic_On_Init_Msg(CYCLIC_TIMER_AC_Ch0);
    }
   else
    {
         /* Call Layer specific API to set flag and do the process later in periodic task */
     SCH_Set_Flag_Cyclic_On_Init_Msg(CYCLIC_TIMER_AC_Ch0);
    }
}
 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

