/*******************************************************************************
 *  Project       : 10021420
 *  SW component  : OS
 *  SW file       : %name:          OS_Cfg.h %
 *  Version       : %version:       3 %
 *  Instance      : %instance:      ctc_aud_5 %
 *  Author        : rz07l7
 *  Creation Date : Mon Mar 17 15:39:35 2008
 *----------------------------------------------------------------------------
 *  Last modification done
 *             by : %derived_by:    lzs7ws %
 *             on : %date_created:  Mon Jan 21 15:21:41 2013 %
 *----------------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description   : OS Configuration
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/* To avoid multiple definition if the file is included several times */
#ifndef OS_CFG_H
#define OS_CFG_H

#include "Systype.h"
#include "EcuM.h"
#include "Hw_Reg.h"
#include "WdgM.h"
#include "Mcu.h"
#include "intrinsics.h"
#include "Polyspace.h"
void OS_Dummy_enable(void);
Mcu_ResetType OS_GetResetReason(void);
/*----------------------------------------------------------------------------*
*                     --- Local constants & typedefs ---                     *
*----------------------------------------------------------------------------*/

/*
    This section defines the basic object types used by OS.
    They must be checked and configured for each target.
 */
typedef uint16_t  OS_IndexType;        /* Used for array index, must be unsigned and fastest target type for performance optimisation */
typedef uint8_t   OS_MsgIdType;        /* Used for message map, must be unsigned and large enough to code OS_MsgIDmax (8 bits for OS_MsgIDmax <= 255) */
typedef uint16_t  OS_MsgParamType1;    /* First message parameter, user defined */
typedef uint8_t   OS_MsgParamType2;    /* Second message parameter, user defined */
typedef uint32_t  OS_TimeType;        /* Used for time representation, must be unsigned and sized for holding the max timer value (8 bits for max timer value <= 255) */
typedef bool_t    OS_BoolType;        /* Boolean type, must be unsigned and fastest target type for performance optimisation */

#define OS_TRUE         (OS_BoolType)1
#define OS_FALSE        (OS_BoolType)0

/*
    The macro OS_MsgCopy is used to copy an OS_Msg content.
    You should define the quickest way to perform the copy.

    Generally, the compiler will correctly optimise the structure copy:

 #define OS_MsgCopy(msg1, msg2) { *msg1=*msg2; }

    If the previous version is correctly handled, you should try a member by member copy:

 #define OS_MsgCopy(msg1, msg2) { msg1->MsgId=msg2->MsgId; msg1->Param1=msg2->Param1; msg1->Param2=msg2->Param2; }
 */
#ifdef POLYSPACE
#define OS_MsgCopy(msg1, msg2) { *msg1 = *msg2; }
#else
/* use one of the following lines according to the compiler speed optimization */
/* #define OS_MsgCopy(msg1, msg2) ((OS_MsgIdType*)(void*)msg1)[0]=((const OS_MsgIdType*)(const void*)msg2)[0]; ((OS_MsgParamType1*)(void*)msg1)[1]=((const OS_MsgParamType1*)(const void*)msg2)[1]; ((OS_MsgParamType2*)(void*)msg1)[2]=((const OS_MsgParamType2*)(const void*)msg2)[2]*/
#define OS_MsgCopy(msg1, msg2) *msg1 = *msg2
#endif

/* IPC defines */
typedef unsigned short OS_EventType;           /* Must be unsigned and large enough to stand for all signals defined in an event */

#define OS_SelfCheckErrEvent()  EcuM_SetNoInitByte (OS_SELFCHECKS_RESET) /* robustness function */

#define OS_IDLE_HOOK                    /* Define this to use Idle Hook feature */
#define OS_IDLE_HOOK_COUNTER    (OS_IndexType) 10000     /* Schedule Idle Hook every 100ms (~XXX OS loops on this implementation) (adjust XXX on your target implementation) */

/* If something to do at the very begining of the SysTick routine */
#define OS_PRE_SYSTICK()  OS_Dummy_enable() /* MCUEnableAllInterrupts()  */

/* If something to do at the very end of the SysTick routine */
/* #define OS_POST_SYSTICK() */

#ifndef POLYSPACE
/* interrupts enable/disable functions */
#define OS_EnableAllInterrupts()  __enable_interrupt() /* MCUEnableAllInterrupts */
#define OS_DisableAllInterrupts() __disable_interrupt() /* MCUDisableAllInterrupts */
#endif

#define OS_GetDifTimer(a)  EcuM_GetDifBaseTimerStepValue(a) /* Returns the difference between old and new count */

#define OS_GetFreeRunCounter() RCP_CPU_Load_TimerRemain()  /* Timer 2 Channel 0 -- 0.66Micro Sec { Multiply with 2/3 for 1 Micro sec count}*/

