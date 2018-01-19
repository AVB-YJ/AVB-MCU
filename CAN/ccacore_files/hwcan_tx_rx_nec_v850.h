/******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS: Prakash, Sandeep                                                  *
 * Project: CCA - HWCAN                                                       *
 * File Name:  hwcan_tx_rx_nec_v850.h                                         *
 * File Description:                                                          *
 * This file contains the register definitions for the on-chip CAN interfaces *
 * available in NEC-V850ES/Fx3 microcontroller. This also contains the        *
 * function declaration and global variables for used in HWCAN layer          *
 * Micro Description:							                              *
 * The HWCAN layer is written for uPD70Fxxxx which belongs to		          *
 * the NEC-V850ES/Fx3 series. This code can support three channels.	          *
 ******************************************************************************/


#ifndef HWCAN_TX_RX_NEC_V850_H
#define HWCAN_TX_RX_NEC_V850_H

#include "hwcan_init_misc_nec_v850.h"
//#include "hwcan_nec_v850_config.h"
#include "can_handler_datatypes.h"
#include "io78f1840_80.h"
#include "io78f1840_80_ext.h"


/******************************************************************************/
/* 							  Macro Definitions                               */
/******************************************************************************/
#define CAN_INVALID_MSG_NUMBER                                             		0xFF
#define FIRST_RX_MSG_BUF_INDEX                                                	   0
#define INVALID_MASK_NO								                            0xFF
#define CAN_DLC_MAX							                                       8

/*===========================================================================*/
/* 					Type declarations (enum, struct, union, typedef)		 */
/*===========================================================================*/

typedef struct RX_Msg_Info_Type
{
   uint8_t hw_rx_buf_num;
   Msg_ID_T rx_msg_id;
   Msg_ID_Type_T rx_msg_id_type;
   uint8_t rx_msg_dlc;
}RX_Msg_Info_T;

typedef struct TX_Buffer_Message_Mapping_Table_Tag
{
    uint8_t channel_number;
    uint16_t tx_message_buffer_num;
}TX_Buffer_Message_Mapping_Table_T;

typedef struct RX_Buffer_Message_Mapping_Table_Tag
{
    canuint16_t rx_message_buffer_num;
    canuint8_t mask_no;
    canuint32_t mask_value;
    canuint32_t hardware_filter;
    Msg_ID_Type_T  ID_type;
}RX_Buffer_Message_Mapping_Table_T;



/******************************************************************************/
/*     NEC-V850 CONTROL REGISTERS FOR MESSAGE_BUFFERS_DECLARATIONS            */
/******************************************************************************/

typedef struct AFCAN_MESSAGE_BUFFER_T
{
   uint8_t                  mssg_buff_data[CAN_DLC_MAX];
   uint8_t                  mssg_buff_dlc;
   uint8_t                  mssg_buff_conf;
   uint16_t                 mssg_buff_idl;
   uint16_t                 mssg_buff_idh;
   uint16_t                 mssg_buff_ctrl;
}AFCAN_MESSAGE_BUFFER_T;

/* defining a structure whose member element is an array with  
   length equal to the number of buffers */

typedef struct AFCAN_MESSAGE_BUFFERS_T
{
   struct AFCAN_MESSAGE_BUFFER_T afcan_message_buffer[AFCAN_MESSAGE_BUFFERS];

}AFCAN_MESSAGE_BUFFERS_T;


/******************************************************************************/
/*     			NEC-V850 CONTROL REGISTERS DECLARATIONS                       */
/******************************************************************************/

typedef struct AFCAN_CONTROL_REGISTERS_T
{
   uint16_t					GMCTRL;
   uint8_t					unused_1[4];
   uint16_t					GMABT;
   uint8_t					unused_2[6];
   uint8_t					GMCS;
   uint8_t					GMABTD;
   uint8_t                  unused_3[16];
   uint16_t					CTRL;
   uint8_t					LEC;
   uint8_t					INFO;
   uint16_t					ERC;
   uint16_t					IE;
   uint16_t					INTS;
   uint8_t					BRP;
   uint8_t					unused_4;
   uint16_t					BTR;
   uint8_t					unused_5;
   uint8_t					LIPT;
   uint16_t					RGPT;
   uint8_t					LOPT;
   uint8_t					unused_6;
   uint16_t					TGPT;
   uint16_t					TS;
}AFCAN_CONTROL_REGISTERS_T;

  

