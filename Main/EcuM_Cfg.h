#ifndef ECUM_CFG_H
#define ECUM_CFG_H
/*===================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     EcuM_Cfg.h
 * Created By:      SIL
 * Created Date:    21st April 2010
 * %version:         1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_created:   Tue Jun 26 15:36:51 2012 %
 *--------------------------------------------------------------------
 *
 * Description:
 *   This is a ECU state manager module which is the manager of ECU
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
#include "Systype.h"
/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/
#define EcuM_CPUClk     24000000 /* 24Mhz CPU Clock */
#define EcuM_ClkDivider 16      /* Based on GPT channel 21 configuration (TPS2) */
/* offset of -4 to get precise 1ms timer tick after trial & error */
#define EcuM_OSTickCompareValue  (uint16_t)((EcuM_CPUClk / (EcuM_ClkDivider * 1000))  - 4)

#define EcuM_CPULoadCompareTime 0xFFFFU

#define EcuM_CheckSumAddressMSB  0xFFFFU         /* Address of Checksum MSB */
#define EcuM_CheckSumAddressLSB  0xFFFEU         /* Address of Checksum LSB */

#ifdef TEMP_RELEASE_VERSION
#define ECUM_SOFT_MAJOR_VER_INDEX       1
#define ECUM_SOFT_MINOR_VER_INDEX       2
#else
#define ECUM_SOFT_MAJOR_VER_INDEX       4
#define ECUM_SOFT_MINOR_VER_INDEX       5
#endif

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
//extern const uint8_t EcuM_SwVersion[];      
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
* 18-May-2011   wade    update the file
* 02-May-2011   Wade    Initial version for ICS Program
                        reuse from Corvette project which reused from B78 project
*******************************************************************************************/

#endif

