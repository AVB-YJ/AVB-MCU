/*******************************************************************************
*--------------------------------------------------------------------
* Module Name:     Application power mode
* Created By:      wade.li
* Created Date:    04/07/2011
* %version:        35.1.12 %
* %cvtype:         csrc %
* %instance:       ctc_aud_1 %
* %derived_by:     rzlw3b %
* date_created:  Tue Apirl 7 13:02:04 2011 %
*--------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description   : power moding control 
 *                   
 *                  Management services following :
 *  \li             Battery voltage detect \n
 *  \li             Power up sequence \n
 *  \li             Power down sequence \n
 *            
 *-----------------------------------------------------------------------------*/

/*============================================================================*\
 *              --- Included files and compilation variables ---
\*============================================================================*/

#include "App_PowerMode.h"
#include "WdgM.h"
#include "Port.h"
#include "Dio.h"
#include "Adc.h"
#include "OS_Task.h"
#include "OS_Timer.h"
#include "TIMER.h"
#include "NVM.h"
#include "Mcu.h"
#include "Irq.h"
#include "UART.h"
#include "can_handler.h"

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/
/*
 * Voltage calculation macros for powerfail values
 */
#define DSLR_FREQ_IS  STD_OFF
#define BATT_CALIB_IS STD_ON
#define  APLUS_R1        3400    /* 340.0  kohm   \  voltage            */
#define  APLUS_R2         649      /*  64.9  kohm   /  divider            */
#define  V_REF             5000        /*   3.30 V      -  reference voltage  */
#define  ADC_RANGE        1023      /*   2^10        -  AD converter range */

#ifndef UINT16_MAX
#define  UINT16_MAX      (65535)
#endif
/* recalcultates battery voltage in mV into ADC reading value */
#define CALC_APLUS(x)   ( ( ((((uint32_t)x)*APLUS_R2) / (APLUS_R1 + APLUS_R2)) * ADC_RANGE ) / V_REF)
/* recalculates ADC reading into battery voltage in mV */
/* this macro is transformed to handle calculations on numbers > 16 bit */
#define CALC_BATT(y)    ( ( (((uint32_t)y) * V_REF)/ADC_RANGE ) + ( ((((uint32_t)APLUS_R1 * V_REF)/APLUS_R2) * (y) )/ADC_RANGE ) )

#define IDEAL_14V4     (CALC_APLUS(14400))//0x02CB  /*ideal value for 14.4V measurement*/
//wade.li, according to 10% precision of resistor, re-set the voltage precision, 20100120
#define LOW_14V4       (CALC_APLUS(13392))  /* 14.4 V - 7% = 13.392 V */      
#define HIGH_14V4      (CALC_APLUS(15408))  /* 14.4 V + 7% = 15.408 V */   

#define REFERENCE_VOLTAGE_DEFAULTS       IDEAL_14V4

//the voltage TBD in EEPROM
#if (BATT_CALIB_IS == STD_ON)
#define PS_Reference_Voltage()          (Power_Reference_Voltage)
#else
#define PS_Reference_Voltage()          (IDEAL_14V4)
#endif
#define PS_Cal_Reference_Voltage()    ( ((PS_Reference_Voltage() < LOW_14V4)||(PS_Reference_Voltage() > HIGH_14V4)) ? \
                                         REFERENCE_VOLTAGE_DEFAULTS : PS_Reference_Voltage() )
/*ICS will work normal between 9v-18v, 06/22/2011 by wade
updated the operation voltage range, 20110824
*/
#if 0
#define HIGH_VOLT_SHUTDOWN      16000     /* 16.0 V */         
#define HIGH_VOLT_HYSTERISIS    15500     /* 15.5 V*/         
#define LOW_VOLT_SHUTDOWN        8000     /*  8 V */      
#define LOW_VOLT_HYSTERISIS      9000     /* 9 V */        
#define VERY_LOW_SHUTDOWN        5300     /*  5.3 V */      
#define VERY_LOWT_HYSTERISIS     5800     /* 5.8 V */   
#endif

#define HIGH_VOLT_SHUTDOWN      16000     /* 16.0 V */         
#define HIGH_VOLT_HYSTERISIS    15500     /* 15.5 V*/         
#define LOW_VOLT_SHUTDOWN        5000     /*  8 V */      
#define LOW_VOLT_HYSTERISIS      5300     /* 9 V */        
#define VERY_LOW_SHUTDOWN        4300     /*  5.3 V */      
#define VERY_LOWT_HYSTERISIS     4800     /* 5.8 V */   

