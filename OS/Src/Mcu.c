/*===========================================================================*
 * Copyright 2011 Technologies, Inc., All Rights Reserved.
 *  Confidential
 *---------------------------------------------------------------------------
 * Module Name:     Mcu
 * %full_filespec: Mcu.c~1:csrc:ctc_aud#6 %
 * %version: 1 %
 * %derived_by: lzs7ws %
 * %date_created: Tue Jun 26 15:37:45 2012 %
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION: 
 * Source File for Small System Architecture of MCU Driver.
 * This file contains the functionality of the public interface
 * of the MCU Driver for SSA.
 *
 *   Applicable Standards (in order of precedence: highest first):
 *     SW REF 264.15D " C Coding Standards" [31-Oct-2010]
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
 *===========================================================================*/

/*============================================================================*\
 * PREPROCESSOR DIRECTIVES
\*============================================================================*/

/* INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------------------*/
#include "uc_registers.h"

/* INCLUDE DIRECTIVES FOR OTHER HEADERS --------------------------------------*/
#include "Mcu.h"
#if(MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/* LOCAL DEFINES OR CONSTANTS -----------------------------------------------*/
#define MCU_DRIVER_INITIALIZED   ((uint8_t)0x35)
#define MCU_DRIVER_UNINITIALIZED   ((uint8_t)0xCA)
/* @} */

/* LOCAL DEFINE MACROS (#, ##) -----------------------------------------------*/

/** \details Value used as expiry count needed during oscillation accuracy
 * stabilization time of internal high-speed osc.
 */
#define MCU_INT_HS_STABILIZATION_TIME (20u)

/** \defgroup ResetMasks
 * \name Masks used for reset reason indication
 * @{
 */
#define MCU_POCRES_OR_EXTERNAL_PIN_RESET_MASK ((uint8_t)0x00)
#define MCU_LOW_VOLTAGE_RESET_MASK            ((uint8_t)0x01)
#define MCU_ILLEGAL_ADDRESS_RESET_MASK        ((uint8_t)0x02)
#define MCU_CLOCK_MONITOR_RESET_MASK          ((uint8_t)0x04)
#define MCU_WATCHDOG_RESET_MASK               ((uint8_t)0x10)
#define MCU_ILLEGAL_INSTRUCTION_RESET_MASK    ((uint8_t)0x80)
/* @} */

/** \details Safety counter maximum value. Used in clock stabilization loops
 * to avoid inifnite loops in case of hardware fail.
 */
#define MCU_SAFETY_CNT_MAX ((uint8_t)0xFF)

//safety counter for stabilization loop for OSTC, the experiment time is < 0x500
#define MCU_OSTC_SAFETY_CNT ((uint16)0x0800)  

/** defgroup ResetMasks
 * \name MCU power modes
 * @{
 */


/* @} */


/*============================================================================*\
 * LOCAL TYPEDEF DECLARATIONS
\*============================================================================*/

/* ENUMS ---------------------------------------------------------------------*/

/* STRUCTS -------------------------------------------------------------------*/

/* UNIONS --------------------------------------------------------------------*/

/* OTHER TYPEDEFS ------------------------------------------------------------*/

/*============================================================================*\
 * OBJECT DEFINITIONS
\*============================================================================*/

/* EXPORTED OBJECTS ----------------------------------------------------------*/

/* LOCAL OBJECTS -------------------------------------------------------------*/

#if(MCU_DEV_ERROR_DETECT == STD_ON)
#define MCU_START_SEC_VAR_8BIT
#include "MemMap.h"

/** Variable contains mcu driver state */
_STATIC_ VAR(uint8_t, MCU_VAR) Mcu_InitState = MCU_DRIVER_UNINITIALIZED;

#define MCU_STOP_SEC_VAR_8BIT
#include "MemMap.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#define MCU_START_SEC_VAR_8BIT
#include "MemMap.h"

/** \details Index of actual clock */
static uint8_t Mcu_CurrClockIdx;

#define MCU_STOP_SEC_VAR_8BIT
#include "MemMap.h"

