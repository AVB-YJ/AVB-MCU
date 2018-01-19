/************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved        *
 * REVISION: 1.0                                                        *
 * AUTHORS: Prakash, Sandeep                                            *
 * Project: CCA - HWCAN                                                 *
 * File Name:  hwcan_init_misc_nec_v850.h                               *
 * File Description:                                                    *
 * This file contains the function prototypes related to Initialization	*
 * Error handling and Power Moding functionalities provided to the 	    *
 * CAN Driver								                            *
 * Micro Description:							                        *
* The HWCAN layer is written for both NEC-V850ES/FG2 and NEC-V850ES/FJ3 *
 * micro. 																*
 *  >>>>> If NEC-V850ES/FG2 micro is used the define "NEC_V850_FG2" 	*
 *		  macro in hwcan_nec_v850_config.h  							*
 *  >>>> If NEC-V850ES/FJ3 is used then undef "NEC_V850_FG2" macro in	*
 *       hwcan_nec_v850_config.h 										*
 *  These two micro differs only in the base address of interrupt 		*
 *  control registers and the number of CAN channels available          *
 ************************************************************************/

#ifndef HWCAN_INIT_MISC_NEC_V850_H
#define HWCAN_INIT_MISC_NEC_V850_H

#include "hwcan_nec_v850_config.h"
//#include "hwcan_tx_rx_nec_v850.h"

/*===========================================================================*/
/*   Local preprocessor #define constants (object-like macros)				 */
/*===========================================================================*/


/*===========================================================================*/
/* 					Type declarations (enum, struct, union, typedef)		 */
/*===========================================================================*/

typedef enum Operating_Mode_Tag
{
  HWCAN_INITIALIZATION_MODE,
  HWCAN_NORMAL_OPERATING_MODE
} Operating_Mode_T;

typedef enum Speed_Mode_Tag
{
  HWCAN_MEDIUM_SPEED_500K,
  	HWCAN_LOW_SPEED_250K,
  	HWCAN_HIGH_SPEED_1M,
  HWCAN_REPROGRAMMING
} Speed_Mode_T;
#define HWCAN_NORMAL_SPEED HWCAN_MEDIUM_SPEED_500K


/*===========================================================================*/
/* 					Type declarations for xxICn register            		 */
/*===========================================================================*/
typedef union
{
   struct xxICn_IntPriL0_Tag
   {
      volatile uint8_t unused : 5;
	  volatile uint8_t errPR0 : 1;
	  volatile uint8_t wupPR0 : 1;
	  volatile uint8_t recPR0 : 1;
   }F;
   volatile uint8_t U8;
}xxICn_IntPriLow_T;

typedef union
{
   struct xxICn_IntPriH0_Tag
   {
      volatile uint8_t unused : 5;
	  volatile uint8_t errPR1 : 1;
	  volatile uint8_t wupPR1 : 1;
	  volatile uint8_t recPR1 : 1;
   }F;
   volatile uint8_t U8;
}xxICn_IntPriHigh_T;

typedef union
{
   struct xxICn_IntTxPriL1_Tag
   {
      volatile uint8_t trxPR0 : 1;
	  volatile uint8_t unused : 7;
   }F;
   volatile uint8_t U8;
}xxICn_IntTxPriLow_T;

typedef union
{
   struct xxICn_IntTxPriH1_Tag
   {
      volatile uint8_t trxPR1 : 1;
	  volatile uint8_t unused : 7;
   }F;
   volatile uint8_t U8;
}xxICn_IntTxPriHigh_T;

typedef union
{
   struct xxICn_IntMask_Tag
   {
      volatile uint8_t unused : 5;
	  volatile uint8_t errMask : 1;
	  volatile uint8_t wupMask : 1;
	  volatile uint8_t recMask : 1;
   }F;
   volatile uint8_t U8;
}xxICn_IntMaskLow_T;

typedef union
{
   struct xxICn_IntMaskT_Tag
   {
      volatile uint8_t trxMask : 1;
	  volatile uint8_t unused : 7;
   }F;
   volatile uint8_t U8;
}xxICn_IntMaskHigh_T;

typedef union
{
   struct xxICn_IntReq_Tag
   {
      volatile uint8_t unused : 5;
	  volatile uint8_t errIntReq : 1;
	  volatile uint8_t wupIntReq : 1;
	  volatile uint8_t recIntReq : 1;
   }F;
   volatile uint8_t U8;
}xxICn_IntReqLow_T;

