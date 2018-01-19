/******************************************************************************
 *  Project       : IK OS
 *  SW component  : OS FyfoSys ( OS fifo management )
 *  File          : OS_FyfoSys.h
 *-----------------------------------------------------------------------------
 *  Description   : OS fifo management
 *
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*----------------------------------------------------------------------------*
 *              --- Included files and compilation variables ---              *
 *----------------------------------------------------------------------------*/
#include "Systype.h"

#include "OS_FifoSys.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*
 *                             --- Variables ---                              *
 *----------------------------------------------------------------------------*/

#ifdef OS_DEBUG
static FIFO_STRUCT_NAME FIFO_STRUCT_QUEUE = { {0,0,0,0} };
#else
static FIFO_STRUCT_NAME FIFO_STRUCT_QUEUE;
#endif


/*----------------------------------------------------------------------------*
 *                    --- Local functions declaration ---                     *
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*
 *                          --- Local functions ---                           *
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

/******************************************************************************
 * Function  : FIFO_PUSH_BACK
 *
 * Role      : Push in fifo
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_PUSH_BACK
void FIFO_PUSH_BACK ( const OS_Msg * elt )
{
   /* Set message pointer to current indexed one. */
   FIFO_ELEMENT * const pCurrentMsg = &FIFO_STRUCT_QUEUE.MsgQueue[FIFO_STRUCT_QUEUE.Ctrl.LastMsg];

#ifdef OS_DEBUG
    if ( elt==0 ) return;
#endif
    OS_DisableAllInterrupts();

    if (MSG_QUEUE_SIZE > FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
    {
        /* Copy message content */
        OS_MsgCopy(pCurrentMsg, elt);

        /* Increment and warp around last message index */
        FIFO_STRUCT_QUEUE.Ctrl.LastMsg = (FIFO_STRUCT_QUEUE.Ctrl.LastMsg + 0x01U) % MSG_QUEUE_SIZE;

        /* Add a pending message */
        ++FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;

#ifdef OS_DEBUG
        if (FIFO_STRUCT_QUEUE.Ctrl.PendingMsg>FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg)
        {
            FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg = FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;
        }
#endif
        OS_EnableAllInterrupts();
    }
    else
    {
        OS_SelfCheckErrEvent(); /* call error handler */
        OS_SoftwareReset();
    }
}
#endif

/******************************************************************************
 * Function  : FIFO_PUSH_BACK0
 *
 * Role      : Push in fifo with 0 parameters
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_PUSH_BACK0
void FIFO_PUSH_BACK0 ( OS_MsgIdType MsgId )
{
   /* Set message pointer to current indexed one. */
   FIFO_ELEMENT * const pCurrentMsg = &FIFO_STRUCT_QUEUE.MsgQueue[FIFO_STRUCT_QUEUE.Ctrl.LastMsg];
   
#ifdef OS_DEBUG
    if ( elt==0 ) return;
#endif
    OS_DisableAllInterrupts();

    if (MSG_QUEUE_SIZE > FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
    {
        /* save msg Id */
        pCurrentMsg->MsgId = MsgId;

        /* Increment and warp around last message index */
        FIFO_STRUCT_QUEUE.Ctrl.LastMsg = (FIFO_STRUCT_QUEUE.Ctrl.LastMsg + 0x01U) % MSG_QUEUE_SIZE;

        /* Add a pending message */
        ++FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;

#ifdef OS_DEBUG
        if (FIFO_STRUCT_QUEUE.Ctrl.PendingMsg>FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg)
        {
            FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg = FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;
        }
#endif

        OS_EnableAllInterrupts();
    }
    else
    {
        OS_SelfCheckErrEvent(); /* call error handler */
        OS_SoftwareReset();
    }
}
#endif

