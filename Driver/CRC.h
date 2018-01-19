#ifndef _CRC_H
#define _CRC_H
/*============================================================================*\
 *------------------------------------------------------------------------------
 * Module Name:     CRC.h
 * Created By:      KS 
 * Created Date:    30-Apr-2010 
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_5 % 
 * %derived_by:     lzs7ws %
 * %date_modified:  % 
 *------------------------------------------------------------------------------
 *
 * Description: This file contains the functions for calculating CRC
 *
 * Traces to: 10024438_SW_SDD_00001569
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
#include "Std_types.h"
#include "CRC_Cfg.h"

/*===========================================================================*\
 * (e) Exported preprocessor #define constants (object-like macros)
\*===========================================================================*/
 #define CHKSUM_OFFSET 0x5555
 
#define CHECKSUM_SIZE 2                                  //define number of bytes in a checksum

#define  UPDATE_CHECKSUM   TRUE                          // update (change) checksum
#define  VERIFY_CHECKSUM   FALSE                         // do not modifiy checksum


#define  NEW_CHECKSUM      TRUE                          // Start a new checksum (not partial sum)
#define  RESET_CHECKSUM    true                          // Start a new checksum (not partial sum)
#define  CONTINUE_CHECKSUM false                         // Add to previous sum  (partial sum)

/*===========================================================================*\
 * (f) Exported preprocessor #define macros (i.e. those using # or ## operator)
\*===========================================================================*/

/*===========================================================================*\
 * (g) Exported type declarations (enum, struct, union, typedef)
\*===========================================================================*/

/*===========================================================================*\
 * (h) Exported object declarations
\*===========================================================================*/

/*============================================================================*\
 *
 * Exported function prototypes (including function-header-block),
 * (without "extern"), mixed case
 *
\*============================================================================*/
uint16_t CRC_CalcCRC(uint16_t InitValue, uint8_t size, const uint8_t *data);

void CRC_InitCalcPartOfCRC(uint16_t crc_init_value);
uint16_t CRC_CalcPartOfCRC(uint32_t Startaddr, uint16_t Length );
uint16_t Getsum (uint32_t Strt_Addr, size_t size,
               bool_t update, bool_t initialize_chksum, uint16_t *checksum);
/*******************************************************************************
*
* Changes for ICP B78 program 
*
* Date        By                        Change
* -----------------------------------------------------------------------------
* 30-Apr-10   KS   Created a module for release 10024438_TCI/1.00
* 07-May-10   KS   Removed the function for release 10024438_TCI/1.00
*   - CalcPartOfCRC()
* 23-Jun-10   SB      Task tci_ik#3689 for release 10024438_TCI/2.00
*                      Added function for for FLASH check.
* 09-Sep-10    RS   Task no.tci_ik#4119 for release 10024438_TCI/3.00.
*                   Changes based on SAD review comments.
* 11-Feb-11    GC   Task no.tci_ik#4921 for release 10024438_TCI/5.00.
*                  - corrections in File Header
*******************************************************************************/
#endif /*  _CRC_H */
