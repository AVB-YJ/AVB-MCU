#ifndef WDG_36_78K0R_FX3H
#define WDG_36_78K0R_FX3H

/*============================================================================*\
 * \b Application:        WDG \n
 * \b Target:             NEC 78K0R/Fx3 \n
 * \b Compiler:           IAR icc78k0r \n
 * \b Module:             Wdg_36_78K0R_FX3.h \n
 * \b File-Revision:      1.1.1 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Fri Sep 10 15:07:01 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/

/**\file
 * \brief Header File for SSA for WDG module.
 * \details This file describes the public interface of the WDG module
 * for Small System Architecture.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-2-1}{SSA-REQ-WDG-220-1}
 */

/*============================================================================*\
 *
 * Copyright 2010  Controls & Security, All Rights Reserved
 * It is not allowed to reproduce or utilize parts of this document in any form
 * or by any means, including photocopying and microfilm, without permission in
 * written by  Electronics & Safety Division.
 *
\*============================================================================*/

/*============================================================================
 * PREPROCESSOR DIRECTIVES
============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/

#include "Std_Types.h"
#include "WdgIf_Types.h"
#include "Wdg_36_78K0R_FX3Cfg.h"

/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/

/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/* PRQA S 288 ++
   MISRA RULE 3.1 VIOLATION:
   Character (at) is required for doxygen syntax.
 */
/** \defgroup
 * \name Published information:
 * \details
 * - Vendor ID of the dedicated implementation of this module according
 * to the AUTOSAR vendor list. \n
 * - Module ID of this module from Module List. \n
 * - Major, minor and patch version number of AUTOSAR specification on which the
 * appropriate implementation is based on. \n
 * - Software major, minor and patch version of this module. \n
 * \n
 * Note: Specific numbers are given only as example of implementation. \n
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-3-1}{SSA-REQ-WDG-220-1, SSA-REQ-WDG-397-1}
 * @{
 */
 #define WDG_36_78K0R_FX3VENDOR_ID ((uint16)36)
 #define WDG_36_78K0R_FX3MODULE_ID ((uint8)102)

 #define WDG_36_78K0R_FX3AR_MAJOR_VERSION (2u)
 #define WDG_36_78K0R_FX3AR_MINOR_VERSION (1u)
 #define WDG_36_78K0R_FX3AR_PATCH_VERSION (0u)

 #define WDG_36_78K0R_FX3SW_MAJOR_VERSION (1u)
 #define WDG_36_78K0R_FX3SW_MINOR_VERSION (1u)
 #define WDG_36_78K0R_FX3SW_PATCH_VERSION (0u)

/* PRQA S 288 ++
   MISRA RULE 3.1 VIOLATION:
   Character (at) is required for doxygen syntax.
 */
/** \defgroup DevelopmentErrorValues
 * \name Instance ID and development error values definition:
 * \details
 * - WDG_36_78K0R_FX3INSTANCE_ID: The identifier of the index based instance of a module, starting from 0, if
 *  the module is a single instance module it shall be equal to 0. \n
 * - WDG_36_78K0R_FX3E_DRIVER_STATE: API service used in wrong context (e.g. driver not initialized). \n
 * - WDG_36_78K0R_FX3E_PARAM_MODE: API service called with wrong / inconsistent parameter(s). \n
 * - WDG_36_78K0R_FX3E_PARAM_CONFIG API service called with wrong / inconsistent parameter(s). \n
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-4-1}{SSA-REQ-WDG-226-1, SSA-REQ-WDG-227-1, SSA-REQ-WDG-228-1}
 * @{
 */
#define WDG_36_78K0R_FX3INSTANCE_ID     ((uint8)0x00)
#define WDG_36_78K0R_FX3E_DRIVER_STATE  ((uint8)0x10)
#define WDG_36_78K0R_FX3E_PARAM_MODE    ((uint8)0x11)
#define WDG_36_78K0R_FX3E_PARAM_CONFIG  ((uint8)0x12)
/* @}*/
/* PRQA S 288 -- */


/** Service ID for Wdg_36_78K0R_FX3Init function.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-5-1}{SSA-REQ-WDG-258-1}
 */
#define WDG_36_78K0R_FX3API_ID_INIT     ((uint8)0x00)