#define BATT_RECOVER_DEBOUNCE    5//  2
#define MAX_RETRY_TIMES 3
#define PWR_DSLR_ADDRESS  0x10
#define PS_POWERFAIL_DEBOUNCE_COUNT       (9)    /* number of measurement cycles for debounce */

#define PWR_IIC_DATA_LEN 2


/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/
/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*! \enum ICS model types
 * List of different types
 */
enum
{
   PWR_AUDIO_HIGH,
   PWR_AUDIO_LOW,
   PWR_HVAC_SZM,
   PWR_HVAC_SZA,
   PWR_HVAC_DZA,   
   PWR_MODEL_MAX
};

/*===========================================================================*\
 * Exported Const Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/
volatile static PWR_MANAGE_STATUS_t Power_Manager_Stat;
volatile static PWR_MANAGE_STATUS_t Batt_Manager_Stat;
static uint16_t Power_Reference_Voltage;
//static uint16_t Power_sleep_for_timeout;



/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/
static void Power_adjust_ADC(uint16_t *adc);
static uint16 Power_Read_Batt_Volt(void);
//static void Power_Supply_Start(void);
static void Power_Get_Batt_Calibration_Value(void);



/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Function Definitions
\*===========================================================================*/


/*===========================================================================*/
/*!
 * This function initializes the power state.\n
 *
 * <b>Actions:</b>
 * \li initiate power state
 * \li initiate battery state                               
 */
/*===========================================================================*/
void App_PowerMode_Init(void)
{
    Power_Manager_Stat = PWR_MANAGE_IDLE;
    Batt_Manager_Stat = PWR_MANAGE_UNDER_VOLTAGE;

}
/*===========================================================================*/
/*!
 * This function active the power task.\n
 *
 * <b>Actions:</b>
 * \li get the battery info
 * \li active the power task                               
 */
/*===========================================================================*/
void App_PowerMode_Start(void)
{  
   //get the BATT info
   Power_Get_Batt_Calibration_Value();

   (void)OS_ActivateTask(OS_Task_PMode, OS_Task_PMode_Offset, OS_Task_PMode_Period);  /* start periodic task */
}
/*===========================================================================*/
/*!
 * This function execute power down.\n
 *
 * <b>Actions:</b>
 * \li shut down a primary switch
 */
/*===========================================================================*/
void App_PowerMode_Stop(void)
{
 
}
/*===========================================================================*/
/*!
 * This function is the main task of power.\n
 *
 * <b>Actions:</b>
 * \li power up DSLR
 * \li periodically check the battery status
 * \li diag to stop
 */
/*===========================================================================*/
void Power_Task(void)
{

    if(Power_Manager_Stat == PWR_MANAGE_IDLE)
    {
        //Power_Supply_Start();
        //enable the analogy input channel for battery voltage before A/D work, wade.li
        //Port_SetPinDirection(PORT_BATT_VOLT_IN, PORT_PIN_IN);
        Power_Manager_Stat = PWR_MANAGE_NORMAL;
        Batt_Manager_Stat = PWR_MANAGE_UNDER_VOLTAGE;
    }
    //test for wake/sleep
    //Power_Ind_test(Local_Wakeup_Flag);
    /* not use event, since the handler is time sensitive
    if(curr_batt!= pre_batt)
    {
        pre_batt = curr_batt;
        func_msg.MsgId  = OS_MESSAGE_PMD_VOLT_CHANGED;
        func_msg.Param1 = curr_batt;
        OS_PostMessage1(&func_msg);
    }*/
    Power_Powerfail_Check();

}

/*===========================================================================*/
/*!
 * This function enable power supply to all component..\n
 */
/*===========================================================================*/

//static void Power_Supply_Start(void)
//{
    //register address (0x01) + data(data:  0 0 0 0 0 SW2EN LREN HSDEN)
   
//}
/*===========================================================================*\
 * interface for battery voltage manager
\*===========================================================================*/


/*===========================================================================*/
/*!
 *  read the current voltage \n
 *
 *  return: \n 
 *  the value of current batt voltage \n
 *         
 */
