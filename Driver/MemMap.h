/*============================================================================*\
 * \b Application:        MemMap.h \n
 * \b Target:             target independent \n
 * \b Compiler:           compiler independent \n
 * \b Module:             MemMap_h.tpl \n
 * \b File-Revision:      2 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Fri Aug 27 15:22:48 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 *
 * Header File for SSA memory mapping mechanism.
 */
#ifndef MEM_MAP_h
#define MEM_MAP_h
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


/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/** Vendor ID */
#define MEM_VENDOR_ID   (36u)
/** Major AUTOSAR version index */
#define MEM_AR_MAJOR_VERSION (2u)
/** Minor AUTOSAR version index */
#define MEM_AR_MINOR_VERSION (1u)
/** Patch AUTOSAR level version index */
#define MEM_AR_PATCH_VERSION (0u)
/** Major file version index */
#define MEM_SW_MAJOR_VERSION (1u)
/** Minor file version index */
#define MEM_SW_MINOR_VERSION (0u)
/** Patch file level version index */
#define MEM_SW_PATCH_VERSION (1u)




#ifdef MEMMAP_ERROR  /* to prevent double definition */
#error "MEMMAP_ERROR defined, wrong MemMap.h usage"
#endif

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/


/**
 * Define error flag. If this file is properly used (included after valid section definition)
 * then MEMMAP_ERROR is undefined in the one of following #elif's.
 */
#define MEMMAP_ERROR


