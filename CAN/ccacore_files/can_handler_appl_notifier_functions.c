/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - CAN Handler Application Notifier functions                 *
 * File Name:  can_handler_appl_notifier_functions.c                         *
 * Description: This file contains dummy definitions for appl notifer        *
 *              functions                                                    *
 *****************************************************************************/
#include "can_handler_appl_notifier_functions.h"
#include "can_handler_datatypes.h"
#include "can_vbm_tx.h"
#include "can_vbm_rx.h"
#include "can_aif_config.h"
#include "can_aif_rx.h"
#include "CCA.h"


extern void ApplCanMsgTransmitConf_BEV( void);

static volatile uint8_t aif_data[8]={0,0,0,0,0,0,0,0};

volatile canuint8_t confirmation_flag = TRUE;
canuint16_t CanSrv27_10s_Timer;
canuint16_t Tester_Present_Timer;
volatile canbool8_t Tx_Passive_Err_Detected = false;
canbool8_t CAN_Init_Failed_V=FALSE;

void ApplCanMsgTransmitConf( void)
{
   confirmation_flag = TRUE;
}

void Appl_Poll_Tx_Msgs_Per_Loop_Overrun(void){}

void Appl_CAN_Handler_Channel_Not_Initialized(uint8_t channel_num)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_num;
   CAN_Init_Failed_V=TRUE;
}

void Appl_Notify_Error_Warning_State(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
}

void Appl_Notify_Error_Passive_State(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
   Boolean_Returnvalue_T in_err_passive;

   if(channel_number==0)
   {
      if( afcan_control_registers[channel_number]->LEC==0x03)
      {
      Tx_Passive_Err_Detected=true;
     }
   }
}

void Appl_Notify_Busoff_Error_State(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
}

void Appl_Hardware_Rx_Buffer_Overrun(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
}

void Appl_CAN_Controller_Has_Wokenup(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
}



/*********************************************************************
* Function Name : Appl_CAN_TX_Notifier                                  *
* Arguments passed : Tx message ID              *
* Return value :                               *
* Functionality : This function provided a TX Notifier to Application. *
* FAW SCRs : 11454
*********************************************************************/
void Appl_CAN_TX_Notifier(canuint8_t msg_handle)
{
/*
   if(1 == msg_handle)
   {
      if(Open_ACC_On_Request )
      { 
         Open_ACC_On_Request = false;
      }
      else if(Open_ACC_Off_Request)
      {
         Open_ACC_Off_Request = false;
      }
   }
*/
   
   if(Received_IPC_Data == 1)
   {
	   Received_IPC_Data = 2;
   }

}

/*********************************************************************
* Function Name : Appl_CAN_RX_Notifier                                  *
* Arguments passed : receive message ID              *
* Return value :                              *
* Functionality : This function provided a RX Notifier to Application.*
*********************************************************************/
void Appl_CAN_RX_Notifier(canuint8_t msg_handle)
{

}


void Appl_Process_CAN_RxMessages()
{
    /*Message HUT1*/
    if(AIF_Get_Rx_Msg_Ind_Ch0(1))
    {

    }
}

void NM_CAN_Controller_Has_Wokenup(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
	uint8_t DUMMY_CHANNEL_NUMBER;
	DUMMY_CHANNEL_NUMBER = channel_number;
	//Appl_Set_NM_Comm_Normal_Status();
	//Appl_Set_CAN_Wakeup_Status();
	//Timer_250ms = 0;
}

bool8_t NM_Is_Initial_Busoff_Indication_Flag_Set(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
   return(0);
}

void NM_Recovered_From_Busoff(uint8_t channel_number)
{
/* to suppress compiler warning channel_num not used */
   uint8_t DUMMY_CHANNEL_NUMBER;
   DUMMY_CHANNEL_NUMBER = channel_number;
}

void Appl_Notify_Invalid_Timer(uint8_t CAN_Timer_Name)
{
/* to suppress compiler warning CAN_Timer_Name not used */
   uint8_t DUMMY_TIMER_NAME;
   DUMMY_TIMER_NAME = CAN_Timer_Name;
}

void Appl_Notify_Invalid_Timer_Value(uint8_t CAN_Timer_Name)
{
/* to suppress compiler warning CAN_Timer_Name not used */
   uint8_t DUMMY_TIMER_NAME;
   DUMMY_TIMER_NAME = CAN_Timer_Name;
}



void Appl_Stop_Tester_Present_Timer()
{
   Tester_Present_Timer = 0;
}

void Appl_Service_Tester_Present_Timer()
{

}

void Appl_Start_Security_Access_Delay_Timer()
{
}


void App_Change_Session_To_Default(void)
{
}

void App_USData_Confirm(canuint8_t trans_result)
{
}

canbool8_t App_Is_It_Unsolicited_Response(void)
{
        return (0 );
}
void App_Clear_Unsolicited_Response_Flag(void)
{
}

void App_TP_Buffer_Empty(void)
{
}

canbool8_t App_Is_Change_of_Session_Requested(void)
{
   return(1);

}
/******************************************************************************
 *         DUMMY CALL BACK FUNCTIONS- AIF and APPLICATION                     *
******************************************************************************/
void Appl_Invalid_Msg_Type_Request(void){}


/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
* Changes for ESR Host FAW
*
* Date     By    Description
* -------- ---   -----------
* 04/6/2010 kpa SCR#11454 for release esr_host_faw/0.X
*                Added call to application funtion in Tx Confirmation callback.
 ******************************************************************************/
