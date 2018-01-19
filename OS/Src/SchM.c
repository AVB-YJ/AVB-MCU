/*==========================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     SchM.c
 * Created By:      JJ
 * Created Date:    13th December 10
 * %version:        1 %
 * %cvtype:         csrc %
 * %instance:       ctc_aud_2 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *   
 * This module schedules the IDLE tasks and launch the reconfiguration and 
 * self-test requested by robustness
 *
 * Traces to: 10024438_SW_SDD_00002054
 *
 *
 * Applicable Standards (in order of precedence: highest first):
 *  coding standards followed where ever necessary.
 * For Datatypes followed Autosar standard    
 *
 * 
 *
 \*============================================================================*/

/*============================================================================*\
 *
 * Preprocessor #include directive(s)
 *
\*============================================================================*/
#include "EcuM.h"
#include "OS_Task.h"
#include "OS_FifoSys.h"
#include "OS_Timer.h"
#include "StackCk.h"
#include "port.h"
#include "SchM.h"
#include "TIMER.h"

/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/
#define IDLE_TASK_STEP_0   (uint8_t)0
#define IDLE_TASK_STEP_1   (uint8_t)1
#define IDLE_TASK_STEP_2   (uint8_t)2
#define IDLE_TASK_STEP_3   (uint8_t)3
#define IDLE_TASK_STEP_4   (uint8_t)4
#define IDLE_TASK_STEP_5   (uint8_t)5
#define IDLE_TASK_STEP_6   (uint8_t)6
#define IDLE_TASK_STEP_7   (uint8_t)7
#define IDLE_TASK_STEP_8   (uint8_t)8
#define IDLE_TASK_STEP_9   (uint8_t)9

/* the error reduction factor is used to reduce the error in the count. if the
 * first time count is greater than the ref time 0x8000 the factor is enabled, 
 * this will prohibit the counting of first ref_time crossing. thus making
 * the error of ref_time approximation to approximately +/-22ms 
 */
#define ERROR_REDUCTION_FACTOR (uint8_t)1
#define ERROR_REDUCTION_NR     (uint8_t)0

/*============================================================================*\
 *
 *  Constant Declarations
 *
\*============================================================================*/
/*============================================================================*\
 *
 * Local type declarations (enum, struct, union, typedef), mixed case
 *
\*============================================================================*/

typedef struct
{
   uint8_t count;
   uint8_t error_reduction;
   const uint8_t timeout[SCHM_TIMEOUT_MAX];
   uint16_t reference_time;
   uint16_t previous_time;
   uint16_t current_time;
}SchM_Timeout_T;

static SchM_Timeout_T SchM_Timeout = SCHM_TIME_OUT_INIT;

/*============================================================================*\
 *
 * Exported object definitions, mixed case
 *
\*============================================================================*/


/*============================================================================*\
 *
 * Local object definitions, lower case
 *
\*============================================================================*/

/*============================================================================*\
 *
 * Local function prototypes, mixed case
 *
\*============================================================================*/

/*============================================================================*\
 *
 * Local inline function definitions and #define function-like macros,
 * mixed case
 *
\*============================================================================*/

#ifdef PROJ_UNUSED_CODE
static uint8_t SchM_Interrupt_State; 
#endif

/*.===================================================================*\
*. FUNCTION: Os_Idle_Task_Robustness
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None 
*. 
*. External references:
*.  External variables: 
*   None
*.  File scope variables:
*.   
*.
*. Description:
*.  This function schedules the IDLE tasks and launch the reconfiguration and 
 * self-test requested by robustness

This function calls the different robustness tasks needs to be executed in
*.  the OS IDLE task. This function called in the OS IDLE task.
*.
*.  Postcondition: None
\*===================================================================*/
void Os_Idle_Task_Robustness(void)
{

  static uint8_t idle_task_step = 0;
  if (IDLE_TASK_STEP_0 == idle_task_step)
  {
     idle_task_step++;
     #ifdef ROBST_OS_FIFO_ENABLE
     OS_FifoSys_Check();
     #endif   /* ROBST_OS_FIFO_ENABLE */
  }
  else if (IDLE_TASK_STEP_1 == idle_task_step)
  {
     idle_task_step++;
     #ifdef OS_TASK_USED
     OS_TaskCheck();
     #endif
  }
  else if (IDLE_TASK_STEP_2 == idle_task_step)
  {
     idle_task_step++;
     #ifdef OS_TIMER_USED
     OS_TimerCheck();
     #endif
  }
  else if (IDLE_TASK_STEP_3 == idle_task_step)
  {
/* calls the stack check function and if the user limit crosses the
 * threshold it resets the cpu
 */
     idle_task_step++;
     #ifdef ROBST_STACK_CK_ENABLE
     StackCk_Handler();
     #endif   /* ROBST_STACK_CK_ENABLE */
  }
  else if (IDLE_TASK_STEP_4 == idle_task_step)
  {
/* calls the CAN check function and if any discrepancy is found it stops 
 * CAN stack and restart the CAN stack 
 */
     idle_task_step++;
     #ifdef ROBST_CAN_CK_ENABLE
     
     //CAN_NM_SelfCheck();
     
     #endif   /* ROBST_CAN_CK_ENABLE */
  }
  else
  {
     /* calls the port refresh task, which assigns the port directions */
     idle_task_step = 0;
  }

}

