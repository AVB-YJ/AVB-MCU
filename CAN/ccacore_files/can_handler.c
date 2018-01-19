/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - CAN Core                                                   *
 * File Name:  can_handler.c                                                 *
 * Description: This file contains function def's for init and other tasks   *
 *              of  CAN Handler (DCH)                                  *
 *****************************************************************************/
#include "can_handler.h"
//#include "dg_consts.h"
#include "can_handler_config.h"
#include "can_vbm_tx.h"
#include "can_vbm_rx.h"
#include "can_sch_tx.h"
#include "can_sch_rx.h"
#include "can_aif_tx.h"
#include "can_aif_rx.h"
#include "can_drv_init_misc.h"
#include "can_timer_mod.h"
#include "can_handler_appl_notifier_functions.h"
//#include "can_diagserv.h"
#include "ivn_faw_nm.h"
#include "Can_drv_init_misc.h"
#ifdef CAN_TEST_TASK
#include "can_stub.h"
#endif

static CHANNEL_INITIALIZATION_STATUS_T CAN_handler_cold_init_status
                                      [NUMBER_OF_CHANNELS_SUPPORTED];
static unsigned char CAN_Init_Misc_Initialized = cbFALSE;

 void CAN_Handler_Init_Misc(void);

#ifdef HASH_SEARCH
const canuint8_t* Hash_Tables[] =
{
  #ifdef CAN_CH0_HASH_SEARCH
  Hash_Table_Ch0,
  #endif
  #ifdef CAN_CH1_HASH_SEARCH
  Hash_Table_Ch1,
  #endif
  #ifdef CAN_CH2_HASH_SEARCH

  #endif
};
#endif

/*******************************************************************************
 * Function Name : CAN_Handler_Cold_Init                                       *
 * Function Parameters : channel number                                        *
 * Return Value : None                                                         *
 * Description : This function would be called by application to initialize    *
 *          the CAN hanlder on the required channel during cold initialization *
 ******************************************************************************/
void CAN_Handler_Cold_Init(canuint8_t channel_num)
{
  #ifdef CCA_HMI
  Initialize_CAN_Ports(channel_num);
  #endif
  if(cbFALSE == CAN_Init_Misc_Initialized)
  {
    CAN_Handler_Init_Misc();				//nothing to do at present
    CAN_Init_Misc_Initialized = cbTRUE;
  }
  #ifdef CAN_HANDLER_TIMER_MODULE_SUPPORTED
  CAN_TIMER_Cold_Init(channel_num);
  #endif
  #ifdef CAN_HANDLER_TRANSPORT_PROTOCOL_SUPPORTED
  TP_Init();
  #endif
  #ifdef CAN_HANDLER_DIAGNOSTICS_LAYER_SUPPORTED
  DG_Init();
  #endif
  #ifdef CAN_HANDLER_SCHEDULER_MODULE_SUPPORTED
  SCH_Tx_Cold_Initialization(channel_num);
#ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
  SCH_Rx_Cold_Initialization(channel_num);
#endif
  #endif
  #ifdef CAN_HANDLER_AIF_LAYER_SUPPORTED
  AIF_Tx_Cold_Initialization(channel_num);
  AIF_Rx_Cold_Initialization(channel_num);
  #endif
  #ifdef CAN_HANDLER_NM_LAYER_SUPPORTED
  NM_Init();
  #endif
  #ifdef CAN_HANDLER_DRIVER_LAYER_SUPPORTED
  VBM_Cold_Initialization_Tx(channel_num);
  VBM_Cold_Initialization_Rx(channel_num);
  #endif
}

  #ifdef CCA_HMI
void NM_CAN_Driver_Init(canuint8_t channel_num)
{
  if(CD_Cold_Initialization(channel_num))
  {
     CAN_handler_cold_init_status[channel_num] = INITIALIZED;
  }
}

void NM_CAN_Driver_BusOff_Init(canuint8_t channel_num)
{
  if(CD_BusOff_Initialization(channel_num))
  {
     CAN_handler_cold_init_status[channel_num] = INITIALIZED;
  }
}
void NM_CAN_Driver_Wakeup_Init(canuint8_t channel_num)
{
 // if(CD_Wakeup_Initialization(channel_num))
  {
     CAN_handler_cold_init_status[channel_num] = INITIALIZED;
  }
}
#endif
/*******************************************************************************
 * Function Name : Is_CAN_Handler_Initialized                                  *
 * Function Parameters : channel number                                        *
 * Return Value : INITIALIZED/NOT_INITIALIZED                                  *
 * Description : This function would be called by CAN handler layers to check  *
 *          if the Channel is initialized before transmission and reception    *
 ******************************************************************************/
