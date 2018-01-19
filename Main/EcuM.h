#ifndef ECUM_H
#define ECUM_H

/*===================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     EcuM.h
 * Created By:      SIL
 * Created Date:    Fri Jun 13 14:16:10 2008
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_created:  Tue Jun 26 15:36:50 2012 %
 *--------------------------------------------------------------------
 *
 * Description:
 *  ECU state manager header file
 *
 * Traces to:  10024438_SW_SDD_00001365
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
 *
\*===================================================================*/

/*============================================================================*\
 *
 * Preprocessor #include directive(s)
 *
\*============================================================================*/
#include "EcuM_Cfg.h"
#include "MCU.h"
//#include "intrinsics.h"
/*============================================================================*\
 *
 * Exported preprocessor #define constants (object-like macros), upper case
 *
\*============================================================================*/

#define RESET_CAUSE_MAX_COUNTER_VALUE      (uint8_t)0x3FU

#define App_EcuM_Get(signal_name)          App_EcuM_Get_ ## signal_name()

#define App_EcuM_Get_Current_MCU_Reset_Cause()     (EcuM_CurrentMcuResetCause)

/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
	Clock operation mode control register (CMC)
*/
/* High-speed system clock pin operation mode (EXCLK, OSCSEL) */
#define	_C0_CG_HISYS_PIN		0xC0U
#define	_00_CG_HISYS_PORT		0x00U	/* X1, X2 as I/O port */
#define	_40_CG_HISYS_OSC		0x40U	/* X1, X2 as crystal/ceramic resonator connection */
#define	_80_CG_HISYS_PORT1		0x80U	/* X1, X2 as I/O port */
#define	_C0_CG_HISYS_EXT		0xC0U	/* X1 as external clock input, X2 as I/O port */
/* Subsystem clock pin operation mode (EXCLKS, OSCSELS) */
#define	_30_CG_SUB_PIN			0x30U
#define	_00_CG_SUB_PORT			0x00U	/* EXCLKS as I/O port	*/
#define	_30_CG_SUB_EXT			0x30U	/* EXCLKS as external clock input */
/* Control of high-speed system clock oscillation frequency (AMPH) */
#define	_00_CG_SYSOSC_UNDER10M		0x00U	/* 2MHz <= fMX <= 10MHz */
#define	_01_CG_SYSOSC_OVER10M		0x01U	/* 10MHz < fMX <= 20MHz */


/*
	Operation speed mode control register (OSMC)
*/
/* Selection the clock frequency (fCLK) of data flash (DMSTP) */
#define	_00_CG_FCLK_UNDER20M		0x00U	/* fCLK <= 20 MHz */
#define	_04_CG_FCLK_OVER20M		0x04U	/* fCLK > 20 MHz */
/* Selection the clock frequency (fCLK) of code flash (FSEL) */
#define	_00_CG_FCLK_UNDER10M		0x00U	/* fCLK <= 10 MHz */
#define	_01_CG_FCLK_OVER10M		0x01U	/* fCLK > 10 MHz */

/*
	Oscillation stabilization time select register (OSTS)
*/
/* Oscillation stabilization time selection (OSTS2 - OSTS0) */
#define	_07_CG_OSCSTAB_SEL		0x07U
#define	_00_CG_OSCSTAB_SEL8		0x00U	/* 2^8/fx */
#define	_01_CG_OSCSTAB_SEL9		0x01U	/* 2^9/fx */
#define	_02_CG_OSCSTAB_SEL10		0x02U	/* 2^10/fx */
#define	_03_CG_OSCSTAB_SEL11		0x03U	/* 2^11/fx */
#define	_04_CG_OSCSTAB_SEL13		0x04U	/* 2^13/fx */
#define	_05_CG_OSCSTAB_SEL15		0x05U	/* 2^15/fx */
#define	_06_CG_OSCSTAB_SEL17		0x06U	/* 2^17/fx */
#define	_07_CG_OSCSTAB_SEL18		0x07U	/* 2^18/fx */

