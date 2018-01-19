#ifndef DIO_H
#define DIO_H
/*============================================================================*\
 * \b Application:        DIO \n
 * \b Target:             NEC 78K0R \n
 * \b Compiler:           IAR 78K0R C/C++ \n
 * \b Module:             Dio.h \n
 * \b File-Revision:      1.0.0 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      %date% \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/
/**\file
 *
 * Header file for SSA DIO driver. This file describes the public
 * interface of the DIO driver for Small System Architecture.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-2-1}{SSA-REQ-DIO-99-1,  SSA-REQ-DIO-100-3, SSA-REQ-DIO-102-1,
 *                            SSA-REQ-DIO-103-1, SSA-REQ-DIO-104-1, SSA-REQ-DIO-105-1,
 *                            SSA-REQ-DIO-107-1, SSA-REQ-DIO-108-1, SSA-REQ-DIO-111-1,
 *                            SSA-REQ-DIO-112-1, SSA-REQ-DIO-116-1, SSA-REQ-DIO-119-1,
 *                            SSA-REQ-DIO-301-1, SSA-REQ-DIO-302-1, SSA-REQ-DIO-303-1,
 *                            SSA-REQ-DIO-304-1}
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
#include "Dio_Cfg.h"


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
 * 2. Module ID of this module from Module List. \n
 * 3. Major, minor and patch version number of AUTOSAR specification on which the
 * appropriate implementation is based on. \n
 * 4. Software major, minor and patch version of this module. \n
 * \n
 * Note: Specific numbers are given only as example of implementation. \n
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-3-1}{SSA-REQ-DIO-235-1, SSA-REQ-DIO-236-1, SSA-REQ-DIO-237-1}
 * @{
 */
 #define DIO_VENDOR_ID ((uint16)36)

 #define DIO_MODULE_ID ((uint8)120)

 #define DIO_AR_MAJOR_VERSION (2u)
 #define DIO_AR_MINOR_VERSION (1u)
 #define DIO_AR_PATCH_VERSION (0u)

 #define DIO_SW_MAJOR_VERSION (1u)
 #define DIO_SW_MINOR_VERSION (0u)
 #define DIO_SW_PATCH_VERSION (0u)
/* @}*/
/* PRQA S 288 -- */

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/** \brief Possible levels of a DIO channel.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-5-1}{SSA-REQ-DIO-106-1, SSA-REQ-DIO-141-1, SSA-REQ-DIO-255-1,
 *                            SSA-REQ-DIO-256-1}
 */
typedef enum Dio_LevelTypeEnum
{
   DIO_LOW = STD_LOW,     /**< low level */
   DIO_HIGH = STD_HIGH    /**< high level */
}
Dio_LevelType;

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

/** \brief This service returns the version information of this module.
 * \details The version information includes: Module Id, Vendor Id,
 * vendor specific version numbers.
 *
 * \param[in]        none
 * \param[out]       versioninfo   Pointer to where to store the version information of this module
 *
 * \ServID           0x12
 * \Reentrancy       non reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-6-1}{SSA-REQ-DIO-212-1, SSA-REQ-DIO-214-1, SSA-REQ-DIO-215-1,
 *                            SSA-REQ-DIO-216-1, SSA-REQ-DIO-217-1, SSA-REQ-DIO-218-1,
 *                            SSA-REQ-DIO-219-1, SSA-REQ-DIO-220-1}
 */
#if(STD_ON == DIO_VERSION_INFO_API)
   #define Dio_GetVersionInfo(versioninfo)                           \
      do                                                             \
      {                                                              \
         if (versioninfo != NULL_PTR)                                \
         {                                                           \
            (versioninfo)->vendorID = DIO_VENDOR_ID;                 \
            (versioninfo)->moduleID = DIO_MODULE_ID;                 \
            (versioninfo)->sw_major_version = DIO_SW_MAJOR_VERSION;  \
            (versioninfo)->sw_minor_version = DIO_SW_MINOR_VERSION;  \
            (versioninfo)->sw_patch_version = DIO_SW_PATCH_VERSION;  \
         }                                                           \
      }                                                              \
      while(0)
