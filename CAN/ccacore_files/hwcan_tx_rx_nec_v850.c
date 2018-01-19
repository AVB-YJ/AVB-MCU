/*****************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved             *
 * REVISION: 1.0                                                             *
 * AUTHORS: Prakash, Sandeep                                                 *
 * Project: CCA - HWCAN                                                      *
 * File Name:  hwcan_tx_rx_nec_v850.c	                                     *
 * File Description:                                                         *
 * This file contains the generic APIs for Tx and Rx provided to CAN Driver  *
 * These generic APIs are translated to specific hardware accesses on the    *
 * NEC-V850ES/Fx3 CAN controller. HWCAN Layer provides accesses to the       *
 * on-chip Control/Status registers and message buffers                      *
 * Micro Description:							                             *
* The HWCAN layer is written for both NEC-V850ES/FG2 and NEC-V850ES/FJ3 	 *
 * micro. 																	 *
 *  >>>>> If NEC-V850ES/FG2 micro is used the define "NEC_V850_FG2" macro in *
 *  	  hwcan_nec_v850_config.h  											 *
 *  >>>> If NEC-V850ES/FJ3 is used then undef "NEC_V850_FG2" macro in		 *
 *       hwcan_nec_v850_config.h 											 *
 *  These two micro differs only in the base address of interrupt 			 *
 *  control registers and the number of CAN channels available                *
 *****************************************************************************/

#include "hwcan_tx_rx_nec_v850.h"

/******************************************************************************/
/*                              LOCAL MACRO DEFINITIONS                       */
/******************************************************************************/

/************************Macros for Message buffer registers***********************/

/* Define Bit Masks for message buffer control register (CTRLm) */
#define MUC_M 0x2000
#define MOW_M 0x0010
#define IE_M  0x0008 
#define DN_M  0x0004 
#define TRQ_M 0x0002 
#define RDY_M 0x0001
#define SET_TRQ_M   0x0200 
#define SET_RDY_M   0x0100
#define CLEAR_MOW_M 0x0010
#define CLEAR_IE_M  0x0008 
#define CLEAR_DN_M  0x0004 
#define CLEAR_TRQ_M 0x0002 
#define CLEAR_RDY_M 0x0001

/* Define bit masks for message buffer configuration register (CONFm) */
#define OWS_M 0x80
#define RTR_M 0x40
#define MA0_M 0x01
#define MESSAGE_CONFIG_TRANSMIT        ( 0x00 << 3 )
#define MESSAGE_CONFIG_RECEIVE_NO_MASK ( 0x01 << 3 )
#define MESSAGE_CONFIG_RECEIVE_MASK_1  ( 0x02 << 3 )
#define MESSAGE_CONFIG_RECEIVE_MASK_2  ( 0x03 << 3 )
#define MESSAGE_CONFIG_RECEIVE_MASK_3  ( 0x04 << 3 )
#define MESSAGE_CONFIG_RECEIVE_MASK_4  ( 0x05 << 3 )

/* Macros for configuring message buffers */
#define AFCAN_MSSG_BUFF_CONF_UNUSED                 	                         0x00
#define AFCAN_MSSG_BUFF_CONF_TRANSMIT             ( MESSAGE_CONFIG_TRANSMIT | MA0_M )
#define AFCAN_MSSG_BUFF_CONF_RECEIVE (MESSAGE_CONFIG_RECEIVE_NO_MASK | MA0_M | OWS_M)

/* Macros related to CTRL register */
#define AFCAN_MSSG_BUFF_CTRL_UNUSED													 CLEAR_RDY_M
#define AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY                                   CLEAR_RDY_M
#define AFCAN_MSSG_BUFF_CTRL_SET_RDY                                       SET_RDY_M
#define AFCAN_BUFFER_AVAILABILITY_MASK                                   CLEAR_TRQ_M
#define AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK				                      CLEAR_RDY_M
#define AFCAN_MSSG_BUFF_CTRL_SET_TRQ                                       SET_TRQ_M
#define AFCAN_MSSG_BUFF_CTRL_MOW_MASK                                    	   MOW_M
#define AFCAN_MSSG_BUFF_CTRL_CLEAR_MOW                                   CLEAR_MOW_M
#define AFCAN_MSSG_BUFF_CTRL_CLEAR_DN					                  CLEAR_DN_M
#define AFCAN_MSSG_BUFF_CTRL_TX_DEFAULT	\
				              (CLEAR_MOW_M | CLEAR_DN_M | CLEAR_TRQ_M | CLEAR_RDY_M)
#define AFCAN_MSSG_BUFF_CTRL_RX_DEFAULT \
				                (CLEAR_MOW_M | CLEAR_DN_M | CLEAR_TRQ_M | SET_RDY_M)
#define AFCAN_MSSG_BUFF_CTRL_SET_IE                                           0x0800
				   
/* Macros for message ID registers */
#define AFCAN_CLEAR_IDE                                                       0x7FFF
#define AFCAN_SET_IDE                                                         0x8000
#define AFCAN_SET_LOWER_WORD_ZERO                                             0x0000
#define AFCAN_ID_H_LS_2                                                            2
#define AFCAN_IDH_RS_2															   2
#define AFCAN_ID_H_RS_16													      16
#define AFCAN_IDH_LS_16                                                 	      16
#define AFCAN_MSSG_BUFF_IDH_MASK                                         	  0x07FF
#define AFCAN_MSSG_BUFF_IDE_MASK                                         	  0x8000
#define AFCAN_MASK_H_LS_2                                                          2
#define AFCAN_Mask_H_RS_16													      16
#define AFCAN_MASK_BUFFERS													       4
#define AFCAN_MAXIMUM_NUMBER_OF_MASK                                          0xFF // mask allowed for every msg object

/********************* Macros for CAN module Control registers ***********************/

/* Macros for Interrupt status (INTS) registers */ 
#define AFCAN_ERROR_INTERRUPT_STATUS_MASK                                 	  0x0004
#define AFCAN_RECEIVE_INTERRUPT_STATUS_MASK                                   0x0002
#define AFCAN_TRANSMIT_INTERRUPT_STATUS_MASK                                  0x0001
#define AFCAN_WAKEUP_INTERRUPT_STATUS_MASK                                    0x0020
#define AFCAN_CLEAR_TRANSMIT_INTERRUPT_PENDING_FLAG                     	  0x0001
#define AFCAN_CLEAR_RECEIVE_INTERRUPT_PENDING_FLAG                       	  0x0002
#define AFCAN_CLEAR_ALL_INTERRUPT_PENDING_FLAG					              0x003F


/* Macros for Interrupt enable (IE) register */
#define AFCAN_IE_DISABLE_INTERRUPTS                                      	  0x003F
#define AFCAN_IE_ENABLE_INTERRUPTS										      0x3F00
#define AFCAN_IE_ENABLE_TRANSMIT_INTERRUPT									  0x013E
#define AFCAN_IE_ENABLE_RECEIVE_INTERRUPT									  0x023D
#define AFCAN_IE_ENABLE_ERROR_INTERRUPT	   									  0x043B
#define AFCAN_IE_ENABLE_WAKEUP_INTERRUPT  									  0x201F
#define AFCAN_IE_DISABLE_TRANSMIT_INTERRUPT									  0x0001
#define AFCAN_IE_DISABLE_RECEIVE_INTERRUPT									  0x0002
#define AFCAN_IE_DISABLE_ERROR_INTERRUPT									  0x0004
#define AFCAN_IE_DISABLE_WAKEUP_INTERRUPT									  0x0020

/* Macros for Receive historty list (RGPT) register */
#define AFCAN_RGPT_MASK                                                  	  0xFF03
#define AFCAN_RGPT_RS_8                                                            8
#define AFCAN_CHECK_ROVF                                                 	  0x0001
#define AFCAN_RHPM_SET_MASK                                                   0x0002
#define AFCAN_CLEAR_ROVF                                                      0x0001


#ifdef HWCAN_MASK_USED
/* Macros for base address of CAN module mask registers */
#define AFCAN_CHANNEL0_MASK_REG_BASE_ADD		\
		  	   (AFCAN_CHANNEL0_CONTROL_REGISTERS_BASE_ADD + AFCAN_MASK_REGISTERS_OFFSET)
#endif

/* Macros for base address of CAN module message buffers */
#define AFCAN_CHANNEL0_MESSAGE_BUFF_BASE_ADD	\
			(AFCAN_MESSAGE_BUFF_REGISTERS_BASE_ADD)