#ifdef PROJ_UNUSED_CODE
/******************************************************************************
* Function  : SchM_EnterCriticalSection
*.=============================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None 
*. 
*. External references:None
*.  External variables: 
*   None
*.  
*. File scope variables:
*. Description:Save the current interrupt state and disable the interrupt
*
******************************************************************************/

void SchM_EnterCriticalSection(void)
{

  SchM_Interrupt_State = __get_interrupt_state();
  __disable_interrupt();
}
/******************************************************************************
* Function  : SchM_ExitCriticalSection
*.=============================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None 
*. 
*. External references:None
*.  External variables: 
*   None
*.  
*. File scope variables: None
*  Description: Restore the previous state of the Interrupt to the value prev
*   to entering Critical section
******************************************************************************/
void SchM_ExitCriticalSection(void)
{
  __set_interrupt_state(SchM_Interrupt_State);
}
#endif   /* PROJ_UNUSED_CODE */



/******************************************************************************

******************************************************************************
* Function  : SchM_Timeout_Get_Ref_Time
*.=============================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None 
*. 
*. External references:None
*.  External variables: 
*   None
*.  
*. File scope variables: SchM_Timeout
*  Description: This function initialises the reference timer for timeout
******************************************************************************/
void SchM_Timeout_Get_Ref_Time(void)
{
  uint16_t cur_time;
  /* get the reference time and initialize the count for new timeout 
  SchM_Timeout.reference_time = OS_GetFreeRunCounter();    */
  cur_time = OS_GetFreeRunCounter();
  SchM_Timeout.reference_time = SCHM_LOOP_CONST_REF_TIME;
  if(cur_time > SchM_Timeout.reference_time)
  {
     SchM_Timeout.error_reduction = ERROR_REDUCTION_FACTOR;
  }
  else
  {
     SchM_Timeout.error_reduction = ERROR_REDUCTION_NR;
  }
  SchM_Timeout.previous_time = 0;
  SchM_Timeout.count = 0;
 
}

/******************************************************************************
* Function  : SchM_Loop_Timeout
*.=============================================================================
*. Return Value:
*.  Std_ReturnType - E_OK/E_NOT_OK
*.
*. Parameters:
*.  SchM_Loop_Timeout_T index 
*. 
*. External references:None
*.  External variables: 
*   None
*.  
*. File scope variables: SchM_Timeout
*  Description: This function returns the loop timeout status
******************************************************************************/
Std_ReturnType SchM_Loop_Timeout(SchM_Loop_Timeout_T index)
{
  bool_t timeout_status = E_OK;
  /* get the current TCR value */
  SchM_Timeout.current_time =  OS_GetFreeRunCounter();

  if (SchM_Timeout.previous_time != 0)
  {
     /* check whether the timer overflow occured or not */
     if ((SchM_Timeout.current_time < SchM_Timeout.reference_time) && (SchM_Timeout.previous_time >= SchM_Timeout.reference_time))
     {
         if(ERROR_REDUCTION_FACTOR == SchM_Timeout.error_reduction)
         {
             SchM_Timeout.error_reduction = ERROR_REDUCTION_NR;
         }
         else
         {
           SchM_Timeout.count++;
           if(index < SCHM_TIMEOUT_MAX )
           {
           /* if the timer overflow count equals timeout count send E_NOT_OK */
             if(SchM_Timeout.count >= SchM_Timeout.timeout[index])
             {
                timeout_status = E_NOT_OK;
             }
           }
         }
     }
  }
  SchM_Timeout.previous_time = SchM_Timeout.current_time;
  return timeout_status;
}
 /*
 * Revision history
 *
 * Date             By                        Change
 * ----------------------------------------------------------------------------
 * 02-May_2011      Wade      initial changed for ICS
 *
 * 14 Dec 2010      JJ        Task No.tci_ik#4553 for release 10024438_TCI/4.00
 *                            Added the SAD req -03.3-0100
 * 20 Dec 2010     JJ        Review comment fixes 
 * 30-Dec-2010    JJ        Task no.tci_ik#4666 for release 10024438_TCI/4.00.
 *                        - Implemented Robustness SRD 00.1-0028
 * 11-Feb-11      GC       Task no.tci_ik#4921 for release 10024438_TCI/5.00.
 *                       - corrections in File Header and function header
 * 25-Feb-11     KK   Task no.tci_ik#4984 for release 10024438_TCI/5.00.
 *                        - SAD verification comments implementation
 * 25-Mar-11    JJ   Task no.tci_ik#5117 for release 10024438_TCI/5.00.
 *                     - Added Lvd_SelfRecovery to idle task
 * 06-Apr-11    JJ   Task no.tci_ik#5067 for release 10024438_TCI/5.00.
 *                     - Added PWM and ADC selfrecovery functions
 * 07-Apr-11    JJ    Task no.tci_ik#5154 for release 10024438_TCI/5.00.
 *                     -  Added the Loop Timeout, SAD req 04.7-0322 
 * 08-Apr-11    JJ     Implemented Review comments ID 103572.3469
 * 11-Apr-11    JJ     Implemented Review comments ID 103572.3469 and QAC
 *                     warning removal.
 * 18-Apr-11    JJ     Implemented TI tci_ik#429 
 * ***************************************************************************/