canbool8_t Is_CAN_Handler_Initialized(canuint8_t channel_num)
{
  return(CAN_handler_cold_init_status[channel_num]);
}

/*******************************************************************************
 * Function Name : CAN_Handler_Warm_Init                                       *
 * Function Parameters : channel number                                        *
 * Return Value : None                                                         *
 * Description : This function would be called by application to initialize    *
 *          the CAN hanlder on the required channel during warm initialization *
 ******************************************************************************/
void CAN_Handler_Warm_Init(canuint8_t channel_num)
{
  #ifdef CAN_HANDLER_TIMER_MODULE_SUPPORTED
  CAN_TIMER_Warm_Init(channel_num);
  #endif
 /* #ifdef CAN_HANDLER_TRANSPORT_PROTOCOL_LAYER_SUPPORTED
  TP_Warm_Init();
  #endif
  #ifdef CAN_HANDLER_DIAGNOSTICS_LAYER_SUPPORTED
  DG_Warm_Init();
  #endif
  #ifdef CAN_HANDLER_SCHEDULER_MODULE_SUPPORTED
  SCH_Tx_Warm_Initialization(channel_num);
  SCH_Rx_Warm_Initialization(channel_num);
  #endif
  #ifdef CAN_HANDLER_AIF_LAYER_SUPPORTED
  AIF_Tx_Warm_Initialization(channel_num);
  AIF_Rx_Warm_Initialization(channel_num);
  #endif
  #ifdef CAN_HANDLER_NM_LAYER_SUPPORTED
  NM_Warm_Init();
  #endif   */
  #ifdef CAN_HANDLER_SCHEDULER_MODULE_SUPPORTED
  SCH_Tx_Cold_Initialization(channel_num);
  #ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
  SCH_Rx_Cold_Initialization(channel_num);
#endif
  #endif
  #ifdef CAN_HANDLER_DRIVER_LAYER_SUPPORTED
  VBM_Warm_Initialization_Tx(channel_num);
  VBM_Warm_Initialization_Rx(channel_num);
 /* CD_Warm_Initialization(channel_num);*/
  if(CD_Cold_Initialization(channel_num))
  {
     CAN_handler_cold_init_status[channel_num] = INITIALIZED;
  }
  #endif
}

/*******************************************************************************
 * Function Name : CAN_Handler_Init_Misc                                       *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by application to initialize    *
 *          the CAN hanlder features which are not channel dependent           *
 ******************************************************************************/
 void CAN_Handler_Init_Misc(void)
{
  CD_Init_Misc();
}

/*******************************************************************************
 * Function Name : CAN_Handler_Periodic_Task                                   *
 * Function Parameters :                                                       *
 * Return Value : None                                                         *
 * Description : This function would be called by application to run the       *
 *          CAN hanlder in the required OS Periodic loop                       *
 ******************************************************************************/
void CAN_Handler_Periodic_Task(void)
{
  #ifdef CAN_HANDLER_TRANSPORT_PROTOCOL_SUPPORTED
  //TP_Update_Timers();
  //TP_Periodic_Task();
  #endif
  #ifdef CAN_HANDLER_DIAGNOSTICS_LAYER_SUPPORTED
  DG_Periodic_Task();
  #endif
  #ifdef CAN_HANDLER_SCHEDULER_MODULE_SUPPORTED
  SCH_Tx_Periodic_Task();
  #ifdef TIMEOUT_FOR_RX_MSG_SUPPORTED
  SCH_Rx_Periodic_Task();
  #endif
  #endif
  #ifdef CAN_HANDLER_AIF_LAYER_SUPPORTED
  AIF_Tx_Periodic_Task();
  AIF_Rx_Periodic_Task();
  #endif
  #ifdef CAN_HANDLER_NM_LAYER_SUPPORTED
  NM_Periodic_Task();
  #endif
  #ifdef CAN_TEST_TASK
  CAN_Transmit_Test_Task();
  CAN_Receive_Test_Task();
  Test_Busoff();
  #endif
}


