
/*============================================================================*\
*------------------------------------------------------------------------------
* Module Name:     RomCk
* Created By:      SB
* Created Date:    30-Apr-2010
* %version:        1 %
* %cvtype:         csrc %
* %instance:       ctc_aud_5 %
* %derived_by:     lzs7ws %
* %date_modified:  %
*------------------------------------------------------------------------------
*
* Description: This file contains the functions for ROM check
*
* Traces to: 10024438_SW_SDD_00001571
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
#include "CRC.h"
#include "OS.h"
#include "RomCk.h"
#include "OS_Task.h"

/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/
#define SHIFT_8                         8
#define LOW_BITS                        (uint8_t)0x00FFU

/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/
enum array_pos
{
   ARRAY_POSITION_0=0,
   ARRAY_POSITION_1,
   ARRAY_POSITION_2
};
/*============================================================================*\
 *
 * Exported object definitions, mixed case
 *
\*============================================================================*/
/* Final value of the CRC after the completion of the ROM Check.*/ 
uint16_t RomCk_FinalCRC;

/*============================================================================*\
 *
 * Local object definitions, lower case
 *
\*============================================================================*/

static uint32_t   RomCk_CurrentStartaddr;
/* Cumulative 2 byte CRC value for the requested data block calculated and 
 * returned by the function, CRC_CalcPartOfCRC().
 */ 
static uint16_t RomCk_Part_Of_CRC;
static uint8_t RomCk_FlashStatus = FLASH_CHECK_INPROGRESS;

typedef struct
{
   uint32_t  RomCk_Flash_Start_Address;
   uint32_t  RomCk_Flash_End_Address;
} RomCk_Flash_Blocks_T;

static const  RomCk_Flash_Blocks_T RomCk_Flash_Blocks[FLASH_BLOCK_NB] = ADDRESS_RANGE;

/*============================================================================*\
 *
 * Local function prototypes, mixed case
 *
\*============================================================================*/

static void RomCk_CompleteROMCheckProcess(void);

/*============================================================================*\
 * FUNCTION: RomCk_Init
 *===============================================================================
 * Return Value:
 *  None
 *
 * Parameters:
 *   None 
 * External references: None
 *  External variables: None
 *  File scope variables: CurrentStartaddr
 *
 * Description:   This function initializes the component 
 \*===========================================================================*/
void RomCk_Init(void)
{
   RomCk_CurrentStartaddr = RomCk_Flash_Blocks[0].RomCk_Flash_Start_Address;   /* Starting address*/
   /* Initialise the running CRC variable (CurrentCrc) used for the calculation 
    * of the CRC.
    */
   CRC_InitCalcPartOfCRC(FLASH_CHKSUM_INITVALUE);
}

/*============================================================================*\
 * FUNCTION: RomCk_Start
 *===============================================================================
 * Return Value:
 *  None
 *
 * Parameters:
 *   None 
 * External references: None
 *  External variables: None
 *  File scope variables: CurrentStartaddr
 *
 * Description:   This function  starts the compute the CRC in slow mode(every 200ms)
 \*===========================================================================*/
void RomCk_Start(void)
{
   RomCk_SetMode(MODE_SLOW);      /* Start the Rom Check Task in Slow mode */
}

/*============================================================================*\
 * FUNCTION: RomCk_Compute
 *===============================================================================
 * Return Value:
 *  None
 *
 * Parameters:
 *   None 
 * External references: CRC_CalcPartOfCRC
 *  External variables: None
 *  File scope variables: CurrentStartaddr
 *
 * Description:   This is the Compute function (task handler) to compute the checksum.
\*===========================================================================*/

void RomCk_Compute(void)
{
   static uint8_t BlockNo = 0;
   uint16_t FlashLength;

   /* for all flash blocks */
   if (BLOCK_SIZE <= ((RomCk_Flash_Blocks[BlockNo].RomCk_Flash_End_Address - RomCk_CurrentStartaddr) + 1UL))
   {
      RomCk_Part_Of_CRC = CRC_CalcPartOfCRC( RomCk_CurrentStartaddr, BLOCK_SIZE );
      if (RomCk_CurrentStartaddr == RomCk_Flash_Blocks[BlockNo].RomCk_Flash_End_Address)
      {
         BlockNo++;
         if (FLASH_BLOCK_NB == BlockNo)
         {
            /* last block */
            BlockNo = 0;
            /* check checksum */
            RomCk_CompleteROMCheckProcess();
         }
         RomCk_CurrentStartaddr = RomCk_Flash_Blocks[BlockNo].RomCk_Flash_Start_Address;
      }
      else
      {
         RomCk_CurrentStartaddr += BLOCK_SIZE;
      }
   }
   else
   {
      /* add checksum for the last bytes of the block */
      FlashLength = (uint16_t)( RomCk_Flash_Blocks[BlockNo].RomCk_Flash_End_Address - RomCk_CurrentStartaddr ) + (uint16_t)0x01U;
      RomCk_Part_Of_CRC = CRC_CalcPartOfCRC( RomCk_CurrentStartaddr, FlashLength );
      BlockNo++;
      if (FLASH_BLOCK_NB == BlockNo)
      {
         /* last block */
         BlockNo = 0;
         /* check checksum */
         RomCk_CompleteROMCheckProcess();
      }
      /* Reinitialize sequence after Final CRC calculated */
      RomCk_CurrentStartaddr = RomCk_Flash_Blocks[BlockNo].RomCk_Flash_Start_Address;
   }
}

