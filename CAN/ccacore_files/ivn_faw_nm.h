/****************************************************************************\
 * FILE: ivn_faw_nm.h
 ****************************************************************************
 * Copyright 2007  Technologies, Inc., All Rights Reserved.
 *  Confidential
****************************************************************************
*
*	Header %name:	ivn_faw_nm.h %
*	Instance:		tci_ibs2_1
*	Description:	
*	%created_by:	wzqjzy %
*	%date_created:	Tue Aug 13 10:36:39 2013 %
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
\*****************************************************************************/
#ifndef _tci_ibs2_1_ivn_faw_nm_h_H
#define _tci_ibs2_1_ivn_faw_nm_h_H

/*****************************************************************************
 * Include Files
 *****************************************************************************/
#include "can_handler_datatypes.h"
#include "ivn_faw_nm_config.h" 
//#include "ad_cond.h"                  /* PBATT_VOLT_UNFILT()  - To be removed later*/

/*****************************************************************************
 * #define Constants
 *****************************************************************************/


/*****************************************************************************
 * Type Declarations
 *****************************************************************************/
/*NM States  */
typedef enum NM_State_Tag
{
   NM_OFF = 0,
   NM_INIT,
   NM_WORKING_WITHOUT_FAILURE,
   NM_WORKING_WITH_FAILURE,
   NM_POWER_DOWN
} NM_State_T;

/* nm ignition voltages */

/* bus off Recovery states */
typedef enum NM_Bus_Off_Rec_State_Tag
{
   NM_BUS_OFF_QUICK_RECOVER_STATE = 0,
   NM_BUS_OFF_QUICK_RECOVER_PROCESS_STATE,
   NM_BUS_OFF_SLOW_RECOVER_STATE,
   NM_BUS_OFF_SLOW_RECOVER_PROCESS_STATE,
   NM_BUS_OFF_RECOVERED_STATE
} NM_Bus_Off_Rec_State_T; 

/* Msg Monitor states */

/*****************************************************************************
 * Global Variables
 *****************************************************************************/
//extern const NM_Msg_Monitor_Parameter_T NM_Receive_Monitor_Parameter_Table [NM_MAX_RX_MESSAGES_FOR_MONITORING];


/*****************************************************************************
 * Global Function Prototypes
 *****************************************************************************/
/* To be called by the communication handler module and Application */
extern void NM_Init(void);
extern void NM_Periodic_Task(void);

extern canuint8_t Get_NM_State(void);
#if 0
extern canuint8_t NM_Get_Rx_Msg_Timeout_Int(canuint8_t  );
extern void NM_Clear_Rx_Msg_Timeout_Int(canuint8_t   );
extern void App_Limited_Functionality(canuint8_t  );
extern void App_Full_Functionality(canuint8_t  );
extern canuint8_t Appl_Read_Ign_Voltage_KL15(void);
extern canuint8_t NM_Get_Rx_Msg_Timeout(canuint8_t   );
extern void NM_Clear_Rx_Msg_Timeout(canuint8_t   );
extern canuint8_t NM_Get_Rx_Msg_Ind(canuint8_t  );
extern void NM_Clear_Rx_Msg_Ind(canuint8_t );
extern canuint8_t Get_Ign_Voltage(void);
extern can_boolean_t NM_Over_Volt_Rec_Timer_Status(void);
extern can_boolean_t NM_Under_Volt_Rec_Timer_Status(void);
extern can_boolean_t NM_Mon_Condition_Check(void);
#endif
extern void Appl_Bus_Off_Notify(void);
extern void Appl_Bus_Off_Recovery_Notify(void);


extern void NM_Bus_Off_Indication(void);
extern void NM_Bus_Off_Recovered(void);



extern void Appl_Network_Power_Down(void);
extern void NM_Disable_Communication(void);
extern void NM_Enable_Communication(void);
extern void NM_Initialize_CAN_Driver(void);
extern void NM_BusOff_Initialize_CAN_Handler(void);

extern void NM_Disable_Transmit_Messages(void);
extern void NM_Enable_Transmit_Messages(void);

extern canuint8_t Get_NM_Busoff_Indication(void);
extern canuint8_t Get_NM_Busoff_Indication_To_Appl(void);
extern void NM_Clear_DTCs_Flags(unsigned char dtc_number);

/*****************************************************************************
 * Global Inlines/ Function-like Macros
 *****************************************************************************/


/**************************************************************************************************
  Changes for MY2009 Mahindra W408 IPC

  Rev.   SCR        Date      By                             Description
  ---- ---------  --------   -----               ------------------------------------------------
  1.0   CS-199    21Nov07  Prakash/HZ8S0R               Created Initial Version
  2.0   CR-405    18Feb08    HZ8S0R         new parameter to indicate key message has been added to 
                                            "NM_Msg_Monitor_Parameter_T" structure varaible.   
  3.0   CR-439    06Mar08    HZ8S0R         new ENUMs are defined for the messages and the type of 
                                            messages for each node.Intf function provided to access
                                            bus off status. 
  4.0   CR-536	  25MAR08	  TNK           The clearing of the NM DTCs Flags with the 
                                            clearing original DTCs 
  6.0
  7.0   CR-857    04Sep08     SI            Added Functions to read the status of over voltage, under volt and
                                            bus off recovery timers.
  8.0   CR-1172  18Feb09      SI            Added NM message monitoring for EMS_8 message
  9.0   CR-1569  27Jul09      SM            Move EE variables to PD KAM. Common init for all EE variables.

 **************************************************************************************************/
#endif
