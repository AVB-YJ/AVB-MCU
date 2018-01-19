 /*-----------------------------------------------------------------------------
 * Copyright  Electronics & Safety. All rights reserved.
 ******************************************************************************/
/* Module Name:    irq_frame
* Created By:      wade.li
* Created Date:    01/30/2012
* %version:        3 %
* date_created:  Tue January 30 13:02:04 2012 %
*--------------------------------------------------------------------*/

/**\file
 * \brief Interrupt vectors for SSA.
 * \details This file contains the interrupt vectors for SSA.
 */

/*============================================================================*\
 *
 * Copyright 2010  Controls & Security, All Rights Reserved
 * It is not allowed to reproduce or utilize parts of this document in any form
 * or by any means, including photocopying and microfilm, without permission in
 * written by  Electronics & Safety Division.
 *
\*============================================================================*/

/*============================================================================*\
 * PREPROCESSOR DIRECTIVES
\*============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/

/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/
#ifndef QAC
#include "uc_registers.h"
#include "OS.h"
#include "Mcu.h"
#include "Adc.h"
#include "EcuM.h"
#include "intrinsics.h"
#include "Irq.h"
#include  "uart.h"
#include  "can_drv_init_misc.h"
#include  "can_drv_tx_rx.h"
/* LOCAL DEFINES FOR CONSTANTS -----------------------------------------------*/

/* LOCAL DEFINE MACROS (#, ##) -----------------------------------------------*/

/*============================================================================*\
 * LOCAL TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
 * OBJECT DEFINITIONS
\*============================================================================*/

/* EXPORTED OBJECTS ----------------------------------------------------------*/


/* LOCAL OBJECTS -------------------------------------------------------------*/

/*============================================================================*\
 * LOCAL FUNCTION PROTOTYPES
\*============================================================================*/

