/*==========================================================================*\
*==========================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     StackCk_Cfg.h
 * Created By:      SIL
 * Created Date:    22nd Mar 2011
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_2 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *   
 * This file contains the header declarations of Stack_Ck configuration module
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
#ifndef STACK_CK_CFG_H
#define STACK_CK_CFG_H

#define STACK_PATTERN              ((uint8_t)0xA5U)

#ifdef POLYSPACE
#define STACK_ARRAY_SIZE            256
#endif

#endif /* StackCk_h*/

/****************************************************************************************************************
 *
 * Revision history
 *
 * Date                By                        Change
 * -------------------------------------------------------------------------------------------------------------
 * 16th Apr 10        SIL              Initial version: for ICP-B78 Program
 *                                     for release 10024438_TCI/5.00 ,Task no tci_ik#5073
 ****************************************************************************************************************/

