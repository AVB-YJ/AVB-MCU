/*******************************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_aif_config.h                                          
  File Description:
  This module contains interfaces with the Application     

*******************************************************************************/

#ifndef CAN_AIF_CONFIG_H
#define CAN_AIF_CONFIG_H 

#include "can_handler_datatypes.h"
#include "bit_flds.h"
#include "can_handler_config.h"
#include "can_aif_misc.h"
#include "can_vbm_config.h"
                

/*******************************************************************************
*                          T R A N S M I T                                     *
*******************************************************************************/
/*******************************************************************************
* Define this macro if the application requires confirmation at signal level   *
*******************************************************************************/
#define TX_APPLICATION_SIGNAL_CONFIRMATION

typedef enum Msg_Handles_Tx
{
DVD_Ch0,
AC_Ch0,
}TX_MSG_LIST_TYPE;

typedef enum Msg_Handles_Rx_Ch0
{
BCM_Ch0,
GW1_Ch0,
GW2_Ch0,
AVM_Ch0,
NUM_OF_RX_MSGS_CH0
}RX_MSG_LIST_TYPE_CH0;

#ifdef CAN_CH0_SELECTED
/*******************************************************************************
*          Transmit Signal Definition                                 *
*******************************************************************************/

/*Message 0 Signals*/
/*DVD_Ch0*/
extern const  Byte_Bit_Fld_T DVD_AVMswitch_Ch0;
extern const  Byte_Bit_Fld_T DVD_AVMQuitRequest_Ch0;
extern const  Byte_Bit_Fld_T DVD_BSDEnableSw_Ch0;
extern const  Long_Word_Bit_Fld_T HU_NaviDistance;
extern const  Byte_Bit_Fld_T HU_NaviIconNumber;



/*Message 1 Signals*/
/*AC_Ch0*/
extern const  Byte_Bit_Fld_T HU_FrontAUTOACOnReq_Ch0;
extern const  Byte_Bit_Fld_T HU_FrontACOffReq_Ch0;
extern const  Byte_Bit_Fld_T HU_ACDEFAdjustReq_Ch0;
extern const  Byte_Bit_Fld_T HU_ACLRTempAdjustValueReq_Ch0;
extern const  Byte_Bit_Fld_T DVD_ACLFTempAdjustValueReq_Ch0;
extern const  Byte_Bit_Fld_T HU_ACFanAdjustValueReq_Ch0;
extern const  Byte_Bit_Fld_T DVD_ACFrontModeAdjustReq_Ch0;
extern const  Byte_Bit_Fld_T DVD_Circulation_ModeReq_Ch0;
extern const  Byte_Bit_Fld_T HU_ACreq_Ch0;

/*******************************************************************************
*                   Macros for updating Tx signals                             *
*******************************************************************************/

/*Message 0 Signals*/
/*DVD_Ch0*/
#define AIFPutDVD_AVMswitch_Ch0(x)					Write_Byte_Bit_Fld(&DVD_AVMswitch_Ch0,(x))				//ȫ���л�����
#define AIFPutDVD_AVMQuitRequest_Ch0(x)				Write_Byte_Bit_Fld(&DVD_AVMQuitRequest_Ch0,(x))			//AVM�˳�����
#define AIFPutDVD_BSDEnableSw_Ch0(x)				Write_Byte_Bit_Fld(&DVD_BSDEnableSw_Ch0,(x))			//BSDʹ�ܿ����ź�
#define AIFPutHU_NaviDistance(x)					Write_Long_Word_Bit_Fld(&HU_NaviDistance,(x))			//����·�ھ���
#define AIFPutHU_NaviIconNumber(x)					Write_Byte_Bit_Fld(&HU_NaviIconNumber,(x))				//������ʶ����


