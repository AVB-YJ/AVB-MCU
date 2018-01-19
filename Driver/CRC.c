/*============================================================================*\
 *------------------------------------------------------------------------------
 * Module Name:     CRC.c
 * Created By:      KS
 * Created Date:    30-Apr-2010
 * %version:        1 %
 * %cvtype:         csrc %
 * %instance:       ctc_aud_5 %
 * %derived_by:     lzs7ws %
 * %date_modified:   %
 *------------------------------------------------------------------------------
 *
 * Description: This file contains the functions for calculating CRC
 *
 * Traces to:  10024438_SW_SDD_00001569
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

#include "CRC.h"        /* For Type definitions and prototye checking */
#include "Polyspace.h"
/*============================================================================*\
 *
 * Local preprocessor #define constants (object-like macros)
 *
\*============================================================================*/

/*============================================================================*\
 *
 *  Constant Declarations
 *
 *
\*============================================================================*/


#ifndef CRC_LOOKUP_DISABLED
#define CRC_TABLE_MAX   0x100U
/*look up table with Pre-calculated CRCs Values*/
static const  uint16_t  crc_table[CRC_TABLE_MAX] =
{
   /*A total of 255 pre calculated CRC values
    *the polynomial being 0x1021
    */
   0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U,
   0x8108U, 0x9129U, 0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,
   0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52B5U, 0x4294U, 0x72F7U, 0x62D6U,
   0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU,
   0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U,
   0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU,
   0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U,
   0xB75BU, 0xA77AU, 0x9719U, 0x8738U, 0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU,
   0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U,
   0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
   0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U,
   0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU,
   0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U, 0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U,
   0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U,
   0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U,
   0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U,
   0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU,
   0x1080U, 0x00A1U, 0x30C2U, 0x20E3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
   0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU,
   0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
   0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU,
   0x34E2U, 0x24C3U, 0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
   0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U, 0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU,
   0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,
   0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU,
   0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U,
   0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU,
   0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U, 0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U,
   0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U,
   0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
   0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U,
   0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U
};
#endif
/*============================================================================*\
 *
 * Local type declarations (enum, struct, union, typedef), mixed case
 *
\*============================================================================*/

#define CONSTANT_VALUE_EIGHT (8)

/*============================================================================*\
 *
 * Exported object definitions, mixed case
 *
\*============================================================================*/

/*============================================================================*\
 *
 * Local object definitions, lower case
 *
\*============================================================================*/
static uint16_t CRC_CurrentCrc;
/*============================================================================*\
 *
 * Local function prototypes, mixed case
 *
\*============================================================================*/

/*============================================================================*\
 *
 * Local inline function definitions and #define function-like macros,
 * mixed case
 *
\*============================================================================*/

/*===========================================================================*\
 * (k) Function definitions
\*===========================================================================*/

/*==============================================================================
* FUNCTION: CRC_CalcCRC
*===============================================================================
* Return Value:
*    CRC value for the input data(2 bytes)
* Parameters:
*    InitValue - Initial value of CRC   
*    size - size of input data in bytes
*    *data - pointer to input data(starting address)
*
* External references:
*  External variables: None
*
*  File scope variables: None
*
* Description:
*  To calculate CRC(2 bytes) for the input data. This routine calculates CRC of a memory block pointed with data
*=============================================================================*/
uint16_t CRC_CalcCRC(uint16_t InitValue, uint8_t size, const uint8_t *data)
{
 /* Pre-conditioning 
  * data-->		Pointer to the data block.
  *	size-->		Size of the data block
  */
uint16_t crc = InitValue; 
uint8_t index;

/* Calculates the 2 byte CRC for the required data block. It computes the 16
   bits CRC with CCITT algorithm.
   CRC_LOOKUP_DISABLED macro can be used to select the dynamic slower method or
   the faster look up table method to calculate the CRC
  */
#ifdef CRC_LOOKUP_DISABLED
uint16_t tmp;
uint8_t i,j;
/* Generate CRC bit ,Slower method than Table Look up*
 * Calculates CRC for the input data
 */
for (i=0;i<size;i++)
{
   tmp = data[i]<<CONSTANT_VALUE_EIGHT;

   for(j=0;j<CONSTANT_VALUE_EIGHT;j++)
   {
      if((crc^tmp) & 0x8000)
      {
         crc = (crc<<1)^ CRC_MASK;
      }
      else
      {
         crc<<=1;
      }
      tmp<<=1;
    }
}
/*CRC calculated*/
return crc;
#else
/* Table look up method to generate CRC */
   index = 0;
   while (index < size)
   {  /*CRC calculation using LOOK-UP table*/   
      crc = ((crc & LOOKUP_CRC_MASK) << CONSTANT_VALUE_EIGHT) ^ crc_table[( (crc >> CONSTANT_VALUE_EIGHT) ^ data[index]) & LOOKUP_CRC_MASK];
      index++; 
   }
  /*CRC calculated*/
  return(crc);
#endif
}

