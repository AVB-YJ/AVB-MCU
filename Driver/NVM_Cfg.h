#ifndef _NVM_CFG_H
#define _NVM_CFG_H
/*============================================================================*\
*------------------------------------------------------------------------------
* Module Name:     NVM_Cfg.h
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

#include "NVM_Types.h"
//#include "App_DIAG.h"
/*===========================================================================*\
* (f) Exported preprocessor #define macros (i.e. those using # or ## operator)
\*===========================================================================*/

/* Maximun No of retry for writing */  
#define NVM_MAX_NO_OF_WRITE_RETRIES (2)
/* NVM RAM Blocks*/

//wade: all block size is 4 bytes
#define NVM_BLK0_LENGTH    (1)    /*4-->8 EEP Sector */

enum
{
    CAL_ROM_DEFAULT = 0xFF,
    CAL_MFT_VALID = 0x01,
    CAL_MFT_INVALID = 0x00
};

#define CAL_DEFAULT CAL_MFT_INVALID

/* Job end notification after completion of requested job to application component */  
#define NVM_App_JobEndNotification(BlockID, JobStatus) //App_DIAG_NVMJobEndNotification(BlockID, JobStatus)

/*===========================================================================*\
* (g) Exported type declarations (enum, struct, union, typedef)
\*===========================================================================*/

typedef enum
{
   NVM_SECTOR_BLK_ID = 0,         /* 1, Fan_Speed*/
   NVM_MAX_B81_ID
}NVM_Block_Id_T;

#define NVM_DTC_START_ID       NVM_DTC1

/*typedef enum
{
   D_TAB_LUM_CLIM_COULEUR_1_MAIN_INDEX = 0,
   D_TAB_LUM_CLIM_COULEUR_1_WHEEL_INDEX = 16,
   D_TAB_CLIM_COULEUR_SPARE1_INDEX = 32,
   D_TAB_CLIM_COULEUR_SPARE2_INDEX = 48,
   D_FCT_LED_DAY_INDEX = 64,
   D_FCT_LED_NIGHT_INDEX = 65,
   PWM_ADJUST_VALUE_INDEX = 66,
   ATM_AUTH_TABLE_INDEX = 67,
   CONFIG_SPARE1_INDEX = 69,
   PUSH_VARIANT_INDEX = 78,
   CONFIG_SPARE2_INDEX = 88
}NVM_Config_Index_T;

typedef enum
{
   DELTA_FSR_PRESSED_PUSH_00_INDEX = 0,
   DELTA_FSR_PRESSED_PUSH_01_INDEX = 2,
   DELTA_FSR_PRESSED_PUSH_02_INDEX = 4,
   DELTA_FSR_PRESSED_PUSH_03_INDEX = 6,
   DELTA_FSR_PRESSED_PUSH_04_INDEX = 8,
   DELTA_FSR_PRESSED_PUSH_05_INDEX = 10,
   DELTA_FSR_PRESSED_PUSH_06_INDEX = 12,
   DELTA_FSR_PRESSED_PUSH_07_INDEX = 14,
   DELTA_FSR_PRESSED_PUSH_08_INDEX = 16,
   DELTA_FSR_PRESSED_PUSH_09_INDEX = 18,
   FSR_SPARE_1_INDEX = 20,
   FSR_PIDLE_PERIOD_INDEX = 251
}NVM_FSR_Index_T;

typedef enum
{
   AUTH_PSAProductNumber_EE_INDEX = 0,
   AUTH_PSAProductRefNumber_EE_INDEX = 5,
   AUTH_SPARE_01_INDEX = 10,
   AUTH_CalibVersion_EE_INDEX = 12,
   AUTH_VersDiag_EE_INDEX = 14,
   AUTH_NbParamFlT_EE_INDEX = 15,
   AUTH_ApplicationType_EE_INDEX = 16,
   TRAC_YearOfBuild_EE_INDEX = 20,
   TRAC_MonthOfBuild_EE_INDEX = 21,
   TRAC_DayOfBuild_EE_INDEX = 22,
   TRAC_ECUChronoNumber_EE_INDEX = 23,
   MANUFACTURING_DATA_EE_INDEX = 27,
   AUTH_SPARE_02_INDEX = 28
}NVM_Ident_Index_T;

typedef enum
{
   PCB_TESTS_DPN = 0,
   PCB_TESTS_DOP_DAY = 5,
   PCB_TESTS_DOP_MONTH = 6,
   PCB_TESTS_DOP_YEAR = 7,
   PCB_TESTS_SERIALNUMBER = 8,
   PCB_TESTS_FREEBYTE_AREA1 = 13,
   PCB_TESTS_HW_RELEASE = 14,
   PCB_TESTS_GONOGO_FLAGS = 16,
   PCB_TESTS_LED_TYPE = 19,
   PCB_TESTS_FREEBYTE_AREA2 = 26
}NVM_PCB_Index_T;

typedef enum
{
   PART_TESTS_1_GOOD_TEST_CNT = 0,
   PART_TESTS_1_BAD_TEST_CNT = 1,
   PART_TESTS_1_DPN = 2,
   PART_TESTS_1_DOP_DAY = 7,
   PART_TESTS_1_DOP_MONTH = 8,
   PART_TESTS_1_DOP_YEAR = 9,
   PART_TESTS_1_SERIALNUMBER = 10,
   PART_TESTS_1_FREEBYTE_AREA1 = 15,
   PART_TESTS_1_GONOGO_FLAGS = 16,
   PART_TESTS_1_FREEBYTE_AREA2 = 17
}NVM_EOL1_Index_T;

typedef enum
{
   PART_TESTS_2_GOOD_TEST_CNT = 0,
   PART_TESTS_2_BAD_TEST_CNT = 1,
   PART_TESTS_2_DOP_DAY = 2,
   PART_TESTS_2_DOP_MONTH = 3,
   PART_TESTS_2_DOP_YEAR = 4,
   PART_TESTS_2_SERIALNUMBER = 5,
   PART_TESTS_2_FREEBYTE_AREA1 = 9,
   PART_TESTS_2_GONOGO_FLAGS = 10,
   PART_TESTS_2_FREEBYTE_AREA2 = 11
}NVM_EOL2_Index_T;*/

