/*******************************************************************************
 *  Project      : IK 10021420
 *  SW component : LIN - Local Interconnect Network
 *  SW file      : LIN_App.h
 *----------------------------------------------------------------------------*/
/*! \file
 *  \brief
 *  Description  : LIN Application Layer
 *
 *
 ******************************************************************************/

/* To avoid multiple definition if the file is included several times */
#ifndef BLOWER_App_h
#define BLOWER_App_h
#include "Platform_Types.h"
#include "Systype.h"
#include "OS.h"

/*============================================================================*\
 *                          --- Public typedefs ---
\*============================================================================*/
/** Values for requesting amplifier mode. */
typedef enum QBA_IB_Amplifier_Mode_Tag
{
   QBA_AMPLIFIER_MODE_OFF,
   QBA_AMPLIFIER_MODE_ON
} QBA_IB_Amplifier_Mode_T;

/** Values for requesting channel gain. */
typedef enum qba_channel_gain_tag
{
   QBA_CHANNEL_GAIN_GV1,
   QBA_CHANNEL_GAIN_GV2,
   QBA_CHANNEL_GAIN_GV3,
   QBA_CHANNEL_GAIN_GV4
} qba_channel_gain_t;
/**
 * This type defines the values that can be passed in functions
 * QBA_Set_Front_Mute_State and QBA_Set_Rear_Mute_State.
 */
typedef enum QBA_Mute_State_Tag
{
   QBA_MUTE_REQUEST,
   QBA_UNMUTE_REQUEST
} QBA_Mute_State_T;

/** Values for requesting diagnostic defeat or enable. */
typedef enum qba_ib_diagnostics_state_tag
{
   QBA_DIAGNOSTIC_DEFEAT,
   QBA_DIAGNOSTIC_ENABLE
} QBA_Diagnostics_Control_T;

/** Used to keep track of requested control states. */
typedef struct QBA_Control_Tag
{
   QBA_Mute_State_T           front_mute_request;
   QBA_Mute_State_T           rear_mute_request;
   QBA_IB_Amplifier_Mode_T    amplifier_mode;
   QBA_Diagnostics_Control_T  diagnostics_control;
} QBA_Control_T;

/*============================================================================*\
*
* Exported preprocessor #define constants (object-like macros), upper case
*
\*============================================================================*/
/*============================================================================*\
*
* Exported preprocessor #define macros (i.e., those using # or ## operator),
* upper case
*
\*============================================================================*/
/* ENABLE_PLL */
#define AMPpi_Enable(dir) 	Port_SetPinDirection(PORT_PIN_P66, dir)   
#define AMPpo_Enable(x)  	Dio_WriteChannel(DIO_PIN_P66,x)  
#define AMPpio_Enable()   	Dio_ReadChannel(DIO_PIN_P66) 

/** IIC timeout in msec */
#define QBA_IIC_LOCK_TIMEOUT   250

/** IIC timeout in msec for read operation */
#define QBA_IIC_READ_TIMEOUT   100

/** IIC timeout in msec for write operation */
#define QBA_IIC_WRITE_TIMEOUT  100

/** IIC requested bus speed in kHz */
#define QBA_IIC_SPEED          400

/** Diagnostic wait timeout */
#define QBA4_DIAG_WAIT_TIMEOUT 120

/** Number of times to retry IIC Read if there is a failure. */
#define QBA_IIC_READ_RETRIES                   2
/** Number of times to retry IIC Write if there is a failure. */
#define QBA_IIC_WRITE_RETRIES                  2

/** The IIC address of the QBA. */
#define QBA_IIC_ADDRESS                        0xD8

/** QBA subaddress for the first instruction register. */
#define QBA_IB0_SUBADDRESS                     0x00
#define QBA_IB1_SUBADDRESS                     0x01
/** QBA subaddress for the first diagnostic register. */
#define QBA_DB0_SUBADDRESS                     0x10
#define QBA_DB1_SUBADDRESS                     0x11
#define QBA_DB2_SUBADDRESS                     0x12
#define QBA_DB3_SUBADDRESS                     0x13
/** Instructs the QBA to increment the subaddress after each read or write. */
#define QBA_ADDRESS_AUTO_INCREMENT             0x20
#define QBA_ADDRESS_NO_AUTO_INCREMENT             0x00
/** For each IIC read, use a start and stop bit, and specify the retries. */
#define QBA_IIC_READ_CONFIGURATION             (IIC_START | IIC_STOP | QBA_IIC_READ_RETRIES)
/** For each IIC write, use a start and stop bit, and specify the retries. */
#define QBA_IIC_WRITE_CONFIGURATION            (IIC_START | IIC_STOP | QBA_IIC_WRITE_RETRIES)

