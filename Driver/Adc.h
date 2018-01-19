#ifndef ADC_H
#define ADC_H

/*============================================================================*\
 * \b Application:        ADC \n
 * \b Target:             NEC 78K0R \n
 * \b Compiler:           IAR 78K0R C/C++ 4.62A \n
 * \b Module:             Adc.h \n
 * \b File-Revision:      1.1.1 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       SSA Team \n
 * \b Last-Modified:      Tue Oct 26 14:22:12 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/
/**\file
 *
 * \brief Header File for SSA for ADC module.
 * \details This file describes the public interface of the ADC module
 * for Small System Architecture.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-ADC-2-1}{SSA-REQ-ADC-394-1, SSA-REQ-ADC-395-2, SSA-REQ-ADC-1060-1,
 *                            SSA-REQ-ADC-1061-1, SSA-REQ-ADC-1062-1}
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

#include "Adc_Cfg.h"

/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/

/* PRQA S 869 ++
 * MISRA RULE 3.1 VIOLATION:
 * Character (at) is required for doxygen syntax.
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
 * SDD: Specific numbers are given only as example of implementation. \n
 * \n
 * \Requirements\n
 * \reqtrace{SSA-SDD-ADC-3-1}{SSA-REQ-ADC-615-1, SSA-REQ-ADC-1081-1}
 * @{
 */
 #define ADC_VENDOR_ID                           ((uint16)36)

 #define ADC_MODULE_ID                           ((uint8)123)

 #define ADC_AR_MAJOR_VERSION                    (2u)
 #define ADC_AR_MINOR_VERSION                    (1u)
 #define ADC_AR_PATCH_VERSION                    (0u)

 #define ADC_SW_MAJOR_VERSION                    (1u)
 #define ADC_SW_MINOR_VERSION                    (1u)
 #define ADC_SW_PATCH_VERSION                    (1u)
/* @} */

/** The identifier of the index based instance of a module, starting from 0, if
 *  the module is a single instance module it shall be equal to 0.
 */
#define ADC_INSTANCE_ID ((uint8)0)

/* AUTOSAR version number checking */
#if ( (ADC_CFG_AR_MAJOR_VERSION != ADC_AR_MAJOR_VERSION) || \
   (ADC_CFG_AR_MINOR_VERSION != ADC_AR_MINOR_VERSION) || \
   (ADC_CFG_AR_PATCH_VERSION != ADC_AR_PATCH_VERSION) )
#error "AUTOSAR version mismatch between Adc.h and Adc_Cfg.h files."
#endif

#if ( (ADC_CFG_SW_MAJOR_VERSION != ADC_SW_MAJOR_VERSION) || \
   (ADC_CFG_SW_MINOR_VERSION != ADC_SW_MINOR_VERSION) )
#error "The version of the Adc.h file does not match the version of the Adc_Cfg.h file"
#endif

/* PRQA S 869 --
 */

/**
 * \defgroup
 * \name Development error values
 * \details
 * - Service called prior to initialization
 * - Service called while ADC converter is running
 * - Service called while ADC converter is idle
 * - Adc_Init service called with invalid 'ConfigPtr' paramter
 * - API service called with invalid 'group' identifier
 * - Service called with invalid conversion mode
 * - Service called with invalid trigger source
 * - Service called while ADC notification is disable
 * \n
 * \Requirements\n
 * \reqtrace{SSA-SDD-ADC-4-1}{SSA-REQ-ADC-618-1, SSA-REQ-ADC-619-1, SSA-REQ-ADC-620-1,
 *                            SSA-REQ-ADC-622-1, SSA-REQ-ADC-628-1}
 * @{
 */
#define ADC_E_UNINIT              ((uint8)0x0A)
#define ADC_E_BUSY                ((uint8)0x0B)
#define ADC_E_IDLE                ((uint8)0x0C)
#define ADC_E_PARAM_CONFIG        ((uint8)0x0E)
#define ADC_E_PARAM_GROUP         ((uint8)0x15)
#define ADC_E_WRONG_CONV_MODE     ((uint8)0x16)
#define ADC_E_WRONG_TRIGG_SRC     ((uint8)0x17)
#define ADC_E_NOTIF_CAPABILITY    ((uint8)0x18)

/* @} */

