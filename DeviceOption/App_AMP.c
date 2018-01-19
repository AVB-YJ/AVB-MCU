/*******************************************************************************
 *  Project       : 10021420
 *  SW component  : LIN - Local Interconnect Network
 *  SW file       : %name:          Blower_App.c %
 *  Version       : %version:       5 %
 *  Instance      : %instance:      ctc_aud_1 %
 *  Author        : rz07l7
 *  Creation Date : Thu Apr  3 16:15:37 2008
 *----------------------------------------------------------------------------
 *  Last modification done
 *             by : %derived_by:    lzs7ws %
 *             on : %date_created:  Fri Apr 26 13:58:10 2013 %
 *----------------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description   : Blower Application Layer
 *
 */
/*============================================================================*\
 *              --- Included files and compilation variables ---
\*============================================================================*/
#include "OS.h"
#include "OS_Cfg.h"
#include "OS_Task.h"
#include "OS_timer.h"
#include "Port.h"
#include "Dio.h"
#include "App_AMP.h"
#include "string.h"
/*============================================================================*\
 *                    --- Private functions prototypes ---
\*============================================================================*/
static bool AMP_Is_Enabled(void);
static bool QBA_Update_Configuration(void);
static uint8_t QBA_IB_Diagnostics_Enable(void);
static uint8_t QBA_IB_Diagnostics_Mode(void);
static uint8_t QBA_IB_Channel_Gain(void);
static uint8_t QBA_IB_Extra_Gain_Enable(void);
static uint8_t QBA_IB_Amplifier_Mode(void);
static uint8_t QBA_IB_Mute_Front(void);
static uint8_t QBA_IB_Mute_Rear(void);
static uint8_t QBA_IB_Noise_Gating_State(void);
/*============================================================================*\
 *                         --- Private constants ---
\*============================================================================*/
 
 
/*============================================================================*\
 *                             --- Variables ---
\*============================================================================*/
static bool amp_enable;
static QBA_Control_T QBA_Control;
/*============================================================================*\
 *                             --- Functions ---
\*============================================================================*/

static bool AMP_Is_Enabled(void)
{
   return( AMPpio_Enable() );
}

static void AMP_Set_Enable(bool enable)
{
   amp_enable = enable;
   AMPpi_Enable(PORT_PIN_OUT);  /*set as output*/
   AMPpo_Enable(enable);
}

void AMP_Exit_Standby_Mode(void)
{
   AMP_Set_Enable(true);
}

/*===========================================================================*
 * Please refer to the detailed description in qba4.h.
 *===========================================================================*/
 bool QBA_Set_Amp_Mode_On(void)
{
   bool update_successful = false;

   QBA_Control.amplifier_mode = QBA_AMPLIFIER_MODE_ON;
   update_successful = QBA_Update_Configuration();
   return(update_successful);
}

/*===========================================================================*
 * Please refer to the detailed description in qba4.h.
 *===========================================================================*/
 bool QBA_Shutdown(void)
{
   bool update_successful = true;

   QBA_Control.amplifier_mode = QBA_AMPLIFIER_MODE_OFF;
   QBA_Control.front_mute_request = QBA_MUTE_REQUEST;
   QBA_Control.rear_mute_request = QBA_MUTE_REQUEST;
   if (AMP_Is_Enabled())
   {
      update_successful = QBA_Update_Configuration();
   }
   AMP_Set_Enable(false);

   return(update_successful);
}

/*===========================================================================*
 * Please refer to the detailed description in qba4.h.
 *===========================================================================*/
 bool QBA_Set_Front_Mute_State(QBA_Mute_State_T front_mute_request)
{   
   bool update_successful = false;

   QBA_Control.front_mute_request = front_mute_request;
   if (QBA_AMPLIFIER_MODE_ON == QBA_Control.amplifier_mode)
   {
      update_successful = QBA_Update_Configuration();
   }
   else
   {
      //Tr_Warn("QBA was not turned on.");
   }

   return(update_successful);
}

/*===========================================================================*
 * Please refer to the detailed description in qba4.h.
 *===========================================================================*/
 bool QBA_Set_Rear_Mute_State(QBA_Mute_State_T rear_mute_request)
{   
   bool update_successful = false;

   QBA_Control.rear_mute_request = rear_mute_request;
   if (QBA_AMPLIFIER_MODE_ON == QBA_Control.amplifier_mode)
   {
      update_successful = QBA_Update_Configuration();
   }
   else
   {
      //Tr_Warn("QBA was not turned on.");
   }

   return(update_successful);
}

