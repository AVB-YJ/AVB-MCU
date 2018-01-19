/*==========================================================================*\
 * Copyright 2007,  Technologies, Inc., All Rights Reserved.
 *  Confidential.
 *--------------------------------------------------------------------
 * Module Name:     StackCk.c
 * Created By:      SIL
 * Created Date:    16th April 10
 * %version:        1 %
 * %cvtype:         csrc %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *   
 * This module checks the stack and generate the software reset if the 
 * stack overflow the threshhold limit
 *
 * Traces to: none
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
#include "StackCk.h"
#include "OS.h"
#include "Mcu.h"
#include "EcuM.h"


/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/


#define FIRST_PATTERN_INDEX        (-1)
#define SECOND_PATTERN_INDEX       (-2)
#define THIRD_PATTERN_INDEX        (-3)
#define FOURTH_PATTERN_INDEX       (-4)
#define HUNDRED_PERCENT            ((uint8_t)0x64U)
#define MUL_8                       3


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
#ifdef PROJ_DEBUG_MODE
    typedef struct
    {
       uint16_t curr_counter;
       uint16_t prev_counter;
       uint16_t diff_time;
       uint16_t max_time;
    } StackCkHandler_time_T;
    StackCkHandler_time_T StackCkHandler_time;
#endif

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
/* Stack grows from Higher address to Lower address */
static uint8_t *__near nUpStackAddress;          /* Hold the end point of Stack address: Lower address */
static uint8_t *__near nBottomStackAddress;      /* Hold the starting point of Stack address: Higher address*/
static int16_t nMaxStackSize;                   /* Holds the maximum stack value */

static uint8_t *__near CPU_pUserStack;
static uint8_t *__near CPU_pStackEndAddress;
static uint8_t *__near CPU_pUserLimit;
static uint16_t CPU_UserStackSize;  /* Changed to 16 bit type as the size size is fixed to 512 bytes*/
static uint8_t *pStackPointer;

/*.===================================================================*\
*. FUNCTION: StackCk_Init
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
*.  This function initialises the stack check functionality.
*.  Precondition: The copy of data and bss variables from ROM to RAM to be 
*.                completed
*.  Postcondition: None
\*===================================================================*/
void StackCk_Init(void)
{
#ifdef POLYSPACE
   static int16_t aStackArray[STACK_ARRAY_SIZE];
   int16_t i16Id;

   /* Initialize the Stack pointer with the array's end address*/
   CPU_pUserStack = (uint8_t*)&aStackArray[STACK_ARRAY_SIZE - 1];

   for (i16Id = 0; i16Id < STACK_ARRAY_SIZE; i16Id++)
   {
      aStackArray[i16Id] = STACK_PATTERN;
   }
#else /*Polyspace*/
   
   {
      #ifndef QAC
     /* Get stack pointer current position*/
      asm("PUSH AX");
      asm("MOVW AX, SP");
      asm("MOVW pStackPointer, AX");
      
     /* Initialise Stack Variables*/

      asm("MOVW AX,#sfb(CSTACK)"); 
      asm("MOVW nUpStackAddress,AX");           /* Lower address of stack */
      asm("MOVW AX,#sfe(CSTACK)"); 
      asm("MOVW nBottomStackAddress,AX");       /* Higher address of stack*/
      asm("MOVW AX,#sizeof(CSTACK)"); 
      asm("MOVW nMaxStackSize,AX");             /* Max stack size */
      asm("POP AX");
      #endif
   }

   /* fill the stack with pattern from current stack pointer address to up stack address*/
   for (CPU_pUserStack = pStackPointer; CPU_pUserStack >= nUpStackAddress; CPU_pUserStack--)
   {
      *CPU_pUserStack = STACK_PATTERN;
   }

   /* Compute Stack limit as 87.5% = 100% - 1/8.StackSize */
   CPU_pUserLimit = (nBottomStackAddress - nMaxStackSize) + (nMaxStackSize >> MUL_8);

   /* begin with user stack equal to stack end address */
   CPU_pUserStack         = nBottomStackAddress;
   CPU_pStackEndAddress = nBottomStackAddress;
#endif /*Polyspace*/
}

