/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - CAN Handler Application Notifier functions                 *
 * File Name:  can_handler_appl_notifier_functions.h                         *
 * Description: This file contains prototypes for appl notifer functions     *
 *****************************************************************************/

#ifndef CAN_HANDLER_APPL_NOTIFIER_FUNCTIONS_H
#define CAN_HANDLER_APPL_NOTIFIER_FUNCTIONS_H

#undef CAN_TEST_TASK

#include "can_handler_datatypes.h"
//#include "Diagcan_config.h"

#define CAN_SRV27_10MS_TIME_OUT                                      10000
#define CAN_SRV27_CALL_RATE                                          10

#define APPL_ENABLE_RX_AND_TX							0x00
#define APPL_ENABLE_RX_AND_DISABLE_TX					0x01
#define APPL_DISABLE_RX_AND_ENABLE_TX					0x02
#define APPL_DISABLE_RX_AND_TX							0x03
#define APPL_NORMAL_COMMUNICATION_MSG					0x01
#define APPL_NM_COMMUNICATION_MSG						0x02
#define APPL_NORMAL_AND_NM_COMMUNICATION_MSG			0x03

extern volatile canuint8_t confirmation_flag;

extern canuint16_t CanSrv27_10s_Timer;
extern canbool8_t CAN_Init_Failed_V;

extern void Appl_Poll_Tx_Msgs_Per_Loop_Overrun(void);
extern void Appl_CAN_Handler_Channel_Not_Initialized(uint8_t channel_num);
extern void Appl_Notify_Error_Warning_State(uint8_t channel_number);
extern void Appl_Notify_Error_Passive_State(uint8_t channel_number);
extern void Appl_Notify_Busoff_Error_State(uint8_t channel_number);
extern void Appl_Hardware_Rx_Buffer_Overrun(uint8_t channel_number);
extern void Appl_CAN_Controller_Has_Wokenup(uint8_t channel_number);
extern void Appl_Notify_Invalid_Timer(uint8_t CAN_Timer_Name);
extern void Appl_Notify_Invalid_Timer_Value(uint8_t CAN_Timer_Name);

extern void NM_CAN_Controller_Has_Wokenup(uint8_t channel_number);
extern bool8_t NM_Is_Initial_Busoff_Indication_Flag_Set(uint8_t channel_number);
extern void  NM_Recovered_From_Busoff(uint8_t channel_number);
extern void Appl_Initialize_Diagnostics(void);

/******************************************************************************
 *         DUMMY CALL BACK FUNCTIONS- AIF and APPLICATION                     *
******************************************************************************/
extern void Appl_Invalid_Msg_Type_Request(void);
extern void Appl_CAN_TX_Notifier(canuint8_t msg_handle);
extern void Appl_CAN_RX_Notifier(canuint8_t msg_handle);

extern void Appl_Start_Tester_Present_Timer();
extern void Appl_Start_Security_Access_Delay_Timer();
extern void Appl_Stop_Tester_Present_Timer();
extern void Appl_Service_Tester_Present_Timer();
//extern Diagnostic_Session_T App_Get_Current_Session(void);

extern canbool8_t App_Is_Change_of_Session_Requested(void);
extern volatile canbool8_t Tx_Passive_Err_Detected;
extern canbool8_t Performing_Ack_Recovery; //disable CAN Transmitting during ack recovery
#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