/* Mode & Setting NVM block parameter indexes*/
enum
{
   DIRECTION_INDEX = 0,
   MODE_FONCT_INDEX,
   DMD_VISI_INDEX,
   DMD_AC_INDEX,
   TYPAGE_INDEX,
   VAL_CONS_TEMP_AVD_INDEX,
   VAL_CONS_TEMP_AVG_INDEX,
   DISTRIBUTION_AVG_INDEX,
   ENTREE_AIR_INDEX,
   PULS_AV_INDEX,
   UNIT_TEMP_INDEX,
   ETAT_REAR_INDEX,
   MEM_MODE_FONCT_INDEX,
   MEM_ENTREE_AIR_INDEX,
   MEM_VAL_CONS_TEMP_AVG_INDEX,
   MEM_VAL_CONS_TEMP_AVD_INDEX,
   MEM_PULS_AV_INDEX,
   MEM_DISTRIBUTION_AVG_INDEX,
   MEM_DMD_AC_INDEX,
   MEM_ETAT_REAR_INDEX,
   MEM_MODESTOP_DMD_AC_INDEX,
   MEM_MODEHY_DMD_AC_INDEX,
   FLAG_RM_EA_INDEX,
   FLAG_RM_MODESTOP_AC_INDEX,
   HVAC_TYPE_INDEX,
   ETAT_AQS_INDEX
};

typedef enum
{
   EXTERNAL_RESET_CAUSE_EE_INDEX = 0,
   WATCHDOG_RESET_CAUSE_EE_INDEX = 1,
   ILLEGAL_OPCODE_RESET_CAUSE_EE_INDEX = 2,
   STACK_OVERFLOW_RESET_CAUSE_EE_INDEX = 3,
   OS_SELFCHECKS_RESET_CAUSE_EE_INDEX = 4,
   UNUSED_INTERRUPT_RESET_CAUSE_EE_INDEX = 5
}NVM_ENGG_Index_T;

typedef enum
{
   NORMAL_GOTO_SLEEP_INDEX = 0,
   RESET_SPARE_1_INDEX = 1
}NVM_ResetBlk_Index_T;

/* NVRAM Blocks Standard and redundent blocks are used */
typedef enum
{
   NVM_STANDARD_BLOCK = 0,
   NVM_DATASET_BLOCK,
   NVM_REDUNDENT_BLOCK
}NVRAM_Block_T;

typedef struct
{
   uint8_t Nvm_EEL_Id;         /* To get EEL ID of each block */
   uint8_t Nvm_Length;         /* To get block length */
   uint8_t *Nvm_Srcptr;        /* To get Ram start address */
   const uint8_t *Nvm_Romptr;  /* To get Rom start address */
   NVRAM_Block_T NvRam_BlkType;
} NVM_Mem_Block_Config_T;

//need block id, block size, mem_pos, sub_block_size, need chksum

typedef struct
{
   uint16_t mem_pos;        /* To get Ram start address */
   bool_t  chksum;
} NVM_Block_Info_Config_T;


