/******************************************************************************
 *  Project       : IK 010246
 *  Module        : OS data pipe
 *  File          : OS_DataPipe.h
 *  Creation date : 25/06/2002
 *-----------------------------------------------------------------------------
 *  Description   : OS data pipe
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
#ifndef OS_DATAPIPE_H
#define OS_DATAPIPE_H

#ifdef OS_DATAPIPE_USED

#include "OS.h"

/*----------------------------------------------------------------------------*
 *                     --- Local constants & typedefs ---                     *
 *----------------------------------------------------------------------------*/

typedef struct
{
    uint8_t* const Buffer;
    uint8_t* const BufferEnd;
    const OS_IndexType   BufferSize;
    OS_IndexType         RemainingSpace;
    uint8_t*       ReadIndex;
    uint8_t*       WriteIndex;
    uint8_t        Padding[4];    /* Optimise struct to have a size of 16 bytes */
} OS_DataPipeCtrl;


/*----------------------------------------------------------------------------*
 *                         --- Global Variables ---                           *
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

OS_Error OS_WriteDataToPipe(OS_DataPipeID PipeID, const void* data, OS_IndexType length);
OS_Error OS_ReadDataFromPipe(OS_DataPipeID PipeID, void* data, OS_IndexType* length);
OS_IndexType OS_PipeDataPending(OS_DataPipeID PipeID);
OS_Error OS_ClearDataPipe(OS_DataPipeID PipeID);
void OS_ClearAllDataPipes(void);

#endif /* OS_DATAPIPE_USED */

#endif /* OS_DataPipe_h*/
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

 