/*============================================================================*\
 * FUNCTION: RomCk_CompleteROMCheckProcess
 *===============================================================================
 * Return Value:
 *       None
 *
 * Parameters:
 *       None
 * 
 * External references: 
 *           
 *    External variables: EcuM_CheckSumAddressMSB, EcuM_CheckSumAddressLSB,
 *                          RomCk_FinalCRC.
 *    File scope variables: RomCk_Part_Of_CRC 
 *
 * Description:
 *       Updates the Flash status and stores the Final Calculated CRC
\*===========================================================================*/
static void RomCk_CompleteROMCheckProcess(void)
{
   uint8_t Sw_Checksum[ARRAY_POSITION_2];
   
   /* Update the Final value of the CRC after the completion of the ROM Check */
   RomCk_FinalCRC = RomCk_Part_Of_CRC;

   /* Read the static check sum value*/
   Sw_Checksum[ARRAY_POSITION_0] = (*((uint8_t __far *)EcuM_CheckSumAddressMSB));
   Sw_Checksum[ARRAY_POSITION_1] = (*((uint8_t __far *)EcuM_CheckSumAddressLSB));

   /* Compare the calculated checksum with the flashed checksum */
   if ((Sw_Checksum[ARRAY_POSITION_0] == (uint8_t)(RomCk_FinalCRC >> SHIFT_8)) &&
       (Sw_Checksum[ARRAY_POSITION_1] == (uint8_t)(RomCk_FinalCRC & LOW_BITS)))
   {
      RomCk_FlashStatus = FLASH_CHECK_COMPLETE_OK;   /* Successfully completed */
   }
   else
   {
      RomCk_FlashStatus = FLASH_CHECK_COMPLETE_NOK;   /* Successfully not completed */
   }
   RomCk_StopCompute();
}

/*============================================================================*\
 * FUNCTION: RomCk_GetComputeResult
 *===============================================================================
 * Return Value:
 *       RomCk_FlashStatus - Status of the Flash Check.
 *
 * Parameters:
 *       None
 * 
 *. External references:   
 *.   External variables: None
 *.
 *.   File scope variables: RomCk_FlashStatus
 *
 * Description:
 *       This function returns the compute result (In progress, CRC OK, CRC NOK)
\*===========================================================================*/
uint8_t RomCk_GetComputeResult(void)
{
   return(RomCk_FlashStatus);         /* Returns the flash status */
}

/*============================================================================*\
 * FUNCTION: RomCk_StopCompute
 *===============================================================================
 * Return Value:
 *  None
 *
 * Parameters:
 *   None 
 * External references: OS_CancelTask
 *  External variables: None
 *  File scope variables: None
 *
 * Description:   This function stops the computation progress.
\*===========================================================================*/
void RomCk_StopCompute(void)
{
   /* stop the periodic task (checksum calculated only one time) */
  // (void)OS_CancelTask(OS_Task_RomCk);
}

/*============================================================================*\
 * FUNCTION: RomCk_SetMode
 *===============================================================================
 * Return Value:
 *  None
 *
 * Parameters:
 *   flashcheck_mode 
 * External references: OS_ActivateTask
 *  External variables: None
 *  File scope variables: None
 *
 * Description:   This function changes the mode between "Normal" (200ms) and "Fast"(1ms).
\*===========================================================================*/
void RomCk_SetMode(Flashcheck_mode_Type flashcheck_mode)
{
   if (flashcheck_mode == MODE_FAST)
   {
      /* Start the Task in fast mode ( 1ms) */
     // (void)OS_ActivateTask(OS_Task_RomCk, FAST_FLASH_PERIODIC_TASK, FAST_FLASH_PERIODIC_TASK);
   }

   else
   {
      /* Start the Task in slow mode ( 200ms) */
     // (void)OS_ActivateTask(OS_Task_RomCk, SLOW_FLASH_PERIODIC_TASK, SLOW_FLASH_PERIODIC_TASK);
   }
}

/*******************************************************************************
*
* Changes for ICS program
*
* Date        By                        Change
* -----------------------------------------------------------------------------
* 02-May_11   Wade   initial version for ICS 
*
* 23-Jun-10   SB     Task tci_ik#3689 for release 10024438_TCI/2.00
                     Created module for FLASH check.
* 20-Jul-10   SIL    Task tci_ik#3836 for release 10024438_TCI/2.00
*                    Implemented review comments
* 09-Sep-10    RS   Task no.tci_ik#4119 for release 10024438_TCI/3.00.
*                   Changes based on SAD review comments.
* 28-Sep-10    RS   Task no.tci_ik#4198 for release 10024438_TCI/3.00.
*                   Changes based on review comment document 
*                   10024438_SW_RVW_00001215_00.14 Nr 61: Renamed extern 
*                   variables to have the module name as prefix.
* 25-Feb-11  KK   Task no.tci_ik#4984 for release 10024438_TCI/5.00.
*             - SAD verification comments implementation
* 15-Feb-11   HI    Task no.tci_ik#4865 for release 10024438_TCI/5.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.18 No 65.
* 21-Mar-11   HI    Task no.tci_ik#5059 for release 10024438_TCI/5.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.19 No 5.

********************************************************************************/