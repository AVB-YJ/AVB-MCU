/*******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved               *
 * REVISION: 1.0                                                               *
 * AUTHORS: Prakash, Sandeep                                                   *
 * Project: CCA - CAN Timer Module                                             *
 * File Name:  can_timer_mod.c                                                 *
 * Description: This file contains timer function def's                        *
 ******************************************************************************/
#include "can_timer_mod.h"
#include "can_timer_mod_config.h"
#include "can_handler_appl_notifier_functions.h"
#include "can_aif_config.h"


CAN_Timer_Runtime_Tbl_T CAN_Timer_Runtime_Table
                        [TOTAL_NUMBER_OF_SUPPORTED_TIMERS];

static canuint16_t CAN_Timer_Counts[TOTAL_NUMBER_OF_SUPPORTED_TIMERS];
 void CAN_TIMER_Calculate_Count(canuint8_t CAN_Timer_Name);
 void CAN_TIMER_Load(canuint8_t timer_index);
 void CAN_TIMER_Processing(void);

/*******************************************************************************
 * Function Name : CAN_TIMER_Cold_Init                                         *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Handler core file to     *
 *          Initialize the configured timers for all the layers                *
 ******************************************************************************/
void CAN_TIMER_Cold_Init(canuint8_t channel_num)
{
  canuint8_t timer_index, start_index, end_index;

  if(0 == channel_num)
  {
    start_index = 0;
    end_index = NUM_OF_TIMERS_CH0 - 1;
  }
  else if(1 == channel_num)
  {
    start_index = NUM_OF_TIMERS_CH0;
    end_index = start_index + NUM_OF_TIMERS_CH1 -1;
  }
  else if(2 == channel_num)
  {
    start_index = NUM_OF_TIMERS_CH0 + NUM_OF_TIMERS_CH1;
    end_index = start_index + NUM_OF_TIMERS_CH2 - 1;
  }
  else 
  {
    start_index = 0;
    end_index = 0;
  }

  for (timer_index = start_index; timer_index <= end_index; timer_index++)
  {
     CAN_Timer_Runtime_Table[timer_index].timer_count = 0;
     CAN_Timer_Runtime_Table[timer_index].timer_status = CAN_TIMER_INACTIVE;
     CAN_TIMER_Calculate_Count(timer_index);
     CAN_TIMER_Load(timer_index);
  }
}

/*******************************************************************************
 * Function Name : CAN_TIMER_Calculate_Count                                   *
 * Function Parameters : CAN Timer Name                                        *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Timer Init to            *
 *          calculate the timer count                                          *
 ******************************************************************************/
 void CAN_TIMER_Calculate_Count(canuint8_t CAN_Timer_Name)
{

   CAN_Timer_Counts[CAN_Timer_Name] = CAN_Timer_Parameter_Table[CAN_Timer_Name].set_timer_value / 
                                      OS_PERIODIC_CALL_RATE_OF_CAN_TIMER_TASK;
                  
   if(0 < CAN_Timer_Counts[CAN_Timer_Name])
   {
      if(NOTIFY_NORMAL == CAN_Timer_Parameter_Table[CAN_Timer_Name].timer_expiry_condition)
      {
        if(CAN_Timer_Parameter_Table[CAN_Timer_Name].set_timer_value  %  
			OS_PERIODIC_CALL_RATE_OF_CAN_TIMER_TASK )
        {
         CAN_Timer_Counts[CAN_Timer_Name]++;
        }
      }
   }
   else
   {
      Appl_Notify_Invalid_Timer_Value(CAN_Timer_Name);
   }
}

/*******************************************************************************
 * Function Name : CAN_TIMER_Task                                              *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Handler core file to     *
 *          process all the timers and to notify the expiry                    *
 ******************************************************************************/
void CAN_TIMER_Task(void)
{
	CAN_TIMER_Processing();
}

/*******************************************************************************
 * Function Name : CAN_TIMER_Load                                              *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Timer Task to            *
 *          load the count first time after initialization                     *
 ******************************************************************************/
 void CAN_TIMER_Load(canuint8_t timer_index)
{
  if(ON_INIT == CAN_Timer_Parameter_Table[timer_index].timer_activation_method)
  {
     CAN_TIMER_Start(timer_index);
  }

}

