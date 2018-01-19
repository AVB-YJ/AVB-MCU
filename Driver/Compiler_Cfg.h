#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/*============================================================================*\
 * \b Application:        Compiler_Cfg.h \n
 * \b Target:             NEC 78K0R \n
 * \b Compiler:           IAR C/C++ Compiler for NEC 78K0 and 78K0S \n
 * \b Module:             Compiler_Cfg_h.tpl \n
 * \b File-Revision:      1 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Tue Aug 24 15:11:57 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 *
 * Header File for SSA compiler abstraction - configuration part.
 * It contains the module specific parameters  (ptrclass  and  memclass)
 * that  are  passed  to  the  macros  defined  in Compiler.h.
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
#include "intrinsics.h"

/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/


/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/** Major AUTOSAR version index */
#define COMPILER_CFG_AR_MAJOR_VERSION (2u)
/** Minor AUTOSAR version index */
#define COMPILER_CFG_AR_MINOR_VERSION (1u)
/** Patch AUTOSAR level version index.*/
#define COMPILER_CFG_AR_PATCH_VERSION (0u)
/** Major module version index */
#define COMPILER_CFG_SW_MAJOR_VERSION (1u)
/** Minor module version index */
#define COMPILER_CFG_SW_MINOR_VERSION (0u)
/** Patch module level version index.*/
#define COMPILER_CFG_SW_PATCH_VERSION (1u)


/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/



/**
 * MemoryAndPointerClasses
 * This container contains the memory and pointer class parameters of
 * a single module.
 * For each module this container has to be provided.
 * The number of different pointer and memory classes per module
 * depends on the different types of variables, constants and pointers
 * used by the module. It is allowed to extend the classes by module
 * specific classes.
 */


/* ADC */
#define ADC_CODE
#define ADC_VAR_NOINIT
#define ADC_VAR_POWER_ON_INIT
#define ADC_VAR_FAST
#define ADC_VAR
#define ADC_CONST
#define ADC_APPL_DATA
#define ADC_APPL_CONST
#define ADC_APPL_CODE

/* DIO */
#define DIO_CODE
#define DIO_VAR_NOINIT
#define DIO_VAR_POWER_ON_INIT
#define DIO_VAR_FAST
#define DIO_VAR
#define DIO_CONST
#define DIO_APPL_DATA
#define DIO_APPL_CONST
#define DIO_APPL_CODE

/* IRQ */
#define IRQ_CODE
#define IRQ_VAR_NOINIT
#define IRQ_VAR_POWER_ON_INIT
#define IRQ_VAR_FAST
#define IRQ_VAR
#define IRQ_CONST
#define IRQ_APPL_DATA
#define IRQ_APPL_CONST
#define IRQ_APPL_CODE

/* MCU */
#define MCU_CODE
#define MCU_VAR_NOINIT
#define MCU_VAR_POWER_ON_INIT
#define MCU_VAR_FAST
#define MCU_VAR
#define MCU_CONST
#define MCU_APPL_DATA
#define MCU_APPL_CONST
#define MCU_APPL_CODE

/* OS */
#define OS_CODE
#define OS_VAR_NOINIT
#define OS_VAR_POWER_ON_INIT
#define OS_VAR_FAST
#define OS_VAR
#define OS_CONST
#define OS_APPL_DATA
#define OS_APPL_CONST
#define OS_APPL_CODE
#define OS_VAR_FAST_16BIT
#define OS_VAR_FAST_ARRAY

/* PORT */
#define PORT_CODE
#define PORT_VAR_NOINIT
#define PORT_VAR_POWER_ON_INIT
#define PORT_VAR_FAST
#define PORT_VAR
#define PORT_CONST
#define PORT_APPL_DATA
#define PORT_APPL_CONST
#define PORT_APPL_CODE

/* WDG */
#define WDG_CODE
#define WDG_VAR_NOINIT
#define WDG_VAR_POWER_ON_INIT
#define WDG_VAR_FAST
#define WDG_VAR
#define WDG_CONST
#define WDG_APPL_DATA
#define WDG_APPL_CONST
#define WDG_APPL_CODE

/* PWM */
#define PWM_CODE
#define PWM_VAR_NOINIT
#define PWM_VAR_POWER_ON_INIT
#define PWM_VAR_FAST
#define PWM_VAR
#define PWM_CONST
#define PWM_APPL_DATA
#define PWM_APPL_CONST
#define PWM_APPL_CODE

 
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


/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------

 * 18-MAR-2011   Wade Li
 * + Created initial file
 *   - Copied from 10024438_ICP_B78_TCI~10024438_TCI_4_01:project:tci_ik#1
 * + Removed unused #defines
 *
\*===========================================================================*/
#endif   /* COMPILER_CFG_H */

/* END OF FILE -------------------------------------------------------------- */

