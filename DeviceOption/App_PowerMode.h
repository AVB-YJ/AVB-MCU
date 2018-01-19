#ifndef APP_PMD_H
#define APP_PMD_H

/*===================================================================*
*--------------------------------------------------------------------
* Module Name:     Application power mode
* Created By:      Wade Li
* Created Date:    4/04/2011
* %version:        12 %cvtype:         incl %instance:       ctc_aud_1 %
*--------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description   : power moding control head file
 *                   
 *            
 *-----------------------------------------------------------------------------*/

/*============================================================================*\
*
* Preprocessor #include directive(s)
*
\*============================================================================*/

 #include "OS.h"

/*============================================================================*\
*
* Exported preprocessor #define constants (object-like macros), upper case
*
\*============================================================================*/

/*============================================================================*\
*
* Exported preprocessor #define macros (i.e., those using # or ## operator),
* upper case
*
\*============================================================================*/

/*============================================================================*\
*
* Exported type declarations (enum, struct, union, typedef), mixed case
*
\*============================================================================*/

/*! \enum PWR_MANAGE_STATUS_t
 * List of power manager status
 */
typedef enum PWR_MANAGE_STATUS_type
{
  PWR_MANAGE_IDLE,
  PWR_MANAGE_POWERING_UP,
  PWR_MANAGE_POWER_FAILED,
  PWR_MANAGE_NORMAL,
  PWR_MANAGE_OVER_VOLTAGE,
  PWR_MANAGE_UNDER_VOLTAGE,
  PWR_MANAGE_RESET,
  PWR_MANAGE_MAX
}PWR_MANAGE_STATUS_t;

 /**********************************************************************
 * Global Enumerations and Structures and Typedefs                     
 *********************************************************************/


/*============================================================================*\
*
* Exported object declarations, mixed case
*
\*============================================================================*/

/*============================================================================*\
*
* Exported function prototypes (including function-header-block),
* (without "extern"), mixed case
*
\*============================================================================*/

void Power_Task(void);
void App_PowerMode_Start(void);
void App_PowerMode_Init(void);
void App_PowerMode_Stop(void);
extern boolean Power_Check_Battery_Status(void);
static void Power_Powerfail_Check(void);
extern PWR_MANAGE_STATUS_t Power_Get_Power_Status(void);
extern void Configure_CAN_Transcvr_Wakeup(void);
extern void Configure_CAN_Transcvr_Normal(void);
#endif /* APP_PMD_H */

/*******************************************************************************
*
* Changes for ICS  program
*
* Date        By                        Change
* ----------------------------------------------------------------------
* 04-April-11  Wade Li      Created the initial module for ICS
* 30-Dec  -11  Wade Li      update the comments to follow DOXYGEN
*******************************************************************************/

