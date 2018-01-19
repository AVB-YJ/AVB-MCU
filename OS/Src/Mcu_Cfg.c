
/*===========================================================================*
 * Copyright 2011  Technologies, Inc., All Rights Reserved.
 *  Confidential
 *---------------------------------------------------------------------------
 * Module Name:     Mcu
 * %full_filespec: Mcu_Cfg.c~1:csrc:ctc_aud#3 %
 * %version: 1 %
 * %derived_by: lzs7ws %
 * %date_created: Tue Jun 26 15:37:47 2012 %
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
#include "Mcu.h" 

/* EXPORTED DEFINES OR CONSTANTS --------------------------------------------*/ 

/*============================================================================*\
* LOCAL TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
* OBJECT DEFINITIONS
\*============================================================================*/
#if defined QAC || defined POLYSPACE
const uint8_t OB_C1;
const uint8_t OB_C2;
const uint8_t OB_C3;    
#else
/* Option bytes setting */
__root __far const uint8_t OB_C1 @ 0x00C1 = MCU_OPTION_BYTE_C1;
__root __far const uint8_t OB_C2 @ 0x00C2 = MCU_OPTION_BYTE_C2;
__root __far const uint8_t OB_C3 @ 0x00C3 = MCU_OPTION_BYTE_C3;
#endif
/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

#define MCU_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

const Mcu_ClockConfigurationType Mcu_ClocksConfiguration[MCU_CLOCKS_NO] =
{ 
   { 
      /* McuClockReferencePoint */
      MCU_INTERNAL_HIGH_SPEED,
      MCU_PLL_NOT_USED,
      1,
      0,
      0,
      (uint8_t)0xF0,  /* 2^11/fx, about 500us for 4MHz OSCillator */
      (uint8_t)0x03,  /* 2^11/fx about 500us for 4MHz OSCillator*/
   }, 
};

const Mcu_RamSectionConfigurationType Mcu_RamSectionsData[MCU_RAM_SECTORS] =
{
   {
      (uint8_t*)0x00,
      (uint8_t)0x00,
      (uint8_t)1,
   },
};

#define MCU_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

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
/* END OF FILE -------------------------------------------------------------- */