//#define OS_EnableSysTick()    ENABLE_INTERRUPT_OS_SYS_TICK() //Gpt_EnableNotification(GPT_CHANNEL_9)   //ENABLE_INTERRUPT_OS_SYS_TICK()         // /*  MCUEnable() */
//#define OS_DisableSysTick()   DISABLE_INTERRUPT_OS_SYS_TICK() //Gpt_DisableNotification(GPT_CHANNEL_9)  //DISABLE_INTERRUPT_OS_SYS_TICK() // /*  MCUDisable() */

#define OS_SoftwareReset()     Mcu_PerformReset() /*  MCU_vSoftwareResetRequested(OSError) */

//#define MCU_InterruptCANRX_Enable()         C0RECMK  = 0  /*CIE = 0x0200*/
//#define MCU_InterruptCANRX_Disable()        C0RECMK =  1 
              /*CIE = 0x0002*/

//from 21 to 02
//#define ENABLE_INTERRUPT_OS_SYS_TICK()      Timer_Tick_Enable_Interrupt()
//#define DISABLE_INTERRUPT_OS_SYS_TICK()     Timer_Tick_Disable_Interrupt() 
/* Protection to MCAL Critical Sections */
#define SchM_Enter_Adc_Excl_Area0
#define SchM_Exit_Adc_Excl_Area0

#define SchM_Enter_Dio_ChGrp_Area
#define SchM_Exit_Dio_ChGrp_Area

#define SchM_Enter_Gpt_MK_Register
#define SchM_Exit_Gpt_MK_Register

#define SchM_Enter_Gpt_MK_Register_Int
#define SchM_Exit_Gpt_MK_Register_Int

#define SchM_Enter_Gpt_Notify_Mask
#define SchM_Exit_Gpt_Notify_Mask


/* Define for system debugging (message map auto coherency check, parameters check,...). Undefine for released systems */
/*#define OS_DEBUG */
/*#define OS_CPU_LOAD    */       /* Do not forget to DISABLE interrupt perfmeter */
/*#define OS_PERF_METER  */       /* Do not forget to ENABLE interrupt perfmeter */
/*#define OS_PERF_P1P2   */
/*#define CAN_DEBUG_FRAME */

/* Define it for system performance debugging. (OS_PERF_FULL_LOAD, OS_PERF_EMPTY_LOAD, OS_PERF_REFRESH must be adjusted ) */

/* capture timer value must be multiplied with the yimer step (1000 ns in this case) */

/* Messages used in OS */
typedef enum
{
   OS_Msg_IPC_Process,
   OS_MsgIDmax
} OS_MsgID;

#define OS_TIMER_USED
#ifdef OS_TIMER_USED
typedef enum
{
   /* Insert here the project specific OS timers */
   OS_Dummy_Timer,
   OS_MaxTimer
} OS_TimerID;
#endif

#define OS_TASK_USED
#ifdef OS_TASK_USED
//next reconfigured for workload performance,20110616

#define OS_Task_Wdg_Period         20
#define OS_Task_Wdg_Offset         8
#define OS_Task_PMode_Period       5   //updated, 20-->2, TBD with EE for power moding
#define OS_Task_PMode_Offset       1    //reuse FSR

#define OS_Task_KB_Period          50//reuse HSM, keyboard periodic is enough less than 30ms
#define OS_Task_KB_Offset          2     //reuse HSM

#define Os_Task_EEPROM_Period      5     //reuse MEMORY
#define Os_Task_EEPROM_Offset      1     //reuse MEMORY

#define OS_Task_CpuLoad_Period     200  //change cpu load task to a more period to give less effect on cpu load calculation
#define OS_Task_CpuLoad_Offset     8

#define Os_Task_Memory_Period      5     //added on 20110505, follow B78
#define Os_Task_Memory_Offset      1

#define Os_Task_AMP_Period     100    
#define Os_Task_AMP_Offset      80


/*#define OS_Task_CAN_Period    9    */
#define OS_Task_CAN_Period    12
#define OS_Task_CAN_Offset    3     //


#if defined OS_CPU_LOAD && defined OS_PERF_METER
#error "OS_CPU_LOAD & OS_PERF_METER can't be defined at same time !"
#endif
#if defined OS_PERF_METER || defined OS_CPU_LOAD
    #define OS_TIMER_STEP            666 /* = 1000*2/3, since 1 count of FreeRunCounter = 0.66Micro Sec */
    #define OS_PERF_FULL_LOAD       (((uint32_t)OS_Task_CpuLoad_Period*1000 * (uint32_t)1000) / (uint32_t)OS_TIMER_STEP)     /* This value, divided by 100 must be a power of 2 for optimisation */
    #define OS_PERF_EMPTY_LOAD      (((uint32_t)20 * (uint32_t)1000) / (uint32_t)OS_TIMER_STEP)     /* Time of main loop with no message to proceed (+50%) */
    #define OS_PERF_COUNTER_UNIT    2      /* uS elapsed by free run counter tick */
    #define OS_PERF_100PERCENT      (uint32_t)100
