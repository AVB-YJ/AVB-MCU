/**************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_vbm_config.c                                         
  File Description:
  This module contains transmit and receive parameter tables. The             
  parameter tables contain supported messages specific information.           

**************************************************************/

#include "can_vbm_config.h"
#include "can_vbm_tx.h"
#include "can_vbm_rx.h"
//#include "can_tp_config.h"


/**************************************************************

Include layer specific header files to call APIs inside timer notifier function

**************************************************************/

#include "can_sch_tx.h"

#include "can_sch_rx.h"

/**************************************************************

                 Receive  Configuration                          

**************************************************************/

#ifdef CAN_CH0_SELECTED

const VBM_Receive_Msg_Parameter_T 
VBM_Rx_Msg_Parameter_Table_Ch0 [] =

{

/* Make sure that IDs in the following table are arranged in increasing order.
For variable dlc, dlc should be entered as 9
maximum supported buffer_depth is 127                                         */
   /*  ID  ,   Msg_ID_Type,    DLC    ,              notifier_function_ptr  ,   notifier_function_Overrun  ,    Realtime/fifo   ,     Buffer depth*/ 

   { 0x288,STANDARD_ID, CAN_CH0_RX_MSG1_DLC, CAN_Rx_Msg_Notifier0_Ch0, CAN_Rx_Msg_Overrun_Notifier0_Ch0, RX_REALTIME_MESSAGE,  1},

   { 0x2B0 ,STANDARD_ID, CAN_CH0_RX_MSG2_DLC, CAN_Rx_Msg_Notifier1_Ch0, CAN_Rx_Msg_Overrun_Notifier1_Ch0, RX_REALTIME_MESSAGE,  1},

   { 0x320,STANDARD_ID, CAN_CH0_RX_MSG3_DLC, CAN_Rx_Msg_Notifier2_Ch0, CAN_Rx_Msg_Overrun_Notifier2_Ch0, RX_REALTIME_MESSAGE,  1},

   { 0x3E0 ,STANDARD_ID, CAN_CH0_RX_MSG4_DLC, CAN_Rx_Msg_Notifier3_Ch0, CAN_Rx_Msg_Overrun_Notifier3_Ch0, RX_REALTIME_MESSAGE,  1}

};

#endif      /* CAN_CH0_SELECTED */
#ifdef CAN_CH1_SELECTED

#endif
#ifdef CAN_CH2_SELECTED

#endif
const canuint8_t Size_Of_Receive_Param_Tables[] =
{
#ifdef CAN_CH0_SELECTED
(sizeof(VBM_Rx_Msg_Parameter_Table_Ch0)/
sizeof(VBM_Rx_Msg_Parameter_Table_Ch0[0])),
#endif
#ifdef CAN_CH1_SELECTED
(sizeof(VBM_Rx_Msg_Parameter_Table_Ch1)/
sizeof(VBM_Rx_Msg_Parameter_Table_Ch1[0])),
#endif
#ifdef CAN_CH2_SELECTED
(sizeof(VBM_Rx_Msg_Parameter_Table_Ch2)/
sizeof(VBM_Rx_Msg_Parameter_Table_Ch2[0]))
#endif
};
const VBM_Transmit_Msg_Parameter_T VBM_Tx_Msg_Parameter_Table [] =

{ 

/* Make sure that IDs in the following table are arranged in increasing order.
For variable dlc, dlc should be entered as 9
maximum supported buffer_depth is 127                                         */
   /*  Channel Num, ID,   Msg_ID_Type, DLC, notifier_function_ptr, 
   Tx_Msg_Type_Realtime_or_FIFO,  buffer_depth
   Note : If J1939_PROTOCOL_IS_USED ID & ID_Type are not required*/

   {0, 0x2f8 ,STANDARD_ID, CAN_CH0_TX_MSG1_DLC , CAN_Tx_Msg_Notifier0, TX_REALTIME_MESSAGE,  1},

   {0, 0x2f9 ,STANDARD_ID, CAN_CH0_TX_MSG2_DLC , CAN_Tx_Msg_Notifier1, TX_REALTIME_MESSAGE,  1}

};
const canuint8_t Size_Of_Transmit_Param_Table =

(sizeof(VBM_Tx_Msg_Parameter_Table)/sizeof(VBM_Tx_Msg_Parameter_Table[0]));

