/*============================================================================*\
 * \b Application:        ADC \n
 * \b Target:             see Adc.h\n
 * \b Compiler:           see Adc.h\n
 * \b Module:             Adc.c \n
 * \b File-Revision:      1.1.1 \n
 * \b Changeable-by-user: No \n
 * \b Module-Owner:       see Adc.h \n
 * \b Last-Modified:      Tue Oct 26 14:22:09 2010 \n
 * \b Classification:     CONFIDENTIAL \n
\*============================================================================*/
/**\file
 *
 * \brief Source File for Small Sysytem Architecture of ADC module.
 * \details This file contains the functionality of the public interface
 * of the ADC module for SSA.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-ADC-1-1}{SSA-REQ-ADC-394-1, SSA-REQ-ADC-395-2, SSA-REQ-ADC-1088-1,
 *                            SSA-REQ-ADC-1089-1, SSA-REQ-ADC-1100-2, SSA-REQ-ADC-1102-2}
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
#include "Adc.h"
#include "SchM_Adc.h"


#if (STD_ON == ADC_DEV_ERROR_DETECT)
#include "Det.h"
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/

/*
 * Version controls for Adc.h file.
 */
#define EXPECTED_ADC_AR_MAJOR_VERSION (2u)
#define EXPECTED_ADC_AR_MINOR_VERSION (1u)
#define EXPECTED_ADC_AR_PATCH_VERSION (0u)

#define EXPECTED_ADC_H_MAJOR_VERSION (1u)
#define EXPECTED_ADC_H_MINOR_VERSION (1u)

#if ( (ADC_AR_MAJOR_VERSION != EXPECTED_ADC_AR_MAJOR_VERSION) || \
      (ADC_AR_MINOR_VERSION != EXPECTED_ADC_AR_MINOR_VERSION) || \
      (ADC_AR_PATCH_VERSION != EXPECTED_ADC_AR_PATCH_VERSION) )
#error "AUTOSAR version mismatch between Adc.c and Adc.h files."
#endif

#if ( (ADC_SW_MAJOR_VERSION != EXPECTED_ADC_H_MAJOR_VERSION) || \
      (ADC_SW_MINOR_VERSION != EXPECTED_ADC_H_MINOR_VERSION) )
#error "The version of the Adc.c file does not match the version of the Adc.h file."
#endif

#if ( STD_ON == ADC_DEV_ERROR_DETECT )
   #if ( (DET_AR_MAJOR_VERSION != EXPECTED_ADC_AR_MAJOR_VERSION) || \
         (DET_AR_MINOR_VERSION != EXPECTED_ADC_AR_MINOR_VERSION) )
   #error "AUTOSAR version mismatch between Adc.c and Det.h modules."
   #endif
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/

/* SchM_Adc.h version checking */
#if ((SCHM_ADC_AR_MAJOR_VERSION != EXPECTED_ADC_AR_MAJOR_VERSION) || \
     (SCHM_ADC_AR_MINOR_VERSION != EXPECTED_ADC_AR_MINOR_VERSION) )
#error "AUTOSAR version mismatch between Adc.c and SchM_Adc.h files."
#endif

/* LOCAL DEFINES FOR CONSTANTS -----------------------------------------------*/

/*
 * Bit offset in byte:\n
 */