/*******************************************************************************
* HWCAN_RX_INIT_TABLES FOR SUPPORTED CHANNELS                                  *
*******************************************************************************/
const RX_Buffer_Message_Mapping_Table_T *HWCAN_Rx_Init_Tables[] =
{
  HWCAN_Rx_Init_Table_Ch0,
};


/*===========================================================================*/
/*              		Exported variable defination                         */
/*===========================================================================*/

volatile AFCAN_MESSAGE_BUFFERS_T *afcan_message_buffers_vcan[AFCAN_NUMBER_OF_CHANNELS] = 
{
   ( AFCAN_MESSAGE_BUFFERS_T*)AFCAN_CHANNEL0_MESSAGE_BUFF_BASE_ADD,
};   


volatile AFCAN_CONTROL_REGISTERS_T *afcan_control_registers[AFCAN_NUMBER_OF_CHANNELS] =
{
   (AFCAN_CONTROL_REGISTERS_T *)AFCAN_CHANNEL0_CONTROL_REGISTERS_BASE_ADD,
};

/*******************************************************************************
* static variable declarations                                                 *
********************************************************************************/
#ifdef HWCAN_MASK_USED
const uint8_t Mask_Register_Config_values[AFCAN_MASK_BUFFERS] = 
{
   (MESSAGE_CONFIG_RECEIVE_MASK_1 | MA0_M | OWS_M),/* Configuration value for a receive buffer to map it to MASK Buffer 1*/
   (MESSAGE_CONFIG_RECEIVE_MASK_2 | MA0_M | OWS_M),/* Configuration value for a receive buffer to map it to MASK Buffer 2*/
   (MESSAGE_CONFIG_RECEIVE_MASK_3 | MA0_M | OWS_M),/* Configuration value for a receive buffer to map it to MASK Buffer 3*/
   (MESSAGE_CONFIG_RECEIVE_MASK_4 | MA0_M | OWS_M) /* Configuration value for a receive buffer to map it to MASK Buffer 4*/
};

volatile AFCAN_MASK_REGISTERS_T *afcan_mask_registers[AFCAN_NUMBER_OF_CHANNELS] =
{
   (AFCAN_MASK_REGISTERS_T *)AFCAN_CHANNEL0_MASK_REG_BASE_ADD,
};
#endif


uint8_t Tx_Msg_Obj[AFCAN_NUMBER_OF_CHANNELS];

RX_Msg_Info_T RX_Msg_Info[AFCAN_NUMBER_OF_CHANNELS];

  void HWCAN_Configure_Message_Objects_For_Tx(uint8_t channel_num);

 void HWCAN_Configure_Message_Objects_For_Rx(uint8_t channel_num);

 void HWCAN_Configure_Message_Objects_For_Rx_ID(uint8_t channel_num,
                                uint8_t Rx_Buf, uint8_t Param_Table_Index);
 void HWCAN_Configure_Message_Object_As_Unused(uint8_t channel_num);
                                

/*******************************************************************************
* 								Function macros                                *
********************************************************************************/

/******************************************************************************/
/* FunctionName      : CLEAR_IDE                                              */
/* Arguments passed  : None                                                   */
/* Return Value      : None                                                   */
/* Function Description : Clears the IDE bit as messages are 				  */
/*						  of standard id type		  						  */
/******************************************************************************/

#define CLEAR_IDE()		(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_idh &= AFCAN_CLEAR_IDE)

/******************************************************************************/
/* FunctionName      : SET_IDE                                                */
/* Arguments passed  : None                                                   */
/* Return Value      : None                                                   */
/* Function Description : SET the IDE bit as messages are 				      */
/*						  of extended id type                    			  */
/******************************************************************************/

#define SET_IDE()		(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_idh |= AFCAN_SET_IDE)
/*******************************************************************************
*                    Function Definitions                                      *
*******************************************************************************/

/*******************************************************************************
 * FunctionName:HWCAN_Configure_Message_Objects_For_Tx_Rx                      *
 * Arguments passed  : channel number                                          *
 * Return Value      : None                                                    *
 * Description : This function configures the Hardware buffers mentioned in    *
 * Tx Init table & Rx Init Table                                               *
*******************************************************************************/
void HWCAN_Configure_Message_Objects_For_Tx_Rx(uint8_t channel_num)
{
  /* Initialize buffers as unused */
  HWCAN_Configure_Message_Object_As_Unused(channel_num);
  HWCAN_Configure_Message_Objects_For_Tx(channel_num);
  HWCAN_Configure_Message_Objects_For_Rx(channel_num);
}

/*******************************************************************************
 * FunctionName:Disable_Message_Buffer                                         *
 * Arguments passed  : channel number                                          *
 * Return Value      : None                                                    *
 * Description : This function disables the specifide transmit buffer number   *
*******************************************************************************/
#if 0
static void Disable_Tx_Message_Buffer(uint8_t channel_num)
{
    /* Set the RDY bit */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl
                                             = AFCAN_MSSG_BUFF_CTRL_SET_RDY;   
}

/******************************************************************************
 * FunctionName: Enable_Message_Buffer                                        *
 * Arguments passed  : channel number                                         *
 * Return Value      : None                                                   *
 * Description : This routine enables the mesasge buffer by clearing a bit in *
 *               in mssg CTRL register corresponding to the mesasge           *
 *               buffer number                                                *
******************************************************************************/
void Enable_Tx_Message_Buffer(uint8_t channel_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
      
   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl =
      AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
   }   
      /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
      //Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }

}

#endif

/*******************************************************************************
 * Function Name : HWCAN_Configure_Message_Object_As_Unused                    *
 * Arguments passed  : uint8_t channel_num                                     *
 * Return Value : None                                                         *
 * Description : This functions sets all the message buffers as unused         *
 *******************************************************************************/
 
 void HWCAN_Configure_Message_Object_As_Unused(uint8_t channel_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;   
   uint8_t buf_cnt;
   
   /* Configure unused buffers not to any of CAN channels */
   for( buf_cnt= 0; buf_cnt < AFCAN_MESSAGE_BUFFERS; buf_cnt++)
   {

	   /* untill the rdy bit is clear be in this loop */
      while( (afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[buf_cnt].mssg_buff_ctrl & 
	  	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
      {
         /* Clear RDY bit */
         afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[buf_cnt].mssg_buff_ctrl =
         AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
	  }

      afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[buf_cnt].mssg_buff_conf = AFCAN_MSSG_BUFF_CONF_UNUSED;

       /* Notify failure to change the mode to application */
      if( 0L == TimeoutCounter_uint32_t ) 
      {
        // Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
      }
	  TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
   }
}

void HWCAN_Clear_TX_Request(uint8_t channel_no)
{
  uint32_t TimeoutCounter_uint32_t = 500;
  afcan_message_buffers_vcan[channel_no]->afcan_message_buffer[0].mssg_buff_ctrl = 0x0002;
  while(--TimeoutCounter_uint32_t > 0L );
  TimeoutCounter_uint32_t = 500;
  while( (afcan_control_registers[channel_no]->CTRL & 0x0300) && (--TimeoutCounter_uint32_t > 0L) );
}
/*******************************************************************************
 * FunctionName:HWCAN_Configure_Message_Objects_For_Tx                         *
 * Arguments passed  : channel number                                          *
 * Return Value      : None                                                    *
 * Description : This function configures the Hardware buffers mentioned in    *
 * Tx Init table                                                               *
*******************************************************************************/
 void HWCAN_Configure_Message_Objects_For_Tx(uint8_t channel_num)
{
/*******************************************************************************
* Assuming ONE transmit message object will be used by the VBM layer           *
* Since only 1 tx buffer will be used/channel 'channel_num' is passed as an    *
* argument to get the transmit message object number.                          *
*******************************************************************************/
	uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
	
   Tx_Msg_Obj[channel_num] = HWCAN_Tx_Init_Table[channel_num].tx_message_buffer_num;

   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl =
      AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
	}
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_conf
                                             = AFCAN_MSSG_BUFF_CONF_TRANSMIT;
   
   /* Enabling of intterupt for message buffer is done here 
     instead doing it at void HWCAN_Enable_All_CAN_Interrupt_At_Init(uint8_t channel_num) function*/
   /* Enable transmit interrupt for transmit buffer */ 
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_IE;  
      
   /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
      //Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }
}

/*******************************************************************************
 * FunctionName:HWCAN_Configure_Message_Objects_For_Rx(uint8_t channel_num)    *
 * Arguments passed  : channel number                                          *
 * Return Value      : None                                                    *
 * Description : This function configures the Hardware buffers mentioned in    *
 * Rx Init table                                                               *
 *******************************************************************************/
 void HWCAN_Configure_Message_Objects_For_Rx(uint8_t channel_num)
{
   uint8_t Param_Table_Index;
   uint8_t Rx_Buf;
   uint8_t mask_no;
   
   for (Param_Table_Index=0;Param_Table_Index < Size_Of_HWCAN_Rx_Init_Tables[channel_num];Param_Table_Index++)
   {
      Rx_Buf = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].rx_message_buffer_num;
	       
      mask_no = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].mask_no;
      
      if(INVALID_MASK_NO != mask_no)
      {
#ifdef HWCAN_MASK_USED
         if(mask_no <= AFCAN_MAXIMUM_NUMBER_OF_MASK)
	     {
            afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_conf = 
            														Mask_Register_Config_values[(mask_no -1)];
            
            /* Call function to configure rx buffers for the corresponding message ID */
            HWCAN_Configure_Message_Objects_For_Rx_ID(channel_num, Rx_Buf,Param_Table_Index);
         }
	     else
	     {
	        /* this function notifies the upper layer that mask is not provided */
	      //  Appl_Mask_Not_Provided();
	     }
#endif
      }	    
      else
      {
           
           
         afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_conf
                                             = AFCAN_MSSG_BUFF_CONF_RECEIVE;
		                                             
         /* Call function to configure rx buffers for the corresponding message ID */
         HWCAN_Configure_Message_Objects_For_Rx_ID(channel_num, Rx_Buf,Param_Table_Index);
      }
	  
	   /* The IE bit is set first and then the RDY bit, before this was done at
	     WCAN_Enable_All_CAN_Interrupt_At_Init(uint8_t channel_num) function*/ 
	  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_IE;
	  /* enable the RDY bit so that the CAN module can write to the receive buffer */
	  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_RDY;      
   }
   
}