/*============================================================================*\
 * LOCAL FUNCTION PROTOTYPES
\*============================================================================*/

static void Mcu_SetCPUClock(const Mcu_ClockConfigurationType* pCurrClock);

/*============================================================================*\
 * LOCAL FUNCTION-LIKE-MACROS and INLINE FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * LOCAL FUNCTIONS
\*============================================================================*/

/*============================================================================*\
 * EXPORTED FUNCTIONS
\*============================================================================*/

#define MCU_START_SEC_CODE
#include "MemMap.h"

/* For detailed explanation on the exported functions see Mcu.h file. */
void Mcu_Init(const Mcu_ConfigType * ConfigPtr)
{
   /* If the MCU_DEV_ERROR_DETECT switch is enabled API parameter
      checking is enabled. */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
   if(NULL_PTR != ConfigPtr)
   {
      Mcu_InitState = MCU_DRIVER_UNINITIALIZED;
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_MCU_INIT,
                        MCU_E_PARAM_CONFIG);
   }
   else
#endif /* (STD_ON == MCU_DEV_ERROR_DETECT) */
   {
      /* Set one-time writable register */
         /* Internal HS -osc -> X1 */
      CMC = MCU_CMC_REG_VALUE;
      /* Set/clear all unused bits of all used registers */
      MCU_CLEAR_UNUSED_BITS_CSC();
      MCU_SET_UNUSED_BITS_CKC();

//timer defined in cg_timer
#if 0
      /* Inialize TAUs */
#if (GPT_TAU0_USED == STD_ON)
      /* Supply input clock */
      PER0_bit.no0 = 1;
      /* Init prescalers */
      TPS0 = MCU_TPS0_VALUE;
#endif
#if (GPT_TAU1_USED == STD_ON)
      /* Supply input clock */
      PER0_bit.no1 = 1;
      /* Init prescalers */
      TPS1 = MCU_TPS1_VALUE;
#endif
#if (GPT_TAU2_USED == STD_ON)
      /* Supply input clock */
      PER0_bit.no2 = 1;
      /* Init prescalers */
      TPS2 = MCU_TPS2_VALUE;
#endif
#endif

   /* Set default clock index as 0 */
   Mcu_CurrClockIdx = (uint8_t)0;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
      Mcu_InitState = MCU_DRIVER_INITIALIZED;
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
   }
}

/*============================================================================*\
 * FUNCTION: Mcu_InitClock
\*============================================================================*/
/* For detailed explanation on the exported functions see Mcu.h file. */
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
   Std_ReturnType ret_val;
   uint8_t iter;
   uint8_t safety_cnt;
   const Mcu_ClockConfigurationType* pCurrClock;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
   if(MCU_DRIVER_INITIALIZED != Mcu_InitState)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_MCU_INIT_CLOCK,
                        MCU_E_UNINIT);
   }
   else if (ClockSetting>=MCU_CLOCKS_NO)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_MCU_INIT_CLOCK,
                        MCU_E_PARAM_CLOCK);
   }
   else
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
   {
      /* Select appropriate clock configuration */
      pCurrClock = &Mcu_ClocksConfiguration[ClockSetting];
      /* Update current clock index */
      Mcu_CurrClockIdx = ClockSetting;

      /* Configure CPU/peripheral clk  */
      Mcu_SetCPUClock(pCurrClock);

      /* Configure remaining clocks    */
      //1  X1/external clock (not used)
      if (MCU_HIGH_SPEED_X1_EXCLK != pCurrClock->cpu_periph_clock)
      {
         /* Set guard bit */
         GDCSC = 1;

         /* Set OSTS register */
         OSTS = pCurrClock->osts_reg;

         /* If X1/EXT_CLK to be runned */
         if (!pCurrClock->mstop_bit)
         {
            /* In case of X1 stopped */
            if (MSTOP)
            {
                /* Enable X1 */
               MSTOP = 0;

               /* Set stabilization loop period */
               iter = pCurrClock->ostc_reg;

               /* Set safety counter */
               safety_cnt = (uint8_t)MCU_SAFETY_CNT_MAX;

               /* Wait clock-stabilization time */
               while ((OSTC < iter) && safety_cnt)
               {
                  __no_operation();
                  safety_cnt--;
               }
            }
         }
         /* If X1 to be stopped */
         else
         {
            /* Prevent stopping internal high-speed oscillator while set as CPU/periph clock (shall never occur in this case) */
            /* CPU: iFL  ||  iHS   */
            #ifndef QAC
            if (CLS || !MCS)
            {
               MSTOP = 1;
            }
            #endif
         }

         /* Clear guard bit */
         GDCSC = 0;
      }

      //2 disable Internal high-speed 
      if (MCU_INTERNAL_HIGH_SPEED != pCurrClock->cpu_periph_clock)
      {
         /* Set guard bit */
         GDCSC = 1;
         /* internal high-speed to be stopped */
         if (pCurrClock->hiostop_bit)
         {
            /* Prevent stopping internal high-speed oscillator while set as CPU/periph clock (shall never occur in this case) */
            /* CPU:   iFL     ||  PLL   */
            if(CLS || MCS)
            {
               HIOSTOP = 1;
            }
         }
         else
         {
            /* Enable internal high-speed oscillatior in case of stopped */
            if (HIOSTOP)
            {
               HIOSTOP = 0;
            }
         }
         /* Clear guard bit */
         GDCSC = 0;
      }
      ret_val = E_OK;
   }
   return ret_val;
}


