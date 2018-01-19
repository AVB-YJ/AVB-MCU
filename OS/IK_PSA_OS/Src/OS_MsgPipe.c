/******************************************************************************
 *  Project       : IK 010246
 *  Module        : OS msg pipe
 *  File          : OS_MsgPipe.c
 *  Creation date : jj/mm/2002
 *-----------------------------------------------------------------------------
 *  Description   : OS msg pipe
 *
 *            
 *-----------------------------------------------------------------------------
 *  History       : 25/06/2002  0.01 Gentner Creation
 *
 *-----------------------------------------------------------------------------
 ******************************************************************************/

/*----------------------------------------------------------------------------*
 *              --- Included files and compilation variables ---              *
 *----------------------------------------------------------------------------*/
#ifdef OS_MSGPIPE_USED

#include "Systype.h"
#include "OS_MsgPipe.h"

extern OS_MsgPipeCtrl OS_MsgPipeControl[OS_MsgPipeMax];

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*
 *                             --- Variables ---                              *
 *----------------------------------------------------------------------------*/


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
 * Function  : OS_WriteMsgToPipe
 *
 * Role      : Write msg to the pipe
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

OS_Error OS_WriteMsgToPipe(OS_MsgPipeID PipeID, const void* data, OS_IndexType length)
{
    register OS_MsgPipeCtrl* pCtrl = &OS_MsgPipeControl[PipeID];
#ifdef OS_DEBUG
    if ( PipeID>=OS_MsgPipeMax )
    {
        return OS_IdOutOfRange;
    }
#endif
    /* Check space availability */
    if ( (pCtrl->PendingMsg<PIPE_MAX_MSG) && (pCtrl->RemainingSpace>=length) )
    {   /* Ok, copy data to pipe */

        /* Decrease remaining space in pipe */
        pCtrl->RemainingSpace -= length;
        /* Store message length */       
        pCtrl->MsgSize[pCtrl->LastMsg] = length;
        
        while ( length-- )
        {
            /* Copy data */
            *(pCtrl->WriteIndex) = *((uint8_t*)data)++;
            /* Warp aroud if necessary */
            if ( pCtrl->WriteIndex<pCtrl->BufferEnd )
            {
                pCtrl->WriteIndex++;
            }
            else
            {
                pCtrl->WriteIndex=pCtrl->Buffer;
            }
        }
        /* Increase LastMsg index */
        pCtrl->LastMsg = (pCtrl->LastMsg+1)%PIPE_MAX_MSG;
        /* Add one pending message */
        pCtrl->PendingMsg++;
        return OS_NoError;
    }
    else
    {
        return OS_PipeFull;
    }
}

/******************************************************************************
 * Function  : OS_ReadMsgFromPipe
 *
 * Role      : Read one msg from pipe
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

OS_Error OS_ReadMsgFromPipe(OS_MsgPipeID PipeID, void* data, OS_IndexType* length)
{
    register OS_MsgPipeCtrl* pCtrl = &OS_MsgPipeControl[PipeID];
#ifdef OS_DEBUG
    if ( PipeID>=OS_MsgPipeMax )
    {
        return OS_IdOutOfRange;
    }
#endif
    /* Check msg availability */
    if ( pCtrl->PendingMsg!=0 )
    {
        /* Check if provided buffer is big enough */
        OS_IndexType MsgLength = pCtrl->MsgSize[pCtrl->FirstMsg];
        if ( MsgLength <= *length )
        {
            /* Ok, copy data from pipe */

            /* Give this space back to pipe */
            pCtrl->RemainingSpace += MsgLength;
            /* Return message length */
            *length = MsgLength;

            while ( MsgLength-- )
            {
                /* Copy data */
                *((uint8_t*)data)++ = *(pCtrl->ReadIndex);
                /* Warp around if necessary */
                if ( pCtrl->ReadIndex<pCtrl->BufferEnd )
                {
                    pCtrl->ReadIndex++;
                }
                else
                {
                    pCtrl->ReadIndex=pCtrl->Buffer;
                }
            }
            /* Incease FirstMsg index */
            pCtrl->FirstMsg = (pCtrl->FirstMsg+1)%PIPE_MAX_MSG;
            /* Substract one pending message */
            pCtrl->PendingMsg--;
        }
        else
        {
            return OS_BufferTooSmall;
        }
        return OS_NoError;
    }
    else
    {
        *length = 0;
        return OS_PipeEmpty;
    }
}

/******************************************************************************
 * Function  : OS_PipeMsgPending
 *
 * Role      : Pipe msg pending
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

OS_IndexType OS_PipeMsgPending(OS_MsgPipeID PipeID)
{
#ifdef OS_DEBUG
    if ( PipeID >= OS_MsgPipeMax )
    {
        return 0;
    }
#endif
    return OS_MsgPipeControl[PipeID].PendingMsg;
}

/******************************************************************************
 * Function  : OS_ClearMsgPipe
 *
 * Role      : Clear one msg pipe
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

OS_Error OS_ClearMsgPipe(OS_MsgPipeID PipeID)
{
    OS_MsgPipeCtrl* pCtrl = &OS_MsgPipeControl[PipeID];
#ifdef OS_DEBUG
    if ( PipeID>=OS_MsgPipeMax )
    {
        return OS_IdOutOfRange;
    }
#endif

    pCtrl->FirstMsg =
    pCtrl->LastMsg =
    pCtrl->PendingMsg = 0;

    pCtrl->ReadIndex =
    pCtrl->WriteIndex = 0;

    pCtrl->RemainingSpace = pCtrl->BufferSize;

    return OS_NoError;
}

/******************************************************************************
 * Function  : OS_ClearAllMsgPipes
 *
 * Role      : Clear all msg pipes
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

void OS_ClearAllMsgPipes(void)
{
    OS_IndexType index;

    for ( index=0; index<OS_MsgPipeMax; index++ )
    {
        (void)OS_ClearMsgPipe(index);
    }
}

#endif

/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/