/*===========================================================================*/
static uint16 Power_Read_Batt_Volt(void)
{
    Adc_StatusType AdcStatus;
    //static   uint16_t aplus_voltage;
    //static   uint16_t current_voltage; 
    uint16_t*   real_battery; 
    #if 0
ADCEN = 1;			/* supplies input clock to A/D converter */

	ADCE = 1;			/* enables comparator operation */

	ADPC = 0x01;		/* A/D port configuration
					   analog input: ANI14/P156, ANI15/P157
					   digital input: ANI0/P20-ANI13/P155 */

	/**************************************************
	 port initial setting */
	PM8 = 0x01;		/* ANI15/P157 & ANI14/P156: input mode */

	/**************************************************
	 A/D conversion mode register */
	ADM0 = 0x01;		/* ADCS=0: stops conversion operation
					   FR2=FR1=FR0=LV1=LV0=0: conversion time = 264/fCLK @20MHz
					   ADCE=1: enables comparator operation */

	ADS = 0x0;			/* analog input channel: ANI14/P156 */

	ADCS = 1;			/* enables conversion operation */

	ADIF = 0;			/* clear interrupt request flag of INTAD */

	while(ADIF == 0);		/* wait until A/D conversion completes */

	aplus_voltage = ADCR;		/* get A/D conversion result (16-bit with lower 6-bit '0') */
	aplus_voltage =  aplus_voltage>>6;
	#endif
	
    Adc_StartGroupConversion(ADC_VOLT_DET_VOLTAGE);
    do
    {
        AdcStatus = Adc_GetGroupStatus(ADC_VOLT_DET_VOLTAGE);
    }
    while (ADC_BUSY == AdcStatus);
    #if 0
    volt1 =0;
    volt2 = Adc_ValueReadGroup(ADC_VOLT_DET_VOLTAGE);
    
    volt1 = (*volt2)*33/0x3FF ;
    volt1 = (volt1*623);
    #else
    real_battery = Adc_ValueReadGroup(ADC_VOLT_DET_VOLTAGE);

    #endif
    /* Adjust read voltage AD value */
    //Power_adjust_ADC(&aplus_voltage);		
    //real_battery  =  CALC_BATT(aplus_voltage);  //only for debuging
    //current_voltage = *real_battery;
    return (*real_battery);
}

/*===========================================================================*/
/*!
 *  return current status: \n
 *
 *  return: \n 
 *    true: power state is ok \n
 *    false: cranking or battery abnormal     
 */
/*===========================================================================*/
extern boolean Power_Check_Battery_Status(void)
{
   return ((boolean)((Power_Manager_Stat == PWR_MANAGE_NORMAL)&&(Batt_Manager_Stat == PWR_MANAGE_NORMAL)));
}

/*===========================================================================*/
/*!
 *  API: current batt status: \n
 *
 *  return type PWR_MANAGE_STATUS_t     
 */
/*===========================================================================*/
extern PWR_MANAGE_STATUS_t Power_Get_Power_Status(void)
{
   return (Batt_Manager_Stat);
}