/*******************************************************************************
 * Function Name : CAN_Handler_Timer_Task                                      *
 * Function Parameters :                                                       *
 * Return Value : None                                                         *
 * Description : This function would be called by application to run the       *
 *          CAN hanlder timer task in the required OS Periodic loop.           *
 * If the OS loop for CAN_Handler_Periodic_Task and CAN_Handler_Timer_Task is  *
 * same then call CAN_Handler_Timer_Task before CAN_Handler_Periodic_Task.     *
 * Otherwise call CAN_Handler_Timer_Task at faster rate than                   *
 * CAN_Handler_Periodic_Task depending on the timer requirements               *
 ******************************************************************************/
#ifdef CAN_HANDLER_TIMER_MODULE_SUPPORTED
void CAN_Handler_Timer_Task(void)
{
	#ifdef CCA_HMI
		#ifdef CAN_CH0_SELECTED
			if(CAN_handler_cold_init_status[0] == INITIALIZED)
			{
				CAN_TIMER_Task();
			}
		#endif
			
		#ifdef CAN_CH1_SELECTED
			if(CAN_handler_cold_init_status[1] == INITIALIZED)
			{
				CAN_TIMER_Task();
			}
		#endif
	#endif
	
	#ifdef CCA_HMI
		//CAN_TIMER_Task();
	#endif
}
#endif
/*******************************************************************************
 * Function Name : CAN_Handler_Shut_Down                                       *
 * Function Parameters : channel_num                                           *
 * Return Value : None                                                         *
 * Description : This function would be called by application to shut the      *
 *          required CAN channel                                               *
 * After this appl has to call CAN_Handler_Cold_Init to initiate the           *
 * communication for the shut down channel                                     *
 ******************************************************************************/
void CAN_Handler_Shut_Down(canuint8_t channel_num)
{
  CD_Shut_Communication_Down(channel_num);
  CAN_handler_cold_init_status[channel_num] = NOT_INITIALIZED;
}

#ifdef CAN_SLEEP_MODE_AVAILABLE
/*******************************************************************************
 * Function Name : CAN_Handler_Go_To_Sleep                                       *
 * Function Parameters : channel_num                                           *
 * Return Value : None                                                         *
 * Description : This function would be called by application to take the      *
 *          required CAN channel to sleep mode                                               *
 ******************************************************************************/
Boolean_Returnvalue_T CAN_Handler_Go_To_Sleep(canuint8_t channel_num)
{
     if (SLEEP_OK == CD_Go_To_Sleep(channel_num))
     {
        return cbTRUE;
     }
     else
        return cbFALSE;
}


/*******************************************************************************
 * Function Name : CAN_Handler_Cancel_Sleep                                       *
 * Function Parameters : channel_num                                           *
 * Return Value : None                                                         *
 * Description : This function would be called by application to take the      *
 *          required CAN channel out of  sleep mode                                               *
 ******************************************************************************/
Boolean_Returnvalue_T CAN_Handler_Cancel_Sleep(canuint8_t channel_num)
{
      if (SLEEP_OK == CD_Cancel_Sleep_State( channel_num))
     {
        return cbTRUE;
     }
     else
     {
        return cbFALSE;
     }

}

#endif

/*******************************************************************************
 * Function Name : CAN_Handler_Disable_Interrupts                              *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by application to disable       *
 *          CAN Interrupts on all selected  CAN channels                       *
 ******************************************************************************/
void CAN_Handler_Disable_Interrupts(void)
{
  #ifdef CAN_INTERRUPT_MODE
    #ifdef CAN_CH0_SELECTED
    CD_Disable_All_Interrupts(0);
    #endif
    #ifdef CAN_CH1_SELECTED
    CD_Disable_All_Interrupts(1);
    #endif
    #ifdef CAN_CH2_SELECTED
    CD_Disable_All_Interrupts(2);
    #endif
  #endif
}

/*******************************************************************************
 * Function Name : CAN_Handler_Enable_Interrupts                               *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by application to enable        *
 *          CAN Interrupts on all selected  CAN channels                       *
 ******************************************************************************/
void CAN_Handler_Enable_Interrupts(void)
{
  #ifdef CAN_INTERRUPT_MODE
    #ifdef CAN_CH0_SELECTED
    CD_Enable_All_Interrupts(0);
    #endif
    #ifdef CAN_CH1_SELECTED
    CD_Enable_All_Interrupts(1);
    #endif
    #ifdef CAN_CH2_SELECTED
    CD_Enable_All_Interrupts(2);
    #endif
  #endif
}