/******************************************************************************/
/*     			NEC-V850 MASK REGISTERS DECLARATIONS	                      */
/******************************************************************************/

#ifdef HWCAN_MASK_USED
/*Structure for accessing the mask registers */
typedef struct AFCAN_MASK_REGISTER_T
{
	uint16_t maskl;
	uint16_t maskh;
}AFCAN_MASK_REGISTER_T;

/* defining a structure whose member element is an array with  
   length equal to the number of masks */
typedef struct AFCAN_MASK_REGISTERS_T
{
	struct AFCAN_MASK_REGISTER_T afcan_mask_register[AFCAN_MASK_REGISTERS];
}AFCAN_MASK_REGISTERS_T;
#endif


/*******************************************************************************
*              EXTERN TABLE DECLARATIONS FOR TX and RX                         *
*******************************************************************************/

extern const TX_Buffer_Message_Mapping_Table_T HWCAN_Tx_Init_Table[];

extern const uint8_t Size_Of_Tx_Init_Table;


#ifdef CAN_CH0_SELECTED
extern const RX_Buffer_Message_Mapping_Table_T HWCAN_Rx_Init_Table_Ch0[];
extern const uint8_t Size_of_HWCAN_Rx_Init_Tbl_Ch0; 
#endif

#ifdef CAN_CH1_SELECTED
extern const RX_Buffer_Message_Mapping_Table_T HWCAN_Rx_Init_Table_Ch1[];
extern const uint8_t Size_of_HWCAN_Rx_Init_Tbl_Ch1; 
#endif

#ifdef CAN_CH2_SELECTED
extern const RX_Buffer_Message_Mapping_Table_T HWCAN_Rx_Init_Table_Ch2[];
extern const uint8_t Size_of_HWCAN_Rx_Init_Tbl_Ch2; 
#endif

extern const uint8_t Size_Of_HWCAN_Rx_Init_Tables[];

extern const RX_Buffer_Message_Mapping_Table_T *HWCAN_Rx_Init_Tables[];

extern uint8_t Tx_Msg_Obj[AFCAN_NUMBER_OF_CHANNELS];

extern RX_Msg_Info_T RX_Msg_Info[];

/*******************************************************************************
 *                      EXTERN VARIABLE DECLARATION                            *
 *******************************************************************************/

extern volatile AFCAN_MESSAGE_BUFFERS_T *afcan_message_buffers_vcan[AFCAN_NUMBER_OF_CHANNELS];
extern volatile AFCAN_CONTROL_REGISTERS_T *afcan_control_registers[AFCAN_NUMBER_OF_CHANNELS];

/*******************************************************************************
 *              EXTERN FUNCTION DECLARATIONS  FOR CAN DRIVER                   *
 *******************************************************************************/

#pragma inline=forced
void Enable_Tx_Message_Buffer(uint8_t channel_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
      
   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl & 
   	0x0001) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl =
      0x0001;
   }   
      /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
      //Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }

}

extern void HWCAN_Configure_Message_Objects_For_Tx_Rx(uint8_t channel_num);

#pragma inline=forced
Boolean_Returnvalue_T HWCAN_Is_Tx_Buffer_Available(uint8_t channel_num)
{
   Boolean_Returnvalue_T buffer_status;
   
   buffer_status = cbFALSE;

   /* Checking the RDY bit */
   if(!(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl & 
   	0x0001))
   {
      buffer_status = cbTRUE;
   }
   
   
   return (buffer_status);
}

#pragma inline=forced
void HWCAN_Load_Tx_ID(uint8_t channel_num, uint8_t ID_type, Msg_ID_T ID)
{
   uint16_t id_l;
   uint16_t id_h;
   
#ifdef STANDARD_ID_MODE

      id_l = 0x0000;
      id_h = (canuint16_t)(ID << 2);
	  id_h &= 0x7fff;
#else
      id_l = (canuint16_t)ID;
      
      /* Right shift id by 16 to get the upper word */
      ID >>= 16;
      id_h = (canuint16_t)ID;
	  id_h |= 0x8000;
#endif
   
   /* TRQ */
   /* as RDY bit is used to check whether the buffer is available or not, so 
      the buffer is locked in HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt (canuint8_t channel_num) function*/
   /* Lock the transmit hardware buffer */
   Enable_Tx_Message_Buffer(channel_num);
      
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_idl = id_l;
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_idh = id_h;
   
}