/*
	Oscillation stabilization time counter status register (OSTC)
*/
/* Oscillation stabilization time status (MOST8 - MOST18) */
#define	_FF_CG_OSCSTAB_STATUS		0xFFU
#define	_00_CG_OSCSTAB_STA0		0x00U	/* < 2^8/fx */
#define	_80_CG_OSCSTAB_STA8		0x80U	/* 2^8/fx */
#define	_C0_CG_OSCSTAB_STA9		0xC0U	/* 2^9/fx */
#define	_E0_CG_OSCSTAB_STA10		0xE0U	/* 2^10/fx */
#define	_F0_CG_OSCSTAB_STA11		0xF0U	/* 2^11/fx */
#define	_F8_CG_OSCSTAB_STA13		0xF8U	/* 2^13/fx */
#define	_FC_CG_OSCSTAB_STA15		0xFCU	/* 2^15/fx */
#define	_FE_CG_OSCSTAB_STA17		0xFEU	/* 2^17/fx */
#define	_FF_CG_OSCSTAB_STA18		0xFFU	/* 2^18/fx */
/*============================================================================*\
 *
 * Exported preprocessor #define macros (i.e., those using # or ## operator),
 * upper case
 *
\*============================================================================*/


/*============================================================================*\
 *
 * Exported type declarations (enum, struct, union, typedef), mixed case
 *
\*============================================================================*/
typedef enum
{
   STACK_OVERFLOW_RESET = (Mcu_ResetType) MCU_RESET_UNDEFINED + 1,    /**<-- Reset caused by stack overflow */
   OS_SELFCHECKS_RESET,                           /**<-- Reset caused by os self check failure */
   UNUSED_INTERRUPT_RESET,                       /**<-- Reset caused by unused interupt */
   RESET_FLAG_LOCAL_WAKEUP_PWR,
   RESET_FLAG_LOCAL_WAKEUP_EJT,
   RESET_FLAG_LIN_WAKEUP,
   RESET_FLAG_OTHER_RESET,
   RESET_FLAG_RUNNING,
   RESET_FLAG_LIN_COMMAND,
   MAX_MCU_RESET_UNDEFINED                              /**<-- Reset unused */
} Soft_ResetType;


/*============================================================================*\
 *
 * Exported object declarations, mixed case
 *
\*============================================================================*/
#if defined QAC || defined POLYSPACE
extern uint8_t EcuM_ResetCauseStatus;
#else
//#pragma dataseg=RESET_CAUSE_VAR
#ifndef RTRT
__no_init extern uint8_t EcuM_ResetCauseStatus;
#endif
//#pragma dataseg=default
#endif

extern uint8_t EcuM_CurrentMcuResetCause;
extern bool Local_Wakeup_Flag;

/*============================================================================*\
 *
 * Exported function prototypes (including function-header-block),
 * (without "extern"), mixed case
 *
\*============================================================================*/
int main(void);
uint16_t EcuM_GetDifBaseTimerStepValue(uint16_t *pDifvar);
extern void EcuM_SetNoInitByte(uint8_t value);
extern void EcuM_Sys_vStartProcess(void);
void EcuM_Stop(void);
/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------
*
* Changes for ICS  program
*
* Date            By                        Change
* -------------------------------------------------------------------------------
* 02-May-2011   Wade    Initial version for ICS Program
                        reuse from Corvette project which reused from B78 project
*******************************************************************************************/


/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
	Clock operation mode control register (CMC)