#define ADC_BIT_OFFSET_0  ((uint8)0)  /**< ADC bit offset = 0*/
#define ADC_BIT_OFFSET_1  ((uint8)1)  /**< ADC bit offset = 1*/
#define ADC_BIT_OFFSET_2  ((uint8)2)  /**< ADC bit offset = 2*/
#define ADC_BIT_OFFSET_3  ((uint8)3)  /**< ADC bit offset = 3*/
#define ADC_BIT_OFFSET_4  ((uint8)4)  /**< ADC bit offset = 4*/
#define ADC_BIT_OFFSET_5  ((uint8)5)  /**< ADC bit offset = 5*/
#define ADC_BIT_OFFSET_6  ((uint8)6)  /**< ADC bit offset = 6*/
#define ADC_BIT_OFFSET_7  ((uint8)7)  /**< ADC bit offset = 7*/
#define ADC_BIT_OFFSET_8  ((uint8)8)  /**< ADC bit offset = 8*/
#define ADC_BIT_OFFSET_9  ((uint8)9)  /**< ADC bit offset = 9*/
#define ADC_BIT_OFFSET_10 ((uint8)10) /**< ADC bit offset = 10*/
#define ADC_BIT_OFFSET_11 ((uint8)11) /**< ADC bit offset = 11*/
#define ADC_BIT_OFFSET_12 ((uint8)12) /**< ADC bit offset = 12*/
#define ADC_BIT_OFFSET_13 ((uint8)13) /**< ADC bit offset = 13*/
#define ADC_BIT_OFFSET_14 ((uint8)14) /**< ADC bit offset = 14*/
#define ADC_BIT_OFFSET_15 ((uint8)15) /**< ADC bit offset = 15*/


/** Out of range value report to the ADC user that converted value is no
 *  available. (value depends on ADC_CONVERSION_MODE)
 */
#define ADC_OUT_OF_RANGE_VAL   ((Adc_ValueGroupType)0x0FFF)

/**
 * Registers reset value.
 */

/* A/D converter mode register 0 (ADM0) */
#define ADC_ADM0_RESET_VAL    ((uint8)0x00)
/* A/D converter mode register 1 (ADM1) */
#define ADC_ADM1_RESET_VAL    ((uint8)0x00)
/*  A/D port configuration register (ADPC) */
#define ADC_ADPC_RESET_VAL    ((uint8)0x00)
/* Analog input channel specification register (ADS) */
#define ADC_ADS_RESET_VAL     ((uint8)0x00)
/* A/D conversion time setting register (ADSMP) */
#define ADC_ADSMP_RESET_VAL   ((uint8)0x00)

/* LOCAL DEFINE MACROS (#, ##) -----------------------------------------------*/

/*============================================================================*\
 * LOCAL TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
 * OBJECT DEFINITIONS
\*============================================================================*/

/* EXPORTED OBJECTS ----------------------------------------------------------*/

/* LOCAL OBJECTS -------------------------------------------------------------*/

/* PRQA S 5087 EOF
 * MISRA RULE 19.1 VIOLATION:
 * #include added at several places to meet the requirements of Memory mapping.
 */
#define ADC_START_SEC_VAR_8BIT
#include "MemMap.h"
/**
 * Currently converted group.
 */
/* ADC_NB_GROUP refers in this case to DUMMY_GROUP */
_STATIC_ VAR(Adc_GroupType, ADC_VAR) Adc_CurrentGroup = ADC_NB_GROUP;

#define ADC_STOP_SEC_VAR_8BIT
#include "MemMap.h"
/**
 * Initialization status flag.
 */

#define ADC_START_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"

/* ADC group flags
 * Size equal to ADC_NB_GROUP+1 because of introduced dummy group
 */

_STATIC_ VAR(Adc_GroupInfoType, ADC_VAR) Adc_GroupInfo[ADC_NB_GROUP+1];

/* ADC driver runtime flags */
_STATIC_ VAR(Adc_DriverInfoType, ADC_VAR) Adc_DriverFlags = {ADC_UNINIT, ADC_IDLE};

#define ADC_STOP_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"


/*============================================================================*\
 * LOCAL FUNCTION PROTOTYPES
\*============================================================================*/

/**
 *\details  This service shall set current group and current channel values and in next step\n
 *  enable the conversion of all channels of the requested ADC Channel group.\n
 *
 * \param        Group - Numeric ID of requested ADC Channel group.
 *
 * \latexonly
 * \DSARfigure{Adc_SetGroupConversion.png}{0.6\textwidth}{fig:Fig1}{Adc\_SetGroupConversion function diagram}
 * \endlatexonly
 */
_STATIC_ void Adc_SetGroupConversion
(
   Adc_GroupType Group
);

/*============================================================================*\
 * LOCAL FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * LOCAL FUNCTIONS
\*============================================================================*/