#pragma inline=forced
void HWCAN_Load_Tx_Data(uint8_t channel_num, uint8_t dlc,uint8_t* dataptr)
{

   volatile uint8_t * temp_data_buf;
   
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_dlc = dlc; 
   temp_data_buf =  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_data;
   
   switch(dlc)  
   {
      case (8):
               *(temp_data_buf)++ = *dataptr++; 
      case (7):
               *(temp_data_buf)++ = *dataptr++; 
      case (6):
               *(temp_data_buf)++ = *dataptr++; 
      case (5):
               *(temp_data_buf)++ = *dataptr++; 
      case (4):
               *(temp_data_buf)++ = *dataptr++; 
      case (3):
               *(temp_data_buf)++ = *dataptr++; 
      case (2):
               *(temp_data_buf)++ = *dataptr++; 
      case (1):
               *(temp_data_buf) = *dataptr; 
      default :
               break;
    }
}
#if 0
#pragma inline=forced
static void Disable_Tx_Message_Buffer(uint8_t channel_num)
{
    /* Set the RDY bit */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl
                                             = 0x0100;   
}

#pragma inline=forced
void HWCAN_Initiate_Transmission(uint8_t channel_num)
{
   Disable_Tx_Message_Buffer(channel_num); 
   /* Initiate transmission */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl
                     = 0x0200;
}
#endif
extern void HWCAN_Initiate_Transmission(uint8_t channel_num);
extern void HWCAN_Clear_TX_Request(uint8_t channel_no);
extern can_boolean_t HWCAN_Is_New_Data_Flag_Set(uint8_t channel_num, 
                                                        uint8_t hw_buf_num);
extern void HWCAN_Clear_NewData_Flag(uint8_t channel_num, uint8_t msg_buf_num);

extern uint8_t HWCAN_Get_IntPnd_Status(uint8_t channel_num, 
                                       Interrupt_Type_T interrupt_type);
                                       
extern void HWCAN_Clear_IntPnd_Register(uint8_t channel_num);                                     

extern bool8_t HWCAN_Has_Transmit_Confirmation_Been_Received (uint8_t channel_num);