/**
 * \defgroup
 * \name Service IDs for all supported APIs
 * \details
 * - Service ID for Adc_Init function.
 * - Service ID for Adc_DeInit function.
 * - Service ID for Adc_StartGroupConversion function.
 * - Service ID for Adc_ValueReadGroup function.
 * - Service ID for Adc_EnableGroupNotification function.
 * - Service ID for Adc_DisableGroupNotification function.
 * - Service ID for Adc_GetGroupStatus function.
 * \Requirements\n
 * \reqtrace{SSA-SDD-ADC-5-1}{SSA-REQ-ADC-736-1, SSA-REQ-ADC-758-1, SSA-REQ-ADC-774-1,
 *                            SSA-REQ-ADC-813-1, SSA-REQ-ADC-871-1, SSA-REQ-ADC-887-1,
 *                            SSA-REQ-ADC-903-1}
 * @{
 */
#define ADC_API_ID_INIT                        ((uint8)0x00)
#define ADC_API_ID_DEINIT                      ((uint8)0x01)
#define ADC_API_ID_START_GROUP_CONVERSION      ((uint8)0x02)
#define ADC_API_ID_VALUE_READ_GROUP            ((uint8)0x04)
#define ADC_API_ID_ENABLE_GROUP_NOTIFICATION   ((uint8)0x07)
#define ADC_API_ID_DISABLE_GROUP_NOTIFICATION  ((uint8)0x08)
#define ADC_API_ID_GET_GROUP_STATUS            ((uint8)0x08)
/* @} */

/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/**
 * \defgroup
 * \name Channel IDs
 * \details Channel IDs. \n
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-6-1}{SSA-REQ-ADC-1072-1}
 * @{
 */
#define ADC_CHANNEL0    ((uint8)0U)
#define ADC_CHANNEL1    ((uint8)1U)
#define ADC_CHANNEL2    ((uint8)2U)
#define ADC_CHANNEL3    ((uint8)3U)
#define ADC_CHANNEL4    ((uint8)4U)
#define ADC_CHANNEL5    ((uint8)5U)
#define ADC_CHANNEL6    ((uint8)6U)
#define ADC_CHANNEL7    ((uint8)7U)
#define ADC_CHANNEL8    ((uint8)8U)
#define ADC_CHANNEL9    ((uint8)9U)
#define ADC_CHANNEL10   ((uint8)10U)
#define ADC_CHANNEL11   ((uint8)11U)
#define ADC_CHANNEL12   ((uint8)12U)
#define ADC_CHANNEL13   ((uint8)13U)
#define ADC_CHANNEL14   ((uint8)14U)
#define ADC_CHANNEL15   ((uint8)15U)
#define ADC_CHANNEL16   ((uint8)16U)
#define ADC_CHANNEL17   ((uint8)17U)
#define ADC_CHANNEL18   ((uint8)18U)
#define ADC_CHANNEL19   ((uint8)19U)
#define ADC_CHANNEL20   ((uint8)20U)
#define ADC_CHANNEL21   ((uint8)21U)
#define ADC_CHANNEL22   ((uint8)22U)
#define ADC_CHANNEL23   ((uint8)23U)
#define ADC_NB_CHANNEL  ((uint8)24U)
/* @} */

/**
 * \defgroup
 * \name Conversion resolution
 * \details Conversion resolution type provided by hardware - 78K0R: fixed at 10 bits\n
 * \n
 * @{
 */
#define  ADC_CONV_RES_8_BIT   (0u)
#define  ADC_CONV_RES_10_BIT  (1u)
/* @} */


/**
 * Conversion sampling time (Normal Mode, no discharge, measured in Fclk Clock Cycles) 78K0R:\n
 */
#define ADC_SAMPLE_CYCLE_NORM_NODIS_22   ((uint8)0x0U) /**< Sample Time in Number of Fclk(<= 2MHz) */
#define ADC_SAMPLE_CYCLE_NORM_NODIS_40   ((uint8)0x1U) /**< Sample Time in Number of Fclk(<= 4MHz) */
#define ADC_SAMPLE_CYCLE_NORM_NODIS_58   ((uint8)0x2U) /**< Sample Time in Number of Fclk(<= 6MHz) */
#define ADC_SAMPLE_CYCLE_NORM_NODIS_76   ((uint8)0x3U) /**< Sample Time in Number of Fclk(<= 8MHz) */
#define ADC_SAMPLE_CYCLE_NORM_NODIS_94   ((uint8)0x4U) /**< Sample Time in Number of Fclk(<=10MHz) */
#define ADC_SAMPLE_CYCLE_NORM_NODIS_114  ((uint8)0x5U) /**< Sample Time in Number of Fclk(<=12MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_NODIS_132  ((uint8)0x6U) /**< Sample Time in Number of Fclk(<=14MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_NODIS_150  ((uint8)0x7U) /**< Sample Time in Number of Fclk(<=16MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_NODIS_168  ((uint8)0x8U) /**< Sample Time in Number of Fclk(<=18MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_NODIS_186  ((uint8)0x9U) /**< Sample Time in Number of Fclk(<=20MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_NODIS_208  ((uint8)0xaU) /**< Sample Time in Number of Fclk(<=22MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_NODIS_226  ((uint8)0xbU) /**< Sample Time in Number of Fclk(<=24MHz)*/