#ifdef HASH_SEARCH
/*********************************************************************
* Function Name : CAN_Hash_Search                                    *
* Arguments passed : channel number, receive message ID              *
* Return value : message handle                                      *
* Functionality : This function uses the Hash search algorithm to    *
* find the message no for the receive message ID passed. ID_NOT_FOUND*
* will be returned if ID is not found in the Receive Parameter Table.*
*********************************************************************/
canuint8_t CAN_Hash_Search(canuint8_t channel_num, Msg_ID_T ID_passed)
{
   canuint8_t index,id_valid;
   Msg_ID_T id;
   const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

   id_valid = ID_NOT_FOUND;
   index = 0xFF;

   id =  ID_passed;
   id &= Hash_Config_Table[channel_num].Hash_Mask;
   id >>= (Hash_Config_Table[channel_num].Hash_Start_Bit -
          (Hash_Config_Table[channel_num].Hash_Length - 1));
   if(Size_Of_Hash_Tables[channel_num] > id)
   {
      index = Hash_Tables[channel_num][id];
      Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables[channel_num]
                                       [index];
      if(Pointer_to_Rx_Parameter_Struct->message_ID == ID_passed)
      {
          id_valid = index;
      }
   }
return(id_valid);
}
#endif

#ifdef BINARY_SEARCH
/*********************************************************************
* Function Name : CAN_Binary_Search                                  *
* Arguments passed : channel number, receive message ID              *
* Return value : Receive message number                              *
* Functionality : This function uses a Binary search algorithm to    *
* find themessage number for the receive message ID passed. NOT_FOUND*
* will be returned if ID is not found in the Receive Parameter Table.*
*********************************************************************/
canuint8_t CAN_Binary_Search(canuint8_t channel_num, Msg_ID_T ID_passed,
                           canuint8_t Tx_or_Rx)
{
   canuint8_t low = 0;
   canuint8_t mid, high;
   Msg_ID_T temp_ID;

   const VBM_Receive_Msg_Parameter_T * Pointer_to_Rx_Parameter_Struct;

   if(HWCAN_TRANSMIT == Tx_or_Rx)
   {
      if(channel_num == 0)
      {
         low = 0;
         high = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;
      }
      else if(channel_num == 1)
      {
         low = NUMBER_OF_TX_MSG_SUPPORTED_CH0;
         high = low + NUMBER_OF_TX_MSG_SUPPORTED_CH1 -1;
      }
      else if(channel_num == 2)
      {
         low = NUMBER_OF_TX_MSG_SUPPORTED_CH0 + NUMBER_OF_TX_MSG_SUPPORTED_CH1;
         high = low + NUMBER_OF_TX_MSG_SUPPORTED_CH2 - 1;
      }
      else
      {
       /* if none of the channels are selected consider channel-0 */
         low = 0;
         high = NUMBER_OF_TX_MSG_SUPPORTED_CH0 - 1;
      }
   }
   else //search in Receive Parameter Table
   {
     high = Size_Of_Receive_Param_Tables[channel_num] - 1;
   }
   while(low <= high)
   {
      mid = (low + high)/2;
      if(HWCAN_TRANSMIT == Tx_or_Rx)
      {
         temp_ID = VBM_Tx_Msg_Parameter_Table[mid].message_ID;
      }
      else
      {
        Pointer_to_Rx_Parameter_Struct = &VBM_Rx_Msg_Parameter_Tables
                                        [channel_num][mid];
        temp_ID = Pointer_to_Rx_Parameter_Struct->message_ID;
      }

      if(temp_ID < ID_passed)
      {
         low = mid+1;
      }
      else
      {
         if (temp_ID > ID_passed)
         {
            if(mid>0)
            {
              high = mid-1;
            }
            else
            {
              return (ID_NOT_FOUND);
            }
         }
         else
         {
            return (mid);
         }
      }
   }
   return (ID_NOT_FOUND);
}
#endif


void CAN_Handler_Recovery_If_Bus_Off(canuint8_t channel_num)
{
     if( CD_Get_Buss_Off_Status_Channel0() == cbTRUE)
     {
           CAN_Handler_Warm_Init(0);
           CD_Set_Buss_Off_Status_Channel0(cbFALSE);
     }
}
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