/* Function for CPU/peripheral clock changing */
static void Mcu_SetCPUClock(const Mcu_ClockConfigurationType* pCurrClock)
{
   uint8_t iter;
   uint16_t safety_cnt;

   switch(pCurrClock->cpu_periph_clock)
   {
      case MCU_HIGH_SPEED_X1_EXCLK:
      {
         /* Set OSTS register before starting clock */
         //This register is used to select the X1 clock oscillation stabilization 
         //wait time when the STOP mode is released.
         OSTS = pCurrClock->osts_reg;
         /* Set GDPLL & GDCSC guard bits for CSC & PLLCTL writing */
         GDPLL = 1;
         GDCSC = 1;
         /* Enable X1 */
         MSTOP = 0;

         /* Set stabilization loop period */
         iter = pCurrClock->ostc_reg;
         /* Set safety counter for stabilization loop */
         safety_cnt = MCU_OSTC_SAFETY_CNT;
         /* Wait clock-stabilization time */
         while ((OSTC < iter) && safety_cnt)
         {
            __no_operation();
            safety_cnt--;
         }
         /* Clear PLLON in order to allow MCM0 writing */
         PLLON = 0;//The PLL clock starts oscillating by setting PLLON to 1.
         /* Clear CSS in order to allow MCM0 writing */
         CSS = 0;
         /* Select external HS system clock by setting MCM0 bit */
         MCM0 = 1;

         /* Clear guard bits */
         GDPLL = 0;
         GDCSC = 0;
         break;
      }
      case MCU_INTERNAL_LOW_SPEED:
      {
         /* Make internal low-speed oscillator CPU/peripheral clock*/
         CSS = 1;
         break;
      }
      case MCU_INTERNAL_HIGH_SPEED:
      {
         /* Set GDPLL & GDCSC guard bits for CSC & PLLCTL writing */
         GDPLL = 1;
         GDCSC = 1;
         /* Enable internal high-speed oscillator */
         HIOSTOP = 0;
         /* Oscillation accuracy stabil. time */
         for (iter=0; iter<MCU_INT_HS_STABILIZATION_TIME; iter++)
         {
            __no_operation();
         }
         /* Clear PLLON for MCM0 clearing */
         PLLON = 0;
         /* Clear CSS for MCM0 writing */
         CSS = 0;
         /* Clear MCM0 - internal high-speed osc. as a main system clock) */
         MCM0 = 0;
         /* Clear guard bits */
         GDPLL = 0;
         GDCSC = 0;
         break;
      }
      default: break;
   }

   //1 configure PLL if used 
   if (MCU_PLL_USED == pCurrClock->pll_used)
   {
       /* Set GUARD register */
      GDPLL = 1;

      /* Set PLLDIVx bits */
      PLLCTL_bit.no4 = MCU_PLL_DIV0;
      PLLCTL_bit.no5 = MCU_PLL_DIV1;

      /* Setup PLL divider */
      CKC &= (uint8_t)0xF8;
      if (pCurrClock->mdiv_bits)
      {
         CKC |= (uint8_t)pCurrClock->mdiv_bits;
      }

      /* Enable PLL */
      PLLON = 1;

      /* Set safety counter */
      safety_cnt = MCU_SAFETY_CNT_MAX;

      /* Wait until PLL lock time expires */
      while ((!LOCK) && safety_cnt)
      {
         __no_operation();
         safety_cnt--;
      }
      /* Enable PLL in the output clock */
      SELPLL = 1;

      /* Set safety counter */
      safety_cnt = MCU_SAFETY_CNT_MAX;
      /* Confirm that PLL is enabled */
      while ((!SELPLLS) && safety_cnt)
      {
         __no_operation();
         safety_cnt--;
      }

      /* Clear GUARD register */
      GDPLL = 0;
   }
}