/** Service ID for Wdg_36_78K0R_FX3SetMode function.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-6-1}{SSA-REQ-WDG-277-1}
 */
#define WDG_36_78K0R_FX3API_ID_SET_MODE ((uint8)0x01)

/** Service ID for Wdg_36_78K0R_FX3Trigger function.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-7-1}{SSA-REQ-WDG-299-1}
 */
#define WDG_36_78K0R_FX3API_ID_TRIGGER  ((uint8)0x02)

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/** \brief Structure to hold the watchdog driver configuration set.
 * \details A pointer to such a structure is provided to the watchdog driver initialization
 * routine for configuration of the driver and watchdog hardware. \n
 * \n
 * Note: Wdg_36_78K0R_FX3ConfigType is empty if all the configurations are pre-compile #defines. \n
 * In this case watchdog driver configuration sets are provided as constants during code generation process.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-8-1}{SSA-REQ-WDG-249-1, SSA-REQ-WDG-250-1, SSA-REQ-WDG-251-1}
 */
 typedef void Wdg_36_78K0R_FX3ConfigType;

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/** \brief Function for initialization watchdog module.
 * \details Remark: Initialization of Wdg functionality in NEC78K0R microcontroller is realized by OPTION BYTES
 * settings. Because of this function changes only driver status to 'initialazed'.
 *
 * \param[in]     *ConfigPtr  Pointer to configuration set
 * \param[out]    none
 * \return        none
 *
 * \ServID        0x00
 * \Reentrancy    non reentrant
 * \Synchronism   synchronous
 * \Precondition  none
 * \Caveats       Watchdog configured as enabled is started just after power-on-reset.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-9-1}{SSA-REQ-WDG-256-1, SSA-REQ-WDG-257-1, SSA-REQ-WDG-259-1,
 *                            SSA-REQ-WDG-260-1, SSA-REQ-WDG-261-1, SSA-REQ-WDG-262-1,
 *                            SSA-REQ-WDG-263-1, SSA-REQ-WDG-265-1, SSA-REQ-WDG-266-1,
 *                            SSA-REQ-WDG-270-1, SSA-REQ-WDG-382-1}
 * \latexonly
 * \DSARfigure{Wdg_36_78K0R_FX3Init.png}{\textwidth}{fig:Wdg_36_78K0R_FX3Init}{Wdg\_36\_78K0R\_FX3Init() algorithm.}
 * \endlatexonly
 */
