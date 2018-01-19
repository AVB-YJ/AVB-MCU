/******************************************************************************
 *  Project       : IK 010246
 *  Module        : OS DataPipe
 *  File          : OS_DataPipe.c
 *  Creation date : 25/06/2002
 *-----------------------------------------------------------------------------
 *  Description   : OS Data Pipe
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

#ifdef OS_DATAPIPE_USED
#include "Systype.h"

#include "OS_DataPipe.h"

extern OS_DataPipeCtrl OS_DataPipeControl[OS_DataPipeMax];

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

/******************************************************************************
 * Function  : OS_Min
 *
 * Role      : OS min
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

#pragma _inline
static OS_IndexType OS_Min(OS_IndexType a, OS_IndexType b)
{
    return (a<b) ? a: b;
}

/*----------------------------------------------------------------------------*
 *                          --- Public functions ---                          *
 *----------------------------------------------------------------------------*/

/******************************************************************************
 * Function  : OS_WriteToPipe
 *
 * Role      : Write to pipe
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

OS_Error OS_WriteDataToPipe(OS_DataPipeID PipeID, const void* data, OS_IndexType length)
{
      register OS_DataPipeCtrl* const pCtrl = &OS_DataPipeControl[PipeID];
#ifdef OS_DEBUG
    if ( PipeID>=OS_DataPipeMax )
    {
        return OS_IdOutOfRange;
    }
#endif
    
    /* Check space availability */
    if ( pCtrl->RemainingSpace >= length)
    {   /* Ok, copy data to pipe */
        /* Decrease remaining space in pipe */
        pCtrl->RemainingSpace -= length;
        
        while ( length-- )
        {
            /* Copy data */
            *(pCtrl->WriteIndex) = *((const uint8_t*)data)++;
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
        return OS_NoError;
    }
    else
    {
        return OS_PipeFull;
    }
}

/******************************************************************************
 * Function  : OS_ReadFromPipe
 *
 * Role      : Read from pipe
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

OS_Error OS_ReadDataFromPipe(OS_DataPipeID PipeID, void* data, OS_IndexType* length)
{
    register OS_DataPipeCtrl* const pCtrl = &OS_DataPipeControl[PipeID];
#ifdef OS_DEBUG
    if ( PipeID>=OS_DataPipeMax )
    {
        return OS_IdOutOfRange;
    }
#endif

    /* Check msg availability */
    if ( pCtrl->RemainingSpace != pCtrl->BufferSize )
    {
        /* Check if provided buffer is big enough */
        OS_IndexType DataLength = OS_Min(pCtrl->BufferSize-pCtrl->RemainingSpace, *length);

        /* Give this space back to pipe */
        pCtrl->RemainingSpace += DataLength;
        /* Return message length */
        *length = DataLength;

        while ( DataLength-- )
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

        return (pCtrl->BufferSize==pCtrl->RemainingSpace) ? OS_NoError : OS_PipeNotEmpty;
    }
    else
    {
        *length = 0;
        return OS_PipeEmpty;
    }
}

/******************************************************************************
 * Function  : OS_PipePending
 *
 * Role      : Pipe pending
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

OS_IndexType OS_PipeDataPending(OS_DataPipeID PipeID)
{
    register const OS_DataPipeCtrl* pCtrl = &OS_DataPipeControl[PipeID];

#ifdef OS_DEBUG
    if ( PipeID>=OS_DataPipeMax )
    {
        return 0;
    }
#endif

    return pCtrl->BufferSize-pCtrl->RemainingSpace;
}

/******************************************************************************
 * Function  : OS_ClearPipe
 *
 * Role      : Clear pipe
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

OS_Error OS_ClearDataPipe(OS_DataPipeID PipeID)
{
    OS_DataPipeCtrl* pCtrl = &OS_DataPipeControl[PipeID];
#ifdef OS_DEBUG
    if ( PipeID>=OS_DataPipeMax )
    {
        return OS_IdOutOfRange;
    }
#endif

    pCtrl->ReadIndex =
    pCtrl->WriteIndex =  pCtrl->Buffer;

    pCtrl->RemainingSpace = pCtrl->BufferSize;

    return OS_NoError;
}

/******************************************************************************
 * Function  : OS_ClearAllPipes
 *
 * Role      : Clear all pipes
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

void OS_ClearAllDataPipes(void)
{
    OS_IndexType index;

    for ( index=0; index<OS_DataPipeMax; index++ )
    {
        (void)OS_ClearDataPipe(index);
    }
}
#endif
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/