/*******************************************************************************
 * FunctionName:HWCAN_Configure_Message_Objects_For_Rx_ID                      *
 * Arguments passed  : channel num, Rx Buf, Param Table_Index                  *
 * Return Value      : None                                                    *
 * Description : This function configures the ID for Rx buffers mentioned in   *
 * Rx Init table                                                               *
 *******************************************************************************/
 void HWCAN_Configure_Message_Objects_For_Rx_ID(uint8_t channel_num,
                                uint8_t Rx_Buf, uint8_t Param_Table_Index)
{
   Msg_ID_T Rx_Id;
   Msg_ID_Type_T ID_Type;
   uint16_t id_l, id_h;
   #ifdef HWCAN_MASK_USED
   Msg_ID_T Mask;
   uint16_t mask_l, mask_h;
   uint8_t mask_no;
   
   
   mask_no = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].mask_no;
   Mask = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].mask_value;
   #endif
      
   Rx_Id = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].hardware_filter;
   
   ID_Type = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].ID_type;
   
   if( ID_Type == STANDARD_ID )
   {
      /* If standard id, then set lower word to zero */
      id_l = AFCAN_SET_LOWER_WORD_ZERO;
      id_h = (canuint16_t)Rx_Id << AFCAN_ID_H_LS_2;
      /* Clear IDE bit as standard type ID */
	  id_h &= AFCAN_CLEAR_IDE; 
      #ifdef HWCAN_MASK_USED
      /* If standard id, then set lower word to zero */
      mask_l = AFCAN_SET_LOWER_WORD_ZERO;
      mask_h = (canuint16_t)Mask << AFCAN_MASK_H_LS_2;
      #endif
   }
   else
   {
      id_l = (canuint16_t)Rx_Id;
      /* Right shift id by 16 to get the upper word */
      Rx_Id >>= AFCAN_ID_H_RS_16;
      id_h = (canuint16_t)Rx_Id;
      /* Set IDE bit as Extended type ID */
	  id_h |= AFCAN_SET_IDE; 
      #ifdef HWCAN_MASK_USED
      mask_l = (canuint16_t)Mask;
      /* Right shift id by 16 to get the upper word */
      Mask >>= AFCAN_Mask_H_RS_16;
      mask_h = (canuint16_t)Mask;
      #endif
   }
      
#ifdef HWCAN_MASK_USED
   /* load mask value in the mask registers */
   afcan_mask_registers[channel_num]->afcan_mask_register[mask_no - 1].maskl = mask_l; 
   afcan_mask_registers[channel_num]->afcan_mask_register[mask_no - 1].maskh = mask_h;
#endif
	    
   /* load message id in the id registers */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_idl = id_l;
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Rx_Buf].mssg_buff_idh = id_h;

}

/*******************************************************************************
 * FunctionName: HWCAN_Is_Tx_Buffer_Available                                  *
 * Arguments passed  : channel number                                          *
 * Return Value      : buffer_status cbTRUE- hardware buffer available         *
 *                                   cbFALSE- hardware buffer not available    *
 * Description:This routine will inform the status of h/w transmit buffer      *
 *             availability to the caller function by returning an unsigned    *
 *             character value. This routine checks the RDY bit of Message     *
 *             control register, and flags availability of transmit buffer     *
 *******************************************************************************/
 #if 0
Boolean_Returnvalue_T HWCAN_Is_Tx_Buffer_Available(uint8_t channel_num)
{
   Boolean_Returnvalue_T buffer_status;
   
   buffer_status = cbFALSE;

   /* Checking the RDY bit */
   if(!(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK))
   {
      buffer_status = cbTRUE;
   }
   
#if 0
   /* This checks the TRQ bit */
   if(!(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl & AFCAN_BUFFER_AVAILABILITY_MASK))
   {
      buffer_status = cbTRUE;
   }
#endif
   
   return (buffer_status);
}
#endif
/*******************************************************************************
 * FunctionName      : HWCAN_Load_Tx_ID		                                  *
 * Arguments passed  : channel number, id type, id                             *
 * Return Value      : None                                                    *
 * Function Description :This function will be called by CAN Driver to load id *
 *                       of the message to be transmitted into the hardware    *
*******************************************************************************/
#if 0
void HWCAN_Load_Tx_ID(uint8_t channel_num, uint8_t ID_type, Msg_ID_T ID)
{
   uint16_t id_l;
   uint16_t id_h;
   
   if(STANDARD_ID == ID_type)
   {
      id_l = AFCAN_SET_LOWER_WORD_ZERO;
      id_h = (canuint16_t)(ID << AFCAN_ID_H_LS_2);
	  id_h &= AFCAN_CLEAR_IDE;
   }
   else
   {
      id_l = (canuint16_t)ID;
      
      /* Right shift id by 16 to get the upper word */
      ID >>= AFCAN_ID_H_RS_16;
      id_h = (canuint16_t)ID;
	  id_h |= AFCAN_SET_IDE;
   }
   
   /* TRQ */
   /* as RDY bit is used to check whether the buffer is available or not, so 
      the buffer is locked in HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt (canuint8_t channel_num) function*/
   /* Lock the transmit hardware buffer */
   Enable_Tx_Message_Buffer(channel_num);
      
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_idl = id_l;
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_idh = id_h;
   
}
#endif
/*******************************************************************************
 * FunctionName      : HWCAN_Load_Transmit_Data                                *
 * Arguments passed  : channel_numsage, DLC, dataptr                           *
 * Return Value      : None                                                    *
 * Function Description :This function loads the DLCregister and dataregisters *
 *                  with the message dlc and message data bytes                *
 *******************************************************************************/
 #if 0