/* ================================================================================
 * ADC 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#if (defined ADC_START_SEC_CODE)
#undef ADC_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_CODE)
#undef ADC_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined ADC_START_SEC_VAR_NOINIT_8BIT)
#undef ADC_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_NOINIT_8BIT)
#undef ADC_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_NOINIT_16BIT)
#undef ADC_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_NOINIT_16BIT)
#undef ADC_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_NOINIT_32BIT)
#undef ADC_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_NOINIT_32BIT)
#undef ADC_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef ADC_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef ADC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined ADC_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef ADC_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef ADC_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef ADC_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef ADC_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef ADC_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef ADC_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef ADC_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef ADC_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined ADC_START_SEC_VAR_FAST_8BIT)
#undef ADC_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_FAST_8BIT)
#undef ADC_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_FAST_16BIT)
#undef ADC_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_FAST_16BIT)
#undef ADC_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_FAST_32BIT)
#undef ADC_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_FAST_32BIT)
#undef ADC_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_FAST_UNSPECIFIED)
#undef ADC_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef ADC_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined ADC_START_SEC_VAR_8BIT)
#undef ADC_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_8BIT)
#undef ADC_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_16BIT)
#undef ADC_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_16BIT)
#undef ADC_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_32BIT)
#undef ADC_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_32BIT)
#undef ADC_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_VAR_UNSPECIFIED)
#undef ADC_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_VAR_UNSPECIFIED)
#undef ADC_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined ADC_START_SEC_CONST_8BIT)
#undef ADC_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_CONST_8BIT)
#undef ADC_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_CONST_16BIT)
#undef ADC_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_CONST_16BIT)
#undef ADC_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_CONST_32BIT)
#undef ADC_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_CONST_32BIT)
#undef ADC_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined ADC_START_SEC_CONST_UNSPECIFIED)
#undef ADC_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ADC_STOP_SEC_CONST_UNSPECIFIED)
#undef ADC_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * DIO 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined DIO_START_SEC_CODE)
#undef DIO_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_CODE)
#undef DIO_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined DIO_START_SEC_VAR_NOINIT_8BIT)
#undef DIO_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_NOINIT_8BIT)
#undef DIO_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_NOINIT_16BIT)
#undef DIO_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_NOINIT_16BIT)
#undef DIO_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_NOINIT_32BIT)
#undef DIO_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_NOINIT_32BIT)
#undef DIO_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef DIO_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef DIO_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined DIO_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef DIO_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef DIO_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef DIO_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef DIO_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef DIO_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef DIO_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef DIO_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef DIO_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined DIO_START_SEC_VAR_FAST_8BIT)
#undef DIO_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_FAST_8BIT)
#undef DIO_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_FAST_16BIT)
#undef DIO_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_FAST_16BIT)
#undef DIO_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_FAST_32BIT)
#undef DIO_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_FAST_32BIT)
#undef DIO_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_FAST_UNSPECIFIED)
#undef DIO_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef DIO_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined DIO_START_SEC_VAR_8BIT)
#undef DIO_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_8BIT)
#undef DIO_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_16BIT)
#undef DIO_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_16BIT)
#undef DIO_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_32BIT)
#undef DIO_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_32BIT)
#undef DIO_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_VAR_UNSPECIFIED)
#undef DIO_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_VAR_UNSPECIFIED)
#undef DIO_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined DIO_START_SEC_CONST_8BIT)
#undef DIO_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_CONST_8BIT)
#undef DIO_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_CONST_16BIT)
#undef DIO_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_CONST_16BIT)
#undef DIO_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_CONST_32BIT)
#undef DIO_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_CONST_32BIT)
#undef DIO_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined DIO_START_SEC_CONST_UNSPECIFIED)
#undef DIO_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined DIO_STOP_SEC_CONST_UNSPECIFIED)
#undef DIO_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * FEE 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined FEE_START_SEC_CODE)
#undef FEE_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_CODE)
#undef FEE_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined FEE_START_SEC_VAR_NOINIT_8BIT)
#undef FEE_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_NOINIT_8BIT)
#undef FEE_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_NOINIT_16BIT)
#undef FEE_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_NOINIT_16BIT)
#undef FEE_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_NOINIT_32BIT)
#undef FEE_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_NOINIT_32BIT)
#undef FEE_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef FEE_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef FEE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined FEE_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef FEE_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef FEE_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef FEE_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef FEE_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef FEE_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef FEE_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef FEE_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef FEE_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined FEE_START_SEC_VAR_FAST_8BIT)
#undef FEE_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_FAST_8BIT)
#undef FEE_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_FAST_16BIT)
#undef FEE_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_FAST_16BIT)
#undef FEE_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_FAST_32BIT)
#undef FEE_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_FAST_32BIT)
#undef FEE_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_FAST_UNSPECIFIED)
#undef FEE_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef FEE_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined FEE_START_SEC_VAR_8BIT)
#undef FEE_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_8BIT)
#undef FEE_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_16BIT)
#undef FEE_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_16BIT)
#undef FEE_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_32BIT)
#undef FEE_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_32BIT)
#undef FEE_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_VAR_UNSPECIFIED)
#undef FEE_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_VAR_UNSPECIFIED)
#undef FEE_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined FEE_START_SEC_CONST_8BIT)
#undef FEE_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_CONST_8BIT)
#undef FEE_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_CONST_16BIT)
#undef FEE_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_CONST_16BIT)
#undef FEE_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_CONST_32BIT)
#undef FEE_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_CONST_32BIT)
#undef FEE_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined FEE_START_SEC_CONST_UNSPECIFIED)
#undef FEE_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined FEE_STOP_SEC_CONST_UNSPECIFIED)
#undef FEE_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * GPT 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined GPT_START_SEC_CODE)
#undef GPT_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_CODE)
#undef GPT_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined GPT_START_SEC_VAR_NOINIT_8BIT)
#undef GPT_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_NOINIT_8BIT)
#undef GPT_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_NOINIT_16BIT)
#undef GPT_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_NOINIT_16BIT)
#undef GPT_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_NOINIT_32BIT)
#undef GPT_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_NOINIT_32BIT)
#undef GPT_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef GPT_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef GPT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined GPT_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef GPT_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef GPT_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef GPT_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef GPT_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef GPT_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef GPT_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef GPT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef GPT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined GPT_START_SEC_VAR_FAST_8BIT)
#undef GPT_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_FAST_8BIT)
#undef GPT_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_FAST_16BIT)
#undef GPT_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_FAST_16BIT)
#undef GPT_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_FAST_32BIT)
#undef GPT_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_FAST_32BIT)
#undef GPT_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_FAST_UNSPECIFIED)
#undef GPT_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef GPT_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined GPT_START_SEC_VAR_8BIT)
#undef GPT_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_8BIT)
#undef GPT_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_16BIT)
#undef GPT_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_16BIT)
#undef GPT_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_32BIT)
#undef GPT_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_32BIT)
#undef GPT_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_VAR_UNSPECIFIED)
#undef GPT_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_VAR_UNSPECIFIED)
#undef GPT_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined GPT_START_SEC_CONST_8BIT)
#undef GPT_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_CONST_8BIT)
#undef GPT_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_CONST_16BIT)
#undef GPT_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_CONST_16BIT)
#undef GPT_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_CONST_32BIT)
#undef GPT_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_CONST_32BIT)
#undef GPT_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined GPT_START_SEC_CONST_UNSPECIFIED)
#undef GPT_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined GPT_STOP_SEC_CONST_UNSPECIFIED)
#undef GPT_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * ICU 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined ICU_START_SEC_CODE)
#undef ICU_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_CODE)
#undef ICU_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined ICU_START_SEC_VAR_NOINIT_8BIT)
#undef ICU_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_NOINIT_8BIT)
#undef ICU_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_NOINIT_16BIT)
#undef ICU_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_NOINIT_16BIT)
#undef ICU_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_NOINIT_32BIT)
#undef ICU_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_NOINIT_32BIT)
#undef ICU_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef ICU_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef ICU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined ICU_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef ICU_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef ICU_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef ICU_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef ICU_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef ICU_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef ICU_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef ICU_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef ICU_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined ICU_START_SEC_VAR_FAST_8BIT)
#undef ICU_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_FAST_8BIT)
#undef ICU_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_FAST_16BIT)
#undef ICU_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_FAST_16BIT)
#undef ICU_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_FAST_32BIT)
#undef ICU_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_FAST_32BIT)
#undef ICU_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_FAST_UNSPECIFIED)
#undef ICU_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef ICU_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined ICU_START_SEC_VAR_8BIT)
#undef ICU_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_8BIT)
#undef ICU_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_16BIT)
#undef ICU_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_16BIT)
#undef ICU_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_32BIT)
#undef ICU_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_32BIT)
#undef ICU_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_VAR_UNSPECIFIED)
#undef ICU_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_VAR_UNSPECIFIED)
#undef ICU_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined ICU_START_SEC_CONST_8BIT)
#undef ICU_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_CONST_8BIT)
#undef ICU_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_CONST_16BIT)
#undef ICU_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_CONST_16BIT)
#undef ICU_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_CONST_32BIT)
#undef ICU_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_CONST_32BIT)
#undef ICU_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined ICU_START_SEC_CONST_UNSPECIFIED)
#undef ICU_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined ICU_STOP_SEC_CONST_UNSPECIFIED)
#undef ICU_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * IRQ 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined IRQ_START_SEC_CODE)
#undef IRQ_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CODE)
#undef IRQ_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined IRQ_START_SEC_VAR_NOINIT_8BIT)
#undef IRQ_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_NOINIT_8BIT)
#undef IRQ_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_NOINIT_16BIT)
#undef IRQ_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_NOINIT_16BIT)
#undef IRQ_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_NOINIT_32BIT)
#undef IRQ_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_NOINIT_32BIT)
#undef IRQ_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef IRQ_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef IRQ_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined IRQ_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef IRQ_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef IRQ_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef IRQ_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef IRQ_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef IRQ_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef IRQ_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef IRQ_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef IRQ_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined IRQ_START_SEC_VAR_FAST_8BIT)
#undef IRQ_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_FAST_8BIT)
#undef IRQ_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_FAST_16BIT)
#undef IRQ_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_FAST_16BIT)
#undef IRQ_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_FAST_32BIT)
#undef IRQ_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_FAST_32BIT)
#undef IRQ_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_FAST_UNSPECIFIED)
#undef IRQ_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef IRQ_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined IRQ_START_SEC_VAR_8BIT)
#undef IRQ_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_8BIT)
#undef IRQ_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_16BIT)
#undef IRQ_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_16BIT)
#undef IRQ_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_32BIT)
#undef IRQ_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_32BIT)
#undef IRQ_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_VAR_UNSPECIFIED)
#undef IRQ_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_VAR_UNSPECIFIED)
#undef IRQ_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined IRQ_START_SEC_CONST_8BIT)
#undef IRQ_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CONST_8BIT)
#undef IRQ_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_CONST_16BIT)
#undef IRQ_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CONST_16BIT)
#undef IRQ_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_CONST_32BIT)
#undef IRQ_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CONST_32BIT)
#undef IRQ_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined IRQ_START_SEC_CONST_UNSPECIFIED)
#undef IRQ_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CONST_UNSPECIFIED)
#undef IRQ_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * MCU 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined MCU_START_SEC_CODE)
#undef MCU_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_CODE)
#undef MCU_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined MCU_START_SEC_VAR_NOINIT_8BIT)
#undef MCU_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_NOINIT_8BIT)
#undef MCU_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_NOINIT_16BIT)
#undef MCU_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_NOINIT_16BIT)
#undef MCU_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_NOINIT_32BIT)
#undef MCU_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_NOINIT_32BIT)
#undef MCU_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef MCU_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef MCU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined MCU_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef MCU_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef MCU_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef MCU_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef MCU_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef MCU_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef MCU_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef MCU_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef MCU_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined MCU_START_SEC_VAR_FAST_8BIT)
#undef MCU_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_FAST_8BIT)
#undef MCU_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_FAST_16BIT)
#undef MCU_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_FAST_16BIT)
#undef MCU_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_FAST_32BIT)
#undef MCU_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_FAST_32BIT)
#undef MCU_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_FAST_UNSPECIFIED)
#undef MCU_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef MCU_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined MCU_START_SEC_VAR_8BIT)
#undef MCU_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_8BIT)
#undef MCU_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_16BIT)
#undef MCU_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_16BIT)
#undef MCU_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_32BIT)
#undef MCU_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_32BIT)
#undef MCU_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_VAR_UNSPECIFIED)
#undef MCU_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_VAR_UNSPECIFIED)
#undef MCU_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined MCU_START_SEC_CONST_8BIT)
#undef MCU_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_CONST_8BIT)
#undef MCU_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_CONST_16BIT)
#undef MCU_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_CONST_16BIT)
#undef MCU_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_CONST_32BIT)
#undef MCU_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_CONST_32BIT)
#undef MCU_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined MCU_START_SEC_CONST_UNSPECIFIED)
#undef MCU_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_CONST_UNSPECIFIED)
#undef MCU_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * OS 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined OS_START_SEC_CODE)
#undef OS_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_CODE)
#undef OS_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * STACK section
 * To be used for mapping to a stack - for stack control in OS.
 */
