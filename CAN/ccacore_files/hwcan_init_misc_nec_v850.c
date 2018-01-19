/******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS: Prakash, Sandeep                                                  *
 * Project: CCA - HWCAN                                                       *
 * File Name:  hwcan_init_misc_nec_v850.c                                     *
 * File Description:                                                          *
 * This file contains the generic APIs related to Initialization, Error       *
 * handling and Power Moding functionalities provided to the CAN Driver.      *
 *                                                                            *
 * These generic APIs are translated to specific hardware accesses on the     *
 * NEC V850 CAN controller. HWCAN Layer provides accesses to the on-chip      *
 * Control/Status registers and message buffers                               *
 * Micro Description:                                                         *
 * The HWCAN layer is written for both NEC-V850ES/FG2 and NEC-V850ES/FJ3      *
 * micro.                                                                     *
 *  >>>>> If NEC-V850ES/FG2 micro is used the define "NEC_V850_FG2" macro in  *
 *        hwcan_nec_v850_config.h                                             *
 *  >>>> If NEC-V850ES/FJ3 is used then undef "NEC_V850_FG2" macro in         *
 *       hwcan_nec_v850_config.h                                              *
 *  These two micro differs only in the base address of interrupt             *
 *  control registers and the number of CAN channels available                *
 *****************************************************************************/


#include "hwcan_init_misc_nec_v850.h"
#include "hwcan_tx_rx_nec_v850.h"
#include "io78f1840_80.h"
#include "io78f1840_80_ext.h"


/******************************************************************************/
/*                                              Local Macro Definitions                               */
/******************************************************************************/

/* Macros for baud rate */
#define AFCAN_GMCS_DEFAULT                          AFCAN_SELECT_CAN_MODULE_SYSTEM_CLOCK
#define AFCAN_GMCTRL_DEFAULT                                                      0x0100
#define AFCAN_GMCTRL_GOM_SET_M                                                                                                                                   0x0001
#define AFCAN_GMCTRL_CLEAR_GOM                                                                                                                                   0x0001

/* Macros for CAN module control registers (CTRL) */
#define AFCAN_INITIALIZATION_MODE_MASK                                            0x0007
#define AFCAN_CTRL_INITIALIZATION_MODE                                                0x001F
#define AFCAN_CTRL_INIT_SET                                                       0x0007
#define AFCAN_CTRL_INIT_MODE_MASK                                                 0x0000
#define AFCAN_CTRL_TSTAT_MASK                                                     0x0100
#define AFCAN_CTRL_RSTAT_MASK                                                     0x0200
#define AFCAN_CTRL_SLEEP_MODE                                                     0x0810
#define AFCAN_CTRL_SLEEP_MODE_MASK                                                0x0008
#define AFCAN_CLEAR_CTRL_SLEEP_MODE                                               0x0018
#define AFCAN_CLEAR_CTRL_SLEEP_MODE_SET                                           0x0018
#define AFCAN_CLEAR_CTRL_SLEEP_MODE_MASK                                          0x0000
#define AFCAN_CTRL_CCERC_SET                                                      0x8000
#define AFCAN_CTRL_NORMAL_MODE                                                    0x013E
#define AFCAN_CTRL_NORMAL_MODE_MASK                                               0x0001
#define AFCAN_MSSG_BUFF_CTRL_SET_RDY                                              0x0100

/* Macros for CAN module information register (INFO) */
#define AFCAN_BUS_OFF_MASK                                                          0x10
#define AFCAN_TX_ERR_WARNING_MASK                                                   0x04
#define AFCAN_RX_ERR_WARNING_MASK                                                   0x01
#define AFCAN_TX_ERR_PASSIVE_MASK                                                   0x0C
#define AFCAN_RX_ERR_PASSIVE_MASK                                                   0x03
#define AFCAN_TX_ERR_COUNT_MASK                                                   0x00FF
#define AFCAN_RX_ERR_COUNT_MASK                                                   0x7F00
#define TECS_COUNT_INVALID                                                          0xFF
#define RECS_COUNT_INVALID                                                          0xFF
#define AFCAN_RECEPT_ERR_PASSIVE_MASK                                             0x8000
#define AFCAN_ERC_RS_8                                                                 8