/**
 * Conversion sampling time (HSMODE1 Mode, no discharge, measured in Fclk Clock Cycles) 78K0R:\n
 */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_16  ((uint8)0x0U) /**< Sample Time in Number of Fclk(<= 2MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_18  ((uint8)0x1U) /**< Sample Time in Number of Fclk(<= 4MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_20  ((uint8)0x2U) /**< Sample Time in Number of Fclk(<= 6MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_33  ((uint8)0x3U) /**< Sample Time in Number of Fclk(<= 8MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_34  ((uint8)0x4U) /**< Sample Time in Number of Fclk(<=10MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_37  ((uint8)0x5U) /**< Sample Time in Number of Fclk(<=12MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_50  ((uint8)0x6U) /**< Sample Time in Number of Fclk(<=14MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_52  ((uint8)0x7U) /**< Sample Time in Number of Fclk(<=16MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_54  ((uint8)0x8U) /**< Sample Time in Number of Fclk(<=18MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_55  ((uint8)0x9U) /**< Sample Time in Number of Fclk(<=20MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_71  ((uint8)0xaU) /**< Sample Time in Number of Fclk(<=22MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_NODIS_73  ((uint8)0xbU) /**< Sample Time in Number of Fclk(<=24MHz) */

/**
 * Conversion sampling time (HSMODE2 Mode, no discharge, measured in Fclk Clock Cycles) 78K0R:\n
 */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_17  ((uint8)0x0U) /**< Sample Time in Number of Fclk(<= 2MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_20  ((uint8)0x1U) /**< Sample Time in Number of Fclk(<= 4MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_35  ((uint8)0x2U) /**< Sample Time in Number of Fclk(<= 6MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_37  ((uint8)0x3U) /**< Sample Time in Number of Fclk(<= 8MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_40  ((uint8)0x4U) /**< Sample Time in Number of Fclk(<=10MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_56  ((uint8)0x5U) /**< Sample Time in Number of Fclk(<=12MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_59  ((uint8)0x6U) /**< Sample Time in Number of Fclk(<=14MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_72  ((uint8)0x7U) /**< Sample Time in Number of Fclk(<=16MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_76  ((uint8)0x8U) /**< Sample Time in Number of Fclk(<=18MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_78  ((uint8)0x9U) /**< Sample Time in Number of Fclk(<=20MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_96  ((uint8)0xaU) /**< Sample Time in Number of Fclk(<=22MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_NODIS_99  ((uint8)0xbU) /**< Sample Time in Number of Fclk(<=24MHz) */

/**
 * Conversion sampling time (Normal Mode, discharge, measured in Fclk Clock Cycles) 78K0R:\n
 */
#define ADC_SAMPLE_CYCLE_NORM_DIS_27    ((uint8)0x0U) /**< Sample Time in Number of Fclk(<= 2MHz) */
#define ADC_SAMPLE_CYCLE_NORM_DIS_47    ((uint8)0x1U) /**< Sample Time in Number of Fclk(<= 4MHz) */
#define ADC_SAMPLE_CYCLE_NORM_DIS_68    ((uint8)0x2U) /**< Sample Time in Number of Fclk(<= 6MHz) */
#define ADC_SAMPLE_CYCLE_NORM_DIS_88    ((uint8)0x3U) /**< Sample Time in Number of Fclk(<= 8MHz) */
#define ADC_SAMPLE_CYCLE_NORM_DIS_108   ((uint8)0x4U) /**< Sample Time in Number of Fclk(<=10MHz) */
#define ADC_SAMPLE_CYCLE_NORM_DIS_132   ((uint8)0x5U) /**< Sample Time in Number of Fclk(<=12MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_DIS_152   ((uint8)0x6U) /**< Sample Time in Number of Fclk(<=14MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_DIS_173   ((uint8)0x8U) /**< Sample Time in Number of Fclk(<=18MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_DIS_193   ((uint8)0x9U) /**< Sample Time in Number of Fclk(<=20MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_DIS_213   ((uint8)0xaU) /**< Sample Time in Number of Fclk(<=22MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_DIS_240   ((uint8)0xbU) /**< Sample Time in Number of Fclk(<=24MHz)*/
#define ADC_SAMPLE_CYCLE_NORM_DIS_260   ((uint8)0x7U) /**< Sample Time in Number of Fclk(<=16MHz)*/

