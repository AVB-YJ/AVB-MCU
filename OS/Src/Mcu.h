#ifndef MCU_H
#define MCU_H

/*===========================================================================*
 * Copyright 2011  Technologies, Inc., All Rights Reserved.
 *  Confidential
 *
 * Module Name:     Mcu
 * %full_filespec: Mcu.h~1:incl:ctc_aud#5 %
 * %version: 1 %
 * %derived_by: lzs7ws %
 * %date_created: Tue Jun 26 15:37:46 2012 %
 *
 *
 * DESCRIPTION: 
 * Header File for SSA MCU module. This file describes the public
 * interface of the MCU module for Small System Architecture.
 *
 * ABBREVIATIONS:
 *   TBD
 *
 * TRACEABILITY INFO:
 *   Design Document(s): TBD
 *
 *   Requirements Document(s): TBD
 *
 *   Applicable Standards (in order of precedence: highest first):
 *     SW REF 264.15D " C Coding Standards" [31Oct2010]
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
 *===========================================================================*/

/*============================================================================*\
 * PREPROCESSOR DIRECTIVES
\*============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS */

/* INCLUDE DIRECTIVES FOR OTHER HEADERS */
#include "Mcu_Cfg.h"

/* PRQA S 288 ++
   MISRA RULE 3.1 VIOLATION:
   Character (at) is required for doxygen syntax.
*/

/* EXPORTED DEFINES OR CONSTANTS */

/**
 * \defgroup
 * \name Published information:
 * \details
 * 1. Vendor ID of the dedicated implementation of this module according
 * to the AUTOSAR vendor list. \n
 * 2. Module ID of this module from Module List. \n
 * 3. Major, minor and patch version number of AUTOSAR specification on which the
 * appropriate implementation is based on. \n
 * 4. Software major, minor and patch version of this module. \n
 * NOTE: Specific numbers are given only as example of implementation. \n
 * \n
 * \Requirements
 * \reqtrace{SSASDDMCUXX}{SSAREQMCU12821}
 * @{
 */

/**
 * \defgroup
 * \name Development error values
 * \details
 *  Function called with wrong parameter \n
 *  Function called with wrong parameter  clock \n
 *  Function called with wrong parameter  mode \n
 *  Function called with wrong parameter  RAM section \n
 *  Function called with wrong parameter  PLL not locked \n
 *  Function called without module initialization \n
 * \n
 * \Requirements
 * \reqtrace{SSASDDMCUXX}{SSAREQMCU9381, SSAREQMCU9391, SSAREQMCU9401, SSAREQMCU9451,
 * SSAREQMCU9481}
 * @{
 */
#define MCU_E_PARAM_CONFIG            ((uint8)0x0A)
#define MCU_E_PARAM_CLOCK             ((uint8)0x0B)
#define MCU_E_PARAM_MODE              ((uint8)0x0C)
#define MCU_E_PARAM_RAMSECTION        ((uint8)0x0D)
#define MCU_E_PARAM_PLL_NOT_LOCKED    ((uint8)0x0E)
#define MCU_E_UNINIT                  ((uint8)0x0F)
/*@}*/

/**
 * \defgroup API identifiers
 * \name Service Id for all supported API's
 * @{
 */
#define MCU_API_ID_MCU_INIT             ((uint8)0x00)
#define MCU_API_ID_MCU_INIT_RAM_SECTION ((uint8)0x01)
#define MCU_API_ID_MCU_INIT_CLOCK       ((uint8)0x02)
#define MCU_API_ID_DISTRIBUTE_PLL_CLOCK ((uint8)0x03)
#define MCU_API_ID_GET_PLL_STATUS       ((uint8)0x04)
#define MCU_API_ID_GET_RESET_RESULT     ((uint8)0x05)
#define MCU_API_ID_RESET_RAW_RESULT     ((uint8)0x06)
#define MCU_API_ID_PERFORM_RESET        ((uint8)0x07)
#define MCU_API_ID_SET_MODE             ((uint8)0x08)
#define MCU_API_ID_GET_VERSION_INFO     ((uint8)0x09)
/*@}*/