/* Macros for Interrupt status register (INTS) */
#define AFCAN_INTS_DEFAULT                                                        0x003F
#define AFCAN_CAN_ERROR_STATUS_INTERRUPT_MASK                                     0x0004
#define AFCAN_CLEAR_CAN_ERROR_STATUS_INTERRUPT                                    0x0004
#define AFCAN_PROTOCOL_ERROR_STATUS_INTERRUPT_MASK                                0x0008
#define AFCAN_CLEAR_PROTOCOL_ERROR_STATUS_INTERRUPT                               0x0008
#define AFCAN_CLEAR_WAKE_UP_INTERRUPT_STATUS                                      0x0020
#define AFCAN_IE_ENABLE_INTERRUPTS                                                0x3F00


#define AFCAN_LEC_DEFAULT                                                           0x00
#define AFCAN_RGPT_DEFAULT                                                        0x0001
#define AFCAN_TGPT_DEFAULT                                                        0x0001

/* Macros to set priority of thr interrupts */
#define AFCAN_TX_INTERRUPT_PRIORITY                                                 0x02
#define AFCAN_ERR_INTERRUPT_PRIORITY                                                0x00
#define AFCAN_RX_INTERRUPT_PRIORITY                                                 0x01
#define AFCAN_WAKE_UP_INTERRUPT_PRIORITY                                            0x03


/* Macro's for assigning address to harware registers */
#define BPC     (*((volatile uint16_t *)0xfffff064))
#define VSWC    (*((volatile uint8_t *)0xfffff06e))

/* Macros for assigning address to I/O port */
#define OCDM    (*((volatile uint8_t *)0xfffff9fc))
#define PMC3L   (*((volatile uint8_t *)0xfffff446))
#define PFCE3L  (*((volatile uint8_t *)0xfffff706))
#define PFC3L   (*((volatile uint8_t *)0xfffff466))

/* transreceiver mode setting */
#define P3L (*((volatile uint8_t *)0xfffff406))

#define PM3L (*((volatile uint8_t *)0xfffff426))

#define PMC6H   (*((volatile uint8_t *)0xfffff44d))
#define PM6H    (*((volatile uint8_t *)0xfffff42d))
#define P6H     (*((volatile uint8_t *)0xfffff40d))
#if 0
volatile xxICn_IntReqLow_T    *CAN0INTREQLOW     = (xxICn_IntReqLow_T *)AFCAN_CH0_INTERRUPT_REQUEST_FLAG_REGISTER_LOW            ;
volatile xxICn_IntReqHigh_T   *CAN0INTREQHIGH    = (xxICn_IntReqHigh_T * )AFCAN_CH0_INTERRUPT_REQUEST_FLAG_REGISTER_HIGH           ;
volatile xxICn_IntPriLow_T    *CAN0INTPRIOLOW    = (xxICn_IntPriLow_T *)AFCAN_CH0_INTERRUPT_PRIORITY_0_SELECTION_REGISTER_LOW    ;
volatile xxICn_IntPriHigh_T   *CAN0INTPRIOHIGH   = (xxICn_IntPriHigh_T *)AFCAN_CH0_INTERRUPT_PRIORITY_0_SELECTION_REGISTER_HIGH   ;
volatile xxICn_IntTxPriLow_T  *CAN0TXINTPRIOLOW  = (xxICn_IntTxPriLow_T *)AFCAN_CH0_INTERRUPT_PRIORITY_1_SELECTION_REGISTER_LOW    ;
volatile xxICn_IntTxPriHigh_T *CAN0TXINTPRIOHIGH = (xxICn_IntTxPriHigh_T *)AFCAN_CH0_INTERRUPT_PRIORITY_1_SELECTION_REGISTER_HIGH   ;
volatile xxICn_IntMaskLow_T   *CAN0MASKLOW       = (xxICn_IntMaskLow_T *)AFCAN_CH0_INTERRUPT_MASK_FLAG_REGISTER_LOW               ;
volatile xxICn_IntMaskHigh_T  *CAN0MASKHIGH      = (xxICn_IntMaskHigh_T *)AFCAN_CH0_INTERRUPT_MASK_FLAG_REGISTER_HIGH              ;
#endif




