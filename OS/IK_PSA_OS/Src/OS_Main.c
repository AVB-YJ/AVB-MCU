/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS Main ( OS main )
 *  File          : OS_Main.c
 *-----------------------------------------------------------------------------
 *  Description   : OS main
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/
/* Module Name:    os main
* Created By:      wade.li
* Created Date:    04/07/2011
* %version:        2 %
* date_modified:  Tue Apirl 7 13:02:04 2011 %
*--------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *              --- Included files and compilation variables ---              *
 *----------------------------------------------------------------------------*/

#include "OS.h"
#include "OS_FifoSys.h"
#include "TIMER.h"
#ifdef OS_TASK_USED
#include "OS_Task.h"
#endif
#ifdef OS_EVENT_USED
#include "OS_Event.h"
#endif
#ifdef OS_DATAPIPE_USED
#include "OS_DataPipe.h"
#endif
#ifdef OS_MSGPIPE_USED
#include "OS_MsgPipe.h"
#endif
#include "StackCk.h"
#include "String.h"
/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/
#define EXPDIFF 0xFFFFU

#define TIMER_MUL   1000

#if (defined OS_CPU_LOAD || defined OS_PERF_METER)

/*
#define OS_PERF_SHIFT8    8
#define OS_PERF_SHIFT1    1

#define OS_PERF_IDL_BYTE    0
#define OS_PERF_USR_BYTE    1
#define OS_PERF_SYS_BYTE    2
#define OS_PERF_INT_BYTE    3
#define OS_PERF_P1_BYTE     4
#define OS_PERF_P2_BYTE     5
#define OS_FIFO_SYS_BYTE    6
#define OS_PERF_MAX_BYTE    7

#define DEBUG_SIZE  8
typedef struct
{
    uint8_t Data[DEBUG_SIZE];
    uint8_t System_MaxLoad;
} t_IPL_stDEBUG_HDC;

static t_IPL_stDEBUG_HDC IPL_stDEBUG_HDC = {{0,0,0,0,0,0,0,0},0};
*/

#define MAX_THROUGH_ARR 5
static uint16 throughput_ARR[MAX_THROUGH_ARR];
static uint8_t curr_pos=0;
#endif

/*----------------------------------------------------------------------------*
 *                             --- Variables ---                              *
 *----------------------------------------------------------------------------*/

/* OS_Control struct is not initialised because of its variable size according to OS facilities used */
/* Init is made by memset in OS_Init. */
OS_ControlType OS_Control;

#if (defined OS_CPU_LOAD || defined OS_PERF_METER)
static OS_PerfCtrl OS_PerfControl = 
{ 
   OS_Idle, 0, 0,
   0, 0, 0,
   0, 0,
   0, 0, 0,
   0, 0, 0 
};
#endif

/*----------------------------------------------------------------------------*
 *                    --- Local functions declaration ---                     *
 *----------------------------------------------------------------------------*/

static void OS_DispatchMessage(const OS_Msg* msg);
#ifdef OS_DEBUG
static void OS_SelfCheck(void);
#endif
#ifdef OS_TIMER_USED
static void OS_CheckTimers(void);
#endif
#ifdef OS_TASK_USED
static void OS_CheckTasks(void);
#endif

static void OS_StartupHook(void);

#if (defined OS_CPU_LOAD || defined OS_PERF_METER)
static void OS_PerfMeterHook(void);
static void OS_PerfEnableDisable(OS_BoolType en);
#endif


/*----------------------------------------------------------------------------*
 *                          --- Local functions ---                           *
 *----------------------------------------------------------------------------*/


/******************************************************************************
 * Function  : OS_DispatchMessage
 *
 * Role      : Dispatch message
 *
 ******************************************************************************/
