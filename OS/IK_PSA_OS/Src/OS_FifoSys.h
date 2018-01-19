/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS FyfoSys ( OS fifo management )
 *  File          : OS_FyfoSys.c
 *-----------------------------------------------------------------------------
 *  Description   : OS fifo management
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*-------------------------------------------------------------------
 * to avoid multiple definition if the file is included several times
 *-------------------------------------------------------------------*/
#ifndef OS_FIFOSYS_H
#define OS_FIFOSYS_H

#include "OS.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/

/*
    Define here the type of the element in Fifo
*/
#define FIFO_ELEMENT        OS_Msg
/*
    Define here the size of the queue (power of 2)
*/
#define MSG_QUEUE_SIZE      0x20U

/*
    Define type used for index
*/
#define FIFO_INDEX_TYPE     OS_IndexType

/*
    Define type used for error return
*/
#define FIFO_RETURN_TYPE    int16_t

/* Only needed operations have to be defined */

/* Push operations */
#define FIFO_PUSH_BACK      OS_FifoSys_PushBack
#define FIFO_PUSH_BACK0     OS_FifoSys_PushBack0
#define FIFO_PUSH_BACK1     OS_FifoSys_PushBack1
#define FIFO_PUSH_FRONT     OS_FifoSys_PushFront

/* Pop operations */
/*#define FIFO_FRONT        OS_FifoSys_Front */
/*#define FIFO_POP          OS_FifoSys_Pop */
#define FIFO_POP_FRONT      OS_FifoSys_PopFront

#define FIFO_PENDING        
#define FIFO_RESET          
#define FIFO_MAX_PENDING    
#define FIFO_CHECK          

#define FIFO_STRUCT_NAME    OS_FifoSys_FifoCtrl
#define FIFO_STRUCT_QUEUE   OS_FifoSys_FifoQueue


/*----------------------------------------------------------------------------*
 *                         --- Global Variables ---                           *
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

/* Do NOT edit code below */

#ifdef FIFO_PUSH_BACK
    void FIFO_PUSH_BACK ( const FIFO_ELEMENT * elt );
#endif
#ifdef FIFO_PUSH_BACK0
    void FIFO_PUSH_BACK0 ( OS_MsgIdType MsgId );
#endif
#ifdef FIFO_PUSH_BACK1
    void FIFO_PUSH_BACK1 ( const FIFO_ELEMENT * elt );
#endif
#ifdef FIFO_PUSH_FRONT
    void FIFO_PUSH_FRONT ( const FIFO_ELEMENT * elt );
#endif
#ifdef FIFO_FRONT
    FIFO_RETURN_TYPE FIFO_FRONT ( FIFO_ELEMENT * elt );
#endif
#ifdef FIFO_POP
    FIFO_RETURN_TYPE FIFO_POP ( void );
#endif
#ifdef FIFO_POP_FRONT
    FIFO_RETURN_TYPE FIFO_POP_FRONT ( FIFO_ELEMENT * elt );
#endif
#ifdef FIFO_PENDING
    FIFO_INDEX_TYPE  OS_FifoSys_Pending( void );
#endif
#ifdef FIFO_RESET
    void              OS_FifoSys_Reset( void );
#endif
#if defined FIFO_MAX_PENDING && defined OS_DEBUG
    FIFO_INDEX_TYPE  OS_FifoSys_MaxPending( void );
#endif
#ifdef FIFO_CHECK
    void              OS_FifoSys_Check( void );
#endif


typedef struct
{
   FIFO_INDEX_TYPE FirstMsg;
   FIFO_INDEX_TYPE LastMsg;
   FIFO_INDEX_TYPE PendingMsg;
#ifdef OS_DEBUG
   FIFO_INDEX_TYPE MaxPendingMsg;
#endif   
} FIFO_Ctrl;

typedef struct
{
    FIFO_Ctrl Ctrl;
    
    FIFO_ELEMENT MsgQueue[MSG_QUEUE_SIZE];
} FIFO_STRUCT_NAME;

#endif /* OS_FifoSys_h*/
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/
