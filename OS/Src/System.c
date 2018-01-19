/*******************************************************************
 **************************************************************************
 **************************************************************************
*  Title                    : SYSTEM.C
*
*  Module Description       : This file contains application specific model 
*                             information for SYSTEM. it defined the specific 
*                             application for each module
*
*  Author                   : Wade Li
*  Created Date:              08/06/2011
*  %version:                  6 %
*  date_created:              Tue Augest 7 13:02:04 2011 %
*--------------------------------------------------------------------*/

/*============================================================================*\
 *
 * Preprocessor #include directive(s)
 *
\*============================================================================*/
#include "System.h"
#include "Nvm.h"


#define SYS_SW_ID_LEN 5
/*============================================================================*\
 *
 * Local object definitions, mixed case
 *
\*============================================================================*/

/*============================================================================
product info, added for formal version check, 20110817
for example: 0xAA, 0x10, 0x18,   0xAA, 0x01};  
                |     |     |     |     |
                |     |     |     |     |____Revision of Subproject
                |     |     |     |__________Subproject ID
                |     |_____|________________Project ID (w/ Product Line byte)
                |____________________________Product Line - MMM / Smart Radios


==============================================================================*/
//wade.li updated on 20120524, for PV delivery
static const uint8_t   sy_swid[SYS_SW_ID_LEN] = {0xAA, 0x11, 0x02, 0xAA, 0x07};/*update for PV build, Jan 21 2013*/

//internal version\

static const uint8_t SW_Version[] = {'2', '0', '0', '9'}; /*updated on April 24 2013,
                               |   |   |   
                               
                               |   |   |   
                               |   |__|________Version number during current milestone
                               |    
                               |___________________development milestone number: 1 for EDU, 2 for DV, etc*/
/*============================================================================*\
 *
 * Local function prototypes, mixed case
 *
\*============================================================================*/


/*==============================================================================
* FUNCTION: SY_Swid
*===============================================================================
* Return Value:
*    return the current sw ID 
* Parameters:
*    None
*
* Description:
*    return sw id for current model
*=============================================================================*/
extern const uint8_t * SY_Swid (void)
{
   return (sy_swid);
}
                               
const uint16_t App_Checksum;

/*==============================================================================
* FUNCTION: SY_Dbid
*===============================================================================
* Return Value:
*    return the current sw version, mini-version 
* Parameters:
*    None
*
* Description:
*    return sw mini-version for current model test
*=============================================================================*/
extern const uint8_t * SY_Dbid (void)
{
   uint16_t i = App_Checksum;
   return (SW_Version);
}

#pragma location="CHECKSUM"
const uint16_t App_Checksum = 0xFFFF;

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------
*
* Changes for ICS  program
*
* Date            By                        Change
* -------------------------------------------------------------------------------
* 17-Aug-2011   Wade    change version info from EcuM.c
* 03-Aug-2011   Wade    initiate system 
*******************************************************************************************/

