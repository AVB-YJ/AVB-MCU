#ifndef WDGM_H
#define WDGM_H

/*===================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     WdgM.h
 * Created By:      SIL
 * Created Date:    01 Jun 2010
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *  This file contains the declaration for the Watch dog manager module
 *
 * Traces to:  10024438_SW_SDD_00001364
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
#include "Std_Types.h"

/*============================================================================*\
 *
 * Exported preprocessor #define constants (object-like macros), upper case
 *
\*============================================================================*/


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


/*============================================================================*\
 *
 * Exported object declarations, mixed case
 *
\*============================================================================*/

  
/*============================================================================*\
 *
 * Exported function prototypes (including function-header-block),
 * (without "extern"), mixed case
 *
\*============================================================================*/
void WdgM_Init(void);
void WdgM_Start(void);
void WdgM_Refresh(void);

#endif /* WDGM_H */

/*******************************************************************************
*
* Changes for ICP B7 program
*
* Date        By                        Change
* ----------------------------------------------------------------------
* 01-Jun-10  IPM      Task no.tci_ik#3550 for release 10024438_TCI/1.00.
*                   Add WdgM component                          
*******************************************************************************/