/**************************************************/
/**************  Instruction bytes  ***************/
/**************************************************/
/** 
 * Index to the first element of an instruction byte buffer, which will
 * contain the QBA IIC address
 */
#define QBA_IIC_ADDRESS_BYTE                   0

/** 
 * Index to the first element of an instruction byte buffer, which will
 * contain the subaddress of the first instruction byte.
 */
#define QBA_IB_SUBADDRESS_BYTE                 1
/**
 * Index to the second element of an instruction byte buffer, which will
 * contain the data for the first instruction byte.
 */
#define QBA_IB_INIT_DATA_BYTE                  2
#define QBA_DB_INIT_DATA_BYTE                  2
/**
 * Size of an instruction byte buffer, one byte to specify the subaddress,
 * and four bytes for each of four instruction registers.
 */
#define QBA_IB_BUFFER_SIZE                     6

/** Register IB0 Mask: Diagnositic Defeat. */
#define QBA_IB_DIAGNOSTIC_DEFEAT               0x00
/** Register IB0 Mask: Diagnositic Enable. */
#define QBA_IB_DIAGNOSTIC_ENABLE               0x80
/** Register IB0 Mask: Front Speaker Mode Diagnositic. */
#define QBA_IB_SPEAKER_MODE_DIAG_FRONT         0x00
/** Register IB0 Mask: Front Booster Mode (Amplifier) Diagnositic. */
#define QBA_IB_BOOSTER_MODE_DIAG_FRONT         0x40
/** Register IB0 Mask: Rear Speaker Mode Diagnositic. */
#define QBA_IB_SPEAKER_MODE_DIAG_REAR          0x00
/** Register IB0 Mask: Rear Booster Mode (Amplifier) Diagnositic. */
#define QBA_IB_BOOSTER_MODE_DIAG_REAR          0x20

/** Register IB0 Mask: Front Channel Gain of GV1. */
#define QBA_IB_GAIN_FRONT_CHANNEL_GV1          0x00
/** Register IB0 Mask: Front Channel Gain of GV2. */
#define QBA_IB_GAIN_FRONT_CHANNEL_GV2          0x08
/** Register IB0 Mask: Front Channel Gain of GV3. */
#define QBA_IB_GAIN_FRONT_CHANNEL_GV3          0x10
/** Register IB0 Mask: Front Channel Gain of GV4. */
#define QBA_IB_GAIN_FRONT_CHANNEL_GV4          0x18

/** Register IB0 Mask: Rear Channel Gain of GV1. */
#define QBA_IB_GAIN_REAR_CHANNEL_GV1           0x00
/** Register IB0 Mask: Rear Channel Gain of GV2. */
#define QBA_IB_GAIN_REAR_CHANNEL_GV2           0x02
/** Register IB0 Mask: Rear Channel Gain of GV3. */
#define QBA_IB_GAIN_REAR_CHANNEL_GV3           0x04
/** Register IB0 Mask: Rear Channel Gain of GV4. */
#define QBA_IB_GAIN_REAR_CHANNEL_GV4           0x06

/** Register IB0 Mask: No Increase of Digital Gain. */
#define QBA_IB_NO_INCREASE_DIGITAL_GAIN        0x00
/** Register IB0 Mask: 6dB Increase of Digital Gain. */
#define QBA_IB_6DB_INCREASE_DIGITAL_GAIN       0x01

/** Register IB1 Mask: Amplifier Off. */
#define QBA_IB_AMPLIFIER_MODE_OFF              0x00
/** Register IB1 Mask: Amplifier On. */
#define QBA_IB_AMPLIFIER_MODE_ON               0x80

