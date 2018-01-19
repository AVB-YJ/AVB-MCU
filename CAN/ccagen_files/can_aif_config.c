/*******************************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_aif_config.c                                         
  File Description:
  This module contains configuration of Transmit and Receive messages   

*******************************************************************************/


#include"can_aif_config.h"
#include"can_aif_rx.h"
#include"can_aif_tx.h"
                   

/*******************************************************************************
*         Configurations for Transmit message                                  *
*******************************************************************************/

#ifdef CAN_CH0_SELECTED 
canuint8_t AIF_TxMessage_DVD_Ch0[CAN_CH0_TX_MSG1_DLC];
canuint8_t AIF_TxMessage_AC_Ch0[CAN_CH0_TX_MSG2_DLC];

#endif/*CH0 Transmit Message Definitions*/

#ifdef CAN_CH1_SELECTED 
/*Tx1*/
#endif/*CH1 Transmit Message Definitions*/

#ifdef CAN_CH2_SELECTED 
/*Tx2*/
#endif/*CH2 Transmit Message Definitions*/

#ifdef TX_APPLICATION_SIGNAL_CONFIRMATION

#ifdef CAN_CH0_SELECTED 
/*  Configuration of Number of signals in each message */
/*Message0*/
#define NO_OF_SIGNALS_FOR_Ch0TxMessage0       5
#define TOTAL_FLAG_BYTES_FOR_Ch0TxMessage0 (NO_OF_SIGNALS_FOR_Ch0TxMessage0+7)/8
/*  Configurations for Transmit Configuration and Timeout flag array for each 
   Functional message*/

canuint8_t AIF_Ch0TxMessage0_Sig_Conf_Array[TOTAL_FLAG_BYTES_FOR_Ch0TxMessage0];
canuint8_t AIF_Ch0TxMessage0_Sig_Timeout_Array[TOTAL_FLAG_BYTES_FOR_Ch0TxMessage0];


/*Message1*/
#define NO_OF_SIGNALS_FOR_Ch0TxMessage1       9
#define TOTAL_FLAG_BYTES_FOR_Ch0TxMessage1 (NO_OF_SIGNALS_FOR_Ch0TxMessage1+7)/8
/*  Configurations for Transmit Configuration and Timeout flag array for each 
   Functional message*/

canuint8_t AIF_Ch0TxMessage1_Sig_Conf_Array[TOTAL_FLAG_BYTES_FOR_Ch0TxMessage1];
canuint8_t AIF_Ch0TxMessage1_Sig_Timeout_Array[TOTAL_FLAG_BYTES_FOR_Ch0TxMessage1];




#endif/*Configuration for number of Tx signals- CH0*/

#ifdef CAN_CH1_SELECTED 
/*Tx_No_of_signals_Ch1*/
#endif/*Configuration for number of Tx signals- CH1*/

#ifdef CAN_CH2_SELECTED 
/*Tx_No_of_signals_Ch2*/
#endif/*Configuration for number of Tx signals- CH2*/

#endif/*TX_APPLICATION_SIGNAL_CONFIRMATION*/

/*****************************************************************************
*         Configurations for Transmit messages                               *
*****************************************************************************/

/*  AIF Transmit Parameter Table                                              
    Note: This table has 1 to 1 mapping with the VBM Transmit Parameter
          table.For diagnostic messages Message_Type must be entered as       
          INVALID(FF) and Buffer addess as NULL  */                            
const AIF_Tx_Msg_Parameters_T
              AIF_Tx_Msg_Parameters[TOTAL_NUMBER_OF_TX_MSG] =
{

/* Message_Type   Buffer address       Base address of Tx Conf flag             
   Base address of Tx Timeout flag       Total_Flag_Bytes                   */

#ifdef CAN_CH0_SELECTED

{CYCLIC_ON_INIT,AIF_TxMessage_DVD_Ch0},				//Tx_message_type, Tx_meassage_addr

{CYCLIC_ON_INIT,AIF_TxMessage_AC_Ch0}				//Tx_message_type, Tx_meassage_addr


   
#endif

#ifdef CAN_CH1_SELECTED

/*TxTable1*/
#endif

#ifdef CAN_CH2_SELECTED
/*TxTable2*/
#endif
};

/*****************************************************************************
*                Transmit signal definitions                                 *
*****************************************************************************/
#ifdef CAN_CH0_SELECTED 


/*        bit field address                             start bit    end bit */
const  Byte_Bit_Fld_T  DVD_AVMswitch_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_DVD_Ch0[0],         5,5};

const  Byte_Bit_Fld_T  DVD_AVMQuitRequest_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_DVD_Ch0[0],         4,4};

const  Byte_Bit_Fld_T  DVD_BSDEnableSw_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_DVD_Ch0[0],         1,0};

const  Long_Word_Bit_Fld_T  HU_NaviDistance = 
 {(canuint32_t *) &AIF_TxMessage_DVD_Ch0[4],         16,0};

const  Byte_Bit_Fld_T  HU_NaviIconNumber = 
 {(canuint8_t *) &AIF_TxMessage_DVD_Ch0[5],         7,0};