*/
/* High-speed system clock pin operation mode (EXCLK, OSCSEL) */
#define	_C0_CG_HISYS_PIN		0xC0U
#define	_00_CG_HISYS_PORT		0x00U	/* X1, X2 as I/O port */
#define	_40_CG_HISYS_OSC		0x40U	/* X1, X2 as crystal/ceramic resonator connection */
#define	_80_CG_HISYS_PORT1		0x80U	/* X1, X2 as I/O port */
#define	_C0_CG_HISYS_EXT		0xC0U	/* X1 as external clock input, X2 as I/O port */
/* Subsystem clock pin operation mode (EXCLKS, OSCSELS) */
#define	_30_CG_SUB_PIN			0x30U
#define	_00_CG_SUB_PORT			0x00U	/* EXCLKS as I/O port	*/
#define	_30_CG_SUB_EXT			0x30U	/* EXCLKS as external clock input */
/* Control of high-speed system clock oscillation frequency (AMPH) */
#define	_00_CG_SYSOSC_UNDER10M		0x00U	/* 2MHz <= fMX <= 10MHz */
#define	_01_CG_SYSOSC_OVER10M		0x01U	/* 10MHz < fMX <= 20MHz */

/*
	Clock operation status control register (CSC)
*/
/* Control of high-speed system clock operation (MSTOP) */
#define	_00_CG_HISYS_OPER		0x00U	/* X1 oscillator/external clock operating */
#define	_80_CG_HISYS_STOP		0x80U	/* X1 oscillator/external clock stopped */
/* Subsystem clock operation (XTSTOP) */
#define	_00_CG_SUB_OPER			0x00U	/* external clock from EXCLK pin is valid */
#define	_40_CG_SUB_STOP			0x40U	/* external clock from EXCLK pin is invalid */
/* Internal high-speed oscillator operation (HIOSTOP) */
#define	_00_CG_HIO_OPER			0x00U	/* internal high-speed oscillator operating */
#define	_01_CG_HIO_STOP			0x01U	/* internal high-speed oscillator stopped */

/*
	Oscillation stabilization time counter status register (OSTC)
*/
/* Oscillation stabilization time status (MOST8 - MOST18) */
#define	_FF_CG_OSCSTAB_STATUS		0xFFU
#define	_00_CG_OSCSTAB_STA0		0x00U	/* < 2^8/fx */
#define	_80_CG_OSCSTAB_STA8		0x80U	/* 2^8/fx */
#define	_C0_CG_OSCSTAB_STA9		0xC0U	/* 2^9/fx */
#define	_E0_CG_OSCSTAB_STA10		0xE0U	/* 2^10/fx */
#define	_F0_CG_OSCSTAB_STA11		0xF0U	/* 2^11/fx */
#define	_F8_CG_OSCSTAB_STA13		0xF8U	/* 2^13/fx */
#define	_FC_CG_OSCSTAB_STA15		0xFCU	/* 2^15/fx */
#define	_FE_CG_OSCSTAB_STA17		0xFEU	/* 2^17/fx */
#define	_FF_CG_OSCSTAB_STA18		0xFFU	/* 2^18/fx */

/*
	Oscillation stabilization time select register (OSTS)
*/
/* Oscillation stabilization time selection (OSTS2 - OSTS0) */
#define	_07_CG_OSCSTAB_SEL		0x07U
#define	_00_CG_OSCSTAB_SEL8		0x00U	/* 2^8/fx */
#define	_01_CG_OSCSTAB_SEL9		0x01U	/* 2^9/fx */
#define	_02_CG_OSCSTAB_SEL10		0x02U	/* 2^10/fx */
#define	_03_CG_OSCSTAB_SEL11		0x03U	/* 2^11/fx */
#define	_04_CG_OSCSTAB_SEL13		0x04U	/* 2^13/fx */
#define	_05_CG_OSCSTAB_SEL15		0x05U	/* 2^15/fx */
#define	_06_CG_OSCSTAB_SEL17		0x06U	/* 2^17/fx */
#define	_07_CG_OSCSTAB_SEL18		0x07U	/* 2^18/fx */