#elif (defined OS_START_SEC_STACK)
#undef OS_START_SEC_STACK
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_STACK)
#undef OS_STOP_SEC_STACK
#undef MEMMAP_ERROR


/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined OS_START_SEC_VAR_NOINIT_8BIT)
#undef OS_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_NOINIT_8BIT)
#undef OS_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_NOINIT_16BIT)
#undef OS_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_NOINIT_16BIT)
#undef OS_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_NOINIT_32BIT)
#undef OS_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_NOINIT_32BIT)
#undef OS_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef OS_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef OS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined OS_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef OS_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef OS_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef OS_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef OS_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef OS_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef OS_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef OS_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef OS_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined OS_START_SEC_VAR_FAST_8BIT)
#undef OS_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_FAST_8BIT)
#undef OS_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_FAST_16BIT)
#undef OS_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_FAST_16BIT)
#undef OS_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_FAST_32BIT)
#undef OS_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_FAST_32BIT)
#undef OS_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_FAST_UNSPECIFIED)
#undef OS_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef OS_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined OS_START_SEC_VAR_8BIT)
#undef OS_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_8BIT)
#undef OS_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_16BIT)
#undef OS_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_16BIT)
#undef OS_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_32BIT)
#undef OS_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_32BIT)
#undef OS_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_VAR_UNSPECIFIED)
#undef OS_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_VAR_UNSPECIFIED)
#undef OS_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined OS_START_SEC_CONST_8BIT)
#undef OS_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_CONST_8BIT)
#undef OS_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_CONST_16BIT)
#undef OS_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_CONST_16BIT)
#undef OS_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_CONST_32BIT)
#undef OS_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_CONST_32BIT)
#undef OS_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined OS_START_SEC_CONST_UNSPECIFIED)
#undef OS_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined OS_STOP_SEC_CONST_UNSPECIFIED)
#undef OS_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * PORT 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined PORT_START_SEC_CODE)
#undef PORT_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_CODE)
#undef PORT_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined PORT_START_SEC_VAR_NOINIT_8BIT)
#undef PORT_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_NOINIT_8BIT)
#undef PORT_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_NOINIT_16BIT)
#undef PORT_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_NOINIT_16BIT)
#undef PORT_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_NOINIT_32BIT)
#undef PORT_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_NOINIT_32BIT)
#undef PORT_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef PORT_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef PORT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined PORT_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef PORT_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef PORT_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef PORT_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef PORT_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef PORT_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef PORT_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef PORT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef PORT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined PORT_START_SEC_VAR_FAST_8BIT)
#undef PORT_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_FAST_8BIT)
#undef PORT_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_FAST_16BIT)
#undef PORT_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_FAST_16BIT)
#undef PORT_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_FAST_32BIT)
#undef PORT_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_FAST_32BIT)
#undef PORT_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_FAST_UNSPECIFIED)
#undef PORT_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef PORT_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined PORT_START_SEC_VAR_8BIT)
#undef PORT_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_8BIT)
#undef PORT_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_16BIT)
#undef PORT_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_16BIT)
#undef PORT_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_32BIT)
#undef PORT_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_32BIT)
#undef PORT_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_VAR_UNSPECIFIED)
#undef PORT_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_VAR_UNSPECIFIED)
#undef PORT_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined PORT_START_SEC_CONST_8BIT)
#undef PORT_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_CONST_8BIT)
#undef PORT_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_CONST_16BIT)
#undef PORT_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_CONST_16BIT)
#undef PORT_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_CONST_32BIT)
#undef PORT_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_CONST_32BIT)
#undef PORT_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined PORT_START_SEC_CONST_UNSPECIFIED)
#undef PORT_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PORT_STOP_SEC_CONST_UNSPECIFIED)
#undef PORT_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * WDG 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined WDG_START_SEC_CODE)
#undef WDG_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_CODE)
#undef WDG_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined WDG_START_SEC_VAR_NOINIT_8BIT)
#undef WDG_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_NOINIT_8BIT)
#undef WDG_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_NOINIT_16BIT)
#undef WDG_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_NOINIT_16BIT)
#undef WDG_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_NOINIT_32BIT)
#undef WDG_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_NOINIT_32BIT)
#undef WDG_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef WDG_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef WDG_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined WDG_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef WDG_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef WDG_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef WDG_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef WDG_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef WDG_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef WDG_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef WDG_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef WDG_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined WDG_START_SEC_VAR_FAST_8BIT)
#undef WDG_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_FAST_8BIT)
#undef WDG_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_FAST_16BIT)
#undef WDG_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_FAST_16BIT)
#undef WDG_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_FAST_32BIT)
#undef WDG_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_FAST_32BIT)
#undef WDG_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_FAST_UNSPECIFIED)
#undef WDG_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef WDG_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined WDG_START_SEC_VAR_8BIT)
#undef WDG_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_8BIT)
#undef WDG_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_16BIT)
#undef WDG_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_16BIT)
#undef WDG_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_32BIT)
#undef WDG_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_32BIT)
#undef WDG_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_VAR_UNSPECIFIED)
#undef WDG_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_VAR_UNSPECIFIED)
#undef WDG_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined WDG_START_SEC_CONST_8BIT)
#undef WDG_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_CONST_8BIT)
#undef WDG_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_CONST_16BIT)
#undef WDG_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_CONST_16BIT)
#undef WDG_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_CONST_32BIT)
#undef WDG_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_CONST_32BIT)
#undef WDG_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined WDG_START_SEC_CONST_UNSPECIFIED)
#undef WDG_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined WDG_STOP_SEC_CONST_UNSPECIFIED)
#undef WDG_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR


