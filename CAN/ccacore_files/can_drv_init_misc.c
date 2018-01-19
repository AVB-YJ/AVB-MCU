/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - Driver                                                     *
 * File Name:  can_drv_init_misc.c                                           *
 * File Description:                                                         *
 * This file contains routines for initializing the on-chip CAN controller,  *
 * error handling, sleep-wakeup handling and interrupt control.              *
 *****************************************************************************/

/*******************************************************************************
* Header File Inclusions                                                       *
*******************************************************************************/

#include "can_drv_init_misc.h"
#include "can_drv_config.h"
#include "can_drv_tx_rx.h"
#include "can_vbm_tx.h"
#include "can_handler_config.h"
#include "can_handler_appl_notifier_functions.h"

#include "hwcan_tx_rx_nec_v850.h"

#include "ivn_faw_nm.h"

Boolean_Returnvalue_T Buss_Off_Channel0 = cbFALSE;
canuint8_t Buss_Off_Channel0_Count = 0;

/*******************************************************************************
*                            STATIC FUNCTION DECLARATIONS                      *
*******************************************************************************/
 void Set_Configuration(canuint8_t channel_number);
 void Enable_Configured_CAN_Interrupts(canuint8_t channel_number);

/*******************************************************************************
*                       START OF INITIALIZATION                                *
 ******************************************************************************/

/*******************************************************************************
 * Function Name : Set_Configuration                                           *
 * Function Parameters : channel number, 0 - (N-1)                             *
                  N - Number of maximum channels present in the CAN controller *
 * Return Value : None                                                         *
 * Description : This function would be called by CD_Cold_Initialization()     *
 *               This function would be called for initializing all the        *
 *               control registers including bit timing registers to the       *
 *               respective designed values.                                   *
*******************************************************************************/
 void Set_Configuration(canuint8_t channel_number)
{
   HWCAN_Init_All_Reg(channel_number);

   //HWCAN_Init_For_Additional_features(channel_number);

   HWCAN_Load_Bit_Timing_Parameters(channel_number, HWCAN_NORMAL_SPEED);

}

/*******************************************************************************
 * Function Name  Enable_Configured_CAN_Interrupts                            *
 * Function Parameters : channel number, 0 - (N-1)                             *
                  N - Number of maximum channels present in the CAN controller *
 * Return Value : None                                                         *
 * Description : This function would be called during cold initialization for  *
 *               enabling the required CAN interrupts.                         *
 ******************************************************************************/
 void Enable_Configured_CAN_Interrupts(canuint8_t channel_number)
{
   #ifdef CAN_INTERRUPT_MODE
      #ifdef CAN_INTERRUPTS_SEPARATE_ENABLING
         #ifdef TRANSMIT_INTERRUPT_MODE
         HWCAN_Enable_CAN_Interrupt(channel_number,HWCAN_TRANSMIT); 
         #endif

         #ifdef RECEIVE_INTERRUPT_MODE
         HWCAN_Enable_CAN_Interrupt(channel_number,HWCAN_RECEIVE); 
         #endif

         #ifdef ERROR_INTERRUPT_MODE
         HWCAN_Enable_CAN_Interrupt(channel_number,HWCAN_ERROR); 
         #endif

         #ifdef WAKEUP_INTERRUPT_MODE
         HWCAN_Enable_CAN_Interrupt(channel_number,HWCAN_WAKEUP); 
         #endif
      #else
         HWCAN_Enable_All_CAN_Interrupts(channel_number);
      #endif
   #endif
}

/*******************************************************************************
 * Macro Name : Configure_TxRx_Message_Objects                                 *
 * Macro Parameters : channel number, 0 - (N-1)                                *
                  N - Number of maximum channels present in the CAN controller *
 * Description : This function would be called during cold initialization for  *
 *               configuring and initializing transmit and receive buffers     *
 *               according to the message requirements.                        *
 ******************************************************************************/