static void OS_DispatchMessage(const OS_Msg* msg)
{
   const pMsgHandler0 pThisFct = MsgHandler[msg->MsgId].pFct;
   const pMsgHandler1 pThisFct1 = (pMsgHandler1)MsgHandler[msg->MsgId].pFct;
   const pMsgHandler pThisFct2 = (pMsgHandler)MsgHandler[msg->MsgId].pFct;
   const OS_MsgHandlerType * const pThisMsg = &MsgHandler[msg->MsgId];
   
#ifdef OS_DEBUG
    if ( (msg!=0) &&  (msg->MsgId>=0) && (msg->MsgId<OS_MsgIDmax) )
    {
#endif
        if (0 == pThisMsg->ParamNb)
        {
            if ( pThisFct != (pMsgHandler0)0 )
            {
                pThisFct();
            }
        }
        else if (1 == pThisMsg->ParamNb)
        {
            if ( pThisFct1 != (pMsgHandler1)0 )
            {
                pThisFct1(msg->Param1);
            }
        }
        else
        {
            if ( pThisFct2 != (pMsgHandler)0 )
            {
                pThisFct2(msg->Param1, msg->Param2);
            }
        }
#ifdef OS_DEBUG
    }
    else
    {
        OS_SoftwareReset();
    }
#endif
}

/******************************************************************************
 * Function  : OS_SelfCheck
 *
 * Role      : Self check
 *
 ******************************************************************************/

#ifdef OS_DEBUG
static void OS_SelfCheck(void)
{
    OS_IndexType index;

    /* Check message size for optimisation */
/*
    if ( sizeof(OS_Msg)!=4 )
    {
        while(1);
    }
*/
    /* Check Message Map coherency */
    for (index=0; index<OS_MsgIDmax; index++)
    {
        if ( MsgHandler[index].MsgId != index )
        {
            while (1);
        }
    }
}
#endif

/******************************************************************************
 * Function  : OS_CheckTimers
 *
 * Role      : Check timers
 *                This function is called when, at least, one timer has expired
 *
 ******************************************************************************/
#ifdef OS_TIMER_USED
static void OS_CheckTimers(void)
{
    OS_IndexType NofActivTimers = OS_Control.TimerActivity;
    OS_TimerType *pWalkingTimer = &OS_Control.Timer[0];
    OS_IndexType index = OS_MaxTimer + 1;
#ifndef OS_1TICK_TIMER_OPTIMISED
    OS_TimeType NextExpirationDiff = EXPDIFF;

#endif

    /* Shorten check timer as soon as all activ timers have been found */
    while ( 0U != NofActivTimers )
    {
        --index;
        if ( pWalkingTimer->Activ != OS_FALSE )
        {
            /* If timer is activ */
            if ( pWalkingTimer->Expiration == OS_Control.Tick )
            {
                /* The msg is declared static to avoid unused param2 init at every loop */
                static OS_Msg OS_TimerMsg = {0,0,0};
                /* If timer has expired */
                /* Prepare message to post */
                OS_TimerMsg.MsgId = pWalkingTimer->PostMsg;
                OS_TimerMsg.Param1 = OS_MaxTimer-index;

                /* Post in system queue */
                OS_FifoSys_PushBack(&OS_TimerMsg);

                /* Reload timer if cyclic */
                if ( 0U != pWalkingTimer->Reload)
                {
                    /* Reload timer */
                    pWalkingTimer->Expiration = OS_Control.Tick + pWalkingTimer->Reload;
                }
                else
                {
                    /* Disable timer */
                    pWalkingTimer->Activ = OS_FALSE;

                    /* Decrease TimerActivity */
                    OS_Control.TimerActivity--;
                }
            }
#ifndef OS_1TICK_TIMER_OPTIMISED
            /* If the timer is still activ */
            if ( pWalkingTimer->Activ != OS_FALSE)
            {
                /* Will this timer expire before next programmed event or not ? */
                const OS_TimeType this_diff = pWalkingTimer->Expiration - OS_Control.Tick;

                /* If there is no timer event foreseen, set this one */
                /* Or if there is a timer event foreseen, but timer expiration is before next expiration, replace it */
                if ( this_diff < NextExpirationDiff )
                {
                    OS_Control.TimerNextEvent = pWalkingTimer->Expiration;
                    NextExpirationDiff = this_diff;
                }
            }
#endif
            NofActivTimers--;
        }
        pWalkingTimer++;
    }
}
#endif