/*.===================================================================*\
*. FUNCTION: StackCk_Handler
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
*.  CPU_pUserStack 
*.  CPU_pStackEndAddress
*.
*. Description:
*.  This function is the main function handler for executing the stack check
*.  functionality. This Handler need to be called in using OS cyclic scheduler.
*.  Precondition: StackCk_Init() to be called initially.
*.  Postcondition: None
\*===================================================================*/
void StackCk_Handler(void)
{

#ifdef PROJ_DEBUG_MODE
      StackCkHandler_time.prev_counter = OS_GetFreeRunCounter();
#endif
      /* Checking the stack pattern */
   while ( (STACK_PATTERN != CPU_pUserStack[FOURTH_PATTERN_INDEX])
           || (STACK_PATTERN != CPU_pUserStack[THIRD_PATTERN_INDEX])
           || (STACK_PATTERN != CPU_pUserStack[SECOND_PATTERN_INDEX])
           || (STACK_PATTERN != CPU_pUserStack[FIRST_PATTERN_INDEX]) )
   {
      --CPU_pUserStack;
      /* Check the stack threshold limit */
      if ( CPU_pUserStack < CPU_pUserLimit )
      {
         EcuM_SetNoInitByte(STACK_OVERFLOW_RESET); /* Update the reset cause status */ 
         OS_SoftwareReset();    /* Issue software reset */
      }
      CPU_UserStackSize = (uint16_t)(CPU_pStackEndAddress - CPU_pUserStack); /* The size of stack used*/
   }

#ifdef PROJ_DEBUG_MODE
   StackCkHandler_time.curr_counter = OS_GetFreeRunCounter();
   StackCkHandler_time.diff_time = StackCkHandler_time.prev_counter - StackCkHandler_time.curr_counter;
   if (StackCkHandler_time.diff_time > StackCkHandler_time.max_time)
   {
      StackCkHandler_time.max_time = StackCkHandler_time.diff_time;
   }
#endif

}

/*.===================================================================*\
*. FUNCTION: StackCk_GetUserStackSize
*.=====================================================================
*. Return Value:
*.  uint8_t
*.
*. Parameters:
*.  None 
*. 
*. External references:
*.  External variables: 
*   None
*.  File scope variables:
*.
*. Description:
*. This function returns the Max stack usage percentage
*.
*.  Precondition: StackCk_Init() to be called initially.  
*.  StackCk_Handler() periodic function to be started.
*.  Postcondition: None
\*===================================================================*/
uint8_t StackCk_GetUserStackSize(void)
{
uint8_t PercentOfStackUsed;
#if defined (QAC) || defined (POLYSPACE)
    /* To avoid a 0 division, during static analysis , UsedStack is always set to a fixed value */
    PercentOfStackUsed = (uint8_t)((uint16_t)nMaxStackSize+CPU_UserStackSize);
#else
    /* MCU_CPU_i16stackSize can NOT be 0, it stands for the Stack max size. It is set by the project option and can not be 0.*/
    PercentOfStackUsed = (uint8_t)(((uint16_t)CPU_UserStackSize * HUNDRED_PERCENT) / (uint16_t)nMaxStackSize);
#endif /* QAC || POLYSPACE */


return PercentOfStackUsed;
}

/*.===================================================================*\
*. FUNCTION: StackCk_ReinitUserStackMeasure
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
*. Description:
*. This function clears the stack usage values.
*.
*.  Precondition: StackCk_Init() to be called initially.  
*.  StackCk_Handler() periodic function to be started.
*.  Postcondition: None
\*===================================================================*/
void StackCk_ReinitUserStackMeasure(void)
{
  /*The current stack address is again initialised to stack start: Higher address */
  CPU_pUserStack = nBottomStackAddress;    
  CPU_UserStackSize = 0;     /* Used stack is zero now */
}
/*******************************************************************************************
 *
 * Revision history
 *
 * Date                By                        Change
 * -----------------------------------------------------------------------------------------
 * 02-May_11           Wade               initial reused for ICS 
 * 16th Apr 2010       SIL              Initial version of stack check function for ICPB78 
 *                                      Program  for release 10024438_TCI/1.00
 * 07th May 2010       SIL              Added 2 new interfaces StackCk_ReinitUserStackMeasure &
 *                                      StackCk_GetUserStackSize needed for DCM module for 10024438_TCI/1.00
 * 08th Dec 2010       JJ               Task No.tci_ik#4459 for release 10024438_TCI/4.00
 *                                      Added the robustness req -00.1-0021
 * 08-Feb-11           JJ               Task No.tci_ik#4859 for release 10024438_TCI/5.00
 *                                      Removed QAC warning
 * 22-Mar-11           SIL              Task No.tci_ik#5073 for release 10024438_TCI/5.00
 *                                      Moved configurable parameters to Cfg file
 * *********************************************************************************************/
        