#define Configure_TxRx_Message_Objects(channel_number) \
        HWCAN_Configure_Message_Objects_For_Tx_Rx(channel_number)


/*******************************************************************************
 * Function Name : CD_Cold_Initialization                                      *
 * Function Parameters : channel number, 0 - (N-1)                             *
                  N - Number of maximum channels present in the CAN controller *
 * Return Value : cbFALSE - CAN controller is not synchronized to the network  *
 *                cbTRUE - CAN controller is synchronized to the network       *
 * Description : This function would be called by application during power ON  *
 *               reset for initializing and preparing the CAN controller for   *
 *               communication on to the bus.                                  *
 * Assumption: This function is expected to be called only after configuring   *
 * ports for CAN, configuring the transceiver in normal operating mode.        *
*******************************************************************************/
Boolean_Returnvalue_T CD_Cold_Initialization(canuint8_t channel_number)
{
   Boolean_Returnvalue_T can_controller_sync_flag;

   CD_Clear_Transmit_Status(channel_number);
   CD_Clear_Receive_Status(channel_number);
   HWCAN_Disable_All_CAN_Interrupts(channel_number);

   HWCAN_Change_Mode(channel_number,HWCAN_INITIALIZATION_MODE);

   Set_Configuration(channel_number);

   Configure_TxRx_Message_Objects(channel_number);

   HWCAN_Change_Mode(channel_number,HWCAN_NORMAL_OPERATING_MODE);

      can_controller_sync_flag = HWCAN_Is_CAN_Controller_Synchronized(channel_number);

   if(can_controller_sync_flag)
   {
      HWCAN_Enable_All_CAN_Interrupt_At_Init(channel_number);
   }

   return(can_controller_sync_flag);
}

Boolean_Returnvalue_T CD_BusOff_Initialization(canuint8_t channel_number)
{
   Boolean_Returnvalue_T can_controller_sync_flag;

   CD_Clear_Transmit_Status(channel_number);
   CD_Clear_Receive_Status(channel_number);

   HWCAN_Disable_All_CAN_Interrupts(channel_number);

   HWCAN_Change_Mode(channel_number,HWCAN_INITIALIZATION_MODE);
   
   HWCAN_Change_Mode(channel_number,HWCAN_NORMAL_OPERATING_MODE);

   can_controller_sync_flag = HWCAN_Is_CAN_Controller_Synchronized
                              (channel_number);

   if(can_controller_sync_flag)
   {
      HWCAN_Enable_All_CAN_Interrupt_At_Init(channel_number);
   }

   return(can_controller_sync_flag);
}
Boolean_Returnvalue_T CD_Wakeup_Initialization(canuint8_t channel_number)
{
   Boolean_Returnvalue_T can_controller_sync_flag;

   HWCAN_Disable_All_CAN_Interrupts(channel_number);

//   HWCAN_Change_Mode(channel_number,HWCAN_NORMAL_OPERATING_MODE);

   can_controller_sync_flag = HWCAN_Is_CAN_Controller_Synchronized
                              (channel_number);

   if(can_controller_sync_flag)
   {
      HWCAN_Enable_All_CAN_Interrupt_At_Init(channel_number);
   }

   return(can_controller_sync_flag);
}

/*******************************************************************************
*                       END OF INITIALIZATION                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name : CD_Error_ISR                                                *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description : This function shall be called by CD_Error_ISR_Channel_n()     *
 * function, which is the interrupt service routine for CAN error interrupt    *
 * for channel 'n'. This function can also be called by the user application   *
 * when the application wants to poll for error information.                   *
 ******************************************************************************/
 #define ERROR_PASSIVE_INDICATION_AVAILABLE