/******************************************************************************
 * Function  : FIFO_PUSH_BACK1
 *
 * Role      : Push in fifo with 1 parameter
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_PUSH_BACK1
void FIFO_PUSH_BACK1 ( const OS_Msg * elt )
{
   /* Set message pointer to current indexed one. */
   FIFO_ELEMENT * const pCurrentMsg = &FIFO_STRUCT_QUEUE.MsgQueue[FIFO_STRUCT_QUEUE.Ctrl.LastMsg];
   
#ifdef OS_DEBUG
    if ( elt==0 ) return;
#endif
    OS_DisableAllInterrupts();

    if (MSG_QUEUE_SIZE > FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
    {
        /* Copy message content */
        OS_MsgCopy(pCurrentMsg, elt);

        /* Increment and warp around last message index */
        FIFO_STRUCT_QUEUE.Ctrl.LastMsg = (FIFO_STRUCT_QUEUE.Ctrl.LastMsg + 0x01U) % MSG_QUEUE_SIZE;

        /* Add a pending message */
        ++FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;

#ifdef OS_DEBUG
        if (FIFO_STRUCT_QUEUE.Ctrl.PendingMsg>FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg)
        {
            FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg = FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;
        }
#endif
        OS_EnableAllInterrupts();
    }
    else
    {
        OS_SelfCheckErrEvent(); /* call error handler */
        OS_SoftwareReset();
    }
}
#endif

/******************************************************************************
 * Function  : FIFO_PUSH_FRONT
 *
 * Role      : Push in fifo
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_PUSH_FRONT
void FIFO_PUSH_FRONT ( const FIFO_ELEMENT * elt )
{
   /* Set index to previous message */
   const FIFO_INDEX_TYPE index = (FIFO_STRUCT_QUEUE.Ctrl.FirstMsg - 0x01U) % MSG_QUEUE_SIZE;
   FIFO_ELEMENT * const pCurrentMsg = &FIFO_STRUCT_QUEUE.MsgQueue[index];
   
#ifdef OS_DEBUG
    if ( elt==0 ) return;
#endif
    OS_DisableAllInterrupts();

    if (MSG_QUEUE_SIZE > FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
    {
        /* Copy message content */
        OS_MsgCopy(pCurrentMsg, elt);

        /* Set first message index to this one */
        FIFO_STRUCT_QUEUE.Ctrl.FirstMsg = index;
        
        /* Add a pending message */
        ++FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;

#ifdef OS_DEBUG
        if (FIFO_STRUCT_QUEUE.Ctrl.PendingMsg > FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg)
        {
            FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg = FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;
        }
#endif
        OS_EnableAllInterrupts();
    }
    else
    {
        OS_SelfCheckErrEvent(); /* call error handler */
        OS_SoftwareReset();
    }
}
#endif

/******************************************************************************
 * Function  : FIFO_FRONT
 *
 * Role      : Fifo front
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_FRONT
FIFO_RETURN_TYPE FIFO_FRONT ( FIFO_ELEMENT * elt )
{
   FIFO_RETURN_TYPE Result = 0;
   
   /* Set message pointer to current indexed one. */
   const FIFO_ELEMENT * const pCurrentMsg = &FIFO_STRUCT_QUEUE.MsgQueue[FIFO_STRUCT_QUEUE.Ctrl.FirstMsg];
   
    if (0U < FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
    {
        /* Copy message content */
        OS_MsgCopy(elt, pCurrentMsg);
    }
    else
    {
      Result = 1;
    }
    return (Result);
}
#endif

/******************************************************************************
 * Function  : FIFO_POP
 *
 * Role      : Fifo pop
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_POP
FIFO_RETURN_TYPE FIFO_POP ( void )
{
   FIFO_RETURN_TYPE Result = 0;
   
   OS_DisableAllInterrupts();

   if (0U <  FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
   {
     /* Increment and warp aroud first message index */       
     FIFO_STRUCT_QUEUE.Ctrl.FirstMsg = (FIFO_STRUCT_QUEUE.Ctrl.FirstMsg + 0x01U) % MSG_QUEUE_SIZE;

     /* Remove a pending message */
     --FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;

     OS_EnableAllInterrupts();
   }
   else
   {
     OS_EnableAllInterrupts();
     Result = 1;
   }
   return (Result);
}
#endif

