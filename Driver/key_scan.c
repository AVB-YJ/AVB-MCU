/*===========================================================================*\
 * FILE: key_arb.c
 *===========================================================================
 * Copyright 2003  Technologies, Inc., All Rights Reserved.
 *  Confidential
 *---------------------------------------------------------------------------
 * %full_filespec: key_scan.c~6:csrc:ctc_aud#12 %
 * %version: 6 %
 * %derived_by: lzs7ws %
 * %date_created: Mon Jan 21 15:21:53 2013 % 
 *----------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *    
 *    
 *
 * ABBREVIATIONS:
 *
 * TRACEABILITY INFO:
 *
 *   Requirements Document(s):
 *
 *   Applicable Standards (in order of precedence: highest first):
 *   C Coding Standards SW REF 264.15D
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
\*===========================================================================*/
/*===========================================================================*\
 * Preprocessor commands
\*===========================================================================*/
#include "Std_Types.h"
#include "Hw_Reg.h"
#include "key_scan.h"
#include "Adc.h"
#include "OS_Task.h"
#include "Port.h"
#include "App_PowerMode.h"
#include "uart.h"
#include "CCA.h"
/*===========================================================================*\
 * Macros
\*===========================================================================*/
#define NUM_DEBOUNCE 3U
#define ON_DEBOUNCE_COUNTER  10U
#define KEY_TASKS  3U
#define keyscan_dalay()   OS_Wait(5)
/*===========================================================================*\
 * Function prototypes
\*===========================================================================*/
static uint16 ADC_Key_Read_SW1_Volt(void);
static uint16 ADC_Key_Read_SW2_Volt(void);
static uint8_t   SW1_Get_Range(uint16_t raw_adc);
static uint8_t   SW2_Get_Range(uint16_t raw_adc);
uint8_t Key_Send_Buf[6];
/*===========================================================================*\
 * Potentiometer_Leavel_Table only for SZM
\*===========================================================================*/
static IoHwAb_HBGRSRangeType Rng_Cluster_Swc1_Arr[]=
{
	{SWC1_STATE_CALL,    {SWC1_STATE_CALL_MIN,    SWC1_STATE_CALL_MAX}},
    	{SWC1_STATE_MUTE, {SWC1_STATE_MUTE_MIN, SWC1_STATE_MUTE_MAX}},
	{SWC1_STATE_VOLUME_P,     {SWC1_STATE_VOLUME_P_MIN,     SWC1_STATE_VOLUME_P_MAX}},
	{SWC1_STATE_VOLUME_M,   {SWC1_STATE_VOLUME_M_MIN,   SWC1_STATE_VOLUME_M_MAX}},
	{SWC1_STATE_SHRT_GND,    {SWC1_STATE_SHRT_GND_MIN,    SWC1_STATE_SHRT_GND_MAX}},

};

static IoHwAb_HBGRSRangeType Rng_Cluster_Swc2_Arr[]=
{
	{SWC2_STATE_UNCALL,    {SWC2_STATE_UNCALL_MIN,    SWC2_STATE_UNCALL_MAX}},
    	{SWC2_STATE_MODE, {SWC2_STATE_MODE_MIN, SWC2_STATE_MODE_MAX}},
	{SWC2_STATE_SEEK_P,     {SWC2_STATE_SEEK_P_MIN,     SWC2_STATE_SEEK_P_MAX}},
	{SWC2_STATE_SEEK_M,   {SWC2_STATE_SEEK_M_MIN,   SWC2_STATE_SEEK_M_MAX}},
	{SWC2_STATE_SHRT_GND,    {SWC2_STATE_SHRT_GND_MIN,    SWC2_STATE_SHRT_GND_MAX}},

};
/*===========================================================================*\
 * OS_CPU_LOAD test  declarations
\*===========================================================================*/
#ifdef OS_CPU_LOAD
typedef struct
{
   uint16_t curr_counter;
   uint16_t prev_counter;
   uint16_t diff_time;
   uint16_t max_time;
} KB_App_Au_Task_time_T;

KB_App_Au_Task_time_T KB_App_Au_Task_time,KB_App_Au_Idle_Task_time;
#endif