/*===========================================================================*/
/*              Local Type declarations (enum, struct, union, typedef)                   */
/*===========================================================================*/


/*===========================================================================*/
/*                                      Exported variable defination                                                     */
/*===========================================================================*/

/*===========================================================================*/
/*                                      Local variable defination                                                                */
/*===========================================================================*/



/*******************************************************************************
* Function macros                                                                                  *
********************************************************************************/

/******************************************************************************/
/* FunctionName      : AFCAN_BTR_DEFAULT                                      */
/* Arguments passed  : None                                                   */
/* Return Value      : None                                                   */
/* Function Description : Set BTR value from HWCAN_Bit_Timing_Table table         */
/******************************************************************************/

#define AFCAN_BTR_DEFAULT()     (HWCAN_Bit_Timing_Table[index].sjw | \
        HWCAN_Bit_Timing_Table[index].tseg1 | HWCAN_Bit_Timing_Table[index].tseg2)

/******************************************************************************/
/*                           FUNCTION DEFINITIONS                             */
/******************************************************************************/

/*******************************************************************************
 * Function Name : Initialize_CAN_Ports                                        *
 * Arguments passed  : None                                                    *
 * Return Value : None                                                         *
 * Description : This function is called by CAN handler to initialize CAN ports*
 ******************************************************************************/

void Initialize_CAN_Ports(uint8_t channel_number)
{
	
#if 0
    // Configure the peripheral clock for CAN
	PCKSEL_bit.no4 = 1;

	// Configure Serial communication pin select register (STSEL)
	STSEL_bit.no7 = 1;		// P10, P11 used for CAN
   	STSEL_bit.no6 = 0;		// TMCAN - TI14 pin input

	// Set the port pins P10 and P11 for Alternate function as CAN.
	PM1_bit.no0=0;	// TxD - Set as output
	PM1_bit.no1=1;	// Rxd - Set as input
	P1_bit.no0=1;
	P1_bit.no1=1;
#endif
#if 1
   if(channel_number == 0)
   {
      PCKSEL_bit.no4 = 1;

      STSEL_bit.no7 = 0;
      STSEL_bit.no6 = 0;

      //MCU_CAN_TXD
      PM7_bit.no2 = 0;
      P7_bit.no2 = 1;

      //MCU_CAN_RXD
      PM7_bit.no3 = 1;
      //P7_bit.no3 = 1;

      //CAN_STB_B
//      PM0_bit.no0 = 0;
//      P0_bit.no0 = 0;
	  
      //CAN_STB_B
      //P13_bit.no0 = 0;
	  
   }

#endif
}

/*******************************************************************************
 * Function Name : HWCAN_Init_Misc                                             *
 * Arguments passed  : channel num                                             *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Driver to initialize     *
 *               the H/W features which are not channel dependent                  *
 ******************************************************************************/
void HWCAN_Init_Misc(void)
{
}

/*******************************************************************************
 * Function Name : HWCAN_Init_For_Additional_features                          *
 * Arguments passed  : channel num                                             *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Driver to initialize     *
 *               the required control registers for handling the additional    *
 *               features of the CAn controller,if any                         *
 ******************************************************************************/
void HWCAN_Init_For_Additional_features(uint8_t channel_num)
{

}

