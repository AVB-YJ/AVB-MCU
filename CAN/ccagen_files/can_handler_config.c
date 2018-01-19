/**********************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_handler_config.c                                         
  File Description:
  This module contains tables that can be used by any of the CAN Handler           
  layers and modules.                               

*************************************************************************/


#include "can_handler_config.h"


#ifdef HASH_SEARCH
/*******************************************************************************
 START OF CONFIGURATION FOR CHANNEL-0 HASH TABLE 
 ******************************************************************************/
#ifdef CAN_CH0_HASH_SEARCH

#endif      /*  End #ifdef CAN_CH0_HASH_SEARCH  */
/*******************************************************************************
 START OF CONFIGURATION FOR CHANNEL-1 HASH TABLE 
 ******************************************************************************/
#ifdef CAN_CH1_HASH_SEARCH

#endif      /*  End #ifdef CAN_CH1_HASH_SEARCH  */
/*******************************************************************************
 START OF CONFIGURATION FOR CHANNEL-2 HASH TABLE 
 ******************************************************************************/
#ifdef CAN_CH2_HASH_SEARCH

#endif      /*  End #ifdef CAN_CH2_HASH_SEARCH  */

/*******************************************************************************
 START OF CONFIGURATION FOR CHANNEL-0,1,2 HASH CONFIGURATION TABLE 
 ******************************************************************************/
/* Define the following values for HASH Search:                    *
* HASH_MASK: Mask used to validate only the bits in the unique pattern*
* HASH_START_BIT: Start bit to get Unique pattern in the Hash Table*
* HASH_LENGTH: Total No. of bits used to get  the unique Pattern   */

const Hash_Config_Table_T  Hash_Config_Table[] = 
{
/* Hash_Mask, Hash_Start_Bit, Hash_Length */
 #ifdef CAN_CH0_HASH_SEARCH
  
 #endif        /*  End #ifdef CAN_CH0_HASH_SEARCH  */

 #ifdef CAN_CH1_HASH_SEARCH
  
 #endif        /*  End #ifdef CAN_CH1_HASH_SEARCH  */

 #ifdef CAN_CH2_HASH_SEARCH

 #endif        /*  End #ifdef CAN_CH2_HASH_SEARCH  */
};

const canuint8_t Size_Of_Hash_Tables[]=
{
 #ifdef CAN_CH0_HASH_SEARCH
 (sizeof(Hash_Table_Ch0))/(sizeof(canuint8_t)),
 #endif      
 #ifdef CAN_CH1_HASH_SEARCH
 (sizeof(Hash_Table_Ch1))/(sizeof(canuint8_t)),
 #endif      
 #ifdef CAN_CH2_HASH_SEARCH
 (sizeof(Hash_Table_Ch2))/(sizeof(canuint8_t)),
 #endif      
};

#endif         /* End #ifdef HASH_SEARCH */

#ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER
void CAN_Handler_Disable_Global_Interrupts(void)
{
  
}

void CAN_Handler_Enable_Global_Interrupts(void)
{
	
}

#endif        /* End #ifdef DISABLE_GLOBAL_INTERRUPTS_FOR_CAN_HANDLER */



 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

