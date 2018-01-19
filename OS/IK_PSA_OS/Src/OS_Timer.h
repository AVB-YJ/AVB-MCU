/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS Timer ( OS Timer )
 *  File          : OS_Timer.h
 *-----------------------------------------------------------------------------
 *  Description   : OS Timer
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*-------------------------------------------------------------------
 * to avoid multiple definition if the file is included several times
 *-------------------------------------------------------------------*/
#ifndef OS_TIMER_H
#define OS_TIMER_H

#include "OS.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                         --- Global Variables ---                           *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/
#ifdef OS_TIMER_USED

OS_Error OS_SetRelativeTimer(OS_TimerID TimerID,
                             OS_TimeType ExpirationTime, OS_TimeType CyclicTime,
                             OS_MsgIdType msgID);

OS_Error OS_SetAbsoluteTimer(OS_TimerID TimerID,
                             OS_TimeType ExpirationTime, OS_TimeType CyclicTime,
                             OS_MsgIdType msgID);

OS_Error OS_CancelTimer(OS_TimerID TimerID);

void OS_CancelAllTimers(void);

void OS_TimerCheck(void);

OS_BoolType OS_IsTimerSet(OS_TimerID TimerID);
//added by wade.li
void EcuM_OS_Sleep(uint16 ticks);

#endif

#endif /* OS_Timer_h*/
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/