/* ================================================================================
 * PWM 
 * ===============================================================================*/

/*
 * CODE section
 * To be used for mapping code to application block, boot block, external flash etc.
 */
#elif (defined PWM_START_SEC_CODE)
#undef PWM_START_SEC_CODE
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_CODE)
#undef PWM_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * VAR_NOINIT section
 * To be used for all global or static variables that are never initialized.
 */
#elif (defined PWM_START_SEC_VAR_NOINIT_8BIT)
#undef PWM_START_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_NOINIT_8BIT)
#undef PWM_STOP_SEC_VAR_NOINIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_NOINIT_16BIT)
#undef PWM_START_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_NOINIT_16BIT)
#undef PWM_STOP_SEC_VAR_NOINIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_NOINIT_32BIT)
#undef PWM_START_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_NOINIT_32BIT)
#undef PWM_STOP_SEC_VAR_NOINIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_NOINIT_UNSPECIFIED)
#undef PWM_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#undef PWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * POWER_ON_INIT section
 * To be used for all global or static variables that are initialized only after power on reset.
 */
#elif (defined PWM_START_SEC_VAR_POWER_ON_INIT_8BIT)
#undef PWM_START_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
#undef PWM_STOP_SEC_VAR_POWER_ON_INIT_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_POWER_ON_INIT_16BIT)
#undef PWM_START_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
#undef PWM_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_POWER_ON_INIT_32BIT)
#undef PWM_START_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
#undef PWM_STOP_SEC_VAR_POWER_ON_INIT_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef PWM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
#undef PWM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR_FAST section
 * To be used for all global or static variables that have at least one of the following properties:
 *  - accessed bitwise
 *  - frequently used
 *  - high number of accesses in source code
 */
