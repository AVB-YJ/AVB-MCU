/*==========================================================================*\
*==========================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     SchM.h
 * Created By:      JJ
 * Created Date:    13th December 10
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_2 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *   
 * This module schedules the IDLE tasks and launch the reconfiguration and 
 * self-test requested by robustness
 *
 * Traces to: 10024438_SW_SDD_00002054
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
#ifndef SCHM_H
#define SCHM_H

#include "SchM_Cfg.h"
#include "Adc_Cfg.h"


void Os_Idle_Task_Robustness(void);

extern Std_ReturnType SchM_Loop_Timeout(SchM_Loop_Timeout_T index);
extern void SchM_Timeout_Get_Ref_Time(void);

#ifdef PROJ_UNUSED_CODE
extern void SchM_EnterCriticalSection(void);
extern void SchM_ExitCriticalSection(void);
#endif

#endif /* SchM_H*/

/******************************************************************************
 *
 * Revision history
 *
 * Date                By                        Change
 * ----------------------------------------------------------------------
 * 02-May_2011      Wade      initial changed for ICS
 *
 * 14 Dec 2010      JJ        Task No.tci_ik#4553 for release 10024438_TCI/4.00
 *                            Added the SAD req -03.3-0100
 * 30-Dec-2010    JJ        Task no.tci_ik#4666 for release 10024438_TCI/4.00.
 *                        - Implemented Robustness SRD 00.1-0028
 * 11-Feb-11      GC        Task no.tci_ik#4921 for release 10024438_TCI/5.00.
 *                        - corrections in File Header
 * 25-Feb-11  KK   Task no.tci_ik#4984 for release 10024438_TCI/5.00.
 *             - SAD verification comments implementation
 * 25-Mar-11  JJ   Task no.tci_ik#5117 for release 10024438_TCI/5.00.
 *                         - Added Lvd_SelfRecovery to idle task
 * 07-Apr-11   JJ    Task no.tci_ik#5154 for release 10024438_TCI/5.00.
 *                   Added the Loop Timeout, SAD req 04.7-0322
 * 08-Apr-2011        JJ     Implemented Review comments ID 103572.3469 
 *****************************************************************************/
