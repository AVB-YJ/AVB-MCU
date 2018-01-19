/*============================================================================*\
*------------------------------------------------------------------------------
* Module Name:     NVM_Cfg.c
* Created By:      KS
* Created Date:    19-Apr-2010
* %version:        1 %
* %cvtype:         csrc %
* %instance:       ctc_aud_4 %
* %derived_by:     lzs7ws %
* %date_modified:   %
*------------------------------------------------------------------------------
*
* Description: This file contains
*
* Traces to: 10024438_SW_SDD_00001366
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

#include "NVM_Cfg.h"

/* NVM RAM Blocks */
/* EEP_Sector ID Ram Block reserved*/
static uint8_t NVM_RAMBlock_UNUSED0[NVM_BLK0_LENGTH];

/* NOTE: If default values are modified update corresponding CRC 
 *       Values at the CRC Location. When restoring default value
 *       CRC is not calculated once again.
 */

/* NVM EEP sector ID ROM data */
static const uint8_t NVM_ROMBlock_UNUSED0[NVM_BLK0_LENGTH] =
{
   (uint8_t)0x00, 
};


/* NOTE: If default values are modified update corresponding CRC 
 *       Values at the CRC Location. When restoring default value
 *       CRC is not calculated once again.
 */

/* NVM EEP sector ID ROM data */
/* EEL Identifier, Length, NVM Ram block Ref address, Rom Block Ref Address 
 * Standard block or redundent block or Data Set block
 the define same as MPI
 */
const NVM_Mem_Block_Config_T NVM_Mem_config[NVM_MAX_B81_ID] =
{
   /* block0:EEP Sector ID, address: 30000-30007, size 8*/
   {(uint8_t)(NVM_SECTOR_BLK_ID+1), NVM_BLK0_LENGTH, NVM_RAMBlock_UNUSED0,  NVM_ROMBlock_UNUSED0, NVM_STANDARD_BLOCK},
};

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
*  11-Aug-11 wade reconfigure it for ICS
*  25-Aug-11 wade add batt calibration for ICS
*  26-Aug-11 wade add TS reserved, DTC reserved, and reserved space
*  27-Aug-11 wade add re-alignment the calibration rom, 4 bytes every unit
*  19-Sep-11 wade update the EEPROM block according to the MPI define
*  13-Apr-12 wade update the EEPROM block: add dim cal and tsc cal block
*******************************************************************************************/

