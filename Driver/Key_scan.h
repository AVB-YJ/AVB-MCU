/******************************************************************************
 *
 *               (c)  Delco Electronics Systems (unpub.)
 *        All Rights Reserved.  Delco Electronics Confidential
 *
 ******************************************************************************
 ******************************************************************************
 *            Title : %name: Key_scan.h %
 *
 *          Version : %version: 1 %
 *
 *           Author : %derived_by: lzs7ws %
 *
 *		     Instance : %instance: ctc_aud_2 %
 *
 *     Date Updated : %date_created: Tue Jun 26 15:37:08 2012 %
 *
 *      Description : 
 *                    
 ******************************************************************************/

/*============================================================================*\
 *                Include Files
\*============================================================================*/
#ifndef KEY_SCAN_H
#define KEY_SCAN_H
#include "Std_Types.h"
#include "Systype.h"


/*============================================================================*\
 *                Macros 
\*============================================================================*/
#define SWC_DEB_COUNT                     (3)
#define SWC_RANGE_TABLE_SIZE              (5)

#define SWC1_STATE_OFF                    (0)
#define SWC1_STATE_CALL                   (1)
#define SWC1_STATE_MUTE                   (2)
#define SWC1_STATE_VOLUME_P               (3)
#define SWC1_STATE_VOLUME_M               (4)
#define SWC1_STATE_SHRT_GND               (5)

#define SWC2_STATE_OFF                    (0)
#define SWC2_STATE_UNCALL                 (1)
#define SWC2_STATE_MODE                   (2)
#define SWC2_STATE_SEEK_P                 (3)
#define SWC2_STATE_SEEK_M                 (4)
#define SWC2_STATE_SHRT_GND               (5)

/*¡À10%*/
#define SWC1_STATE_SHRT_GND_MAX           (100)
#define SWC1_STATE_SHRT_GND_MIN           (0)

/*2.62V CALL ¡À10%*/
#define SWC1_STATE_CALL_MAX               (2882)
#define SWC1_STATE_CALL_MIN               (2358)

/*1.95V MUTE ¡À10%*/
#define SWC1_STATE_MUTE_MAX               (2145)
#define SWC1_STATE_MUTE_MIN               (1755)

/*1.29V VOLUME + ¡À10%*/
#define SWC1_STATE_VOLUME_P_MAX           (1419)
#define SWC1_STATE_VOLUME_P_MIN           (1161)

/*0.67V VOLUME - ¡À10%*/
#define SWC1_STATE_VOLUME_M_MAX           (737)
#define SWC1_STATE_VOLUME_M_MIN           (603)

/*¡À10% VOLUME - ¡À10%*/
#define SWC2_STATE_SHRT_GND_MAX           (100)
#define SWC2_STATE_SHRT_GND_MIN           (0)

/*2.62V UNCALL ¡À10%*/
#define SWC2_STATE_UNCALL_MAX             (2882)
#define SWC2_STATE_UNCALL_MIN             (2358)

/*1.95V MODE ¡À10%*/
#define SWC2_STATE_MODE_MAX               (2145)
#define SWC2_STATE_MODE_MIN               (1755)

/*1.29V SEEK + ¡À10%*/
#define SWC2_STATE_SEEK_P_MAX             (1419)
#define SWC2_STATE_SEEK_P_MIN             (1161)

/*0.67V SEEK  - ¡À10%*/
#define SWC2_STATE_SEEK_M_MAX             (737)
#define SWC2_STATE_SEEK_M_MIN             (603)


typedef  union {
    uint8   Byte;
    struct {
    uint8_t call_key:1;
    uint8_t mute_key:1;
    uint8_t volume_p_key:1;
    uint8_t volume_m_key:1;
    uint8_t fault:1;
    uint8_t unused:3;
    } Bit;
} SWC1_Switch_Status_T;


typedef  union {
    uint8   Byte;
    struct {
    uint8_t uncall_key:1;
    uint8_t mode_key:1;
    uint8_t seek_p_key:1;
    uint8_t seek_m_key:1;
    uint8_t fault:1;
    uint8_t unused:3;
    } Bit;
} SWC2_Switch_Status_T;

typedef struct
{
	uint8_t  state;
	struct
	{
		uint16_t min;
		uint16_t max;
	} Limit;
} IoHwAb_HBGRSRangeType;

extern SWC1_Switch_Status_T SWC1_Appl_Status;
extern SWC2_Switch_Status_T SWC2_Appl_Status;
/*============================================================================*\
 *                Global ( Public ) Variables and Functions
\*============================================================================*/
extern void IoHwAb_KB_Start(void);
extern void IoHwAb_KB_Task(void);
#endif
/*===========================================================================*\
 * File Revision History 
 *===========================================================================
 *
 *Date            userid   Description
 *--------------- -------  -------------------------------------------------
 * 04-5-2011   lzs7ws Change for ICS
 * 
 *05/Jun/06  	  rzqrv5	Initial version for FORD CD3XX
 *--------------- -------  -------------------------------------------------
 *  10-May-2007   (rzqrv5) Cesar Ramirez
 * + Implementation of configuration tables for buttons mapping on LIN messages
 *
 * 08 Sep 2008 (nzb8cb) Update encoders functionality to report counts 
 * + SCR 10611          according spec
 *
\*===========================================================================*/
