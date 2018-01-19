/****************************************************************************\
 * FILE: ivn_faw_nm.c
 ****************************************************************************
 * Copyright 2007  Technologies, Inc., All Rights Reserved.
 *  Confidential
 ****************************************************************************
****************************************************************************
*
*	C %name:		ivn_faw_nm.c %
*	Instance:		tci_ibs2_1
*	Description:	
*	%created_by:	wzqndv %
*	%date_created:	Fri May  9 19:55:53 2014 %
*
****************************************************************************/
/****************************************************************************
 *
 * DESCRIPTION:
 *   Description of file's purpose.
 *
 * ABBREVIATIONS:
 *   List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *
 *   Requirements Document(s):
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   None.
 *
\*****************************************************************************/

/*****************************************************************************
 * Include Files
 ****************************************************************************/
#include "can_aif_rx.h"
#include "can_aif_tx.h"
#include "ivn_faw_nm.h"
#include "ivn_faw_nm_config.h"
#include "can_handler.h"
#include "can_aif_config.h"


/*****************************************************************************
 * #define Constants
 ****************************************************************************/


/*          IGNITION VOLTAGE         */


#ifdef FOUR_BYTE_DTC_STATUS_FLAG
   /* constant variable to set the particular bits */
   const canuint32_t NM_Bit_Mask_Set[] = 
   {
     0x00000001, 0x00000002, 0x00000004, 0x00000008, 
     0x00000010, 0x00000020, 0x00000040, 0x00000080,
     0x00000100, 0x00000200, 0x00000400, 0x00000800, 
     0x00001000, 0x00002000, 0x00004000, 0x00008000,

     0x00010000, 0x00020000, 0x00040000, 0x00080000, 
     0x00100000, 0x00200000, 0x00400000, 0x00800000,
     0x01000000, 0x02000000, 0x04000000, 0x08000000, 
     0x10000000, 0x20000000, 0x40000000, 0x80000000,
   };
#else 
   /* constant variable to set the particular bits */
   const canuint16_t NM_Bit_Mask_Set[] = 
   {
     0x0001, 0x0002, 0x0004, 0x0008, 
     0x0010, 0x0020, 0x0040, 0x0080,
     0x0100, 0x0200, 0x0400, 0x0800, 
     0x1000, 0x2000, 0x4000, 0x8000,
   };
#endif


/*****************************************************************************
 * Local Type Declarations
 ****************************************************************************/


/*****************************************************************************
 * Global Variables
 ****************************************************************************/



/*****************************************************************************
 * File Scope Variables
 ****************************************************************************/
/* Variable to indicate stop/start monitoring due to voltages */
//static canuint8_t NM_Ign_Vol_Abn_Stop_Mon;
/* variable to indicate bus off state */
/* variable to hold the NM state */
static NM_State_T Nm_State;
/* variable to hold NM ignition voltage state */
//static NM_Ign_Vol_State_T Nm_Ign_Vol_Monitoring_State;
/*variable to hold the bus off recovery state  */
static NM_Bus_Off_Rec_State_T Nm_Bus_Off_Rec_State;
/* varaible to hold the bus off state */
canuint8_t Nm_Bus_Off_Indication_Flag;
static canuint8_t Nm_Bus_Off_Indication_To_CCA;
canuint8_t Nm_Bus_Off_Indication_To_DTC_Counter;
can_boolean_t bus_off_Set_DTC=CAN_cbFALSE;
/*static canuint16_t Nm_Ign_Wakeup_Timer;*/
/*static canuint16_t Nm_Ign_Under_Vol_Rec_Timer;*/
/*static canuint16_t Nm_Ign_Over_Vol_Rec_Timer;*/
static canuint16_t Nm_Bus_Off_Recovery_Timer;
static canuint8_t  Nm_Num_Of_Quick_Rec_Attempts;

static canbool8_t Nm_busoff_temp_flag;


/*static NM_Ign_Vol_T prev_state=0;*/

#ifdef FOUR_BYTE_DTC_STATUS_FLAG
  /* variable to track the DTC Logging */
  static canuint32_t Nm_Msg_Mon_Dtc_Status_Word;
#else 
  /* variable to track the DTC Logging */
  static canuint16_t Nm_Msg_Mon_Dtc_Status_Word;

#endif


/*****************************************************************************
 * File Scope Function Prototypes
 ****************************************************************************/
static void NM_Bus_Off_Recovery_Process(void);

/*****************************************************************************
 * Local Inlines/ Function-like Macros
 ****************************************************************************/

/*****************************************************************************
 * Function Definition
 ****************************************************************************/