/**
 * Conversion sampling time (HSMODE1 Mode, discharge, measured in Fclk Clock Cycles) 78K0R:\n
 */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_19   ((uint8)0x0U) /**< Sample Time in Number of Fclk(<= 2MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_22   ((uint8)0x1U) /**< Sample Time in Number of Fclk(<= 4MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_24   ((uint8)0x2U) /**< Sample Time in Number of Fclk(<= 6MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_38   ((uint8)0x3U) /**< Sample Time in Number of Fclk(<= 8MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_39   ((uint8)0x4U) /**< Sample Time in Number of Fclk(<=10MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_44   ((uint8)0x5U) /**< Sample Time in Number of Fclk(<=12MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_58   ((uint8)0x6U) /**< Sample Time in Number of Fclk(<=14MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_60   ((uint8)0x7U) /**< Sample Time in Number of Fclk(<=16MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_63   ((uint8)0x8U) /**< Sample Time in Number of Fclk(<=18MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_64   ((uint8)0x9U) /**< Sample Time in Number of Fclk(<=20MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_83   ((uint8)0xaU) /**< Sample Time in Number of Fclk(<=22MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD1_DIS_86   ((uint8)0xbU) /**< Sample Time in Number of Fclk(<=24MHz) */

/**
 * Conversion sampling time (HSMODE2 Mode, discharge, measured in Fclk Clock Cycles) 78K0R:\n
 */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_22   ((uint8)0x0U) /**< Sample Time in Number of Fclk(<= 2MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_25   ((uint8)0x1U) /**< Sample Time in Number of Fclk(<= 4MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_42   ((uint8)0x2U) /**< Sample Time in Number of Fclk(<= 6MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_44   ((uint8)0x3U) /**< Sample Time in Number of Fclk(<= 8MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_48   ((uint8)0x4U) /**< Sample Time in Number of Fclk(<=10MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_67   ((uint8)0x5U) /**< Sample Time in Number of Fclk(<=12MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_70   ((uint8)0x6U) /**< Sample Time in Number of Fclk(<=14MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_84   ((uint8)0x7U) /**< Sample Time in Number of Fclk(<=16MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_89   ((uint8)0x8U) /**< Sample Time in Number of Fclk(<=18MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_92   ((uint8)0x9U) /**< Sample Time in Number of Fclk(<=20MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_115  ((uint8)0xaU) /**< Sample Time in Number of Fclk(<=22MHz) */
#define ADC_SAMPLE_CYCLE_HSMOD2_DIS_119  ((uint8)0xbU) /**< Sample Time in Number of Fclk(<=24MHz) */

/**
 * Operation mode (Continuous/One shot , select channel or scan, one INT or all INT).78K0R ADM0/ADMD:\n
 */
#define ADC_CONTINUOUSSELECT              ((uint8)0x0U)
#define ADC_CONTINUOUSSCAN_ALLINT         ((uint8)0x2U)
#define ADC_CONTINUOUSSCAN_ONEINT         ((uint8)0x3U)
#define ADC_ONESHOTSELECT                 ((uint8)0x4U)
#define ADC_ONESHOTSCAN_ALLINT            ((uint8)0x6U)
#define ADC_ONESHOTSCAN_ONEINT            ((uint8)0x7U)

/**
 * Speed mode (High speed mode 1 , mode 2 , normal mode) 78K0R ADM0/ADHS:\n
 */
#define ADC_HIGHSPEED_MODE1              ((uint8)0x0U)
#define ADC_HIGHSPEED_MODE2              ((uint8)0x1U)
#define ADC_NORMAL_MODE                  ((uint8)0x2U)

/**
 * Trigger HW selector (INTTM12 INTTM22 ADTRG) 78K0R ADM1/ADTMS:\n
 */
#define ADC_TRIGGER_INTTM12 0x00U
#define ADC_TRIGGER_INTTM22 0x01U
#define ADC_TRIGGER_ADTRG   0x03U

/**
 * Trigger HW edge setting (No edge, falling, rising, both edges) 78K0R ADM1/ADETS:\n
 */