/*.==========================================================================*\
 *. FUNCTION: CRC_InitCalcPartOfCRC
 *.==========================================================================
 *. Return Value: 
 *.     None
 *.
 *. Parameters: 
 *.     crc_init_value - Initial Value of the CRC
 *.
 *. External references:   
 *.   External variables: None
 *.
 *.   File scope variables: CRC_CurrentCrc
 *.
 *. Description: 
 *.    This function initialises the CRC_CurrentCrc used for calculation 
 *.    of the CRC as required by the ROMCk component. 
 \*==========================================================================*/
void CRC_InitCalcPartOfCRC(uint16_t crc_init_value)
{
   /*initialises the CRC_CurrentCrc
    *This is called by the ROMck Component
    */
   CRC_CurrentCrc = crc_init_value;  
}

/*.==========================================================================*\
 *. FUNCTION: CRC_CalcPartOfCRC
 *.==========================================================================
 *. Return Value: 
 *.     CRC_CurrentCrc - Updated cumulative value of the CRC of the blocks for
 *.     which it is calculated.
 *.
 *. Parameters: 
 *.     Start Address - Start Address of the Block of Data
 *.     Length - Size of the input block of data in bytes
 *.
 *. External references:   
 *.   External variables: None
 *.
 *.   File scope variables: CRC_CurrentCrc
 *.
 *. Description: 
 *.    This function calculates the 2 byte CRC for the required data. 
 *.    
 *.     
 \*==========================================================================*/
uint16_t CRC_CalcPartOfCRC(uint32_t Startaddr, uint16_t Length ) 
{
   /* This Function is called by the Rom_Compute Function 
    * to compute the function.
    *It computes the 16 bits CRC with CCITT algorithm 
    *using the faster look up table method and updated 
    *also returns computed cumulative CRC
	*/
   uint8_t Index;
   /*Start Address of the Block of Data*/
   const uint8_t __far *DataPointer = ((uint8_t __far *)Startaddr);

   for( Index = 0; Index < Length; Index++ )
   {
      CRC_CurrentCrc = ((CRC_CurrentCrc & LOOKUP_CRC_MASK) << CONSTANT_VALUE_EIGHT) ^ crc_table[( (CRC_CurrentCrc >> CONSTANT_VALUE_EIGHT) ^ *(DataPointer++) ) & LOOKUP_CRC_MASK];
   }
   /*Updated cumulative value of the CRC*/
   return(CRC_CurrentCrc);
}

/**********************************************************************
 *    Function:  GETSUM
 *
 *    Parameters: *Strt_Addr - pointer of begin address of data to be checksumed
 *                bool update - true = update this checksum byte
 *                bool initialize_chksum - true = write the new checksum value
 *                *checksum - pointer to address of checksum
 *
 *     Returns:  Status_Type (E_OK or E_ERROR)
 *
 * Description:  This module will calculate a 16 bit checksum, and either update
 *               the variable or not.  Has capability to calculate a continuation
 *               of a previous call.  If 8 bit Checksum is only needed, then the
 *               MSB can simply be ignored.
 *
 *
 *********************************************************************/
uint16_t Getsum (uint32_t Strt_Addr, size_t size,
               bool_t update, bool_t initialize_chksum, uint16_t *checksum)
{

   const uint8_t __far *ptr = (uint8_t __far *) Strt_Addr;   // pointer to start addr.
   uint16_t cs_succ;
   uint_fast16_t  chs_sum;                               // working summation
   static uint16_t chs_build;                            // store checksum between calls

   chs_sum = (initialize_chksum) ? CHKSUM_OFFSET : chs_build;  // if not a continuation, then start with CHKSUM_OFFSET

   for (; (0 != size); size--)
   {
      chs_sum += *ptr++;                                 // add the bytes
   }

   chs_build = chs_sum;

   if ((chs_build != *checksum) && (!update))
   {
      cs_succ = E_ERROR;
   }
   else
   {
      cs_succ = E_OK;
   }

   if (update)
   {
      *checksum = chs_build;                             // if update requested write in the calculated checksum
   }

   return(cs_succ);
}
/*******************************************************************************
*
* Changes for ICP B78 program
*
* Date         By                        Change
* -----------------------------------------------------------------------------
* 30-Apr-10    KS   Task tci_ik#3384 for release 10024438_TCI/1.00
*   - Created initial version of module
*
* 07-May-10    KS   Task tci_ik#3410 for release 10024438_TCI/1.00
*   - Removed the function CalcPartOfCRC()
*
* 02-Jun-10    KS   Task tci_ik#3561 for release 10024438_TCI/1.00
*   - Modified to remove QAC Warnings.
* 23-Jun-10   SB      Task tci_ik#3689 for release 10024438_TCI/2.00
*                       Added function for for FLASH check.
* 09-Sep-10    RS   Task no.tci_ik#4119 for release 10024438_TCI/3.00.
*                   Changes based on SAD review comments.
* 15-Feb-11   HI    Task no.tci_ik#4973 for release 10024438_TCI/5.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.18 No 65.
* 21-Mar-11   HI    Task no.tci_ik#5059 for release 10024438_TCI/5.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.19 No 5.
*******************************************************************************/