/** Register IB1 Mask: Mute Time Setting = 1.45ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_1_45_MS               0x00
/** Register IB1 Mask: Mute Time Setting = 5.8ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_5_8_MS                0x10
/** Register IB1 Mask: Mute Time Setting = 11.6ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_11_6_MS               0x20
/** Register IB1 Mask: Mute Time Setting = 23.2ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_23_2_MS               0x30
/** Register IB1 Mask: Mute Time Setting = 34.8ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_34_8_MS               0x40
/** Register IB1 Mask: Mute Time Setting = 69.6ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_69_6_MS               0x50
/** Register IB1 Mask: Mute Time Setting = 140ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_140_MS                0x60
/** Register IB1 Mask: Mute Time Setting = 278ms. (Fs = 44.1kHz) */
#define QBA_IB_MUTE_TIME_278_MS                0x70

/** Register IB1 Mask: Mute Front Channels. */
#define QBA_IB_MUTE_FRONT_CHANNELS             0x00
/** Register IB1 Mask: Unmute Front Channels. */
#define QBA_IB_UNMUTE_FRONT_CHANNELS           0x08
/** Register IB1 Mask: Mute Rear Channels. */
#define QBA_IB_MUTE_REAR_CHANNELS              0x00
/** Register IB1 Mask: Unmute Rear Channels. */
#define QBA_IB_UNMUTE_REAR_CHANNELS            0x04

/** Register IB1 Mask: Sample Frequency = 44.1/48 kHz. */
#define QBA_IB_SAMPLE_FREQ_STD_1               0x00
/** Register IB1 Mask: Sample Frequency = 44.1/48 kHz. */
#define QBA_IB_SAMPLE_FREQ_STD_2               0x01
/** Register IB1 Mask: Sample Frequency = 96 kHz. */
#define QBA_IB_SAMPLE_FREQ_96_KHZ              0x02
/** Register IB1 Mask: Sample Frequency = 192 kHz. */
#define QBA_IB_SAMPLE_FREQ_192_KHZ             0x03

/** Register IB2 Mask: No Short Fault Information on Diag Pin. */
#define QBA_IB_NO_SHORT_FAULT_INFO_ON_DIAG_PIN 0x00
/** Register IB2 Mask: Short Fault Information on Diag Pin. */
#define QBA_IB_SHORT_FAULT_INFO_ON_DIAG_PIN    0x80
/** Register IB2 Mask: No Offset Fault Information on Diag Pin. */
#define QBA_IB_NO_OFFSET_INFO_ON_DIAG_PIN      0x00
/** Register IB2 Mask: Offset Fault Information on Diag Pin. */
#define QBA_IB_OFFSET_INFO_ON_DIAG_PIN         0x40

/** Register IB2 Mask: Temperature Warning Information on Diag Pin, Tw1. */
#define QBA_IB_THERMAL_WARNING_1               0x00
/** Register IB2 Mask: Temperature Warning Information on Diag Pin, Tw2. */
#define QBA_IB_THERMAL_WARNING_2               0x08
/** Register IB2 Mask: Temperature Warning Information on Diag Pin, Tw3. */
#define QBA_IB_THERMAL_WARNING_3               0x10
/** Register IB2 Mask: Temperature Warning Information on Diag Pin, Tw4. */
#define QBA_IB_THERMAL_WARNING_4               0x18
/** Register IB2 Mask: No Temperature Warning Information on Diag Pin. */
#define QBA_IB_NO_THERMAL_WARNING              0x20

/** Register IB2 Mask: Clip Detection Level, 1%. */
#define QBA_CLIP_DETECTION_LEVEL_1_PERCENT     0x00
/** Register IB2 Mask: Clip Detection Level, 5%. */
#define QBA_CLIP_DETECTION_LEVEL_5_PERCENT     0x02
/** Register IB2 Mask: Clip Detection Level, 10%. */
#define QBA_CLIP_DETECTION_LEVEL_10_PERCENT    0x04
/** Register IB2 Mask: Clip Detection Level Disabled. */
#define QBA_CLIP_DETECTION_LEVEL_DISABLED      0x06

/** Register IB3 Mask: Noise Gating On. */
#define QBA_IB_NOISE_GATING_ON                 0x00
/** Register IB3 Mask: Noise Gating Off. */
#define QBA_IB_NOISE_GATING_OFF                0x80

