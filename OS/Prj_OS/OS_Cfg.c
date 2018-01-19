/*******************************************************************************
 *  Project       : 10021420
 *  SW component  : OS
 *  SW file       : %name:          OS_Cfg.c %
 *  Version       : %version:       2 %
 *  Instance      : %instance:      ctc_aud_5 %
 *  Author        : rz07l7
 *  Creation Date : Mon Mar 17 15:39:33 2008
 *----------------------------------------------------------------------------
 *  Last modification done
 *             by : %derived_by:    lzs7ws %
 *             on : %date_created:  Thu Jul 19 16:47:17 2012 %
 *----------------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description   : OS Configuration
 *
 */
/*-----------------------------------------------------------------------------
******************************************************************************/

/*----------------------------------------------------------------------------*
*              --- Included files and compilation variables ---              *
*----------------------------------------------------------------------------*/
#include "Systype.h"
#include "OS.h"
#include "OS_Task.h"
#include "OS_Timer.h"
#include "OS_FifoSys.h"
#include "EcuM.h"
#include "App_Powermode.h"
#include "WdgM.h"
#include "SchM.h"
#include "nvm.h"
#include "Key_scan.h"
#include "Polyspace.h"
#include "TIMER.h" 
#include "App_AMP.h" 
#include "CCA.h"
#include "uart.h"
/*----------------------------------------------------------------------------*
*                     --- Local constants & typedefs ---                     *
*----------------------------------------------------------------------------*/

/* !!!
    Message map MUST be ordered
    All messages must be handled, even with a NULL pointer
 */

#ifndef QAC

BEGIN_MESSAGE_MAP
ON_MESSAGE(OS_Msg_IPC_Process, NO_PARAM,    APP_IPC_Handler)
END_MESSAGE_MAP

/*
    Declare Tasks here
    DECLARE_TASK(task_name, period_in_ms)   if period_in_ms is 0, task is inactive at startup
    Task must be ordered like OS_TaskID declared in OS_Cfg.h
    task prototype is void-void, see pTaskHandler typedef
 */

#ifdef OS_TASK_USED
BEGIN_TASKS
/* Insert here the differents tasks */
DECLARE_TASK(&WdgM_Refresh, 0)
DECLARE_TASK(&Power_Task, 0)
DECLARE_TASK(&NVM_Task, 0)
DECLARE_TASK(&IoHwAb_KB_Task, 0)
DECLARE_TASK(&App_AMP_Control_Task, 0)
DECLARE_TASK(&CCA_Task, 0)
#if defined OS_CPU_LOAD || defined OS_PERF_METER
	DECLARE_TASK(&OS_PerfMeter, 0)
#endif
END_TASKS
#endif

/*
   Idle Hook functions, called on CPU idle with a period of at least OS_IDLE_HOOK_COUNTER
 */
#ifdef OS_IDLE_HOOK
BEGIN_IDLE_HOOK
ON_IDLE_HOOK(&Os_Idle_Task_Robustness)
END_IDLE_HOOK
#endif

#ifdef OS_EVENT_USED
BEGIN_EVENTS
/* Insert here the events used byt the application */
DECLARE_EVENT(Event)
END_EVENTS
#endif

#ifdef OS_DATAPIPE_USED
/* Insert here the data pipes used by the application
   Af first, define the data pipe buffer
   OS_DECLARE_DATAPIPE_BUFFER(data pipe's name, nBytes) */

OS_BEGIN_DATAPIPES
/* Second, here the data pipes used by the application
   OS_DECLARE_DATAPIPE(Data pipe's name) */
OS_END_DATAPIPES
#endif

#ifdef OS_MSGPIPE_USED
/* Insert here the message pipes used by the application
   Af first, define the message pipe buffer
    OS_DECLARE_MSGPIPE_BUFFER(Message pipe's name, nBytes) */

OS_BEGIN_MSGPIPES
/* Second, define the message pipes used by the application
        OS_DECLARE_MSGPIPE(Message pipe's name) */
OS_END_MSGPIPES
#endif
#endif
void OS_Dummy_enable(void)
{
}