#endif
typedef enum
{
   /* Insert here the project specific tasks */
   OS_Task_Wdg,
   OS_Task_PMode,   
   OS_Task_Memory,
   OS_Task_KB,
   OS_Task_AMP,
   OS_Task_CAN,
#if defined OS_CPU_LOAD || defined OS_PERF_METER
   OS_Task_CpuLoad,                    /* Perfmeter 100ms */
#endif
   OS_MaxTask
} OS_TaskID;

#endif

/* Used this define to enable the OS event management */
/* #define OS_EVENT_USED*/
#ifdef OS_EVENT_USED
typedef enum
{
   /* Insert here the project specific OS events */
   OS_EventMax
} OS_EventID;
#endif

/* Used this define to enable the OS data pipe management */
/* #define OS_DATAPIPE_USED */
#ifdef OS_DATAPIPE_USED
typedef enum
{
#ifdef __DEBUG_LINK__
   OS_DebugOutPipe,
#endif
   /* Insert here the project specific OS data pipes */
   OS_DataPipeMax
} OS_DataPipeID;
#endif

/* Used this define to enable the OS message pipe management */
/* #define OS_MSGPIPE_USED */
#ifdef OS_MSGPIPE_USED
/* Defined here the number of maximum messages (this definition concerns all pipes) */
/* #define PIPE_MAX_MSG    4 */
typedef enum
{
   /* Insert here the project specific OS message pipes */

   OS_MsgPipeMax
} OS_MsgPipeID;
#endif

#define OS_EnableInterrupt(OS_Int)              OS_Int ## _Enable
#define OS_DisableInterrupt(OS_Int)             OS_Int ## _Disable

#define OS_InterruptCANRX_Enable                MCU_InterruptCANRX_Enable() 
#define OS_InterruptCANRX_Disable               MCU_InterruptCANRX_Disable()

#define FREE_RUNNING_TIMER_Enable      TMMK20 = 0
#define FREE_RUNNING_TIMER_Disable     TMMK20 = 1

extern void OS_EnableSysTick(void);
extern void OS_DisableSysTick(void);

/*============================================================================*\
*                          --- Public functions ---
\*============================================================================*/