/**
 * Determine the necessary configuration and send it to the QBA via IIC.
 *
 * @return     
 *   TRUE if the IIC write is successful.
 */
static bool QBA_Update_Configuration(void)
{
   uint8_t ib_buffer[QBA_IB_BUFFER_SIZE];
   bool successful_update = false;

   memset(ib_buffer,0,sizeof(ib_buffer));

   ib_buffer[QBA_IB_SUBADDRESS_BYTE] = QBA_ADDRESS_AUTO_INCREMENT | QBA_IB0_SUBADDRESS;

   ib_buffer[QBA_IB_INIT_DATA_BYTE]     = QBA_Get_IB0_Data();
   ib_buffer[QBA_IB_INIT_DATA_BYTE + 1] = QBA_Get_IB1_Data();
   ib_buffer[QBA_IB_INIT_DATA_BYTE + 2] = QBA_Get_IB2_Data();
   ib_buffer[QBA_IB_INIT_DATA_BYTE + 3] = QBA_Get_IB3_Data();
   
   //successful_update = IIC11_MasterSendStart(TDA75610_WRITE_ADDR, ib_buffer, sizeof(ib_buffer));

   return(successful_update);
}

/**
 * Determine the necessary mask for the diagnostic enable/defeat flag of
 * register IB0.
 *
 * @return     
 *   Mask for IB0.
 */
static uint8_t QBA_IB_Diagnostics_Enable(void)
{
   uint8_t diagnostics_enable = QBA_IB_DIAGNOSTIC_DEFEAT;

   if(QBA_DIAGNOSTIC_ENABLE == QBA_Control.diagnostics_control)
   {
      diagnostics_enable = QBA_IB_DIAGNOSTIC_ENABLE;
   }
   
   return(diagnostics_enable);
}

/**
 * Determine the necessary mask for the speaker/booster mode diagnostic flags of
 * register IB0.
 *
 * @return     
 *   Mask for IB0.
 */
static uint8_t QBA_IB_Diagnostics_Mode(void)
{
   uint8_t diagnostics_mode = QBA_IB_SPEAKER_MODE_DIAG_FRONT |
                              QBA_IB_SPEAKER_MODE_DIAG_REAR;

   //if (QBA_Get_External_Amp_Present())  /* Need to also check for RSA active. */
   {
      //diagnostics_mode = QBA_IB_BOOSTER_MODE_DIAG_FRONT |
                         //QBA_IB_BOOSTER_MODE_DIAG_REAR;
   }

   return(diagnostics_mode);
}

/**
 * Determine the necessary mask for the channel gain flags of register IB0.
 * The result is based on whether there is an external amp.
 *
 * @return     
 *   Mask for IB0.
 */
static uint8_t QBA_IB_Channel_Gain(void)
{
   qba_channel_gain_t channel_gain = QBA_CHANNEL_GAIN_FOR_SPEAKER;
   uint8_t channel_gain_ib;

   //if (QBA_Get_External_Amp_Present())  /* Need to also check for RSA active. */
   {
      //channel_gain = QBA_CHANNEL_GAIN_FOR_AMP;
   }

   switch (channel_gain)
   {
      case QBA_CHANNEL_GAIN_GV4:
         channel_gain_ib = QBA_IB_GAIN_FRONT_CHANNEL_GV4 |
                           QBA_IB_GAIN_REAR_CHANNEL_GV4;
         break;
      case QBA_CHANNEL_GAIN_GV3:
         channel_gain_ib = QBA_IB_GAIN_FRONT_CHANNEL_GV3 |
                           QBA_IB_GAIN_REAR_CHANNEL_GV3;
         break;
      case QBA_CHANNEL_GAIN_GV2:
         channel_gain_ib = QBA_IB_GAIN_FRONT_CHANNEL_GV2 |
                           QBA_IB_GAIN_REAR_CHANNEL_GV2;
         break;
      case QBA_CHANNEL_GAIN_GV1:
      default:
         channel_gain_ib = QBA_IB_GAIN_FRONT_CHANNEL_GV1 |
                           QBA_IB_GAIN_REAR_CHANNEL_GV1;
         break;
   }

   return(channel_gain_ib);
}

static uint8_t QBA_IB_Extra_Gain_Enable(void)
{
   bool extra_gain_enable = QBA_EXTRA_GAIN_FOR_SPEAKER;

   uint8_t extra_gain_ib = QBA_IB_NO_INCREASE_DIGITAL_GAIN;

   //if (QBA_Get_External_Amp_Present())  
   {
      //extra_gain_enable = QBA_EXTRA_GAIN_FOR_AMP;
   }
   if(extra_gain_enable)
   {
      extra_gain_ib = QBA_IB_6DB_INCREASE_DIGITAL_GAIN;
   }
   return(extra_gain_ib);
}
/**
 * Determine the necessary mask for the amplifier mode flag of register IB1.
 *
 * @return     
 *   Mask for IB1.
 */