/*******************************************************************************
 * Function Name : HWCAN_Init_All_Reg                                          *
 * Arguments passed  : channel num                                             *
 * Return Value : None                                                         *
 * Description : This function would be called by CAN Driver to initialize     *
 *               all the control registers to their respectiove reset values in*
 *               order to make sure the proper operation                       *
 ******************************************************************************/
void HWCAN_Init_All_Reg(uint8_t channel_num)
{
   /* Intialize all control registers */

    /* check if the GOM bit is set */
   if(afcan_control_registers[channel_num]->GMCTRL & AFCAN_GMCTRL_GOM_SET_M)
   {
     afcan_control_registers[channel_num]->GMCTRL = AFCAN_GMCTRL_CLEAR_GOM;
   }
    /* Select clock for CAN module from CPU clock */
   afcan_control_registers[channel_num]->GMCS = AFCAN_GMCS_DEFAULT;

   /* Enable AFCAN module operation (GOM = 1) */
   afcan_control_registers[channel_num]->GMCTRL = AFCAN_GMCTRL_DEFAULT;

   /* Clear last error information register(LEC) contents to zero */
   afcan_control_registers[channel_num]->LEC = AFCAN_LEC_DEFAULT;

   /* Clear pending interrupts of all AFCAN interrupt levels */
   afcan_control_registers[channel_num]->INTS = AFCAN_INTS_DEFAULT;

   /* Clear RGPT and TGPT registers by clearing TOVF & ROVF flags */
   afcan_control_registers[channel_num]->RGPT = AFCAN_RGPT_DEFAULT;
   afcan_control_registers[channel_num]->TGPT = AFCAN_TGPT_DEFAULT;

}

/*******************************************************************************
 * FunctionName: HWCAN_Change_Mode                                             *
 * Arguments passed  : channel num, mode                                       *
 * Return Value      : None                                                    *
 * Description : This function would put the CAN controller channel in         *
 * requested mode of operation.                                                *
*******************************************************************************/

void HWCAN_Change_Mode(uint8_t channel_num, Operating_Mode_T mode)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;

   if(HWCAN_INITIALIZATION_MODE == mode)
   {
      /* put the controller in initialization mode */
      afcan_control_registers[channel_num]->CTRL = AFCAN_CTRL_INITIALIZATION_MODE;

      while( ( --TimeoutCounter_uint32_t > 0L ) &&
      !(AFCAN_CTRL_INIT_MODE_MASK == ( afcan_control_registers[channel_num]->CTRL & AFCAN_CTRL_INIT_SET)));
   }
   else if(HWCAN_NORMAL_OPERATING_MODE == mode)
   {
      afcan_control_registers[channel_num]->CTRL = AFCAN_CTRL_CCERC_SET;

      /* put the controller in normal operating mode */
      afcan_control_registers[channel_num]->CTRL = AFCAN_CTRL_NORMAL_MODE;

      /* amit */
      /* can b removed as HWCAN_Is_CAN_Controller_Synchronized makes the same check */
      /* Check wether the controller is in noraml operating mode or not */
      while( ( --TimeoutCounter_uint32_t > 0L ) &&
      !(AFCAN_CTRL_NORMAL_MODE_MASK == (afcan_control_registers[channel_num]->CTRL & AFCAN_CTRL_NORMAL_MODE_MASK)));
   }

   /* Notify failure to change the mode to application */
   if( 0L == TimeoutCounter_uint32_t )
   {
//      Appl_Initialization_Failure_Set(); /* May be to set DTC code */
   }
}

/*******************************************************************************
 * FunctionName: HWCAN_Load_Bit_Timing_Parameters                              *
 * Arguments passed  : channel number, speed mode                              *
 * Return Value      : None                                                    *
 * Description : This function configures the Bit timing parameters for        *
 * communication on the bus                                                    *
 *******************************************************************************/