/* PRQA S 288 
*/

/* EXPORTED DEFINE MACROS (#, ##) */

/* Clock identifiers */
#define MCU_HIGH_SPEED_X1_EXCLK (0u)
#define MCU_INTERNAL_LOW_SPEED  (1u)
#define MCU_INTERNAL_HIGH_SPEED (2u)
#define MCU_INTERNAL_HIGH_SPEED_PLL (3u)
#define MCU_HIGH_SPEED_PLL (4u)


#define MCU_MODE_HALT       ((uint8_t)0x35)
#define MCU_MODE_STOP       ((uint8_t)0xCA)
#define MCU_MODE_RUN        ((uint8_t)0x66)
/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS */

/** \details Status type of PLL. */
typedef enum
{
   MCU_PLL_STATUS_UNDEFINED = 0,    /**< PLL status undefined */
   MCU_PLL_LOCKED = 0x69,           /**< PLL locked */
   MCU_PLL_UNLOCKED = 0x96          /**< PLL unlocked */
} Mcu_PllStatusType;

/** \details This is the type of the reset enumerator containing the subset of reset types.
 * \n
 * \Requirements \n
 * \reqtrace{SSASDDMCUXX}{SSAREQMCU9181}
 */
typedef enum
{
   MCU_POWER_ON_RESET = 0,                          /**< Reset caused by power on */
   MCU_LOW_VOLTAGE_RESET,                           /**< Reset caused by low voltage */
   MCU_ILLEGAL_ADDRESS_RESET,                       /**< Reset caused by illegal address access */
   MCU_CLOCK_MONITOR_RESET,                         /**< Reset caused by clock monitor */
   MCU_WATCHDOG_RESET,                              /**< Reset caused by watchdog timer (WDT)*/
   MCU_ILLEGAL_INSTRUCTION_RESET,                   /**< reset caused by execution of illegal instruction*/
   MCU_EXTERNAL_PIN_RESET,                          /**< Reset caused by external reset input via ~RESET pin */
   MCU_RESET_UNDEFINED                              /**< Reset undefined */
} Mcu_ResetType;

/* OTHER TYPEDEFS */

/** \details
 * This type specifies the identification (ID) for a clock setting
 * which is configured in the configuration structure.
 */
typedef uint8_t Mcu_ClockType;

/** \details Type not used since PostBuild variant is not supported in MCU Driver.\n
* All initialization data is taken from statically configured defines placed in Mcu_Cfg.h file.\n
* (Defined only for Mcu_Init(Mcu_ConfigType*) prototype consistence).
* \n
* \Requirements \n
* \reqtrace{SSASDDMCUXX}{SSAREQMCU11}
*/
typedef void Mcu_ConfigType;

/** \details
 * This type specifies the reset reason in raw register format
 * read from a reset status register.
 */
typedef uint8_t Mcu_RawResetType;

/** \details
 * This type specifies the identification (ID) for a MCU mode,
 * which is configured in the configuration structure.
 */
typedef uint8_t Mcu_ModeType;

/** \details
 * This type specifies the identification (ID) for a MCU RAM section,
 * which is configured in the configuration structure.
 */
typedef uint8_t Mcu_RamSectionType;

/* STRUCTS */

/* UNIONS */

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/* PRQA S 3447 ++
   MISRA RULE 8.8 VIOLATION:
   In test environment all _STATIC_ defines are empty even an object is unused
   outside the driver.
*/

/** \details
 * This function initializes MCU.
 * Function initializes MCU according to MCU configuration settings.
 * This function should be called first in order to initialize the uC for use.
 * If PC configuration variant is used then NULL pointer should be passed to function.
 * If PB configuration variant is used then a pointer to
 * desired configuration structure in Mcu_Conf array should be passed.
 *
 * \param[in]    ConfigPtr  pointer to data structure contained the
 *                           initialization data for the MCU Driver.
 * \return       void
 * \ServID       0x00
 * \Reentrancy   nonreentrant
 * \Synchronism  synchronous
 */