#define ADC_TRIGGER_NOEDGE 0x00U
#define ADC_TRIGGER_FALLINGEDGE 0x01U
#define ADC_TRIGGER_RISINGEDGE 0x02U
#define ADC_TRIGGER_BOTHEDGE 0x03U

/**
 * Trigger selection (Software / Hardware) 78K0R ADM1/ADTMD:\n
 */
#define ADC_TRIGGER_SOFTWARE              ((uint8)0x0U)
#define ADC_TRIGGER_HARDWARE              ((uint8)0x1U)

/**
 * One channel sample mode FS12
 */
#define ADC_ONE_CHANNEL_SAMPLE_MODE ((uint8)0U)

/**
 * Multi-channle sample mode FS12
 */
#define ADC_MULTI_CHANNEL_SAMPLE_MODE ((uint8)1U)

/**
 * Sequence length register mask. FS12
 */
#define ADC_SEQUENCE_LENGTH_MASK ((uint8)0x78U) /*spec page.:314*/

/**
 * Possible driver statuses:\n
 */
#define ADC_UNINIT    ((uint8)0x69U) /**< UNINIT - driver status */
#define ADC_INIT      ((uint8)0x96U) /**< INIT - driver status */

/*============================================================================*\
 * EXPORTED TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/**
 * \details Possible modes of ADC. \n
 *  Current status of the conversion of the requested ADC Channel group.
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-7-1}{SSA-REQ-ADC-685-1, SSA-REQ-ADC-686-1}
 */
typedef enum
{
   ADC_IDLE      = 0x69U, /**< ADC IDLE state of conversion*/
   ADC_BUSY      = 0x96U, /**< ADC BUSY state of conversion*/
   ADC_COMPLETED = 0x3CU  /**< ADC COMPLETED state of conversion*/
} Adc_StatusType;

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/** \details Unused type since Post-Build variant is not supported in ADC Driver.\n
 * All initialization data comes from statically configured defines from Adc_Cfg.h.\n
 * (Defined only for Adc_Init(Adc_ConfigType*) prototype consistence).
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-8-1}{SSA-REQ-ADC-639-1, SSA-REQ-ADC-641-1}
 */
typedef void Adc_ConfigType;

/** \details Type for ADC channels identifiers. Numberic ID of an ADC channel.
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-9-1}{SSA-REQ-ADC-643-1, SSA-REQ-ADC-644-1, SSA-REQ-ADC-645-1}
 */
typedef uint8 Adc_ChannelType;

/** \details Type for ADC chanel group. Numberic ID of an ADC channel group.
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-10-1}{SSA-REQ-ADC-647-1, SSA-REQ-ADC-648-1, SSA-REQ-ADC-649-1}
 */
typedef uint8 Adc_GroupType;

/**
 * \details Type of conversion result value.
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-11-1}{SSA-REQ-ADC-651-1, SSA-REQ-ADC-656-1, SSA-REQ-ADC-658-1}
 */
typedef uint16 Adc_ValueGroupType;

/**
 * \details Notification function type.
 */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
typedef void (*Adc_NotifiFunctionType)(void);
#endif /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/

/** \details Type of priority level of the group. Lowest priority is 0.
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-13-1}{SSA-REQ-ADC-697-1, SSA-REQ-ADC-698-1, SSA-REQ-ADC-699-1,
 *                             SSA-REQ-ADC-1058-1}
 */
typedef uint8 Adc_GroupPriorityType;

/** \details Group information structure type.\n
 * Implementation specific configuration data structure.
 *
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-32-1}{SSA-REQ-ADC-701-1, SSA-REQ-ADC-970-1, SSA-REQ-ADC-972-1,
 *                             SSA-REQ-ADC-974-1, SSA-REQ-ADC-576-1, SSA-REQ-ADC-577-1,
 *                             SSA-REQ-ADC-578-1, SSA-REQ-ADC-1059-1}
 */
typedef struct Adc_GroupDefType_Tag
{
   Adc_ChannelType first_channel;                /**< First channel in the group */
   Adc_ChannelType length;                       /**< Number of channels in the group */
   Adc_GroupPriorityType priority;               /**< Priority of group */
#if ( STD_ON == ADC_GRP_NOTIF_CAPABILITY )       /**< ADC GRP NOTIF CAPABILITY can be ON or OFF */
   Adc_NotifiFunctionType notification;          /**< Notification depends from ADC GRP NOTIF CAPABILITY */
#endif /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/
   P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) result; /**< Result from ADC conversion */
} Adc_GroupDefType;


typedef uint8 Adc_DriverStatusType;