/******************************************************************************
 * Function  : OS_CheckTasks
 *
 * Role      : Check tasks
 *                This function is called periodically, at each system tick
 *              It will update task schedule counter but will not schedule tasks by itself
 *
 ******************************************************************************/
#ifdef OS_TASK_USED
static void OS_CheckTasks(void)
{
   OS_TaskType* pThisTask = OS_TaskArray;

   while (pThisTask != &OS_TaskArray[OS_MaxTask])
   {
     if ( 0U != pThisTask->Expiration)
     {
         --pThisTask->Expiration;
         if ( 0U == pThisTask->Expiration)
         {
             ++pThisTask->Schedule;
             ++OS_Control.TasksToSchedule;
             pThisTask->Expiration = pThisTask->Reload;
         }
     }
     ++pThisTask;
   }
}
#endif

/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/


 /******************************************************************************
 * Function  : OS_Init
 *
 * Role      :
 *
 ******************************************************************************/
void OS_Init(void)
{
    /* Initialised main OS data structure to 0 */
    uint16_t Count;
    uint8_t *ptData = (uint8_t *)&OS_Control;

    for (Count = 0;Count < (uint16_t)sizeof(OS_Control);Count++)
    {
        *ptData = 0;
        ptData++;
    }
#if defined OS_DEBUG
    OS_SelfCheck();
#endif
    /* Initialisation of the 2 queues */
    OS_FifoSys_Reset();

    /* Int all pipes */
#ifdef OS_EVENT_USED
    OS_ClearAllEvents();
#endif
#ifdef OS_DATAPIPE_USED
    OS_ClearAllDataPipes();
#endif
#ifdef OS_MSGPIPE_USED
    OS_ClearAllMsgPipes();
#endif

    OS_StartupHook();
}

/******************************************************************************
 * Function  : OS_Run
 *
 * Role      : Run ...
 *
 ******************************************************************************/