void HWCAN_Load_Bit_Timing_Parameters(uint8_t channel_num, Speed_Mode_T speed_mode)
{
      uint8_t index;

   for(index=0; index < Size_Of_Bit_Timing_Parameter_Table; index++)
   {
      if((HWCAN_Bit_Timing_Table[index].channel_no == channel_num)
        && (HWCAN_Bit_Timing_Table[index].speed == speed_mode))
      {
          /* Set fTQ = fCANMOD/X(say) (X*16 divisions = division ratio),TSEG1 = say 'Y'TQ,
         TSEG2 = say 'Z' TQ,  SJW = say 'P'TQ where X,Y,Z and P are arbitrary values
         that will be decided upon application bit timing requirements */
         afcan_control_registers[channel_num]->BRP = HWCAN_Bit_Timing_Table[index].brp;
         afcan_control_registers[channel_num]->BTR = AFCAN_BTR_DEFAULT();
      }
   }
}

/*******************************************************************************
 * FunctionName  : HWCAN_Is_CAN_Controller_Synchronized (uint8_t channel_num)  *
 * Arguments passed  : channel_num                                             *
 * Return Value: cbTRUE if CAN Controller is in Normal Operating mode          *
 * Function Description :This function checks the init bit in CnCTRL Reg       *
 *******************************************************************************/
