/****************************************************************************\
 * FILE: ivn_faw_nm_config.c
 ****************************************************************************
 * Copyright 2007  Technologies, Inc., All Rights Reserved.
 *  Confidential
***************************************************************************
*
*	C %name:		ivn_faw_nm_config.c %
*	Instance:		tci_ibs2_1
*	Description:	
*	%created_by:	wzqndv %
*	%date_created:	Fri May  9 19:55:53 2014 %
*
* ***************************************************************************
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

/*****************************************************************************
 * Include Files
 ****************************************************************************/
#include "can_handler.h"
#include "can_aif_rx.h"
#include "can_aif_tx.h"
#include "can_sch_rx.h"
#include "can_vbm_rx.h"
#include "ivn_faw_nm.h"
#include "ivn_faw_nm_config.h"

#include "can_timer_mod.h"

/*****************************************************************************
 * #define Constants
 ****************************************************************************/

/*****************************************************************************
 * Local Type Declarations
 ****************************************************************************/



/*****************************************************************************
 * Global Variables
 ****************************************************************************/
Boolean_Returnvalue_T Appln_Bus_Off_Recovered_Flag = cbTRUE ;
/*
typedef enum
{
   BUS_OFF,
   BUS_VERIFY,
   BUS_ACTIVE
}Appln_Bus_Off_Recovered_Flag_T;

static Appln_Bus_Off_Recovered_Flag_T Appln_Bus_Off_Recovered_Flag = BUS_ACTIVE;
*/
/*****************************************************************************
 * File Scope Variables
 ****************************************************************************/

/*****************************************************************************
 * File Scope Function Prototypes
 ****************************************************************************/

/*****************************************************************************
 * Local Inlines/ Function-like Macros
 ****************************************************************************/

/*****************************************************************************
 * Function Definition
 ****************************************************************************/



/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void Appl_Network_Power_Down(void)
{
  /* here application function needs to be called to excute the power down seq */
  #ifdef CAN_CH0_SELECTED
     CAN_Handler_Shut_Down(0);
  #endif
  #ifdef CAN_CH1_SELECTED
     CAN_Handler_Shut_Down(1);
  #endif

}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void Appl_Bus_Off_Notify(void)
{
  /* here application function needs to be called to take necessary action  */
  /* when there is bus off  */
  Appln_Bus_Off_Recovered_Flag = cbFALSE;
  //Appln_Bus_Off_Recovered_Flag = BUS_OFF;

}
/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void Appl_Bus_Off_Recovery_Notify(void)
{
  /* here application function needs to be called to take necessary action  */
  /* after bus off recovery */
  Appln_Bus_Off_Recovered_Flag = cbTRUE;
  //Appln_Bus_Off_Recovered_Flag = BUS_ACTIVE;
  //Clear_CAN_Rx_Msg_Timeout_Flags();

}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :This function disbles the only TX channel, as per FAW 
 *                    requirement
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 * 
 ******************************************************************************/
