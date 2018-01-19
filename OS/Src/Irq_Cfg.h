#ifndef IRQ_CFG_H
#define IRQ_CFG_H
 /*-----------------------------------------------------------------------------
 * Copyright  Electronics & Safety. All rights reserved.
 ******************************************************************************/
/* Module Name:    irq
* Created By:      wade.li
* Created Date:    01/30/2012
* %version:        1 %
* date_created:  Tue January 30 13:02:04 2012 %
*--------------------------------------------------------------------*/

/**\file
 * \brief Configuration file for SSA IRQ driver.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-IRQ-XX}{}
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

#include "Std_Types.h"


/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/

/* EXPORTED DEFINES FOR CONSTANTS --------------------------------------------*/


/* PRQA S 288 ++
   MISRA RULE 3.1 VIOLATION:
   Character (at) is required for doxygen syntax.
 */
/** \defgroup VersionInfo_Cfg
 * \name Published information:
 * \details
 * 1. Software major, minor and patch version of this file. \n
 * \n
 * Note: Specific numbers are given only as an example of implementation.\n
 *
 * \Requirements
 * \reqtrace{SSA-SDD-IRQ-XX}{}
 * @{
 */
#define IRQ_CFG_H_SW_MAJOR_VERSION (1u)
#define IRQ_CFG_H_SW_MINOR_VERSION (0u)
#define IRQ_CFG_H_SW_PATCH_VERSION (1u)
/* @}*/
/* PRQA S 288 -- */



/* EXPORTED DEFINE MACROS (#, ##) --------------------------------------------*/

/* ICS reconfigured the priority, 20120120
strategy: set LIN Rx/Tx/Sx to high priority, set tick to high priority, other is low priority*/

//set LTPR00:0, LTPR10:0, highest priority for INTLT0
#define IRQ_PR00_VAL ((uint16)0x7FFFU)
#define IRQ_PR10_VAL ((uint16)0x7FFFU)

//set LRPR00:0, LRPR10:0, highest priority for INTLR0
//set LSPR00:0, LSPR00:0, highest priority for INTLS0
//set LTPR01:0, LTPR11:0, highest priority for INTLT1
//set LRPR01:0, LRPR11:0, highest priority for INTLR1
//set LSPR01:0, LSPR11:0, highest priority for INTLS1
#define IRQ_PR01_VAL ((uint16)0xF1FCU)
#define IRQ_PR11_VAL ((uint16)0xF1FCU)

#define IRQ_PR02_VAL ((uint16)0xFFFFU)
#define IRQ_PR12_VAL ((uint16)0xFFFFU)

#define IRQ_PR03_VAL ((uint16)0xFFFFU)
#define IRQ_PR13_VAL ((uint16)0xFFFFU)

//TICK priority set is in CG_TIMER initiate. 20120120


/*
	External Interrupt Rising Edge Enable Register (EGP)
*/
/* INTPn pin valid edge selection(EGPn) */
#define _00_INTP_EGP_RESET_VALUE		0x00U	/* external interrupt rising edge enable register value after reset */
#define _01_INTP0_EDGE_RISING_SEL		0x01U	/* rising edge selected for INTP0 pin */
#define _00_INTP0_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP0 pin */
#define _02_INTP1_EDGE_RISING_SEL		0x02U	/* rising edge selected for INTP1 pin */
#define _00_INTP1_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP1 pin*/
#define _04_INTP2_EDGE_RISING_SEL		0x04U	/* rising edge selected for INTP2 pin */
#define _00_INTP2_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP2 pin */
#define _08_INTP3_EDGE_RISING_SEL		0x08U	/* rising edge selected for INTP3 pin */
#define _00_INTP3_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP3 pin */
#define _10_INTP4_EDGE_RISING_SEL		0x10U	/* rising edge selected for INTP4 pin */
#define _00_INTP4_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP4 pin */
#define _20_INTP5_EDGE_RISING_SEL		0x20U	/* rising edge selected for INTP5 pin */
#define _00_INTP5_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP5 pin */
#define _40_INTP6_EDGE_RISING_SEL		0x40U	/* rising edge selected for INTP6 pin */
#define _00_INTP6_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP6 pin */
#define _80_INTP7_EDGE_RISING_SEL		0x80U	/* rising edge selected for INTP7 pin */
#define _00_INTP7_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP7 pin */

/*
	External Interrupt Falling Edge Enable Register (EGN)
*/
/* INTPn pin valid edge selection(EGNn) */
#define _00_INTP_EGN_RESET_VALUE		0x00U	/* external interrupt falling edge enable register value after reset */
#define _01_INTP0_EDGE_FALLING_SEL		0x01U	/* falling edge selected for INTP0 pin */
#define _00_INTP0_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP0 pin */
#define _02_INTP1_EDGE_FALLING_SEL		0x02U	/* falling edge selected for INTP1 pin */
#define _00_INTP1_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP1 pin */
#define _04_INTP2_EDGE_FALLING_SEL		0x04U	/* falling edge selected for INTP2 pin */
#define _00_INTP2_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP2 pin */
#define _08_INTP3_EDGE_FALLING_SEL		0x08U	/* falling edge selected for INTP3 pin */
#define _00_INTP3_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP3 pin */
#define _10_INTP4_EDGE_FALLING_SEL		0x10U	/* falling edge selected for INTP4 pin */
#define _00_INTP4_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP4 pin */
#define _20_INTP5_EDGE_FALLING_SEL		0x20U	/* falling edge selected for INTP5 pin */
#define _00_INTP5_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP5 pin */
#define _40_INTP6_EDGE_FALLING_SEL		0x40U	/* falling edge selected for INTP6 pin */
#define _00_INTP6_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP6 pin */
#define _80_INTP7_EDGE_FALLING_SEL		0x80U	/* falling edge selected for INTP7 pin */
#define _00_INTP7_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP7 pin */

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


#endif   /* ifndef IRQ_CFG_H */

/* END OF FILE -------------------------------------------------------------- */