/*===========================================================================*/
/*!
* Description: Power_Powerfail_Check \n
*    It will be called by RTI_Tick(). This function checks the voltage level of 
*    AIN0 (used for measurement of the battery voltage) and checks also the powerfail 
*    counter. If a powerfail happened, a message will be send to the psync task.  \n
*                                 \n
*    0-----------------9.0 ---------14.0 ------------18.0-------+   \n
*                      |                         |                  \n
*                      |                         |                  \n
*           low                    normal                 abnormal  
*/
/*===========================================================================*/
static void Power_Powerfail_Check(void)
{
     //uint16_t real_battery; 
     uint16_t aplus_voltage;
     static int8_t power_fail_check_debounce =  PS_POWERFAIL_DEBOUNCE_COUNT;
     
     if(PWR_MANAGE_NORMAL > Batt_Manager_Stat)
     {
       // return; //error, return
     }
     aplus_voltage = Power_Read_Batt_Volt();
     #if (BATT_CALIB_IS == STD_ON)
     /* Adjust read voltage AD value */
     Power_adjust_ADC(&aplus_voltage);		
     #endif
     //real_battery  = CALC_BATT(aplus_voltage);  //only for debuging
     //real_battery++;

     switch(Batt_Manager_Stat)
     {
        case PWR_MANAGE_NORMAL:   /*if power is in normal status*/
	          if(aplus_voltage < CALC_APLUS(LOW_VOLT_SHUTDOWN)) /* < 8.5V*/
	          {
		        power_fail_check_debounce -= 3; /*go quickly to LEVEL 2*/
    			if(power_fail_check_debounce <= 0)
    			{
    			    Batt_Manager_Stat = PWR_MANAGE_UNDER_VOLTAGE;
    			    power_fail_check_debounce = PS_POWERFAIL_DEBOUNCE_COUNT;
    			}
	          }
		      else if(aplus_voltage > CALC_APLUS(HIGH_VOLT_SHUTDOWN))  /*>18.0V*/
		      {
		          power_fail_check_debounce-=3;
			      if(power_fail_check_debounce <= 0)
			      {
			          Batt_Manager_Stat = PWR_MANAGE_OVER_VOLTAGE;
			          power_fail_check_debounce = PS_POWERFAIL_DEBOUNCE_COUNT;
			      }
		      }
       		  else  /*still in normal status*/
		      {
		          if(power_fail_check_debounce < PS_POWERFAIL_DEBOUNCE_COUNT)
		          {
				      power_fail_check_debounce += 3;
		          }
		      }
	    break;
	    case PWR_MANAGE_UNDER_VOLTAGE:
	          if(aplus_voltage > CALC_APLUS(LOW_VOLT_HYSTERISIS)) /*>9.5V*/
		      {
		          power_fail_check_debounce-=3;
			      if(power_fail_check_debounce <= 0)
			      {
			          Batt_Manager_Stat = PWR_MANAGE_NORMAL;  /*go back normal status*/
			          power_fail_check_debounce = PS_POWERFAIL_DEBOUNCE_COUNT;
			      }
		      }
              else if(aplus_voltage < CALC_APLUS(VERY_LOW_SHUTDOWN)) /*<6.0V*/
              {
		          power_fail_check_debounce-=3;
			      if(power_fail_check_debounce <= 0)
			      {
			          Batt_Manager_Stat = PWR_MANAGE_RESET;  /*go back normal status*/
			          power_fail_check_debounce = PS_POWERFAIL_DEBOUNCE_COUNT;
			      }
              }
		      else  /*still in LEVEL1  status*/
		      {
		          if(power_fail_check_debounce < PS_POWERFAIL_DEBOUNCE_COUNT)
		          {
				      power_fail_check_debounce += 3;
		          }
		      }	
	    break;	  
        //wade add this state for the cases: when battery fall quickly to low (<6.0V) and quick up, at this time,
        //the MCU power supply is not reset, so need reset system to re-power up all other components.
        case PWR_MANAGE_RESET:
	          if(aplus_voltage > CALC_APLUS(VERY_LOWT_HYSTERISIS)) /*>7.0V*/
		      {
		          power_fail_check_debounce-=3;
			      if(power_fail_check_debounce <= 0)
			      {
			          power_fail_check_debounce = PS_POWERFAIL_DEBOUNCE_COUNT;
                      //reset
                      //Mcu_PerformReset();/*no reset, Oct19, 2012, Todd*/
			      }
		      }
		      else  /*still in LEVEL1  status*/
		      {
		          if(power_fail_check_debounce < PS_POWERFAIL_DEBOUNCE_COUNT)
		          {
				      power_fail_check_debounce += 3;
		          }
		      }	
        break;
	    case PWR_MANAGE_OVER_VOLTAGE: 
              if(aplus_voltage < CALC_APLUS(HIGH_VOLT_HYSTERISIS)) /*<17.5V*/
		      {
		          power_fail_check_debounce-=3;
			      if(power_fail_check_debounce <= 0)
			      {
			          Batt_Manager_Stat = PWR_MANAGE_NORMAL;  /*go back normal status*/
			          power_fail_check_debounce = PS_POWERFAIL_DEBOUNCE_COUNT;
			      }
		      }
  		      else  /*still in LEVEL2  status*/
  		      {
  		          if(power_fail_check_debounce < PS_POWERFAIL_DEBOUNCE_COUNT)
  		          {
  				      power_fail_check_debounce += 2;
  		          }
  		      }	
	    break;	 
	   default:
	    break;
    }
}

 /*===========================================================================*/
/*!
 * Description: This function adjusts voltage read by ADC according 
 *              to reference value stored in EEPROM during manufacture 
 *              process and ideal 14 V measurement.   \n
 *
 *              Idea behind this is: \n
 *              - during manufacture process, unit is supplied with 14V
 *                and ADC value for this measurement is stored
 *                in eeprom as reference value  \n
 *              - ideal value for 14 V measurement is stored in ROM  \n
 *              - relation of ideal and reference voltage gives     
 *                factor for adjusting voltage measurements      \n
 *
 *              Adjustment equation:  \n
 *    \n
 *                                                IDEAL_VOLT  \n
 *              ADJ_ADC = MEAS_ADC * ----------               \n
 *                                                 REF_VOLT   \n
*/
/*===========================================================================*/
static void Power_adjust_ADC(uint16_t *adc)
{
   uint16_t reference_voltage = PS_Cal_Reference_Voltage();
   uint32_t temp_value;

   temp_value = (uint32_t)*adc * IDEAL_14V4;
   temp_value /= reference_voltage;

   if(ADC_RANGE < temp_value)
   {
      *adc = ADC_RANGE;
   }
   else
   {
      *adc = (uint16_t)temp_value;
   }
}
/*===========================================================================*/
/*!
 *  battery change handler
 *
 */