/*============================================================================*\
 * LOCAL FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/
__interrupt void IrqVector_Adc(void);
__interrupt void INTTM21_unused(void);
__interrupt void IrqVector_FreeRunningTimer(void);
__interrupt void IrqVector_CANRx(void);
__interrupt void IrqVector_CANTx(void);
__interrupt void IrqVector_CANErr(void);
__interrupt void IrqVector_INTLS1(void);
__interrupt void IrqVector_INTLT1(void);
__interrupt void IrqVector_INTLR1(void);
__interrupt void IrqVector_INTPLR1(void);
__interrupt void IrqVector_INTLS0(void);
__interrupt void IrqVector_INTLT0(void);
__interrupt void IrqVector_INTLR0(void);
__interrupt void IrqVector_INTPLR0(void);
__interrupt void IrqVector_INTP8(void);
__interrupt void BRK_I_unused(void);
__interrupt void INTC0WUP_unused(void);
__interrupt void INTCLM_unused(void);
__interrupt void INTCSI00_unused(void);
__interrupt void INTCSI01_unused(void);
__interrupt void INTCSI10_unused(void);
__interrupt void INTDMA0_unused(void);
__interrupt void INTDMA1_unused(void);
__interrupt void INTDMA2_unused(void);
__interrupt void INTDMA3_unused(void);
__interrupt void INTFL_unused(void);
__interrupt void INTIIC11_IIC_Handler(void);
__interrupt void INTLVI_unused(void);
__interrupt void INTMD_unused(void);
__interrupt void INTP0_unused(void);
__interrupt void INTP1_unused(void);
__interrupt void INTP2_unused(void);
__interrupt void INTP3_unused(void);
__interrupt void INTP4_unused(void);
__interrupt void INTP5_unused(void);
__interrupt void INTP6_unused(void);
__interrupt void INTP7_unused(void);
__interrupt void INTPR2_unused(void);
__interrupt void IrqVector_INTST2(void);
__interrupt void IrqVector_INTSR2(void);
__interrupt void INTTM00_unused(void);
__interrupt void INTTM01_unused(void);
__interrupt void INTTM02_Tick(void);
__interrupt void INTTM03_unused(void);
__interrupt void INTTM04_unused(void);
__interrupt void INTTM05_unused(void);
__interrupt void INTTM06_unused(void);
__interrupt void INTTM07_unused(void);
__interrupt void INTTM10_unused(void);
__interrupt void INTTM11_unused(void);
__interrupt void INTTM12_unused(void);
__interrupt void INTTM13_unused(void);
__interrupt void INTTM14_unused(void);
__interrupt void INTTM15_unused(void);
__interrupt void INTTM16_unused(void);
__interrupt void INTTM17_unused(void);
__interrupt void INTTM22_unused(void);
__interrupt void INTTM23_unused(void);
__interrupt void INTTM25_unused(void);
__interrupt void INTTM27_unused(void);
__interrupt void INTWDTI_unused(void);
__interrupt void INTWUTM_unused(void);

/*============================================================================*\
 * LOCAL FUNCTIONS
\*============================================================================*/
#define INVEC_04H_ADR _Pragma("location=\"INVEC_04H\"")
#define INVEC_06H_ADR _Pragma("location=\"INVEC_06H\"")
#define INVEC_08H_ADR _Pragma("location=\"INVEC_08H\"")
#define INVEC_0AH_ADR _Pragma("location=\"INVEC_0AH\"")
#define INVEC_0CH_ADR _Pragma("location=\"INVEC_0CH\"")
#define INVEC_0EH_ADR _Pragma("location=\"INVEC_0EH\"")
#define INVEC_10H_ADR _Pragma("location=\"INVEC_10H\"")
#define INVEC_12H_ADR _Pragma("location=\"INVEC_12H\"")
#define INVEC_14H_ADR _Pragma("location=\"INVEC_14H\"")
#define INVEC_16H_ADR _Pragma("location=\"INVEC_16H\"")
#define INVEC_18H_ADR _Pragma("location=\"INVEC_18H\"")
#define INVEC_1AH_ADR _Pragma("location=\"INVEC_1AH\"")
#define INVEC_1CH_ADR _Pragma("location=\"INVEC_1CH\"")
#define INVEC_1EH_ADR _Pragma("location=\"INVEC_1EH\"")
#define INVEC_20H_ADR _Pragma("location=\"INVEC_20H\"")
#define INVEC_22H_ADR _Pragma("location=\"INVEC_22H\"")
#define INVEC_24H_ADR _Pragma("location=\"INVEC_24H\"")
#define INVEC_26H_ADR _Pragma("location=\"INVEC_26H\"")
#define INVEC_28H_ADR _Pragma("location=\"INVEC_28H\"")
#define INVEC_2AH_ADR _Pragma("location=\"INVEC_2AH\"")
#define INVEC_2CH_ADR _Pragma("location=\"INVEC_2CH\"")
#define INVEC_2EH_ADR _Pragma("location=\"INVEC_2EH\"")
#define INVEC_30H_ADR _Pragma("location=\"INVEC_30H\"")
#define INVEC_32H_ADR _Pragma("location=\"INVEC_32H\"")
#define INVEC_34H_ADR _Pragma("location=\"INVEC_34H\"")
#define INVEC_36H_ADR _Pragma("location=\"INVEC_36H\"")
#define INVEC_38H_ADR _Pragma("location=\"INVEC_38H\"")
#define INVEC_3AH_ADR _Pragma("location=\"INVEC_3AH\"")
#define INVEC_3CH_ADR _Pragma("location=\"INVEC_3CH\"")
#define INVEC_3EH_ADR _Pragma("location=\"INVEC_3EH\"")
#define INVEC_40H_ADR _Pragma("location=\"INVEC_40H\"")
#define INVEC_42H_ADR _Pragma("location=\"INVEC_42H\"")
#define INVEC_44H_ADR _Pragma("location=\"INVEC_44H\"")
#define INVEC_46H_ADR _Pragma("location=\"INVEC_46H\"")
#define INVEC_48H_ADR _Pragma("location=\"INVEC_48H\"")
#define INVEC_4AH_ADR _Pragma("location=\"INVEC_4AH\"")
#define INVEC_4CH_ADR _Pragma("location=\"INVEC_4CH\"")
#define INVEC_4EH_ADR _Pragma("location=\"INVEC_4EH\"")
#define INVEC_50H_ADR _Pragma("location=\"INVEC_50H\"")
#define INVEC_52H_ADR _Pragma("location=\"INVEC_52H\"")
#define INVEC_54H_ADR _Pragma("location=\"INVEC_54H\"")
#define INVEC_56H_ADR _Pragma("location=\"INVEC_56H\"")
#define INVEC_58H_ADR _Pragma("location=\"INVEC_58H\"")
#define INVEC_5AH_ADR _Pragma("location=\"INVEC_5AH\"")
#define INVEC_5CH_ADR _Pragma("location=\"INVEC_5CH\"")
#define INVEC_5EH_ADR _Pragma("location=\"INVEC_5EH\"")
#define INVEC_60H_ADR _Pragma("location=\"INVEC_60H\"")
#define INVEC_62H_ADR _Pragma("location=\"INVEC_62H\"")
#define INVEC_64H_ADR _Pragma("location=\"INVEC_64H\"")
#define INVEC_66H_ADR _Pragma("location=\"INVEC_66H\"")
#define INVEC_68H_ADR _Pragma("location=\"INVEC_68H\"")
#define INVEC_6AH_ADR _Pragma("location=\"INVEC_6AH\"")
#define INVEC_6CH_ADR _Pragma("location=\"INVEC_6CH\"")
#define INVEC_6EH_ADR _Pragma("location=\"INVEC_6EH\"")
#define INVEC_70H_ADR _Pragma("location=\"INVEC_70H\"")
#define INVEC_72H_ADR _Pragma("location=\"INVEC_72H\"")
#define INVEC_74H_ADR _Pragma("location=\"INVEC_74H\"")
#define INVEC_76H_ADR _Pragma("location=\"INVEC_76H\"")
#define INVEC_78H_ADR _Pragma("location=\"INVEC_78H\"")
#define INVEC_7AH_ADR _Pragma("location=\"INVEC_7AH\"")
#define INVEC_7CH_ADR _Pragma("location=\"INVEC_7CH\"")
#define INVEC_7EH_ADR _Pragma("location=\"INVEC_7EH\"")

