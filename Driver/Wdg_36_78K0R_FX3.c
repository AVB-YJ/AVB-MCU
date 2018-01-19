/*============================================================================*\
 * \b Application:        WDG \n
 * \b Target:             see Wdg_36_78K0R_FX3.h \n
 * \b Compiler:           see Wdg_36_78K0R_FX3.h \n
 * \b Module:             Wdg_36_78K0R_FX3.c \n
 * \b File-Revision:      1.1.0 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       see Wdg_36_78K0R_FX3.h \n
 * \b Last-Modified:      Wed Sep  8 09:50:00 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 * \brief Source File for Small Sysytem Architecture of WDG module.
 * \details This file contains the functionality of the public interface
 * of the WDG module for SSA. \n
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-1-1}{SSA-REQ-WDG-40-1, SSA-REQ-WDG-41-2, SSA-REQ-WDG-44-2,
 *                            SSA-REQ-WDG-220-1}
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
#include "Wdg_36_78K0R_FX3.h"

#if (STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT)
#include "Det.h"
#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */

/* LOCAL DEFINES FOR CONSTANTS -----------------------------------------------*/

/* Expected AUTOSAR and file versions. */
#define EXPECTED_WDG_36_78K0R_FX3AR_MAJOR_VERSION (2u)
#define EXPECTED_WDG_36_78K0R_FX3AR_MINOR_VERSION (1u)
#define EXPECTED_WDG_36_78K0R_FX3AR_PATCH_VERSION (0u)

#define EXPECTED_WDG_36_78K0R_FX3H_MAJOR_VERSION (1u)
#define EXPECTED_WDG_36_78K0R_FX3H_MINOR_VERSION (1u)

/* Wdg_36_78K0R_FX3.h AUTOSAR version checking. */
#if( (WDG_36_78K0R_FX3AR_MAJOR_VERSION != EXPECTED_WDG_36_78K0R_FX3AR_MAJOR_VERSION) || \
     (WDG_36_78K0R_FX3AR_MINOR_VERSION != EXPECTED_WDG_36_78K0R_FX3AR_MINOR_VERSION) || \
     (WDG_36_78K0R_FX3AR_PATCH_VERSION != EXPECTED_WDG_36_78K0R_FX3AR_PATCH_VERSION) )
#error "AUTOSAR version mismatch between Wdg_36_78K0R_FX3.c and Wdg_36_78K0R_FX3.h files."
#endif

/* Wdg_36_78K0R_FX3.h file version checking. */
#if( (WDG_36_78K0R_FX3SW_MAJOR_VERSION != EXPECTED_WDG_36_78K0R_FX3H_MAJOR_VERSION) || \
     (WDG_36_78K0R_FX3SW_MINOR_VERSION != EXPECTED_WDG_36_78K0R_FX3H_MINOR_VERSION) )
#error "The version of the Wdg_36_78K0R_FX3.c file does not match the version of the Wdg_36_78K0R_FX3.h file"
#endif

#if (STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT)
   /* Det.h AUTOSAR version checking */
   #if ((DET_AR_MAJOR_VERSION != EXPECTED_WDG_36_78K0R_FX3AR_MAJOR_VERSION) || \
        (DET_AR_MINOR_VERSION != EXPECTED_WDG_36_78K0R_FX3AR_MINOR_VERSION))
   #error "AUTOSAR version mismatch between Wdg_36_78K0R_FX3.c and Det.h files."
   #endif
#endif /* (STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT) */

/** Values to refresh /trigger Watchdog */
#define WDG_36_78K0R_FX3TRIG_VALUE ((uint8) 0xAC)

#if( STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT )
/** WDG driver statuses */
/** Watchdog is not initialized */
#define WDG_36_78K0R_FX3UNINIT ((Wdg_36_78K0R_FX3StatusType)0x69)
/** Watchdog is in idle state */
#define WDG_36_78K0R_FX3IDLE   ((Wdg_36_78K0R_FX3StatusType)0x96)
/** Watchdog is busy */
#define WDG_36_78K0R_FX3BUSY   ((Wdg_36_78K0R_FX3StatusType)0x3C)
#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */

/* LOCAL DEFINE MACROS (#, ##) -----------------------------------------------*/

/*============================================================================*\
 * LOCAL TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/** Type used for setting and identifying driver status. */
typedef uint8 Wdg_36_78K0R_FX3StatusType;

/*============================================================================*\
 * OBJECT DEFINITIONS
\*============================================================================*/

/* EXPORTED OBJECTS ----------------------------------------------------------*/

/* LOCAL OBJECTS -------------------------------------------------------------*/

/* PRQA S 5087 EOF
   MISRA RULE 19.1 VIOLATION:
   Usage of memory map file is taken from AUTOSAR specification.
 */

#if( STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT )

#define WDG_START_SEC_VAR_8BIT
#include "MemMap.h"