#define ADC_START_SEC_CODE
#include "MemMap.h"


/*============================================================================*\
 * FUNCTION: Adc_SetGroupConversion
 *
 * begin to convert group from first channel to end
\*============================================================================*/
_STATIC_ void Adc_SetGroupConversion
(
   Adc_GroupType Group
)
{
   /* Enter critical section, nothing to do */
   SchM_Enter_Adc(ADC_EXCLUSIVE_AREA_0);
   if ( ADC_BUSY != Adc_GroupInfo[Group].adc_group_status )
   {
      Adc_CurrentGroup = Group;
      Adc_GroupInfo[Group].adc_group_status = ADC_BUSY;

      /* Analog input channel specification register (ADS) - scan mode*/
      ADS = Adc_Group[Group].first_channel + Adc_Group[Group].length - 1U;

      ADCS = 1; /* Enables conversion operation */
   }
   /* Exit critical section */
   SchM_Exit_Adc(ADC_EXCLUSIVE_AREA_0);
}

/*============================================================================*\
 * EXPORTED FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * FUNCTION: Adc_Init()
\*============================================================================*/
void Adc_Init
(
   P2CONST( Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr
)
{
   Adc_GroupType gr_idx = 0;
   Adc_ChannelType ch_idx = 0;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
   if (NULL_PTR != ConfigPtr)
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_INIT,
                      ADC_E_PARAM_CONFIG);
   }
   else
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   if (ADC_INIT != Adc_DriverFlags.adc_init_status)
   {
      /* Release the reset state of the A/D converter and start clock supply */
      ADCEN = 1;
      /* Disable AD conversion and clear ADM0 register */
      ADM0 = ADC_ADM0_RESET_VAL;
      /* setting ADM0 register */
      ADM0 = (uint8)((uint8)(((uint8)ADC_DISCHARGE_BEFORE_SAMPLING) << ADC_BIT_OFFSET_3)
                   | (uint8)(((uint8)ADC_SPEED_MODE) << ADC_BIT_OFFSET_1));
      /* Enables A/D voltage comparator operation - Conversion waiting mode */
      /* need to wait 1microsec, or ignore data of 1st conversion */
      ADCE = 1;
      /* setting ADM1 register */
      ADM1 = (uint8)(ADC_TRIGGER_SELECTOR);
      /*Setting ADSMP register, ??*/
      ADSMP = ADC_SAMPLE_TIME_SELECTOR;
      /* ADM0 Select the operation mode*/
      ADM0 = (uint8)((uint8)ADM0 | (uint8)(ADC_OPERATION_MODE << ADC_BIT_OFFSET_4));
      
      for ( gr_idx = 0; gr_idx < ADC_NB_GROUP; gr_idx++)
      {
         for ( ch_idx = 0; ch_idx < Adc_Group[gr_idx].length; ch_idx++ )
         {
            Adc_Group[gr_idx].result[ch_idx] = (Adc_ValueGroupType)ADC_OUT_OF_RANGE_VAL;
         }
         Adc_GroupInfo[gr_idx].adc_group_status = ADC_IDLE;
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
         Adc_GroupInfo[gr_idx].notification_flag = FALSE;
#endif  /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/
      }
      Adc_GroupInfo[ADC_NB_GROUP].adc_group_status=ADC_IDLE;
      Adc_DriverFlags.adc_init_status = ADC_INIT;
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_INIT,
                      ADC_E_UNINIT);
   }
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
}

