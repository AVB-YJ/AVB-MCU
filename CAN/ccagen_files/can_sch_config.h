/*******************************************************************************

  Copyright 2014  Technologies, Inc., All Rights Reserved             
  Project Name : cca
  ECU :  HMI
  File Name:  can_sch_config.h                                          
  File Description:
  Contains Macros related to Transmit Message Types        

*******************************************************************************/

#ifndef CAN_SCHEDULER_CONFIG_H
#define CAN_SCHEDULER_CONFIG_H



/*******************************************************************************

Note: Descriptions about the different message types are provided in the 
User Manual (Scheduler section)
*******************************************************************************/

/*******************************************************************************

             CONFIGURATION TO SELECT TX MESSAGE TYPES 

*******************************************************************************/

/**************************************************************************
             CONFIGURATION FOR ON_EVENT_MSG
**************************************************************************/
#define ON_EVENT_MSG_SUPPORTED
#ifdef ON_EVENT_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_ON_EVENT_MSG_CH0 1
#define NUM_OF_ON_EVENT_MSG_CH1 0
#define NUM_OF_ON_EVENT_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_ON_EVENT_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_ON_EVENT_MSG_SUPPORTED

#endif  /* Message Type: ON_EVENT_MSG */

/**************************************************************************
             CONFIGURATION FOR ON_EVENT_WITH_MIN_UPDATE_TIME_MSG
**************************************************************************/
#undef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 0
#define NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 0
#define NUM_OF_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED

#endif  /* Message Type: ON_EVENT_WITH_MIN_UPDATE_TIME_MSG */

/**************************************************************************
             CONFIGURATION FOR N_TIMES_ON_EVENT_MSG
**************************************************************************/
#undef N_TIMES_ON_EVENT_MSG_SUPPORTED
#ifdef N_TIMES_ON_EVENT_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_N_TIMES_ON_EVENT_MSG_CH0 0
#define NUM_OF_N_TIMES_ON_EVENT_MSG_CH1 0
#define NUM_OF_N_TIMES_ON_EVENT_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_MSG_SUPPORTED

#endif  /* Message Type: N_TIMES_ON_EVENT_MSG */

/**************************************************************************
             CONFIGURATION FOR N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG 
**************************************************************************/
#undef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
#ifdef N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 0
#define NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 0
#define NUM_OF_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED

#endif  /* Message Type: N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG  */

/**************************************************************************
             CONFIGURATION FOR CYCLIC_ON_INIT_MSG
**************************************************************************/
#define CYCLIC_ON_INIT_MSG_SUPPORTED
#ifdef CYCLIC_ON_INIT_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_CYCLIC_ON_INIT_MSG_CH0 2
#define NUM_OF_CYCLIC_ON_INIT_MSG_CH1 0
#define NUM_OF_CYCLIC_ON_INIT_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_CYCLIC_ON_INIT_MSG_SUPPORTED

#endif  /* Message Type: CYCLIC_ON_INIT_MSG */

/**************************************************************************
             CONFIGURATION FOR CYCLIC_ON_REQUEST_MSG  
**************************************************************************/
#undef CYCLIC_ON_REQUEST_MSG_SUPPORTED
#ifdef CYCLIC_ON_REQUEST_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_CYCLIC_ON_REQUEST_MSG_CH0 0
#define NUM_OF_CYCLIC_ON_REQUEST_MSG_CH1 0
#define NUM_OF_CYCLIC_ON_REQUEST_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_CYCLIC_ON_REQUEST_MSG_SUPPORTED

#endif  /* Message Type: CYCLIC_ON_REQUEST_MSG   */

/**************************************************************************
             CONFIGURATION FOR CYCLIC_AND_ON_EVENT_MSG 
**************************************************************************/
#undef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
#ifdef CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH0 0
#define NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH1 0
#define NUM_OF_CYCLIC_AND_ON_EVENT_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_MSG_SUPPORTED

#endif  /* Message Type: CYCLIC_AND_ON_EVENT_MSG  */

/**************************************************************************
             CONFIGURATION FOR CYCLIC_AND_ON_EVENT_MSG  
**************************************************************************/
#undef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
#ifdef CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH0 0
#define NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH1 0
#define NUM_OF_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED

#endif  /* Message Type: CYCLIC_AND_ON_EVENT_MSG   */

/**************************************************************************
             CONFIGURATION FOR BAF_MSG
**************************************************************************/
#undef BAF_MSG_SUPPORTED
#ifdef BAF_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_BAF_MSG_CH0 0
#define NUM_OF_BAF_MSG_CH1 0
#define NUM_OF_BAF_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_BAF_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_BAF_MSG_SUPPORTED

#endif  /* Message Type: BAF_MSG */

/**************************************************************************
             CONFIGURATION FOR FAST_MSG  
**************************************************************************/
#undef FAST_MSG_SUPPORTED
#ifdef FAST_MSG_SUPPORTED
/**************************************************************************
             CONFIGURATION FOR NUMBER OF MESSAGES ON EACH CHANNEL    
**************************************************************************/
#define NUM_OF_FAST_MSG_CH0 0
#define NUM_OF_FAST_MSG_CH1 0
#define NUM_OF_FAST_MSG_CH2 0
/**************************************************************************
              CONFIGURATION FOR TIMEOUT SUPPORT   
**************************************************************************/
#undef TIMEOUT_FOR_FAST_MSG_SUPPORTED
/**************************************************************************
              CONFIGURATION FOR STARTUP DELAY SUPPORT 
**************************************************************************/
#undef STARTUP_DELAY_FOR_FAST_MSG_SUPPORTED

#endif  /* Message Type: FAST_MSG   */


typedef enum
{
#ifdef ON_EVENT_MSG_SUPPORTED  
ON_EVENT,
#endif 
#ifdef ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
ON_EVENT_WITH_MIN_UPDATE_TIME,
#endif 
#ifdef  N_TIMES_ON_EVENT_MSG_SUPPORTED
N_TIMES_ON_EVENT,
#endif
#ifdef  N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
N_TIMES_ON_EVENT_WITH_MIN_UPDATE_TIME,
#endif 
#ifdef  CYCLIC_ON_INIT_MSG_SUPPORTED
CYCLIC_ON_INIT,
#endif 
#ifdef  CYCLIC_ON_REQUEST_MSG_SUPPORTED
CYCLIC_ON_REQUEST,
#endif 
#ifdef  CYCLIC_AND_ON_EVENT_MSG_SUPPORTED
CYCLIC_AND_ON_EVENT,
#endif
#ifdef  CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME_MSG_SUPPORTED
CYCLIC_AND_ON_EVENT_WITH_MIN_UPDATE_TIME,
#endif
#ifdef  BAF_MSG_SUPPORTED
BAF,
#endif
#ifdef  FAST_MSG_SUPPORTED
FAST
#endif 
} Message_Transmission_Mode_T;

/*******************************************************************************

              CONFIGURATION TO SELECT TIMEOUT MONITORING FOR RX MESSAGES  

*******************************************************************************/

#undef TIMEOUT_FOR_RX_MSG_SUPPORTED

#endif  /* End CAN_SCHEDULER_CONFIG_H */


 /******************************************************************************* 
                           REVISION HISTORY                                       
 ******************************************************************************* 
  Rev      Date            S/W Engineer                Description                 
 ******************************************************************************* 
   1      15/10/2014
 ********************************************************************************/