/*Message 1 Signals*/
/*AC_Ch0*/
#define AIFPutHU_FrontAUTOACOnReq_Ch0(x)			Write_Byte_Bit_Fld(&HU_FrontAUTOACOnReq_Ch0,(x))		//ǰ�ſյ��Զ�ģʽ���������ź�
#define AIFPutHU_FrontACOffReq_Ch0(x)				Write_Byte_Bit_Fld(&HU_FrontACOffReq_Ch0,(x))			//ǰ�ſյ��ر������ź�
#define AIFPutHU_ACDEFAdjustReq_Ch0(x)				Write_Byte_Bit_Fld(&HU_ACDEFAdjustReq_Ch0,(x))			//ǰ��˪ģʽ�趨�����ź�
#define AIFPutHU_ACLRTempAdjustValueReq_Ch0(x)      Write_Byte_Bit_Fld(&HU_ACLRTempAdjustValueReq_Ch0,(x))	//�����¶��趨�����ź�
#define AIFPutDVD_ACLFTempAdjustValueReq_Ch0(x)		Write_Byte_Bit_Fld(&DVD_ACLFTempAdjustValueReq_Ch0,(x))	//�����¶��趨�����ź�
#define AIFPutHU_ACFanAdjustValueReq_Ch0(x)			Write_Byte_Bit_Fld(&HU_ACFanAdjustValueReq_Ch0,(x))		//�����趨�����ź�
#define AIFPutDVD_ACFrontModeAdjustReq_Ch0(x)		Write_Byte_Bit_Fld(&DVD_ACFrontModeAdjustReq_Ch0,(x))	//����ģʽ�趨�����ź�
#define AIFPutDVD_Circulation_ModeReq_Ch0(x)		Write_Byte_Bit_Fld(&DVD_Circulation_ModeReq_Ch0,(x))	//ѭ��ģʽ�趨�����ź�
#define AIFPutHU_ACreq_Ch0(x)						Write_Byte_Bit_Fld(&HU_ACreq_Ch0,(x))					//A/C�趨�����ź�


#ifdef TX_APPLICATION_SIGNAL_CONFIRMATION 

typedef enum 
{
/* Configure enum value for the each messages corresponding to msg_handle
in the VBM Transmit table for Functional messages only */
Ch0TxMessage0=0,
Ch0TxMessage1=1

}Can_MessageType;


#endif/*TX_APPLICATION_SIGNAL_CONFIRMATION */
#endif/* CAN_CH0_SELECTED*/
/*******************************************************************************
*                          R E C E I V E                                       *
*******************************************************************************/
/*******************************************************************************
* Define this macro if the application requires indication at signal level     *
*******************************************************************************/
#undef RX_APPLICATION_SIGNAL_INDICATION

/*******************************************************************************
* Receive Ch0 signal definition                                              *
*******************************************************************************/
#ifdef CAN_CH0_SELECTED


/*Message 0 Signals*/
/*BCM_Ch0*/
extern const  Byte_Bit_Fld_T BCM_LowBeamStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_HighBeamStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_FrontFoglampStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_RearFoglampStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_TurnIndicatorLeft_Ch0;
extern const  Byte_Bit_Fld_T BCM_TurnIndicatorRight_Ch0;
extern const  Byte_Bit_Fld_T BCM_PositionLampStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_DriverDoorStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_PassengerDoorStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_LeftRearDoorStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_RightRearDoorStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_TrunkStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_HoodStatus_Ch0;
extern const  Byte_Bit_Fld_T BCM_SunroofStatusCh0;
extern const  Byte_Bit_Fld_T BCM_PowerStatusFeedback_Ch0;

/*Message 1 Signals*/
/*GW1_Ch0*/
extern const  Byte_Bit_Fld_T AS_SteeringAngleValid_Ch0;
extern const  Byte_Bit_Fld_T SAS_SteeringAngle_MSB_Ch0;
extern const  Byte_Bit_Fld_T SAS_SteeringAngle_LSB_Ch0;
extern const  Byte_Bit_Fld_T TCU_ShiftPostionValid_Ch0;
extern const  Byte_Bit_Fld_T TCU_GearShiftPositon_Ch0;


/*Message 2 Signals*/
/*GW2_Ch0*/
extern const  Byte_Bit_Fld_T ESP_VehicleSpeedValid_Ch0;
extern const  Byte_Bit_Fld_T ESP_VehicleSpeed_MSB_Ch0;
extern const  Byte_Bit_Fld_T ESP_VehicleSpeed_LSB_Ch0;


/*Message 3 Signals*/
/*AVM_Ch0*/
extern const  Byte_Bit_Fld_T AVM_DisplayReq_Ch0;


/*******************************************************************************
*                   Macros for updating Rx signals                             *
*******************************************************************************/

