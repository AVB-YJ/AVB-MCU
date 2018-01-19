/*============================================================================*\
 * \b Application:        IRQ \n
 * \b Target:             see Irq.h \n
 * \b Compiler:           see Irq.h \n
 * \b Module:             Irq.c \n
 * \b File-Revision:      1.0.1 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       see Irq.h \n
 * \b Last-Modified:      Fri Sep 10 13:58:26 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/
/**\file
 *
 * Source file for Small System Architecture of IRQ driver.
 * This file contains the functionality of the public interface
 * of the IRQ driver for SSA.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-IRQ-XX}{}
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

#include "uc_registers.h"
#include "Irq.h"

/*
 * Version controls for Irq.h file.
 */
#define IRQ_C_EXPECTED_IRQ_H_MAJOR_VERSION (1u)
#define IRQ_C_EXPECTED_IRQ_H_MINOR_VERSION (0u)

#if(   (IRQ_SW_MAJOR_VERSION != IRQ_C_EXPECTED_IRQ_H_MAJOR_VERSION) || \
       (IRQ_SW_MINOR_VERSION != IRQ_C_EXPECTED_IRQ_H_MINOR_VERSION))
#error "The version of the Irq.c file does not match the version of the Irq.h file."
#endif

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

/*============================================================================*\
 * EXPORTED FUNCTIONS
\*============================================================================*/

#define IRQ_START_SEC_CODE
#include "MemMap.h"

void INTP5_Enable(void);

FUNC(void, IRQ_CODE) Irq_Init
(
   void
)
{
   /* Initialize interrupt priorities */
   PR00 = IRQ_PR00_VAL;
   PR01 = IRQ_PR01_VAL;
   PR02 = IRQ_PR02_VAL;
   PR03 = IRQ_PR03_VAL;
   PR10 = IRQ_PR10_VAL;
   PR11 = IRQ_PR11_VAL;
   PR12 = IRQ_PR12_VAL;
   PR13 = IRQ_PR13_VAL;
}
/*============================================================================*\
 * below is added from CodeGenerator
 *-----------------------------------------------------------------------------*/

void INTP4_Enable_Falling_Edge_INTP(void)
{
	 EGN0 |= _10_INTP4_EDGE_FALLING_SEL; /* Enable CLK_Falling_Edge*/
}
void INTP4_Disable_Falling_Edge_INTP(void)
{
   EGN0 &= ~_10_INTP4_EDGE_FALLING_SEL; /*Disble CLK_Falling_Edge*/
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function clears INTP4 interrupt flag and enables interrupt.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP4_Enable(void)
{
	PIF4 = 0U;	/* clear INTP4 interrupt flag */
	PMK4 = 0U;	/* enable INTP4 interrupt */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function disables INTP4 interrupt and clears interrupt flag.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP4_Disable(void)
{
	PMK4 = 1U;	/* disable INTP4 interrupt */
	PIF4 = 0U;	/* clear INTP4 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function clears INTP5 interrupt flag and enables interrupt.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP5_Enable(void)
{
	PIF5 = 0U;	/* clear INTP5 interrupt flag */
	PMK5 = 0U;	/* enable INTP5 interrupt */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function disables INTP5 interrupt and clears interrupt flag.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP5_Disable(void)
{
	PMK5 = 1U;	/* disable INTP5 interrupt */
	PIF5 = 0U;	/* clear INTP5 interrupt flag */
}
/*============================================================================*\
 * end of code of CodeGenerator
 *-----------------------------------------------------------------------------*/

#define IRQ_STOP_SEC_CODE
#include "MemMap.h"


/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV          AUTHOR          NOTE
 *  ---------------------------------------------------------------------------
 *  23-Jun-2011   1.0.2        wade            add external interrupt for system wakeup
 *  ---------------------------------------------------------------------------
 *  11-Aug-2010   1.0.0       tck_ssa#126       lukasz.zemla(at).com
 *      - File creation
 *  ---------------------------------------------------------------------------
 *  10-Sep-2010   1.0.1       tck_ssa#126       lukasz.zemla(at).com
 *      - Added inclusion of uc_registers.h file.
 *  ---------------------------------------------------------------------------
\*============================================================================*/

/* END OF FILE -------------------------------------------------------------- */

