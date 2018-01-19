#ifndef _NVM_TYPES_H
#define _NVM_TYPES_H
/*============================================================================*\
*------------------------------------------------------------------------------
* Module Name:     NVM_Types.h
* Created By:      KS
* Created Date:    19-Apr-2010
* %version:        1 %
* %cvtype:         incl %
* %instance:       ctc_aud_4 %
* %derived_by:     lzs7ws %
* %date_modified:   %
*------------------------------------------------------------------------------
*
* Description: This file contains the functions for DIO Driver
*
* Traces to: 10024438_SW_SDD_00001366
*
* Applicable Standards (in order of precedence: highest first):
*     SW REF 264.15D "DE Systems C Coding Standards" dated 12-MAR-06
*
* Deviations from Delco C Coding standards:
*   1. C46 - Abbreviations are not documented in this source file.
*
*   2. C54 - Function header block is placed at the beginning of
*      function definition instead before function proto type
*      declaration.
*
*   4. C60 - The function is pre-emptible or re-entrant is not
*      applicable to this program.
\*============================================================================*/

/*============================================================================*\
*
* Preprocessor #include directive(s)
*
\*============================================================================*/
#include "Systype.h" /*standard types*/

/*===========================================================================*\
* (e) Exported preprocessor #define constants (object-like macros)
\*===========================================================================*/
#define NVM_NULL_PTR        (0x00U)

#define NVM_NOT_INITIALISED (0)
#define NVM_INITIALISED     (1)

#define NVM_JOB_NOT_PRESENT (0)
#define NVM_JOB_PRESENT     (1)

/*===========================================================================*\
* (f) Exported preprocessor #define macros (i.e. those using # or ## operator)
\*===========================================================================*/

/*===========================================================================*\
* (g) Exported type declarations (enum, struct, union, typedef)
\*===========================================================================*/
/* provides job status */
typedef enum
{
   NVM_QUEUE_NORMAL = 0,
   NVM_QUEUE_EMPTY,
   NVM_QUEUE_FULL
}NVM_QueueStatus_T;

/* provide service IDs of READ,WRITE,ERASE to update in queue */
typedef enum
{
   NVM_INIT = 0,
   NVM_READ_BLOCK,
   NVM_WRITE_BLOCK
} NVM_ServiceId_T;

/* provides job status */
typedef enum
{
   NVM_JOB_REQ_IN_QUEUE = 0,
   NVM_JOB_REQ_PENDING,
   NVM_JOB_REQ_NOT_OK,
   NVM_JOB_REQ_COMPLETED,
   NVM_JOB_REQ_FAILED,
   NVM_JOB_REQ_CANCELLED
} NVM_RequestResult_T;

/* updates the cmmonds for assigned job */
typedef enum
{
   NVM_READ_CMD = 0,
   NVM_WRITE_CMD,
   NVM_ERASE_CMD,
   NVM_COMPARE_CMD,
   NVM_REQ_COMPLETED,
   NVM_REQ_DONE
} NVM_CmdStatus_T;

typedef enum
{
   /* The EEL Driver is currently idle */
   NVM_MEM_IDLE = 0,
   /* The EEL Driver is currently busy */
   NVM_MEM_BUSY
} NVM_Mem_Status_T;

/* Job result value returned by EEPROm driver */
typedef enum
{
   /* last read/write/erase job has been finished successsfully */
   NVM_MEM_JOB_OK = 0,
   /* last read/write/erase job failed */
   NVM_MEM_JOB_FAILED,
   /* EEL driver is performing read/write/erase job */
   NVM_MEM_JOB_PENDING,
   /* last job has been aborted */
   NVM_MEM_JOB_CANCELLED,
   /* Job has been launced but not yet complete */
   NVM_MEM_JOB_LAUNCHED,
   /* Previous Job is in progress */
   NVM_MEM_PREV_COMMAND_IN_PROG
} NVM_Mem_JobResult_T;

/* CRC Status */
enum
{
   NVM_CRC_INVALID = 0, /* 0 */
   NVM_CRC_VALID    /* 1 */
};

/* Ram Status */
enum
{
   NVM_RAM_PROTECTED = 0,     /* 0 */
   NVM_RAM_NOT_PROTECTED,     /* 1 */
   NVM_RAM_INVALID_STATE      /* 2 */
};

/* Compare status*/
enum
{
   NVM_EQUAL = 0,    /* 0 */
   NVM_NOT_EQUAL /* 1 */
};


typedef struct
{
   uint8_t blockid;            /* id which represents Event/Fault, configParameters etc */
   uint8_t job_pre_status : 1; /* JOB_PRESENT/NOT status, used to manage queue */
   uint8_t serviceid : 4;     /* NVM_READ_BLOCK, NVM_WRITE_BLOCK, NVM_ERASE_BLOCK*/
   uint8_t Unused : 3;
} NVM_JobRequest_T;

typedef struct
{
   uint8_t CRC_Validity : 1;  /* updates the CRC Validity status */
   uint8_t Job_Status : 4;    /* updates the Job status as in NVM_RequestResult_T */
   uint8_t Prot_Status : 1;   /* updates the ram is protected or not status */
   uint8_t Unused : 2;
} NVM_Admin_Block_T;

/*******************************************************************************
*
* Changes for ICP B78 program
*
* Date        By                        Change
* -----------------------------------------------------------------------------
* 19-Apr-10   KS   Created a module for release 10024438_TCI/1.00
* 07-May-10   KS   updated review comments for release 10024438_TCI/1.00 
*
* 28-May-10   KS   Fix Task tci_ik#3509 for release 10024438_TCI/1.00.
*  - Updated review comments (Review ID : 82521.1296)
*
* 25-Jun-10   KS   Task tci_ik#3701 for release 10024438_TCI/2.00.
*  - Changed NvM to NVM 
*
* 08-Jul-10   KS   Task tci_ik#3804 for release 10024438_TCI/2.00.
*  - Updated as per review comments (Review Id : 83889.1133).
*
* 08-Jul-10   KS   Task tci_ik#3804 for release 10024438_TCI/2.00.
*  - Added typedef to NVM_QueueStatus_T enum
*
* 01-Oct-10  KS      Task no.tci_ik#4116 for release 10024438_TCI/3.00.                                 
*   - modified as per review comments and correscted polyspace warnings.
* 11-Feb-11    GC   Task no.tci_ik#4921 for release 10024438_TCI/5.00.
*                  - corrections in File Header
*******************************************************************************/
#endif /*  NVM_TYPES_H */