SWC1_Switch_Status_T SWC1_Appl_Status;
SWC2_Switch_Status_T SWC2_Appl_Status;
/*===========================================================================*\
 * Local type declarations
\*===========================================================================*/

/*===========================================================================*\
 * Constants Key_Mapping
\*===========================================================================*/

/*===========================================================================*\
 * Variables for keyscan
\*===========================================================================*/

/*===========================================================================*\
 * FUNCTION: debounce_key_M
 *===========================================================================
 * RETURN VALUE:
 *    None
 * PARAMETERS:
 *    ow_column, column_mask
 * EXTERNAL REFERENCES:
 *    None.
 * DEVIATION FROM STANDARDS:
 *    None.
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 * Returns the value of the key that has passed through the debounce routine
\*===========================================================================*/

/*===========================================================================*\
 * FUNCTION: Key_Process_Row1
 *===========================================================================
 * RETURN VALUE:
 *    None.
 * PARAMETERS:
 *    None.
 * EXTERNAL REFERENCES:
 *    None.
 * DEVIATION FROM STANDARDS:
 *    None.
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 * Scan the keyboard ROW1 for any key to be pressed and return the row-column 
 * position of such key.
\*===========================================================================*/

/*===========================================================================*\
 * FUNCTION: Key_Process_Row2
 *===========================================================================
 * RETURN VALUE:
 *    None.
 * PARAMETERS:
 *    None.
 * EXTERNAL REFERENCES:
 *    None.
 * DEVIATION FROM STANDARDS:
 *    None.
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 * Scan the keyboard ROW2 for any key to be pressed and return the row-column 
 * position of such key.
\*===========================================================================*/

