/******************************************************************************
 * Copyright 2008  Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS: Prakash, Sandeep                                                  *
 * Project: CCA - DATA TYPES                                                  *
 * File Name:  can_handler_datatypes.h                                        *
 * Description: This file contans the data types those are commonly used in   *
 *               CAN Handler (DCH)                                      *
 *****************************************************************************/

#ifndef CAN_HANDLER_DATATYPES_H
#define CAN_HANDLER_DATATYPES_H

//#include "Compiler.h"
#include "Systype.h"

#ifndef NULL
#define NULL  (( void * ) 0 )
#endif

#ifndef NULL_NOTIFIER_FUNCTION_POINTER
#define NULL_NOTIFIER_FUNCTION_POINTER ((void *)0)
#endif

#ifndef NOP
#define NOP   __asm( "nop" )
#endif

#ifndef b_cbFALSE
#define b_cbFALSE ( 0 )
#define b_cbTRUE  ( !b_cbFALSE )
#endif

/*RC stands For Response Code*/

#define RC_OK            0x00  /* Positive Response                            */
#define RC_GR            0x10  /* General Reject                               */
#define RC_SNS           0x11  /* ServiceNotSupported                          */
#define RC_SFNS          0x12  /* SubfunctionNotSupported                      */
#define RC_CNC           0x22  /* ConditionsNotCorrect                         */
#define RC_ROOR          0x31  /* RequestOutOfRange                            */
#define RC_SAD           0x33  /* Security Aceess Denied                       */
#define RC_IK            0x35  /* Invalid Key                                  */
#define RC_ENOA          0x36  /*  Exceeded Number of Attempts                 */
#define RC_RTDNE         0x37  /* Required Time Delay Not Expired              */
#define RC_RCRRP         0x78  /* RequestCorrectlyReceivedResponsePending      */
#define RC_SNSIAS        0x80  /* serviceNotSupportedInActiveSession           */

/*=======================           INCLUDES           =======================*/
/*=======================        TYPE DEFINITIONS      =======================*/

/*
 *   Standard Types:
 *   ===============
*/
typedef unsigned char       canuint8_t;
//typedef canuint8_t          uint8_t;

typedef unsigned short      canuint16_t;
//typedef canuint16_t         uint16_t;
typedef unsigned long       canuint32_t;
//typedef canuint32_t         uint32_t;

typedef unsigned char       canbool8_t;
typedef canbool8_t          bool8_t;
typedef unsigned int        canbool16_t;
typedef canbool16_t         bool16_t;

typedef signed char         cansint8_t;
typedef signed short        cansint16_t;

typedef void ( * function_pointer_T)(void);

/*=======================             ENUMS            =======================*/
 typedef enum
{
   STANDARD_ID,
   EXTENDED_ID,
   ID_TYPE_NOT_FOUND
} Msg_ID_Type_T;

typedef enum
{
   SLEEP_NOT_OK,
   SLEEP_OK,
   SLEEP_INVALID_REQUEST
}Sleep_Result_T;


#undef EXTENDED_ID_MODE
#define STANDARD_ID_MODE

#ifdef STANDARD_ID_MODE
typedef canuint16_t Msg_ID_T;
#else //if EXTENDED_ID_MODE or MIXED_ID_MODE
typedef canuint32_t Msg_ID_T;
#endif

typedef enum
{
   CAN_ZERO,
   CAN_ONE,
   CAN_TWO,
   CAN_THREE
}CHANNEL_NUM;

typedef enum Interrupt_Type_Tag
{
 HWCAN_TRANSMIT=0,
 HWCAN_RECEIVE,
 HWCAN_ERROR,
 HWCAN_WAKEUP,
 NUMBER_OF_INTERRUPTS_SUPPORTED
} Interrupt_Type_T;

/*  Common Enumerated data types for HWCAN Layer */

typedef enum Boolean_Returnvalue_Tag
{
  cbFALSE,
  cbTRUE,
  cbINVALIDREQUEST
} Boolean_Returnvalue_T;

 typedef enum
{
   CAN_cbFALSE,
   CAN_cbTRUE
} can_boolean_t;    //  boolean_t

typedef enum
{
   CAN_DISABLE,
   CAN_ENABLE
} can_control_t;

typedef enum
{
   CAN_RECEIVE,
   CAN_TRANSMIT
} can_direction_t;

typedef enum
{
  NOT_INITIALIZED =0,
  INITIALIZED
}CHANNEL_INITIALIZATION_STATUS_T;

typedef enum
{
  ID_NOT_FOUND = 0xFF,
  ID_TYPE_MISMATCH = 0xFF,
  DLC_MISMATCH = 0xFF
}MISMATCHES_IN_SEARCH; //debug

typedef enum
{
  MESSAGE_INVALID =0,
  MESSAGE_VALID
}MESSAGE_VALIDITY;

#endif
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08   Prakash,      Created initial version of this file          *
 *                 Sandeep                                                     *
 ******************************************************************************/
