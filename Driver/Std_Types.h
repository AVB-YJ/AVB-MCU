#ifndef STD_TYPES_H
#define STD_TYPES_H

/*============================================================================*\
 * \b Application:        Std_Types.h \n
 * \b Target:             target independent \n
 * \b Compiler:           compiler independent \n
 * \b Module:             Std_Types.h \n
 * \b File-Revision:      1.0.0 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Thu Oct  1 13:10:48 2009 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 *
 * Header File for SSA standard types.
 * It contains all types that are used across several modules of the basic software
 * and that are platform and compiler independent.
 */

/*============================================================================*\
 *
 * Copyright 2009  Controls & Security, All Rights Reserved
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

#include "Compiler.h"
#include "Platform_Types.h"

/** Major AUTOSAR version index */
#define STD_TYPES_AR_MAJOR_VERSION (2)
/** Minor AUTOSAR version index */
#define STD_TYPES_AR_MINOR_VERSION (1)

#ifndef STATUSTYPEDEFINED
   #define STATUSTYPEDEFINED
   typedef uint8 StatusType;    /* OSEK compliance */
   //#define E_OK         (uint8)(0x00u) /** standard return - OK */
#endif /* endif: STATUSTYPEDEFINED*/

#define E_NOT_OK      (uint8)(0x01u) /** standard return - NOK */
//#define E_ERROR      (uint8)(0x01u) /** standard return - NOK */


#define STD_LOW      (0u)  /** Physical low level state (0V) */
#define STD_HIGH     (1u)  /** Physical high level state (e.g. 5V) */

#define STD_IDLE     (0u)   /** Logical state idle */
#define STD_ACTIVE   (1u)   /** Logical state active */

#ifndef STD_OFF
#define STD_OFF      (0u)  /** Switch - option disabled */
#endif
#ifndef STD_ON
#define STD_ON       (1u)  /** Switch - option enabled */
#endif

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/** Autosar standard API return type */
typedef uint8 Std_ReturnType;
/* END OF FILE -------------------------------------------------------------- */

#endif /* STD_TYPES_H  */

