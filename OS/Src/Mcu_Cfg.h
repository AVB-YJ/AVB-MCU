#ifndef MCU_CFG_H
#define MCU_CFG_H

/*===========================================================================*
 * Copyright 2011  Technologies, Inc., All Rights Reserved.
 *  Confidential
 *---------------------------------------------------------------------------
 * Module Name:     Mcu
 * %full_filespec: Mcu_Cfg.h~2:incl:ctc_aud#5 %
 * %version: 2 %
 * %derived_by: lzs7ws %
 * %date_created: Thu Jul 19 16:47:23 2012 %
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION: 
 * Configuration File for SSA MCU driver.
 *
 * ABBREVIATIONS:
 *   TBD
 *
 * TRACEABILITY INFO:
 *   Design Document(s): TBD
 *
 *   Requirements Document(s): TBD
 *
 *   Applicable Standards (in order of precedence: highest first):
 *     SW REF 264.15D " C Coding Standards" [31-Oct-2010]
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
 *===========================================================================*/

/*============================================================================*\ 
* PREPROCESSOR DIRECTIVES
\*============================================================================*/ 

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/ 

/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/ 
#include "Std_Types.h" 
#include "Systype.h"

/* EXPORTED DEFINES OR CONSTANTS --------------------------------------------*/ 

/* PRQA S 288 ++
   MISRA RULE 3.1 VIOLATION:
   (at) character  is required for doxygen syntax.
*/

/** \details Development error notification API switch.
 *  \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-MCU-XX}{SSA-REQ-MCU-1-1}
 */
#define MCU_DEV_ERROR_DETECT (STD_OFF)

/**
 * \defgroup ApiFunctionsSwitch
 * \name API functions enable/disable switches
 * \details
 * - Mcu_PerformReset function availability switch
 * - Mcu_GetVersionInfo function availability switch
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-MCU-XX}{SSA-REQ-MCU-1-1}
 * @{
 */
#define MCU_PERFORM_RESET_API (STD_ON)
#define MCU_VERSION_INFO_API (STD_OFF)
/* @} */

/** \details This define determines reset reason used for performing resets via Mcu_PerformReset function.
 *  \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-MCU-XX}{SSA-REQ-MCU-1-1}
 */
#define MCU_WDG_PERFORM_RESET

/** \details Number of configured MCU clocks */
#define MCU_CLOCKS_NO ((uint8_t)1)

/** \details Number of configured RAM sections */
#define MCU_RAM_SECTORS ((uint8_t)1)

/** \defgroup TauSwitches
 * \name Timer Arrays Units switches
 * \details This defines are used to indicate whether TAUx is used.
 * If so, prescalers for TAUx are initialized by MCU driver.
 * @{
 */
 #if 0
#define MCU_TAU0_USED (STD_ON)
#define MCU_TAU1_USED (STD_OFF)
#define MCU_TAU2_USED (STD_OFF)
#endif
/* @} */

/** \defgroup PrescalerFactors
 * \name Prescaler factors of all used TAUs.
 * @{
 */
#define MCU_TPS0_VALUE  ((uint16_t)0x4444)
#define MCU_TPS1_VALUE  ((uint16_t)0x4444)
#define MCU_TPS2_VALUE  ((uint16_t)0x4444)
/* @} */

/** \details Values used to set option byte 00C1H
 *  ------------------------------------------------------------------------
 * |   7   |     6    |    5    |   4   |    3    |   2    |   1   |   0    |
 *  ------------------------------------------------------------------------
 * |LIOUSE | LIOSTOPB | LIOSYSB | CLKMB | RESOUTB | OPTPLL | SEL4M | LVIOFF |
 *  ------------------------------------------------------------------------
 * |   1   |     0    |    1    |   0   |    1    |   1    |   0   |   0    |
 *  ---|---------|---------|--------|--------|--------|--------|-------|----
 *     |         |         |        |        |        |        |       |_
 *     |         |         |        |        |        |        |_
 *     |         |         |        |        |        |_ PLL x6 multiplication
 *     |         |         |        |        |_ Uses P130 as normal port (dedicated to output). [ICS Corvette]
 *     |         |         |        |_ Operates clock monitoring.
 *     |         |         |_
 *     |         |_
 *     |_ Enables internal low-speed oscillation operation. [For watchdog and clock monitoring]
 * */
#define MCU_OPTION_BYTE_C1 ((uint8_t)0xAC)

/** \details Values used to set option byte 00C2H
 *  ------------------------------------------------------------------
 * |   7    |   6   |   5   |   4    |    3   |   2   |   1   |   0   |
 *  ------------------------------------------------------------------
 * | PCLOFF |   1   |   1   | CSEL1B | CSEL0B | CCS2B | CCS1B | CCS0B |
 *  ------------------------------------------------------------------
 * |   1    |   1   |   1   |   1    |    0   |   1   |   0   |   1   |
 *  ---|--------|-------|-------|------ --|-------|-------|-------|---
 *     |        |       |       |                                 |___
 *     |        |       |       |      (ICS Corvette - Not used)      |
 *     |        |       |       |          PCL = fPLL/2^2             |
 *     |        |       |       |    If fPLL = 24Mhz, PCL = 6Mhz      |
 *     |        |       |       |_____________________________________|
 *     |        |       |_ N/A
 *     |        |_ N/A
 *     |_ PCL default output disable. [ICS Corvette - Port 140]
 * */