/*===========================================================================*\
 * FUNCTION: Key_Process
 *===========================================================================
 * RETURN VALUE:
 *    None.
 * PARAMETERS:
 *    None.
 * EXTERNAL REFERENCES:
 *    None.
 * DEVIATION FROM STANDARDS:
 *    None.
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 * Process for key press, virtual switch key press and local wake up key press 
\*===========================================================================*/
void IoHwAb_KB_Start(void)
{
			//Set_STRB0_Value_Low();  /*STRB0 output low */
			//Set_STRB1_Value_Low();  /*STRB1 output low */  
     (void)OS_ActivateTask(OS_Task_KB, OS_Task_KB_Offset, OS_Task_KB_Period);
}
/*===========================================================================*\
 * FUNCTION: IoHwAb_KB_Task
 *===========================================================================
 * RETURN VALUE:
 *    None.
 * PARAMETERS:
 *    None.
 * EXTERNAL REFERENCES:
 *    None.
 * DEVIATION FROM STANDARDS:
 *    None.
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 * key scan task, each row scan for 2ms once and after all row scan, prosess row scan result 
\*===========================================================================*/
void IoHwAb_KB_Task(void)
{
    uint32 aplus_swc1_voltage;
    uint32 aplus_swc2_voltage;
    uint16_t raw_swc1_voltage;
    uint16_t raw_swc2_voltage;
    uint8_t  SWC1_HWIO_Status;
    uint8_t  SWC2_HWIO_Status;
    
    static uint8_t  key_send_timer = 0;
    /*ADC read*/
    aplus_swc1_voltage = ADC_Key_Read_SW1_Volt();
    aplus_swc2_voltage = ADC_Key_Read_SW2_Volt();

    raw_swc1_voltage = (aplus_swc1_voltage*3300/1023);
    raw_swc2_voltage = (aplus_swc2_voltage*3300/1023);
    

    /*Key detection*/	
    /* Read the SWC status from the hardware  */
    SWC1_HWIO_Status = SW1_Get_Range(raw_swc1_voltage);
    SWC2_HWIO_Status = SW2_Get_Range(raw_swc2_voltage);

    if(1)/*Battery is normal*/
    {
        /* Process the read value and update the application status  */
        switch (SWC1_HWIO_Status)
        {
            case SWC1_STATE_OFF:
            {
                SWC1_Appl_Status.Bit.call_key = 0;
                SWC1_Appl_Status.Bit.mute_key = 0;
                SWC1_Appl_Status.Bit.volume_p_key = 0;
                SWC1_Appl_Status.Bit.volume_m_key = 0;
                SWC1_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC1_STATE_CALL:
            {
                SWC1_Appl_Status.Bit.call_key = 1;
                SWC1_Appl_Status.Bit.mute_key = 0;
                SWC1_Appl_Status.Bit.volume_p_key = 0;
                SWC1_Appl_Status.Bit.volume_m_key = 0;
                SWC1_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC1_STATE_MUTE:
            {
                SWC1_Appl_Status.Bit.call_key = 0;
                SWC1_Appl_Status.Bit.mute_key = 1;
                SWC1_Appl_Status.Bit.volume_p_key = 0;
                SWC1_Appl_Status.Bit.volume_m_key = 0;
                SWC1_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC1_STATE_VOLUME_P:
            {
                SWC1_Appl_Status.Bit.call_key = 0;
                SWC1_Appl_Status.Bit.mute_key = 0;
                SWC1_Appl_Status.Bit.volume_p_key = 1;
                SWC1_Appl_Status.Bit.volume_m_key = 0;
                SWC1_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC1_STATE_VOLUME_M:
            {
                SWC1_Appl_Status.Bit.call_key = 0;
                SWC1_Appl_Status.Bit.mute_key = 0;
                SWC1_Appl_Status.Bit.volume_p_key = 0;
                SWC1_Appl_Status.Bit.volume_m_key = 1;
                SWC1_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC1_STATE_SHRT_GND:
            {
                SWC1_Appl_Status.Bit.call_key = 0;
                SWC1_Appl_Status.Bit.mute_key = 0;
                SWC1_Appl_Status.Bit.volume_p_key = 0;
                SWC1_Appl_Status.Bit.volume_m_key = 0;
                SWC1_Appl_Status.Bit.fault = 1;
                break;
            }
            default:
                break;
        }
    }
    else
    {
        SWC1_Appl_Status.Bit.call_key = 0;
        SWC1_Appl_Status.Bit.mute_key = 0;
        SWC1_Appl_Status.Bit.volume_p_key = 0;
        SWC1_Appl_Status.Bit.volume_m_key = 0;
        SWC1_Appl_Status.Bit.fault = 0;
    }

    if(1)/*Battery is normal*/
    {
        /* Process the read value and update the application status  */
        switch (SWC2_HWIO_Status)
        {
            case SWC2_STATE_OFF:
            {
                SWC2_Appl_Status.Bit.uncall_key = 0;
                SWC2_Appl_Status.Bit.mode_key = 0;
                SWC2_Appl_Status.Bit.seek_p_key = 0;
                SWC2_Appl_Status.Bit.seek_m_key = 0;
                SWC2_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC2_STATE_UNCALL:
            {
                SWC2_Appl_Status.Bit.uncall_key = 1;
                SWC2_Appl_Status.Bit.mode_key = 0;
                SWC2_Appl_Status.Bit.seek_p_key = 0;
                SWC2_Appl_Status.Bit.seek_m_key = 0;
                SWC2_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC2_STATE_MODE:
            {
               SWC2_Appl_Status.Bit.uncall_key = 0;
               SWC2_Appl_Status.Bit.mode_key = 1;
               SWC2_Appl_Status.Bit.seek_p_key = 0;
               SWC2_Appl_Status.Bit.seek_m_key = 0;
               SWC2_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC2_STATE_SEEK_P:
            {
                SWC2_Appl_Status.Bit.uncall_key = 0;
                SWC2_Appl_Status.Bit.mode_key = 0;
                SWC2_Appl_Status.Bit.seek_p_key = 1;
                SWC2_Appl_Status.Bit.seek_m_key = 0;
                SWC2_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC2_STATE_SEEK_M:
            {
                SWC2_Appl_Status.Bit.uncall_key = 0;
                SWC2_Appl_Status.Bit.mode_key = 0;
                SWC2_Appl_Status.Bit.seek_p_key = 0;
                SWC2_Appl_Status.Bit.seek_m_key = 1;
                SWC2_Appl_Status.Bit.fault = 0;
                break;
            }
            case SWC2_STATE_SHRT_GND:
            {
                SWC2_Appl_Status.Bit.uncall_key = 0;
                SWC2_Appl_Status.Bit.mode_key = 0;
                SWC2_Appl_Status.Bit.seek_p_key = 0;
                SWC2_Appl_Status.Bit.seek_m_key = 0;
                SWC2_Appl_Status.Bit.fault = 0;
                break;
            }
            default:
                break;
        }
    }
    else
     {
        SWC2_Appl_Status.Bit.uncall_key = 0;
        SWC2_Appl_Status.Bit.mode_key = 0;
        SWC2_Appl_Status.Bit.seek_p_key = 0;
        SWC2_Appl_Status.Bit.seek_m_key = 0;
        SWC2_Appl_Status.Bit.fault = 0;
    }

    key_send_timer++;
    if(key_send_timer > 5)
    {
      Key_Send_Buf[0] = 0x31;
      Key_Send_Buf[1] = 0x32;
   //   Key_Send_Buf[2] = 0x03;
  //    Key_Send_Buf[3] = 0x01;
   //   Key_Send_Buf[4] = SWC1_Appl_Status.Byte;
   //   Key_Send_Buf[5] = SWC2_Appl_Status.Byte;
	  //m_InterruptTimes ++;
      //UART2_Tx_Data(Key_Send_Buf,2);
      if(SWC1_Appl_Status.Byte||SWC2_Appl_Status.Byte)
         {
             Door_Status |= 0x80;
         }
         else
         {
            Door_Status &= 0x7F;
         }
      key_send_timer = 0;
    }
    
}

static uint16 ADC_Key_Read_SW1_Volt(void)
{
    Adc_StatusType AdcStatus;
    uint16_t*   real_battery;
	
    Adc_StartGroupConversion(ADC_SW1_VOLTAGE);
    do
    {
        AdcStatus = Adc_GetGroupStatus(ADC_SW1_VOLTAGE);
    }
    while (ADC_BUSY == AdcStatus);

    real_battery = Adc_ValueReadGroup(ADC_SW1_VOLTAGE);

    return (*real_battery);
}

static uint16 ADC_Key_Read_SW2_Volt(void)
{
     Adc_StatusType AdcStatus;
     uint16_t*   real_battery;
	
    Adc_StartGroupConversion(ADC_SW2_VOLTAGE);
    do
    {
        AdcStatus = Adc_GetGroupStatus(ADC_SW2_VOLTAGE);
    }
    while (ADC_BUSY == AdcStatus);

    real_battery = Adc_ValueReadGroup(ADC_SW2_VOLTAGE);

    return (*real_battery);
}

static uint8_t   SW1_Get_Range(uint16_t raw_adc)
{
   uint8_t state;
   uint8_t index = 0;
   bool state_val = FALSE;
   
   do {
   	if (((Rng_Cluster_Swc1_Arr[index].Limit.min) <= raw_adc) &&
   	    ((Rng_Cluster_Swc1_Arr[index].Limit.max) >= raw_adc)) {
   		state = Rng_Cluster_Swc1_Arr[index].state;
   		state_val = TRUE;
   	}
   	index++;
   } while(!state_val && (index < SWC_RANGE_TABLE_SIZE));
		
	if (!state_val)
     {
		state = 0xFF;
	}

	return (state);
}

static uint8_t   SW2_Get_Range(uint16_t raw_adc)
{
   uint8_t state;
   uint8_t index = 0;
   bool state_val = FALSE;
   
   do {
   	if (((Rng_Cluster_Swc2_Arr[index].Limit.min) <= raw_adc) &&
   	    ((Rng_Cluster_Swc2_Arr[index].Limit.max) >= raw_adc)) {
   		state = Rng_Cluster_Swc2_Arr[index].state;
   		state_val = TRUE;
   	}
   	index++;
   } while(!state_val && (index < SWC_RANGE_TABLE_SIZE));
		
	if (!state_val)
     {
		state = 0xFF;
	}

	return (state);
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * 01-Nov-2012 (lzs7ws) Todd Yu 
 *+ fix degraded mode issue
 *
 * 19-July-2012 (lzs7ws) Todd Yu  Init for B81
 *+ fix QAC warning
\*===========================================================================*/