/*        bit field address                             start bit    end bit */
const  Byte_Bit_Fld_T  HU_FrontAUTOACOnReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[0],         7,6};

const  Byte_Bit_Fld_T  HU_FrontACOffReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[0],         5,4};

const  Byte_Bit_Fld_T  HU_ACDEFAdjustReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[0],         3,2};

const  Byte_Bit_Fld_T  HU_ACLRTempAdjustValueReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[1],         7,6};

const  Byte_Bit_Fld_T  DVD_ACLFTempAdjustValueReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[1],         5,0};

const  Byte_Bit_Fld_T  HU_ACFanAdjustValueReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[2],         7,4};

const  Byte_Bit_Fld_T  DVD_ACFrontModeAdjustReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[2],         2,0};

const  Byte_Bit_Fld_T  DVD_Circulation_ModeReq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[4],         6,4};

const  Byte_Bit_Fld_T  HU_ACreq_Ch0 = 
 {(canuint8_t *) &AIF_TxMessage_AC_Ch0[4],         3,2};

#endif/*CH0 Transmit Signal Definitions*/

#ifdef CAN_CH1_SELECTED
/*TxSignalDef1*/

#endif/*CH1 Transmit Signal Definitions*/

#ifdef CAN_CH2_SELECTED
/*TxSignalDef2*/
#endif/*CH2 Transmit Signal Definitions*/

/*****************************************************************************
*         Configurations for Receive messages                                *
*****************************************************************************/

#ifdef CAN_CH0_SELECTED
/*****************************************************************************
*                  AIF Receive message Buffer                                *
*****************************************************************************/
canuint8_t AIF_RxMessage_BCM_Ch0[CAN_CH0_RX_MSG1_DLC];
canuint8_t AIF_RxMessage_GW1_Ch0[CAN_CH0_RX_MSG2_DLC];
canuint8_t AIF_RxMessage_GW2_Ch0[CAN_CH0_RX_MSG3_DLC];
canuint8_t AIF_RxMessage_AVM_Ch0[CAN_CH0_RX_MSG4_DLC];


#endif/* CH0 Receive Messages*/

#ifdef CAN_CH1_SELECTED
/*****************************************************************************
*                  AIF Receive message Buffer                                *
*****************************************************************************/
/*Rx1*/

#endif/* CH1 Receive Messages*/


#ifdef RX_APPLICATION_SIGNAL_INDICATION

#ifdef CAN_CH0_SELECTED
/* Configuration of Number of signals in each message */
/*   Message0*/
#define NO_OF_SIGNALS_FOR_Ch0RxMessage0      15
#define TOTAL_FLAG_BYTES_FOR_Ch0RxMessage0 (NO_OF_SIGNALS_FOR_Ch0RxMessage0+7)/8
/*     Configurations for Transmit Configuration and Timeout flag array for each 
   Functional message*/

canuint8_t AIF_Ch0RxMessage0_Sig_Ind_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage0];
canuint8_t AIF_Ch0RxMessage0_Sig_Timeout_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage0];


/*   Message1*/
#define NO_OF_SIGNALS_FOR_Ch0RxMessage1      5
#define TOTAL_FLAG_BYTES_FOR_Ch0RxMessage1 (NO_OF_SIGNALS_FOR_Ch0RxMessage1+7)/8
/*     Configurations for Transmit Configuration and Timeout flag array for each 
   Functional message*/

canuint8_t AIF_Ch0RxMessage1_Sig_Ind_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage1];
canuint8_t AIF_Ch0RxMessage1_Sig_Timeout_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage1];


/*   Message2*/
#define NO_OF_SIGNALS_FOR_Ch0RxMessage2      3
#define TOTAL_FLAG_BYTES_FOR_Ch0RxMessage2 (NO_OF_SIGNALS_FOR_Ch0RxMessage2+7)/8
/*     Configurations for Transmit Configuration and Timeout flag array for each 
   Functional message*/

canuint8_t AIF_Ch0RxMessage2_Sig_Ind_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage2];
canuint8_t AIF_Ch0RxMessage2_Sig_Timeout_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage2];


/*   Message3*/
#define NO_OF_SIGNALS_FOR_Ch0RxMessage3      1
#define TOTAL_FLAG_BYTES_FOR_Ch0RxMessage3 (NO_OF_SIGNALS_FOR_Ch0RxMessage3+7)/8
/*     Configurations for Transmit Configuration and Timeout flag array for each 
   Functional message*/

canuint8_t AIF_Ch0RxMessage3_Sig_Ind_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage3];
canuint8_t AIF_Ch0RxMessage3_Sig_Timeout_Array[TOTAL_FLAG_BYTES_FOR_Ch0RxMessage3];







#endif/*Configuration for number of Rx signals- CH0*/

#ifdef CAN_CH1_SELECTED

/*Rx_No_of_signals_Ch1*/

#endif/*Configuration for number of Rx signals- CH1*/

#ifdef CAN_CH2_SELECTED

/*Rx_No_of_signals_Ch2*/