#define MCU_OPTION_BYTE_C2 ((uint8_t)0xF5)

/** \details Values used to set option byte 00C3H
  *  -------------------------------------------------------------------
 * |   7      |   6   |   5   |   4   |   3   |   2   |   1   |    0    |
 *  --------------------------------------------------------------------
 * | OCDENSET |   0   |   0   |   0   |   0   |   1   |   0   | OCDERSD |
 *  --------------------------------------------------------------------
 * |   1      |   0   |   0   |   0   |   0   |   1   |   0   |    1    |
 *  ---|---- -----|-------|-------|-------|-------|-------|---- ---|----
 *     |          |       |       |       |       |       |        |____
 *     |          |       |       |       |       |       |_ N/A        |
 *     |          |       |       |       |       |_ N/A                |
 *     |          |       |       |       |_ N/A                        |
 *     |          |       |       |_ N/A                                |
 *     |          |       |_ N/A          Enables on-chip debugging     |
 *     |          |_ N/A                                                |
 *     |________________________________________________________________|
 * */
#define MCU_OPTION_BYTE_C3 ((uint8_t)0x85)

/** \details CMC register value. This register is one time writable
 * so must be set once in initialization routine.
 ****** Internal HS -osc -> X1 */
#define MCU_CMC_REG_VALUE ((uint8_t) 0x40)

/** \defgroup PLL_used_flags
 * \name Defines used to indicate if PLL is used.
 * @{
 */
#define MCU_PLL_USED ((uint8_t)0x69)
#define MCU_PLL_NOT_USED ((uint8_t)0x96)
/* @} */

/** \defgroup PllDivBits
 * \name PLL division bits
 * @{
 */
#define MCU_PLL_DIV0 (0u)
#define MCU_PLL_DIV1 (0u)
/* @} */

/** \defgroup Clock_IDs
 * \name User identifiers of all MCU clocks.
 * @{
 */
#define McuClockReferencePoint   ((Mcu_ClockType)0)
/* @} */

/** \defgroup RAM_sectors_IDs
 * \name User identifiers of all RAM sections.
 * @{
 */
#define McuRamSectorSettingConf   ((Mcu_RamSectionType)0)
/* @} */

/** \defgroup Mcu modes
 * \name MCU power modes
 * @{
 */
#define McuModeSettingConf      ((Mcu_ModeType)0x00)

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/** \details Type used for defferent clocks setting
 * \Requirements
 * \reqtrace{SSA-SDD-MCU-XX}{SSA-REQ-MCU-1-1}
 */
typedef struct Mcu_ClockConfiguration_Tag
{
   uint8_t cpu_periph_clock;    /**< CPU and peripheral hardware clock source */
   uint8_t pll_used;            /**< Specify whether PLL is unsed */
   uint8_t mstop_bit :1;        /**< MSTOP bit value,'0'
                                 X1 oscillating,'1' - X1 stopped */
   uint8_t hiostop_bit :1;      /**< HIOSTOP bit value.
                                 '0' - iHS operating,'1' - iHS stopped */
   uint8_t mdiv_bits :3;        /**< PLL divider factor */
   uint8_t ostc_reg;            /**< OSTC register value */
   uint8_t osts_reg;            /**< OSTS register value */
} Mcu_ClockConfigurationType;

/** \detais Typed used for RAM sections configuration. */
typedef struct Mcu_RamSectionConfiguration_Tag
{
   uint8_t* base_addr;          /**< RAM section base address */
   uint8_t default_val;         /**< Deafult value to be used for section initialization */
   uint8_t size;                /**< Size of section in bytes */
} Mcu_RamSectionConfigurationType;

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

/** \details This constant array contains settings for all configured clocks */
extern const Mcu_ClockConfigurationType Mcu_ClocksConfiguration[MCU_CLOCKS_NO];

/** \details An array with constant values for all RAM-sections initialization.*/
extern const Mcu_RamSectionConfigurationType Mcu_RamSectionsData[MCU_RAM_SECTORS];

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

#define MCU_CLEAR_UNUSED_BITS_CSC() \
   do { \
      GDCSC = 1; \
      CSC &= (uint8_t)0x81; \
      GDCSC = 0; \
   }while(0)
/* MCU_CLEAR_UNUSED_BITS_CSC */

#define MCU_SET_UNUSED_BITS_CKC() \
   do{ \
      CKC_bit.no3 = 1; \
   }while(0)
/* MCU_SET_UNUSED_BITS_CKC() */
/* END OF FILE -------------------------------------------------------------- */

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------

 * 02-May-2010   Wade Li
 * + Created initial file
 *   - Copied from 10024438_ICP_B78_TCI~10024438_TCI_4_01:project:tci_ik#1
 *
\*===========================================================================*/

#endif /* MCU_CFG_H */

