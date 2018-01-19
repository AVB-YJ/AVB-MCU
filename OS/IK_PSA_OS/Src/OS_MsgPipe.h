/******************************************************************************
 *  Project       : IK 010246
 *  Module        : Msg pipe
 *  File          : OS_MsgPipe.h
 *  Creation date : 25/06/2002
 *-----------------------------------------------------------------------------
 *  Description   : Msg pipe
 *
 *            
 *-----------------------------------------------------------------------------
 *  History       : 25/06/2002  0.01 Gentner Creation
 *
 *-----------------------------------------------------------------------------
 * Copyright Delphi Mechatronic Systems, All right reserved
 ******************************************************************************/

/*-------------------------------------------------------------------
 * to avoid multiple definition if the file is included several times
 *-------------------------------------------------------------------*/
#ifndef OS_MSGPIPE_H
#define OS_MSGPIPE_H

#ifdef OS_MSGPIPE_USED

#include "OS.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/

typedef struct
{
    uint8_t* const Buffer;
    uint8_t* const BufferEnd;
    const OS_IndexType   BufferSize;
    OS_IndexType         MsgSize[PIPE_MAX_MSG];
    OS_IndexType         FirstMsg;
    OS_IndexType         LastMsg;
    OS_IndexType         PendingMsg;
    OS_IndexType         RemainingSpace;
    uint8_t*       ReadIndex;
    uint8_t*       WriteIndex;
} OS_MsgPipeCtrl;

/*----------------------------------------------------------------------------*
 *                         --- Global Variables ---                           *
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

OS_Error OS_WriteMsgToPipe(OS_MsgPipeID PipeID, const void* data, OS_IndexType length);
OS_Error OS_ReadMsgFromPipe(OS_MsgPipeID PipeID, void* data, OS_IndexType* length);
OS_IndexType OS_PipeMsgPending(OS_MsgPipeID PipeID);
OS_Error OS_ClearMsgPipe(OS_MsgPipeID PipeID);
void OS_ClearAllMsgPipes(void);

#endif /* OS_MSGPIPE_USED */

#endif /* OS_MsgPipe_h*/
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

 
