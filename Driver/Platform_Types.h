#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*============================================================================*\
 * \b Application:        Platform_Types.h \n
 * \b Target:             NEC 78K0R \n
 * \b Compiler:           IAR C/C++ Compiler for NEC 78K0 and 78K0S \n
 * \b Module:             Platform_Types.h \n
 * \b File-Revision:      1.0.0 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Tue Aug 24 15:12:02 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 *
 * Header File for SSA platform specific types.
 * It contains all platform dependent types and symbols.
 * Those types must be abstracted in order to become platform and compiler independent.
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


/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/** Vendor ID */
#define PLATFORM_VENDOR_ID ((uint16)36)
/** Major AUTOSAR version index */
#define PLATFORM_AR_MAJOR_VERSION   (2u)
/** Minor AUTOSAR version index */
#define PLATFORM_AR_MINOR_VERSION   (1u)
/** Patch AUTOSAR level version index */
#define PLATFORM_AR_PATCH_VERSION   (0u)
/** Major file version index */
#define PLATFORM_SW_MAJOR_VERSION   (1u)
/** Minor file version index */
#define PLATFORM_SW_MINOR_VERSION   (0u)
/** Patch file level version index */
#define PLATFORM_SW_PATCH_VERSION   (0u)

/** Possible CPU types definitions */
#define CPU_TYPE_8  (8u)
#define CPU_TYPE_16 (16u)
#define CPU_TYPE_32 (32u)

/** CPU endianess - bit ordering */
#define MSB_FIRST (0u)
#define LSB_FIRST (1u)

/** CPU endianess - byte ordering */
#define HIGH_BYTE_FIRST (0u)
#define LOW_BYTE_FIRST  (1u)

/** This symbol shall be defined as #define having one of the values CPU_TYPE_8,
  * CPU_TYPE_16 or CPU_TYPE_32 according to the platform.
  */
#define CPU_TYPE        (CPU_TYPE_16)

/** Bit order: MSB_FIRST or LSB_FIRST */
#define CPU_BIT_ORDER   (LSB_FIRST)

/** This  symbol  shall  be  defined  as  #define  having  one  of  the
  * values HIGH_BYTE_FIRST or LOW_BYTE_FIRST according to the platform.
  */
#define CPU_BYTE_ORDER  (LOW_BYTE_FIRST)


/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/**
 * This standard AUTOSAR type shall only be used together with the definitions
 * TRUE and FALSE.
 */
typedef unsigned char   boolean;

typedef unsigned char bool;
/**
 * This standard AUTOSAR type shall be of 8 bit unsigned. (0..255)
 */
typedef unsigned char   uint8;

/**
 * This standard AUTOSAR type shall be of 16 bit unsigned. (0..65535)
 */
typedef unsigned short  uint16;

/**
 * This standard AUTOSAR type shall be 32 bit unsigned. (0..4294967295)
 */
typedef unsigned long   uint32;

/**
 * This standard AUTOSAR type shall be 8 bit signed. (-128..+127)
 */
typedef signed char     sint8;

/**
 * This standard AUTOSAR type shall be 16 bit signed. (-32768..+32767)
 */
typedef signed short    sint16;

/**
 * This standard AUTOSAR type shall be 32 bit signed.(-2147483648..+2147483647)
 */
typedef signed long     sint32;

/**
 * This standard AUTOSAR type shall be at least 8 bit unsigned.
 */
typedef unsigned char   uint8_least;

/**
 * This standard AUTOSAR type shall be at least 16 bit unsigned.
 */
typedef unsigned short   uint16_least;

/**
 * This standard AUTOSAR type shall be at least 32 bit unsigned.
 */
typedef unsigned long   uint32_least;

/**
 * This standard AUTOSAR type shall be at least 7 bit + 1 bit sign.
 */
typedef signed char     sint8_least;

/**
 * This standard AUTOSAR type shall be at least 15 bit + 1 bit sign.
 */
typedef signed short     sint16_least;

/**
 * This standard AUTOSAR type shall be at least 31 bit + 1 bit sign.
 */
typedef signed long     sint32_least;

/**
 * Float 32Bit
 */
typedef float           float32;

/**
 * Float 64Bit
 */
typedef double          float64;

#ifndef TRUE   /* conditional check */
/**
 * In case of in-built compiler support of the symbols, redefinitions shall be
 * avoided using a conditional check.
 * These symbols shall only be used in conjunction with the boolean type
 * defined in Platform_Types.h.
 */
 #define TRUE           ((boolean) 1)
#endif

#ifndef FALSE  /* conditional check */
/**
 * In case of in-built compiler support of the symbols, redefinitions shall be
 * avoided using a conditional check.
 * These symbols shall only be used in conjunction with the boolean type
 * defined in Platform_Types.h.
 */
 #define FALSE          ((boolean) 0)
#endif

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

#endif /* PLATFORM_TYPES_H */

/* END OF FILE -------------------------------------------------------------- */