/********************************************************************************************/
/*									INLINE FUNCTIONS Declaration							*/
/********************************************************************************************/
extern void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt (uint8_t channel_num);
extern void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt (uint8_t channel_num, uint8_t rx_msg_obj);
extern uint8_t HWCAN_Get_Rx_Buffer_Number(uint8_t channel_num);
extern can_boolean_t HWCAN_Is_Message_OverWritten (uint8_t channel_num, uint8_t hw_buf_num);
extern void HWCAN_Lock_Buffer(uint8_t channel_num, uint8_t rx_buf_num);
extern void HWCAN_UnLock_Buffer(uint8_t channel_num, uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_ID(uint8_t channel_num, uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_IDtype(uint8_t channel_num, uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_DLC(uint8_t channel_num,uint8_t rx_buf_num);
extern RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info (uint8_t channel_number);
extern uint8_t* HWCAN_Get_Rx_Data_Pointer(uint8_t channel_num, uint8_t hw_rx_buf_num);
extern bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer(uint8_t channel_num, uint8_t hw_rx_buf);
extern uint8_t HWCAN_Get_Tx_Buf_Number(uint8_t channel_num);
extern uint8_t HWCAN_Get_First_Rx_Buf_Number(uint8_t channel_num);

//#pragma inline=forced
//void HWCAN_Disable_All_CAN_Interrupts(uint8_t channel_num);
#pragma inline=forced
void HWCAN_Disable_All_CAN_Interrupts(uint8_t channel_num)
{
/* To mask/unmask the interrupts,access xxICn register as bit wise only */
//   CAN0MASKLOW->F.recMask = 1;    
   C0RECMK= 1;

//   CAN0MASKLOW->F.errMask = 1;
   C0ERRMK= 1;
//   CAN0MASKHIGH->F.trxMask = 1;
   C0TRXMK= 1; 
 #ifdef CAN_WAKEUP_MODE_AVAILABLE
//   CAN0MASKLOW->F.wupMask = 1;
   C0WUPMK = 1;
 #endif
}

#pragma inline=forced
void HWCAN_Disable_TX_CAN_Interrupts(uint8_t channel_num)
{
   //CAN0MASKHIGH->F.trxMask = 1;
   //CAN0MASKLOW->F.errMask = 1;
   HWCAN_Disable_All_CAN_Interrupts(channel_num);
}

#pragma inline=forced
void HWCAN_Disable_RX_CAN_Interrupts(uint8_t channel_num)
{
/* To mask/unmask the interrupts,access xxICn register as bit wise only */
  // CAN0MASKLOW->F.recMask = 1;    
  // CAN0MASKLOW->F.errMask = 1;
  HWCAN_Disable_All_CAN_Interrupts(channel_num);
}

//#pragma inline=forced
//void HWCAN_Enable_All_CAN_Interrupts(uint8_t channel_num);

#pragma inline=forced
void HWCAN_Enable_All_CAN_Interrupts(uint8_t channel_num)
{
#if 0
  canuint8_t rx_buf, Param_Table_Index; 
  afcan_control_registers[channel_num]->IE = 0x2F00;
  
  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl = 0x0800;
  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[1].mssg_buff_ctrl = 0x0800;  
    /* Enables all CAN interrupts */
   for(Param_Table_Index=0; Param_Table_Index < Size_Of_HWCAN_Rx_Init_Tables[channel_num];
                                                                    Param_Table_Index ++) 
   {
      rx_buf = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].rx_message_buffer_num;
	  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf].mssg_buff_ctrl = 0x0800;
	  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf].mssg_buff_ctrl = 0x0100;
   }
#endif
   C0RECMK= 0U;
   C0ERRMK= 0U;

//   CAN0MASKLOW->F.recMask = 0;    
//   CAN0MASKLOW->F.errMask = 0;
//   CAN0MASKHIGH->F.trxMask = 0;
   C0TRXMK= 0U; 
  #ifdef CAN_WAKEUP_MODE_AVAILABLE
//   CAN0MASKLOW->F.wupMask = 0;
   C0WUPMK= 0U;
  #endif
}
#if 0
#pragma inline=forced
void HWCAN_Enable_RX_CAN_Interrupts(uint8_t channel_num)
{
   //CAN0MASKLOW->F.recMask = 0;
   //CAN0MASKLOW->F.errMask = 0;    
   HWCAN_Enable_All_CAN_Interrupts(channel_num);
}

#pragma inline=forced
void HWCAN_Enable_TX_CAN_Interrupts(uint8_t channel_num)
{
 /* afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl = 0x0800;  
  CAN0MASKHIGH->F.trxMask = 0;
  CAN0MASKLOW->F.errMask = 0;*/
  HWCAN_Enable_All_CAN_Interrupts(channel_num);
}
#endif
#pragma inline=forced
void HWCAN_Disable_CAN_Tx_Rx_Interrupts(uint8_t channel_num)
{
  // CAN0MASKLOW->F.recMask = 1;    
  // CAN0MASKLOW->F.errMask = 1;
  // CAN0MASKHIGH->F.trxMask = 1;
  HWCAN_Disable_All_CAN_Interrupts(channel_num);
}
#pragma inline=forced
extern void HWCAN_Enable_CAN_Interrupt(uint8_t channel_num, uint8_t CAN_Int_Type);

#pragma inline=forced
extern void HWCAN_Disable_CAN_Interrupt(uint8_t channel_num, uint8_t CAN_Int_Type);


#ifdef CAN_CH0_SELECTED


#pragma inline=forced
void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch0 (void)
{
   /* Clear transmit interrupt pending flag by writing 1 into INTS register
      at the bit position corresponding to the transmit buffer */
   afcan_control_registers[0]->INTS = 0x0001;

   /* Clear RDy bit */
   Enable_Tx_Message_Buffer(0);    
}

#pragma inline=forced
void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch0 (uint8_t rx_msg_obj)
{
   /* Clear receive interrupt pending flag by writing 1 into INTS register
     at the bit position corresponding to the transmit buffer */
   if( CAN_INVALID_MSG_NUMBER != rx_msg_obj )
   {
      afcan_control_registers[0]->INTS = 0x0002;
   }
}

