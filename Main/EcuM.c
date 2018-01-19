/*===================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     EcuM.c
 * Created By:      SIL
 * Created Date:    21st April 2010
 * %version:         4 %
 * %cvtype:         csrc %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_created:   Mon Oct 29 14:27:14 2012 %
 *--------------------------------------------------------------------
 *
 * Description:
 *  This module does the initialisation of the modules in all layers. It has 
 *  the main function which will be called from the startup code. This module
 *  does the reset cause management at power-up. 
 *
 * Traces to: 10024438_SW_SDD_00001365
 *
 *
 * Applicable Standards (in order of precedence: highest first):
 *     SW REF 264.15D "DE Systems C Coding Standards" dated 12-Mar-2006
 *
 * Deviations from Delco C Coding standards:
 *   1. C46 - Abbreviations are not documented in this source file.
 *
 *   2. C54 - Function header block is placed at the beginning of
 *      function definition instead before function proto type
 *      declaration.
 *
 *   3. C58 - Function header blocks only list global variables that
 *      are not accessed by macros or functions.
 *
 *   4. C60 - The function is pre-emptible or re-entrant is not
 *      applicable to this program.
 *   <Write any other deviations from Delco C Coding  Standards >
\*===================================================================*/


/*============================================================================*\
 *
 * Preprocessor #include directive(s)
 *
\*============================================================================*/

#include "Mcu.h"
#include "Port.h"
#include "OS_Task.h"
#include "EcuM.h"
#include "StackCk.h"
#include "WdgM.h"
#include "RomCk.h"
#include "TIMER.h"
#include "Adc.h"
#include "Irq.h"
#include "OS_Task.h"
#include "App_PowerMode.h"
#include "OS_timer.h"
#include "NVM.h"
#include "Key_scan.h"
#include "App_AMP.h"
#include "UART.h"
#include "CCA.h"
#include "Hardware_IIC.h"
#include "Peripheral_PowerON.h"
#include "TDA75610.h"


/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/
//#define RST_CAUSE_BIT          (uint8_t)0x40U
//#define CRC_CONSISTENCY_BIT    (uint8_t)0x80U
//#define RST_CAUSE_CLEAR_BIT    (uint8_t)0xBFU
//#define START_SWC_TIMEOUT          30       /* Swc start timeout */
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

/*============================================================================*\
 *
 * Exported object definitions, mixed case
 *
\*============================================================================*/

#if defined QAC || defined POLYSPACE
uint8_t EcuM_ResetCauseStatus;
#else
//#pragma dataseg=RESET_CAUSE_VAR
__no_init uint8_t EcuM_ResetCauseStatus;
//#pragma dataseg=default
#endif

uint8_t EcuM_CurrentMcuResetCause;
bool Local_Wakeup_Flag;

/* this variable gives the Current MCU reset causes such as 
 * - Power on Reset
 * - External Pin Reset
 * - Watchdog Reset
 * - Illegal opcode or illegal address
 */

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
static void EcuM_Init(void);
static void EcuM_Start(void);
static void EcuM_Run(void);
static void EcuM_Driver_Init(void);
static void EcuM_Service_Init(void);


/*============================================================================*\
 *
 * Local inline function definitions and #define function-like macros,
 * mixed case
 *
\*============================================================================*/


/*.===================================================================*\
*. FUNCTION: main
*.=====================================================================
*. Return Value:
*.  0
*.
*. Parameters:
*.  None
*.
*. External references: EcuM_Init(),EcuM_Start(),EcuM_Run()
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This main function of the project is getting called
*. from the start-up code after the initialising of all the logical
*  Data segments and bss segments
*.
\*===================================================================*/
int main( void )
{ 
   /* Initialize ECU */
   EcuM_Init();

   /* Start tasks and tick timer*/
   EcuM_Start();

   /* Execute ECU back ground tasks */
   EcuM_Run();
   
   /* Return from main */
   return(0);
}


/*.===================================================================*\
*. FUNCTION: EcuM_Init
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references: All the init functions of the project
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description:  This module initialises the driver layer, System, 
*. Communication and memory Services layer,OS and Application
*. 
*.
\*=======================================================================*/
static void EcuM_Init(void)
{
	EcuM_Driver_Init();
	
	//EcuM_IoHwAb_Init();/*nothint to do*/
	
	EcuM_Service_Init();
	
	//CAN_Handler_Cold_Init(0);
	
	//TDA_75610_Off();
	//TDA75610_Open();
	
	//EcuM_Appl_Init(); /*nothing to do*/
	
	/* Enable all the interrupts */
	//OS_EnableAllInterrupts();
}

/*.===================================================================*\
*. FUNCTION: Driver_Init
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references: All the init functions of the project
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description:  This module initialises the driver layer 
*.
\*=======================================================================*/
static void EcuM_Driver_Init(void)
{
	External_SystemClock_Init();
	Port_Init(NULL_PTR);
	Timer_Array_Initialize();
	
	//CAN Init
	Configure_CAN_Transcvr_Normal();/*Enable CAN transcvr*/
	CAN_Handler_Cold_Init(0);
	
	//IIC Init
	IIC11_Init();
	
	//Power On All Peripheral
	All_Power_Init();
	
	//UART2 Init
	UART2_Init();
}

/*.===================================================================*\
*. FUNCTION: IoHwAb_Init
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references: All the init functions of the project
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description:  This module initialises the driver layer 
*.
\*=======================================================================*/

/*.===================================================================*\
*. FUNCTION: Service_Init
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references: All the init functions of the project
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description:  This module initialises the Service layer 
*.
\*=======================================================================*/



