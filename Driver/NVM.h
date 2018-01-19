#ifndef _NVM_H
#define _NVM_H
/*============================================================================*\
*------------------------------------------------------------------------------
* Module Name:     NVM.h
* Created By:      KS
* Created Date:    19-Apr-2010
* %version:        5.1.7 %
* %cvtype:         incl %
* %instance:       ctc_aud_3 %
* %derived_by:     rzlw3b %
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
#include "Std_Types.h"
#include "NVM_Cfg.h"        /* For NVRAM configurations */
#include "CRC.h"
#include "fdl.h"
#include "fdl_descriptor.h"
#include "eel.h"
#include "OS.h"

/*===========================================================================*\
* (e) Exported preprocessor #define constants (object-like macros)
\*===========================================================================*/

/*===========================================================================*\
* (f) Exported preprocessor #define macros (i.e. those using # or ## operator)
\*===========================================================================*/
//#define NVM_Get(signal_name)   NVM_Get_##signal_name()
//#define NVM_Set(signal_name, value)   NVM_Set_##signal_name(value)

//#define NVM_Set_NVM_INHIBITION(vlaue)   (NVM_Inhibition = vlaue)


#define NVM_EEL_POLLING                     (uint8_t)0x00U
#define NVM_EEL_ENFORCE                     (uint8_t)0xFFU
#define NVM_CRC_INIT_VALUE                  0xFFFFU

/*===========================================================================*\
* (g) Exported type declarations (enum, struct, union, typedef)
\*===========================================================================*/

/*===========================================================================*\
* (h) Exported object declarations
\*===========================================================================*/
//extern bool_t NVM_Inhibition;

typedef enum  __DIM_CHANNEL_Tag
{
    DIM_CHANNEL_Q, 
    DIM_CHANNEL_1, 
    DIM_CHANNEL_2, 
    DIM_CHANNEL_3,
    #ifdef ICS_HVAC_IS
    DIM_CHANNEL_4,
    DIM_ChANNEL_5, 
    DIM_ChANNEL_6, 
    DIM_CHANNEL_7,
    DIM_CHANNEL_8,
    #endif
    DIM_CHANNEL_MAX
}DIM_CHANNEL_T;
/*******************************************************************************************/

/*============================================================================*\
*
* Exported function prototypes (including function-header-block),
* (without "extern"), mixed case
*
\*============================================================================*/
void NVM_Init(void);
void NVM_Start(void);
/* 5ms Periodic task */
void NVM_Task(void);  
//NVM_Mem_Status_T NVM_Get_EEL_Status(void);
//eel_status_t NVM_DIAG_EEL_Command_Request(uint8_t rcs_Com, uint8_t nvm_diag_com);
//added for ICS
extern void NVM_EEPROM_Shutdowm(void);
extern NVM_Mem_JobResult_T NVM_Direct_Read2(uint8_t block_id, uint16_t sub_pos, uint8_t *NVM_DstPtr, uint8_t bytes);
extern  NVM_Mem_JobResult_T NVM_Direct_Write(uint8_t block_id, uint8_t sub_pos, uint8_t *NVM_DstPtr, uint8_t bytes);
//extern uint16_t NVM_Get_SubBlock_Addr(uint16_t mem_pos);
//extern uint8_t NVM_Get_Block_ID(uint16_t mem_pos);
extern void NVM_Set_Rom_To_EE(void);
extern void OS_Delay(uint8_t usec);
extern void NVM_Set_DTC_To_Default(void);
static uint16_t NVM_Get_SubBlock_Size(uint8_t block_id, uint16_t sub_pos);
extern NVM_Mem_JobResult_T NVM_Write_EE(uint32_t dest, uint32_t src, uint8_t num_bytes);
extern NVM_Mem_JobResult_T NVM_Read_EE(uint32_t dest, uint32_t src, uint8_t num_bytes);
/*extern boolean NVM_Get_DIM_Cal_Data(DIM_CHANNEL_T channel, uint8_t* dest);*/
extern boolean NVM_Update_Block_Chksum(NVM_Block_Id_T block_id);