/*
	System clock control register (CKC)
*/
/* Status of CPU/peripheral hardware clock fCLK (CLS) */
#define	_00_CG_CPUCLK_FPLL		0x00U	/* PLL clock (fPLL) being selected */
#define	_80_CG_CPUCLK_FIL		0x80U	/* internal low-speed oscillation clock (fIL) being selected */
/* Selection of CPU/peripheral hardware clock fCLK (CSS) */
#define	_00_CG_CPUCLK_SELFPLL		0x00U	/* PLL clock (fPLL) */
#define	_40_CG_CPUCLK_SELFIL		0x40U	/* internal low-speed oscillation clock (fIL) */
/* Status of Main system clock fMAIN (MCS) */
#define	_00_CG_MAINCLK_HIO		0x00U	/* internal high-speed oscillation clock (fIH) */
#define	_20_CG_MAINCLK_HISYS		0x20U	/* high-speed system clock (fMX) */
/* Selection of Main system clock fMAIN (MCM0) */
#define	_00_CG_MAINCLK_SELHIO		0x00U	/* internal high-speed oscillation clock (fIH) */
#define	_10_CG_MAINCLK_SELHISYS		0x10U	/* high-speed system clock (fMX) */
/* CPU clock (fCPU) selection (MDIV2 - MDIV0) */
#define	_07_CG_CPUCLK			0x07U
#define	_00_CG_CPUCLK_MAIN0		0x00U	/* fCLK = fPLL */
#define	_01_CG_CPUCLK_MAIN1		0x01U	/* fCLK = fPLL/2 (default) */
#define	_02_CG_CPUCLK_MAIN2		0x02U	/* fCLK = fPLL/2^2 */
#define	_03_CG_CPUCLK_MAIN3		0x03U	/* fCLK = fPLL/2^3 */
#define	_04_CG_CPUCLK_MAIN4		0x04U	/* fCLK = fPLL/2^4 */
#define	_05_CG_CPUCLK_MAIN5		0x05U	/* fCLK = fPLL/2^5 */

/*
	Operation speed mode control register (OSMC)
*/
/* Selection the clock frequency (fCLK) of data flash (DMSTP) */
#define	_00_CG_FCLK_UNDER20M		0x00U	/* fCLK <= 20 MHz */
#define	_04_CG_FCLK_OVER20M		0x04U	/* fCLK > 20 MHz */
/* Selection the clock frequency (fCLK) of code flash (FSEL) */
#define	_00_CG_FCLK_UNDER10M		0x00U	/* fCLK <= 10 MHz */
#define	_01_CG_FCLK_OVER10M		0x01U	/* fCLK > 10 MHz */

/*
	PLL clock control register (PLLCTL)
*/
/* Lockup wait counter setting value (LCKSEL1, LCKSEL0) */
#define	_C0_CG_PLL_LCK			0xC0U
#define	_00_CG_PLLLOCKUP_SEL0		0x00U	/* 2^8/fPLLI */
#define	_40_CG_PLLLOCKUP_SEL1		0x40U	/* 2^9/fPLLI */
#define	_80_CG_PLLLOCKUP_SEL2		0x80U	/* 2^10/fPLLI */
/* PLL output clock (fPLLO) selection (PLLDIV1) */
#define	_00_CG_FPLLO_DIV1		0x00U	/* does not operate PLL output divider */
#define	_20_CG_FPLLO_DIV2		0x20U	/* operates PLL output half divider */
/* PLL input clock (fPLLI) selection (PLLDIV0) */
#define	_00_CG_FPLLI_DIV1		0x00U	/* does not operate PLL output divider */
#define	_10_CG_FPLLI_DIV2		0x10U	/* operates PLL output half divider */
/* Clock mode selection (SELPLL) */
#define	_00_CG_PLL_FMAIN		0x00U	/* clock through mode (fMAIN) */
#define	_04_CG_PLL_FPLL			0x04U	/* PLL clock select mode (fPLL) */
/* PLL operation control (PLLON) */
#define	_00_CG_PLL_OFF			0x00U	/* stops PLL */
#define	_01_CG_PLL_ON			0x01U	/* operates PLL */

