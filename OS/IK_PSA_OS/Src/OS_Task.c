/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS Task ( OS task )
 *  File          : OS_Task.c
 *-----------------------------------------------------------------------------
 *  Description   : OS task
 *
 *  Version       : %version:       1 %
 *  Instance      : %instance:      ctc_aud_5 %
 *----------------------------------------------------------------------------
 *  Last modification done
 *             by : %derived_by:    lzs7ws %
 *             on : %date_created:  Tue Jun 26 15:36:41 2012 %

 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*----------------------------------------------------------------------------*
 *              --- Included files and compilation variables ---              *
 *----------------------------------------------------------------------------*/
#include "Systype.h"

#include "OS.h"

#ifdef OS_TASK_USED

#include "OS_Task.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                             --- Variables ---                              *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                    --- Local functions declaration ---                     *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                          --- Local functions ---                           *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

/******************************************************************************
 * Function  : OS_ActivateTask
 *
 * Role      : Schedule a task for activation.
 *
 * ExpirationTime: 0: scheduling immediately
                   x: delay x ms to schedule
 * CyclicTime: the periodic time                   
 ******************************************************************************/

OS_Error OS_ActivateTask(OS_TaskID TaskID, OS_TimeType ExpirationTime, OS_TimeType CyclicTime)
{
    OS_TaskType* const pTask = &OS_TaskArray[TaskID];

#ifdef OS_DEBUG    
    if ( (0 > TaskID) || (OS_MaxTask <= TaskID) )
    {
        return OS_IdOutOfRange;
    }
#endif

    OS_DisableSysTick();
    if (0U == ExpirationTime)
    {
        /* Immediate scheduling */
        pTask->Schedule++;
        OS_Control.TasksToSchedule++;
        /* Next expiration after CyclicTime */
        pTask->Expiration = CyclicTime;
    }
    else
    {
        /* Delayed scheduling */
        pTask->Expiration = ExpirationTime;
    }
    pTask->Reload = CyclicTime;
    OS_EnableSysTick();

    return OS_NoError;
}


/******************************************************************************
 * Function  : OS_CancelTask
 *
 * Role      : Cancel a task
 *
 ******************************************************************************/

OS_Error OS_CancelTask(OS_TaskID TaskID)
{
    OS_TaskType* const pTask = &OS_TaskArray[TaskID];

#ifdef OS_DEBUG    
    if ( (0U > TaskID) || (OS_MaxTask <= TaskID) )
    {
        return OS_IdOutOfRange;
    }
#endif

    OS_DisableSysTick();
    pTask->Expiration = 0;
    pTask->Reload = 0;
    /* Decrease total tasks to schedule counter */
    OS_Control.TasksToSchedule-=pTask->Schedule;
    pTask->Schedule=0;
    OS_EnableSysTick();

    return OS_NoError;
}

/******************************************************************************
 * Function  : OS_CancelAllTasks
 *
 * Role      : Cancel all tasks
 *
 ******************************************************************************/

void OS_CancelAllTasks(void)
{
    OS_TaskType* pCtrlTask = &OS_TaskArray[0];

    OS_IndexType index;

    OS_DisableSysTick();
    for (index=0; index<OS_MaxTask; index++)
    {
        pCtrlTask->Expiration = 0;
        pCtrlTask->Reload = 0;
        pCtrlTask++;
    }
    
    OS_Control.TasksToSchedule = 0;
    OS_EnableSysTick();
}


/******************************************************************************
 * Function  : OS_IsTaskActive
 *
 * Role      : Return Task activity state for given task
 *
 ******************************************************************************/

OS_BoolType OS_IsTaskActive(OS_TaskID TaskID)
{
    const OS_TaskType* const pTask = &OS_TaskArray[TaskID];

#ifdef OS_DEBUG    
    if ( (0U > TaskID) || (OS_MaxTask <= TaskID) )
    {
        return OS_IdOutOfRange;
    }
#endif

    return (OS_BoolType)((0U != pTask->Expiration) || (0U != pTask->Reload));
}


/******************************************************************************
 * Function  : OS_ScheduleTasks
 *
 * Role      : Schedule every in ready state. Must be call periodically by OS
 *
 ******************************************************************************/
void OS_ScheduleTasks(void)
{
   OS_IndexType index = OS_MaxTask;
   OS_TaskType* pTask = OS_TaskArray;
   uint16_t OS_DiffTime;
   OS_TaskID curr_task;

   while ( (0U != index) && (0U != OS_Control.TasksToSchedule) )
   {
      if (0U != pTask->Schedule)
      {
         /* Decrease scheduler counters before executing task */
         OS_DisableSysTick();
         --pTask->Schedule;
         --OS_Control.TasksToSchedule;
         OS_EnableSysTick();
         /* Otherwise, calling CancelTask within pTaskFct will corrupt OS_Control */
         #if defined OS_CPU_LOAD
         //clear the diff time
         OS_GetDifTimer(&OS_DiffTime);
         pTask->pTaskFct();
         //get the curr task
         curr_task = OS_MaxTask - index;
         //save the consume time to current task info
         #ifndef QAC
         if(curr_task >= OS_Task_Wdg && curr_task<OS_MaxTask)
         #endif   
         {
             OS_SaveTaskThroughput(curr_task, OS_GetDifTimer(&OS_DiffTime));
         }
         #else
         pTask->pTaskFct();
         #endif
      }
      ++pTask;
      --index;
   }
}

/******************************************************************************
 * Function  : OS_TaskCheck
 *
 * Role      : Scan task array to check task scheduling coherency
 *
 ******************************************************************************/
void OS_TaskCheck(void)
{
   OS_IndexType index = OS_MaxTask;
   OS_TaskType* pCtrlTask = &OS_TaskArray[0];
   OS_IndexType schedule = 0;

   /* Need to disable tick interrupt for calculation */
   OS_DisableSysTick();

   /* Check every timer */
   while (0U != index)
   {
     schedule += pCtrlTask->Schedule;
     ++pCtrlTask;
     --index;
   }

   /* Compare newly calculated activity with OS_Control */
   if ( schedule!=OS_Control.TasksToSchedule )
   {
      OS_SelfCheckErrEvent(); /* call error handler */
      /* No way to recover, timed events may have been lost. */
      OS_SoftwareReset();
   }

   /* Enable tick interrupt */
   OS_EnableSysTick();
}
#endif

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date          Rev      userid    (Description on following lines: SCR #, etc)
 * ----------- --------  ---------  --------------------------------------------
 * 06-16-2011    1.1      rzlw3b     add test code for workload calculation  

 *                          
 *
 *
\*===========================================================================*/

/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