/*******************************************************************************
 * Function Name : CAN_TIMER_Processing                                        *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Timer Task to            *
 *          process the timers                                                 *
 ******************************************************************************/
 void CAN_TIMER_Processing(void)
{
	canuint8_t timer_index;
	
	for(timer_index = 0; timer_index < Size_Of_Timer_Param_Table; timer_index++)
	{
		if(CAN_TIMER_ACTIVE == CAN_Timer_Runtime_Table[timer_index].timer_status)
		{
			CAN_Timer_Runtime_Table[timer_index].timer_count--;
			if(0 == CAN_Timer_Runtime_Table[timer_index].timer_count)
			{
				(*CAN_Timer_Parameter_Table[timer_index].expiry_notifier_function)();
				
				if( CONT_RUNNING == CAN_Timer_Parameter_Table[timer_index].
					   timer_type )
				{
					CAN_TIMER_Start(timer_index);
				}
				else
				{
					CAN_Timer_Runtime_Table[timer_index].timer_status = 
					CAN_TIMER_INACTIVE;
				}
			}
		}
	}
}

/*******************************************************************************
 * Function Name : CAN_TIMER_Start                                             *
 * Function Parameters : CAN Timer Name                                        *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Handler layers to        *
 *          start the timer                                                    *
 ******************************************************************************/
void CAN_TIMER_Start(canuint8_t CAN_Timer_Name)
{

   if(CAN_Timer_Name < Size_Of_Timer_Param_Table)
   {
      if(CAN_Timer_Counts[CAN_Timer_Name] > 0 )
      {
         CAN_Timer_Runtime_Table[CAN_Timer_Name].timer_count = 
         CAN_Timer_Counts[CAN_Timer_Name];
         CAN_Timer_Runtime_Table[CAN_Timer_Name].timer_status = 
         CAN_TIMER_ACTIVE;
      }
   }
   else
   {
      Appl_Notify_Invalid_Timer(CAN_Timer_Name);
   }
}

/*******************************************************************************
 * Function Name : CAN_TIMER_Cancel                                            *
 * Function Parameters : CAN Timer Name                                        *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Handler layers to        *
 *          cancel the timer                                                   *
 ******************************************************************************/
void CAN_TIMER_Cancel(canuint8_t CAN_Timer_Name)
{
   if(CAN_Timer_Name < Size_Of_Timer_Param_Table)
   {
     CAN_Timer_Runtime_Table[CAN_Timer_Name].timer_status = CAN_TIMER_INACTIVE;
   }
   else
   {
      Appl_Notify_Invalid_Timer(CAN_Timer_Name);
   }
}

/*******************************************************************************
 * Function Name : CAN_TIMER_Warm_Init                                         *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Handler core file to     *
 *          Initialize the configured timers for all the layers                *
 ******************************************************************************/
void CAN_TIMER_Warm_Init(canuint8_t channel_num)
{
  canuint8_t timer_index, start_index, end_index;

  if(0 == channel_num)
  {
    start_index = 0;
    end_index = NUM_OF_TIMERS_CH0 - 1;
  }
  else if(1 == channel_num)
  {
    start_index = NUM_OF_TIMERS_CH0;
    end_index = start_index + NUM_OF_TIMERS_CH1 -1;
  }
  else if(2 == channel_num)
  {
    start_index = NUM_OF_TIMERS_CH0 + NUM_OF_TIMERS_CH1;
    end_index = start_index + NUM_OF_TIMERS_CH2 - 1;
  }
  else 
  {
    start_index = 0;
    end_index = 0;
  }

  for (timer_index = start_index; timer_index <= end_index; timer_index++)
  {
    CAN_Timer_Runtime_Table[timer_index].timer_count = 0;
    CAN_Timer_Runtime_Table[timer_index].timer_status = CAN_TIMER_INACTIVE;
    CAN_TIMER_Load(timer_index);
  }
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