/*
	PLL Clock Status Register (PLLSTS)
*/
/* PLL lock state (LOCK) */
#define	_00_CG_PLLSTATUS_LOCK		0x00U	/* unlocked state */
#define	_80_CG_PLLSTATUS_UNLOCK		0x80U	/* locked state */
/* State of the clock mode (SELPLLS) */
#define	_00_CG_CPUCLK_CLKTHROUGH	0x00U	/* clock through mode (fMAIN) */
#define	_08_CG_CPUCLK_PLL		0x08U	/* PLL clock select mode (fPLL) */

/*
	Specific-register manipulation protection register (GUARD)
*/
/* Protection against manipulation of PLL clock control register (GDPLL) */
#define	_00_CG_PLLCTL_DIWR		0x00U	/* disables manipulation of PLLCTL register */
#define	_02_CG_PLLCTL_ENWR		0x02U	/* enables manipulation of PLLCTL register */
/* Protection against manipulation of clock operation status control register (GDCSC) */
#define	_00_CG_CSC_DIWR			0x00U	/* disables manipulation of CSC register */
#define	_01_CG_CSC_ENWR			0x01U	/* enables manipulation of CSC register */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	CG_LOCK_WAITTIME		2400U
#define CG_SUBWAITTIME			120U
#define CG_FIHWAITTIME			240U
#define CG_OPTIONBYTE			0x000C1U
enum ClockMode
{
	HIOCLK, SYSX1CLK, SYSEXTCLK, FILCLK
};
enum CPUClock
{
	SYSTEMCLOCK, SYSONEHALF, SYSONEFOURTH, SYSONEEIGHTH, SYSONESIXTEENTH, SYSONETHIRTYSECOND
};
enum PSLevel
{
	PSSTOP, PSHALT
};
enum StabTime
{
	STLEVEL0, STLEVEL1, STLEVEL2, STLEVEL3, STLEVEL4, STLEVEL5, STLEVEL6, STLEVEL7
};

/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
	Clock operation mode control register (CMC)
*/
/* High-speed system clock pin operation mode (EXCLK, OSCSEL) */
#define	_C0_CG_HISYS_PIN		0xC0U
#define	_00_CG_HISYS_PORT		0x00U	/* X1, X2 as I/O port */
#define	_40_CG_HISYS_OSC		0x40U	/* X1, X2 as crystal/ceramic resonator connection */
#define	_80_CG_HISYS_PORT1		0x80U	/* X1, X2 as I/O port */
#define	_C0_CG_HISYS_EXT		0xC0U	/* X1 as external clock input, X2 as I/O port */
/* Subsystem clock pin operation mode (EXCLKS, OSCSELS) */
#define	_30_CG_SUB_PIN			0x30U
#define	_00_CG_SUB_PORT			0x00U	/* EXCLKS as I/O port	*/
#define	_30_CG_SUB_EXT			0x30U	/* EXCLKS as external clock input */
/* Control of high-speed system clock oscillation frequency (AMPH) */
#define	_00_CG_SYSOSC_UNDER10M		0x00U	/* 2MHz <= fMX <= 10MHz */
#define	_01_CG_SYSOSC_OVER10M		0x01U	/* 10MHz < fMX <= 20MHz */

/*
	Clock operation status control register (CSC)
*/
/* Control of high-speed system clock operation (MSTOP) */
#define	_00_CG_HISYS_OPER		0x00U	/* X1 oscillator/external clock operating */
#define	_80_CG_HISYS_STOP		0x80U	/* X1 oscillator/external clock stopped */
/* Subsystem clock operation (XTSTOP) */
#define	_00_CG_SUB_OPER			0x00U	/* external clock from EXCLK pin is valid */
#define	_40_CG_SUB_STOP			0x40U	/* external clock from EXCLK pin is invalid */
/* Internal high-speed oscillator operation (HIOSTOP) */
#define	_00_CG_HIO_OPER			0x00U	/* internal high-speed oscillator operating */
#define	_01_CG_HIO_STOP			0x01U	/* internal high-speed oscillator stopped */