/*============================================================================*\
 * FUNCTION: Adc_DeInit()
\*============================================================================*/
#if (STD_ON == ADC_DEINIT_API)
FUNC(void, ADC_CODE) Adc_DeInit
(
   void
)
{
   Adc_GroupType gr_idx = 0;
   Adc_ChannelType ch_idx = 0;

   if (ADC_UNINIT != Adc_DriverFlags.adc_init_status)
   {
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      for ( gr_idx = 0; gr_idx < ADC_NB_GROUP; gr_idx++)
      {
         if (ADC_BUSY == Adc_GroupInfo[gr_idx].adc_group_status)
         {
            Adc_DriverFlags.adc_driver_status = ADC_BUSY;
            break;
         }
      }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
      if ( ADC_BUSY != Adc_DriverFlags.adc_driver_status)
      {
         /* ADM0 register settings */
         ADM0 = ADC_ADM0_RESET_VAL;
         /* ADM1 register */
         ADM1 = ADC_ADM1_RESET_VAL;
         /* ADS register */
         ADS = ADC_ADS_RESET_VAL;
         /* ADSMP register */
         ADSMP = ADC_ADSMP_RESET_VAL;
         /* PER0 register bit ADCEN settings */
         ADCEN = 0;            /* no more clock on ADC */
         /* Stops A/D voltage comparator operation */
         ADCE=0;

         for ( gr_idx = 0; gr_idx < ADC_NB_GROUP; gr_idx++)
         {
            for ( ch_idx = 0; ch_idx < Adc_Group[gr_idx].length; ch_idx++ )
            {
               Adc_Group[gr_idx].result[ch_idx] = (Adc_ValueGroupType)ADC_OUT_OF_RANGE_VAL;
            }
            Adc_GroupInfo[gr_idx].adc_group_status = ADC_IDLE;
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
            Adc_GroupInfo[gr_idx].notification_flag = FALSE;
#endif  /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/
         }

         Adc_DriverFlags.adc_init_status = ADC_UNINIT;
         Adc_DriverFlags.adc_driver_status = ADC_IDLE;
         /* In this case ADC_NB_GROUP refers to DUMMY group */
         Adc_CurrentGroup = ADC_NB_GROUP;
         /* Dummy group */
         Adc_GroupInfo[ADC_NB_GROUP].adc_group_status=ADC_IDLE;
      }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      else
      {
         Det_ReportError(ADC_MODULE_ID,
                         ADC_INSTANCE_ID,
                         ADC_API_ID_DEINIT,
                         ADC_E_BUSY);
      }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_DEINIT,
                      ADC_E_UNINIT);
   }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
}
#endif  /*(STD_ON == ADC_DEINIT_API)*/

/*============================================================================*\
 * FUNCTION: Adc_StartGroupConversion()
 * ADC288 - : Priority mechanism is optionally configurable (on/off)
 *                  and optionally implementable (i.e.present for 78Kx2 and
 *                  not present for Freescale uC).
\*============================================================================*/
#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
void Adc_StartGroupConversion
(
   Adc_GroupType Group
)
{
   if (ADC_UNINIT != Adc_DriverFlags.adc_init_status)
   {
      if (Group < ADC_NB_GROUP)
      {
         /* No ongoing conversion */
         if ( ADC_BUSY != Adc_GroupInfo[Adc_CurrentGroup].adc_group_status )
         {
            /* Enable INTAD interrupt */
            ADMK = 0U;
            /* Clear INTAD interrupt flag */
            ADIF = 0U;
            Adc_SetGroupConversion(Group);
         }
#if ( STD_ON == ADC_GRP_PRIORITY_IMP_LEVEL )
         else if ( Adc_Group[Group].priority > Adc_Group[Adc_CurrentGroup].priority )
         {
            /* Stop actual conversion */
            ADCS=0;
            /* Run new request */
            /* Restart conversion for new group and abort current group */
            /* Enable INTAD interrupt */
            ADMK = 0U;
            /* Clear INTAD interrupt flag */
            ADIF = 0U;
            Adc_GroupInfo[Adc_CurrentGroup].adc_group_status = ADC_IDLE;
            Adc_SetGroupConversion(Group);
         }
#endif /* ( STD_ON == ADC_GRP_PRIORITY_IMP_LEVEL ) */
#if (STD_ON == ADC_DEV_ERROR_DETECT)
         else
         {
            Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_START_GROUP_CONVERSION,
                      ADC_E_BUSY);
         }
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
      }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      else
      {
         Det_ReportError(ADC_MODULE_ID,
                         ADC_INSTANCE_ID,
                         ADC_API_ID_START_GROUP_CONVERSION,
                         ADC_E_PARAM_GROUP);
      }
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_START_GROUP_CONVERSION,
                      ADC_E_UNINIT);
   }
