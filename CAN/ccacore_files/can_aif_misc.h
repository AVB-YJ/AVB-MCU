/*******************************************************************************
* Copyright 2008  Technologies, Inc., All Rights Reserved                *
* REVISION: 1.0                                                                *
* AUTHORS: Sandeep,Prakash                                                     *
* Project: CCA - AIF                                                           *
* File Name:  can_aif_misc.h                                                   *
* File Description:                                                            *
* This module contains miscellaneous variable definitions                      *
*******************************************************************************/

#ifndef CAN_AIF_MISC_H
#define CAN_AIF_MISC_H

#include "can_handler_datatypes.h"
// Array used to mask the bits in a byte
extern const canuint8_t Mask_Bit_Array[];

/* The signal enum list is used by the AIF for processing signal level 
 indication,confirmation and Timeout flags*/
typedef enum
{
 Signal0=0,Signal1,Signal2,Signal3,Signal4,Signal5,Signal6,Signal7,
 Signal8,Signal9,Signal10,Signal11,Signal12,Signal13,Signal14,Signal15,
 Signal16,Signal17,Signal18,Signal19,Signal20,Signal21,Signal22,Signal23,
 Signal24,Signal25,Signal26,Signal27,Signal28,Signal29,Signal30,Signal31,
 Signal32,Signal33,Signal34,Signal35,Signal36,Signal37,Signal38,Signal39,
 Signal40,Signal41,Signal42,Signal43,Signal44,Signal45,Signal46,Signal47,
 Signal48,Signal49,Signal50,Signal51,Signal52,Signal53,Signal54,Signal55,
 Signal56,Signal57,Signal58,Signal59,Signal60,Signal61,Signal62,Signal63
}Signals_T;

#endif

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
