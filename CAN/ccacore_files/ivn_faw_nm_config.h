/****************************************************************************\
 * FILE: ivn_faw_nm_config.h
 ****************************************************************************
 * Copyright 2007  Technologies, Inc., All Rights Reserved.
 *  Confidential
***************************************************************************
*
*	Header %name:	ivn_faw_nm_config.h %
*	Instance:		tci_ibs2_1
*	Description:	
*	%created_by:	wzqndv %
*	%date_created:	Fri May  9 19:55:53 2014 %
*
****************************************************************************
 *
 * DESCRIPTION:
 *   Description of file's purpose.
 *
 * ABBREVIATIONS:
 *   List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *
 *   Requirements Document(s):
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
*****************************************************************************/
#ifndef _tci_ibs2_1_ivn_faw_nm_config_h_H
#define _tci_ibs2_1_ivn_faw_nm_config_h_H


/*****************************************************************************
 * Include Files
 *****************************************************************************/
#include "can_handler_datatypes.h"


/*****************************************************************************
 * #define Constants
 *****************************************************************************/
#define NM_CALL_RATE                                                   10
/*
#define NM_IGN_VOL_KL15_ON_TIME                                       2000/NM_CALL_RATE  
#define NM_IGN_OVER_VOL_REC_TIME                                      500/NM_CALL_RATE 
#define NM_IGN_UNDER_VOL_REC_TIME                                     500/NM_CALL_RATE 
*/

#define NM_BUS_OFF_SLOW_RECOVERY_TIME                                1000/NM_CALL_RATE  //10000ms
#define NM_BUS_OFF_QUICK_RECOVERY_TIME                                100/NM_CALL_RATE  //100ms
#define NM_MAX_NUMBER_OF_BUS_OFF_QUICK_RECOVERY_ATTEMPTS                5

//#define NM_BUS_OFF_RECOVERED_TIME                                    1000/NM_CALL_RATE 
//#define NM_NUM_OF_IGN_CYCLES                                           40
//#define NM_NUM_OF_KEY_MSG_DETECT_THRESHOLD                              5 

//#define NM_NUM_OF_MSG_HEAL_THRESHOLD                                   10 
//#define NM_NUM_OF_MSG_DETECT_THRESHOLD                                 10


//#define NM_MAX_RX_MESSAGES_FOR_MONITORING                              8
/* THE Number of RX Messages becomes more than 15 this Macro 
    Need to be defined                                        */
#undef FOUR_BYTE_DTC_STATUS_FLAG

/*****************************************************************************
 * Type Declarations
 *****************************************************************************/


/*****************************************************************************
 * Global Variables
 *****************************************************************************/



/*****************************************************************************
 * Global Function Prototypes
 *****************************************************************************/


/*****************************************************************************
 * Global Inlines/ Function-like Macros
 *****************************************************************************/


/**************************************************************************************************
  Changes for FAW

  Rev.   SCR        Date      By                             Description
  ---- ---------  --------   -----                -------------------------------------------------
  1.0   CR-199    21Dec07    Prakash/HZ8S0R                 Created Initial Version
 **************************************************************************************************/


#endif
