#ifndef _CCA_H_
#define _CCA_H_


//#include    "CCA_Diag_Handle.h"
#include  "can_handler.h"
#include    "Can_aif_rx.h"
#include    "can_aif_config.h"
#include    "can_aif_tx.h"
#include    "Key_scan.h"

/**********************************************************************
 * Global Constant and Macro Definitions using #define                        
 *********************************************************************/


/**********************************************************************
 * Global Enumerations and Structures and Typedefs                          
 *********************************************************************/

/**********************************************************************
 * Global Variable extern Declarations                               
 *********************************************************************/
extern bool Open_ACC_On_Request;
extern bool Open_ACC_Off_Request;
extern bool Air_AutoMode_Request;
extern canuint8_t Air_DefrostMode_Request;
extern canuint8_t Air_CircuationMode_Request;
extern canuint8_t Air_TempOfMain;
extern canuint8_t Air_TempOfCopilot;
extern canuint8_t Air_Speed;
extern canuint8_t Air_Direction;
extern canuint8_t Received_IPC_Data;

/**********************************************************************
 * Global Function Prototypes                                               
 *********************************************************************/
extern void CCA_Task (void);
void CCA_Task_Start(void);
void CCA_Init(void);
//extern void CCA_Key_WriteBit(SW_TYPE Key_Type, canuint8_t Value);

extern canuint8_t ACC_Status;
extern canuint8_t Door_Status;

/* Mask bits for Door Status message byte */
#define DRIVER_DOOR_STATUS_MASK         0x01
#define PASSENGER_DOOR_STATUS_MASK    	0x02
#define LEFTREAR_DOOR_STATUS_MASK       0x04
#define RIGHTREAR_DOOR_STATUS_MASK     	0x08

#endif

