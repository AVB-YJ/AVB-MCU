#ifndef IRQ_H
#define IRQ_H
/*============================================================================*\
 * \b Application:        IRQ \n
 * \b Target:             NEC 78K0R \n
 * \b Compiler:           IAR 78K0R C/C++ \n
 * \b Module:             Irq.h \n
 * \b File-Revision:      1.0.1 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      %date% \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/
/**\file
 *
 * Header file for SSA IRQ driver. This file describes the public
 * interface of the IRQ driver for Small System Architecture.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-IRQ-XX}{SSA-REQ-IRQ-99-1}
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

#include "Irq_Cfg.h"


/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/* PRQA S 288 ++
   MISRA RULE 3.1 VIOLATION:
   Character (at) is required for doxygen syntax.
 */
/** \defgroup
 * \name Published information:
 * \details
 * 1. Vendor ID of the dedicated implementation of this module according
 * to the AUTOSAR vendor list. \n
 * 2. Software major, minor and patch version of this module. \n
 * \n
 * Note: Specific numbers are given only as example of implementation. \n
 *
 * \Requirements
 * \reqtrace{SSA-SDD-IRQ-XX}{}
 * @{
 */
 #define IRQ_VENDOR_ID ((uint16)36)

 #define IRQ_SW_MAJOR_VERSION (1u)
 #define IRQ_SW_MINOR_VERSION (0u)
 #define IRQ_SW_PATCH_VERSION (0u)
/* @}*/
/* PRQA S 288 -- */


#if( (IRQ_CFG_H_SW_MAJOR_VERSION != IRQ_SW_MAJOR_VERSION) || \
     (IRQ_CFG_H_SW_MINOR_VERSION != IRQ_SW_MINOR_VERSION) )
#error "The version of the Irq.h file does not match the version of the Irq_Cfg.h file"
#endif

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/**
* \details Service for initializing IRQ module.\n
*  This service initializes the hardware interrupt priorities which have InitializePriority parameter set to TRUE.
*  All other priorities are set to default (power-on) state.
*
* \n
* \ServID  0x01
* \Synchronism   Synchronous
* \Reentrancy  Non-reentrant
*
* \param[in]  None.
*
* \return None
* \Caveats This service does not unmask global interrupt mask (EI).
* \n
* \Requirements \n
* \reqtrace{SSA-SDD-IRQ-XX}{}
* \latexonly
* \DSARfigure{Irq_Init.png}{\textwidth}{fig:Fig1}{Irq\_Init function diagram}
* \endlatexonly
*/
extern FUNC(void, IRQ_CODE) Irq_Init
(
   void
);
extern void INTP4_Disable(void);
extern void INTP4_Enable(void);
extern void INTP5_Enable(void);
extern void INTP5_Disable(void);
extern void INTP4_Enable_Falling_Edge_INTP(void);
extern void	INTP4_Enable_Falling_Edge_INTP(void);

/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  11-Aug-2010   1.0.0       tck_ssa#126       lukasz.zemla(at).com
 *      - File creation.
 *  ---------------------------------------------------------------------------
 *  10-Sep-2010   1.0.1       tck_ssa#126       lukasz.zemla(at).com
 *      - Removed inclusion of io78f1826_a0.h file.
 *  ---------------------------------------------------------------------------
\*============================================================================*/

#endif   /* IRQ_H */

/* END OF FILE -------------------------------------------------------------- */