extern uint8_t HWCAN_Get_Rx_Buffer_Number_Ch0(void);

#pragma inline=forced
can_boolean_t HWCAN_Is_Message_OverWritten_Ch0 (uint8_t hw_buf_num)
{
   can_boolean_t msg_overwritten;
   
   if(afcan_message_buffers_vcan[0]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl & 
   	0x0010)
   {
      afcan_message_buffers_vcan[0]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl = 0x0010;
      msg_overwritten = CAN_cbTRUE;
   }
   else
   {
      msg_overwritten = CAN_cbFALSE;
   }
   return(msg_overwritten);
}

extern void HWCAN_Lock_Buffer_Ch0(uint8_t rx_buf_num);
extern void HWCAN_UnLock_Buffer_Ch0(uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_ID_Ch0(uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_IDtype_Ch0(uint8_t Rx_buf_num);
extern void HWCAN_Get_Rx_DLC_Ch0(uint8_t rx_buf_num);

extern RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info_Ch0 (void);

//#pragma inline=forced
//extern uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch0(uint8_t hw_rx_buf_num);
#pragma inline=forced
uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch0(uint8_t hw_rx_buf_num)
{
   return((uint8_t *)afcan_message_buffers_vcan[0]->afcan_message_buffer[hw_rx_buf_num].mssg_buff_data);
}

extern bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch0(uint8_t hw_rx_buf);
extern uint8_t HWCAN_Get_Tx_Buf_Number_Ch0(void);
extern uint8_t HWCAN_Get_First_Rx_Buf_Number_Ch0(void);

#endif

#ifdef CAN_CH1_SELECTED

extern void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch1 (void);
extern void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch1 (uint8_t rx_msg_obj);
extern uint8_t HWCAN_Get_Rx_Buffer_Number_Ch1(void);
extern can_boolean_t HWCAN_Is_Message_OverWritten_Ch1(uint8_t hw_buf_num);
extern void HWCAN_Lock_Buffer_Ch1(uint8_t rx_buf_num);
extern void HWCAN_UnLock_Buffer_Ch1(uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_ID_Ch1(uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_IDtype_Ch1(uint8_t Rx_buf_num);
extern void HWCAN_Get_Rx_DLC_Ch1(uint8_t rx_buf_num);
extern RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info_Ch1 (void);
extern uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch1(uint8_t hw_rx_buf_num);
extern bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch1(uint8_t hw_rx_buf);
extern uint8_t HWCAN_Get_Tx_Buf_Number_Ch1(void);
extern uint8_t HWCAN_Get_First_Rx_Buf_Number_Ch1(void);

#endif
#ifdef CAN_CH2_SELECTED
extern void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch2 (void);
extern void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch2 (uint8_t rx_msg_obj);
extern uint8_t HWCAN_Get_Rx_Buffer_Number_Ch2(void);
extern can_boolean_t HWCAN_Is_Message_OverWritten_Ch2 (uint8_t hw_buf_num);
extern void HWCAN_Lock_Buffer_Ch2(uint8_t rx_buf_num);
extern void HWCAN_UnLock_Buffer_Ch2(uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_ID_Ch2(uint8_t rx_buf_num);
extern void HWCAN_Get_Rx_IDtype_Ch2(uint8_t Rx_buf_num);
extern void HWCAN_Get_Rx_DLC_Ch2(uint8_t rx_buf_num);
extern RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info_Ch2 (void);
extern uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch2(uint8_t hw_rx_buf_num);
extern bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch2(uint8_t hw_rx_buf);
extern uint8_t HWCAN_Get_Tx_Buf_Number_Ch2(void);
extern uint8_t HWCAN_Get_First_Rx_Buf_Number_Ch2(void);

#endif
#endif
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file for      *
 *                 Sandeep       NEC v850 Fx3                                  *
 * 2   10-Mar-2010 Ashwini       Renamed afcan_message_buffers as 			   *
 *                               afcan_message_buffers_vcan. 	
 *     19Sept2011  Anil           Added Enable interrupts 
 ******************************************************************************/