/*
	Oscillation stabilization time counter status register (OSTC)
*/
/* Oscillation stabilization time status (MOST8 - MOST18) */
#define	_FF_CG_OSCSTAB_STATUS		0xFFU
#define	_00_CG_OSCSTAB_STA0		0x00U	/* < 2^8/fx */
#define	_80_CG_OSCSTAB_STA8		0x80U	/* 2^8/fx */
#define	_C0_CG_OSCSTAB_STA9		0xC0U	/* 2^9/fx */
#define	_E0_CG_OSCSTAB_STA10		0xE0U	/* 2^10/fx */
#define	_F0_CG_OSCSTAB_STA11		0xF0U	/* 2^11/fx */
#define	_F8_CG_OSCSTAB_STA13		0xF8U	/* 2^13/fx */
#define	_FC_CG_OSCSTAB_STA15		0xFCU	/* 2^15/fx */
#define	_FE_CG_OSCSTAB_STA17		0xFEU	/* 2^17/fx */
#define	_FF_CG_OSCSTAB_STA18		0xFFU	/* 2^18/fx */

/*
	Oscillation stabilization time select register (OSTS)
*/
/* Oscillation stabilization time selection (OSTS2 - OSTS0) */
#define	_07_CG_OSCSTAB_SEL		0x07U
#define	_00_CG_OSCSTAB_SEL8		0x00U	/* 2^8/fx */
#define	_01_CG_OSCSTAB_SEL9		0x01U	/* 2^9/fx */
#define	_02_CG_OSCSTAB_SEL10		0x02U	/* 2^10/fx */
#define	_03_CG_OSCSTAB_SEL11		0x03U	/* 2^11/fx */
#define	_04_CG_OSCSTAB_SEL13		0x04U	/* 2^13/fx */
#define	_05_CG_OSCSTAB_SEL15		0x05U	/* 2^15/fx */
#define	_06_CG_OSCSTAB_SEL17		0x06U	/* 2^17/fx */
#define	_07_CG_OSCSTAB_SEL18		0x07U	/* 2^18/fx */

/*
	System clock control register (CKC)
*/
/* Status of CPU/peripheral hardware clock fCLK (CLS) */
#define	_00_CG_CPUCLK_FPLL		0x00U	/* PLL clock (fPLL) being selected */
#define	_80_CG_CPUCLK_FIL		0x80U	/* internal low-speed oscillation clock (fIL) being selected */
/* Selection of CPU/peripheral hardware clock fCLK (CSS) */
#define	_00_CG_CPUCLK_SELFPLL		0x00U	/* PLL clock (fPLL) */
#define	_40_CG_CPUCLK_SELFIL		0x40U	/* internal low-speed oscillation clock (fIL) */
/* Status of Main system clock fMAIN (MCS) */
#define	_00_CG_MAINCLK_HIO		0x00U	/* internal high-speed oscillation clock (fIH) */
#define	_20_CG_MAINCLK_HISYS		0x20U	/* high-speed system clock (fMX) */
/* Selection of Main system clock fMAIN (MCM0) */
#define	_00_CG_MAINCLK_SELHIO		0x00U	/* internal high-speed oscillation clock (fIH) */
#define	_10_CG_MAINCLK_SELHISYS		0x10U	/* high-speed system clock (fMX) */
/* CPU clock (fCPU) selection (MDIV2 - MDIV0) */
#define	_07_CG_CPUCLK			0x07U
#define	_00_CG_CPUCLK_MAIN0		0x00U	/* fCLK = fPLL */
#define	_01_CG_CPUCLK_MAIN1		0x01U	/* fCLK = fPLL/2 (default) */
#define	_02_CG_CPUCLK_MAIN2		0x02U	/* fCLK = fPLL/2^2 */
#define	_03_CG_CPUCLK_MAIN3		0x03U	/* fCLK = fPLL/2^3 */
#define	_04_CG_CPUCLK_MAIN4		0x04U	/* fCLK = fPLL/2^4 */
#define	_05_CG_CPUCLK_MAIN5		0x05U	/* fCLK = fPLL/2^5 */