//#define INTVEC_FUN  _Pragma("location=\"INTVECCODE\"")
//#pragma location="INTVECCODE"
/*----------------------------------------------------------------------------*\
 * CAT1
\*----------------------------------------------------------------------------*/

/* Watchdog timer interval: 0x04*/
#pragma vector=INTWDTI_vect
 INVEC_04H_ADR __interrupt void INTWDTI_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* Low-voltage detection: 0x06 */
#pragma vector=INTLVI_vect
INVEC_06H_ADR __interrupt void INTLVI_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* Pin input edge detection: 0x08 */
#pragma vector=INTP0_vect
INVEC_08H_ADR  __interrupt void INTP0_unused(void)
{
   EcuM_SetNoInitByte(RESET_FLAG_LOCAL_WAKEUP_EJT);Mcu_PerformReset();
}
/* Pin input edge detection: 0x0A */
#pragma vector=INTP1_vect
 INVEC_0AH_ADR __interrupt void INTP1_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* Pin input edge detection: 0x0C */
#pragma vector=INTP2_vect
INVEC_0CH_ADR __interrupt void INTP2_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* Pin input edge detection: 0x0E */
#pragma vector=INTP3_vect
INVEC_0EH_ADR __interrupt void INTP3_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* Pin input edge detection: 0x10 */
#pragma vector=INTP4_vect
INVEC_10H_ADR __interrupt void INTP4_unused(void)
{
    EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* Pin input edge detection: 0x12 */
#pragma vector=INTP5_vect
 INVEC_12H_ADR __interrupt void INTP5_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* To stop main system clock or PLL clock: 0x14 */
#pragma vector=INTCLM_vect
 INVEC_14H_ADR __interrupt void INTCLM_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* End of CSI00 communication: 0x16 */
#pragma vector=INTCSI00_vect
 INVEC_16H_ADR __interrupt void INTCSI00_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of DMA0 transfer: 0x1A */
#pragma vector=INTDMA0_vect
 INVEC_1AH_ADR __interrupt void INTDMA0_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of DMA1 transfer: 0x1C */
#pragma vector=INTDMA1_vect
 INVEC_1CH_ADR __interrupt void INTDMA1_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}


/* Wakeup timer compare match: 0x1E */
#pragma vector=INTWUTM_vect
INVEC_1EH_ADR __interrupt void INTWUTM_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of data flash programming: 0x20 */
#pragma vector=INTFL_vect
 INVEC_20H_ADR __interrupt void INTFL_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* LIN-UART0 reception pin input: 0x28 */
