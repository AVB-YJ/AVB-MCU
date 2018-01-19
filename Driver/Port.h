#ifndef PORT_H
#define PORT_H

/**\file
 *
 * \brief Header File for SSA PORT module.
 * \details This file describes the public interface of the PORT module for
 *          Small System Architecture.
 *
 * \Requirements
 * \reqtrace{SSA-SDD-PORT-2-1}{SSA-REQ-PORT-96-2, SSA-REQ-PORT-92-1, SSA-REQ-PORT-93-1,
 *                             SSA-REQ-PORT-94-1, SSA-REQ-PORT-175-1}
 */

/*============================================================================*\
 * PREPROCESSOR DIRECTIVES
\*============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/

/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/

#include "uc_registers.h"
#include "Port_Cfg.h"

/** 
 * Enum with possible directions and values of this enumeration are adapted
 * for PMx register in 78K0R uC.\n
 * \n
 * \Requirements
 * \reqtrace{SSA-SDD-PORT-6-1}{SSA-REQ-PORT-132-1, SSA-REQ-PORT-133-1, SSA-REQ-PORT-134-1}
 */
typedef enum Port_PinDirection_Tag
{
   PORT_PIN_OUT = 0,     /**< Direction set to output (output buffer on) */
   PORT_PIN_IN  = 1      /**< Direction set to input (output buffer off) */
}
Port_PinDirectionType;


/**
 * Enum with possible Pin input modes and values of this enumeration are adapted
 * for PIMx register in 78K0R uC.\n
 */
typedef enum Port_PinPIM_Tag
{
   PORT_PIN_PIM_NORMAL = 0,     /**< Normal input buffer */
   PORT_PIN_PIM_TTL  = 1        /**< TTL input buffer */
}
Port_PinPIMType;


/**
 * Enum with possible Pin output modes and values of this enumeration are adapted
 * for POMx register in 78K0R uC.
 */
typedef enum Port_PinPOM_Tag
{
   PORT_PIN_POM_NORMAL = 0,     /**< Normal output buffer */
   PORT_PIN_POM_NCH  = 1        /**< N-ch open-drain output (VDD tolerance) mode */
}
Port_PinPOMType;


/**
 * Enum with possible Pin slew rates and values of this enumeration are adapted
 * for PSRSEL register in 78K0R uC.\n
 */
typedef enum Port_PinPSR_Tag
{
   PORT_PIN_PSR_NORMAL = 0,     /**< Normal mode (5 V/5 ns) */
   PORT_PIN_PSR_SLOW   = 1      /**< Slow mode (25 V/5 ns (target) (TYP.)) */
}
Port_PinPSRType;

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/**
 * Type defined for pins.
 * \n
 * \Requirements
 * \reqtrace{SSA-SDD-PORT-7-1}{SSA-REQ-PORT-128-1, SSA-REQ-PORT-129-1}
 */
typedef uint8 Port_PinType;


/**
 * Type defined for modes of pin.
 * \n
 * \Requirements
 * \reqtrace{SSA-SDD-PORT-8-1}{SSA-REQ-PORT-135-1, SSA-REQ-PORT-137-1}
 */
typedef uint8 Port_PinModeType;


/** 
 * Unused type since Post-Build variant is not supported in PORT Driver and
 * all initialization data comes from statically configured defines from Port_Cfg.h
 * (Defined only for Port_Init(Port_ConfigType*) prototype consistence).\n
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-PORT-9-1}{SSA-REQ-PORT-124-1, SSA-REQ-PORT-125-1, SSA-REQ-PORT-126-1,
 *                             SSA-REQ-PORT-127-1}
 */
typedef void Port_ConfigType;


