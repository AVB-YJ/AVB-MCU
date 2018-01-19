#ifndef WDGIF_TYPES_H
#define WDGIF_TYPES_H

 /*============================================================================*\
 * \b Application:        WdgIf \n
 * \b Target:             target independent \n
 * \b Compiler:           compiler independent \n
 * \b Module:             WdgIf_Types.h \n
 * \b File-Revision:      1.0.2 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      %date% \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/
/**\file
 *
 * Watchdog Interface type-definitons header file.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDGIF-17-1}{SSA-REQ-WDGIF-250-1, SSA-REQ-WDGIF-251-1}
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

#include "Std_Types.h"

/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/


/**
 * \defgroup
 * \name Published information:
 * \details
 * 1. Vendor ID of the dedicated implementation of this module according
 * to the AUTOSAR vendor list \n
 * 2. Module ID of this module from Module List. \n
 * 3. Major, minor and patch version number of AUTOSAR specification on which the
 * appropriate implementation is based on. \n
 * 4. Software major, minor and patch version of this module. \n
 * SDD: Specific numbers are given only as example of implementation. \n
 * \Requirements
 * \reqtrace{SSA-SDD-WDGIF-39-1}{SSA-REQ-WDGIF-351-1}
 * @{
 */
#define WDGIF_TYPES_AR_MAJOR_VERSION                    (2u)
#define WDGIF_TYPES_AR_MINOR_VERSION                    (1u)
#define WDGIF_TYPES_AR_PATCH_VERSION                    (0u)

#define WDGIF_TYPES_SW_MAJOR_VERSION                    (1u)
#define WDGIF_TYPES_SW_MINOR_VERSION                    (0u)
#define WDGIF_TYPES_SW_PATCH_VERSION                    (2u)
/*@}*/

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/**
 *\details Type used by the underlying watchdog driver(s) if they are configured
 * for development mode,for internal status.
 * \Requirements\n
 * reqtrace{SSA-SDD-WDGIF-18-1}{SSA-REQ-WDGIF-257-1, SSA-REQ-WDGIF-258-1,
 * SSA-REQ-WDGIF-259-1, SSA-REQ-WDGIF-260-1, SSA-REQ-WDGIF-261-1}
 * \n
 */
typedef enum WdgIf_Status_Tag
  {
  WDGIF_UNINIT    = 0x5A,
  WDGIF_IDLE      = 0xA5,
  WDGIF_BUSY      = 0x3C
  }WdgIf_StatusType;

/**
 *\details Type used for specifying mode to which the undrlying
 * watchdog is switched
 * \Requirements\n
 * reqtrace{SSA-SDD-WDGIF-19-1}{SSA-REQ-WDGIF-265-1, SSA-REQ-WDGIF-266-1,
 *                                                     SSA-REQ-WDGIF-267-1}
 * \n
 */
typedef enum WdgIf_Mode_Tag
  {
  WDGIF_OFF_MODE   = 0x69,
  WDGIF_SLOW_MODE  = 0x96,
  WDGIF_FAST_MODE  = 0xC3
  }WdgIf_ModeType;

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/**
 *\details Type used for watchdog device index
* \Requirements\n
 * reqtrace{SSA-SDD-WDGIF-20-1}{SSA-REQ-WDGIF-252-1}
 * \n
 */
typedef uint8 WdgIf_DeviceIndexType ;

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

#endif   /* #ifdef WDGIF_TYPES_H */

/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  04-Mar-2010   1.0.2       tck_ssa#6         Dawid.Piotrowski(at).com
 *      - Update after peer review 78610.1871
 *  ---------------------------------------------------------------------------
 *  21-Jan-2010   1.0.1       tck_ssa#6         Dawid.Piotrowski(at).com
 *      - Update to AR 2.1.4 Rev.18 and new version of DocGen
 *  ---------------------------------------------------------------------------
 *  17-Oct-2008   1.0.0       tck_ssa#6         Dawid.Piotrowski(at).com
 *      - File creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

/* END OF FILE ---------------------------------------------------------------*/