/** Register IB3 Mask: Under-voltage Digital Mute On. */
#define QBA_IB_UNDER_VOLTAGE_DIGITAL_MUTE_ON   0x00
/** Register IB3 Mask: Under-voltage Digital Mute Off. */
#define QBA_IB_UNDER_VOLTAGE_DIGITAL_MUTE_OFF  0x20

/** Register IB3 Mask: No Channels in Tristate. */
#define QBA_IB_NO_CHANNELS_IN_TRISTATE         0x00
/** Register IB3 Mask: Right Front Channel in Tristate. */
#define QBA_IB_TRISTATE_RF_CHANNEL             0x10
/** Register IB3 Mask: Left Front Channel in Tristate. */
#define QBA_IB_TRISTATE_LF_CHANNEL             0x08
/** Register IB3 Mask: Right Rear Channel in Tristate. */
#define QBA_IB_TRISTATE_RR_CHANNEL             0x04
/** Register IB3 Mask: Left Rear Channel in Tristate. */
#define QBA_IB_TRISTATE_LR_CHANNEL             0x02

/** Register IB3 Mask: Input High Pass Filter Off. */
#define QBA_IB_INPUT_HIGH_PASS_FILTER_OFF      0x00
/** Register IB3 Mask: Input High Pass Filter On. */
#define QBA_IB_INPUT_HIGH_PASS_FILTER_ON       0x01

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/** Return the required mask for instruction register IB0. */
#define QBA_Get_IB0_Data() ( QBA_IB_Diagnostics_Enable()                               | \
                             QBA_IB_Diagnostics_Mode()                                 | \
                             QBA_IB_Channel_Gain()                                     | \
                             QBA_IB_Extra_Gain_Enable() )

/** Return the required mask for instruction register IB1. */
#define QBA_Get_IB1_Data() ( QBA_IB_Amplifier_Mode()                   | \
                             QBA_IB_MUTE_TIME_SETTING                  | \
                             QBA_IB_Mute_Front()                       | \
                             QBA_IB_Mute_Rear()                        | \
                             QBA_IB_SAMPLE_FREQ_STD_1                    )

/** Return the required mask for instruction register IB2. */
#define QBA_Get_IB2_Data() ( QBA_IB_NO_SHORT_FAULT_INFO_ON_DIAG_PIN    | \
                             QBA_IB_NO_OFFSET_INFO_ON_DIAG_PIN         | \
                             QBA_IB_THERMAL_WARNING_1                  | \
                             QBA_CLIP_DETECT                             )

/** Return the required mask for instruction register IB3. */
#define QBA_Get_IB3_Data() ( QBA_IB_Noise_Gating_State()               | \
                             QBA_IB_UNDER_VOLTAGE_DIGITAL_MUTE_ON      | \
                             QBA_IB_NO_CHANNELS_IN_TRISTATE            | \
                             QBA_IB_INPUT_HIGH_PASS_FILTER_ON            )

/**
 * QBA_MUTE_TIME_MS controls the time that it takes for the QBA to fully mute
 * or unmute after being commanded.
 *
 * It is also used to initialize QBA_Mute_Time_ms, which should be used outside
 * of this building block, to determine when full muting or unmuting has
 * occurred.  This can be useful to eliminate pops.
 *
 * All radios are assumed to be configured to use a sampling rate of Fs = 44.1kHz.
 * At this rate, the following are the valid selections for QBA_MUTE_TIME.
 * Any other value will generate an error.
 *
 * @verbatim
    Actual Time       QBA_MUTE_TIME
       1.45 ms              2
       5.8  ms              6
      11.6  ms             12
      23.2  ms             24
      34.8  ms             35
      69.8  ms             70
     140    ms            140
     278    ms            278
   @endverbatim
 *
 * A value of 35 is recommended for most radios.  Consult with audio
 * engineers for confirmation.
 */
#define QBA_MUTE_TIME_MS                35

/**
 * QBA_STANDBY_TO_TRISTATE_TIME is the time in msec from when QBA Enable
 * pin on the micro is commanded high until the Enable pin on the QBA is high.
 * This typically should be less than 20 msec, but could vary according to
 * the actual circuit.  The correct timing should be determined by using
 * an oscilloscope.
 *
 * It is used to initialize QBA_Standby_To_Tristate_Time_ms, which should
 * be used as the wait time between calls to QBA_Exit_Standby_Mode and
 * QBA_Set_Amp_Mode_On.
 */