#pragma vector=INTPLR0_vect
 INVEC_28H_ADR __interrupt void IrqVector_INTPLR0(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 00 count or capture: 0x2C */
#pragma vector=INTTM00_vect //(0x2C)
INVEC_2CH_ADR __interrupt void INTTM00_unused(void)
{
   // uint8 tmp;
     OS_SysTick();
    // tmp = P1_bit.no0;
    // P1_bit.no0 = ~tmp;
     
}

/* End of timer array unit 01 count or capture: 0x2E */
#pragma vector=INTTM01_vect
 INVEC_2EH_ADR __interrupt void INTTM01_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 02 count or capture: 0x30 */
#pragma vector=INTTM02_vect
 INVEC_30H_ADR __interrupt void INTTM02_Tick(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 03 count or capture: 0x32 */
#pragma vector=INTTM03_vect
INVEC_32H_ADR  __interrupt void INTTM03_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of A/D conversion (priority: 3): 0x34 */
#pragma vector=INTAD_vect
INVEC_34H_ADR __interrupt void IrqVector_Adc(void)
{
   Adc_Isr_ConvFinished();
}

/* LIN-UART1 reception pin input : 0x3C*/
#pragma vector=INTPLR1_vect
 INVEC_3CH_ADR  __interrupt void IrqVector_INTPLR1(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of CSI10 communication: 0x3E */
#pragma vector=INTCSI10_vect
 INVEC_3EH_ADR __interrupt void INTCSI10_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 04 count or capture : 0x42*/
#pragma vector=INTTM04_vect
INVEC_42H_ADR __interrupt void INTTM04_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 05 count or capture: 0x44 */
#pragma vector=INTTM05_vect
 INVEC_44H_ADR __interrupt void INTTM05_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}
/* End of timer array unit 06 count or capture: 0x46 */
#pragma vector=INTTM06_vect
 INVEC_46H_ADR __interrupt void INTTM06_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 07 count or capture: 0x48 */
#pragma vector=INTTM07_vect
INVEC_48H_ADR  __interrupt void INTTM07_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* vector: 0x4E */
#pragma vector=INTC0ERR_vect
INVEC_4EH_ADR __interrupt void INTC0ERR_unused(void)
{
   CD_Error_ISR_Channel_0();
}

/* vector: 0x50 */
#pragma vector=INTC0WUP_vect
INVEC_50H_ADR __interrupt void INTC0WUP_unused(void)
{}

/* vector: 0x52 */
#pragma vector=INTC0REC_vect
INVEC_52H_ADR __interrupt void INTC0REC_unused(void)
{
     CD_Receive_ISR_Channel_0();
}

/* vector: 0x54 */
#pragma vector=INTC0TRX_vect
INVEC_54H_ADR __interrupt void INTC0TRX_unused(void)
{
     CD_Transmit_ISR_Channel_0();
}

/* End of timer array unit 10 count or capture : 0x56*/
#pragma vector=INTTM10_vect
INVEC_56H_ADR  __interrupt void INTTM10_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 11 count or capture: 0x58 */
#pragma vector=INTTM11_vect
 INVEC_58H_ADR __interrupt void INTTM11_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 13 count or capture: 0x5C */
#pragma vector=INTTM13_vect
INVEC_5CH_ADR __interrupt void INTTM13_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of multiply/divide operation: 0x5E */
#pragma vector=INTMD_vect
INVEC_5EH_ADR  __interrupt void INTMD_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}
/* End of timer array unit 14 count or capture: 0x66 */
#pragma vector=INTTM14_vect
INVEC_66H_ADR __interrupt void INTTM14_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 15 count or capture: 0x68 */
#pragma vector=INTTM15_vect
 INVEC_68H_ADR __interrupt void INTTM15_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 16 count or capture: 0x6A */
#pragma vector=INTTM16_vect
 INVEC_6AH_ADR __interrupt void INTTM16_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of timer array unit 17 count or capture: 0x6C */
#pragma vector=INTTM17_vect
 INVEC_6CH_ADR __interrupt void INTTM17_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}




/* End of DMA2 transfer : 0x7A*/
#pragma vector=INTDMA2_vect
 INVEC_7AH_ADR __interrupt void INTDMA2_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* End of DMA3 transfer : 0x7C*/
#pragma vector=INTDMA3_vect
 INVEC_7CH_ADR __interrupt void INTDMA3_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}

/* Execution of BRK instruction: 0x7E */
#pragma vector=BRK_I_vect
INVEC_7EH_ADR  __interrupt void BRK_I_unused(void)
{
   EcuM_SetNoInitByte(UNUSED_INTERRUPT_RESET);Mcu_PerformReset();
}
#endif
/*----------------------------------------------------------------------------*\
 * UNUSED INTERRUPTS
\*----------------------------------------------------------------------------*/

/*============================================================================*\
 * EXPORTED FUNCTIONS
\*============================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------
 * 19-July-2012  Todd Yu  change for B81 RCP
 * 23-Jun-2011   Wade Li   add external interrupt
 * 18-MAR-2011   Wade Li
 * + Created initial file
 *   - Copied from 10024438_ICP_B78_TCI~10024438_TCI_4_01:project:tci_ik#1
 * + Add Os_SysTick()and IIC, SPI Interrupt
 *
\*===========================================================================*/

/* END OF FILE -------------------------------------------------------------- */