void HWCAN_Load_Tx_Data(uint8_t channel_num, uint8_t dlc,uint8_t* dataptr)
{

   volatile uint8_t * temp_data_buf;
   
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_dlc = dlc; 
   temp_data_buf =  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_data;
   
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
 #endif

/*******************************************************************************
 * FunctionName:  HWCAN_Initiate_Transmission                                  *
 * Parameter(s): channel num                                                   *
.* Return Value(s): none                                                       *
 * Description:  This function initiates Tx by setting Transmit Request (TRQ)  *
 * bit                                                                         *
 *******************************************************************************/
#if 0
void HWCAN_Initiate_Transmission(uint8_t channel_num)
{
   Disable_Tx_Message_Buffer(channel_num); 
   /* Initiate transmission */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl
                     = AFCAN_MSSG_BUFF_CTRL_SET_TRQ;
}
#endif
void Disable_Tx_Message_Buffer(uint8_t channel_num)
{
    /* Set the RDY bit */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl
                                             = 0x0100;   
}

void HWCAN_Initiate_Transmission(uint8_t channel_num)
{
   Disable_Tx_Message_Buffer(channel_num); 
   /* Initiate transmission */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[0].mssg_buff_ctrl
                     = 0x0200;
}

/************************** ****************************************************
 * Function:     HWCAN_Is_New_Data_Flag_Set                                    *
 * Parameter(s): channel num, hw buf num                                       *
 * Return Value:cbTRUE if NEWDAT bit is set, else cbFALSE                      *
 * Description: This function checks the NEWDAT bit in Message Control Register*
 *******************************************************************************/
can_boolean_t HWCAN_Is_New_Data_Flag_Set(uint8_t channel_num, 
                                                 uint8_t hw_buf_num)
{
	//amit
	//to avoid warnings
	return(CAN_cbFALSE);
}

/*******************************************************************************
 * Function: HWCAN_Clear_NewData_Flag                                          *
 * Parameter(s): channel num, hw buf num                                       *
 * Return Value: none                                                          *
 * Description:This function clears the NEWDAT bit in Message Control Register *
 *******************************************************************************/
/* amit */

/* dont knw what this funcion does???? */
void HWCAN_Clear_NewData_Flag(uint8_t channel_num, uint8_t hw_buf_num)
{

}


/*******************************************************************************
 * FunctionName : HWCAN_Get_IntPnd_Status                                      *
 * Arguments passed  : channel num, interrupt type                             *
 * Return Value: Whether it was Tx, Rx, Error or Wake-up interrupt             *
 * Function Description :This function checks the CAN INT Status Register      *
 *******************************************************************************/
/* amit */
/* the return type should be Boolean_Returnvalue_T */
uint8_t HWCAN_Get_IntPnd_Status(uint8_t channel_num, Interrupt_Type_T interrupt_type)
{
   uint8_t Int_Pnd_Status;
   Int_Pnd_Status = CAN_cbFALSE;

   if(HWCAN_ERROR == interrupt_type)
   {
      if(afcan_control_registers[channel_num]->INTS & AFCAN_ERROR_INTERRUPT_STATUS_MASK)
      {
         Int_Pnd_Status = CAN_cbTRUE;
	   }
   }
#ifdef CAN_WAKEUP_MODE_AVAILABLE
   else if(HWCAN_WAKEUP == interrupt_type)
   {
      if(afcan_control_registers[channel_num]->INTS & AFCAN_WAKEUP_INTERRUPT_STATUS_MASK )
      {
         Int_Pnd_Status = CAN_cbTRUE;
	  }
   }
#endif
   else if(HWCAN_TRANSMIT == interrupt_type)
   {
      if(afcan_control_registers[channel_num]->INTS & AFCAN_TRANSMIT_INTERRUPT_STATUS_MASK )
      {
         Int_Pnd_Status = CAN_cbTRUE;
	  }
   }
   else if(HWCAN_RECEIVE == interrupt_type)
   {
      if(afcan_control_registers[channel_num]->INTS & AFCAN_RECEIVE_INTERRUPT_STATUS_MASK )
      {
         Int_Pnd_Status = CAN_cbTRUE;
	  }
   }
   return(Int_Pnd_Status);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Has_Transmit_Confirmation_Been_Received               *
 * Arguments passed  : channel num                                             *
 * Return Value: cbFALSE if RDY is set, else cbTRUE                            *
 * Function Description :This function checks RDY bit                          *
 *******************************************************************************/

bool8_t HWCAN_Has_Transmit_Confirmation_Been_Received (uint8_t channel_num)
{
   bool8_t tx_confirm_status;
   
   tx_confirm_status = CAN_cbFALSE;

  if(!(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl & 
  	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK))
   {
      tx_confirm_status = CAN_cbTRUE;
   }   
   return(tx_confirm_status);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Clear_IntPnd_Register(uint8_t channel_num)            *
 * Arguments passed  : channel_num                                             *
 * Return Value: none                                                          *
 * Function Description :This function clears all Int Pnd bits in CnINTS Reg   *
*******************************************************************************/
void HWCAN_Clear_IntPnd_Register (uint8_t channel_num)
{
   afcan_control_registers[channel_num]->INTS = AFCAN_CLEAR_ALL_INTERRUPT_PENDING_FLAG;
}



/********************************************************************************************/
/*									INLINE FUNCTIONS Defination								*/
/********************************************************************************************/
/*******************************************************************************
 * FunctionName  : HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt                    *
 * Arguments passed  : channel num                                             *
 * Return Value: none                                                          *
 * Function Description :This function clears Tx Int Pnd bit                   *
*******************************************************************************/
#if 0
void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt (uint8_t channel_num)
{
   afcan_control_registers[channel_num]->INTS = AFCAN_CLEAR_TRANSMIT_INTERRUPT_PENDING_FLAG;

   /* Clear RDy bit */
   Enable_Tx_Message_Buffer(channel_num);   
}
#endif
/* Separate APIs to reduce ISR Timing */

#if 0 //CAN_CH0_SELECTED
#pragma inline=forced
void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch0 (void)
{
   /* Clear transmit interrupt pending flag by writing 1 into INTS register
      at the bit position corresponding to the transmit buffer */
   afcan_control_registers[0]->INTS = AFCAN_CLEAR_TRANSMIT_INTERRUPT_PENDING_FLAG;

   /* Clear RDy bit */
   Enable_Tx_Message_Buffer(0);    
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced 
void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch1 (void)
{
   /* Clear transmit interrupt pending flag by writing 1 into INTS register
      at the bit position corresponding to the transmit buffer */
   afcan_control_registers[1]->INTS = AFCAN_CLEAR_TRANSMIT_INTERRUPT_PENDING_FLAG;
    
   /* Clear RDy bit */
   Enable_Tx_Message_Buffer(1);     
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced 
void HWCAN_Clear_Tx_IntPnd_Flag_On_Interrupt_Ch2 (void)
{
   /* Clear transmit interrupt pending flag by writing 1 into INTS register
     at the bit position corresponding to the transmit buffer */
   afcan_control_registers[2]->INTS = AFCAN_CLEAR_TRANSMIT_INTERRUPT_PENDING_FLAG;

   /* Clear RDy bit */
   Enable_Tx_Message_Buffer(2);
}
#endif

/*******************************************************************************
 * FunctionName  : HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt                     *
 * Arguments passed  : channel_num                                             *
 * Return Value: none                                                          *
 * Function Description :This function clears RX Int Pnd bit                   *
 *******************************************************************************/
//#pragma inline=forced
void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt (uint8_t channel_num, uint8_t rx_msg_obj)
{
   /* Clear receive interrupt pending flag by writing 1 into INTS register
     at the bit position corresponding to the transmit buffer */
   if( CAN_INVALID_MSG_NUMBER != rx_msg_obj )
   {
      afcan_control_registers[channel_num]->INTS = AFCAN_CLEAR_RECEIVE_INTERRUPT_PENDING_FLAG;
   }
}

/*              Separate APIs to reduce ISR Timing                         */
#if 0 //CAN_CH0_SELECTED
#pragma inline=forced
void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch0 (uint8_t rx_msg_obj)
{
   /* Clear receive interrupt pending flag by writing 1 into INTS register
     at the bit position corresponding to the transmit buffer */
   if( CAN_INVALID_MSG_NUMBER != rx_msg_obj )
   {
      afcan_control_registers[0]->INTS = AFCAN_CLEAR_RECEIVE_INTERRUPT_PENDING_FLAG;
   }
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch1 (uint8_t rx_msg_obj)
{
   /* Clear receive interrupt pending flag by writing 1 into INTS register
     at the bit position corresponding to the transmit buffer */
   if( CAN_INVALID_MSG_NUMBER != rx_msg_obj )
   {
      afcan_control_registers[1]->INTS = AFCAN_CLEAR_RECEIVE_INTERRUPT_PENDING_FLAG;
   }
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
void HWCAN_Clear_Rx_IntPnd_Flag_On_Interrupt_Ch2 (uint8_t rx_msg_obj)
{
   /* Clear receive interrupt pending flag by writing 1 into INTS register
     at the bit position corresponding to the transmit buffer */
   if( CAN_INVALID_MSG_NUMBER != rx_msg_obj )
   {
      afcan_control_registers[2]->INTS = AFCAN_CLEAR_RECEIVE_INTERRUPT_PENDING_FLAG;
   }
}
#endif

/*******************************************************************************
 * FunctonName      :  HWCAN_Get_Rx_Buffer_Number                              *
 * Arguments passed  : channel_num                                             *
 * Return Value      : buffer number of the hw buffer that received message    *
 * Functon Description : This function returns rx buff number                  *
 *******************************************************************************/
/* amit */
/* A check has been made for the buffer no. is it required???? */
//#pragma inline=forced 
uint8_t HWCAN_Get_Rx_Buffer_Number(uint8_t channel_num)
{
   uint8_t rx_buf_num;
   uint16_t temp_rgpt_16;
    
   /* Read RGPT regiater */
   temp_rgpt_16 = afcan_control_registers[channel_num]->RGPT;
   temp_rgpt_16 &= AFCAN_RGPT_MASK;
   rx_buf_num = (uint8_t) (temp_rgpt_16 >> AFCAN_RGPT_RS_8);
  
   /*Check for ROVF bit i.e receive history list overflow */
   if(temp_rgpt_16 & AFCAN_CHECK_ROVF)
   {
      /* Calling an application function to indicate that the receive history list is full */
      /*Clear ROVF bit*/
      afcan_control_registers[channel_num]->RGPT = AFCAN_CLEAR_ROVF;
   }
   if(temp_rgpt_16 & AFCAN_RHPM_SET_MASK)
   {
         rx_buf_num = CAN_INVALID_MSG_NUMBER;
   }
   return(rx_buf_num);  
}

/* Separate APIs to reduce ISR Timing */
#ifdef CAN_CH0_SELECTED
#pragma inline=forced 
uint8_t HWCAN_Get_Rx_Buffer_Number_Ch0(void)
{
   uint8_t rx_buf_num;
   uint16_t temp_rgpt_16;
    
   /* Read RGPT regiater */
   temp_rgpt_16 = afcan_control_registers[0]->RGPT;
   temp_rgpt_16 &= AFCAN_RGPT_MASK;
   rx_buf_num = (uint8_t)(temp_rgpt_16 >> AFCAN_RGPT_RS_8);
  
   /*Check for ROVF bit i.e receive history list overflow */
   if(temp_rgpt_16 & AFCAN_CHECK_ROVF)
   {
      /* Calling an application function to indicate that the receive history list is full */
      /*Clear ROVF bit*/
      afcan_control_registers[0]->RGPT = AFCAN_CLEAR_ROVF;
   }
   if(temp_rgpt_16 & AFCAN_RHPM_SET_MASK)
   {
         rx_buf_num = CAN_INVALID_MSG_NUMBER;
   }
   return(rx_buf_num);  
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced 
uint8_t HWCAN_Get_Rx_Buffer_Number_Ch1(void)
{
   uint8_t rx_buf_num, buf_num, int_pnd_index;
   uint16_t temp_rgpt_16;
    
   /* Read RGPT regiater */
   temp_rgpt_16 = afcan_control_registers[1]->RGPT;
   temp_rgpt_16 &= AFCAN_RGPT_MASK;
   rx_buf_num = (uint8_t) (temp_rgpt_16 >> AFCAN_RGPT_RS_8);
  
   /*Check for ROVF bit i.e receive history list overflow */
   if(temp_rgpt_16 & AFCAN_CHECK_ROVF)
   {
      /* Calling an application function to indicate that the receive history list is full */
      /*Clear ROVF bit*/
      afcan_control_registers[1]->RGPT = AFCAN_CLEAR_ROVF;
   }
   if(temp_rgpt_16 & AFCAN_RHPM_SET_MASK)
   {
         rx_buf_num = CAN_INVALID_MSG_NUMBER;
   }
   return(rx_buf_num);  
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced 
uint8_t HWCAN_Get_Rx_Buffer_Number_Ch2(void)
{
   uint8_t rx_buf_num, buf_num, int_pnd_index;
   uint16_t temp_rgpt_16;
    
   /* Read RGPT regiater */
   temp_rgpt_16 = afcan_control_registers[2]->RGPT;
   temp_rgpt_16 &= AFCAN_RGPT_MASK;
   rx_buf_num = (uint8_t) (temp_rgpt_16 >> AFCAN_RGPT_RS_8);
  
   /*Check for ROVF bit i.e receive history list overflow */
   if(temp_rgpt_16 & AFCAN_CHECK_ROVF)
   {
      /* Calling an application function to indicate that the receive history list is full */
      /*Clear ROVF bit*/
      afcan_control_registers[2]->RGPT = AFCAN_CLEAR_ROVF;
   }
   if(temp_rgpt_16 & AFCAN_RHPM_SET_MASK)
   {
         rx_buf_num = CAN_INVALID_MSG_NUMBER;
   }
   return(rx_buf_num);  
}
#endif

/*******************************************************************************
 * Function: HWCAN_Is_Message_Overwritten                                      *
 * Parameter(s): channel num, hw buf num                                       *
 * Return Value: cbTRUE if Message Overflow bit in                             *
 *               CAN Message Control Register is set, else cbFALSE             *
 * Description:This function reads Message Overflow bit in Message Control     *
 *  				Register,if set, it clears the bit and returns cbTRUE, 			 *
 *					else returns cbFALSE															 *
*******************************************************************************/
//#pragma inline=forced
can_boolean_t HWCAN_Is_Message_OverWritten (uint8_t channel_num, uint8_t hw_buf_num)
{
   can_boolean_t msg_overwritten;
   
   if(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_MOW_MASK)
   {
      afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_MOW;
      msg_overwritten = CAN_cbTRUE;
   }
   else
   {
      msg_overwritten = CAN_cbFALSE;
   }
   return(msg_overwritten);
}

/* Separate APIs to reduce ISR Timing */

#if 0 //CAN_CH0_SELECTED
#pragma _inline
can_boolean_t HWCAN_Is_Message_OverWritten_Ch0 (uint8_t hw_buf_num)
{
   can_boolean_t msg_overwritten;
   
   if(afcan_message_buffers_vcan[0]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_MOW_MASK)
   {
      afcan_message_buffers_vcan[0]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_MOW;
      msg_overwritten = CAN_cbTRUE;
   }
   else
   {
      msg_overwritten = CAN_cbFALSE;
   }
   return(msg_overwritten);
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
can_boolean_t HWCAN_Is_Message_OverWritten_Ch1 (uint8_t hw_buf_num)
{
   can_boolean_t msg_overwritten;
   
   if(afcan_message_buffers_vcan[1]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_MOW_MASK)
   {
      afcan_message_buffers_vcan[1]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_MOW;
      msg_overwritten = CAN_cbTRUE;
   }
   else
   {
      msg_overwritten = CAN_cbFALSE;
   }
   return(msg_overwritten);
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
can_boolean_t HWCAN_Is_Message_OverWritten_Ch2 (uint8_t hw_buf_num)
{
   bool8_t msg_overwritten;
   
   if(afcan_message_buffers_vcan[2]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_MOW_MASK)
   {
      afcan_message_buffers_vcan[2]->afcan_message_buffer[hw_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_MOW;
      msg_overwritten = CAN_cbTRUE;
   }
   else
   {
      msg_overwritten = CAN_cbFALSE;
   }
   return(msg_overwritten);
}
#endif

/******************************************************************************
 * FunctionName: Lock_Buffer                                                  *
 * Arguments passed  : rx_buf_num, mesasge buffer number to be locked         *
 * Return Value      : None                                                   *
 * Description:This routine locks receive buffer by clearing RDY bit of CnCTRL*
 *            register of the corresponding receive buffer. By doing so,no new*
 *            message will ovrewrite the message that is being currently read *
 ******************************************************************************/
#pragma inline=forced 
void HWCAN_Lock_Buffer(uint8_t channel_num, uint8_t rx_buf_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
      
   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl =
      AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
   }   
      /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
      //Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }
}

#ifdef CAN_CH0_SELECTED
#pragma inline=forced
void HWCAN_Lock_Buffer_Ch0(uint8_t rx_buf_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
      
   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl =
      AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
   }   
      /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
    //  Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
void HWCAN_Lock_Buffer_Ch1(uint8_t rx_buf_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
      
   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl =
      AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
   }   
      /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
     // Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
void HWCAN_Lock_Buffer_Ch2(uint8_t rx_buf_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;
      
   /* untill the rdy bit is clear be in this loop */
   while( (afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl & 
   	AFCAN_MSSG_BUFF_CTRL_RDY_SET_MASK) && ( --TimeoutCounter_uint32_t > 0L ) )
   {
      /* Clear RDY bit */
      afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl =
      AFCAN_MSSG_BUFF_CTRL_CLEAR_RDY;
   }   
      /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t ) 
   {
     // Appl_Could_Not_Make_RDY_Bit_Low(); /* May be to set DTC code */       
   }
}
#endif

/******************************************************************************
 * FunctionName: UnLock_Buffer                                                *
 * Arguments passed  : rx_buf_num, mesasge buffer number to be un locked      *
 * Return Value      : None                                                   *
 * Description:This routine unlocks receive buffer by setting RDY bit of CTRL *
 *        register of the corresponding receive buffer. By doing so,          *
 *        next new message is allowed to be received                          *
 ******************************************************************************/
#pragma inline=forced 
void HWCAN_UnLock_Buffer(uint8_t channel_num, uint8_t rx_buf_num)
{
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_RDY;
		    
   /* Clear DN bit (i.e. no data in the message buffer) */
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_DN;
}

#ifdef CAN_CH0_SELECTED
#pragma inline=forced
void HWCAN_UnLock_Buffer_Ch0(uint8_t rx_buf_num)
{
   afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_RDY;
		    
   /* Clear DN bit (i.e. no data in the message buffer) */
   afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_DN;
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
void HWCAN_UnLock_Buffer_Ch1(uint8_t rx_buf_num)
{
   afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_RDY;
		    
   /* Clear DN bit (i.e. no data in the message buffer) */
   afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_DN;		    
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
void HWCAN_UnLock_Buffer_Ch2(uint8_t rx_buf_num)
{
   afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_RDY;
		    
   /* Clear DN bit (i.e. no data in the message buffer) */
   afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_CLEAR_DN;		    
}
#endif


/*******************************************************************************
 * FunctionName     : HWCAN_Get_Rx_ID                                          *
 * Arguments passed  : channel num, Rx buf num                                 *
 * Return Value      :Received ID                                              *
 * Functon Description :This function returns content of ID register           *
 *                      corresponding to the received message                  *
 *******************************************************************************/
#pragma inline=forced
void HWCAN_Get_Rx_ID(uint8_t channel_num, uint8_t rx_buf_num)
{
   Msg_ID_T msg_id;
   Msg_ID_T mssg_id_temp;
   
   HWCAN_Lock_Buffer(channel_num, rx_buf_num);

   if( STANDARD_ID == HWCAN_Rx_Init_Tables[channel_num][rx_buf_num].ID_type)
   {
      msg_id = (canuint32_t)((afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_idh) >> AFCAN_IDH_RS_2);
   }
   else
   {
      /* Read lower 16 bits of extended message id */
      msg_id = (canuint32_t)(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_idl);
   
      /* Read IDH register */
      mssg_id_temp = (canuint32_t)(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_idh);

      /* Mask upper 13 bits */
      mssg_id_temp &= AFCAN_MSSG_BUFF_IDH_MASK;
      mssg_id_temp <<= AFCAN_IDH_LS_16;

      /* load 29bits ID in msg_id */  
      msg_id |= mssg_id_temp;
   }
   /* Update Rx_Msg_Info with the received ID */
   RX_Msg_Info[channel_num].rx_msg_id = msg_id;
}

#ifdef CAN_CH0_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_ID_Ch0(uint8_t rx_buf_num)
{
   canuint32_t msg_id, mssg_id_temp;
   
   HWCAN_Lock_Buffer_Ch0(rx_buf_num);

   if( STANDARD_ID == HWCAN_Rx_Init_Table_Ch0[rx_buf_num-1].ID_type)
   {
      msg_id = (canuint32_t)((afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_idh) >> AFCAN_IDH_RS_2);
   }
   else
   {
      /* Read lower 16 bits of extended message id */
      msg_id = (canuint32_t)(afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_idl);
   
      /* Read IDH register */
      mssg_id_temp = (canuint32_t)(afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_idh);

      /* Mask upper 13 bits */
      mssg_id_temp &= (canuint32_t)AFCAN_MSSG_BUFF_IDH_MASK;
      mssg_id_temp <<= AFCAN_IDH_LS_16;

      /* load 29bits ID in msg_id */  
      msg_id |= mssg_id_temp;
   }
   /* Read the ID of the received mesasge */
   RX_Msg_Info[0].rx_msg_id = msg_id;
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_ID_Ch1(uint8_t rx_buf_num)
{
   canuint32_t msg_id, mssg_id_temp;
   HWCAN_Lock_Buffer_Ch1(rx_buf_num);

   if( STANDARD_ID == HWCAN_Rx_Init_Table_Ch1[rx_buf_num-1].ID_type)
   {
      msg_id = (canuint32_t)((afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_idh) >> AFCAN_IDH_RS_2);
   }
   else
   {
      /* Read lower 16 bits of extended message id */
      msg_id = (canuint32_t)(afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_idl);
   
      /* Read IDH register */
      mssg_id_temp = (canuint32_t)(afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_idh);

      /* Mask upper 13 bits */
      mssg_id_temp &= AFCAN_MSSG_BUFF_IDH_MASK;
      mssg_id_temp <<= AFCAN_IDH_LS_16;

      /* load 29bits ID in msg_id */  
      msg_id |= mssg_id_temp;
   }
   /* Read the ID of the received mesasge */
   RX_Msg_Info[1].rx_msg_id = msg_id;
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_ID_Ch2(uint8_t rx_buf_num)
{
   uint32_t msg_id, mssg_id_temp;
   HWCAN_Lock_Buffer_Ch2(rx_buf_num);

   if( STANDARD_ID == HWCAN_Rx_Init_Table_Ch2[rx_buf_num-1].ID_type)
   {
      msg_id = (canuint32_t)((afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_idh) >> AFCAN_IDH_RS_2);
   }
   else
   {
      /* Read lower 16 bits of extended message id */
      msg_id = (canuint32_t)(afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_idl);
   
      /* Read IDH register */
      mssg_id_temp = (canuint32_t)(afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_idh);

      /* Mask upper 13 bits */
      mssg_id_temp &= AFCAN_MSSG_BUFF_IDH_MASK;
      mssg_id_temp <<= AFCAN_IDH_LS_16;

      /* load 29bits ID in msg_id */  
      msg_id |= mssg_id_temp;
   }
   /* Read the ID of the received mesasge */
   RX_Msg_Info[2].rx_msg_id = msg_id;
}
#endif

/*******************************************************************************
 * FunctionName  :HWCAN_Get_Rx_IDtype                                          *
 * Arguments passed  : channel num, Rx buf num                                 *
 * Return Value      :ID Type of received message                              *
 * Functon Description :This function reads IDE bit of ID register             *
 *                      corresponding to the received message                  *
 *******************************************************************************/
#pragma inline=forced
void HWCAN_Get_Rx_IDtype(uint8_t channel_num, uint8_t rx_buf_num)
{
   if(afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_idh 
                                                & AFCAN_MSSG_BUFF_IDE_MASK)
   {
      RX_Msg_Info[channel_num].rx_msg_id_type = EXTENDED_ID; 
   }
   else                                                                
   {
      RX_Msg_Info[channel_num].rx_msg_id_type = STANDARD_ID;
   }
}

/*              Separate APIs to reduce ISR Timing                         */
#ifdef CAN_CH0_SELECTED
#pragma inline=forced 
void HWCAN_Get_Rx_IDtype_Ch0(uint8_t rx_buf_num)
{
   if(afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_idh 
                                                & AFCAN_MSSG_BUFF_IDE_MASK)
   {
      RX_Msg_Info[0].rx_msg_id_type = EXTENDED_ID; 
   }
   else                                                                
   {
      RX_Msg_Info[0].rx_msg_id_type = STANDARD_ID;
   }
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_IDtype_Ch1(uint8_t rx_buf_num)
{
   if(afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_idh 
                                                & AFCAN_MSSG_BUFF_IDE_MASK)
   {
      RX_Msg_Info[1].rx_msg_id_type = EXTENDED_ID; 
   }
   else                                                                
   {
      RX_Msg_Info[1].rx_msg_id_type = STANDARD_ID;
   }
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_IDtype_Ch2(uint8_t rx_buf_num)
{
   if(afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_idh 
                                                & AFCAN_MSSG_BUFF_IDE_MASK)
   {
      RX_Msg_Info[2].rx_msg_id_type = EXTENDED_ID; 
   }
   else                                                                
   {
      RX_Msg_Info[2].rx_msg_id_type = STANDARD_ID;
   }
}
#endif
/*******************************************************************************
 * FunctionName  :HWCAN_Get_Rx_DLC                                             *
 * Arguments passed  : channel num, Rx buf num                                 *
 * Return Value      :DLC of received message                                  *
 * Functon Description :This function returns the dlcfrom the DLC register     *
 *                      corresponding to the received message                  *
*******************************************************************************/
#pragma inline=forced 
void HWCAN_Get_Rx_DLC(uint8_t channel_num,uint8_t rx_buf_num)
{
   RX_Msg_Info[channel_num].rx_msg_dlc = 
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf_num].mssg_buff_dlc;
}

/*              Separate APIs to reduce ISR Timing                         */
#ifdef CAN_CH0_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_DLC_Ch0(uint8_t rx_buf_num)
{
   RX_Msg_Info[0].rx_msg_dlc = 
   afcan_message_buffers_vcan[0]->afcan_message_buffer[rx_buf_num].mssg_buff_dlc;
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_DLC_Ch1(uint8_t rx_buf_num)
{
   RX_Msg_Info[1].rx_msg_dlc = 
   afcan_message_buffers_vcan[1]->afcan_message_buffer[rx_buf_num].mssg_buff_dlc;
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
void HWCAN_Get_Rx_DLC_Ch2(uint8_t rx_buf_num)
{
   RX_Msg_Info[2].rx_msg_dlc = 
   afcan_message_buffers_vcan[2]->afcan_message_buffer[rx_buf_num].mssg_buff_dlc;
}
#endif


/*******************************************************************************
 * Function:void HWCAN_Get_Rx_Msg_Info                                         *
 * Parameter(s): channel_num,                                                  *
 * Return Value: Rx_Msg_Info                                                   *
 * Description: This function updates Rx_Msg_Info structure with Received ID   *
 *                Received ID type, and received dlc                           *
*******************************************************************************/
//#pragma inline=forced
RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info (uint8_t channel_number)
{
   /* This variable is used to unlock the last buffer which received mssg */
   static uint8_t previous_rx_buf_num = 0xFF;
   
   if(0xFF != previous_rx_buf_num)
   {
      /* Call function to unlosk the last received message */
      HWCAN_UnLock_Buffer(channel_number, previous_rx_buf_num);
	  
	  /* Reset the variable */ 
	  previous_rx_buf_num = 0xFF;
   }
   
   RX_Msg_Info[channel_number].hw_rx_buf_num = HWCAN_Get_Rx_Buffer_Number(channel_number);
   
   if(CAN_INVALID_MSG_NUMBER != RX_Msg_Info[channel_number].hw_rx_buf_num)
   {
      /* The variable is updated only if the hw_rx_buf is valid */
      previous_rx_buf_num = RX_Msg_Info[channel_number].hw_rx_buf_num;      
      
      HWCAN_Get_Rx_ID(channel_number, RX_Msg_Info[channel_number].hw_rx_buf_num);

	  HWCAN_Get_Rx_IDtype(channel_number, RX_Msg_Info[channel_number].hw_rx_buf_num);

      HWCAN_Get_Rx_DLC(channel_number, RX_Msg_Info[channel_number].hw_rx_buf_num);
   } 
 
   return(&RX_Msg_Info[channel_number]);
}

#ifdef CAN_CH0_SELECTED
RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info_Ch0 (void)
{
   /* This variable is used to unlock the last buffer which received mssg */
   static uint8_t previous_rx_buf_num = 0xFF;
   
   if(0xFF != previous_rx_buf_num)
   {
      /* Call function to unlosk the last received message */
      HWCAN_UnLock_Buffer_Ch0(previous_rx_buf_num);
	  
	  /* Reset the variable */ 
   }

   RX_Msg_Info[0].hw_rx_buf_num = HWCAN_Get_Rx_Buffer_Number_Ch0();
   if(CAN_INVALID_MSG_NUMBER != RX_Msg_Info[0].hw_rx_buf_num)
   {
      HWCAN_Get_Rx_ID_Ch0(RX_Msg_Info[0].hw_rx_buf_num);

   	  HWCAN_Get_Rx_IDtype_Ch0(RX_Msg_Info[0].hw_rx_buf_num);

      HWCAN_Get_Rx_DLC_Ch0(RX_Msg_Info[0].hw_rx_buf_num);
   } 
   previous_rx_buf_num = RX_Msg_Info[0].hw_rx_buf_num;
   return(&RX_Msg_Info[0]);
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info_Ch1 (void)
{
   /* This variable is used to unlock the last buffer which received mssg */
   static uint8_t previous_rx_buf_num = 0xFF;
   
   if(0xFF != previous_rx_buf_num)
   {
      /* Call function to unlosk the last received message */
      HWCAN_UnLock_Buffer_Ch1(previous_rx_buf_num);
	  
	  /* Reset the variable */ 
	  previous_rx_buf_num = 0xFF;
   } 
     
   RX_Msg_Info[1].hw_rx_buf_num = HWCAN_Get_Rx_Buffer_Number_Ch1();
   if(CAN_INVALID_MSG_NUMBER != RX_Msg_Info[1].hw_rx_buf_num)
   {
      HWCAN_Get_Rx_ID_Ch1(RX_Msg_Info[1].hw_rx_buf_num);

   	  HWCAN_Get_Rx_IDtype_Ch1(RX_Msg_Info[1].hw_rx_buf_num);

      HWCAN_Get_Rx_DLC_Ch1(RX_Msg_Info[1].hw_rx_buf_num);
   }  
 
   return(&RX_Msg_Info[1]);
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
RX_Msg_Info_T* HWCAN_Get_Rx_Msg_Info_Ch2 (void)
{
   /* This variable is used to unlock the last buffer which received mssg */
   static uint8_t previous_rx_buf_num = 0xFF;
   
   if(0xFF != previous_rx_buf_num)
   {
      /* Call function to unlosk the last received message */
      HWCAN_UnLock_Buffer_Ch2(previous_rx_buf_num);
	  
	  /* Reset the variable */ 
	  previous_rx_buf_num = 0xFF;
   }    
   
   RX_Msg_Info[2].hw_rx_buf_num = HWCAN_Get_Rx_Buffer_Number_Ch2();
   if(CAN_INVALID_MSG_NUMBER != RX_Msg_Info[2].hw_rx_buf_num)
   {
      HWCAN_Get_Rx_ID_Ch2(RX_Msg_Info[2].hw_rx_buf_num);

	  HWCAN_Get_Rx_IDtype_Ch2(RX_Msg_Info[2].hw_rx_buf_num);

      HWCAN_Get_Rx_DLC_Ch2(RX_Msg_Info[2].hw_rx_buf_num);
   } 
 
   return(&RX_Msg_Info[2]);

}
#endif


/*******************************************************************************
 * FunctionName  :HWCAN_Get_Rx_Data_Pointer                                    *
 * Arguments passed  : channel num, Rx buf num                                 *
 * Return Value      :data pointer                                             *
 * Functon Description :This function provides data pointer of the h/w buffer  *
*******************************************************************************/
//#pragma inline=forced
uint8_t* HWCAN_Get_Rx_Data_Pointer(uint8_t channel_num, uint8_t hw_rx_buf_num)
{
   return((uint8_t *)afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[hw_rx_buf_num].mssg_buff_data);
}

/*              Separate APIs to reduce ISR Timing                           */
#if 0 //CAN_CH0_SELECTED
#pragma _inline
uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch0(uint8_t hw_rx_buf_num)
{
   return((uint8_t *)afcan_message_buffers_vcan[0]->afcan_message_buffer[hw_rx_buf_num].mssg_buff_data);
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch1(uint8_t hw_rx_buf_num)
{
   return((uint8_t *)afcan_message_buffers_vcan[1]->afcan_message_buffer[hw_rx_buf_num].mssg_buff_data);
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
uint8_t* HWCAN_Get_Rx_Data_Pointer_Ch2(uint8_t hw_rx_buf_num)
{
   return((uint8_t *)afcan_message_buffers_vcan[2]->afcan_message_buffer[hw_rx_buf_num].mssg_buff_data);
}
#endif

/*******************************************************************************
 * FunctionName  : HWCAN_Mask_Used_For_Rx_Buffer                               *
 * Arguments passed  : channel num, hw rx buf                                  *
 * Return Value: cbTRUE if Mask used for the hw Rx buffer passed as parameter, *
 * else cbFALSE                                                                *
 * Function Description:This API returns mask_is_needed flag in Rx Init Table  *
*******************************************************************************/
//#pragma inline=forced
bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer(uint8_t channel_num, uint8_t hw_rx_buf)
{
   bool8_t mask_needed = CAN_cbFALSE;
   
   if(INVALID_MASK_NO != HWCAN_Rx_Init_Tables[channel_num][hw_rx_buf].mask_no)
   {
      mask_needed = CAN_cbTRUE;
   }
   else
   {
      mask_needed = CAN_cbFALSE;
   }
   return(mask_needed);
}


/* Seperate API's for different channels */
#ifdef CAN_CH0_SELECTED
//#pragma inline=forced
bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch0(uint8_t hw_rx_buf)
{
   bool8_t mask_needed = CAN_cbFALSE;
   
   if(INVALID_MASK_NO != HWCAN_Rx_Init_Tables[0][hw_rx_buf].mask_no)
   {
      mask_needed = CAN_cbTRUE;
   }
   else
   {
      mask_needed = CAN_cbFALSE;
   }
   return(mask_needed);

}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch1(uint8_t hw_rx_buf)
{
   bool8_t mask_needed = CAN_cbFALSE;
   
   if(INVALID_MASK_NO != HWCAN_Rx_Init_Tables[1][hw_rx_buf].mask_no)
   {
      mask_needed = CAN_cbTRUE;
   }
   else
   {
      mask_needed = CAN_cbFALSE;
   }
   return(mask_needed);
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
bool8_t HWCAN_Is_Mask_Used_For_Rx_Buffer_Ch2(uint8_t hw_rx_buf)
{
   bool8_t mask_needed = CAN_cbFALSE;
   
   if(INVALID_MASK_NO != HWCAN_Rx_Init_Tables[2][hw_rx_buf].mask_no)
   {
      mask_needed = CAN_cbTRUE;
   }
   else
   {
      mask_needed = CAN_cbFALSE;
   }
   return(mask_needed);

}
#endif

/*******************************************************************************
 * FunctionName  : HWCAN_Get_Tx_Buf_Number                                     *
 * Arguments passed  : channel num                                             *
 * Return Value: uint8_t                                                       *
 * Function Description:This API returns Tx buf no. used by the channel passed *
*******************************************************************************/
//#pragma inline=forced 
uint8_t HWCAN_Get_Tx_Buf_Number(uint8_t channel_num)
{
   return(Tx_Msg_Obj[channel_num]);
}

/*              Separate Channel wise APIs to reduce ISR Timing            */
#ifdef CAN_CH0_SELECTED
//#pragma inline=forced
uint8_t HWCAN_Get_Tx_Buf_Number_Ch0(void)
{
   return(Tx_Msg_Obj[0]);
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
uint8_t HWCAN_Get_Tx_Buf_Number_Ch1(void)
{
   return(Tx_Msg_Obj[1]);
}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
uint8_t HWCAN_Get_Tx_Buf_Number_Ch2(void)
{
   return(Tx_Msg_Obj[2]);
}
#endif

/*******************************************************************************
 * FunctionName  : HWCAN_Get_First_Rx_Buf_Number                               *
 * Arguments passed  : channel num                                             *
 * Return Value: uint8_t                                                       *
 * Function Description:This API returns the msg object number of the first Rx *
 * message for the  channel number passed                                      *
*******************************************************************************/
//#pragma inline=forced 
uint8_t HWCAN_Get_First_Rx_Buf_Number(uint8_t channel_num)
{
   return(HWCAN_Rx_Init_Tables[channel_num][FIRST_RX_MSG_BUF_INDEX].rx_message_buffer_num);
}

/*              Separate Channel wise APIs to reduce ISR Timing            */
#ifdef CAN_CH0_SELECTED
//#pragma inline=forced
uint8_t HWCAN_Get_First_Rx_Buf_Number_Ch0(void)
{
   return(HWCAN_Rx_Init_Tables[0][FIRST_RX_MSG_BUF_INDEX].rx_message_buffer_num);
}
#endif

#ifdef CAN_CH1_SELECTED
#pragma inline=forced
uint8_t HWCAN_Get_First_Rx_Buf_Number_Ch1(void)
{
 return(HWCAN_Rx_Init_Tables[1][FIRST_RX_MSG_BUF_INDEX].rx_message_buffer_num);

}
#endif

#ifdef CAN_CH2_SELECTED
#pragma inline=forced
uint8_t HWCAN_Get_First_Rx_Buf_Number_Ch2(void)
{
   return(HWCAN_Rx_Init_Tables[2][FIRST_RX_MSG_BUF_INDEX].rx_message_buffer_num);
}
#endif

/* amit */
/* these functions can be made extern instead of inline, as these r not called in the ISR */
/*******************************************************************************
  * FunctionName: HWCAN_Disable_All_CAN_Interrupts                              *
  * Arguments passed  : channel number                                          *
  * Return Value      : None                                                    *
  * Description : This routine disables all CAN interrupts                      *
 *******************************************************************************/
#if 0
#pragma inline=forced
void HWCAN_Disable_All_CAN_Interrupts(uint8_t channel_num)
{
/* To mask/unmask the interrupts,access xxICn register as bit wise only */
   CAN0MASKLOW->F.recMask = 1;    
   CAN0MASKLOW->F.errMask = 1;
  
   CAN0MASKHIGH->F.trxMask = 1;
   

  #ifdef CAN_WAKEUP_MODE_AVAILABLE

   CAN0MASKLOW->F.wupMask = 1;

  #endif
}


/*******************************************************************************
 * FunctionName: HWCAN_Enable_All_CAN_Interrupts                               *
 * Arguments passed  : channel number                                          *
 * Return Value      : None                                                    *
 * Description : This routine enables all CAN interrupts                       *
 *******************************************************************************/
#pragma inline=forced
void HWCAN_Enable_All_CAN_Interrupts(uint8_t channel_num)
{
   canuint8_t rx_buf, Param_Table_Index;

   afcan_control_registers[channel_num]->IE = AFCAN_IE_ENABLE_INTERRUPTS;
#if 0
   afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[Tx_Msg_Obj[channel_num]].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_IE;  
   /* Enables all CAN interrupts */
   for(Param_Table_Index=0; Param_Table_Index < Size_Of_HWCAN_Rx_Init_Tables[channel_num];
                                                                    Param_Table_Index ++) 
   {
      rx_buf = HWCAN_Rx_Init_Tables[channel_num][Param_Table_Index].rx_message_buffer_num;
	  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_IE;
	  afcan_message_buffers_vcan[channel_num]->afcan_message_buffer[rx_buf].mssg_buff_ctrl = AFCAN_MSSG_BUFF_CTRL_SET_RDY;
   }
#endif
 
   CAN0MASKLOW->F.recMask = 0;    
   CAN0MASKLOW->F.errMask = 0;
  
   CAN0MASKHIGH->F.trxMask = 0;
   


  #ifdef CAN_WAKEUP_MODE_AVAILABLE

   CAN0MASKLOW->F.wupMask = 0;

  #endif
}
#endif
/*******************************************************************************
 * FunctionName: HWCAN_Enable_CAN_Interrupt                                    *
 * Arguments passed  : channel number, CAN_Int_Type                            *
 * Return Value      : None                                                    *
 * Description : This routine enables CAN interrupts according to the 		   *
 * 					  parameters passed                                        *
 *******************************************************************************/
#pragma inline=forced
void HWCAN_Enable_CAN_Interrupt(uint8_t channel_num, uint8_t CAN_Int_Type)
{

}


/*******************************************************************************
 * FunctionName: HWCAN_Disnable_CAN_Interrupt                                  *
 * Arguments passed  : channel number, CAN_Int_Type                            *
 * Return Value      : None                                                    *
 * Description : This routine disables CAN interrupts according to the 		   *
 * 					  parameters passed                                        *
 *******************************************************************************/
#pragma inline=forced
void HWCAN_Disable_CAN_Interrupt(uint8_t channel_num, uint8_t CAN_Int_Type)
{
		
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file for      *
 *                 Sandeep       NEC v850 Fx3 
 * 2   10-Mar-2010 Ashwini       Renamed afcan_message_buffers as 
 *                               afcan_message_buffers_vcan.                       
 *****************************************************************************/