static uint8_t QBA_IB_Amplifier_Mode(void)
{
   uint8_t amplifier_mode = QBA_IB_AMPLIFIER_MODE_OFF;
   
   if( QBA_AMPLIFIER_MODE_ON == QBA_Control.amplifier_mode )
   {
      amplifier_mode = QBA_IB_AMPLIFIER_MODE_ON;
   }

   return(amplifier_mode);
}

/**
 * Determine the necessary mask for the front mute/unmute flag of register IB1.
 *
 * @return     
 *   Mask for IB1.
 */
static uint8_t QBA_IB_Mute_Front(void)
{
   uint8_t front_mute_state = QBA_IB_MUTE_FRONT_CHANNELS;
   
   if (QBA_UNMUTE_REQUEST == QBA_Control.front_mute_request)
   {
      front_mute_state = QBA_IB_UNMUTE_FRONT_CHANNELS;
   }

   return(front_mute_state);
}

/**
 * Determine the necessary mask for the rear mute/unmute flag of register IB1.
 *
 * @return     
 *   Mask for IB1.
 */
static uint8_t QBA_IB_Mute_Rear(void)
{
   uint8_t rear_mute_state = QBA_IB_MUTE_REAR_CHANNELS;
   
   if (QBA_UNMUTE_REQUEST == QBA_Control.rear_mute_request)
   {
      rear_mute_state = QBA_IB_UNMUTE_REAR_CHANNELS;
   }

   return(rear_mute_state);
}

/**
 * Determine the necessary mask for the noise gating flag of register IB3.
 *
 * @return     
 *   Mask for IB3.
 */
static uint8_t QBA_IB_Noise_Gating_State(void)
{
   uint8_t noise_gating_state = QBA_IB_NOISE_GATING_ON;
   
   //if (QBA_Get_External_Amp_Present())  /* Need to also check for RSA active. */
   {
     // noise_gating_state = QBA_IB_NOISE_GATING_OFF;
   }

   return(noise_gating_state);
}

/*!===========================================================================*\
 *
 * Function  : AMP_State_Init
 * Role      :          
 *
\*============================================================================*/
void AMP_State_Init(void)
{
    AMP_Exit_Standby_Mode();
    QBA_Set_Amp_Mode_On();
}
/*!===========================================================================*\
 *
 * Function  : App_AMP_Control_Task
 * Role      :          
 *
\*============================================================================*/
void App_AMP_Control_Task(void)
{
  
}
/*!===========================================================================*\
 *
 * Function  : App_AMP_Control_Start
 * Role      :          
 *
\*============================================================================*/
void App_AMP_Control_Start(void)
{
     (void)OS_ActivateTask(OS_Task_AMP, Os_Task_AMP_Offset, Os_Task_AMP_Period);
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date          Rev      userid    (Description on following lines: SCR #, etc)
 * ----------- --------  ---------  --------------------------------------------
 * 4-26-2013      3.1         lzs7ws    adjust indicator PWM from 80% to 23%
 * 5-02-2012      3.0         lzs7ws     remove PWM dimming control task to IoHwAb_Dimming.c and remove PWR_Cotrol task to App_PowerMode.c
 * 4-11-2012      2.9         lzs7ws     Add PID 109, fix ctc_aud#6962.
 *	3-15-2012      2.8         lzs7ws     Add PID 104
 *	2-7-2012        2.7         lzs7ws     Add LIN message control for new add PWM in PV
 * 11-29-2011    2.6      lzs7ws    add Diagnostic  ICS
 * 09-29-2011    2.5      tz27jb      add dimming diagnositic function, set the DZA default dimming to 100%, 
 *                                    when no LIN message, don't goto sleep when MFT is running or GM diag is running
 * 09-14-2011    2.5      lzs7ws    add ILIN and TLIN sleep command
 * 09-02-2011    2.4      lzs7ws     add shut down PWM dimming function when power mode abnormal                                       
 * 08-24-2011    2.3      lzs7ws     integrate APP_LIN_Function.c file into LIN_App.c file.
 * 06-16-2011    2.2      rzlw3b     update task periodic and offset time    
 * 05-09-2011    2.1      lzs7ws     HLIN message $37 ($37) was adde    
 * 04-07-2011    2.0      lz6bwk     HLIN message $36 ($76) was added.
 *                          
 *
 *
\*===========================================================================*/
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/
