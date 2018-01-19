#ifndef _ROMCK_H
#define _ROMCK_H
/*============================================================================*\
*------------------------------------------------------------------------------
* Module Name:     RomCk
* Created By:      SB
* Created Date:    30-Apr-2010
* %version:        1 %
* %cvtype:         incl %
* %instance:       ctc_aud_5 %
* %derived_by:     lzs7ws %
* %date_modified:  %
*------------------------------------------------------------------------------
*
* Description: This file contains the functions for ROM check
*
* Traces to: 10024438_SW_SDD_00001571
*
* Applicable Standards (in order of precedence: highest first):
*     SW REF 264.15D "DE Systems C Coding Standards" dated 12-MAR-06
*
* Deviations from Delco C Coding standards:
*   1. C46 - Abbreviations are not documented in this source file.
*
*   2. C54 - Function header block is placed at the beginning of
*      function definition instead before function proto type
*      declaration.
*
*   4. C60 - The function is pre-emptible or re-entrant is not
*      applicable to this program.
\*============================================================================*/

/*============================================================================*\
*
* Preprocessor #include directive(s)
*
\*============================================================================*/

#include "Systype.h" /*standard types*/
#include "RomCk_Cfg.h"
/*===========================================================================*\
* (e) Exported preprocessor #define constants (object-like macros)
\*===========================================================================*/
#define RomCk_Get(signal_name)          RomCk_Get_##signal_name()
#define RomCk_Get_FINAL_CRC()           (RomCk_FinalCRC)

#define FLASH_CHECK_COMPLETE_OK               (uint8_t)0x01U
#define FLASH_CHECK_COMPLETE_NOK              (uint8_t)0xFFU
#define FLASH_CHECK_INPROGRESS                (uint8_t)0x00U

/*===========================================================================*\
* (f) Exported preprocessor #define macros (i.e. those using # or ## operator)
\*===========================================================================*/

/*===========================================================================*\
* (g) Exported type declarations (enum, struct, union, typedef)
\*===========================================================================*/
typedef enum
{
   MODE_SLOW,
   MODE_FAST
} Flashcheck_mode_Type;
/*===========================================================================*\
* (h) Exported object declarations
\*===========================================================================*/
extern uint16_t RomCk_FinalCRC;

/*============================================================================*\
*
* Exported function prototypes (including function-header-block),
* (without "extern"), mixed case
*
\*============================================================================*/
void RomCk_Init(void);
void RomCk_Start(void);
void RomCk_Compute(void);
void RomCk_StopCompute(void);
void RomCk_SetMode(Flashcheck_mode_Type flashcheck_mode);
uint8_t RomCk_GetComputeResult(void);
/*******************************************************************************
*
* Changes for ICP B78 program
*
* Date        By                        Change
* -----------------------------------------------------------------------------
* 02-May_11   Wade   initial version for ICS 
*
* 23-Jun-10   SB     Task tci_ik#3689 for release 10024438_TCI/2.00
                       Created module for FLASH check.
* 20-Jul-10   SIL    Task tci_ik#3836 for release 10024438_TCI/2.00
*                    Implemented review comments
* 09-Sep-10    RS   Task no.tci_ik#4119 for release 10024438_TCI/3.00.
*                   Changes based on SAD review comments.
* 21-Sep-10    RS   Task no.tci_ik#4177 for release 10024438_TCI/3.00.
*                   Peer review correction: Renamed "ROMCK" to "RomCk".
*                   (Capital letters to Small letters)
* 28-Sep-10    RS   Task no.tci_ik#4198 for release 10024438_TCI/3.00.
*                   Changes based on review comment document 
*                   10024438_SW_RVW_00001215_00.14 Nr 61: Renamed extern 
*                   variables to have the module name as prefix.
********************************************************************************/
#endif /*  _ROMCK_H */