void CD_Error_ISR(canuint8_t channel_number)
{
   if(cbTRUE == HWCAN_Is_Bus_Off(channel_number))
   {
      Buss_Off_Channel0 = cbTRUE;
      Tx_Passive_Err_Detected=false;
      Appl_Notify_Busoff_Error_State(channel_number);
      #ifdef CAN_HANDLER_NM_LAYER_SUPPORTED
	  NM_Bus_Off_Indication();
      //HWCAN_Change_Mode(channel_number,HWCAN_NORMAL_OPERATING_MODE);
      #endif
   }
   #ifdef ERROR_PASSIVE_INDICATION_AVAILABLE
   else if(cbTRUE == HWCAN_Is_Err_Passive(channel_number))
   {
            Tx_Passive_Err_Detected=false;
      Appl_Notify_Error_Passive_State(channel_number);
   }
   #endif
   #ifdef ERROR_WARNING_INDICATION_AVAILABLE
   else if(cbTRUE == HWCAN_Is_Err_Warning(channel_number))
   {
         Tx_Passive_Err_Detected=false;
      Appl_Notify_Error_Warning_State(channel_number);
   }
   #endif
   else
   {
         
   }
   HWCAN_Clear_Err_IntPnd_Flag_On_Interrupt(channel_number);

}

#ifdef ERROR_INTERRUPT_MODE
#ifdef CAN_CH0_SELECTED
/*******************************************************************************
 * Function Name : CD_Error_ISR_Channel_0                                      *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the interrupt service routine for CAN error  *
 * interrupt for channel '0'.                                                  *
 ******************************************************************************/
//sg #pragma interrupt INTC0ERR CD_Error_ISR_Channel_0
/*CAN_INTERRUPT_ERROR_0*/ void CD_Error_ISR_Channel_0(void)
{
    CD_Error_ISR(0);
}
#endif
#ifdef CAN_CH1_SELECTED
/*******************************************************************************
 * Function Name : CD_Error_ISR_Channel_1                                      *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the interrupt service routine for CAN error  *
 * interrupt for channel '1'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_ERROR_1 void CD_Error_ISR_Channel_1(void)
{
    CD_Error_ISR(1);
}
#endif
#ifdef CAN_CH2_SELECTED
/*******************************************************************************
 * Function Name : CD_Error_ISR_Channel_2                                      *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the interrupt service routine for CAN error  *
 * interrupt for channel '2'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_ERROR_2 void CD_Error_ISR_Channel_2(void)
{
    CD_Error_ISR(2);
}

#endif

#endif

#ifndef ERROR_INTERRUPT_MODE
/*******************************************************************************
 * Function Name : CD_Poll_Error                                               *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the poll service routine for CAN error       *
 ******************************************************************************/
void CD_Poll_Error(canuint8_t channel_number)
{
    CD_Error_ISR(channel_number);
}
#endif


#ifdef CAN_WAKEUP_MODE_AVAILABLE
/*******************************************************************************
 * Function Name : CD_Wakeup_ISR                                               *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description : This function shall be called by CD_Wakeup_ISR_Channel_n()    *
 * function, which is the interrupt service routine for CAN wakeup interrupt   *
 * for channel 'n'.                                                            *
 ******************************************************************************/
void CD_Wakeup_ISR(canuint8_t channel_number)
{
   HWCAN_Clear_Wakeup_IntPnd_Flag_On_Interrupt(channel_number);

   #ifdef CAN_HANDLER_NM_LAYER_SUPPORTED

   NM_CAN_Controller_Has_Wokenup(channel_number);

   #endif

   Appl_CAN_Controller_Has_Wokenup(channel_number);
}
#endif

#ifdef WAKEUP_INTERRUPT_MODE
#ifdef CAN_CH0_SELECTED
/*******************************************************************************
 * Function Name : CD_Wakeup_ISR_Channel_0                                     *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the interrupt service routine for CAN error  *
 * interrupt for channel '0'.                                                  *
 ******************************************************************************/
