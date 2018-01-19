/*******************************************************************************
 *  Project       : 10024438_ICP_B78
 *  SW component  : RomCk - ROM Check
 *  SW file       : %name:          RomCk_Cfg.h %
 *  Version       : %version:       1 %
 *  Instance      : %instance:      ctc_aud_2 %
 *  Author        : rzh73y
 *  Creation Date : Mon Mar 21 16:37:07 2011
 *----------------------------------------------------------------------------
 *  Last modification done
 *             by : %derived_by:    lzs7ws %
 *             on : %date_created:  Tue Jun 26 15:36:54 2012 %
 *----------------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description   : <Description>
 *
 */            
 /*-----------------------------------------------------------------------------
 ******************************************************************************/

/* To avoid multiple definition if the file is included several times */
#ifndef _RomCk_CFG_H
#define _RomCk_CFG_H

/*============================================================================*\
 *                          --- Public typedefs ---
\*============================================================================*/


/*============================================================================*\
 *                          --- Public constants ---
\*============================================================================*/
#define BLOCK_SIZE                      16UL /* CRC is computed 16byte size block wise*/

/* the macro COMPLETE_FLASH_CHECKSUM used to calculate the checksum of the
 * entire flash that is 0 to 0x00017FFD. 0x17FFE and 0x17FFF used for storing
 * the checksum
 */

#ifdef COMPLETE_FLASH_CHECKSUM   
#define FLASH_BLOCK_NB           1   /* No. of flash separate address ranges */
#define ADDRESS_RANGE      { {0x00000000UL, 0x00017FFDUL} } 
#else
/* the checksum calculated avoiding the Flash area used by the minicube to 
 * enable the debug capability.
 */
#define FLASH_BLOCK_NB          4    /* No. of flash separate address ranges */
#define ADDRESS_RANGE      { {0x00000004UL, 0x0000007FUL}, \
                             {0x000000C0UL, 0x000000C2UL}, \
                             {0x000000D8UL, 0x0000FFFDUL}, \
                             {0x00010000UL, 0x00017BFFUL}  \
                           }
#endif                                                        

#define FLASH_CHKSUM_INITVALUE  0x1D0FU


#define ROMCK_SLOW_FLASH_PERIODIC_TASK        OS_Task_RomCk_Period_Slow    /* 200ms */
#define ROMCK_FAST_FLASH_PERIODIC_TASK        OS_Task_RomCk_Period_Fast    /* 1ms */


/*============================================================================*\
 *                          --- Public variables ---
\*============================================================================*/




/*============================================================================*\
 *                          --- Public functions ---
\*============================================================================*/



#endif /* CRC_CFG_H */
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/


/*******************************************************************************
*
* Changes for ICP B78 program
*
* Date         By                        Change
* -----------------------------------------------------------------------------
* 21-Mar-11   HI    Task no.tci_ik#5059 for release 10024438_TCI/5.00.
*                   Changes made as per review comment document 
*                   10024438_SW_RVW_00001215_00.19 No 5.
* 21-Mar-11    JJ   Task no.tci_ik#5066 for release 10024438_TCI/5.00.
*                    -Calculate the Flash checksum for entire area
******************************************************************************/