/*Message0 */
/*BCM_Ch0*/
#define AIFGetBCM_LowBeamStatus_Ch0()			Read_Byte_Bit_Fld(&BCM_LowBeamStatus_Ch0)			//����ƹ���״̬
#define AIFGetBCM_HighBeamStatus_Ch0()			Read_Byte_Bit_Fld(&BCM_HighBeamStatus_Ch0)			//Զ��ƹ���״̬
#define AIFGetBCM_FrontFoglampStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_FrontFoglampStatus_Ch0)		//ǰ��ƹ���״̬
#define AIFGetBCM_RearFoglampStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_RearFoglampStatus_Ch0)		//����ƹ���״̬
#define AIFGetBCM_TurnIndicatorLeft_Ch0()		Read_Byte_Bit_Fld(&BCM_TurnIndicatorLeft_Ch0)		//��ת����ź�
#define AIFGetBCM_TurnIndicatorRight_Ch0()		Read_Byte_Bit_Fld(&BCM_TurnIndicatorRight_Ch0)		//��ת����ź�
#define AIFGetBCM_PositionLampStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_PositionLampStatus_Ch0)		//λ�õƹ���״̬
#define AIFGetBCM_DriverDoorStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_DriverDoorStatus_Ch0)		//��ǰ��״̬
#define AIFGetBCM_PassengerDoorStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_PassengerDoorStatus_Ch0)		//��ǰ��״̬
#define AIFGetBCM_LeftRearDoorStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_LeftRearDoorStatus_Ch0)		//�����״̬
#define AIFGetBCM_RightRearDoorStatus_Ch0()		Read_Byte_Bit_Fld(&BCM_RightRearDoorStatus_Ch0)		//�Һ���״̬
#define AIFGetBCM_TrunkStatus_Ch0()				Read_Byte_Bit_Fld(&BCM_TrunkStatus_Ch0)				//������״̬
#define AIFGetBCM_HoodStatus_Ch0()				Read_Byte_Bit_Fld(&BCM_HoodStatus_Ch0)				//�������ո�״̬
#define AIFGetBCM_SunroofStatusCh0()			Read_Byte_Bit_Fld(&BCM_SunroofStatusCh0)			//�촰״̬(�촰δ���ź�)
#define AIFGetBCM_PowerStatusFeedback_Ch0()		Read_Byte_Bit_Fld(&BCM_PowerStatusFeedback_Ch0)		//��Դ״̬����

/*Message1 */
/*GW1_Ch0*/
#define AIFGetAS_SteeringAngleValid_Ch0()                Read_Byte_Bit_Fld(&AS_SteeringAngleValid_Ch0)
#define AIFGetSAS_SteeringAngle_MSB_Ch0()                Read_Byte_Bit_Fld(&SAS_SteeringAngle_MSB_Ch0)  
#define AIFGetSAS_SteeringAngle_LSB_Ch0()                Read_Byte_Bit_Fld(&SAS_SteeringAngle_LSB_Ch0)
#define AIFGetTCU_ShiftPostionValid_Ch0()                Read_Byte_Bit_Fld(&TCU_ShiftPostionValid_Ch0)   
#define AIFGetTCU_GearShiftPositon_Ch0()                 Read_Byte_Bit_Fld(&TCU_GearShiftPositon_Ch0)


/*Message2 */
/*GW2_Ch0*/
#define AIFGetESP_VehicleSpeedValid_Ch0()                Read_Byte_Bit_Fld(&ESP_VehicleSpeedValid_Ch0)
#define AIFGetESP_VehicleSpeed_MSB_Ch0()                 Read_Byte_Bit_Fld(&ESP_VehicleSpeed_MSB_Ch0)
#define AIFGetESP_VehicleSpeed_LSB_Ch0()                 Read_Byte_Bit_Fld(&ESP_VehicleSpeed_LSB_Ch0)

/*Message3 */
/*AVM_Ch0*/
#define AIFGetESP_VehicleSpeed_LSB_Ch0()                 Read_Byte_Bit_Fld(&ESP_VehicleSpeed_LSB_Ch0)

#endif/*CAN_CH0_SELECTED*/
#endif/*#ifndef CAN_AIF_CONFIG_H*/

 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