//sg #pragma interrupt INTC0WUP CD_Wakeup_ISR_Channel_0
CAN_INTERRUPT_WAKEUP_0 void CD_Wakeup_ISR_Channel_0(void)
{
    CD_Wakeup_ISR(0);
}
#endif
#ifdef CAN_CH1_SELECTED
/*******************************************************************************
 * Function Name : CD_Wakeup_ISR_Channel_1                                     *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the interrupt service routine for CAN error  *
 * interrupt for channel '1'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_WAKEUP_1 void CD_Wakeup_ISR_Channel_1(void)
{
    CD_Wakeup_ISR(1);
}
#endif
#ifdef CAN_CH2_SELECTED
/*******************************************************************************
 * Function Name : CD_Wakeup_ISR_Channel_2                                     *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the interrupt service routine for CAN error  *
 * interrupt for channel '2'.                                                  *
 ******************************************************************************/
CAN_INTERRUPT_WAKEUP_2 void CD_Wakeup_ISR_Channel_2(void)
{
    CD_Wakeup_ISR(2);
}
#endif

#endif

#ifdef CAN_WAKEUP_MODE_AVAILABLE
#ifndef WAKEUP_INTERRUPT_MODE
/*******************************************************************************
 * Function Name : CD_Poll_Wakeup                                              *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function is the poll service routine for CAN wakeup      *
 ******************************************************************************/
void CD_Poll_Wakeup(canuint8_t channel_number)
{
    CD_Wakeup_ISR(channel_number);
}
#endif
#endif


#ifdef CAN_SLEEP_MODE_AVAILABLE
/*******************************************************************************
 * Function Name : CD_Go_To_Sleep                                              *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : SLEEP_OK - CAN controller is put to sleep                    *
 *                SLEEP_NOT_OK - CAN controller is not put to sleep            *
 *                SLEEP_INVALID_REQUEST - CAN controller does not support      *
 *                                        sleep                                *
 *                                    state                                    *
 * Description:This function would put the CAN controller in sleep state after *
 * making sure that neither message transmission nor message reception is in   *
 * in progress. In addition this function also verifies that no message is     *
 * waiting for transmission in virtual buffers                                 *
 ******************************************************************************/
Sleep_Result_T CD_Go_To_Sleep(canuint8_t channel_number)
{
   Sleep_Result_T ok_to_sleep;

   canbool8_t one_tx_msg_is_pending;
   
  // ok_to_sleep = SLEEP_NOT_OK;
 
   one_tx_msg_is_pending = CAN_cbFALSE;
    
   #ifdef CHECK_PENDING_Tx_MSGS_FOR_SLEEP_STATE
   
   one_tx_msg_is_pending = VBM_Is_Any_Message_Pending(channel_number);
   
   #endif
   
   if(  ( CAN_cbFALSE ==one_tx_msg_is_pending  ) && 
        ( SLEEP_OK == HWCAN_Is_OK_To_Sleep(channel_number) )  )
   {
      ok_to_sleep = SLEEP_OK;       
      HWCAN_Go_To_Sleep(channel_number);
      HWCAN_Disable_CAN_Tx_Rx_Interrupts(channel_number);
   }
  /* if(SLEEP_INVALID_REQUEST == HWCAN_Is_OK_To_Sleep(channel_number) )
   {
      ok_to_sleep = SLEEP_INVALID_REQUEST;
   }*/
   else
   {
      ok_to_sleep = SLEEP_NOT_OK;
   }
   
   return(ok_to_sleep);
}

/*******************************************************************************
 * Function Name : CD_Cancel_Sleep_State                                       *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : cbTRUE - CAN controller's sleep state is cancelled           *
 *                cbFALSE - CAN controller's sleep state is not cancelled      *
 *                b_INVALID_REQUEST - CAN controller does not support sleep    *
 *                                    state                                    *
 * Description:This function would cancel the prevailing sleep state of the    *
 * CAN controller, if sleep state is supported by the CAN controller.          *
 ******************************************************************************/