void OS_Run(void)
{

#ifdef OS_IDLE_HOOK
static OS_IndexType last_idle = OS_IDLE_HOOK_COUNTER;
static const pIdleHook* idle_hook = IdleHookHandler;
#endif

#ifdef OS_CPU_LOAD
        static uint16_t OS_DiffTime;
#endif

        OS_Msg msg;
        OS_IndexType OS_Fifo_Index;


#ifdef OS_TASK_USED
        /* Check System tasks for scheduling */
        while (0U != OS_Control.TasksToSchedule)
        {
#ifdef OS_PERF_METER
            /* Store Entering time */
            (void)OS_GetDifTimer(&OS_PerfControl.FreeRunCounter);

            /* Switch current Running level */
            OS_PerfControl.CurrentLevel = OS_System;
#endif
            /* At least one task to schedule */
            OS_ScheduleTasks();
#ifdef OS_PERF_METER
            /* Retrieve exit time, Compute elapsed time until last Idle and Add it to System counter */
            OS_PerfControl.SystemLoad += OS_GetDifTimer(&OS_PerfControl.FreeRunCounter);

            /* Switch current Running level */
            OS_PerfControl.CurrentLevel = OS_Idle;
#endif
        }
#endif

        /* Check System fifo for pending message */
        OS_Fifo_Index = OS_FifoSys_Pending();
        if ( 0U != OS_Fifo_Index )
        {
#ifdef OS_PERF_METER
            /* Store Entering time */
            (void)OS_GetDifTimer(&OS_PerfControl.FreeRunCounter);

            /* Switch current Running level */
            OS_PerfControl.CurrentLevel = OS_User;
#endif
            /* We do not test PopFront return because we know
               there is at least one pending message */
            (void)OS_FifoSys_PopFront(&msg);

            /* Dispatch this message by calling associated handler */
            OS_DispatchMessage(&msg);
#ifdef OS_PERF_METER
            /* Retrieve exit time, Compute elapsed time until last Idle and Add it to System counter */
            OS_PerfControl.UserLoad += OS_GetDifTimer(&OS_PerfControl.FreeRunCounter);

            /* Switch current Running level */
            OS_PerfControl.CurrentLevel = OS_Idle;
#endif
        }
        else
        {
        /* Call Idle time hook */
#ifdef OS_IDLE_HOOK
            /* Idle Hook calls */
            --last_idle;
            if ( 0U == last_idle)
            {
                /* OS_IDLE_HOOK_COUNTER loops elapsed, call an idle hook */
                if ( 0U != (*idle_hook) )
                {
                    /* call hook function */
                    (*idle_hook)();
                    /* jump to next hook function */
                    ++idle_hook;
                }
                else
                {
                    /* rebind first hook function */
                    idle_hook = IdleHookHandler;
                }
                last_idle = OS_IDLE_HOOK_COUNTER;
            }
#endif
#ifdef OS_CPU_LOAD
            /* Simple CPU load meter: compute elapsed time since last Idle */
            OS_DiffTime = OS_GetDifTimer(&OS_PerfControl.OS_LastIdle);
            /* If elapsed time is >> idle time loop time */
            if ( OS_DiffTime > (uint16_t)OS_PERF_EMPTY_LOAD )
            {
                    /* Add it to System Load */
                    OS_PerfControl.SystemLoad += OS_DiffTime;

                    if ( OS_DiffTime > OS_PerfControl.MaxTaskTime )
                    {
                        OS_PerfControl.MaxTaskTime = OS_DiffTime;
                    }
            }
#endif
        }
}

/******************************************************************************
 * Function  : OS_SysTick
 *
 * Role      : System tick
 *
 ******************************************************************************/
void OS_SysTick(void)
{
    OS_PRE_SYSTICK();

    /* This function must be called cyclic by hardware timer */
    OS_Control.Tick++;
#ifdef OS_TASK_USED
    OS_CheckTasks();
#endif

#ifdef OS_TIMER_USED
#ifndef OS_1TICK_TIMER_OPTIMISED
    if ( (0U != OS_Control.TimerActivity) && (OS_Control.Tick == OS_Control.TimerNextEvent) )
    {
        OS_CheckTimers();
    }
#else
    OS_CheckTimers();
#endif
#endif
#ifdef OS_POST_SYSTICK
    OS_POST_SYSTICK();
#endif
}
/******************************************************************************
 * Function  : OS_Wait
 *
 * Role      : Activ wait n us
 *
 ******************************************************************************/
#if defined OS_PERF_METER || defined OS_CPU_LOAD
// wait x uS
void OS_Wait(uint8_t OS_time)
{

    uint8_t i = OS_time;  

    //last = OS_time;
    while(i--)
    {
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation();
       __no_operation(); 
       __no_operation();
       __no_operation();
       __no_operation();// 1.0
       __no_operation();// 1.0
       __no_operation();// 1.0
    }
}
/*===========================================================================*
 *       Name: Delay
 *    Purpose: Assembly delay. Temporal function required by BB, will be moved
 *             to util.c when integrated into code
 * Parameters: time in usec
 *    Returns: none
 *===========================================================================*/
void OS_Delay(uint8_t usec)            /* loop execution time is 4 cycles which at ~4 MHz is 1 us per loop */
{
   asm ("LOOP: DEC A");
   asm ("BNZ   LOOP");
}
#endif

/******************************************************************************
 * Function  : OS_StartupHook
 *
 * Role      : Startup function
 *
 ******************************************************************************/