#endif
/* End Dio_GetVersionInfo */

/** \brief This service returns the value of the specified DIO channel.
 *
 * \param[in]        ChannelId          ID of DIO channel
 * \param[out]       none
 *
 * \ServID           0x00
 * \Reentrancy       reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-7-1}{SSA-REQ-DIO-125-1, SSA-REQ-DIO-126-1, SSA-REQ-DIO-127-1,
 *                            SSA-REQ-DIO-143-1, SSA-REQ-DIO-145-1, SSA-REQ-DIO-146-1,
 *                            SSA-REQ-DIO-147-1, SSA-REQ-DIO-148-1, SSA-REQ-DIO-149-1,
 *                            SSA-REQ-DIO-150-1, SSA-REQ-DIO-151-1, SSA-REQ-DIO-247-1,
 *                            SSA-REQ-DIO-250-1}
 */
#define Dio_ReadChannel(ChannelId)      \
   (                                    \
      (0 == DIO_CFG_READ_##ChannelId) ? \
         DIO_LOW                        \
         :                              \
         DIO_HIGH                       \
   )
/* End Dio_ReadChannel */

/* PRQA S 881 ++
   MISRA RULE 19.11 VIOLATION:
   Intentional and no side effects (checked by peer review).
 */
/** \brief This service sets channel state to Level value.
 *
 * \param[in]        ChannelId          ID of DIO channel
 * \param[in]        Level              Level
 * \param[out]       none
 *
 * \ServID           0x01
 * \Reentrancy       reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-8-1}{SSA-REQ-DIO-152-1, SSA-REQ-DIO-154-1, SSA-REQ-DIO-155-1,
 *                            SSA-REQ-DIO-156-1, SSA-REQ-DIO-157-1, SSA-REQ-DIO-158-1,
 *                            SSA-REQ-DIO-159-1, SSA-REQ-DIO-242-1, SSA-REQ-DIO-251-1}
 */
#define Dio_WriteChannel(ChannelId,Level)     \
   (                                          \
      ((Level)==DIO_LOW) ?                    \
         (DIO_CFG_WRITE_##ChannelId=DIO_LOW)  \
         :                                    \
         (DIO_CFG_WRITE_##ChannelId=DIO_HIGH) \
   )
/* PRQA S 881 -- */
/* End Dio_WriteChannel */

/** \brief This service returns the level of all channels of selected port.
 *
 * \param[in]        PortId             ID of DIO port
 * \param[out]       none
 *
 * \ServID           0x02
 * \Reentrancy       reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-9-1}{SSA-REQ-DIO-172-1, SSA-REQ-DIO-174-1, SSA-REQ-DIO-175-1,
 *                            SSA-REQ-DIO-176-1, SSA-REQ-DIO-177-1, SSA-REQ-DIO-178-1,
 *                            SSA-REQ-DIO-179-1, SSA-REQ-DIO-247-1, SSA-REQ-DIO-248-1,
 *                            SSA-REQ-DIO-252-1}
 */
#define Dio_ReadPort(PortId) (DIO_CFG_READ_##PortId)
/* End Dio_ReadPort*/

/** \brief This service sets the specified value for the specified port.
 *
 * \param[in]        PortId             ID of DIO port
 * \param[in]        Level              Port value
 * \param[out]       none
 *
 * \ServID           0x03
 * \Reentrancy       reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-10-1}{SSA-REQ-DIO-181-1, SSA-REQ-DIO-183-1, SSA-REQ-DIO-184-1,
 *                             SSA-REQ-DIO-185-1, SSA-REQ-DIO-186-1, SSA-REQ-DIO-187-1,
 *                             SSA-REQ-DIO-243-1, SSA-REQ-DIO-253-1}
 */
#define Dio_WritePort(PortId,Level) (DIO_CFG_WRITE_##PortId)=(Level)  //Px1_bit.nox2 = Level(x1表示Px端口，x2表示第x个bit)
/* End Dio_WritePort */

/*============================================================================*/
/** \brief This service reads a subset of the adjoining bits of a port (channel group).
 *
 * \param[in]        ChannelGroupIdPtr     Pointer to ChannelGroup
 * \param[out]       none
 *
 * \ServID           0x04
 * \Reentrancy       reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-20-1}{SSA-REQ-DIO-124-1, SSA-REQ-DIO-191-1, SSA-REQ-DIO-193-1,
 *                             SSA-REQ-DIO-194-1, SSA-REQ-DIO-195-1, SSA-REQ-DIO-196-1,
 *                             SSA-REQ-DIO-197-1, SSA-REQ-DIO-198-1, SSA-REQ-DIO-199-1,
 *                             SSA-REQ-DIO-200-1, SSA-REQ-DIO-249-1, SSA-REQ-DIO-298-1}
 */
/*============================================================================*/
#define Dio_ReadChannelGroup(ChannelGroupIdPtr)                                         \
   ((((ChannelGroupIdPtr)->port) < DIO_NB_PORTS_WITH_CHANNEL_GROUPS) ?                                       \
      (uint8)(((*(Dio_PortInfoLookup[(ChannelGroupIdPtr)->port].data_register)) & \
      ((ChannelGroupIdPtr)->mask)) >> ((ChannelGroupIdPtr)->offset))                    \
      :                                                                                 \
      ((uint8)0)                                                                        \
   )

/*============================================================================*/
/** \brief This service sets a subset of the adjoining bits of a port (channel group)
 *  to a specified level.
 *
 * \param[in]        ChannelGroupIdPtr     Pointer to ChannelGroup
 * \param[in]        Level                 Value to be written
 * \param[out]       none
 *
 * \ServID           0x05
 * \Reentrancy       reentrant
 * \Synchronism      synchronous
 * \Precondition     none
 * \Caveats          none
 *
 * \Requirements
 * \reqtrace{SSA-SDD-DIO-21-1}{SSA-REQ-DIO-122-1, SSA-REQ-DIO-123-1, SSA-REQ-DIO-201-1,
 *                             SSA-REQ-DIO-203-1, SSA-REQ-DIO-204-1, SSA-REQ-DIO-205-1,
 *                             SSA-REQ-DIO-206-1, SSA-REQ-DIO-207-1, SSA-REQ-DIO-208-1,
 *                             SSA-REQ-DIO-210-1, SSA-REQ-DIO-211-1, SSA-REQ-DIO-299-1}
 */
/*============================================================================*/
#define Dio_WriteChannelGroup(ChannelGroupIdPtr,Level)                                  \
   {                                                                                    \
      if(((ChannelGroupIdPtr)->port) < DIO_NB_PORTS_WITH_CHANNEL_GROUPS)                                     \
      {                                                                                 \
         SchM_Enter_Dio(DIO_CHANNEL_GROUP_AREA);                                        \
         (*(Dio_PortInfoLookup[(ChannelGroupIdPtr)->port].data_register))=              \
         (((*(Dio_PortInfoLookup[(ChannelGroupIdPtr)->port].data_register)) &           \
         ((Dio_PortLevelType)(~((ChannelGroupIdPtr)->mask)))) |                         \
         ((((Level) << ((ChannelGroupIdPtr)->offset)) & (ChannelGroupIdPtr)->mask)));   \
         SchM_Exit_Dio(DIO_CHANNEL_GROUP_AREA);                                         \
      }                                                                                 \
   }

/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  21-May-2010   1.0.0       tck_ssa#111       lukasz.zemla(at).com
 *      - File creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

#endif   /* DIO_H */

/* END OF FILE -------------------------------------------------------------- */