#endif /* OS_Cfg_h*/
/******************************************************************************
 *
 * Date         By                        Change
 * -----------------------------------------------------------------------------
 * 25-Oct-11   LLP     update touch srceen tasks periodic and offset time 
 * 16-June-11   wade     update tasks periodic and offset time to meet ICS requirement
 * 28-Apr-10    SB       Task no.tci_ik#3382 for release 10024438_TCI/1.00.
                        Added post messages and tasks for DCM module.
 * 30-Apr-10    SB       Fix Task for task no.tci_ik#3382 for release 10024438_TCI/1.00.
                        Modifeid name of  DCM task as per SAD.
 * 06-May-10    KS       Removed Periodic task id for release 10024438_TCI/1.00.
                        -OS_Task_NVM_MainFunction
 * 07-May-10    IPM      Added OS_Msg_ASV_MainFunction.
 * 19-May-10    IPM      Added OS_Msg_COM_MainFunction.
 * 19-May-10    IPM      Added IoHwAb_WHL_Task
 * 20-May-10  IPM      Added RAT_MainFunction
 * 20-May-10    SB   Task no.tci_ik#3437 for release 10024438_TCI/1.00.
                     added timers and post messages for BLKL.
 * 20-May-10    KS       Added post message and Periodic task IDs for release 10024438_TCI/1.00.
     - OS_Task_DDP, OS_Msg_DDP_Process_RequestContextSave,
     - OS_Msg_DDP_Process_ConfirmFaultStatus, OS_Msg_DDP_Process_ReportRtEvent,
     - OS_Msg_DDP_CallBk_OnLifePhaseChange
 * 26-May-10    SB   Task no.tci_ik#3478 for release 10024438_TCI/1.00.
                     Added timers and post messages for DCM.
* 31-May-10  IPM      Task no.tci_ik#3530 for release 10024438_TCI/1.00.
*                   Append prefix 'App_' to all application interface names
* 25-Jun-10  IPM      Task no.tci_ik#3752 for release 10024438_TCI/2.00.
*                Added timers/messages to filter HVAC PUSH signals in App_COM_Filt module
* 28-Jun-10  KS      Task no.tci_ik#3700 for release 10024438_TCI/2.00.
*                   Changed OS_Msg_DDP_Process_ReportRTEvent to 
*                   OS_Msg_DDP_Process_RequestRTContextSave
* 29-Jun-10  SB      Task no.tci_ik#3754 for release 10024438_TCI/2.00.
*                   Added messages for function LED backligthing related functions.
* 09-Jul-10 HI      Task no.tci_ik#3802 Added the following OS Msg ID 
*                   1) OS_Msg_App_RAT_Control_Event 
*                   2) OS_MESSAGE_WHL_INCREMENT
*                   3)  OS_MESSAGE_WHL_DECREMENT
 
*09-Jul-10    KK    Task no.tci_ik#3793 for release 10024438_TCI/2.00.
                     Added HSM Tasks, Post messages and timers.
*15-Jul-10   HI     task no tci_ik#3803 Added OS_Task_RAT and removed OS_MESSAGE_FSR_PUSH_9_CHANGED

* 15-Jul-10  KK       Task no.tci_ik#3812 for release 10024438_TCI/2.00.
*                      Implementation of new OS message structure
* 19-Jul-10  KK       Task no.tci_ik#3829 for release 10024438_TCI/2.00.
*                      Function name changed as per SAD version 01.8
* 19-Jul-10  KS       Task no.tci_ik#3829 for release 10024438_TCI/2.00.
*                      Function name changed as per SAD version 01.9
* 19-Jul-10    KK    Task no.tci_ik#3834 for release 10024438_TCI/2.00.
*                    VOY_LUCH and AFF_LUCH interfaces added.
* 20-Jul-10    KK    Task no.tci_ik#3835 for release 10024438_TCI/2.00.
*                     New message added for COM loss management in App_HSM
* 26-Jul-10    KS   Task no.tci_ik#3869 for release 10024438_TCI/2.00.
                     updated as per review comments (Rev Id: 84466.5827)
* 26-Jul-10    IPM    Task no.tci_ik#3866 for release 10024438_TCI/2.00.
*                     Implement review comments:
*                     - OS_TIMER_STEP should be equal to 660, to manage the Cpu load tic at 0,66µs.
*                     - OS_InterruptCANRX_Enable/ OS_InterruptCANRX_Disable should not access directly to register (use MCU)
*                     - OS_GetFreeRunCounter should not access directly to register (use GPT)
*
* 29-Sep-10   HI     Task No tci_ik#4212 CAN_INTR_RX Enable/Disable code moved from Mcu_Irq.c(file deleted)
*                    FREE_RUNNING_TIMER_Enable/Disable Added.
* 30-Sep-10  KK    Task No. 4234 for release 10024438_TCI/3.00.
*                   Added message for ETAT_GMP signal

* 01-Oct-10   KS     Task No tci_ik#4117 for release 10024438_TCI/3.00.
*                    Removed OS_Msg_DDP_CallBk_OnLifePhaseChange.
* 01-Oct-10   RS     Task No tci_ik#4197 for release 10024438_TCI/3.00.
*                    Changes made as per review comment document 
*                    10024438_SW_RVW_00001215_00.14 Nr 48,52,55.
*                    Added/Renamed Messages.
* 04-Oct-10   KK     Task No tci_ik#4200 for release 10024438_TCI/3.00.
*                    Changes made as per review comment document 
*                    10024438_SW_RVW_00001215_00.14 Nr 48,52,55.
*                    Added/Renamed Messages.
* 04-Oct-10  KK    Task N0. 4267 for release 10024438_TCI/3.00.
*                   Implementation of MODE_HY and UB_MODE_HY functionality
*
* 29-Nov-10    KS   Task no.tci_ik#4422 for release 10024438_TCI/4.00.
*   App_BKL/App_DIAG:Modification as per SAD verification document
*
* 02-Dec-10    KS   Task no.tci_ik#4424 for release 10024438_TCI/4.00.
*   Removed OS_Msg_DDP_Process_ReportRtEvent
*
* 02-Dec-10   KS    Task no.tci_ik#4423 for release 10024438_TCI/4.00..
*   -Modification of the software component as per SAD verification report 
*   -ID SWIT-MTC-SAD-117-01
* 16-Dec-10  KS     Task no.tci_ik#4457 for release 10024438_TCI/4.00.
*   - Added event OS_MESSAGE_RESTORE_DEFAULT.
* 17-Dec-10  JJ    enabled the setting of reset cause byte
* 17-Dec-10    KS   Task no.tci_ik#4589 for release 10024438_TCI/4.00.
*   Added OS_App_DIAG_IOCBI_BklConnective_Timer and OS_Msg_App_DIAG_IOCBI_BklConnective_Timeout
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
* 13 -01-11   HI Task No 4756 PR 393 Fix
********************************************************************************/