/**************************************************************

START OF TIMER EXPIRY NOTIFIER FUNCTION PROCESSING

**************************************************************/

#ifdef CAN_CH0_SELECTED
/* CAN Receive Message Notifier Functions: Channel 0 */

/**************************************************************
 Prototype:  CAN_Rx_Msg_Notifier0_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-0 Notify processing                
**************************************************************/

void CAN_Rx_Msg_Notifier0_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
   							     or
   Call Layer specific API to set flag and do the process later in periodic task */
   SCH_Rx_Message_Indication_Ch0(0);

   Appl_CAN_RX_Notifier(0);

}

/**************************************************************
 Prototype:  CAN_Rx_Msg_Notifier1_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-1 Notify processing                
**************************************************************/

void CAN_Rx_Msg_Notifier1_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
   							     or
   Call Layer specific API to set flag and do the process later in periodic task */
   SCH_Rx_Message_Indication_Ch0(1);

   Appl_CAN_RX_Notifier(1);

}

/**************************************************************
 Prototype:  CAN_Rx_Msg_Notifier2_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-2 Notify processing                
**************************************************************/

void CAN_Rx_Msg_Notifier2_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
   							     or
   Call Layer specific API to set flag and do the process later in periodic task */
   SCH_Rx_Message_Indication_Ch0(2);

   Appl_CAN_RX_Notifier(2);

}

/**************************************************************
 Prototype:  CAN_Rx_Msg_Notifier3_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-3 Notify processing                
**************************************************************/

void CAN_Rx_Msg_Notifier3_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
   							     or
   Call Layer specific API to set flag and do the process later in periodic task */
   SCH_Rx_Message_Indication_Ch0(3);

   Appl_CAN_RX_Notifier(3);

}

#endif      /* CAN_CH0_SELECTED */
#ifdef CAN_CH1_SELECTED

#endif
#ifdef CAN_CH2_SELECTED

#endif
#ifdef CAN_CH0_SELECTED
/* CAN Receive Message Overrun Notifier Functions: Channel 0 */

/**************************************************************

 Prototype:  CAN_Rx_Msg_Overrun_Notifier0_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-0 Overrun Notify processing                
**************************************************************/

void CAN_Rx_Msg_Overrun_Notifier0_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
							     or
   Call Layer specific API to set flag and do the process later in periodic task */
}

/**************************************************************

 Prototype:  CAN_Rx_Msg_Overrun_Notifier1_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-1 Overrun Notify processing                
**************************************************************/

void CAN_Rx_Msg_Overrun_Notifier1_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
							     or
   Call Layer specific API to set flag and do the process later in periodic task */
}

/**************************************************************

 Prototype:  CAN_Rx_Msg_Overrun_Notifier2_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-2 Overrun Notify processing                
**************************************************************/

void CAN_Rx_Msg_Overrun_Notifier2_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
							     or
   Call Layer specific API to set flag and do the process later in periodic task */
}

/**************************************************************

 Prototype:  CAN_Rx_Msg_Overrun_Notifier3_Ch0        
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: Channel-0: CAN Rx Message-3 Overrun Notify processing                
**************************************************************/

void CAN_Rx_Msg_Overrun_Notifier3_Ch0(void)
{
   /* Call Layer specific API to process inside this notifier function 
							     or
   Call Layer specific API to set flag and do the process later in periodic task */
}

#endif      /* CAN_CH0_SELECTED */
#ifdef CAN_CH1_SELECTED

#endif
#ifdef CAN_CH2_SELECTED

#endif
/**************************************************************
 Prototype:  CAN_Tx_Msg_Notifier0                      
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: CAN Tx Message-0 Notify processing                           
**************************************************************/
void CAN_Tx_Msg_Notifier0(void)
{
   /* Call Layer specific API to process inside this notifier function
							     or
   Call Layer specific API to set flag and do the process later in periodic task */
   Appl_CAN_TX_Notifier(0);

}
/**************************************************************
 Prototype:  CAN_Tx_Msg_Notifier1                      
 Arguments passed: None                                                      
 Return type: None                                                           
 Functionality: CAN Tx Message-1 Notify processing                           
**************************************************************/
void CAN_Tx_Msg_Notifier1(void)
{
   /* Call Layer specific API to process inside this notifier function
							     or
   Call Layer specific API to set flag and do the process later in periodic task */
   Appl_CAN_TX_Notifier(1);

}

 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

