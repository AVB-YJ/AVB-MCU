/*==========================================================================*\
*==========================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     SchM_Types.h
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
#ifndef SCHM_TYPES_H
#define SCHM_TYPES_H

#include "Systype.h"

typedef enum SchM_Loop_Timeout_Tag
{
NVM_STARTUP_EEL_HANDLER_TIMEOUT,
SCHM_TIMEOUT_MAX
}
SchM_Loop_Timeout_T;


#endif /* SCHM_TYPES_H*/

/******************************************************************************
 *
 * Revision history
 *
 * Date                By                        Change
 * ----------------------------------------------------------------------
 * 08-Apr-2011        JJ     Implemented Review comments ID 103572.3469
 *****************************************************************************/