#endif /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
}
#endif  /*(STD_ON == ADC_ENABLE_START_STOP_GROUP_API)*/

/*============================================================================*\
 * FUNCTION: Adc_ValueReadGroup()
 * wade: add status check function. if the status is busy, don't read it now.
\*============================================================================*/
Adc_ValueGroupType* Adc_ValueReadGroup
(
   Adc_GroupType Group
)
{
   P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA ) ret_value = NULL_PTR;
   Adc_StatusType grp_state;

    //wade added
   grp_state = Adc_GetGroupStatus(Group);
   if ((ADC_UNINIT != Adc_DriverFlags.adc_init_status) && (grp_state != ADC_BUSY))
   {
      if (Group < ADC_NB_GROUP)
      {
         ret_value = Adc_Group[Group].result;
         Adc_GroupInfo[Group].adc_group_status = ADC_IDLE;
      }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      else
      {
         Det_ReportError(ADC_MODULE_ID,
                         ADC_INSTANCE_ID,
                         ADC_API_ID_VALUE_READ_GROUP,
                         ADC_E_PARAM_GROUP);
      }
#endif /*(ON==ADC_DEV_ERROR_DETECT)*/
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   /* if module is not initialized */
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_VALUE_READ_GROUP,
                      ADC_E_UNINIT);
   }
#endif /*(ON==ADC_DEV_ERROR_DETECT)*/
   return ret_value;
}

/*============================================================================*\
 * FUNCTION: Adc_EnableGroupNotification()
\*============================================================================*/
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
FUNC(void, ADC_CODE) Adc_EnableGroupNotification
(
   VAR(Adc_GroupType, AUTOMATIC) Group
)
{
   if (ADC_UNINIT != Adc_DriverFlags.adc_init_status)
   {
      if (Group < ADC_NB_GROUP)
      {
         if ( NULL_PTR != Adc_Group[Group].notification )
         {
            if ( FALSE == Adc_GroupInfo[Group].notification_flag )
            {
               /*Enable notifications by setting notifi flag*/
               Adc_GroupInfo[Group].notification_flag = TRUE;
            }
         }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
         else
         {
            Det_ReportError(ADC_MODULE_ID,
                            ADC_INSTANCE_ID,
                            ADC_API_ID_ENABLE_GROUP_NOTIFICATION,
                            ADC_E_NOTIF_CAPABILITY);
         }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
      }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      else
      {
         Det_ReportError(ADC_MODULE_ID,
                         ADC_INSTANCE_ID,
                         ADC_API_ID_ENABLE_GROUP_NOTIFICATION,
                         ADC_E_PARAM_GROUP);
      }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_ENABLE_GROUP_NOTIFICATION,
                      ADC_E_UNINIT);
   }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
}
#endif  /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/

/*============================================================================*\
 * FUNCTION: Adc_DisableGroupNotification()
\*============================================================================*/
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
FUNC(void, ADC_CODE) Adc_DisableGroupNotification
(
   VAR(Adc_GroupType, AUTOMATIC) Group
)
{
   if (ADC_UNINIT != Adc_DriverFlags.adc_init_status)
   {
      if (Group < ADC_NB_GROUP)
      {
         if ( NULL_PTR != Adc_Group[Group].notification )
         {
            if ( TRUE == Adc_GroupInfo[Group].notification_flag )
            {
               /*Disable notifications by clearing notifi flag*/
               Adc_GroupInfo[Group].notification_flag = FALSE;
            }
         }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
         else
         {
            Det_ReportError(ADC_MODULE_ID,
                            ADC_INSTANCE_ID,
                            ADC_API_ID_DISABLE_GROUP_NOTIFICATION,
                            ADC_E_NOTIF_CAPABILITY);
         }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
      }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      else
      {
         Det_ReportError(ADC_MODULE_ID,
                         ADC_INSTANCE_ID,
                         ADC_API_ID_DISABLE_GROUP_NOTIFICATION,
                         ADC_E_PARAM_GROUP);
      }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_DISABLE_GROUP_NOTIFICATION,
                      ADC_E_UNINIT);
   }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
}
#endif  /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/

