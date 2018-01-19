/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS Timer ( OS Timer )
 *  File          : OS_Timer.c
 *-----------------------------------------------------------------------------
 *  Description   : OS Timer
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*----------------------------------------------------------------------------*
 *              --- Included files and compilation variables ---              *
 *----------------------------------------------------------------------------*/
#include "Systype.h"

#include "OS_Cfg.h"

#ifdef OS_TIMER_USED

#include "OS_Timer.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/
#define DIFF_INIT  0xFFFFU

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
 * Function  : OS_SetRelativeTimer
 *
 * Role      : Start a relative timer (expiration time is relative to call
 *               system time).
 *
 ******************************************************************************/

OS_Error OS_SetRelativeTimer( OS_TimerID TimerID,
                     OS_TimeType ExpirationTime, OS_TimeType CyclicTime,
                     OS_MsgIdType msgID)
{
   OS_TimerType* const pCtrlTimer = &OS_Control.Timer[TimerID];
   OS_Error Result = OS_NoError;
   
#ifdef OS_DEBUG
    if ( (TimerID<0) || (TimerID>=OS_MaxTimer) )
    {
        return OS_IdOutOfRange;
    }

    if ( 0U == ExpirationTime )
    {
        return OS_InvalidParameter;
    }
#endif

    if ( OS_FALSE == pCtrlTimer->Activ )
    {
        OS_DisableSysTick();

        /* Configure the whole timer structure */
        pCtrlTimer->Activ = OS_TRUE;
        pCtrlTimer->Expiration = OS_Control.Tick + ExpirationTime;
        pCtrlTimer->Reload = CyclicTime;
        pCtrlTimer->PostMsg = msgID;

#ifndef OS_1TICK_TIMER_OPTIMISED
        if ( 0U < OS_Control.TimerActivity)
        {
            const OS_TimeType this_diff = pCtrlTimer->Expiration - OS_Control.Tick;

            /* There other timer activity, set this one only */
            /* if timer expiration is before next expiration, replace next expiration time */
            if ( (this_diff) < (OS_Control.TimerNextEvent - OS_Control.Tick) )
            {
                OS_Control.TimerNextEvent = pCtrlTimer->Expiration;
            }
        }
        else
        {
            /* This is the only activ timer */
            OS_Control.TimerNextEvent = pCtrlTimer->Expiration;
        }
#endif
        OS_Control.TimerActivity++;

        OS_EnableSysTick();
    }
    else
    {
        Result = OS_TimerInUse;
    }
    
    
    return Result;
}

/******************************************************************************
 * Function  : OS_SetAbsoluteTimer
 *
 * Role      : Start a absolute timer (expiration time is absolute in system
 *               time).
 *
 ******************************************************************************/
/*
OS_Error OS_SetAbsoluteTimer( OS_TimerID TimerID,
                     OS_TimeType ExpirationTime, OS_TimeType CyclicTime,
                     OS_MsgIdType msgID)
{
    register OS_TimerType* pCtrlTimer = &OS_Control.Timer[TimerID];

#ifdef OS_DEBUG
    if ( (TimerID<0) || (TimerID>=OS_MaxTimer) )
    {
        return OS_IdOutOfRange;
    }

    if ( ExpirationTime==OS_Control.Tick )
    {
        return OS_InvalidParameter;
    }
#endif

    if ( pCtrlTimer->Activ==OS_FALSE )
    {
        OS_DisableSysTick();

        // Configure the whole timer structure
        pCtrlTimer->Activ = OS_TRUE;
        pCtrlTimer->Expiration = ExpirationTime;
        pCtrlTimer->Reload = CyclicTime;
        pCtrlTimer->PostMsg = msgID;

#ifndef OS_1TICK_TIMER_OPTIMISED
        if ( OS_Control.TimerActivity>0 )
        {
            OS_TimeType this_diff = pCtrlTimer->Expiration - OS_Control.Tick;

            // There other timer activity, set this one only
            // if timer expiration is before next expiration, replace next expiration time
            if ( (this_diff) < (OS_Control.TimerNextEvent - OS_Control.Tick) )
            {
                OS_Control.TimerNextEvent = pCtrlTimer->Expiration;
            }
        }
        else
        {
            // This is the only activ timer
            OS_Control.TimerNextEvent = pCtrlTimer->Expiration;
        }
#endif
        OS_Control.TimerActivity++;

        OS_EnableSysTick();

        return OS_NoError;
    }
    else
    {
        return OS_TimerInUse;
    }
}
*/
/******************************************************************************
 * Function  : OS_CancelTimer
 *
 * Role      : Cancel a timer
 *
 ******************************************************************************/

