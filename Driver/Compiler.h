#ifndef COMPILER_H
#define COMPILER_H

/*============================================================================*\
 * \b Application:        Compiler.h \n
 * \b Target:             NEC 78K0R \n
 * \b Compiler:           IAR C/C++ Compiler for NEC 78K0 and 78K0S \n
 * \b Module:             Compiler.h \n
 * \b File-Revision:      1.0.0 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Tue Aug 24 15:11:55 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 *
 * Header File for SSA compiler abstraction.
 * It contains defines which can be used to switch between different implementations
 * for different compilers, e.g.
 *  - inline assembler fragments in drivers
 *  - special pragmas for memory alignment control
 *  - localization of function calls
 *  - adaptions to memory models
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

#include "Compiler_Cfg.h"

/** Vendor ID */
#define COMPILER_VENDOR_ID ((uint16)36)
/** Major AUTOSAR version index */
#define COMPILER_AR_MAJOR_VERSION (2)
/** Minor AUTOSAR version index */
#define COMPILER_AR_MINOR_VERSION (1)
/** Patch AUTOSAR level version index.*/
#define COMPILER_AR_PATCH_VERSION (0)
/** Major module version index */
#define COMPILER_SW_MAJOR_VERSION (1)
/** Minor module version index */
#define COMPILER_SW_MINOR_VERSION (0)
/** Patch module level version index.*/
#define COMPILER_SW_PATCH_VERSION (0)

#if (   (COMPILER_AR_MAJOR_VERSION!=COMPILER_CFG_AR_MAJOR_VERSION) \
     || (COMPILER_AR_MINOR_VERSION!=COMPILER_CFG_AR_MINOR_VERSION) \
     || (COMPILER_SW_MAJOR_VERSION!=COMPILER_CFG_SW_MAJOR_VERSION) \
     || (COMPILER_SW_MINOR_VERSION!=COMPILER_CFG_SW_MINOR_VERSION) )
#error "The version of the Compiler.h file does not match the version of the Compiler_Cfg.h file."
#endif


/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/** Compiler symbol for IAR C/C++ Compiler for NEC 78K0 and 78K0S */
#define _IAR_C_NEC78K_ (1u)

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/**
 * NULL_PTR define with a void pointer to zero definition.
 */
#ifndef NULL_PTR 
#define NULL_PTR  ((void *)0)
#endif
/**
 * The memory class AUTOMATIC is provided as empty
 * definition, used for the declaration of local pointers.
 */
#define AUTOMATIC

/**
 * _STATIC_ define for abstraction of compiler keyword 'static'.
 */
#define _STATIC_ static

/**
 * _INLINE_ define for abstraction of the keyword 'inline'.
 */
#define _INLINE_ inline

/**
 * _VOLATILE_ define for abstraction of the keyword 'volatile'.
 */
#define _VOLATILE_ volatile


/**
 * _INTERRUPT_ define for abstraction of interrupt frame declaration keyword.
 */
#define _INTERRUPT_ __interrupt


/**
 * The compiler abstraction shall define the FUNC macro for the declaration and
 * definition of functions, that ensures correct syntax of function declarations
 * as required by a specific compiler.
 * rettype     return type of the function
 * memclass    classification of the function itself
 *             (not used on 32bit platforms)
 */
#define FUNC(type, memclass) memclass type

/**
 * Pointer to variable data
 * ptrtype     type of the referenced data
 * memclass    classification of the pointer's variable itself
 *             (not used on 32bit platforms)
 * ptrclass    defines the classification of the pointer's distance
 *             (not used on 32bit platforms)
 */
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype ptrclass * memclass

/**
 * Pointer to constant data
 * ptrtype     type of the referenced data
 * memclass    classification of the pointer's variable itself
 *             (not used on 32bit platforms)
 * ptrclass    defines the classification of the pointer's distance
 *             (not used on 32bit platforms)
 */
#define P2CONST(ptrtype, memclass, ptrclass)  const ptrtype ptrclass * memclass

/**
 * Const pointer to variable data
 * ptrtype     type of the referenced data
 * memclass    classification of the pointer's variable itself
 *             (not used on 32bit platforms)
 * ptrclass    defines the classification of the pointer's distance
 *             (not used on 32bit platforms)
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype ptrclass * memclass const

/**
 * Const pointer to constant data
 * ptrtype     type of the referenced data
 * memclass    classification of the pointer's variable itself
 *             (not used on 32bit platforms)
 * ptrclass    defines the classification of the pointer's distance
 *             (not used on 32bit platforms)
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype ptrclass * memclass const

/**
 * Type definition of const pointers to functions
 * rettype     return type of the function
 * ptrclass    defines the classification of the pointer's distance
 *             (not used on 32bit platforms)
 * fctname     function name respectivly name of the defined type
 */
#define CONSTP2FUNC(rettype, ptrclass, fctname)  rettype (ptrclass * const fctname)

/**
 * Type definition of pointers to functions
 * rettype     return type of the function
 * ptrclass    defines the classification of the pointer's distance
 *             (not used on 32bit platforms)
 * fctname     function name respectivly name of the defined type
 */
#define P2FUNC(rettype, ptrclass, fctname) rettype (ptrclass * fctname)

/**
 * ROM constant
 * type        type of the constant
 * memclass    classification of the constant
 *             (not used on 32bit platforms)
 */
#define CONST(type, memclass) const memclass type

/**
 * RAM variables
 * type        type of the variable
 * memclass    classification of the variable
 *             (not used on 32bit platforms)
 */
#define VAR(type, memclass) type memclass



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



/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  24-Aug-2010   1.0.0          -              Pawel.Zawalski(at).com
 *      - File creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

#endif   /* COMPILER_H */

/* END OF FILE -------------------------------------------------------------- */

