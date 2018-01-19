/*==========================================================================*\
*==========================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     StackCk.h
 * Created By:      SIL
 * Created Date:    16th April 10
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *   
 * This file contains the header declarations of Stack_Ck module
 *
 * Traces to: 10024438_SW_SDD_00001570
 *
 *
 * Applicable Standards (in order of precedence: highest first):
 *  coding standards followed where ever necessary.
 * For Datatypes followed Autosar standard    
 *
 * 
 *
 \*============================================================================*/

/*-------------------------------------------------------------------
 * to avoid multiple definition if the file is included several times
 *-------------------------------------------------------------------*/
#ifndef STACK_CK_H
#define STACK_CK_H

#include "Systype.h"
#include "StackCk_Cfg.h"

void StackCk_Init(void);
void StackCk_Handler(void);
uint8_t StackCk_GetUserStackSize(void);
void StackCk_ReinitUserStackMeasure(void);


#endif /* StackCk_h*/

/****************************************************************************************************************
 *
 * Revision history
 *
 * Date                By                        Change
 * ----------------------------------------------------------------------
 * 02-May_11           Wade               initial reused for ICS 
 *
 * 16th Apr 10         SIL              Initial version: for ICP-B78 Program
 *                                     for release 10024438_TCI/1.00
 * 07th May 2010       SIL                Added 2 new interfaces StackCk_ReinitUserStackMeasure &
 *                                       StackCk_GetUserStackSize needed for DCM module for 10024438_TCI/1.00
 ****************************************************************************************************************/