/******************************************************************************
 * Function  : FIFO_POP
 *
 * Role      : Fifo pop
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_POP_FRONT
FIFO_RETURN_TYPE FIFO_POP_FRONT ( FIFO_ELEMENT * elt )
{
   FIFO_RETURN_TYPE Result = 0;
   
   /* Set message pointer to current indexed one. */
   const FIFO_ELEMENT * const pCurrentMsg = &FIFO_STRUCT_QUEUE.MsgQueue[FIFO_STRUCT_QUEUE.Ctrl.FirstMsg];
   
#ifdef OS_DEBUG
    if ( elt==0 ) return;
#endif
    OS_DisableAllInterrupts();

    if (0U < FIFO_STRUCT_QUEUE.Ctrl.PendingMsg)
    {
        /* Copy message content */
        OS_MsgCopy(elt, pCurrentMsg);

        /* Increment and warp aroud first message index */       
        FIFO_STRUCT_QUEUE.Ctrl.FirstMsg = (FIFO_STRUCT_QUEUE.Ctrl.FirstMsg + 0x01U) % MSG_QUEUE_SIZE;

        /* Remove a pending message */
        --FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;

        OS_EnableAllInterrupts();
    }
    else
    {
        /* Fifo was empty */
        OS_EnableAllInterrupts();
        Result = 1;

    }
    return (Result);
}
#endif

/******************************************************************************
 * Function  : OS_FifoSys_Reset
 *
 * Role      : Fifo reset
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_RESET
void OS_FifoSys_Reset ( void )
{
    FIFO_STRUCT_QUEUE.Ctrl.PendingMsg = 0;
    FIFO_STRUCT_QUEUE.Ctrl.FirstMsg = 0;
    FIFO_STRUCT_QUEUE.Ctrl.LastMsg = 0;
#ifdef OS_DEBUG
    FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg = 0;
#endif
}
#endif

/******************************************************************************
 * Function  : OS_FifoSys_Pending
 *
 * Role      : Fifo pending
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_PENDING
FIFO_INDEX_TYPE OS_FifoSys_Pending ( void )
{
    return FIFO_STRUCT_QUEUE.Ctrl.PendingMsg;
}
#endif

/******************************************************************************
 * Function  : FIFO_MAX_PENDING
 *
 * Role      : Fifo pending
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#if defined FIFO_MAX_PENDING && defined OS_DEBUG
FIFO_INDEX_TYPE FIFO_MAX_PENDING(void)
{
    const OS_IndexType mpm = FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg;
    
    FIFO_STRUCT_QUEUE.Ctrl.MaxPendingMsg = 0;
    
    return mpm;
}
#endif

/******************************************************************************
 * Function  : OS_FifoSys_Check
 *
 * Role      : Fifo coherency check
 *
 *-----------------------------------------------------------------------------
 * Entry     : <<entry parameters>>
 *
 * Exit      : <<exit parameters>>
 *
 *-----------------------------------------------------------------------------
 * globals   : r/w Name Of Variable    Range       Description
 *             --- ------------------  ---------   ----------------------------
 *
 *
 ******************************************************************************/
#ifdef FIFO_CHECK
void OS_FifoSys_Check(void)
{
  OS_DisableAllInterrupts();
  if (((FIFO_STRUCT_QUEUE.Ctrl.FirstMsg + FIFO_STRUCT_QUEUE.Ctrl.PendingMsg) % MSG_QUEUE_SIZE) != FIFO_STRUCT_QUEUE.Ctrl.LastMsg)
  {
     OS_SelfCheckErrEvent(); /* call error handler */
     OS_SoftwareReset();
  }
  OS_EnableAllInterrupts();
}
#endif

/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/
