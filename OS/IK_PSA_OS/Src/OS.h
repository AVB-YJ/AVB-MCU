/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS  ( OS )
 *  File          : OS.h
 *-----------------------------------------------------------------------------
 *  Description   : OS 
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*-------------------------------------------------------------------
 * to avoid multiple definition if the file is included several times
 *-------------------------------------------------------------------*/
#ifndef OS_H
#define OS_H

#include "Systype.h"
#include "OS_Cfg.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/

#define OS_NULL_PTR  (0x00U)

typedef enum
{
    OS_NoError,
    OS_IdOutOfRange,
    OS_TimerInUse,
    OS_PipeEmpty,
    OS_PipeNotEmpty,
    OS_PipeFull,
    OS_BufferTooSmall,
    OS_InvalidParameter
} OS_Error;


/* Define structure of message exchanged by OS */
typedef struct
{
    OS_MsgIdType     MsgId;

    OS_MsgParamType1 Param1;
    OS_MsgParamType2 Param2;
} OS_Msg;


/* Function pointer of a message handler */
typedef void (*pMsgHandler)(OS_MsgParamType1, OS_MsgParamType2);
typedef void (*pMsgHandler0)(void);
typedef void (*pMsgHandler1)(OS_MsgParamType1);

typedef struct
{
#ifdef OS_DEBUG
    OS_MsgIdType  MsgId;
#endif
    uint8_t       ParamNb;
    pMsgHandler0  pFct;
} OS_MsgHandlerType;

#ifdef OS_IDLE_HOOK
/* Function pointer of a Idle Hook */
typedef void (*pIdleHook)(void);
#endif

#ifdef OS_TIMER_USED
typedef struct
{
    OS_BoolType     Activ;
    OS_TimeType     Expiration;
    OS_TimeType     Reload;
    OS_MsgIdType    PostMsg;
} OS_TimerType;
#endif


#ifdef OS_TASK_USED
typedef void (* const pTaskHandler)(void);
typedef struct
{
    OS_TimeType     Expiration;
    OS_TimeType     Reload;
    OS_IndexType    Schedule;
    pTaskHandler    pTaskFct;
} OS_TaskType;
#endif

typedef struct
{
    volatile OS_TimeType    Tick;                    /* OS tick, incremented by hardware interrupt */
#ifdef OS_TASK_USED
    volatile OS_IndexType   TasksToSchedule;        /* Number of tasks ready for scheduling */
#endif

#ifdef OS_TIMER_USED
#ifndef OS_1TICK_TIMER_OPTIMISED
    OS_TimeType    TimerNextEvent;            /* Time remaining untill next timer event, decremented by hardware interrupt */
#endif
    OS_IndexType   TimerActivity;
    OS_TimerType   Timer[OS_MaxTimer];
#endif
} OS_ControlType;

#if defined OS_CPU_LOAD || defined OS_PERF_METER
/*
**  MODIFYING THIS STRUCTURE      **
**  OR THESE ENUMS                **
**  IMPLIES MODIFY ASM PERFMETER  **
**  INTERRUPT CODE                **
*/
typedef enum
{
    OS_Idle,    /* 0 */
    OS_System,  /* 1 */
    OS_User     /* 2 */
} OS_Level;

typedef struct
{
    OS_Level   CurrentLevel;          /* +0 */

    int16_t    InterruptLevel;        /* +2 */

    OS_TimeType FreeRunCounter;       /* +4 */

    uint32_t   SystemLoad;         /* +6 */
    uint16_t   UserLoad;           /* +8 */ 
    uint16_t   InterruptLoad;      /* +10 */

    uint16_t   MaxTaskTime;

    OS_IndexType OS_LastIdle;

    /*OS_TimeType P1itLoad;
    OS_TimeType P1Enter;
    OS_TimeType P1Load;

    OS_TimeType P2itLoad;
    OS_TimeType P2Enter;
    OS_TimeType P2Load; */
    OS_TimeType TaskLoad[OS_MaxTask];

} OS_PerfCtrl;
#endif

#define OS_PostMessage(msg) OS_FifoSys_PushBack(msg)
#define OS_PostMessage0(msg) OS_FifoSys_PushBack0(msg)
#define OS_PostMessage1(msg) OS_FifoSys_PushBack1(msg)
#define OS_PostPriorityMessage(msg) OS_FifoSys_PushFront(msg)

#define OS_Time()  OS_GetSysTick()
/* System & user fifos 'users operations'. Other fifo ops are called by OS only */
void OS_FifoSys_PushBack( const OS_Msg* elt );
void OS_FifoSys_PushBack0( OS_MsgIdType MsgId );
void OS_FifoSys_PushBack1( const OS_Msg* elt );
void OS_FifoSys_PushFront( const OS_Msg* elt );