static void OS_StartupHook(void)
{
/* Insert here all the user functions that must be called in the OS Startup function */

#if defined OS_CPU_LOAD || defined OS_PERF_METER
    OS_PerfEnableDisable(OS_TRUE);
#endif
}



#if defined OS_CPU_LOAD || defined OS_PERF_METER
#if 0
uint8_t OS_GetMaxCPULoad(void) 
{
    return IPL_stDEBUG_HDC.System_MaxLoad;
}

uint8_t OS_GetCPULoad(void) 
{
    return IPL_stDEBUG_HDC.Data[OS_PERF_SYS_BYTE];
}

/******************************************************************************
 * Function  : OS_ResetMaxCPULoad
 *
 * Role      : Reset the max data of CPU load
 *
 ******************************************************************************/
void OS_ResetMaxCPULoad(void) 
{
  IPL_stDEBUG_HDC.System_MaxLoad = 0;
}


#endif

/******************************************************************************
 * Function  : OS_PerfMeterHook
 *
 * Role      : Called cyclic, pass performance indicator to application.
 *
 ******************************************************************************/
static void OS_PerfMeterHook(void)
{
    OS_TaskID task_id;
    int8_t actual_systemLoad;
    
    /* Compute load as %, where OS_PERF_FULL_LOAD equals 100% */
    /* Because WDC can't optimize /=512, let's do it by hand... */
    OS_PerfControl.SystemLoad  /= (uint32_t)(OS_PERF_FULL_LOAD / OS_PERF_100PERCENT);
    for(task_id =OS_Task_Wdg; task_id<OS_MaxTask; task_id++)
    {
        if(OS_PerfControl.TaskLoad[task_id]!=0)
        {
            OS_PerfControl.TaskLoad[task_id] /= (uint32_t)(OS_PERF_FULL_LOAD / OS_PERF_100PERCENT);
        }
    }
    #if defined OS_CPU_LOAD || defined OS_PERF_METER
    //wade added: remove the cpuload task workload, since it's not included to the system throughput
    if(OS_PerfControl.TaskLoad[OS_Task_CpuLoad]>0)
    {
        actual_systemLoad = OS_PerfControl.SystemLoad - OS_PerfControl.TaskLoad[OS_Task_CpuLoad];
        OS_PerfControl.SystemLoad = (actual_systemLoad>0)?  actual_systemLoad:0;
    }
    #endif

#if 0    
    IPL_stDEBUG_HDC.Data[OS_PERF_SYS_BYTE] = (uint8_t)(OS_PerfControl.SystemLoad);
    if (IPL_stDEBUG_HDC.System_MaxLoad < OS_PerfControl.SystemLoad)
    {
        IPL_stDEBUG_HDC.System_MaxLoad = (uint8_t)OS_PerfControl.SystemLoad;
    }

#ifdef OS_PERF_METER
    OS_PerfControl.UserLoad /= (OS_PERF_FULL_LOAD/OS_PERF_100PERCENT);
    IPL_stDEBUG_HDC.Data[OS_PERF_USR_BYTE] = (uint8_t)(OS_PerfControl.UserLoad);

    OS_PerfControl.InterruptLoad /= (OS_PERF_FULL_LOAD/OS_PERF_100PERCENT);
    IPL_stDEBUG_HDC.Data[OS_PERF_INT_BYTE] = (uint8_t)(OS_PerfControl.InterruptLoad);
#endif
#endif
}






/******************************************************************************
 * Function  : OS_GetAveThroughput
 *
 * Role      : get the average throughput and reset the record array.
 *
 ******************************************************************************/