/*============================================================================*\
 * EXPORTED OBJECT DECLARATIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS PROTOTYPES
\*============================================================================*/

 /**
 * \details Service for initializing the Port module.\n
 *          All initialization is being made with statically configured macros.\n
 *
 * \n
 * \ServID      0x00
 * \Synchronism Synchronous
 * \Reentrancy  Non-reentrant
 *
 * \param[in]   ConfigPtr - pointer to configuration data.
 *
 * \return      None
 * \Caveats     None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-PORT-10-1}{SSA-REQ-PORT-118-1, SSA-REQ-PORT-199-1, SSA-REQ-PORT-200-1,
 *                              SSA-REQ-PORT-201-1, SSA-REQ-PORT-202-1, SSA-REQ-PORT-203-1,
 *                              SSA-REQ-PORT-204-1, SSA-REQ-PORT-205-1, SSA-REQ-PORT-206-1,
 *                              SSA-REQ-PORT-208-1, SSA-REQ-PORT-209-1, SSA-REQ-PORT-210-1,
 *                              SSA-REQ-PORT-211-1, SSA-REQ-PORT-212-1, SSA-REQ-PORT-213-1,
 *                              SSA-REQ-PORT-179-1, SSA-REQ-PORT-176-1, SSA-REQ-PORT-178-1,
 *                              SSA-REQ-PORT-98-1,  SSA-REQ-PORT-99-1, SSA-REQ-PORT-100-1,
 *                              SSA-REQ-PORT-101-1, SSA-REQ-PORT-102-1, SSA-REQ-PORT-108-1}
 * \latexonly
 * \DSARfigure{Port_Init.png}{0.7\textwidth}{fig:Fig1}{Port\_Init function diagram}
 * \endlatexonly
 */
extern FUNC(void, PORT_CODE) Port_Init
(
   P2CONST(Port_ConfigType, PORT_CONST, PORT_APPL_CONST) ConfigPtr
);

/**
 * \details This routine sets the port pin direction during runtime.\n
 *
 * \n
 * \ServID      0x01
 * \Synchronism Synchronous
 * \Reentrancy  Re-entrant (limited)
 *
 * \param[in]   Pin - Port Pin ID Number.
 * \param[in]   Direction - Port Pin Direction
 *
 * \return      None
 * \Caveats     None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-PORT-11-1}{SSA-REQ-PORT-216-1, SSA-REQ-PORT-217-1, SSA-REQ-PORT-218-1,
 *                              SSA-REQ-PORT-219-1, SSA-REQ-PORT-220-1, SSA-REQ-PORT-221-1,
 *                              SSA-REQ-PORT-222-1, SSA-REQ-PORT-224-1, SSA-REQ-PORT-225-1,
 *                              SSA-REQ-PORT-227-1, SSA-REQ-PORT-228-1, SSA-REQ-PORT-177-1,
 *                              SSA-REQ-PORT-178-1, SSA-REQ-PORT-176-1, SSA-REQ-PORT-106-1}
 * \latexonly
 * \DSARfigure{Port_SetPinDirection.png}{0.7\textwidth}{fig:Fig1}{Port\_SetPinDirection() function diagram}
 * \endlatexonly
 */
extern FUNC(void, PORT_CODE) Port_SetPinDirection
(
   Port_PinType Pin,
   Port_PinDirectionType Direction
);

/**
 * \details This routine sets the port pin mode during runtime.\n
 *
 * \n
 * \ServID      0x04
 * \Synchronism Synchronous
 * \Reentrancy  Re-entrant
 *
 * \param[in]   Pin - Port Pin ID Number.
 * \param[in]   Mode - Port Pin Mode
 *
 * \return      None
 * \Caveats     None
 * \n
 * \Requirements \n
 * \reqtrace{SSA-SDD-PORT-13-1}{SSA-REQ-PORT-167-1, SSA-REQ-PORT-168-1, SSA-REQ-PORT-169-1,
 *                              SSA-REQ-PORT-170-1, SSA-REQ-PORT-171-1, SSA-REQ-PORT-172-1,
 *                              SSA-REQ-PORT-173-1, SSA-REQ-PORT-174-1, SSA-REQ-PORT-252-1,
 *                              SSA-REQ-PORT-176-1, SSA-REQ-PORT-178-1}
 * \latexonly
 * \DSARfigure{Port_SetPinMode.png}{0.7\textwidth}{fig:Fig1}{Port\_SetPinMode() function diagram}
 * \endlatexonly
 */
extern FUNC(void,PORT_CODE) Port_SetPinMode
(
   Port_PinType Pin,
   Port_PinModeType Mode
);

#endif   /* PORT_H */