/*******************************************************************************
*
* Changes for ICP B78 program
*
* Date        By                        Change
* -----------------------------------------------------------------------------
* 19-Apr-10   KS   Created a module for release 10024438_TCI/1.00
*
* 07-May-10   KS   updated review comments for release 10024438_TCI/1.00 
*  - Removed periodic function NvM_Handler() and added enum Block_Id_T
*
* 18-May-10   KS   Task tci_ik#3420 for release 10024438_TCI/1.00
*  - Added EEl and Fdl header files and updated Enum according memory map 
*
* 21-May-10   KS   Fix Task tci_ik#3455 for release 10024438_TCI/1.00
*  - Added Header files DDP.h, DDP_Types.h
*
* 27-May-10   KS   Fix Task tci_ik#3476 for release 10024438_TCI/1.00
*  - Removed stub function and NVM_EraseBlock and NVM_Direct_Erase.
*  - Added function NVM_Daig_EEL_Command_Request()
*  - Fixed QAC warning.
*
* 04-Jun-10   KK   Task no.tci_ik#3576 for release 10024438_TCI/1.00.
*   - Changing NVM_Get_EEL_Status from static to public
*
* 07-Jun-10   SB   Task no.tci_ik#3579 for release 10024438_TCI/1.00.
*   - Changed function name to NVM_DIAG_EEL_Command_Request.
*
* 25-Jun-10   KS   Task no.tci_ik#3701 for release 10024438_TCI/2.00.
*   - Changed to NVM and added #define.
*
* 02-Jul-10    KS   Task no.tci_ik#3770 for release 10024438_TCI/2.00.
*   - Added function NVM_FDL_EEL_Activate()
*
* 19-Jul-10    KS   Task no.tci_ik#3823 for release 10024438_TCI/2.00.
*   - Modified NVN_MainFunction to NVM_Task as per SAD v1.8.
*
* 02-Aug-10   KS    Task no.tci_ik#3894 for release 10024438_TCI/2.00..
*   - Implemented PR tci_ik#298 and modified for QAC warnings.
*
* 01-Oct-10  KS      Task no.tci_ik#4116 for release 10024438_TCI/3.00.                                 
*   - modified as per review comments and correscted polyspace warnings.
*
* 24-Nov-10   KS    Task no.tci_ik#4323 for release 10024438_TCI/4.00.
*   - Modified as per new NVM Mapping ver3.2.
*
* 1-Dec-10   GC    Task no.tci_ik#4428 for release 10024438_TCI/4.00.
*   - Modified for suppressing QAC warning.
*
* 6-Dec-10  GC  Task no.tci_ik#4483 for release 10024438_TCI/4.00.
*      Modified as per peer review comments.
*
* 16-Dec-10  KS     Task no.tci_ik#4457 for release 10024438_TCI/4.00.
*   - Modified as per SAD requirement 03.1-0288 ~3.2.
*
* 05-Jan-11    KS   Task no.tci_ik#4681 for release 10024438_TCI/4.00.
*   - Modification of software component to match SAD interface name
*
* 07-Jan-11    KS   Task no.tci_ik#4704 for release 10024438_TCI/4.00.
*   - Modified for Remove QAC Warnings
*
* 11-Feb-11    GC   Task no.tci_ik#4921 for release 10024438_TCI/5.00.
*   - corrections in File Header
*
* 10-Mar-11  KS   Task no.tci_ik#5011 for release 10024438_TCI/5.00.
*   - Modified as per EPM_00001239_NVM_Mapping_File_ICP_B78.xls~03.14
*
* 07-Apr-11  KS   Task no.tci_ik#5156 for release 10024438_TCI/5.00.
*   - Modified the function NVM_RestoreDefaultAllBlocks function for optimisation.
*******************************************************************************/
#endif /*  _NVM_H */