/*
	Operation speed mode control register (OSMC)
*/
/* Selection the clock frequency (fCLK) of data flash (DMSTP) */
#define	_00_CG_FCLK_UNDER20M		0x00U	/* fCLK <= 20 MHz */
#define	_04_CG_FCLK_OVER20M		0x04U	/* fCLK > 20 MHz */
/* Selection the clock frequency (fCLK) of code flash (FSEL) */
#define	_00_CG_FCLK_UNDER10M		0x00U	/* fCLK <= 10 MHz */
#define	_01_CG_FCLK_OVER10M		0x01U	/* fCLK > 10 MHz */

/*
	PLL clock control register (PLLCTL)
*/
/* Lockup wait counter setting value (LCKSEL1, LCKSEL0) */
#define	_C0_CG_PLL_LCK			0xC0U
#define	_00_CG_PLLLOCKUP_SEL0		0x00U	/* 2^8/fPLLI */
#define	_40_CG_PLLLOCKUP_SEL1		0x40U	/* 2^9/fPLLI */
#define	_80_CG_PLLLOCKUP_SEL2		0x80U	/* 2^10/fPLLI */
/* PLL output clock (fPLLO) selection (PLLDIV1) */
#define	_00_CG_FPLLO_DIV1		0x00U	/* does not operate PLL output divider */
#define	_20_CG_FPLLO_DIV2		0x20U	/* operates PLL output half divider */
/* PLL input clock (fPLLI) selection (PLLDIV0) */
#define	_00_CG_FPLLI_DIV1		0x00U	/* does not operate PLL output divider */
#define	_10_CG_FPLLI_DIV2		0x10U	/* operates PLL output half divider */
/* Clock mode selection (SELPLL) */
#define	_00_CG_PLL_FMAIN		0x00U	/* clock through mode (fMAIN) */
#define	_04_CG_PLL_FPLL			0x04U	/* PLL clock select mode (fPLL) */
/* PLL operation control (PLLON) */
#define	_00_CG_PLL_OFF			0x00U	/* stops PLL */
#define	_01_CG_PLL_ON			0x01U	/* operates PLL */

/*
	PLL Clock Status Register (PLLSTS)
*/
/* PLL lock state (LOCK) */
#define	_00_CG_PLLSTATUS_LOCK		0x00U	/* unlocked state */
#define	_80_CG_PLLSTATUS_UNLOCK		0x80U	/* locked state */
/* State of the clock mode (SELPLLS) */
#define	_00_CG_CPUCLK_CLKTHROUGH	0x00U	/* clock through mode (fMAIN) */
#define	_08_CG_CPUCLK_PLL		0x08U	/* PLL clock select mode (fPLL) */

/*
	Specific-register manipulation protection register (GUARD)
*/
/* Protection against manipulation of PLL clock control register (GDPLL) */
#define	_00_CG_PLLCTL_DIWR		0x00U	/* disables manipulation of PLLCTL register */
#define	_02_CG_PLLCTL_ENWR		0x02U	/* enables manipulation of PLLCTL register */
/* Protection against manipulation of clock operation status control register (GDCSC) */
#define	_00_CG_CSC_DIWR			0x00U	/* disables manipulation of CSC register */
#define	_01_CG_CSC_ENWR			0x01U	/* enables manipulation of CSC register */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	CG_LOCK_WAITTIME		2400U
#define CG_SUBWAITTIME			120U

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void External_SystemClock_Init();
void CLOCK_Init(void);
void CLOCK_UserInit(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

#endif
