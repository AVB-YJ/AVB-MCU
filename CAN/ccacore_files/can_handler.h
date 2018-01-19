/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - CAN Core                                                   *
 * File Name:  can_handler.h                                                 *
 * Description: This file contains prototypes for init and other tasks       *
 *              of  CAN Handler (DCH)                                  *
 *****************************************************************************/
#ifndef CAN_HANDLER_H
#define CAN_HANDLER_H

#include "can_handler_datatypes.h"
#include "can_handler_config.h"
//amit
//#include "can_drv_config.h"
//#include "can_timer_mod.h"


typedef struct Hash_Config_Table_Tag
{
   Msg_ID_T Hash_Mask;
   canuint8_t  Hash_Start_Bit;
   canuint8_t  Hash_Length;
} Hash_Config_Table_T;

extern void CAN_Handler_Cold_Init(canuint8_t channel_num);
extern canbool8_t Is_CAN_Handler_Initialized(canuint8_t channel_num);
extern void CAN_Handler_Warm_Init(canuint8_t channel_num);
extern void CAN_Handler_Periodic_Task(void);
extern void CAN_Handler_Timer_Task(void);
extern void CAN_Handler_Shut_Down(canuint8_t channel_num);
extern void CAN_Handler_Disable_Interrupts(void);
extern void CAN_Handler_Enable_Interrupts(void);
extern Boolean_Returnvalue_T CAN_Handler_Go_To_Sleep(canuint8_t channel_num);


extern canuint8_t CAN_Binary_Search(canuint8_t channel_num, Msg_ID_T ID_passed,
                           canuint8_t Tx_or_Rx);
extern canuint8_t CAN_Hash_Search(canuint8_t channel_num, Msg_ID_T ID_passed);

#ifdef HASH_SEARCH
  #ifdef CAN_CH0_HASH_SEARCH
  extern const canuint8_t Hash_Table_Ch0[];
  #endif
  #ifdef CAN_CH1_HASH_SEARCH
  extern const canuint8_t Hash_Table_Ch1[];
  #endif
  #ifdef CAN_CH2_HASH_SEARCH
  extern const canuint8_t Hash_Table_Ch2[];
  #endif
#endif

extern const canuint8_t Size_Of_Hash_Tables[];
extern const Hash_Config_Table_T Hash_Config_Table[];

//#ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
extern void CAN_Handler_Disable_Global_Interrupts(void);
extern void CAN_Handler_Enable_Global_Interrupts(void);
//#endif
extern void CAN_Handler_Recovery_If_Bus_Off(canuint8_t channel_num);
#ifdef CCA_HMI
extern void NM_CAN_Driver_Init(canuint8_t channel_num);
extern void NM_CAN_Driver_BusOff_Init(canuint8_t channel_num);
extern void NM_CAN_Driver_Wakeup_Init(canuint8_t channel_num);
#endif
extern Boolean_Returnvalue_T CAN_Handler_Cancel_Sleep(canuint8_t channel_num);

#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