uint8_t OS_GetAveThroughput(void)
{
    uint16 ave_thr =0;
    uint8_t i =0;

    while(i<MAX_THROUGH_ARR)
    {
        ave_thr+=throughput_ARR[i];
        i++;
    }
    ave_thr/=MAX_THROUGH_ARR;
     
    memset(throughput_ARR, 0, sizeof(throughput_ARR));
    curr_pos = 0;
    
    return ave_thr;
}
/******************************************************************************
 * Function  : OS_SaveCurrThroughput
 *
 * Role      : save the current system throughput
 *
 ******************************************************************************/
static void OS_SaveCurrThroughput(uint32_t through)
{

    throughput_ARR[curr_pos]= (uint16_t)through;
    
    if(curr_pos < (MAX_THROUGH_ARR-1))
    {
        curr_pos++;
    }
    else
    {
       curr_pos = 0;
    }

}
/******************************************************************************
 * Function  : OS_SaveTaskThroughput
 *
 * Role      : save the current task throughput
 *
 ******************************************************************************/
void OS_SaveTaskThroughput(OS_TaskID index, uint16_t through)
{
    if(index< OS_MaxTask)
    {
        OS_PerfControl.TaskLoad[index] += through;
    }
    
}
/******************************************************************************
 * Function  : OS_PerfMeter
 *
 * Role      : Compute perf indicators, cyclic called by timer
 *
 ******************************************************************************/
void OS_PerfMeter(void)
{
    static uint8_t i=0;
    uint8_t index;
//    uint8 OsThroughPut;

    
#ifdef OS_PERF_METER
    /* Interrupts have to be disabled to maintain accurate Interrupt Load */
    OS_DisableAllInterrupts();

    /* Call PerfMeter hook to treat values */
    OS_PerfMeterHook();
    /* Reset statistics */
    OS_PerfControl.SystemLoad    = 0;
    OS_PerfControl.UserLoad      = 0;
    OS_PerfControl.InterruptLoad = 0;

    OS_EnableAllInterrupts();
#endif

#ifdef OS_CPU_LOAD
    /* Diff time since last idle has to be added to system load */
    /* Add it to System Load */
    //OS_PerfControl.SystemLoad += OS_GetDifTimer(&OS_PerfControl.OS_LastIdle);

    /* Call PerfMeter hook to treat values */
    OS_PerfMeterHook();

    OS_SaveCurrThroughput(OS_PerfControl.SystemLoad);

    if(i< (MAX_THROUGH_ARR))
    {
        i++;
    }
    else
    {     
        i=0;
        //write to lIN every 200ms*5, OS_GetAveThroughput(), StackCk_GetUserStackSize
        //#ifdef ICS_HVAC_IS
        //LIN_SIL_vWriteByte(CPU_LOAD, OS_GetAveThroughput());
        //#else
        //LIN_SIL_vWriteByte(ENCODER_MENU, OS_GetAveThroughput());
        //#endif
//        OsThroughPut    =  OS_GetAveThroughput();
//        UARTF1_SendData(&OsThroughPut,1);
    }
    /* Reset statistics */
    OS_PerfControl.SystemLoad       = 0;
    OS_PerfControl.UserLoad         = 0;
    OS_PerfControl.InterruptLoad    = 0;
    OS_PerfControl.MaxTaskTime      = 0;
    for(index =0; index<OS_MaxTask; index++)
    {
        OS_PerfControl.TaskLoad[index] = 0;
    }

#endif

#ifdef OS_PERF_P1P2
    OS_PerfControl.P1Load = OS_PerfControl.P2Load = 0;
#endif

}

/******************************************************************************
 * Function  : OS_PerfEnableDisable
 *
 * Role      : Start or stop the performance meter process
 *
 ******************************************************************************/

static void OS_PerfEnableDisable(OS_BoolType en)
{
    if ( en == OS_FALSE )
    {
        (void)OS_CancelTask(OS_Task_CpuLoad);
    }
    else
    {
        (void)OS_ActivateTask(OS_Task_CpuLoad, OS_Task_CpuLoad_Offset, OS_Task_CpuLoad_Period);
    }
}

#endif

/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

