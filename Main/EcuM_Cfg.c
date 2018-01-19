/*===================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     EcuM_Cfg.c
 * Created By:      SIL
 * Created Date:    19th May 2010
 * %version:         1 %
 * %cvtype:          csrc %
 * %instance:        ctc_aud_5 %
 * %derived_by:      lzs7ws %
 * %date_modified:   %
 *--------------------------------------------------------------------
 *
 * Description:
 *   This is the file which contains configuration data for EcuM module
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
#include "EcuM_Cfg.h"
/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/
#define ICP_NODE_ADDRESS    (uint8_t)0x3BU
#define TEST_VERSION_MARKER (uint8_t)0x99U
#define ECUM_SW_VER_LENTH     8
/*============================================================================*\
 *
 *  Constant Declarations
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
* 17-Aug-2011   Wade    change version info to system.c
* 03-Aug-2011   Wade    version info division
* 23-May-2011   Wade    add version info for ICS
* 02-May-2011   Wade    Initial version for ICS Program
                        reuse from Corvette project which reused from B78 project
*******************************************************************************************/