Sleep_Result_T CD_Cancel_Sleep_State(canuint8_t channel_number)
{
   Sleep_Result_T ok_to_cancel_sleep_state;

   ok_to_cancel_sleep_state = HWCAN_Clear_Sleep_State(channel_number);

   return(ok_to_cancel_sleep_state);
}
#endif

/*******************************************************************************
 * Function Name : CD_Enable_All_Interrupts                                    *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description:This function would enable all the configured CAN interrupts    *
 ******************************************************************************/
void CD_Enable_All_Interrupts(canuint8_t channel_number)
{
  // Enable_Configured_CAN_Interrupts(channel_number);
   HWCAN_Enable_All_CAN_Interrupts(channel_number);
}

/*******************************************************************************
 * Function Name : CD_Disable_All_Interrupts                                   *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description:This function would disable all the CAN related interrupts      *
 ******************************************************************************/
void CD_Disable_All_Interrupts(canuint8_t channel_number)
{
   HWCAN_Disable_All_CAN_Interrupts(channel_number);
}

#ifdef CAN_INTERRUPTS_SEPARATE_ENABLING
/*******************************************************************************
 * Function Name : CD_Enable_Interrupt                                         *
 * Function Parameters : channel number, CAN_Int_Type                          *
 * Return Value : None                                                         *
 * Description:This function would enable the requested CAN interrupt          *
 ******************************************************************************/
void CD_Enable_Interrupt(canuint8_t channel_num, canuint8_t CAN_Int_Type)
{
   HWCAN_Enable_CAN_Interrupt(channel_num, CAN_Int_Type);
}

/*******************************************************************************
 * Function Name : CD_Disable_Interrupt                                        *
 * Function Parameters : channel number, CAN_Int_Type                          *
 * Return Value : None                                                         *
 * Description:This function would disable the requested CAN interrupt         *
 ******************************************************************************/
void CD_Disable_Interrupt(canuint8_t channel_num, canuint8_t CAN_Int_Type)
{
   HWCAN_Disable_CAN_Interrupt(channel_num, CAN_Int_Type);
}
#endif

/*******************************************************************************
 * Function Name : CD_Shut_Communication_Down                                  *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description:This function will put the CAN controller in initialization     *
 * mode that takes the CAN controller to non-operating mode.                   *
 ******************************************************************************/
void CD_Shut_Communication_Down(canuint8_t channel_number)
{
   HWCAN_Change_Mode(channel_number,HWCAN_INITIALIZATION_MODE);
}

/*******************************************************************************
 * Function Name : CD_Warm_Initialization                                      *
 * Function Parameters : channel number, 0 - (N-1)                             *
 *               N - Number of maximum channels present in the CAN controller  *
 * Return Value : None                                                         *
 * Description:This function would be called by warm initialization routine    *
 * of DCH while after coming out of sleep state.                               *
 ******************************************************************************/
void CD_Warm_Initialization(canuint8_t channel_number)
{


    CD_Cold_Initialization(channel_number);
}

/*******************************************************************************
 * Function Name : CD_Init_Misc                                                *
 * Function Parameters : None                                                  *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN handler to initialize    *
 *          the H/W features which are not channel dependent                   *
 ******************************************************************************/
void CD_Init_Misc(void)
{
   HWCAN_Init_Misc();

}

Boolean_Returnvalue_T CD_Get_Buss_Off_Status_Channel0(void)
{
     return Buss_Off_Channel0;
 }

void CD_Set_Buss_Off_Status_Channel0(Boolean_Returnvalue_T  bus_off_value)
{
    Buss_Off_Channel0 = bus_off_value;

}

void CD_Increment_Buss_Off_Channel0_Count()
{
    Buss_Off_Channel0_Count++;

}
  
void CD_Reset_Buss_Off_Channel0_Count(void)
{
    Buss_Off_Channel0_Count = 0;
}

canuint8_t CD_Get_Buss_Off_Channel0_Count(void)
{
     return Buss_Off_Channel0_Count;
 }


/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