typedef struct Adc_GroupInfo_Tag
{
   Adc_StatusType adc_group_status;       /* Adc group status data */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
   uint8 notification_flag;               /* Notification flag */
#endif /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/
} Adc_GroupInfoType;

typedef struct Adc_DriverInfo_Tag
{
   Adc_DriverStatusType adc_init_status;         /* Adc init driver status data */
   Adc_StatusType adc_driver_status;             /* Adc driver status data */
} Adc_DriverInfoType;

/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

extern CONST(Adc_GroupDefType, ADC_VAR) Adc_Group[ADC_NB_GROUP+1];

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

/**
 * \details Service for initializing ADC module.\n
 * All initialization is being made with statically configured macros.\n
 *
 * \n
 * \ServID      0x00
 * \Synchronism Synchronous
 * \Reentrancy  Non-reentrant
 *
 * \param[in]   ConfigPt - pointer to configuration data
 *                         (unused, only for function prototype consistence).
 *
 * \return      None
 * \Caveats     None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-14-1}{SSA-REQ-ADC-735-1, SSA-REQ-ADC-743-1, SSA-REQ-ADC-744-1,
 *                             SSA-REQ-ADC-746-1, SSA-REQ-ADC-747-1, SSA-REQ-ADC-748-1,
 *                             SSA-REQ-ADC-749-1, SSA-REQ-ADC-750-1, SSA-REQ-ADC-751-1,
 *                             SSA-REQ-ADC-752-1, SSA-REQ-ADC-966-1, SSA-REQ-ADC-627-1,
 *                             SSA-REQ-ADC-628-1, SSA-REQ-ADC-631-1, SSA-REQ-ADC-1038-1}
 * \latexonly
 * \DSARfigure{Adc_Init.png}{\textwidth}{fig:Fig1}{Adc\_Init function diagram}
 * \endlatexonly
 */
extern void Adc_Init
(
   P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr
);

/**
 *\details Service for deinitializing all used ADC channels to their power on reset state.
 *
 * \ServID       0x01
 * \Synchronism  Synchronous
 * \Reentrancy   Non-reentrant
 *
 * \param None
 *
 * \return       None
 * \Caveats      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-15-1}{SSA-REQ-ADC-757-1, SSA-REQ-ADC-765-1, SSA-REQ-ADC-766-1,
 *                             SSA-REQ-ADC-767-1, SSA-REQ-ADC-768-1, SSA-REQ-ADC-770-1,
 *                             SSA-REQ-ADC-966-1, SSA-REQ-ADC-627-1, SSA-REQ-ADC-628-1,
 *                             SSA-REQ-ADC-631-1}
 * \latexonly
 * \DSARfigure{Adc_DeInit.png}{\textwidth}{fig:Fig1}{Adc\_DeInit function diagram}
 * \endlatexonly
 */
#if (STD_ON == ADC_DEINIT_API)
extern FUNC(void, ADC_CODE) Adc_DeInit
(
   void
);

#endif /*(STD_ON == ADC_DEINIT_API)*/

/**
 *\details  This service shall start the conversion of all channels of the requested\n
 * ADC Channel group. Depending on the group configuration single-shot or continuous\n
 * conversion is started.\n
 * : Continous conversions are not available.
 *
 * \ServID       0x02
 * \Synchronism  Asynchronous
 * \Reentrancy   Re-entrant
 *
 * \param        Group - Numeric ID of requested ADC Channel group
 *
 * \return       None
 * \Caveats      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-16-1}{SSA-REQ-ADC-773-1, SSA-REQ-ADC-781-1, SSA-REQ-ADC-783-1,
 *                             SSA-REQ-ADC-784-1, SSA-REQ-ADC-786-1, SSA-REQ-ADC-788-1,
 *                             SSA-REQ-ADC-789-1, SSA-REQ-ADC-790-1, SSA-REQ-ADC-966-1,
 *                             SSA-REQ-ADC-627-1, SSA-REQ-ADC-628-1, SSA-REQ-ADC-631-1,
 *                             SSA-REQ-ADC-580-1, SSA-REQ-ADC-581-1}
 * \latexonly
 * \DSARfigure{Adc_StartGroupConversion.png}{\textwidth}{fig:Fig1}{Adc\_StartGroupConversion function diagram}
 * \endlatexonly
 */