/* For detailed explanation on the exported functions see Mcu.h file. */
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
   Std_ReturnType ret_value = E_NOT_OK;
   uint8_t data_idx;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
   if(MCU_DRIVER_INITIALIZED != Mcu_InitState)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_MCU_INIT_RAM_SECTION,
                        MCU_E_UNINIT);
   }
   else if (RamSection>=MCU_RAM_SECTORS)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_MCU_INIT_RAM_SECTION,
                        MCU_E_PARAM_RAMSECTION);
   }
   else
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
   {
      for (data_idx=0; data_idx<Mcu_RamSectionsData[RamSection].size; data_idx++)
      {
         /* Fill RAM section with default data */
         Mcu_RamSectionsData[RamSection].base_addr[data_idx] =
            Mcu_RamSectionsData[RamSection].default_val;
      }

      ret_value = E_OK;
   }

   return ret_value;
}

/* For detailed explanation on the exported functions see Mcu.h file. */
/* For detailed explanation on the exported functions see Mcu.h file. */
void Mcu_DistributePllClock(void)
{
   uint8_t safety_cnt;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
   if(MCU_DRIVER_INITIALIZED != Mcu_InitState)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_DISTRIBUTE_PLL_CLOCK,
                        MCU_E_UNINIT);
   }
   else if(0 == LOCK)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_DISTRIBUTE_PLL_CLOCK,
                        MCU_E_PARAM_PLL_NOT_LOCKED);
   }
   else
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
   {
      /* Disable guard */
      GDPLL = 1;
      /* Set clock mode through PLL */
      SELPLL = 1;

      /* Set safety counter */
      safety_cnt = MCU_SAFETY_CNT_MAX;

      /* Wait until PLL is switched ON */
      while ((1 != SELPLLS) && safety_cnt)
      {
         __no_operation();
         safety_cnt--;
      }
      /* Enable guard */
      GDPLL = 0;
   }
}

/* For detailed explanation on the exported functions see Mcu.h file. */
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
   Mcu_PllStatusType ret_val = MCU_PLL_STATUS_UNDEFINED;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
   if(MCU_DRIVER_INITIALIZED != Mcu_InitState)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_GET_PLL_STATUS,
                        MCU_E_UNINIT);
   }
   else
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
   {
      if(0 == LOCK)
      {
         ret_val=MCU_PLL_UNLOCKED;
      }
      else
      {
         ret_val=MCU_PLL_LOCKED;
      }
   }
   return ret_val;
}