extern  const NVM_Mem_Block_Config_T NVM_Mem_config[NVM_MAX_B81_ID];

//extern uint8_t NVM_RAMBlock_DTC2[NVM_DTC_LENGTH];   /* DTC2 */
//extern uint8_t NVM_RAMBlock_DTC3[NVM_DTC_LENGTH];   /* DTC3 */
//extern uint8_t NVM_RAMBlock_DTC4[NVM_DTC_LENGTH];   /* DTC4 */
//extern uint8_t NVM_RAMBlock_DTC5[NVM_DTC_LENGTH];   /* DTC5 */
//extern uint8_t NVM_RAMBlock_DTC6[NVM_DTC_LENGTH];   /* DTC6 */
//extern uint8_t NVM_RAMBlock_DTC7[NVM_DTC_LENGTH];   /* DTC7 */
//extern uint8_t NVM_RAMBlock_DTC8[NVM_DTC_LENGTH];   /* DTC8 */
//extern uint8_t NVM_RAMBlock_DTC9[NVM_DTC_LENGTH];   /* DTC9 */

/*******************************************************************************
*
* Changes for ICP B78 program
*
* Date        By                        Change
* ----------------------------------------------------------------------
* 19-Apr-10   KS   Created a module for release 10024438_TCI/1.00
*
* 07-May-10   KS   updated review comments for release 10024438_TCI/1.00 
*  - Moved #define NVM_JOB_QUEUE_SIZE to NVM.c file
*  
* 18-May-10   KS   Task tci_ik#3420 for release 10024438_TCI/1.00.
*  - Updated DTC Ram and rom block.
*
* 27-May-10   KS   Fix Task tci_ik#3476 for release 10024438_TCI/1.00.
*  - Renamed call back function to App_DIAG_NVMJobEndNotification. 
*  - Added header file App_DIAG.h and added Block_Id_T enum.
*
* 28-May-10   KS   Fix Task tci_ik#3509 for release 10024438_TCI/1.00.
*  - Updated review comments (Review ID : 82521.1296) 

* 25-Jun-10   KS   Task tci_ik#3701 for release 10024438_TCI/2.00.
*  - Changed Nvm to NVM 

* 09-Jul-10   KS   Task tci_ik#3808 for release 10024438_TCI/2.00.
*   - Changed the rom block and NVM_Mem_config as per NVM mapping ver 1.1

* 02-Aug-10   KS    Task no.tci_ik#3894 for release 10024438_TCI/2.00..
*   - Implemented PR tci_ik#298 and modified for QAC warnings.

* 05-Aug-10   KS    Task no.tci_ik#3912 for release 10024438_TCI/2.00..
*   - Added index type for NVM blocks.
*
* 08-Sep-10   KS   Task tci_ik#4124 for release 10024438_TCI/3.00.
*   - Updated Default values as per NVM Mapping Ver2.3
*
* 21-Sep-10   KS   Task tci_ik#4174 for release 10024438_TCI/3.00.
*   - Updated Default values as per NVM Mapping Ver2.4
*
* 24-Nov-10   KS    Task no.tci_ik#4421 for release 10024438_TCI/4.00.
*   - Modified as per new NVM Mapping ver3.2.
*
* 26-Nov-10   KS    Task no.tci_ik#4421 for release 10024438_TCI/4.00.
*   - Modified as per new NVM Mapping ver3.3.
*
* 01-Dec-10   GC    Task no.tci_ik#4428 for release 10024438_TCI/4.00.
*   - Modified for suppressing QAC warning.
*
* 06-Dec-10  GC  Task no.tci_ik#4483 for release 10024438_TCI/4.00.
*     Modified as per peer review comments.
*
* 16-Dec-10    KS   Task no.tci_ik#4588 for release 10024438_TCI/4.00.
*   Changes done as per NVM Memory mapping Version 3.7.
*
* 20-Dec-10    KS   Task no.tci_ik#4611 for release 10024438_TCI/4.00.
*   Mode and settings index enum is moved to NVM_Cfg.h
*
* 10-Mar-11  KS   Task no.tci_ik#5011 for release 10024438_TCI/5.00.
*   - Modified as per EPM_00001239_NVM_Mapping_File_ICP_B78.xls~03.14
*
* 05-Apr-11  KS   Task no.tci_ik#5148 for release 10024438_TCI/5.00.
*   - Modified as per EPM_00001239_NVM_Mapping_File_ICP_B78.xls~03.19

*******************************************************************
*  11-Aug-11 wade reconfigure it for ICS
*******************************************************************************/

#endif /* _NVM_CFG_H */