/** Status of watchdog driver. */
_STATIC_ VAR(Wdg_36_78K0R_FX3StatusType, WDG_VAR) Wdg_36_78K0R_FX3Status = WDG_36_78K0R_FX3UNINIT;

#define WDG_STOP_SEC_VAR_8BIT
#include "MemMap.h"

#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */

/* PRQA S 3408 ++
   MISRA RULE 8.8 VIOLATION:
  (at) an external object or function shall be declared in one and only one file..
 */
#if defined QAC || defined POLYSPACE
CONST(Wdg_36_78K0R_FX3StatusType, WDG_CONST) Wdg_36_78K0R_FX3OptionByte = WDG_36_78K0R_FX3MODE;
#else
#if (STD_ON == WDG_36_78K0R_FX3UNIT_TEST)
CONST(Wdg_36_78K0R_FX3StatusType, WDG_CONST) Wdg_36_78K0R_FX3OptionByte = WDG_36_78K0R_FX3MODE;
#else
__root __far CONST(Wdg_36_78K0R_FX3StatusType, WDG_CONST) Wdg_36_78K0R_FX3OptionByte @ 0x00C0 = WDG_36_78K0R_FX3MODE;
#endif /*STD_ON == WDG_36_78K0R_FX3UNIT_TEST */
/* PRQA S 3408 --
 */
#endif

/*============================================================================*\
 * LOCAL FUNCTION PROTOTYPES
\*============================================================================*/

/*============================================================================*\
 * LOCAL FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * LOCAL FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS
\*============================================================================*/

#define WDG_START_SEC_CODE
#include "MemMap.h"

/*============================================================================*\
 * FUNCTION: Wdg_36_78K0R_FX3Init()
\*============================================================================*/
/* For detailed explanation on the exported functions see Wdg_36_78K0R_FX3.h file. */
FUNC(void, WDG_CODE) Wdg_36_78K0R_FX3Init
(
   P2CONST(Wdg_36_78K0R_FX3ConfigType, AUTOMATIC, WDG_CONST) ConfigPtr
)
{
#if( STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT )
   if(NULL_PTR != ConfigPtr)
   {
      Det_ReportError
      (
         WDG_36_78K0R_FX3MODULE_ID,
         WDG_36_78K0R_FX3INSTANCE_ID,
         WDG_36_78K0R_FX3API_ID_INIT,
         WDG_36_78K0R_FX3E_PARAM_CONFIG
      );
   }
   else
   {
#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */

#if( STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT )
      Wdg_36_78K0R_FX3Status = WDG_36_78K0R_FX3IDLE;
   }
#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */
}

/*============================================================================*\
 * FUNCTION: Wdg_36_78K0R_FX3SetMode()
\*============================================================================*/
/* For detailed explanation on the exported functions see Wdg_36_78K0R_FX3.h file. */
FUNC(Std_ReturnType, WDG_CODE) Wdg_36_78K0R_FX3SetMode
(
   WdgIf_ModeType Mode
)
{
   return E_NOT_OK;
}

/*============================================================================*\
 * FUNCTION: Wdg_36_78K0R_FX3Trigger()
\*============================================================================*/
/* For detailed explanation on the exported functions see Wdg_36_78K0R_FX3.h file. */
FUNC(void, WDG_CODE) Wdg_36_78K0R_FX3Trigger(void)
{
#if( STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT )
   if( WDG_36_78K0R_FX3IDLE != Wdg_36_78K0R_FX3Status )
   {
      Det_ReportError
      (
         WDG_36_78K0R_FX3MODULE_ID,
         WDG_36_78K0R_FX3INSTANCE_ID,
         WDG_36_78K0R_FX3API_ID_TRIGGER,
         WDG_36_78K0R_FX3E_DRIVER_STATE
      );
   }
   else
   {
      Wdg_36_78K0R_FX3Status = WDG_36_78K0R_FX3BUSY;
#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */
      WDTE = WDG_36_78K0R_FX3TRIG_VALUE;
#if( STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT )
      Wdg_36_78K0R_FX3Status = WDG_36_78K0R_FX3IDLE;
   }
#endif /* STD_ON == WDG_36_78K0R_FX3DEV_ERROR_DETECT */
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  07-Sep-2010   1.1.0       tck_ssa#129      Pawel.Zawalski(at).com
 *      - API names correction (WDG_... to Wdg_...)
 *  ---------------------------------------------------------------------------
 *  27-Aug-2010   1.0.2       tck_ssa#117      Pawel.Zawalski(at).com
 *      - File updated after code peer review (85385.9133)
 *  ---------------------------------------------------------------------------
 *  18-May-2010   1.0.1       tck_ssa#117      Pawel.Zawalski(at).com
 *      - File updated after SDD peer review (84005.4107)
 *  ---------------------------------------------------------------------------
 *  17-May-2010   1.0.0       tck_ssa#117      Pawel.Zawalski(at).com
 *      - Module creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

/* END OF FILE -------------------------------------------------------------- */