typedef union
{
   struct xxICn_IntReqT_Tag
   {
      volatile uint8_t trxIntReq : 1;
	  volatile uint8_t unused : 7;
   }F;
   volatile uint8_t U8;
}xxICn_IntReqHigh_T;


/*******************************************************************************
*              EXTERN TABLE DECLARATIONS FOR BIT TIMING                        *
*******************************************************************************/

typedef struct Bit_Timing_Parameter_Table_Tag
{
    uint8_t channel_no;
    Speed_Mode_T speed;
    uint8_t brp;
    uint16_t sjw;
    uint16_t tseg1;
    uint16_t tseg2;
}Bit_Timing_Parameter_Table_T;



/*===========================================================================*/
/* 					Exported variable declaration							 */
/*===========================================================================*/

extern const Bit_Timing_Parameter_Table_T HWCAN_Bit_Timing_Table[];

extern const uint8_t Size_Of_Bit_Timing_Parameter_Table;
#if 0
extern volatile xxICn_IntMaskLow_T  *CAN0MASKLOW;
extern volatile xxICn_IntMaskHigh_T  *CAN0MASKHIGH;
extern volatile xxICn_IntPriLow_T     *CAN0INTPRIOLOW;
extern volatile xxICn_IntPriHigh_T     *CAN0INTPRIOHIGH;
extern volatile xxICn_IntTxPriLow_T     *CAN0TXINTPRIOLOW;
extern volatile xxICn_IntTxPriHigh_T     *CAN0TXINTPRIOHIGH;
extern volatile xxICn_IntReqLow_T     *CAN0INTREQLOW;
extern volatile xxICn_IntReqHigh_T     *CAN0INTREQHIGH;
#endif

/*******************************************************************************
*              EXTERN FUNCTION DECLARATIONS  FOR CAN DRIVER                    *
********************************************************************************/

extern void HWCAN_Init_Misc(void);

extern void HWCAN_Init_For_Additional_features(uint8_t channel_num);

extern void HWCAN_Change_Mode(uint8_t channel_num, Operating_Mode_T mode);

extern void HWCAN_Load_Bit_Timing_Parameters(uint8_t channel_num, Speed_Mode_T speed_mode);

extern Boolean_Returnvalue_T HWCAN_Is_Bus_Off(uint8_t channel_num);

extern Boolean_Returnvalue_T HWCAN_Is_Err_Warning(uint8_t channel_num);

extern Boolean_Returnvalue_T HWCAN_Is_Err_Passive(uint8_t channel_num);

extern void HWCAN_Clear_Err_IntPnd_Flag_On_Interrupt (uint8_t channel_num);

extern Boolean_Returnvalue_T HWCAN_Is_CAN_Controller_Synchronized (uint8_t channel_num);

extern void HWCAN_Enable_All_CAN_Interrupt_At_Init(uint8_t channel_num);

#ifdef CAN_SLEEP_MODE_AVAILABLE

extern Sleep_Result_T HWCAN_Is_OK_To_Sleep (uint8_t channel_num);

extern void HWCAN_Go_To_Sleep (uint8_t channel_num);

extern Sleep_Result_T HWCAN_Clear_Sleep_State (uint8_t channel_num);

#endif

#ifdef CAN_WAKEUP_MODE_AVAILABLE

extern void HWCAN_Clear_Wakeup_IntPnd_Flag_On_Interrupt (uint8_t channel_num);

extern Boolean_Returnvalue_T HWCAN_Has_Controller_Woken_Up (uint8_t channel_num); 
#endif

extern void Initialize_CAN_Ports(uint8_t channel_num);
extern void HWCAN_Init_All_Reg(uint8_t channel_num);

/*******************************************************************************
*              EXTERN FUNCTION DECLARATIONS  FOR APPLICATION                   *
********************************************************************************/
extern uint8_t HWCAN_Get_Tx_Err_Cnt(uint8_t channel_num);

extern uint8_t HWCAN_Get_Rx_Err_Cnt(uint8_t channel_num);

#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file for      *
 *                 Sandeep       NEC v850 Fx3                                  *
 * 2   27-May-11   Sharma        Added Speed_Mode_T for SID 87                 *
 ******************************************************************************/