#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
extern FUNC(void, ADC_CODE) Adc_StartGroupConversion
(
   VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif /*(STD_ON == ADC_ENABLE_START_STOP_GROUP_API)*/

/**
 *\details This service shall return the raw converted values without further scaling.\n
 * The returned values shall be right-aligned.
 *
 * \ServID       0x04
 * \Synchronism  Synchronous
 * \Reentrancy   Re-entrant
 *
 * \param        Group - Numeric ID of requested ADC Channel group.
 *
 * \return       Adc_ValueGroupType - Pointer to the latest conversion results available\n
 *                  for the requested channel group.
 * \Caveats      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-17-1}{SSA-REQ-ADC-812-1, SSA-REQ-ADC-820-1, SSA-REQ-ADC-821-1,
 *                             SSA-REQ-ADC-822-1, SSA-REQ-ADC-823-1, SSA-REQ-ADC-824-1,
 *                             SSA-REQ-ADC-825-1, SSA-REQ-ADC-966-1, SSA-REQ-ADC-627-1,
 *                             SSA-REQ-ADC-628-1, SSA-REQ-ADC-631-1, SSA-REQ-ADC-583-1}
 * \latexonly
 * \DSARfigure{Adc_ValueReadGroup.png}{\textwidth}{fig:Fig1}{Adc\_ValueReadGroup function diagram}
 * \endlatexonly
 */
/*extern FUNC(P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_VAR), ADC_CODE) Adc_ValueReadGroup
(
   VAR(Adc_GroupType, AUTOMATIC) Group
);*/
Adc_ValueGroupType* Adc_ValueReadGroup
(
   Adc_GroupType Group
);

/**
 *\details This service shall enable the notification mechanism for the requested ADC Channel group.
 *
 * \ServID       0x07
 * \Synchronism  Synchronous
 * \Reentrancy   Re-entrant
 *
 * \param        Group - Numeric ID of requested ADC Channel group.
 *
 * \return       None
 * \Caveats      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-18-1}{SSA-REQ-ADC-870-1, SSA-REQ-ADC-878-1, SSA-REQ-ADC-879-1,
 *                             SSA-REQ-ADC-880-1, SSA-REQ-ADC-881-1, SSA-REQ-ADC-966-1,
 *                             SSA-REQ-ADC-627-1, SSA-REQ-ADC-628-1, SSA-REQ-ADC-631-1}
 * \latexonly
 * \DSARfigure{Adc_Enable_GroupNotification.png}{\textwidth}{fig:Fig1}{Adc\_EnableGroupNotification function diagram}
 * \endlatexonly
 */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
extern FUNC(void, ADC_CODE) Adc_EnableGroupNotification
(
   VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/

/**
 *\details This service shall disable the notification mechanism for the requested ADC Channel group.
 *
 * \ServID       0x08
 * \Synchronism  Synchronous
 * \Reentrancy   Re-entrant
 *
 * \param        Group - Numeric ID of requested ADC Channel group.
 *
 * \return       None
 * \Caveats      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-19-1}{SSA-REQ-ADC-886-1, SSA-REQ-ADC-894-1, SSA-REQ-ADC-895-1,
 *                             SSA-REQ-ADC-896-1, SSA-REQ-ADC-897-1, SSA-REQ-ADC-899-1,
 *                             SSA-REQ-ADC-966-1, SSA-REQ-ADC-627-1, SSA-REQ-ADC-628-1,
 *                             SSA-REQ-ADC-631-1}
 * \latexonly
 * \DSARfigure{Adc_Disable_GroupNotification.png}{\textwidth}{fig:Fig1}{Adc\_DisableGroupNotification function diagram}
 * \endlatexonly
 */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
extern FUNC(void, ADC_CODE) Adc_DisableGroupNotification
(
   VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/

/**
 *\details This service shall return the conversion status of the requested ADC Channel group.
 *
 * \ServID       0x09
 * \Synchronism  Synchronous
 * \Reentrancy   Re-entrant
 *
 * \param        Group - Numeric ID of requested ADC Channel group.
 *
 * \return       Adc_StatusType - Conversion status for the requested group.
 * \Caveats      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-20-1}{SSA-REQ-ADC-902-1, SSA-REQ-ADC-910-1, SSA-REQ-ADC-911-1,
 *                             SSA-REQ-ADC-912-1, SSA-REQ-ADC-913-1, SSA-REQ-ADC-914-1,
 *                             SSA-REQ-ADC-915-1, SSA-REQ-ADC-916-1, SSA-REQ-ADC-917-1,
 *                             SSA-REQ-ADC-919-1, SSA-REQ-ADC-966-1, SSA-REQ-ADC-627-1,
 *                             SSA-REQ-ADC-628-1, SSA-REQ-ADC-631-1}
 * \latexonly
 * \DSARfigure{Adc_GetGroupStatus.png}{\textwidth}{fig:Fig1}{Adc\_GetGroupStatus function diagram}
 * \endlatexonly
 */
extern FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus
(
   VAR(Adc_GroupType, AUTOMATIC) Group
);

/*============================================================================*\
 * FUNCTION:
\*============================================================================*/
/**
 *\details This service shall provide interrupt mechanism for current ADC group.
 *
 * \ServID      None
 * \Synchronism Synchronous
 * \Reentrancy  Re-entrant
 *
 * \param       None
 * \return      None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-ADC-21-1}{SSA-REQ-ADC-969-1, SSA-REQ-ADC-782-1, SSA-REQ-ADC-971-1,
 *                             SSA-REQ-ADC-973-1, SSA-REQ-ADC-584-1}
 * \latexonly
 * \DSARfigure{Adc_Isr_ConvFinished.png}{0.7\textwidth}{fig:Fig1}{Adc\_ConvFinished function diagram}
 * \endlatexonly
 */
extern FUNC(void, ADC_CODE) Adc_Isr_ConvFinished
(
   void
);

/*============================================================================*\
 * EXPORTED FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/** \brief This service returns the version information of this module.
 * \details The version information includes: Module Id, Vendor Id,
 * Vendor specific version numbers.
 *
 *
 * \ServID       0xA
 * \Synchronism  Synchronous
 * \Reentrancy   Non-reentrant
 *
 * \param[in]    None
 * \param[out]   versioninfo   Pointer to where to store the version information of this module
 *
 * \Return       None
 * \Caveats      None
 *
 * \Requirements
 * \reqtrace{SSA-SDD-ADC-22-1}{SSA-REQ-ADC-943-1, SSA-REQ-ADC-951-1}
 */
#if (STD_ON == ADC_VERSION_INFO_API)
   #define Adc_GetVersionInfo(versioninfo)                       \
   do {                                                          \
      if ( NULL_PTR != (versioninfo) )                           \
      {                                                          \
         (versioninfo)->vendorID = ADC_VENDOR_ID;                \
         (versioninfo)->moduleID = ADC_MODULE_ID;                \
         (versioninfo)->sw_major_version = ADC_SW_MAJOR_VERSION; \
         (versioninfo)->sw_minor_version = ADC_SW_MINOR_VERSION; \
         (versioninfo)->sw_patch_version = ADC_SW_PATCH_VERSION; \
      }                                                          \
   } while (0)
#endif /*(STD_ON == ADC_VERSION_INFO_API)*/

/*============================================================================*\
 * FILE REVISION HISTORY
 *-----------------------------------------------------------------------------
 *
 *  DATE          REV         SCR               AUTHOR
 *      SUMMARY OF CHANGES
 *  ---------------------------------------------------------------------------
 *  02-May-2011   1.1.2                       Wade Li
 *    - initial change for ICS project
 *  ---------------------------------------------------------------------------
 *  21-Oct-2010   1.1.1       tck_ssa#157      pawel.zawalski(at).com
 *    - Setings of INTAD priority removed from Adc_StartGroupConversion()
 *      (priority mechanism introduced in Irq module)
 *    - Adc_SetGroupConversion updated to be able start converion of 'group'
 *      marked as 'ADC_COMPLETED'
 *  ---------------------------------------------------------------------------
 *  30-Sep-2010   1.1.0       tck_ssa#154      pawel.zawalski(at).com
 *    - ADC_SAMPLE_CYCLE_HSMODE1_DIS_19 parameter defined twice in EPD
 *    - modyfied short names of some enum literals (some of them are to long)
 *  ---------------------------------------------------------------------------
 *  22-Sep-2010   1.0.2       tck_ssa#149      pawel.zawalski(at).com
 *    - Corrected wrong settings for ADS register in Adc_SetGroupConversion()
 *      local function.
 *    - Adc_ConvFinished() function name changet to Adc_Isr_ConvFinished
 *      to follow new SSA naming convention for interrupt service routines.
 *  ---------------------------------------------------------------------------
 *  20-Aug-2010   1.0.1       tck_ssa#124      pawel.zawalski(at).com
 *    - File updated after peer reviews (SDD-85202.4886, code-85203.0405)
 *  ---------------------------------------------------------------------------
 *  17-Jun-2010   1.0.0       tck_ssa#124       pawel.zawalski(at).com
 *    - File creation
 *  ---------------------------------------------------------------------------
\*============================================================================*/

/* END OF FILE -------------------------------------------------------------- */
#endif /* ADC_H */