Boolean_Returnvalue_T HWCAN_Is_CAN_Controller_Synchronized (uint8_t channel_num)
{
   Boolean_Returnvalue_T sync_bit;

   if(AFCAN_CTRL_NORMAL_MODE_MASK & afcan_control_registers[channel_num]->CTRL )
   {
      sync_bit = cbTRUE;
   }
   else
   {
      sync_bit = cbFALSE;
   }
   return(sync_bit);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Is_Bus_Off                                            *
 * Arguments passed  : channel num                                             *
 * Return Value      :cbTRUE if bus is off, else cbFALSE                       *
 * Function Description :This function reads and return BOFF bit in            *
 *                      CAN Status register                                    *
 *******************************************************************************/
Boolean_Returnvalue_T HWCAN_Is_Bus_Off(uint8_t channel_num)
{
   Boolean_Returnvalue_T in_bus_off;

   /* checks whether the BOFF bit is set or not */
   if(AFCAN_BUS_OFF_MASK & afcan_control_registers[channel_num]->INFO)
   {
      in_bus_off = cbTRUE;
   }
   else
   {
      in_bus_off = cbFALSE;
   }

   return(in_bus_off);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Is_Err_Warning                                        *
 * Arguments passed  : channel num                                             *
 * Return Value:cbTRUE if error warning state is reached, else cbFALSE         *
 * Function Description :This function reads CAN Status register               *
*******************************************************************************/
Boolean_Returnvalue_T HWCAN_Is_Err_Warning(uint8_t channel_num)
{
   Boolean_Returnvalue_T in_err_warning;

   /* Checks for transmit and receive error warning state */
   if( (AFCAN_TX_ERR_WARNING_MASK & afcan_control_registers[channel_num]->INFO) ||
       (AFCAN_RX_ERR_WARNING_MASK & afcan_control_registers[channel_num]->INFO) )
   {
      in_err_warning = cbTRUE;
   }
   else
   {
      in_err_warning = cbFALSE;
   }
   return(in_err_warning);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Is_Err_Passive                                        *
 * Arguments passed  : channel num                                             *
 * Return Value:cbTRUE if error passive state is reached, else cbFALSE         *
 * Function Description :This function reads CAN Status register               *
*******************************************************************************/
Boolean_Returnvalue_T HWCAN_Is_Err_Passive(uint8_t channel_num)
{
   Boolean_Returnvalue_T in_err_passive;

   /* Checks for transmit and receive error passive */
   if( (AFCAN_TX_ERR_PASSIVE_MASK & afcan_control_registers[channel_num]->INFO) ||
       (AFCAN_RX_ERR_PASSIVE_MASK & afcan_control_registers[channel_num]->INFO) )
   {
      in_err_passive = cbTRUE;
   }
   else
   {
      in_err_passive = cbFALSE;
   }
   return(in_err_passive);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Get_Tx_Err_Cnt                                        *
 * Arguments passed  : channel num                                             *
 * Return Value:Transmit Error Count                                           *
 * Function Description :This function returns content of TEC  field in        *
 *                        CAN Transmit Error Counter Register                  *
 *******************************************************************************/
uint8_t HWCAN_Get_Tx_Err_Cnt(uint8_t channel_num)
{
   uint8_t tx_err_cnt;
   uint16_t erc_copy;

   erc_copy = afcan_control_registers[channel_num]->ERC;

   /* if in bus off then the tx error counter value is invalid */
   if(HWCAN_Is_Bus_Off(channel_num))
   {
      tx_err_cnt = ((uint8_t)TECS_COUNT_INVALID);
   }
   else
   {
      erc_copy &= AFCAN_TX_ERR_COUNT_MASK;
      tx_err_cnt = (uint8_t)erc_copy;
   }
   return(tx_err_cnt);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Get_Rx_Err_Cnt                                        *
 * Arguments passed  : channel num                                             *
 * Return Value:Receive Error Count                                            *
 * Function Description :This function returns content of RECS field in        *
 *                        CAN receive Error Counter Register                   *
*******************************************************************************/
uint8_t HWCAN_Get_Rx_Err_Cnt(uint8_t channel_num)
{
   uint8_t rx_err_cnt;
   uint16_t erc_copy;

   erc_copy = afcan_control_registers[channel_num]->ERC;

   if( AFCAN_RECEPT_ERR_PASSIVE_MASK & erc_copy )
   {
      rx_err_cnt = ((uint8_t)RECS_COUNT_INVALID);
   }
   else
   {
      erc_copy &= AFCAN_RX_ERR_COUNT_MASK;
      erc_copy >>= AFCAN_ERC_RS_8;
      rx_err_cnt = (uint8_t)erc_copy;
   }
   return(rx_err_cnt);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Clear_Err_IntPnd_Flag_On_Interrupt                    *
 * Arguments passed  : channel num                                             *
 * Return Value: none                                                          *
 * Function Description :This function clears error interrupt pending flag     *
 *                       in the interrupt register                             *
*******************************************************************************/
void HWCAN_Clear_Err_IntPnd_Flag_On_Interrupt (uint8_t channel_num)
{
   /* Check for CAN error status interrupt */
   if( AFCAN_CAN_ERROR_STATUS_INTERRUPT_MASK & afcan_control_registers[channel_num]->INTS)
   {
      /* Clear CAN error status interrupt bit */
      afcan_control_registers[channel_num]->INTS = AFCAN_CLEAR_CAN_ERROR_STATUS_INTERRUPT;
   }
   /* Check for protocol error status interrupt */
   if( AFCAN_PROTOCOL_ERROR_STATUS_INTERRUPT_MASK & afcan_control_registers[channel_num]->INTS)
   {
      /* Clear protocol error status interrupt bit */
      afcan_control_registers[channel_num]->INTS = AFCAN_CLEAR_PROTOCOL_ERROR_STATUS_INTERRUPT;
   }
   if( 0x0010 & afcan_control_registers[channel_num]->INTS)
   {
      /* Clear protocol error status interrupt bit */
      afcan_control_registers[channel_num]->INTS = 0x0010;
   }
}
/*******************************************************************************
 * FunctionName: HWCAN_Enable_All_CAN_Interrupt_At_Init                         *
 * Arguments passed  : channel number, CAN_Int_Type                            *
 * Return Value      : None                                                    *
 * Description : This routine enables the CAN interrupts during initialization *
 *******************************************************************************/
void HWCAN_Enable_All_CAN_Interrupt_At_Init(uint8_t channel_num)
{

   /* Enable all CAN interrupts */
   afcan_control_registers[channel_num]->IE = AFCAN_IE_ENABLE_INTERRUPTS;

   /* The enabling of interrupts for message buffers is done at the time of configurations.
      According to the mannual the IE bit(for message buffer) should be set first and then RDY bit shouls be set
      The change has been so the setting of RDY bit can be moved to receive buffer initialization,
      which was done in this functin before */

//   CAN0INTREQLOW->F.recIntReq = 0;    
//   CAN0INTREQLOW->F.errIntReq = 0;
   C0ERRIF = 0;
   C0RECIF = 0;
   
//   CAN0INTREQHIGH->F.trxIntReq = 0;
   C0TRXIF = 0;
   
//   CAN0MASKLOW->F.recMask = 0;    
   C0RECMK= 0U;
//   CAN0MASKLOW->F.errMask = 0;
   C0ERRMK= 0U;
  
//   CAN0MASKHIGH->F.trxMask = 0;
   C0TRXMK= 0U;    
//   CAN0INTPRIOLOW->F.recPR0 = 1;
   C0RECPR0 = 1;
//   CAN0INTPRIOHIGH->F.recPR1 = 0; 
   SRPR02 = 0;//?
   
//   CAN0INTPRIOLOW->F.errPR0 = 0;
   C0ERRPR0 = 0;
//   CAN0INTPRIOHIGH->F.errPR1 = 0;
   MDPR0 = 0;//?
   
   

//   CAN0TXINTPRIOLOW->F.trxPR0 = 0;
   TMPR105 = 0;//?
//   CAN0TXINTPRIOHIGH->F.trxPR1 = 1; 
   C0TRXPR1 = 1;


  #ifdef CAN_WAKEUP_MODE_AVAILABLE

//   CAN0INTREQLOW->F.wupIntReq = 0;
   C0WUPIF = 0;
//   CAN0MASKLOW->F.wupMask = 0;
   C0WUPMK= 0U;
//   CAN0INTPRIOLOW->F.wupPR0 = 1;
   C0WUPPR0 = 1;
//   CAN0INTPRIOHIGH->F.wupPR1 = 1;
   STPR02 = 1;//?
   

  #endif
}


#ifdef CAN_SLEEP_MODE_AVAILABLE

/*******************************************************************************
 * FunctionName  : HWCAN_Is_OK_To_Sleep                                        *
 * Arguments passed  : channel_num                                             *
 * Return Value:    Returns cbTRUE - if NEC is ready to sleep                  *
                    Returns cbFALSE - if NEC is not ready to sleep             *
 * Description :This routine will be called by upper layer routines to know    *
 *              the readiness of NEC peripheral to go to SLEEP state.          *
 *******************************************************************************/

Sleep_Result_T HWCAN_Is_OK_To_Sleep (uint8_t channel_num)
{
   Sleep_Result_T ok_to_sleep = SLEEP_NOT_OK;

   /* Check whether the CAN module is in transmission or reception state or and not in initialization mode */

   if( ( AFCAN_CTRL_INIT_MODE_MASK != (afcan_control_registers[channel_num]->CTRL & AFCAN_CTRL_INIT_SET) )
        && ( AFCAN_CTRL_TSTAT_MASK != (afcan_control_registers[channel_num]->CTRL & AFCAN_CTRL_TSTAT_MASK) ) &&
             ( AFCAN_CTRL_RSTAT_MASK != (afcan_control_registers[channel_num]->CTRL & AFCAN_CTRL_RSTAT_MASK) ) )
   {
      ok_to_sleep = SLEEP_OK;
   }
   return (ok_to_sleep);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Go_To_Sleep                                           *
 * Arguments passed  : channel num                                             *
 * Return Value:    None                                                       *
 * Function Description :This routine will be called by upper layer routines to*
 *                       put the NEC peripheral in SLEEP state.                *
 *******************************************************************************/
void HWCAN_Go_To_Sleep (uint8_t channel_num)
{
   uint32_t TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;

   afcan_control_registers[channel_num]->CTRL = AFCAN_CTRL_SLEEP_MODE;

   while((--TimeoutCounter_uint32_t > 0L) &&
         !((afcan_control_registers[channel_num]->CTRL) & AFCAN_CTRL_SLEEP_MODE_MASK));

   /* Notify if the sleep mode is not set */
   if( (0L == TimeoutCounter_uint32_t) &&
   !((afcan_control_registers[channel_num]->CTRL) & AFCAN_CTRL_SLEEP_MODE_MASK))
   {
   //     Appl_Sleep_Mode_Failure(channel_num);
   }
}

/*******************************************************************************
 * FunctionName  : HWCAN_Clear_Sleep_State                                     *
 * Arguments passed  : channel num                                             *
 * Return Value:    Returns cbTRUE - if NEC is out of sleep mode                  *
                    Returns cbFALSE - if NEC is in sleep mode                  *
 * Function Description : This function cancels the sleep state upon request by*
 *                        application                                          *
*******************************************************************************/
Sleep_Result_T HWCAN_Clear_Sleep_State (uint8_t channel_num)
{
   Sleep_Result_T sleep_cancelled;

   uint32_t TimeoutCounter_uint32_t;

   sleep_cancelled = SLEEP_OK;

   TimeoutCounter_uint32_t = AFCAN_INITTIMEOUT;

   afcan_control_registers[channel_num]->CTRL = AFCAN_CLEAR_CTRL_SLEEP_MODE;
   while((--TimeoutCounter_uint32_t > 0L) &&
         !(AFCAN_CLEAR_CTRL_SLEEP_MODE_MASK == ((afcan_control_registers[channel_num]->CTRL) & AFCAN_CLEAR_CTRL_SLEEP_MODE_SET)));

   /* Notify if the sleep mode is not set */
   if( (0L == TimeoutCounter_uint32_t) &&
   !(AFCAN_CLEAR_CTRL_SLEEP_MODE_MASK == ((afcan_control_registers[channel_num]->CTRL) & AFCAN_CLEAR_CTRL_SLEEP_MODE_SET)))
   {
        sleep_cancelled = SLEEP_NOT_OK;
   }
   return(sleep_cancelled);
}

#endif

#ifdef CAN_WAKEUP_MODE_AVAILABLE
/*******************************************************************************
 * FunctionName  : HWCAN_Has_Controller_Woken_Up                               *
 * Arguments passed  : channel num                                             *
 * Return Value:    Returns cbTRUE - if NEC is ready to sleep                  *
 *                  Returns cbFALSE - if NEC is not ready to sleep             *
 * Function Description : This function checks if the controller has woken up  *
 *                        or not                                               *
*******************************************************************************/
Boolean_Returnvalue_T HWCAN_Has_Controller_Woken_Up (uint8_t channel_num)
{
   Boolean_Returnvalue_T wakeup_result = cbFALSE;

      if(AFCAN_CLEAR_CTRL_SLEEP_MODE_MASK == ((afcan_control_registers[channel_num]->CTRL) & AFCAN_CLEAR_CTRL_SLEEP_MODE_SET))
   {
       wakeup_result = cbTRUE;
   }
   return(wakeup_result);
}

/*******************************************************************************
 * FunctionName  : HWCAN_Clear_Wakeup_IntPnd_Flag_On_Interrupt                 *
 * Arguments passed  : channel num                                             *
 * Return Value:                                                               *
 * Function Description :This function clears error interrupt pending flag     *
 *                       in the interrupt register                             *
*******************************************************************************/
void HWCAN_Clear_Wakeup_IntPnd_Flag_On_Interrupt (uint8_t channel_num)
{
      /* Clear WUIF0 flag by writing 1 into it*/
      afcan_control_registers[channel_num]->INTS = AFCAN_CLEAR_WAKE_UP_INTERRUPT_STATUS;
}

#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file for      *
 *                 Sandeep       NEC v850 Fx3                                  *
 ******************************************************************************/
