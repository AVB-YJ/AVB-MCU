/************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved        *
 * REVISION: 1.0                                                        *
 * AUTHORS: Prakash, Sandeep                                            *
 * Project: CCA - HWCAN                                                 *
 * File Name:  hwcan_nec_v850_config.h                                  *
 * File Description:                                                    *
 * This file contains macro's and configuration items for HWCAN layer   *
 * Micro Description:                                                   *
 * The HWCAN layer is written for uPD70Fxxxx which belongs to           *
 * the NEC-V850ES/Fx3 series. This code can support three channels      *
 ************************************************************************/

#ifndef HWCAN_NEC_V850_CONFIG_H
#define HWCAN_NEC_V850_CONFIG_H


#include "can_handler_config.h"
#include "can_handler_appl_notifier_functions.h"

/*===========================================================================*/
/*   Preprocessor #define constants (object-like macros)                     */
/*===========================================================================*/

/* Define this macro if mask buffers are used for reception */
#undef HWCAN_MASK_USED
#define AFCAN_MESSAGE_BUFFERS      16
#define AFCAN_MASK_REGISTERS       4
#define AFCAN_NUMBER_OF_CHANNELS   1


/* Macros for base address of CAN module control register */

#define AFCAN_CHANNEL0_CONTROL_REGISTERS_BASE_ADD   0x000F05C0// 0x03FEC000

/* Macros for base address of Interrupt control register */

#define AFCAN_CHANNEL0_INTERRUPT_PRIORITY_CONTROL_REGISTER_ADD  0xfffff158
#define AFCAN_CHANNEL0_INTERRUPT_MASK_FALG_REGISTER_ADD         0xfffff158
#define AFCAN_CHANNEL0_INTERRUPT_REQUEST_FALG_REGISTER_ADD      0xfffff158

#define AFCAN_ERROR_INTERRUPT_CONTROL_REGISTER_OFFSET      0x0
#define AFCAN_WAKEUP_INTERRUPT_CONTROL_REGISTER_OFFSET     0x2
#define AFCAN_RX_INTERRUPT_CONTROL_REGISTER_OFFSET         0x4
#define AFCAN_TX_INTERRUPT_CONTROL_REGISTER_OFFSET         0x6

#ifdef HWCAN_MASK_USED
/* Macro for offset of the CAN module mask registers */
#define AFCAN_MASK_REGISTERS_OFFSET                                                                                             0x10
#endif

/* Macros for offset of the CAN module message buffers */
#define AFCAN_MESSAGE_BUFF_REGISTERS_BASE_ADD                          0x000F0600   
#define AFCAN_MESSAGE_BUFF_REGISTERS_OFFSET                                                                                0x100


#define AFCAN_CH0_INTERRUPT_REQUEST_FLAG_REGISTER_LOW             (uint32_t)(0x000FFFD0)
#define AFCAN_CH0_INTERRUPT_REQUEST_FLAG_REGISTER_HIGH            (uint32_t)(0x000FFFD1)
#define AFCAN_CH0_INTERRUPT_PRIORITY_0_SELECTION_REGISTER_LOW     (uint32_t)(0x000FFFD8)
#define AFCAN_CH0_INTERRUPT_PRIORITY_0_SELECTION_REGISTER_HIGH    (uint32_t)(0x000FFFD9)
#define AFCAN_CH0_INTERRUPT_PRIORITY_1_SELECTION_REGISTER_LOW     (uint32_t)(0x000FFFDC)
#define AFCAN_CH0_INTERRUPT_PRIORITY_1_SELECTION_REGISTER_HIGH    (uint32_t)(0x000FFFDD)
#define AFCAN_CH0_INTERRUPT_MASK_FLAG_REGISTER_LOW                (uint32_t)(0x000FFFD4)
#define AFCAN_CH0_INTERRUPT_MASK_FLAG_REGISTER_HIGH               (uint32_t)(0x000FFFD5)


/**************************** Macor's for baud rate settings *****************************/

/* Configure baud rate to 500kbps(I/P frequency to the CAN contoller is 16MHz )*/
/* Clock to the CAN module is (CPU_clock)/2 */
//#define AFCAN_SELECT_CAN_MODULE_SYSTEM_CLOCK 0x00  //If I/P frequency to the CAN contoller is 4MHz
#define AFCAN_SELECT_CAN_MODULE_SYSTEM_CLOCK                                                                    0x00 //If I/P frequency to the CAN contoller is 16MHz

/* Frequency in Hz */
//#define MAX_CPU_FREQUENCY  4000000
#define MAX_CPU_FREQUENCY   24000000

#define AFCAN_INITTIMEOUT                                                 (MAX_CPU_FREQUENCY/64)


#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file for      *
 *                 Sandeep       NEC v850 Fx3                                  *
 ******************************************************************************/