#endif/*Configuration for number of Rx signals- CH2*/

#endif/*RX_APPLICATION_SIGNAL_INDICATION*/


#ifdef CAN_CH0_SELECTED
/* Configuration of Receive parameter Table*/
const AIF_Rx_Msg_Parameters_T
              AIF_Rx_Msg_Parameters_Ch0[NUMBER_OF_RX_MSG_SUPPORTED_CH0] =
{

/* Buffer address           Base address of Rx Ind flags
     Base address of Rx Timeout flags     Total_Flag_Bytes*/


{AIF_RxMessage_BCM_Ch0},

{AIF_RxMessage_GW1_Ch0},

{AIF_RxMessage_GW2_Ch0},

{AIF_RxMessage_AVM_Ch0}


  

};


/**********************************************************************
*                      Receive signal definitions                     *
**********************************************************************/
/*                 bit field address                      start bit  end bit */

/*This parameter requires word access from odd address,so byte bit field is used*/

/*BCM*/
const  Byte_Bit_Fld_T  BCM_LowBeamStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[0],         7,6};

const  Byte_Bit_Fld_T  BCM_HighBeamStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[0],         5,4};

const  Byte_Bit_Fld_T  BCM_FrontFoglampStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[0],         3,2};

const  Byte_Bit_Fld_T  BCM_RearFoglampStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[0],         1,0};

const  Byte_Bit_Fld_T  BCM_TurnIndicatorLeft_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[1],         7,6};

const  Byte_Bit_Fld_T  BCM_TurnIndicatorRight_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[1],         5,4};

const  Byte_Bit_Fld_T  BCM_PositionLampStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[1],         2,3};

const  Byte_Bit_Fld_T  BCM_DriverDoorStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         7,7};

const  Byte_Bit_Fld_T  BCM_PassengerDoorStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         6,6};

const  Byte_Bit_Fld_T  BCM_LeftRearDoorStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         5,5};

const  Byte_Bit_Fld_T  BCM_RightRearDoorStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         4,4};

const  Byte_Bit_Fld_T  BCM_TrunkStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         3,3};

const  Byte_Bit_Fld_T  BCM_HoodStatus_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         2,2};

const  Byte_Bit_Fld_T  BCM_SunroofStatusCh0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[2],         1,1};

const  Byte_Bit_Fld_T  BCM_PowerStatusFeedback_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_BCM_Ch0[5],         3,2};


/*GW1*/
const  Byte_Bit_Fld_T  AS_SteeringAngleValid_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW1_Ch0[0],         0,0};

const  Byte_Bit_Fld_T  SAS_SteeringAngle_MSB_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW1_Ch0[3],         7,0};

const  Byte_Bit_Fld_T  SAS_SteeringAngle_LSB_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW1_Ch0[4],         7,0};

const  Byte_Bit_Fld_T  TCU_ShiftPostionValid_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW1_Ch0[5],         7,7};

const  Byte_Bit_Fld_T  TCU_GearShiftPositon_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW1_Ch0[5],         6,3};

/*GW2*/
const  Byte_Bit_Fld_T  ESP_VehicleSpeedValid_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW2_Ch0[1],         6,6};

const  Byte_Bit_Fld_T  ESP_VehicleSpeed_MSB_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW2_Ch0[1],         4,0};

const  Byte_Bit_Fld_T  ESP_VehicleSpeed_LSB_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_GW2_Ch0[2],         7,0};

/*AVM*/
const  Byte_Bit_Fld_T  AVM_DisplayReq_Ch0 = 
 {(canuint8_t *) &AIF_RxMessage_AVM_Ch0[0],         7,7};

#endif/*Channel 0 Rx Signal Definition*/

#ifdef CAN_CH1_SELECTED
/* Configuration of Receive parameter Table*/
const AIF_Rx_Msg_Parameters_T
              AIF_Rx_Msg_Parameters_Ch1[NUMBER_OF_RX_MSG_SUPPORTED_CH1] =
{
  /* Buffer address           Base address of Rx Ind flags
     Base address of Rx Timeout flags     Total_Flag_Bytes*/
  
/*RxTable1*/
};

/**********************************************************************
*                      Receive signal definitions                     *
**********************************************************************/
/*                 bit field address                      start bit  end bit */



/*RxSignalDef1*/

#endif/*Channel 1 Rx Signal Definition*/



#ifdef CAN_CH2_SELECTED
/* Configuration of Receive parameter Table*/
const AIF_Rx_Msg_Parameters_T
              AIF_Rx_Msg_Parameters_Ch1[NUMBER_OF_RX_MSG_SUPPORTED_CH2] =
{
  /* Buffer address           Base address of Rx Ind flags
     Base address of Rx Timeout flags     Total_Flag_Bytes*/
  
/*RxTable2*/
};

/**********************************************************************
*                      Receive signal definitions                     *
**********************************************************************/
/*                 bit field address                      start bit  end bit */



/*RxSignalDef2*/

#endif/*Channel 2 Rx Signal Definition*/

 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