#elif (defined PWM_START_SEC_VAR_FAST_8BIT)
#undef PWM_START_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_FAST_8BIT)
#undef PWM_STOP_SEC_VAR_FAST_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_FAST_16BIT)
#undef PWM_START_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_FAST_16BIT)
#undef PWM_STOP_SEC_VAR_FAST_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_FAST_32BIT)
#undef PWM_START_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_FAST_32BIT)
#undef PWM_STOP_SEC_VAR_FAST_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_FAST_UNSPECIFIED)
#undef PWM_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef PWM_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * VAR section
 * To be used for global or static variables that are initialized after every reset (the normal case).
 */
#elif (defined PWM_START_SEC_VAR_8BIT)
#undef PWM_START_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_8BIT)
#undef PWM_STOP_SEC_VAR_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_16BIT)
#undef PWM_START_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_16BIT)
#undef PWM_STOP_SEC_VAR_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_32BIT)
#undef PWM_START_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_32BIT)
#undef PWM_STOP_SEC_VAR_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_VAR_UNSPECIFIED)
#undef PWM_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_VAR_UNSPECIFIED)
#undef PWM_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * CONST section
 * To be used for global or static constants.
 */
#elif (defined PWM_START_SEC_CONST_8BIT)
#undef PWM_START_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_CONST_8BIT)
#undef PWM_STOP_SEC_CONST_8BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_CONST_16BIT)
#undef PWM_START_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_CONST_16BIT)
#undef PWM_STOP_SEC_CONST_16BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_CONST_32BIT)
#undef PWM_START_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_CONST_32BIT)
#undef PWM_STOP_SEC_CONST_32BIT
#undef MEMMAP_ERROR

#elif (defined PWM_START_SEC_CONST_UNSPECIFIED)
#undef PWM_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif (defined PWM_STOP_SEC_CONST_UNSPECIFIED)
#undef PWM_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#endif

#ifdef MEMMAP_ERROR  /* to prevent double definition */
#error "MEMMAP_ERROR defined, wrong MemMap.h usage"
#endif

#endif
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
 *  14-Sep-2010   1.0.1       tck_ssa#93        Lukasz.Zemla(at).com
 *      - Added memory mapping for FEE, PWM, OS, IRQ.
 *  ---------------------------------------------------------------------------
 *  27-Aug-2010   1.0.0        -          Pawel.Zawalski(at).com
 *      - File creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

/* END OF FILE -------------------------------------------------------------- */