#if defined OS_CPU_LOAD || defined OS_PERF_METER
#if 0
void OS_PerfEnterP1(void);
OS_TimeType OS_PerfExitP1(void);
void OS_PerfEnterP2(void);
OS_TimeType OS_PerfExitP2(void);
uint8_t OS_GetMaxCPULoad(void);
uint8_t OS_GetCPULoad(void);
void OS_ResetMaxCPULoad(void);
#endif
void OS_SaveTaskThroughput(OS_TaskID index, uint16_t through);
#endif
void OS_SysTick(void);

/*----------------------------------------------------------------------------*
 *                         --- Global Variables ---                           *
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

void OS_Init(void);

#ifndef POLYSPACE
void OS_Run(void);
#endif

//#if defined OS_PERF_METER || defined OS_CPU_LOAD
 void OS_Wait(uint8 OS_time); 
//#endif

#if defined OS_CPU_LOAD || defined OS_PERF_METER
  void OS_PerfMeter(void);
#endif

void OS_SysTick(void);

void OS_AppHalt(void);
uint8_t OS_GetAveThroughput(void);

#define OS_GetSysTick() OS_Control.Tick

#define NO_PARAM    (uint8_t)0x00U
#define ONE_PARAM   (uint8_t)0x01U
#define TWO_PARAM   (uint8_t)0x02U



/* MsgHandler (message handler table) will be declared in OS_Cfg.c */
extern const OS_MsgHandlerType MsgHandler[OS_MsgIDmax];
/* Timers need to know about OS_Control struct because of system tick */
extern OS_ControlType OS_Control;

/* Message map related defines */
#define BEGIN_MESSAGE_MAP const OS_MsgHandlerType MsgHandler[OS_MsgIDmax] = {
#ifdef OS_DEBUG
    #define    ON_MESSAGE(msg, param, fct) { msg, param, (void *)&fct() },
#else
    #define    ON_MESSAGE(msg, param, fct) { param, (pMsgHandler0)fct },
#endif
#define END_MESSAGE_MAP };

#ifdef OS_TASK_USED
/* Tasks related defines */
#define BEGIN_TASKS OS_TaskType OS_TaskArray[OS_MaxTask] = {
#define DECLARE_TASK(name, time)    {time,time,0,name},
#define END_TASKS };
extern OS_TaskType OS_TaskArray[OS_MaxTask];
#endif

#ifdef OS_IDLE_HOOK
/* SelfCheck related defines */
#define BEGIN_IDLE_HOOK const pIdleHook IdleHookHandler[] = {
#define ON_IDLE_HOOK(fct) fct,
#define END_IDLE_HOOK OS_NULL_PTR };
extern const pIdleHook IdleHookHandler[];
#endif

#ifdef OS_EVENT_USED
/* Events related defines */
#define BEGIN_EVENTS OS_EventType OS_EventArray[OS_EventMax] = {
#define DECLARE_EVENT(name)    0,
#define END_EVENTS };
extern OS_EventType OS_EventArray[OS_EventMax];
#endif

#ifdef OS_DATAPIPE_USED
/* Pipe related defines */
#define OS_DECLARE_DATAPIPE_BUFFER(name, size) unsigned char OS_DataPipeBuffer##name[size];
#define OS_BEGIN_DATAPIPES OS_DataPipeCtrl OS_DataPipeControl[OS_DataPipeMax] = {
#define OS_DECLARE_DATAPIPE(name) { OS_DataPipeBuffer##name, OS_DataPipeBuffer##name+sizeof(OS_DataPipeBuffer##name)-1, sizeof(OS_DataPipeBuffer##name), sizeof(OS_DataPipeBuffer##name), OS_DataPipeBuffer##name, OS_DataPipeBuffer##name },
#define OS_END_DATAPIPES };
#endif

#ifdef OS_MSGPIPE_USED
#define OS_DECLARE_MSGPIPE_BUFFER(name, size) unsigned char OS_MsgPipeBuffer##name[size];
#define OS_BEGIN_MSGPIPES OS_MsgPipeCtrl OS_MsgPipeControl[OS_MsgPipeMax] = {
#define OS_DECLARE_MSGPIPE(name) { OS_MsgPipeBuffer##name, OS_MsgPipeBuffer##name+sizeof(OS_MsgPipeBuffer##name)-1, sizeof(OS_MsgPipeBuffer##name), {0}, 0, 0, 0, sizeof(OS_MsgPipeBuffer##name), OS_MsgPipeBuffer##name, OS_MsgPipeBuffer##name },
#define OS_END_MSGPIPES };
#endif

#endif /* OS_h*/
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