/* For detailed explanation on the exported functions see Mcu.h file. */
Mcu_ResetType Mcu_GetResetReason(void)
{
   Mcu_ResetType ret_value;
   Mcu_RawResetType reset_value = Mcu_GetResetRawValue();   /* Reading RESF sets RESF to 00H. */

   switch (reset_value)
   {
      case(MCU_POCRES_OR_EXTERNAL_PIN_RESET_MASK):
      {
         if ( POCRES_bit.no0 == 0 )
         {
            POCRES_bit.no0 = 1;                 /* POCRES - POC reset register */
            ret_value = MCU_POWER_ON_RESET;     /* Power-on clear circuit reset signal */
         }
         else
         {
            ret_value = MCU_EXTERNAL_PIN_RESET; /* External reset input via ~RESET pin */
         }
         break;
      }
      case(MCU_LOW_VOLTAGE_RESET_MASK):
      {
         ret_value = MCU_LOW_VOLTAGE_RESET;
         break;
      }
      case(MCU_ILLEGAL_ADDRESS_RESET_MASK):
      {
         ret_value = MCU_ILLEGAL_ADDRESS_RESET;
         break;
      }
      case(MCU_CLOCK_MONITOR_RESET_MASK):
      {
         ret_value = MCU_CLOCK_MONITOR_RESET;
         break;
      }
      case(MCU_WATCHDOG_RESET_MASK):
      {
         ret_value = MCU_WATCHDOG_RESET;
         break;
      }
      case(MCU_ILLEGAL_INSTRUCTION_RESET_MASK):
      {
         ret_value = MCU_ILLEGAL_INSTRUCTION_RESET;
         break;
      }
      default:
      {
         ret_value = MCU_RESET_UNDEFINED;
         break;
      }
   }
   return ret_value;
}

/*============================================================================*\
 * FUNCTION: Mcu_GetResetRawValue
 *
 * For detailed explanation on the exported functions see Mcu.h file.
\*============================================================================*/
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
   static Mcu_RawResetType ret_value = 0xFF;

   if (ret_value == 0xFF)
   {
      ret_value = RESF;               /* Reading RESF sets RESF to 00H. */
   }

   return ret_value;
}


/* For detailed explanation on the exported functions see Mcu.h file. */
#if (MCU_PERFORM_RESET_API == STD_ON)
void Mcu_PerformReset(void)
{
#if defined(MCU_WDG_PERFORM_RESET)
    /* Internal reset triggered by watchdog timer reset */
    WDTE = (uint8_t)0x00;
#elif defined(MCU_ILLEGAL_INSTR)
    /* Perform reset via executing illegal instruction */
    asm("DS8 0xff");
#endif
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */
/* For detailed explanation on the exported functions see Mcu.h file. */
void Mcu_SetMode(Mcu_ModeType McuMode)
{
#if (MCU_DEV_ERROR_DETECT == STD_ON)
   if(MCU_DRIVER_INITIALIZED != Mcu_InitState)
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_SET_MODE,
                        MCU_E_UNINIT);
   }
   else if ((MCU_MODE_HALT != McuMode) && (MCU_MODE_STOP != McuMode) && (MCU_MODE_RUN != McuMode))
   {
      Det_ReportError(  MCU_MODULE_ID,
                        MCU_INSTANCE_ID,
                        MCU_API_ID_SET_MODE,
                        MCU_E_PARAM_MODE);
   }
   else
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */
   {
      if (MCU_MODE_HALT == McuMode)
      {
         __enable_interrupt();
         __halt();
      }
      else if (MCU_MODE_STOP == McuMode)
      {
         /* In case of X1 is CPU/peripheral clock, set OSTS register */
         #ifndef QAC
         if (!MSTOP && !CLS && MCS)
         #endif   
         {
            OSTS = Mcu_ClocksConfiguration[Mcu_CurrClockIdx].osts_reg;
         }
         __enable_interrupt();
         __stop();
      }
      else
      {
      }
   }
}

#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/* END OF FILE -------------------------------------------------------------- */

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------

 * 02-May-2011   Wade Li
 * + Created initial file
 *   -reused from Corvette project which Copied from 10024438_ICP_B78_TCI~10024438_TCI_4_01:project:tci_ik#1
 *
\*===========================================================================*/

/* END OF FILE -------------------------------------------------------------- */