/*===========================================================================*/
void Power_Batt_ChangeEventHandler(OS_MsgParamType1 event1)
{
    __no_operation();
}

/*===========================================================================*/
/*!
*. Description:get the BATT calibration value from EEPROM
 *
 */
/*===========================================================================*/
static void Power_Get_Batt_Calibration_Value(void)
{
#if 0
   //get the calibration value from EEPROM
   if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_SECTOR_BLK1_ID, 0, (uint8_t*)&Power_Reference_Voltage, sizeof(Power_Reference_Voltage)))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
   else
   {
       Power_Reference_Voltage = IDEAL_14V4;
   }
#endif
   
   //keep the test code for further change EERPROM verify
#if 0
   //test code
       memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
       //TBD: get the calibration value from EEPROM
       if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_RESET_BLK_ID9, Power_Reserved_space, 4))
       {
          //Sys_Get_Model_Info = TRUE;
          //nothing to do
          __no_operation();
       }   //test code
      memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
       //TBD: get the calibration value from EEPROM
       if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_RESET_BLK_ID1, Power_Reserved_space, 4))
       {
          //Sys_Get_Model_Info = TRUE;
          //nothing to do
          __no_operation();
       }   //test code
   memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
   //TBD: get the calibration value from EEPROM
   if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_DTC1, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
   //test code
   memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
   //TBD: get the calibration value from EEPROM
   if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_CAL_CHKSUM, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
   memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
   if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_DIM_CAL, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
   memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
      if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_TSC_DATA_BLK_ID, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
   memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
         if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_CONFIG_BATT_BLK_ID, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
   memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
         if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_CONFIG_PN_BLK_ID, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
            memset(Power_Reserved_space, 0xFF, sizeof(Power_Reserved_space));
         if(NVM_MEM_JOB_OK == NVM_Direct_Read2(NVM_CONFIG_BLK_ID, Power_Reserved_space, 4))
   {
      //Sys_Get_Model_Info = TRUE;
      //nothing to do
      __no_operation();
   }
#endif  
}
/*===========================================================================*/
/*!
*. Description: judge if the power down trigger or not
 *
 */
/*===========================================================================*/
void Configure_CAN_Transcvr_Wakeup(void)
{
#if 0
   Dio_WriteChannel(DIO_PIN_P51, STD_LOW);//CAN EN
   Dio_WriteChannel(DIO_PIN_P52, STD_HIGH);//CAN_STB#
   OS_Wait(70);
 #endif
   Dio_WriteChannel(DIO_PIN_P86, STD_LOW);//CAN EN
   Dio_WriteChannel(DIO_PIN_P52, STD_HIGH);//CAN_STB#
   OS_Wait(70);
   
}

void Configure_CAN_Transcvr_Normal(void)
{
#if 0
  Dio_WriteChannel(DIO_PIN_P51, STD_HIGH);//CAN EN
  Dio_WriteChannel(DIO_PIN_P52, STD_HIGH);//CAN_STB#

  Dio_WriteChannel(DIO_PIN_P12, STD_HIGH);//CAN_WAKE
  OS_Delay(200);
  Dio_WriteChannel(DIO_PIN_P12, STD_LOW);//CAN_WAKE
#endif
  
  Dio_WriteChannel(DIO_PIN_P86, STD_HIGH);//CAN EN
  Dio_WriteChannel(DIO_PIN_P52, STD_HIGH);//CAN_STB#

  //Dio_WriteChannel(DIO_PIN_P12, STD_HIGH);//CAN_WAKE
  OS_Delay(200);
  //Dio_WriteChannel(DIO_PIN_P12, STD_LOW);//CAN_WAKE
  
}


/*===========================================================================*\
 * interface for DSLR FREQ control, TBD with EE
\*===========================================================================*/

/*******************************************************************************
*
* Changes for ICS  program
*
* Date        By                        Change
* ----------------------------------------------------------------------
* 02-May-12   Wade Li       update sleep/wakeup strategy to shorten startup time
* 10-Apr-12   Wade Li       add the gmlan bus and lin bus timeout control strategy
* 30-Dec-11   Wade Li       update the comments to follow DOXYGEN
* 25_Aug-11   wade Li       add Battery Calibration
* 11_Aug-11   wade Li       add diagnostics handler
* 03-Aug-11   Wade Li       add Battery monitor state: PWR_MANAGE_RESET
* 22-June-11  Wade Li       update MCU sleep/wake control, batt control
* 04-April-11 Wade Li       Created the initial module for ICS
*******************************************************************************/