static void EcuM_Service_Init(void)
{
    /* Initialise CAN */
   CCA_Init();
    
   /* Initialise OS */
   OS_Init();
   
   //WdgM_Refresh();  /* This service of WDT is added to satisfy EEL */
   /* Enable all the interrupts */
   OS_EnableAllInterrupts();

   /* Initialise Stack Check */
   StackCk_Init();
   /* Initialise Rom Check */
}

/*.===================================================================*\
*. FUNCTION: Appl_Init
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references: All the init functions of the project
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description:  This module initialises the Application layer 
*.
\*=======================================================================*/


/*.===================================================================*\
*. FUNCTION: EcuM_Start
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references:
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This module start the S/W Components
*.
\*===================================================================*/
static void EcuM_Start(void)
{   
	/* Start Watch dog Manager, reflash watchdog */
	//WdgM_Start();
	
	//NVM_Start(); 
	/*Start OS Timer*/
	RCP_Tick_Start();
	//wade added power started
	App_PowerMode_Start();
	
	App_AMP_Control_Start();
	
	CCA_Task_Start();
	
	IoHwAb_KB_Start();
	//Uart_Start(0);
	//Uart_Start(1);
	//Uart_Start(2);
	UART2_Start();
}

/*.===================================================================*\
*. FUNCTION: IoHwAb_Start
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references:
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This module start the IoHwAb S/W Components
*.
\*===================================================================*/


/*static void EcuM_IoHwAb_Start(void)
{
   // Start WHL component 
   //IoHwAb_WHL_Start();
   //IoHwAb_KB_Start();
   
}*/

/*.===================================================================*\
*. FUNCTION: EcuM_Run
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  None
*.
*. External references:
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description: This public function starts the Scheduling of OS
*.
\*===================================================================*/
static void EcuM_Run(void)
{
   while(1)  /* Execute the back ground loop */
   {
	//IIC11_MasterReceiveStart(0x08, iic_data, 2);

      OS_Run();
      //run the background maintain process for eeprom
      //EEL_Handler(NVM_EEL_POLLING);
   }
}

/*.===================================================================*\
*. FUNCTION: EcuM_GetDifBaseTimerStepValue
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*.  Timer Channel No., Pointer to Current count. 
*.
*. External references: Gpt_GetTimeRemaining
*.  External variables:
*.   None
*.  File scope variables:
*.   None
*.
*. Description:  This function returns the difference of the last time 
*. and Present time. Also the current time is copied to the second parameter.
*. The function taken in to consideration the timer is configured as down
*. counter.
\*===================================================================*/
uint16_t EcuM_GetDifBaseTimerStepValue(uint16_t *pDifvar)
{
   uint16_t Result;

   Result = ((*pDifvar) > RCP_CPU_Load_TimerRemain())? ((*pDifvar) - RCP_CPU_Load_TimerRemain()): 0;     /* Calulating the difference time */
   *pDifvar = RCP_CPU_Load_TimerRemain();

   return (Result);
}

/*.===================================================================*\
*. FUNCTION: EcuM_SetNoInitByte
*.=====================================================================
*. Return Value:
*.  None
*.
*. Parameters:
*. None
*.
*. External references: Gpt_GetTimeRemaining
*.  External variables:
*.   EcuM_ResetCauseStatus
*.  File scope variables:
*.   None
*.
*. Description:  This function sets the cause for stack overflow, unused
*. interrupt and os self check fail resets to a no init ram variable
\*===================================================================*/
void EcuM_SetNoInitByte(uint8_t value)
{
/* EcuM_ResetCauseStatus - the no init variable used to store and distinguish
 * the reset cause by stack overflow, os_selfcheck and unused interrupt.
 */
   EcuM_ResetCauseStatus  = value;
}

void External_SystemClock_Init()
{
	CLOCK_Init();
}

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the clock generator.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CLOCK_Init(void)
{
	USHORT i;
	UCHAR temp_stabset, temp_stabwait;

	/* Set fMX */
	CMC = _40_CG_HISYS_OSC | _00_CG_SYSOSC_UNDER10M | _00_CG_SUB_PORT;
	OSTS = _07_CG_OSCSTAB_SEL18;
	GUARD |= _01_CG_CSC_ENWR;
	MSTOP = 0U;
	temp_stabset = _FF_CG_OSCSTAB_STA18;
	do
	{
		temp_stabwait = OSTC;
		temp_stabwait &= temp_stabset;
	}
	while (temp_stabwait != temp_stabset);
	/* Set fMAIN */
	DI();
	OSMC = _04_CG_FCLK_OVER20M | _01_CG_FCLK_OVER10M;
	NOP();//__asm( "nop" );
	NOP();
	EI();
	MCM0 = 1U;
	/* Set fPLL */
	GUARD |= _02_CG_PLLCTL_ENWR;
	PLLCTL = _40_CG_PLLLOCKUP_SEL1 | _00_CG_FPLLO_DIV1 | _00_CG_FPLLI_DIV1;
	PLLON = 1U;
	/* Software wait 100us or more */
	for( i=0U; i<=CG_LOCK_WAITTIME; i++ )
	{
		NOP();
	}
	
	while (LOCK != 1U)
	{
		;
	}
	SELPLL = 1U;
	while (SELPLLS != 1U)
	{
		;
	}
	GUARD &= (UCHAR)~_02_CG_PLLCTL_ENWR;
	/* Set fSUB */
	XTSTOP = 1U;
	/* Set fCLK */
	CSS = 0U;
	CKC &= (UCHAR)~_07_CG_CPUCLK;
	CKC |= _00_CG_CPUCLK_MAIN0;
	/* Set fIH */
	HIOSTOP = 1U;    
	GUARD &= (UCHAR)~_01_CG_CSC_ENWR;
}