/*.===================================================================*\
*. FUNCTION: OS_GetResetReason
*.=====================================================================
*. Return Value:
*.  Reset reason
*.
*. Parameters:
*. None
*.
*. External references: Mcu_GetResetReason
*.  External variables:
*.   EcuM_ResetCauseStatus
*.  File scope variables:
*.   None
*.
*. Description:  This function reads reset cause from MCU module
\*===================================================================*/

Mcu_ResetType OS_GetResetReason(void)
{
   return Mcu_GetResetReason();
}
void OS_EnableSysTick(void)
{
    Timer_Tick_Enable_Interrupt();
}
void OS_DisableSysTick(void)
{
    Timer_Tick_Disable_Interrupt();
}

/*============================================================================*\
*                             --- Variables ---
\*============================================================================*/

/*============================================================================*\
*                          --- Public functions ---
\*============================================================================*/

/*============================================================================*\
*                         --- Private functions ---
\*============================================================================*/

/******************************************************************************
*
* Date         By                        Change
* -----------------------------------------------------------------------------
* 28-Apr-10    SB       Task no.tci_ik#3382 for release 10024438_TCI/1.00.
                         Added post messages and tasks for DCM module.
* 30-Apr-10    KS       Added Periodic tasks for release 10024438_TCI/1.00.
                        -NvM_MainFunction and NvM_Handler
* 06-May-10    KS       Removed Periodic task for release 10024438_TCI/1.00.
                        -NvM_Handler
* 07-May-10  IPM      Added ASV_Mainfunction into the message list
* 19-May-10  IPM      Changed ASV_Mainfunction() to ONE_PARAM type, Added OS_Msg_COM_MainFunction;
* 19-May-10  IPM      Added IoHwAb_WHL_Task
* 20-May-10  IPM      Added RAT_MainFunction
* 20-May-10    SB   Task no.tci_ik#3437 for release 10024438_TCI/1.00.
                     added timers and post messages for BLKL.
* 20-May-10    KS       Added Periodic task and post message for release 10024438_TCI/1.00.
     - DDP_MainFunction, DDP_Process_RequestContextSave, DDP_Process_ConfirmFaultStatus
     - DDP_Process_ReportRtEvent, DDP_CallBk_OnLifePhaseChange
* 26-May-10    SB   Task no.tci_ik#3478 for release 10024438_TCI/1.00.
                     Added timers and post messages for DCM.
* 31-May-10  IPM      Task no.tci_ik#3530 for release 10024438_TCI/1.00.
*                   Append prefix 'App_' to all application interface names 
* 01-Jun-10  IPM      Task no.tci_ik#3550 for release 10024438_TCI/1.00.
*                   Add WdgM component
* 25-Jun-10  IPM      Task no.tci_ik#3752 for release 10024438_TCI/2.00.
*                Added timers/messages to filter HVAC PUSH signals in App_COM_Filt module 
* 28-Jun-10 KS      Task no.tci_ik#3700 for release 10024438_TCI/2.00.
*                   Changed to DDP_Process_RequestRTContextSave
* 29-Jun-10  SB      Task no.tci_ik#3754 for release 10024438_TCI/2.00.
*                   Added messages for function LED backligthing related functions.
* 09-JUL-10  HI     Task no . tci_ik#3802 Changed name of OS_Msg_App_RAT_MainFunction 
*                             to OS_Msg_App_RAT_Control_Event.
*                             Changed TASK IoHwAb_WHL_Task to IoHwAb_WHL_AcquisitionTask.

*09-Jul-10    KK    Task no.tci_ik#3793 for release 10024438_TCI/2.00.
                     Added HSM Tasks, Post messages and timers.
*15-Jul-10   HI     task no tci_ik#3803 declare task App_RAT_AutoTestTask 

* 15-Jul-10  KK       Task no.tci_ik#3812 for release 10024438_TCI/2.00.
*                      Implementation of new OS message structure
* 16-Jul-10    KS    Task no.tci_ik#3824 for release 10024438_TCI/2.00.
*                  Changed DDP_MainFunction() to DDP_Task() as per SAD ver 1.8 
* 19-Jul-10    KK    Task no.tci_ik#3829 for release 10024438_TCI/2.00.
*                      Function name changed as per SAD version 01.8
* 19-Jul-10    KS    Task no.tci_ik#3823 for release 10024438_TCI/2.00.
*                    Modified NVN_MainFunction to NVM_Task as per SAD v1.9.
* 19-Jul-10    KS    Task no.tci_ik#3834 for release 10024438_TCI/2.00.
*                    VOY_LUCH and AFF_LUCH interfaces added.
* 19-Jul-10    KS    Task no.tci_ik#3806 for release 10024438_TCI/2.00.
*                    Changed Two param to one param for bkl time out function.
* 20-Jul-10    KK    Task no.tci_ik#3835 for release 10024438_TCI/2.00.
*                     New message added for COM loss management in App_HSM.
* 03-Aug-10    SB    Task no.tci_ik#3896 for release 10024438_TCI/2.00.
                     Modification as per IK code review document v00.7.
* 05-Aug-10   IPM   Task no.tci_ik#3914 for release 10024438_TCI/2.00.
*                    Changed the OS_PostMessage as per IK review comments
* 30-Sep-10   KK    Task No. 4234 for release 10024438_TCI/3.00.
*                   Added message for ETAT_GMP signal
* 01-Oct-10   KS     Task No tci_ik#4117 for release 10024438_TCI/3.00.
*                    Removed OS_Msg_DDP_CallBk_OnLifePhaseChange.
* 01-Oct-10   RS    Task no.tci_ik#4197 for release 10024438_TCI/3.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.14 Nr 48,52,55.
*                   Added/Renamed Messages.
* 04-Oct-10   KK    Task no.tci_ik#4197 for release 10024438_TCI/3.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.14 Nr 48,52,55.
*                   Added/Renamed Messages.
* 04-Oct-10  KK    Task N0. 4267 for release 10024438_TCI/3.00.
*                   Implementation of MODE_HY and UB_MODE_HY functionality
*
* 29-Nov-10    KS   Task no.tci_ik#4422 for release 10024438_TCI/4.00.
*   -App_BKL/App_DIAG:Modification as per SAD verification document
*
* 02-Dec-10    KS   Task no.tci_ik#4424 for release 10024438_TCI/4.00.
*   -Removed DDP_Process_ReportRtEvent
*
* 02-Dec-10   KS    Task no.tci_ik#4423 for release 10024438_TCI/4.00..
*   -Modification of the software component as per SAD verification report 
*   -ID SWIT-MTC-SAD-117-01
*05-Dec-10  HI     Task No tci_ik#4495 for the release 10024438_TCI/4.00
*                  Removal of a ORANGE warning(polyspace)
* 08-Dec-10  JJ     Task No.tci_ik#4459 for release 10024438_TCI/4.00
*                   Added the robustness req $-00.1-0037
* 14-Dec-10  JJ     Task No.tci_ik#4553 for release 10024438_TCI/4.00
*                   Implemented the SAD req -03.3-0100
* 16-Dec-10  KS     Task no.tci_ik#4457 for release 10024438_TCI/4.00.
*   - Added event OS_MESSAGE_RESTORE_DEFAULT.
* 17-Dec-10    KS   Task no.tci_ik#4589 for release 10024438_TCI/4.00.
*   Added event OS_Msg_App_DIAG_IOCBI_BklConnective_Timeout
* 22-Dec-10    KK   Task no.tci_ik#4626 for release 10024438_TCI/4.00.
*   Added new function OS_GetResetReason
* 28-Dec-10    KS   Task no.tci_ik#4662 for release 10024438_TCI/4.00.
*   -Update of the software component compatible with SAD for v4.0
* 05-Jan-11  KK    Task no.tci_ik#4682 for release 10024438_TCI/4.00.
*                   Changes done tobe compatible with SAD
* 06-Jan-10    KS   Task no.tci_ik#4387 for release 10024438_TCI/4.00.
*   -Modified OS message name as per SAD
* 07-Jan-10    KS   Task no.tci_ik#4705 for release 10024438_TCI/4.00.
*   -Modified OS message name as per SAD
******************************************************************************/

