/* $Header:   O:\Pvcs\IBS_Software\07BlackTie\Up_Level\rtos.c_v   1.15   27 Jul 2005 18:57:20   Dworaczyk_Marcin  $*/
/*===========================================================================*\
 * FILE: CCA.c
 *===========================================================================
 * Copyright 1998-2008  Technologies, Inc., All Rights Reserved.
 *  Confidential
 *---------------------------------------------------------------------------
 * %full_filespec: CCA.c~2:csrc:ctc_ec#9 %
 * %version: 2 %
 * %derived_by: bzxwpg %
 * %date_modified: Mon Dec  2 12:27:30 2013 %
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *    CCA task & initialization.
 *
 * AUTHOR:
 *    Liting
 *
\*===========================================================================*/

/*===========================================================================*\
 * Include Header files 
\*===========================================================================*/

#include "global.h"
#include "CCA.h"
#include "OS_Task.h"
#include "Port.h"
#include "Dio.h"
#include "UART.h"
#include "ipc_utils.h"

canuint8_t ACC_Status;

bool Open_ACC_On_Request = false;
bool Open_ACC_Off_Request = false;
bool Air_AutoMode_Request = false;
canuint8_t Air_DefrostMode_Request = 0;
canuint8_t Air_CircuationMode_Request = 0;
canuint8_t Air_TempOfMain = 0;
canuint8_t Air_TempOfCopilot = 0;
canuint8_t Air_Speed = 0;
canuint8_t Air_Direction = 0;
canuint8_t Received_IPC_Data = 0;

canuint8_t Door_Status = 0;
canuint8_t Door_Status_Buffer[5];
canuint8_t Lamp_Status_Buffer[5];


#define 	UI_UNFINISHED

/*===========================================================================*/
/*!
 * This function active the CCA task.\n
 *
 * <b>Actions:</b>
 * 
 *                             
 */
/*===========================================================================*/
void CCA_Task_Start(void)
{
   (void)OS_ActivateTask(OS_Task_CAN, OS_Task_CAN_Offset, OS_Task_CAN_Period);  /* start periodic task */
}

