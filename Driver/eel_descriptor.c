/*==============================================================================================*/
/* Project      = 78K0R EEPROM Emulation Library, MF2 single voltage flash                      */
/* Module       = eel_descriptor.c                                                              */
/* Device:      = 78K0R/Fx3                                                                     */
/* Version      = V1.0.3                                                                        */
/* Date         = 19.02.2010 15:12:58                                                           */
/*==============================================================================================*/
/*                                  COPYRIGHT                                                   */
/*==============================================================================================*/
/* Copyright (c) 2008, 2009, 2010  by NEC Electronics (Europe) GmbH,                            */
/*               a company of the NEC Electronics Corporation                                   */
/*==============================================================================================*/
/*                                                                                              */
/* Purpose:     contains the user defined EEL-variable descriptor                               */
/*                                                                                              */
/*==============================================================================================*/
/*                                                                                              */
/* Warranty Disclaimer                                                                          */
/*                                                                                              */
/* Because the Product(s) is licensed free of charge, there is no warranty of any kind          */
/* whatsoever and expressly disclaimed and excluded by NEC, either expressed or implied,        */
/* including but not limited to those for non-infringement of intellectual property,            */
/* merchantability and/or fitness for the particular purpose. NEC shall not have any obligation */
/* to maintain, service or provide bug fixes for the supplied Product(s) and/or the Application.*/
/*                                                                                              */
/* Each User is solely responsible for determining the appropriateness of using the Product(s)  */
/* and assumes all risks associated with its exercise of rights under this Agreement,           */
/* including, but not limited to the risks and costs of program errors, compliance with         */
/* applicable laws, damage to or loss of data, programs or equipment, and unavailability or     */
/* interruption of operations.                                                                  */
/*                                                                                              */
/* Limitation of Liability                                                                      */
/*                                                                                              */
/* In no event shall NEC be liable to the User for any incidental, consequential, indirect,     */
/* or punitive damage (including but not limited to lost profits) regardless of whether         */
/* such liability is based on breach of contract, tort, strict liability, breach of warranties, */
/* failure of essential purpose or otherwise and even if advised of the possibility of          */
/* such damages. NEC shall not be liable for any services or products provided by third party   */
/* vendors, developers or consultants identified or referred to the User by NEC in connection   */
/* with the Product(s) and/or the Application.                                                  */
/*                                                                                              */
/*==============================================================================================*/
/* Environment: IAR environment for 78K0R (version V4.xx)                                       */
/*==============================================================================================*/

/*--------------------------------------------------------------------
* Module Name:     EEL
* Created By:      wade.li
* Created Date:    04/18/2011
* %version:          %
* %cvtype:         csrc %
* %instance:       ctc_aud_1 %
* %derived_by:      %
* date_created:     %
*--------------------------------------------------------------------*/


/*==============================================================================================*/
/* compiler settings                                                                            */
/*==============================================================================================*/
#pragma language = extended

/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#define  __EEL_DESCRIPTOR_C
  #include "Polyspace.h"
  #include  "eel_types.h"
  #include  "eel_descriptor.h"
#undef   __EEL_DESCRIPTOR_C

#if (EEL_STORAGE_TYPE == 'C')
  #include  "fcl_types.h"
#elif (EEL_STORAGE_TYPE=='D')
  #include  "fdl_types.h"
#else
  #error "EEL: wrong storage type defined !"
#endif


/* definition of variable types registered at EEL */
#include "NVM_Cfg.h"



/*==============================================================================================*/
/* import list                                                                                  */
/*==============================================================================================*/
/* empty */


/* data segment definition */
 #pragma dataseg="EEL_UDAT"

/*==============================================================================================*/
/* data definition                                                                              */
/*==============================================================================================*/
#if (EEL_STORAGE_TYPE=='C')
  __no_init eel_u16   EEL_var_ref[EEL_VAR_NO];
#else
  __no_init eel_u16   EEL_var_ref[1];                          /* dummy address for FDL variant */
#endif

/* constant segment definition */
 #pragma location="EEL_CNST"
 #pragma data_alignment=2

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      B E G I N    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A      *******/
/*******                                                                                           *******/
/*********************************************************************************************************/
 __far const eel_u08 eel_descriptor[(EEL_VAR_NO + 1)][4] =
            {
            /*  identifier        word-size (1...64)                  byte-size (1..255)         RAM-Ref. */
            /*  ----------------------------------------------------------------------------------------- */
                (eel_u08)(NVM_SECTOR_BLK_ID+1),     (eel_u08)((NVM_BLK0_LENGTH+3)/4),              (eel_u08)NVM_BLK0_LENGTH,             0x01,   

     };
            

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      E N D    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A          *******/
/*******                                                                                           *******/
/*********************************************************************************************************/





/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
 #pragma location="EEL_CNST"
__far const eel_u08   eel_refresh_bth_u08     = (eel_u08)EEL_REFRESH_BLOCK_THRESHOLD;

 #pragma location="EEL_CNST"
__far const eel_u08   eel_storage_type_u08    = (eel_u08)EEL_STORAGE_TYPE;

 #pragma location="EEL_CNST"
__far const eel_u08   eel_var_number_u08      = (eel_u08)EEL_VAR_NO;
/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