OS_Error OS_CancelTimer(OS_TimerID TimerID)
{
    
    OS_TimerType* const pCtrlTimer = &OS_Control.Timer[TimerID];
#ifndef OS_1TICK_TIMER_OPTIMISED
        /* If the cancelled timer expire at next programmed event time, we have to recompute next event */
        const OS_TimerType *pWalkingTimer = &OS_Control.Timer[0];
        
        OS_IndexType index = OS_MaxTimer;
        OS_TimeType  diff = DIFF_INIT;
#endif


#ifdef OS_DEBUG
    if ( (0U > TimerID) || (OS_MaxTimer <= TimerID) )
    {
        return OS_IdOutOfRange;
    }
#endif
    OS_DisableSysTick();

    if (OS_FALSE != pCtrlTimer->Activ)
    {
        /* If the timer was on, cancel it */

        pCtrlTimer->Activ = OS_FALSE;

        /* Decrease timer activity */
        OS_Control.TimerActivity--;

#ifndef OS_1TICK_TIMER_OPTIMISED
        if ( (0U != OS_Control.TimerActivity) && (pCtrlTimer->Expiration==OS_Control.TimerNextEvent) )
        {
            OS_IndexType activity = OS_Control.TimerActivity;

            while ( (0U != index) && (0U != activity) )
            {
               if ( pWalkingTimer->Activ != OS_FALSE )
               {
                  const OS_TimeType this_diff = pWalkingTimer->Expiration - OS_Control.Tick;

                  if ( this_diff < diff )
                  {
                     OS_Control.TimerNextEvent = pWalkingTimer->Expiration;
                     diff = this_diff;
                  }
                  activity--;
               }
               pWalkingTimer++;
               --index;
            }
        }
#endif
    }

    OS_EnableSysTick();

    return OS_NoError;
}

/******************************************************************************
 * Function  : OS_CancelAllTimers
 *
 * Role      : Cancel all timers
 *
 ******************************************************************************/

void OS_CancelAllTimers(void)
{
    OS_TimerType* pCtrlTimer = &OS_Control.Timer[0];

    OS_IndexType index;

    OS_DisableSysTick();
    for (index=0; index<OS_MaxTimer; index++)
    {
        pCtrlTimer->Activ = OS_FALSE;
        pCtrlTimer++;
    }

    OS_Control.TimerActivity = 0;
    OS_EnableSysTick();
}


/******************************************************************************
 * Function  : OS_TimerCheck
 *
 * Role      : Scan timer array to check timer activity coherency
 *
 ******************************************************************************/
void OS_TimerCheck(void)
{
    OS_IndexType index = OS_MaxTimer;
    OS_TimerType* pCtrlTimer = &OS_Control.Timer[0];
    OS_IndexType activ = 0;

    /* Need to disable tick interrupt for calculation */
    OS_DisableSysTick();

    /* Check every timer */
    while (0U != index)
    {
        /* Increment global activity if timer is set */
        if (OS_FALSE != pCtrlTimer->Activ)
        { 
            ++activ; 
        }
        /* And jump to next timer */
        ++pCtrlTimer;
        --index;
    }

    /* Compare newly calculated activity with OS_Control */
    if ( activ!=OS_Control.TimerActivity )
    {
        OS_SelfCheckErrEvent(); /* call error handler */
        /* No way to recover, timed events may have been lost. */
        OS_SoftwareReset();
    }

    /* Enable tick interrupt */
    OS_EnableSysTick();
}


/******************************************************************************
 * Function  : OS_IsTimerSet
 *
 * Role      : Return Timer activity state for given timer
 *
 ******************************************************************************/
OS_BoolType OS_IsTimerSet(OS_TimerID TimerID)
{
    const OS_TimerType* const pCtrlTimer = &OS_Control.Timer[TimerID];

#ifdef OS_DEBUG
    if ( (0U > TimerID) || (OS_MaxTimer <= TimerID) )
    {
        return OS_IdOutOfRange;
    }
#endif

    return pCtrlTimer->Activ;
}
void EcuM_OS_Sleep(uint16 ticks)
{
   OS_TimeType  currTime;

   currTime = OS_GetSysTick()+ticks;
   do
   {
       WdgM_Refresh();
   }
   while(currTime>OS_GetSysTick());
}
#endif

/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