extern void Mcu_Init(const Mcu_ConfigType* ConfigPtr);

/** \details
 * This function initializes the RAM section wise.
 * This function initializes the RAM section wise.
 * The definition of the section and the initialization value
 * is provided via the configuration structure.
 *
 * \pre This function requires an execution of Mcu_Init() before it can be used.
 * \param[in]    RamSection  selects RAM memory section provided in configuration set
 * \return       Std_ReturnType    E_OK/E_NOT_OK
 * \ServID       0x01
 * \Reentrancy   nonreentrant
 * \Synchronism  synchronous
 */
extern Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection);

/** \details
 * This function initializes the MCU specific clock options.
 *
 * \pre This function requires an execution of Mcu_Init() before it can be used.
 * \param[in]    void
 * \return       Std_ReturnType    E_OK/E_NOT_OK
 * \ServID       0x02
 * \Reentrancy   nonreentrant
 * \Synchronism  synchronous
 */
extern Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);

/** \details
 * This function activates the PLL clock to the MCU clock distribution.
 *
 * \return       void
 * \ServID       0x03
 * \Reentrancy   nonreentrant
 * \Synchronism  synchronous
 */

extern void Mcu_DistributePllClock(void);

/** \details
 * This function provides the lock status of the PLL.
 *
 * \return       Mcu_PllStatusType
 * \ServID       0x04
 * \Reentrancy   reentrant
 * \Synchronism  synchronous
 */
extern Mcu_PllStatusType Mcu_GetPllStatus(void);

/** \details
 * The function reads the reset reason from the hardware.
 *
 * \return Mcu_ResetType
 * \ServID            0x05
 * \Reentrancy      reentrant
 * \Synchronism    synchronous
 * \n
 * \Requirements
 * \reqtrace{SSASDDMCUXX}{SSAREQMCU9181}
 */
extern Mcu_ResetType Mcu_GetResetReason(void);

/** \details
 * The function reads the reset reason from the hardware register.
 * This function reads the reset reason from the hardware register (if
 * reset reason register exist).
 *
 * \pre This function requires an execution of Mcu_Init() before it can be used.
 * \return       Mcu_RawResetType
 * \ServID       0x06
 * \Reentrancy   reentrant
 * \Synchronism  synchronous
 */
extern Mcu_RawResetType Mcu_GetResetRawValue(void);

/** \details
 * This function performs a uC reset.
 * The function performs a microcontroller reset.
 * When MCU_PERFORM_RESET_API is OFF this fucntion is unavailable.
 *
 * \pre This function requires an execution of Mcu_Init() before it can be used.
 * \return       void
 * \ServID       0x07
 * \Reentrancy   nonreentrant
 * \Synchronism  synchronous
 * \n
 * \Requirements
 * \reqtrace{SSASDDMCUXX}{SSAREQMCU9161}
 */
#if (MCU_PERFORM_RESET_API == STD_ON)
extern void Mcu_PerformReset(void);
#endif

/** \details
 * This function forces a hardware reset via illegal instruction.
 *
 * \param[in]    McuMode  Set different MCU power modes
 * \return       void
 * \ServID       0x08
 * \Reentrancy   nonreentrant
 * \Synchronism  synchronous
 * \n
 * \Requirements \n
 * \reqtrace{SSASDDMCUXX}{SSAREQMCU9201}
 */
extern void Mcu_SetMode(Mcu_ModeType McuMode);

/** \details
 * This function activates the MCU power modes. In case of the CPU
 * is switched off, the function is finished after a wakeup was performed.
 *
 * \pre This function requires an execution of Mcu_Init() before it can be used.
 * \return       never returns from this function as it is supposed to reset the �C
 */
extern void Mcu_Force_Illegal_OP_Fetch_Reset(void);
/* END OF FILE  */

#endif /* MCU_H */