/*============================================================================*\
 * FUNCTION: Adc_GetGroupStatus()
\*============================================================================*/
Adc_StatusType Adc_GetGroupStatus
(
   VAR(Adc_GroupType, AUTOMATIC) Group
)
{
   Adc_StatusType ret_value = (Adc_StatusType)ADC_IDLE;

   if (ADC_UNINIT != Adc_DriverFlags.adc_init_status)
   {
      if (Group < ADC_NB_GROUP)
      {
         ret_value = Adc_GroupInfo[Group].adc_group_status;
      }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
      else
      {
         Det_ReportError(ADC_MODULE_ID,
                         ADC_INSTANCE_ID,
                         ADC_API_ID_GET_GROUP_STATUS,
                         ADC_E_PARAM_GROUP);
      }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
   else
   {
      Det_ReportError(ADC_MODULE_ID,
                      ADC_INSTANCE_ID,
                      ADC_API_ID_GET_GROUP_STATUS,
                      ADC_E_UNINIT);
   }
#endif  /*(STD_ON == ADC_DEV_ERROR_DETECT)*/
   return ret_value;
}

/*============================================================================*\
 * FUNCTION: Interrupt Adc_Isr_ConvFinished()
\*============================================================================*/
void Adc_Isr_ConvFinished
(
   void
)
{
   Adc_ChannelType ch_idx = 0;

/* PRQA S 0310 ++
   MISRA RULE 3.1 VIOLATION:
   result_ptr it's pointer to ADC result registers (ADCR0 and ADCR0H).
*/
#if (ADC_CONV_RES_10_BIT == ADC_CONVERSION_MODE)
   /*10-bit A/D conversion result register (ADCR0)*/
   P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA ) result_ptr = ((Adc_ValueGroupType*)&ADCR0);
#else
   /*8-bit A/D conversion result register (ADCR0H)*/
   P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA ) result_ptr = ((Adc_ValueGroupType*)&ADCR0H);
#endif /* (ADC_CONV_RES_10_BIT == ADC_CONVERSION_MODE) */
/* PRQA S 0310 --
 */

   /* Clear interrupt flag automatically done by interrupt servicing */
   if ( (Adc_CurrentGroup < ADC_NB_GROUP)
        && (Adc_GroupInfo[Adc_CurrentGroup].adc_group_status == ADC_BUSY) )
   {
      for ( ch_idx = 0; ch_idx < Adc_Group[Adc_CurrentGroup].length; ch_idx++ )
      {
         #if (ADC_CONV_RES_10_BIT == ADC_CONVERSION_MODE)
         Adc_Group[Adc_CurrentGroup].result[ch_idx] = 
            (result_ptr[Adc_Group[Adc_CurrentGroup].first_channel + ch_idx] >> ADC_BIT_OFFSET_6);
         #else
         Adc_Group[Adc_CurrentGroup].result[ch_idx] = 
             result_ptr[Adc_Group[Adc_CurrentGroup].first_channel + ch_idx];
         #endif /* (ADC_CONV_RES_10_BIT == ADC_CONVERSION_MODE) */
      }
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
      if ( ( NULL_PTR != Adc_Group[Adc_CurrentGroup].notification )
           && ( TRUE == Adc_GroupInfo[Adc_CurrentGroup].notification_flag ) )
      {
         Adc_Group[Adc_CurrentGroup].notification();
      }
#endif /*(STD_ON == ADC_GRP_NOTIF_CAPABILITY)*/
      Adc_GroupInfo[Adc_CurrentGroup].adc_group_status = ADC_COMPLETED;
   }
   /* Disable INTAD interrupt */
   ADMK = 1U;
}

#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/* END OF FILE -------------------------------------------------------------- */

