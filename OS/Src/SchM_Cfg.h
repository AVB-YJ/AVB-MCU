/*==========================================================================*\
*==========================================================================*\
 *--------------------------------------------------------------------
 * Module Name:     SchM_Cfg.h
 * Created By:      SIL
 * Created Date:    22nd Mar 2011
 * %version:        1 %
 * %cvtype:         incl %
 * %instance:       ctc_aud_2 %
 * %derived_by:     lzs7ws %
 * %date_modified:  %
 *--------------------------------------------------------------------
 *
 * Description:
 *   
 * This file contains the header declarations of Stack_Ck configuration module
 *
 * Traces to: 10024438_SW_SDD_00001570
 *
 *
 * Applicable Standards (in order of precedence: highest first):
 *  coding standards followed where ever necessary.
 * For Datatypes followed Autosar standard    
 *
 * 
 *
 \*============================================================================*/

/*-------------------------------------------------------------------
 * to avoid multiple definition if the file is included several times
 *-------------------------------------------------------------------*/
#ifndef SCHM_CFG_H
#define SCHM_CFG_H

#include "SchM_Types.h"

#define ROBST_OS_FIFO_ENABLE
/* to enable the stack checking in idle task */
#define ROBST_STACK_CK_ENABLE
/* to enable the CAN checking in idle task */
#define ROBST_CAN_CK_ENABLE
/* to enable the port refreshing in idle task */
#define ROBST_PORT_DIR_ENABLE
/* to enable the LVD configuration checking in idle task */
#define ROBST_LVD_CK_ENABLE
/* to enable the ICC configuration checking in idle task */
#define ROBST_ICC_RFSH_ENABLE
/* to enable the ADC configuration checking in idle task */
#define ROBST_ADC_RFSH_ENABLE
/* to enable the PWM configuration checking in idle task */
#define ROBST_PWM_RFSH_ENABLE

/* the Sys clock is 24 MHz and prescaler used is 4. With this the GPT Channel 6
will be able to measure 65536 * 2/3 = 43.69 ms. Since the Accuracy required for the Loop timeout is less, the one complete cycle of free running counter is 
assumed to be 43 ms 
*/
#define SCHM_SYS_CLOCK_RANGE  43
/* give the timeout required in ms for the loop */
#define NVM_STARTUP_EEL_HANDLER_LOOP_TIMEOUT_IN_MS   (uint16_t)1000

/* this will give a count which will generate the timeout for 1004.87 ms */
#define NVM_STARTUP_EEL_HANDLER_LOOP_TIMEOUT_COUNT   (uint8_t)(NVM_STARTUP_EEL_HANDLER_LOOP_TIMEOUT_IN_MS/SCHM_SYS_CLOCK_RANGE)

/* the boundary conditions are not taken care. So the reference time count is
set to 0x8000. Due to this the timeout will be having a tolerance of +/-21.845ms
*/
#define SCHM_LOOP_CONST_REF_TIME (uint16_t)32768

#define SCHM_TIME_OUT_INIT {0,0,{NVM_STARTUP_EEL_HANDLER_LOOP_TIMEOUT_COUNT},0,0,0}


#define SchM_ADHS_ADCE_MASK        (uint8_t)0x07 

#define SchM_ADC_CLOCK_ENABLE_INIT (uint8_t)1 
#define SchM_ADC_ADCE_ENABLE       (uint8_t)1
#define SchM_ADC_ADHS_ADCE_INIT    (uint8_t)0x05
#define SchM_ADC_ADS_INIT          (uint8_t)0x01
#define SchM_ADC_ADPC_INIT         (uint8_t)0x02

/*
 * bit 0    = MDmn0         = 1   -> generate INTTM when start counting
 * bit 3-1  = MDmn3-MDmn0   = 000 -> channel works in interval mode
 * bit 5-4  = reserved      = 00
 * bit 7-6  = CISmn7-CIDmn6 = 00  -> sets to 00 because TImn input is not used
 * bit 10-8 = STSmn2-STSmn0 = 000 -> master is allways triggered by software
 * bit 11   = MASTERmn      = 1   -> channel is set as master
 * bit 12   = CCSmn         = 0   -> channel works on clock specified by CKS bits
 * bit 13   = reserved      = 0
 * bit 15-14= CKSmn1-CKSmn0 =     -> select clock, the value is taken from configuration structure
*/
#define SchM_PWM_MSTR_CONFIG_INIT   (uint16_t)0x0801

/*
 * bit 0    = MDmn0         = 1   -> trigger input is valid
 * bit 3-1  = MDmn3-MDmn0   = 100 -> channel works in one count mode
 * bit 5-4  = reserved      = 00
 * bit 7-6  = CISmn7-CIDmn6 = 00  -> sets to 00 because TImn input is not used
 * bit 10-8 = STSmn2-STSmn0 = 100 -> master is allways triggered by INTM of the master channel
 * bit 11   = MASTERmn      = 0   -> channel is set as slave
 * bit 12   = CCSmn         = 0   -> channel works on clock specified by CKS bits
 * bit 13   = reserved      = 0
 * bit 15-14= CKSmn1-CKSmn0 =     -> select clock, the value is taken from configuration structure
*/
#define SchM_PWM_SLAVE_CONFIG_INIT  (uint16_t)0x0409
#define SchM_PWM_PERIOD_CH01        (uint16_t)0x01ad
#define SchM_PWM_PERIOD_CH05        (uint16_t)0x1d4c
#define SchM_PWM_PERIOD_CH21        (uint16_t)0x53B5
#define SchM_PWM_OP_MODE_REG_CH0    (uint8_t)0x002E
#define SchM_PWM_OP_MODE_REG_CH2    (uint8_t)0x0002
#define SchM_PWM_OP_LEVEL_REG_CH0   (uint8_t)0x0008
#define SchM_PWM_OP_LEVEL_REG_CH2   (uint8_t)0
#define SchM_PWM_OP_EN_REG_CH0      (uint8_t)0x002e
#define SchM_PWM_OP_EN_REG_CH2      (uint8_t)0x0002


#define ADC_ADM0_RESET_VAL   ((uint8)0x00)

#define ADC_BIT_OFFSET_1     ((uint8)1)  
#define ADC_BIT_OFFSET_2     ((uint8)2)  
#define ADC_BIT_OFFSET_3     ((uint8)3)  
#define ADC_BIT_OFFSET_4     ((uint8)4)  


#endif /* SCHM_CFG_H */

/****************************************************************************************************************
 *
 * Revision history
 *
 * Date                By                        Change
 * -------------------------------------------------------------------------------------------------------------
 * 05-Apr-2011        JJ     Initial version: for ICP-B78 Program
 *                           for release 10024438_TCI/5.00 ,Task no tci_ik#5073
 * 08-Apr-2011        JJ     Implemented Review comments ID 103572.3469
 ****************************************************************************************************************/