/******************************************************************************
 * FUNCTION          :   NM_Init                                                     
 ******************************************************************************
 * ABSTRACT          :	To initilize the NM related variables. 
 *
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	during Init process only.
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Init(void)
{
  
  //Nm_State = (NM_State_T)NM_OFF;
  Nm_State = (NM_State_T)NM_INIT;
  Nm_Bus_Off_Rec_State = (NM_Bus_Off_Rec_State_T)NM_BUS_OFF_QUICK_RECOVER_STATE;
  Nm_Bus_Off_Indication_Flag = (canuint8_t)0; 
  Nm_Bus_Off_Indication_To_CCA = (canuint8_t)0;
  Nm_Num_Of_Quick_Rec_Attempts = (canuint8_t)0;
  
  #ifdef FOUR_BYTE_DTC_STATUS_FLAG
    Nm_Msg_Mon_Dtc_Status_Word = (canuint32_t)0;
  #else
    Nm_Msg_Mon_Dtc_Status_Word = (canuint16_t)0;
  #endif
  
  //NM_Init_Msg_Mon();
  /*Deleted NM read variables from EE. This is done as a common function
    (on KAM failure) to init the RAM shadow from EE*/

   NM_Initialize_CAN_Driver();

   Nm_busoff_temp_flag = cbFALSE;
}

/******************************************************************************
 * FUNCTION          :   NM_Periodic_Task                                                     
 ******************************************************************************
 * ABSTRACT          :	This is the periodic taskn function of NM called by the 
 *						comm handler modules in OS periodic task.
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	10 ms.
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
//ya rewrite this with only three states , remove #if 0
void NM_Periodic_Task(void)
{
  if(1)
  {
    switch(Nm_State)
    {
      case NM_OFF:
      /* If application needs that the CAN driver to be initialised by NM
	  then use this state*/      
      break;

      case NM_INIT:
      NM_Bus_Off_Recovery_Process();
	  
      break;

      default:
      break;
    }
  }
  else 
  {
    if(Nm_State != NM_OFF)
    {
       Appl_Network_Power_Down();
    } 
    Nm_State = NM_OFF;

  }

}