//OS_Task_CAN
void CCA_Task (void)
{
    uint8_t DriverDoorStatus = 0;
    uint8_t PassengerDoorStatus= 0;
    uint8_t LeftRearDoorStatus = 0;
    uint8_t RightRearDoorStatus= 0;
	uint8_t TrunkDoorSatus = 0;
    
    static uint8_t PreDriverDoorStatus = 0xFF;
    static uint8_t PrePassengerDoorStatus= 0xFF;
    static uint8_t PreLeftRearDoorStatus = 0xFF;
    static uint8_t PreRightRearDoorStatus= 0xFF;
	static uint8_t PreTrunkDoorSatus = 0xFF;
    
	//Lamp Para
	uint8_t LowBeamStatus = 0;
	uint8_t HighBeamStatus = 0;
	uint8_t FrontFoglampStatus = 0;
	uint8_t RearFoglampStatus = 0;
	uint8_t TurnIndicatorLeftStatus = 0;
	uint8_t TurnIndicatorRightStatus = 0;
	uint8_t PositionLampStatus = 0;
	
	static uint8_t PreLowBeamStatus = 0xFF;
	static uint8_t PreHighBeamStatus = 0xFF;
	static uint8_t PreFrontFoglampStatus = 0xFF;
	static uint8_t PreRearFoglampStatus = 0xFF;
	static uint8_t PreTurnIndicatorLeftStatus = 0xFF;
	static uint8_t PreTurnIndicatorRightStatus = 0xFF;
	static uint8_t PrePositionLampStatus = 0xFF;
	
    static uint16_t task_timer_10ms = 0;
    
    
    CAN_Handler_Timer_Task();  
    CAN_Handler_Periodic_Task();
	
	if(Received_IPC_Data == 1)
	{
		if(Open_ACC_On_Request)
		{
			AIFPutHU_FrontAUTOACOnReq_Ch0(1);
			AIFPutHU_FrontACOffReq_Ch0(0);
			Open_ACC_On_Request = 0;
		}
		else if(Open_ACC_Off_Request)
		{
			AIFPutHU_FrontAUTOACOnReq_Ch0(0);
			AIFPutHU_FrontACOffReq_Ch0(1);
			Open_ACC_Off_Request = 0;
		}
		
		if(Air_AutoMode_Request)
		{
			AIFPutHU_FrontAUTOACOnReq_Ch0(Air_AutoMode_Request);
			Air_AutoMode_Request = 0;
		}
		
		if(Air_DefrostMode_Request)
		{
			AIFPutHU_ACDEFAdjustReq_Ch0(Air_DefrostMode_Request);
			Air_DefrostMode_Request = 0;
		}
		
		if(Air_CircuationMode_Request)
		{
			AIFPutDVD_Circulation_ModeReq_Ch0(Air_CircuationMode_Request);
			Air_CircuationMode_Request = 0;
		}
		
		if(Air_TempOfMain)
		{
			AIFPutDVD_ACLFTempAdjustValueReq_Ch0(Air_TempOfMain);
			Air_TempOfMain = 0;
		}
		
		if(Air_TempOfCopilot)
		{
			AIFPutHU_ACLRTempAdjustValueReq_Ch0(Air_TempOfCopilot);
			Air_TempOfCopilot = 0;
		}
		
		if(Air_Speed)
		{
			if(Air_Speed == 0x01)
			{
				Air_Speed = 1;
			}
			else if(Air_Speed == 0x02)
			{
				Air_Speed = 2;
			}
			else if(Air_Speed == 0x03)
			{
				Air_Speed = 4;
			}
			else if(Air_Speed == 0x04)
			{
				Air_Speed = 5;
			}
			else if(Air_Speed == 0x05)
			{
				Air_Speed = 6;
			}
			else if(Air_Speed == 0x06)
			{
				Air_Speed = 8;
			}
			AIFPutHU_ACFanAdjustValueReq_Ch0(Air_Speed);
			Air_Speed = 0;
		}
		
		if(Air_Direction)
		{
			AIFPutDVD_ACFrontModeAdjustReq_Ch0(Air_Direction);
			Air_Direction = 0;
		}
		
		//Received_IPC_Data = 0;
	}
	else if(Received_IPC_Data == 2)
	{
		AIFPutHU_FrontAUTOACOnReq_Ch0(0);
		AIFPutHU_FrontACOffReq_Ch0(0);
		AIFPutHU_FrontAUTOACOnReq_Ch0(0);
		AIFPutHU_ACDEFAdjustReq_Ch0(0);
		AIFPutDVD_Circulation_ModeReq_Ch0(0);
		AIFPutDVD_ACLFTempAdjustValueReq_Ch0(0);
	
		AIFPutHU_ACLRTempAdjustValueReq_Ch0(0);
	
		
		AIFPutHU_ACFanAdjustValueReq_Ch0(0);
	
		AIFPutDVD_ACFrontModeAdjustReq_Ch0(0);
		
		Received_IPC_Data = 0;
	}

    task_timer_10ms++;
    if(task_timer_10ms > 200) /*2s task*/
    {
        DriverDoorStatus = AIFGetBCM_DriverDoorStatus_Ch0();
        PassengerDoorStatus = AIFGetBCM_PassengerDoorStatus_Ch0();
        LeftRearDoorStatus = AIFGetBCM_LeftRearDoorStatus_Ch0();
        RightRearDoorStatus = AIFGetBCM_RightRearDoorStatus_Ch0();
		TrunkDoorSatus = AIFGetBCM_TrunkStatus_Ch0();
             
        
        /*Any door status changed, send lastest data to J6*/
		
        if((DriverDoorStatus != PreDriverDoorStatus))
		{			
			PreDriverDoorStatus = DriverDoorStatus;
			
			Door_Status_Buffer[0] = 0x02;
        	Door_Status_Buffer[1] = 0x00;
        	Door_Status_Buffer[2] = 0x01;
			if(DriverDoorStatus)
			{
        		Door_Status_Buffer[3] = 0x01;
			}
			else
			{
        		Door_Status_Buffer[3] = 0x00;
			}
			
        	UART2_SendData(Door_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(PassengerDoorStatus != PrePassengerDoorStatus)
		{			
			PrePassengerDoorStatus = PassengerDoorStatus;
			
			Door_Status_Buffer[0] = 0x02;
        	Door_Status_Buffer[1] = 0x00;
        	Door_Status_Buffer[2] = 0x02;
			if(PassengerDoorStatus)
			{
        		Door_Status_Buffer[3] = 0x01;
			}
			else
			{
        		Door_Status_Buffer[3] = 0x00;
			}
			
        	UART2_SendData(Door_Status_Buffer, 4); 
            Delay_ms(50);
		}
        
		if(LeftRearDoorStatus != PreLeftRearDoorStatus)
		{
			PreLeftRearDoorStatus = LeftRearDoorStatus;
			
			Door_Status_Buffer[0] = 0x02;
        	Door_Status_Buffer[1] = 0x00;
        	Door_Status_Buffer[2] = 0x03;
			if(LeftRearDoorStatus)
			{
        		Door_Status_Buffer[3] = 0x01;
			}
			else
			{
        		Door_Status_Buffer[3] = 0x00;
			}
			
        	UART2_SendData(Door_Status_Buffer, 4); 
            Delay_ms(50);
		}
		
		if(RightRearDoorStatus != PreRightRearDoorStatus)
		{			
			PreRightRearDoorStatus = RightRearDoorStatus;
			
			Door_Status_Buffer[0] = 0x02;
        	Door_Status_Buffer[1] = 0x00;
        	Door_Status_Buffer[2] = 0x04;
			if(RightRearDoorStatus)
			{
        		Door_Status_Buffer[3] = 0x01;
			}
			else
			{
        		Door_Status_Buffer[3] = 0x00;
			}
			
        	UART2_SendData(Door_Status_Buffer, 4); 
            Delay_ms(50);
		}
		
		if(TrunkDoorSatus != PreTrunkDoorSatus)
		{			
			PreTrunkDoorSatus = TrunkDoorSatus;
			
			Door_Status_Buffer[0] = 0x02;
        	Door_Status_Buffer[1] = 0x00;
        	Door_Status_Buffer[2] = 0x05;
			if(TrunkDoorSatus)
			{
        		Door_Status_Buffer[3] = 0x01;
			}
			else
			{
        		Door_Status_Buffer[3] = 0x00;
			}
			
        	UART2_SendData(Door_Status_Buffer, 4);
            Delay_ms(50); 
		}
		
		//Get lamp Status
		LowBeamStatus = AIFGetBCM_LowBeamStatus_Ch0();
		HighBeamStatus = AIFGetBCM_HighBeamStatus_Ch0();
		FrontFoglampStatus = AIFGetBCM_FrontFoglampStatus_Ch0();
		RearFoglampStatus = AIFGetBCM_RearFoglampStatus_Ch0();
		TurnIndicatorLeftStatus = AIFGetBCM_TurnIndicatorLeft_Ch0();
		TurnIndicatorRightStatus = AIFGetBCM_TurnIndicatorRight_Ch0();
		PositionLampStatus = AIFGetBCM_PositionLampStatus_Ch0();
		
		/*Any lamp status changed, send lastest data to J6*/
		if(LowBeamStatus != PreLowBeamStatus)
		{
			PreLowBeamStatus = LowBeamStatus;
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
            Lamp_Status_Buffer[1] = 0x00;
                
            Lamp_Status_Buffer[2] = 0x01;

#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = LowBeamStatus;			
		    UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(HighBeamStatus != PreHighBeamStatus)
		{
			PreHighBeamStatus = HighBeamStatus;
					
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
        	Lamp_Status_Buffer[1] = 0x00;
        	Lamp_Status_Buffer[2] = 0x02;
                
#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = HighBeamStatus;
            UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(FrontFoglampStatus != PreFrontFoglampStatus)
		{
			PreFrontFoglampStatus = FrontFoglampStatus;
					
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
        	Lamp_Status_Buffer[1] = 0x00;
        	Lamp_Status_Buffer[2] = 0x03;

#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = FrontFoglampStatus;
            UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(RearFoglampStatus != PreRearFoglampStatus)
		{
			PreRearFoglampStatus = RearFoglampStatus;
					
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
        	Lamp_Status_Buffer[1] = 0x00;
        	Lamp_Status_Buffer[2] = 0x04;

#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = RearFoglampStatus;
            UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(TurnIndicatorLeftStatus != PreTurnIndicatorLeftStatus)
		{
			PreTurnIndicatorLeftStatus = TurnIndicatorLeftStatus;
					
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
        	Lamp_Status_Buffer[1] = 0x00;
        	Lamp_Status_Buffer[2] = 0x05;

#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = TurnIndicatorLeftStatus;
            UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(TurnIndicatorRightStatus != PreTurnIndicatorRightStatus)
		{
			PreTurnIndicatorRightStatus = TurnIndicatorRightStatus;
					
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
        	Lamp_Status_Buffer[1] = 0x00;
        	Lamp_Status_Buffer[2] = 0x06;

#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = TurnIndicatorRightStatus;
            UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
		if(PositionLampStatus != PrePositionLampStatus)
		{
			PrePositionLampStatus = PositionLampStatus;
					
#ifndef 	UI_UNFINISHED				
			Lamp_Status_Buffer[0] = 0x03;
#else
			Lamp_Status_Buffer[0] = 0x02;
#endif
        	Lamp_Status_Buffer[1] = 0x00;
        	Lamp_Status_Buffer[2] = 0x07;

#ifdef 	    UI_UNFINISHED
        	Lamp_Status_Buffer[2] += 0x10;
#endif
            Lamp_Status_Buffer[3] = PositionLampStatus;
            UART2_SendData(Lamp_Status_Buffer, 4);
            Delay_ms(50);
		}
		
        task_timer_10ms = 0;
    }
    
    //ACC_Status = Get_ACC_Status();
}

void CAN_TJA1055_Init(void)
{
   /*CAN_EN*/
   //PM8_bit.no6=0;
   //P8_bit.no6=1;
   Dio_WriteChannel(DIO_PIN_P86, DIO_HIGH);
   /*CAN_STB*/
   //PM5_bit.no3=0;
   //P5_bit.no3=1;
   //Dio_WriteChannel(DIO_PIN_P53, DIO_HIGH);
   Dio_WriteChannel(DIO_PIN_P52, DIO_HIGH);

}
void Init_CAN_Transmit_Signal_Value(void)
{
   AIFPutHU_FrontAUTOACOnReq_Ch0(0);
   AIFPutHU_FrontACOffReq_Ch0(0);
   //AIFPutHU_ACreq_Ch0(1);
   
}
void CCA_Init(void)
{
   CAN_TJA1055_Init();
   Init_CAN_Transmit_Signal_Value();
}