void NM_Disable_Communication(void)
{
  /* here AIF/IL function needs to be called to disable normal communication    */
  #ifdef CAN_CH0_SELECTED
     AIF_Set_Tx_Inactive(0);
     //as per requirement from FAW
	 //AIF_Set_Rx_Inactive(0);
  #endif
  #ifdef CAN_CH1_SELECTED
    AIF_Set_Tx_Inactive(1);
    AIF_Set_Rx_Inactive(1);
  #endif
}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Enable_Communication(void)
{
  /* here AIF/IL function needs to be called to enable normal communication    */
  #ifdef CAN_CH0_SELECTED
     #ifdef CAN_TX_MSG_SUPPORTED
     AIF_Set_Tx_Active(0);
     #endif
     AIF_Set_Rx_Active(0);
  #endif
  #ifdef CAN_CH1_SELECTED
    #ifdef CAN_TX_MSG_SUPPORTED
    AIF_Set_Tx_Active(1);
    #endif
    AIF_Set_Rx_Active(1);
  #endif
}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Initialize_CAN_Driver(void)
{
  /* here driver function needs to be called to initialize CAN Driver */
  #ifdef CAN_CH0_SELECTED
     AIF_Set_Rx_Active(0);
     #ifdef CAN_TX_MSG_SUPPORTED
     AIF_Set_Tx_Active(0);
     #endif
     NM_CAN_Driver_Init(0);
  #endif

  #ifdef CAN_CH1_SELECTED
     AIF_Set_Rx_Active(1);
     #ifdef CAN_TX_MSG_SUPPORTED
     AIF_Set_Tx_Active(1);
     #endif   
     NM_CAN_Driver_Init(1);
  #endif
}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_BusOff_Initialize_CAN_Handler(void)
{
  /* here driver function needs to be called to initialize CAN Driver */
  #ifdef CAN_CH0_SELECTED

     AIF_Set_Rx_Active(0);
     #ifdef CAN_TX_MSG_SUPPORTED
       AIF_Set_Tx_Active(0);
     #endif   
  #ifdef CAN_HANDLER_TIMER_MODULE_SUPPORTED
  CAN_TIMER_Warm_Init(0);
  #endif	 
     VBM_Warm_Initialization_Tx(0);
     VBM_Warm_Initialization_Rx(0);
     NM_CAN_Driver_Init(0);
  #endif
  #ifdef CAN_HANDLER_SCHEDULER_MODULE_SUPPORTED
  SCH_Tx_Cold_Initialization(0);
  #ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
  SCH_Rx_Cold_Initialization(0);
#endif
  #endif
  #ifdef CAN_CH1_SELECTED

     AIF_Set_Rx_Active(1);
     #ifdef CAN_TX_MSG_SUPPORTED
       AIF_Set_Tx_Active(1);
     #endif 
     VBM_Warm_Initialization_Tx(1);
     VBM_Warm_Initialization_Rx(1);
     NM_CAN_Driver_Init(1);
  #endif
}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
/*
canuint8_t NM_Get_Rx_Msg_Ind(canuint8_t msg_num)
{
  // here AIF/IL function needs to be called to get the message indication 
  #ifdef CAN_CH0_SELECTED
    return (AIF_NM_Get_Rx_Msg_Ind_Ch0(msg_num));
  #endif
  #ifdef CAN_CH1_SELECTED
    return (AIF_NM_Get_Rx_Msg_Ind_Ch1(msg_num));
  #endif
}
*/
/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
/*
void NM_Clear_Rx_Msg_Ind(canuint8_t msg_num)
{
  // here AIF/IL function needs to be called to clear the message indication 
  // application needs to clear this flag 
  #ifdef CAN_CH0_SELECTED
     AIF_NM_Clr_Rx_Msg_Ind_Ch0(msg_num);
  #endif
  #ifdef CAN_CH1_SELECTED
     AIF_NM_Clr_Rx_Msg_Ind_Ch1(msg_num);
  #endif
}
*/
/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Disable_Transmit_Messages(void)
{
  /* here AIF/IL function needs to be called to disable tx messages            */
  #ifdef CAN_CH0_SELECTED
     AIF_Set_Tx_Inactive(0);
  #endif
  #ifdef CAN_CH1_SELECTED
    AIF_Set_Tx_Inactive(1); 
  #endif
}

/******************************************************************************
 * FUNCTION          :                                                        
 ******************************************************************************
 * ABSTRACT          :
 *
 * RETURN PARAMETERS :
 *
 * PARAMETERS        :
 *
 * CALLING RATE     :
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Enable_Transmit_Messages(void)
{
  /* here AIF/IL function needs to be called to enable tx messages             */
  #ifdef CAN_CH0_SELECTED
     #ifdef CAN_TX_MSG_SUPPORTED
       AIF_Set_Tx_Active(0);
     #endif   
  #endif
  #ifdef CAN_CH1_SELECTED
     #ifdef CAN_TX_MSG_SUPPORTED
       AIF_Set_Tx_Active(1);
     #endif   
  #endif
}
/**************************************************************************************************
  Changes for FAW

  Rev.   SCR        Date        By                             Description
  ---- ---------  --------    -----         -------------------------------------------------------
  1.0   CR-199    21Nov07    HZ8S0R                Created Initial Version 
  2.0               10March10  fz40qj                For FAW Initial version
  3.0   tci_cmn#47	22Oct10	   zzdr6q			Changed the APIs from SCH to AIF
 **************************************************************************************************/