/******************************************************************************
 * FUNCTION          :   NM_Bus_Off_Recovery_Process                                                    
 ******************************************************************************
 * ABSTRACT          :	To initilize the NM related variables. 
 *
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	during Init process only.
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
static void NM_Bus_Off_Recovery_Process(void)
{
  if(Nm_Bus_Off_Indication_Flag == (canuint8_t)cbTRUE)
  {  
     switch(Nm_Bus_Off_Rec_State)
     {
       case NM_BUS_OFF_QUICK_RECOVER_STATE:
           Appl_Bus_Off_Notify();
           //NM_Set_DTC(IC_BUS_OFF_DTC, cbFALSE, 0xff);
            Nm_Bus_Off_Recovery_Timer = (canuint16_t)(NM_BUS_OFF_QUICK_RECOVERY_TIME ) - 1; 
          // Nm_Bus_Off_Recovery_Timer = (canuint16_t)(Bus_Off_Quick_Rec_Timer );
           Nm_Bus_Off_Rec_State = NM_BUS_OFF_QUICK_RECOVER_PROCESS_STATE;
		//   NM_BusOff_Initialize_CAN_Handler();
		//	  Nm_busoff_temp_flag = cbFALSE;
       break;

       case NM_BUS_OFF_QUICK_RECOVER_PROCESS_STATE:
           if(0 < Nm_Bus_Off_Recovery_Timer)
           {
		      Nm_Bus_Off_Recovery_Timer --;
           }
           if( Nm_busoff_temp_flag != cbFALSE )
           {
              if(0 == Nm_Bus_Off_Recovery_Timer)
              {
                 Nm_busoff_temp_flag = cbFALSE;
                 #ifdef CAN_TX_MSG_SUPPORTED
                 Nm_Bus_Off_Indication_Flag = (canuint8_t)cbFALSE;
                  AIF_Set_Tx_Active(0);
                 #endif
                 Nm_Num_Of_Quick_Rec_Attempts++;
                 if(NM_MAX_NUMBER_OF_BUS_OFF_QUICK_RECOVERY_ATTEMPTS == Nm_Num_Of_Quick_Rec_Attempts)
                // if(Num_Of_Quick_Rec_Attempts == Nm_Num_Of_Quick_Rec_Attempts)
                 {
                    Nm_Bus_Off_Rec_State = NM_BUS_OFF_SLOW_RECOVER_STATE;
                    Nm_Num_Of_Quick_Rec_Attempts = (canuint8_t)0;
                 }
                 else
                 {
                   // Nm_Bus_Off_Recovery_Timer = (canuint16_t)(NM_BUS_OFF_QUICK_RECOVERY_TIME ); 
                  //  Nm_Bus_Off_Recovery_Timer = (canuint16_t)(Bus_Off_Quick_Rec_Timer );
                 }
              }
           }
       break;

       case NM_BUS_OFF_SLOW_RECOVER_STATE:
            Nm_Bus_Off_Recovery_Timer = (canuint16_t)(NM_BUS_OFF_SLOW_RECOVERY_TIME ) - 1; 

           //Nm_Bus_Off_Recovery_Timer = (canuint16_t)(Bus_Off_Slow_Rec_Timer );
           Nm_Bus_Off_Rec_State = NM_BUS_OFF_SLOW_RECOVER_PROCESS_STATE;
       break;

       case NM_BUS_OFF_SLOW_RECOVER_PROCESS_STATE:
           if(0 < Nm_Bus_Off_Recovery_Timer)
           {
		     Nm_Bus_Off_Recovery_Timer --;
           }
           

	       if( (Nm_Bus_Off_Recovery_Timer == (canuint16_t)0) &&
		       (Nm_busoff_temp_flag != cbFALSE) )
           {
			  Nm_busoff_temp_flag = cbFALSE;
			  Nm_Bus_Off_Indication_Flag = (canuint8_t)cbFALSE;
              #ifdef CAN_TX_MSG_SUPPORTED
               AIF_Set_Tx_Active(0);
              #endif
           }
       break;

       case NM_BUS_OFF_RECOVERED_STATE:
           Nm_Num_Of_Quick_Rec_Attempts = (canuint8_t)0;
           Nm_Bus_Off_Indication_Flag = (canuint8_t)cbFALSE;
           Nm_Bus_Off_Rec_State = NM_BUS_OFF_QUICK_RECOVER_STATE;
	       Nm_busoff_temp_flag = cbFALSE;
       break;

       default:
       break;
     }
  }
}

/******************************************************************************
 * FUNCTION          :    Get_NM_Busoff_Indication                                                     
 ******************************************************************************
 * ABSTRACT          :	To give the buss off status flag to CCA. 
 *
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	application call rate
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
canuint8_t Get_NM_Busoff_Indication(void)
{
   return(Nm_Bus_Off_Indication_To_CCA);
}
/******************************************************************************
 * FUNCTION          :    Get_NM_Busoff_Indication_To_Appl                                                     
 ******************************************************************************
 * ABSTRACT          :	To give the buss off status flag to appl. 
 *
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	application call rate.
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
canuint8_t Get_NM_Busoff_Indication_To_Appl(void)
{
   return(Nm_Bus_Off_Indication_Flag);
}

/******************************************************************************
 * FUNCTION          :   NM_Bus_Off_Indication                                                    
 ******************************************************************************
 * ABSTRACT          :	To initilize the NM related variables. 
 *
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	during Init process only.
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Bus_Off_Indication(void)
{
  Nm_Bus_Off_Indication_To_CCA = cbTRUE;
  Nm_Bus_Off_Indication_Flag = cbTRUE;

  Nm_busoff_temp_flag  = cbTRUE;
  

  if( NM_BUS_OFF_QUICK_RECOVER_PROCESS_STATE==Nm_Bus_Off_Rec_State )
  {
    Nm_Bus_Off_Recovery_Timer = (canuint16_t)(NM_BUS_OFF_QUICK_RECOVERY_TIME ); 
  }
  else if( NM_BUS_OFF_SLOW_RECOVER_PROCESS_STATE==Nm_Bus_Off_Rec_State )
  {
  	Nm_Bus_Off_Recovery_Timer = (canuint16_t)(NM_BUS_OFF_SLOW_RECOVERY_TIME ); 
  }
  else
  {
  }
 
  #ifdef CAN_CH0_SELECTED
     CAN_Handler_Shut_Down(0);
  #endif
  #ifdef CAN_CH1_SELECTED
     CAN_Handler_Shut_Down(1);
  #endif

  NM_BusOff_Initialize_CAN_Handler();
  NM_Disable_Communication();
}

/******************************************************************************
 * FUNCTION          :   NM_Bus_Off_Recovered                                                    
 ******************************************************************************
 * ABSTRACT          :	To initilize the NM related variables. 
 *
 * RETURN PARAMETERS :	None
 *
 * PARAMETERS        :	None
 *
 * CALLING RATE     :	during Init process only.
 *
 * TRACEABILITY     :
 *
 ******************************************************************************/
void NM_Bus_Off_Recovered(void)
{
   Nm_Bus_Off_Indication_To_CCA = cbFALSE;

   Nm_Bus_Off_Indication_Flag = cbTRUE;
   
   Nm_Bus_Off_Rec_State = NM_BUS_OFF_RECOVERED_STATE;
      
       //Nm_Bus_Off_Recovery_Timer =0; 
      //Nm_Bus_Off_Recovery_Timer = (canuint16_t)(Bus_Off_Rec_Timer );
   AIF_Set_Rx_Active(0);
   #ifdef CAN_TX_MSG_SUPPORTED
    AIF_Set_Tx_Active(0);
   #endif

   Nm_Bus_Off_Indication_To_DTC_Counter = 0;
   bus_off_Set_DTC = CAN_cbFALSE;
}