#define QBA_STANDBY_TO_TRISTATE_TIME_MS 20

/**
 * Desired gain for speaker mode.
 * Choose one of the following:
 *
 * @verbatim
    QBA_CHANNEL_GAIN_GV1    15.1 - 17.1 dB
    QBA_CHANNEL_GAIN_GV2    10.1 - 12.1 dB
    QBA_CHANNEL_GAIN_GV3     7.1 -  9.1 dB
    QBA_CHANNEL_GAIN_GV4     2.1 -  4.1 dB
   @endverbatim
 *
 * Consult with audio engineers to determine the correct value.
 */
#define QBA_CHANNEL_GAIN_FOR_SPEAKER    QBA_CHANNEL_GAIN_GV1

/**
 * Desired gain for amp mode.
 * Choose one of the following:
 *
 * @verbatim
    QBA_CHANNEL_GAIN_GV1    15.1 - 17.1 dB
    QBA_CHANNEL_GAIN_GV2    10.1 - 12.1 dB
    QBA_CHANNEL_GAIN_GV3     7.1 -  9.1 dB
    QBA_CHANNEL_GAIN_GV4     2.1 -  4.1 dB
   @endverbatim
 *
 * Consult with audio engineers to determine the correct value.
 */
#define QBA_CHANNEL_GAIN_FOR_AMP        QBA_CHANNEL_GAIN_GV3

/**
 * Return true if 6 dB additional gain is desired.
 */
#define QBA_EXTRA_GAIN_FOR_SPEAKER          true
#define QBA_EXTRA_GAIN_FOR_AMP              false

/**
 * Clip detection level.  Choose one of the following:
 *
 * @verbatim
    QBA_CLIP_DETECTION_LEVEL_1_PERCENT
    QBA_CLIP_DETECTION_LEVEL_5_PERCENT
    QBA_CLIP_DETECTION_LEVEL_10_PERCENT
    QBA_CLIP_DETECTION_LEVEL_DISABLED
   @endverbatim
 *
 * Recommendation is 10% for GM and 1% for VW.
 *
 * Consult with audio engineers for confirmation.
 */
#define QBA_CLIP_DETECT                 QBA_CLIP_DETECTION_LEVEL_5_PERCENT

/*As per the ICR QBA circuitry, threshold voltage for 5% THD is 2.5V */
#define AD_DDL_THRESHOLD    (0xC1F0)
/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/**
 * Mute Time Setting flags for register IB0.  It is configured according to the
 * setting of QBA_MUTE_TIME_MS in qba4_cfg.h.
 * The mute times are determined with the assumption that the sample rate is
 * 44.1kHz.  At this time, all radios are expected to use this sample rate.
 */

#if (2 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_1_45_MS
#elif (6 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_5_8_MS
#elif (12 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_11_6_MS
#elif (24 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_23_2_MS
#elif (35 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_34_8_MS
#elif (70 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_69_6_MS
#elif (140 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_140_MS
#elif (278 == QBA_MUTE_TIME_MS)
   #define QBA_IB_MUTE_TIME_SETTING   QBA_IB_MUTE_TIME_278_MS
#else
   #define QBA_IB_MUTE_TIME_SETTING
   #error "Configure with a valid QBA_MUTE_TIME_MS."
#endif


/*============================================================================*\
*
* Exported type declarations (enum, struct, union, typedef), mixed case
*
\*============================================================================*/

/*============================================================================*\
*
* Exported object declarations, mixed case
*
\*============================================================================*/

/*============================================================================*\
 *                          --- Public constants ---
\*============================================================================*/


/*============================================================================*\
 *                          --- Public variables ---
\*============================================================================*/


/*============================================================================*\
 *                          --- Public functions ---
\*============================================================================*/
extern void AMP_State_Init(void);
extern void App_AMP_Control_Start(void);
extern void App_AMP_Control_Task(void);
/*============================================================================*\
*
* Exported function prototypes (including function-header-block),
* (without "extern"), mixed case
*
\*============================================================================*/


#endif /* App_AMP.h */
/******************************************************************************
 *                               End of file                                  *
 ******************************************************************************/

