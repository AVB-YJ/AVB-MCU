/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - HWCAN                                                      *
 * File Name:  hwcan_nec_v850_config.c                                       *
 * File Description:                                                         *
 * This module contains configurable parameters of HWCAN Layer such as       *
 * bit timing register definitions and  message buffer initialization tables *
 * Micro Description:                                                        *
 * The HWCAN layer is written for uPD70Fxxxx which belongs to                *
 * the NEC-V850ES/Fx3 series. This code can support three channels.          *
 *****************************************************************************/

#include "hwcan_nec_v850_config.h"
#include "hwcan_init_misc_nec_v850.h"
#include "hwcan_tx_rx_nec_v850.h"


/*******************************************************************************/
/*                            Local macro defination                           */
/*******************************************************************************/


/*******************************************************************************/
/*                          Global table defination                            */
/*******************************************************************************/

const Bit_Timing_Parameter_Table_T HWCAN_Bit_Timing_Table[] =
{
 /* ch.no  speed_mode          BRP     SJW,      TSEG1,       TSEG2  */

   /* For 500 Kbps at 16 MHz CPU clock */
  /* AFCAN_SELECT_CAN_MODULE_SYSTEM_CLOCK macro should also be set */
  /* number of time quanta's are 16TQ, so the prescalar value is 1*/
  /* SJW = 1TQ */
  /* TSEG1 = 16TQ */
  /* TSEG2 = 3TQ */
  /*85% Sampling point*/

   /* ch.no  speed_mode          BRP     SJW,      TSEG1,       TSEG2  */

   //{ 0,   HWCAN_NORMAL_SPEED,   0x00,   0x3000,   0x000A,      0x0300},  //for 16MHz 500 kbps
   //{ 0,   HWCAN_NORMAL_SPEED,   0x04,   0x3000,   0x000A,      0x0300},	//for 8MHz 125Kbpss
   { 0,   HWCAN_NORMAL_SPEED,   0x01,    0x2000,   0x000B,      0x0200},  //for 8MHz 500 kbps 80% sampling pt
   { 0,   HWCAN_LOW_SPEED_250K, 0x01,   0x3000,   0x000A,      0x0300},  //for 16MHz 250 kbps
   { 0,   HWCAN_HIGH_SPEED_1M,  0x00,   0x3000,   0x0004,      0x0100}  //for 16MHz 1000 kbps
};

const canuint8_t Size_Of_Bit_Timing_Parameter_Table = ( sizeof
                     (HWCAN_Bit_Timing_Table)/sizeof(Bit_Timing_Parameter_Table_T));


const TX_Buffer_Message_Mapping_Table_T HWCAN_Tx_Init_Table[] =
{
   /* channel_number,  tx_message_buffer_num */

    {       0,                0                      }
};

const canuint8_t Size_Of_Tx_Init_Table =  (sizeof(HWCAN_Tx_Init_Table)/
                                        sizeof(TX_Buffer_Message_Mapping_Table_T));

#ifdef CAN_CH0_SELECTED

const RX_Buffer_Message_Mapping_Table_T HWCAN_Rx_Init_Table_Ch0[] =

{
  /* rx_msg_buf_num      mask_no          mask_value      hw_filter ,ID Type     */

   {1,            INVALID_MASK_NO,  0x00000000, 0x288, STANDARD_ID},

   {2,            INVALID_MASK_NO,  0x00000000, 0x2B0, STANDARD_ID},

   {3,            INVALID_MASK_NO,  0x00000000, 0x320, STANDARD_ID},

   {4,            INVALID_MASK_NO,  0x00000000, 0x3E0 , STANDARD_ID},


};
#endif

#ifdef CAN_CH1_SELECTED

const RX_Buffer_Message_Mapping_Table_T HWCAN_Rx_Init_Table_Ch1[] =
{
 {      1,            INVALID_MASK_NO,         0x00000000,      0x5FF      },

};
#endif

#ifdef CAN_CH2_SELECTED

const RX_Buffer_Message_Mapping_Table_T HWCAN_Rx_Init_Table_Ch2[] =
{
1, /* to avoid compilation */
};

#endif

/*******************************************************************************
 NON CONFIGURABLE  TABLE : DO NOT DISTURB
 ******************************************************************************/
const uint8_t Size_Of_HWCAN_Rx_Init_Tables[] =
{
 #ifdef CAN_CH0_SELECTED
 (sizeof(HWCAN_Rx_Init_Table_Ch0)/sizeof(HWCAN_Rx_Init_Table_Ch0[0])),
 #endif
 #ifdef CAN_CH1_SELECTED
 (sizeof(HWCAN_Rx_Init_Table_Ch1)/sizeof(HWCAN_Rx_Init_Table_Ch1[0])),
 #endif
 #ifdef CAN_CH2_SELECTED
 (sizeof(HWCAN_Rx_Init_Table_Ch2)/sizeof(HWCAN_Rx_Init_Table_Ch2[0])),
 #endif
};
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file for      *
 *                 Sandeep       NEC v850 Fx3                                  *
 *                                                                             *
 * 2   31-Mar-10   Sarma,         Added comments for HWCAN_Bit_Timing_Table[]  *
 *                Anupindi                                                     *
 ******************************************************************************/