extern FUNC(void, WDG_CODE) Wdg_36_78K0R_FX3Init
(
   P2CONST(Wdg_36_78K0R_FX3ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr
);

/** \brief Function for switching watchdog driver to different modes.
 * \details Remark: NEC78K0R does not support watchdog mode switching during run-time. Because of this
 *          function does nothing and returns always E_NOT_OK value.
 *          Function exist in the code only because of compatiblity reason - module need to
 *          be compatible with rest of SSA architecture.
 *
 * \param[in]     Mode  WdgIf_ModeType
 *                       N/A
 * \param[out]    none
 * \return        Std_ReturnType:
 *                       - E_NOT_OK allways
 *
 * \ServID        0x01
 * \Reentrancy    non reentrant
 * \Synchronism   synchronous
 * \Precondition  none
 * \Caveats       none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-10-1}{SSA-REQ-WDG-221-1, SSA-REQ-WDG-235-1, SSA-REQ-WDG-275-1,
 *                             SSA-REQ-WDG-276-1, SSA-REQ-WDG-278-1, SSA-REQ-WDG-279-1,
 *                             SSA-REQ-WDG-280-1, SSA-REQ-WDG-281-1, SSA-REQ-WDG-282-1,
 *                             SSA-REQ-WDG-284-1, SSA-REQ-WDG-287-1, SSA-REQ-WDG-288-1,
 *                             SSA-REQ-WDG-289-1, SSA-REQ-WDG-290-1}
 * \latexonly
 * \DSARfigure{Wdg_36_78K0R_FX3SetMode.png}{0.7\textwidth}{fig:Wdg_36_78K0R_FX3SetMode}{Wdg\_36\_78K0R\_FX3SetMode() algorithm.}
 * \endlatexonly
 */

extern FUNC(Std_ReturnType, WDG_CODE) Wdg_36_78K0R_FX3SetMode
(
   WdgIf_ModeType Mode
);

/** \brief Function for triggering watchdog hardware.
 * \details This routine triggers the watchdog hardware.
 *          It has to be called cyclically by some upper layer function (ususally the watchdog manager)
 *          in order to prevent the watchdog hardware from expiring.
 *
 * \param[in]     none
 * \param[out]    none
 * \return        none
 *
 * \ServID        0x02
 * \Reentrancy    non reentrant
 * \Synchronism   synchronous
 * \Precondition  none
 * \Caveats       The watchdog driver shall have been initialized before this service is called.
 *                This routine might be called on interrupt level.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-11-1}{SSA-REQ-WDG-297-1, SSA-REQ-WDG-298-1, SSA-REQ-WDG-300-1,
 *                             SSA-REQ-WDG-301-1, SSA-REQ-WDG-302-1, SSA-REQ-WDG-303-1,
 *                             SSA-REQ-WDG-304-1, SSA-REQ-WDG-306-1, SSA-REQ-WDG-308-1,
 *                             SSA-REQ-WDG-309-1, SSA-REQ-WDG-310-1}
 * \latexonly
 * \DSARfigure{Wdg_36_78K0R_FX3Trigger.png}{\textwidth}{fig:Wdg_36_78K0R_FX3Trigger}{Wdg\_36\_78K0R\_FX3Trigger() algorithm.}
 * \endlatexonly
 */
extern FUNC(void, WDG_CODE) Wdg_36_78K0R_FX3Trigger(void);

/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/** \brief This service returns the version information of this module.
 * \details The version information includes: Module Id, Vendor Id, Vendor specific version numbers.
 *
 * \param[in]     none
 * \param[out]    versioninfo Pointer to where to store the version information of this module.
 * \return        none
 *
 * \ServID        0x04
 * \Reentrancy    non reentrant
 * \Synchronism   synchronous
 * \Precondition  none
 * \Caveats       none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-WDG-12-1}{SSA-REQ-WDG-315-1, SSA-REQ-WDG-316-1, SSA-REQ-WDG-318-1,
 *                             SSA-REQ-WDG-319-1, SSA-REQ-WDG-320-1, SSA-REQ-WDG-321-1,
 *                             SSA-REQ-WDG-322-1, SSA-REQ-WDG-324-1, SSA-REQ-WDG-325-1}
 */
#if( STD_ON == WDG_36_78K0R_FX3VERSION_INFO_API )
#define Wdg_36_78K0R_FX3GetVersionInfo(versioninfo)                        \
do {                                                                       \
   if ( NULL_PTR != (versioninfo) )                                        \
   {                                                                       \
      (versioninfo)->vendorID = WDG_36_78K0R_FX3VENDOR_ID;                 \
      (versioninfo)->moduleID = WDG_36_78K0R_FX3MODULE_ID;                 \
      (versioninfo)->sw_major_version = WDG_36_78K0R_FX3SW_MAJOR_VERSION;  \
      (versioninfo)->sw_minor_version = WDG_36_78K0R_FX3SW_MINOR_VERSION;  \
      (versioninfo)->sw_patch_version = WDG_36_78K0R_FX3SW_PATCH_VERSION;  \
   }                                                                       \
} while (0)
#endif
/* STD_ON == WDG_36_78K0R_FX3VERSION_INFO_API */

/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  27-Aug-2010   1.1.1       tck_ssa#117      Pawel.Zawalski(at).com
 *      - WdgIf compatiblity checking updated
 *  ---------------------------------------------------------------------------
 *  07-Sep-2010   1.1.0       tck_ssa#129      Pawel.Zawalski(at).com
 *      - API names correction (WDG_... to Wdg_...)
 *  ---------------------------------------------------------------------------
 *  27-Aug-2010   1.0.2       tck_ssa#117      Pawel.Zawalski(at).com
 *      - File updated after code peer review (85385.9133)
 *  ---------------------------------------------------------------------------
 *  08-Jul-2010   1.0.1       tck_ssa#117      Pawel.Zawalski(at).com
 *      - Coments correction after SDD peer review (84005.4107)
 *  ---------------------------------------------------------------------------
 *  17-May-2010   1.0.0       tck_ssa#117      Pawel.Zawalski(at).com
 *      - File creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

#endif /* #ifndef WDG_36_78K0R_FX3H */

/* END OF FILE -------------------------------------------------------------- */

