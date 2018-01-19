/*============================================================================*\
* Description: This file contains the functions for NVRAM manager
*
* Traces to: 10024438_SW_SDD_00001366
*
* Applicable Standards (in order of precedence: highest first):
*     SW REF 264.15D "DE Systems C Coding Standards" dated 12-MAR-06
*
* Deviations from Delco C Coding standards:
*   1. C46 - Abbreviations are not documented in this source file.
*
*   2. C54 - Function header block is placed at the beginning of
*      function definition instead before function proto type
*      declaration.
*
*   4. C60 - The function is pre-emptible or re-entrant is not
*      applicable to this program.
\*============================================================================
* Module Name:     NVM.c
* Created By:      KS
* Created Date:    19-Apr-2011
* %version:        15.1.10 %
* %cvtype:         csrc %
* %instance:       ctc_aud_3 %
* %derived_by:     rzlw3b %
* %date_modified:   %
*------------------------------------------------------------------------------*/
/*============================================================================*\
*
* Preprocessor #include directive(s)
*
\*============================================================================*/
#include "OS_Task.h"
#include "NVM.h"        /* For Type definitions and prototye checking */
//#include "WdgM.h"
#include "SchM.h"
#include "string.h"     /* to remove !!!!!!!*/


/*============================================================================*\
*
* Local preprocessor #define constants (object-like macros)
*
\*============================================================================*/
#define DATA_CRC_SIZE              (uint8_t)(2)

#define SHIFT_CONST_VALUE          (0x08U)

#define NO_OF_REDUNT_JOB           2
#define NO_OF_DUP1_REDUNT_JOB      1
/* Queue size is required NVM_MAX_BLOCK_ID + 1, but extra space is added 
 * as per requirement for future use.
 */
#define NVM_JOB_QUEUE_SIZE         (NVM_MAX_B81_ID + 5) 

#define NVM_ECU_INTFAULT_DEG_ID    (uint8_t)0x7FU

#define NVM_EEL_CMD_FORMAT         (uint8_t)0x05U
#define NVM_RCS_START              (uint8_t)0x01U
/* EEL identifier range is 1 to 36 and block id range is 0 to 35.
 * So max eel identifier is NVM_MAX_BLOCK_ID.
 */
#define NVM_MAX_EEL_IDENTIFIER     (NVM_MAX_B81_ID)
#define NVM_MAX_ACCESS_TIME 1000 //ms

#define LED_CAL_VALID_BIT 18
#define LED_CAL_DATA_SIZE 18

/* #define NVM_TEST_CANCEL_ALL  */   /* Enable this macro to test Nvm_Cancel_All() */
/*============================================================================*\
*
*  Constant Declarations
*
\*============================================================================*/
/*============================================================================*\
*
* Local type declarations (enum, struct, union, typedef), mixed case
*
\*============================================================================*/

#ifdef PROJ_DEBUG_MODE
typedef struct
{
   uint16_t NVM_curr_counter;
   uint16_t NVM_prev_counter;
   uint16_t NVM_diff_time;
   uint16_t NVM_max_time;
} NVM_time_T;
NVM_time_T NVM_module_time;
NVM_time_T NVM_RestoreAll_time;
#endif

typedef struct
{
   uint8_t RW_Flag;
   uint8_t EEL_ShutDownFlag;
   eel_command_t EEL_Command;
   uint8_t Restore_Default;
}NVM_Eel_Handler_T;

typedef enum  _CMD_STAT
{
   NVM_CMD_BUSY,
   NVM_CMD_ERR,
   NVM_CMD_SUCCESSFUL
}NVM_CMD_STATUS;
/*============================================================================*\
*
* Exported object definitions, mixed case
*
\*============================================================================*/
//bool_t NVM_Inhibition = FALSE;
/* To test Nvm_cancel All function */
#ifdef NVM_TEST_CANCEL_ALL    
uint8_t Que_Loc = 0;
static void NVM_Test_Function(void);
#endif

/*============================================================================*\
*
* Local object definitions, lower case
*
\*============================================================================*/
/* NVM_Manager Initialization status */
//static uint8_t NVM_Init_Status; 
/* State of the Standard queue */         
//static uint8_t NVM_Job_Queue_State;
/* result of the requested Job */
//static NVM_Mem_JobResult_T NVM_EEL_Drv_JobResult;  
/* Queue for jobs */      
//static NVM_JobRequest_T NVM_Job_Queue[NVM_JOB_QUEUE_SIZE];
/* Job Status */ 
static NVM_Admin_Block_T NVM_Admin_Block_Status[NVM_MAX_B81_ID]; 
/* Substatus of the single block request */
//static NVM_CmdStatus_T NVM_Block_Status; 
/* To maintain queue index */
//static uint8_t NVM_Push_Wr_Index;
//static uint8_t NVM_Pop_Rd_Index;
/* Updates the EEL job status and Command */
static NVM_Eel_Handler_T NVM_Eel_Handler;
/* Updates the EEL job request parametes */
static eel_request_t NVM_Eel_Request;


//need block id, block size, mem_pos, sub_block_size, need chksum
static  NVM_Block_Info_Config_T NVM_Block_Config[NVM_MAX_B81_ID]=
{
  //block 1: mft reserved1
  {0, FALSE},
};
/*============================================================================*\
*
* Local function prototypes, mixed case
*
\*============================================================================*/
static void NVM_EEL_Error_Handler(eel_status_t nvm_eel_status);
static void NVM_EEL_InitStartup(void);
/* To compare Two blockS of data */
static void NVM_Memory_Copy(uint8_t dest_ptr[], const uint8_t src_ptr[],uint8_t length);
static void NVM_ReadAll(void);
static NVM_Mem_JobResult_T NVM_Restore_Default(uint8_t BlockId);
//static NVM_Mem_JobResult_T NVM_Direct_Write(uint8_t block_id, const uint8_t *NVM_DstPtr, uint8_t bytes)
static NVM_Mem_JobResult_T NVM_Direct_Read_By_ID(uint8_t block_id, uint8_t *);
static NVM_Mem_JobResult_T NVM_Direct_Write_By_ID(uint8_t block_id);
static NVM_CMD_STATUS NVM_CommandExecute_Polling(void);
static NVM_Mem_Status_T NVM_Get_EEL_Status(void);
static void NVM_EEL_Error_Handler_Ext(eel_status_t nvm_eel_status);


/*============================================================================*\
*
* Local inline function definitions and #define function-like macros,
* mixed case
*
\*============================================================================*/

/*===========================================================================*\
*  Function definitions
\*===========================================================================*/

/*==============================================================================
* FUNCTION: NVM_EEPROM_Init
*===============================================================================
* Return Value:
*    None
* Parameters:
*    None
*
*
*  External variables: None
* 
*  File scope variables: None
*
* Description:
*  Initialize the Data flash Driver, added for ICS
*=============================================================================*/
static bool_t NVM_EEPROM_Init(void)
{
  fal_status_t fdl_result;
  eel_status_t ee_result;

  WdgM_Refresh(); //feed dog because the  process need more time to run

  fdl_result = FAL_Init(&fal_descriptor_str);
   // Initialize the Data flash Driver 
   if(fdl_result!= FAL_OK)
   {
      return FALSE;
   }
   FAL_Open();
   
   ee_result = EEL_Init();
   if(ee_result!= EEL_OK)
   {
      return FALSE;
   }
   EEL_Open();

   
   return TRUE;
}
/*==============================================================================
* FUNCTION: NVM_Init
*===============================================================================
* Return Value:
*    None
* Parameters:
*    None
*
* External references: EEL_Open
*
*  External variables: None
* 
*  File scope variables: None
*
* Description:
*  Initialise NVM Job queue and global variables
*=============================================================================*/
void NVM_Init(void)
{
   //uint8_t index;
   bool_t EEPROM_init= FALSE;
#if 0   
   NVM_Mem_JobResult_T  test_result = NVM_MEM_JOB_OK;
   uint8_t test_buffer[10];// = {0,1,2,3,4,5,6,7,8,9};
   uint8_t test_r_buffer[10];
#endif   

   //added for ICS
   if(NVM_EEPROM_Init())
   {
      EEPROM_init = TRUE;
   }
   
   //NVM_Block_Status = NVM_REQ_COMPLETED;
   //NVM_Job_Queue_State = NVM_QUEUE_EMPTY;
   //NVM_Push_Wr_Index = 0;
   //NVM_Pop_Rd_Index = 0;
   /* EEL driver job result is initilised to job pending status */
   //NVM_EEL_Drv_JobResult = NVM_MEM_JOB_PENDING;
   //NVM_Eel_Handler.EEL_Command = EEL_CMD_UNDEFINED;
   NVM_Eel_Handler.RW_Flag = FALSE;
   /* To open access to the EEL-pool EEL_Open() function has to be called */
   //EEL_Open();
   /* opens the access to the EEL data */
   if(EEPROM_init)
   {
       NVM_EEL_InitStartup();
   }
   else
   {
       //handler: carryout the format
       NVM_EEL_Error_Handler_Ext(EEL_ERR_CONFIGURATION);
   }
   /* updated status flag Nvm is initialised */
   if(NVM_Eel_Handler.RW_Flag)
   {
       NVM_ReadAll();
   }
#if 0
   //test code...
   if(NVM_Eel_Handler.RW_Flag)
   {
      test_result = NVM_Direct_Read2(0x01, test_buffer);
      if(test_result == NVM_MEM_JOB_OK)
      {
          test_result = NVM_Direct_Write(0x01, test_buffer);
      }
      if(test_result == NVM_MEM_JOB_OK)
      {
          test_result = NVM_Direct_Read2(0x01, test_buffer);
      }
      if(test_result == NVM_MEM_JOB_OK)
      {
          __no_operation();
      }
      else
      {
          __no_operation();
      }
   }
   #endif
}

/*==============================================================================
* FUNCTION: NVM_Start
*===============================================================================
* Return Value:
*    None
* Parameters:
*    None
*
* External references: OS_ActivateTask
*
*  External variables: None

*  File scope variables: None
*
* Description:
*  Start periodic task
*=============================================================================*/
void NVM_Start(void)
{
   /* Activate NVM Task */
   //(void)OS_ActivateTask(OS_Task_Memory, Os_Task_Memory_Offset, Os_Task_Memory_Period);

}

/*==============================================================================
* FUNCTION: NVM_Task
*===============================================================================
* Return Value:
*    None
* Parameters:
*    None
*
* External references: None
*
*  External variables: None
*
*  File scope variables: NVM_Init_Status,NVM_Eel_Handler
*
* Description:
*  This function is called cyclically every 5ms from OS, It checks job in the 
*  queue, if Any Job is pending it is serviced. If there is no job, it does 
*  nothing. 
*=============================================================================*/
void NVM_Task(void)
{
   //static NVM_JobRequest_T *NVM_Current_Job_Details = NVM_NULL_PTR;
   //NVM_Mem_Status_T nvm_eel_status;
   
   #ifdef PROJ_DEBUG_MODE
   NVM_module_time.NVM_prev_counter = OS_GetFreeRunCounter();
   #endif

#if 0   //not used Job queue
   /* NVM should be initialised before */
   if ( (NVM_INITIALISED == NVM_Init_Status) && (TRUE == NVM_Eel_Handler.RW_Flag))
   {  
      nvm_eel_status = NVM_Get_EEL_Status();
      /* Check the previous job is completed and memory is idle then get job from queue */
      if ((NVM_REQ_COMPLETED == NVM_Block_Status) && (NVM_MEM_IDLE == nvm_eel_status))
      {
         /* Get the first pending Job from the queue */
         NVM_Current_Job_Details = NVM_Get_Job();
      }
      else
      {
         /* Do Nothing */
      }
      /* check if pointer is not Null pointer */
      if (NVM_NULL_PTR != NVM_Current_Job_Details)
      {
         if (NVM_Current_Job_Details->blockid < NVM_MAX_B81_ID)
         {
            switch (NVM_Current_Job_Details->serviceid)
            {
               /* Request for Read EEL block */
               case (uint8_t)NVM_READ_BLOCK:
                  if (NVM_REQ_DONE != NVM_Block_Status)
                  {
                     NVM_Block_Status = NVM_Job_Read(NVM_Current_Job_Details->blockid);
                  }
                  else
                  {
                     NVM_Block_Status = NVM_REQ_COMPLETED;
                  }
                  break;
               /* Request for write EEL block */
               case (uint8_t)NVM_WRITE_BLOCK:
                  if (NVM_REQ_DONE != NVM_Block_Status)
                  {
                     NVM_Block_Status = NVM_Job_Write(NVM_Current_Job_Details->blockid);
                  }
                  else
                  {
                     NVM_Block_Status = NVM_REQ_COMPLETED;
                  }
                  break;

               default:
                  break;
            }
         }
         else
         {
            /* Do Nothing */
         }
      }
      else
      {
         /* Do Nothing */
      }
   }
   else
   {
      /* Do Nothing */
   }
#endif
   
   #ifdef PROJ_DEBUG_MODE
   NVM_module_time.NVM_curr_counter = OS_GetFreeRunCounter();
   NVM_module_time.NVM_diff_time = NVM_module_time.NVM_prev_counter - NVM_module_time.NVM_curr_counter;
   /* Timer operates as a down counter */
   if (NVM_module_time.NVM_max_time < NVM_module_time.NVM_diff_time)
   {
      NVM_module_time.NVM_max_time = NVM_module_time.NVM_diff_time;
   }
   #endif
}

/*.===================================================================*\
 *. FUNCTION: NVM_Check_Valid_Block
 *.=====================================================================
 *. Return Value: None
 *.
 *. Parameters: None
 *.
 *. External references: DDP_RequestContextSave, DDP_ConfirmFaultStatus
 *.
 *.  External variables: None
 *.
 *.  File scope variables: NVM_Admin_Block_Status
 *.
 *. Description:   This function Checks CRC Validity for all the Block.
 *  if CRC is invalid restores default data by sending write request
 *  to EEPROM
 \*===================================================================*/
static void NVM_Check_Valid_Block(void)
{
   uint8_t nvm_blockid;
   uint8_t nvm_crc_state;

   nvm_blockid = 0;
   //redundant_block = 0;
   do
   {
      /* Get CRC validity */      
      nvm_crc_state = NVM_Admin_Block_Status[nvm_blockid].CRC_Validity;
      /* If CRC is not valid,restore default settings */         
      if (NVM_CRC_VALID != nvm_crc_state)        
      {
         (void)NVM_Restore_Default(nvm_blockid);//set rom to default
      }
      else
      {
         /* Do Nothing */
      }
      nvm_blockid++;
      WdgM_Refresh();
   }
   while (nvm_blockid < NVM_MAX_B81_ID);
} /* End of Function */

/*==============================================================================
* FUNCTION: NVM_ReadAll
*===============================================================================
* Return Value:
*    None
* Parameters:
*    None
*
* External references: CRC_CalcCRC, DDP_RequestContextSave,
*                      DDP_ConfirmFaultStatus
*
* External variables: NVM_Mem_config, EcuM_SwVersion
*
*  File scope variables: NVM_Admin_Block_Status
*
* Description:
*  The function reads All EEPROM parameters to its data structure(RAM Copy) &
*   verify CRC. Maintain separate data-structure for each block of data
*  (Eg: Fault, Config, Settings & ID). If CRC is correct, it will set the
*  corresponding data flag to VALID else to INVALID.
*
*=============================================================================*/
static void NVM_ReadAll(void)
{
   //uint16_t calc_crc_value;
   //uint8_t crc_value[DATA_CRC_SIZE];
   uint8_t block_Id;
   uint8_t *nvm_srcptr;
   uint8_t length;
   uint8_t data_size;
   NVM_Mem_JobResult_T job_result;

   
  for (block_Id = NVM_SECTOR_BLK_ID; block_Id < NVM_MAX_B81_ID; block_Id++)  
  {
     length = NVM_Mem_config[block_Id].Nvm_Length;
     nvm_srcptr = NVM_Mem_config[block_Id].Nvm_Srcptr;


     NVM_Admin_Block_Status[block_Id].CRC_Validity = NVM_CRC_INVALID;
     /* it reads data from EEPROM and calculate CRC and update validity flag 1 */
     if (NVM_NULL_PTR != nvm_srcptr)
     {
        job_result = NVM_Direct_Read_By_ID(block_Id, nvm_srcptr);
        if (NVM_MEM_JOB_OK == job_result)
        {
           if(NVM_Block_Config[block_Id].chksum)
           {
              data_size = length - DATA_CRC_SIZE;
               /* Calculates CRC */
              // calc_crc_value = CRC_CalcCRC(NVM_CRC_INIT_VALUE, data_size, nvm_srcptr);
    
              // crc_value[0] = (uint8_t)(calc_crc_value);
              // crc_value[1] = (uint8_t)(calc_crc_value >> SHIFT_CONST_VALUE);
               /* Checks Calculated CRC is equal to Read CRC value */
              // if ( (nvm_srcptr[data_size] == crc_value[0]) && (nvm_srcptr[data_size + 1] == crc_value[1]) )
              #ifndef QAC
               if(E_OK == Getsum ((uint32_t)nvm_srcptr, data_size, VERIFY_CHECKSUM, TRUE, (uint16_t*)&nvm_srcptr[data_size]))
               {
                  /* Updates CRC Validity flag for all the Blocks */
                  NVM_Admin_Block_Status[block_Id].CRC_Validity = NVM_CRC_VALID;
               }
               else
               {
                  /* Do Nothing */
               }
               #endif
           }
           else//no need calculate chksum
           {
              NVM_Admin_Block_Status[block_Id].CRC_Validity = NVM_CRC_VALID;
           }
        }
        else
        {
           /* Do Nothing */
        }
     }
     else
     {
        /* Do Nothing */
     }
      WdgM_Refresh();
  } /* End of For Loop */
  NVM_Check_Valid_Block();
} /* End of NVM_ReadAll */
/*==============================================================================
* FUNCTION: NVM_Restore_Default
*===============================================================================
* Return Value:
*    Std_ReturnType - E_OK/E_NOT_OK
* Parameters:
*    uint8_t block_id - id which represents Event/Fault, configParameters etc
*
* External references: memcpy
*
* External variables: NVM_Mem_configr
* 
*  File scope variables: NVM_Admin_Block_Status
*
* Description:
*  This function restore invalid EEP Block with Default Data or by request.
* wade: added for ICS
*=============================================================================*/
static NVM_Mem_JobResult_T NVM_Restore_Default(uint8_t BlockId)
{
   NVM_Mem_JobResult_T write_req_status;
   uint8_t *ram_ptr;
   const uint8_t *rom_ptr;
   uint8_t length;
   //uint8_t nvm_eel_id;
   //uint16_t calc_crc_value;

   ram_ptr = NVM_Mem_config[BlockId].Nvm_Srcptr;
   rom_ptr = NVM_Mem_config[BlockId].Nvm_Romptr;
   length  = NVM_Mem_config[BlockId].Nvm_Length;
   //nvm_eel_id = NVM_Mem_config[BlockId].Nvm_EEL_Id;

   write_req_status = NVM_MEM_JOB_FAILED;
   
   /* Checks if ECU life phase not in sleep mode */
   if ((NVM_Eel_Handler.RW_Flag) && (BlockId < NVM_MAX_B81_ID))   
   {
      /* It will check ram block and Rom block pointer is not Null pointer */
      if ((NVM_NULL_PTR != ram_ptr) && (NVM_NULL_PTR != rom_ptr))
      {
           /* It store default value to ram pointer */
           NVM_Memory_Copy(ram_ptr,rom_ptr,length);
          /*request will be queued directly for write service */
           //write_req_status = NVM_Queue_Request(BlockId, NVM_WRITE_BLOCK);
          //write_req_status = NVM_Direct_Write(BlockId, rom_ptr, length);

          //step2: recalculate the checksum, for thos need chksum 
              #ifndef QAC
          if(NVM_Block_Config[BlockId].chksum)
          {
              length = NVM_Mem_config[BlockId].Nvm_Length - DATA_CRC_SIZE;
              /* CRC is calculated for requested block ID */
              Getsum ((uint32_t)ram_ptr, length, UPDATE_CHECKSUM, TRUE, (uint16_t*)&ram_ptr[length]);
          }
          #endif
          write_req_status = NVM_Direct_Write_By_ID(BlockId);
        }
   }
   if((write_req_status == NVM_MEM_JOB_OK) && (BlockId < NVM_MAX_B81_ID))
   {
       NVM_Admin_Block_Status[BlockId].CRC_Validity = NVM_CRC_VALID;
   }
   
   return(write_req_status);
}

/*==============================================================================
* FUNCTION: NVM_Direct_Read_By_ID
*===============================================================================
* Return Value:
*    NVM_Mem_JobResult_T - Job result[JOB_OK, JOB_FAILED]
* Description:
*  This function is used to read from EEL directly without scheduler. it 
*  calls EEL_Execute and EEL_Handler function to do the Job
*
* Wade: read EEPROM, called by internally
*=============================================================================*/
static NVM_Mem_JobResult_T NVM_Direct_Read_By_ID(uint8_t block_id, uint8_t *NVM_DstPtr)
{
   NVM_Mem_JobResult_T nvm_dir_rd_status;
   uint8_t nvm_eel_id;
   uint16_t v_cnt = 0;
   NVM_Mem_Status_T nvm_eel_status = NVM_MEM_BUSY;
   NVM_CMD_STATUS polling_result;


   //before read, check EEL status;
   while((nvm_eel_status == NVM_MEM_BUSY)&&(v_cnt<NVM_MAX_ACCESS_TIME))
   {
       nvm_eel_status = NVM_Get_EEL_Status();
       OS_Delay(100);
       v_cnt++;
   }
   //timeout for EEL busy
   if(v_cnt>=NVM_MAX_ACCESS_TIME)
   {
       return (NVM_MEM_PREV_COMMAND_IN_PROG);
   }
   WdgM_Refresh(); //feed dog because the  process need more time to run



   nvm_eel_id = NVM_Mem_config[block_id].Nvm_EEL_Id;
   /* Checks EEL Id is less than MAX EEL Id and sourc pointer is not null 
    * pointer 
    */
   if (((nvm_eel_id > 0) && (nvm_eel_id <= NVM_MAX_EEL_IDENTIFIER)) && 
       (NVM_NULL_PTR != NVM_DstPtr))
   {
      /* Ram starting Address */
      NVM_Eel_Request.address_pu08   = NVM_DstPtr; 
      /* Identifier */     
      NVM_Eel_Request.identifier_u08 = nvm_eel_id;
      /* EE Command */
      NVM_Eel_Request.command_enu    = EEL_CMD_READ;    

      polling_result = NVM_CommandExecute_Polling();
      
      //timeout for EEL busy
      if(NVM_CMD_SUCCESSFUL == polling_result)
      {
         nvm_dir_rd_status = NVM_MEM_JOB_OK;   
      }
      else if(NVM_CMD_BUSY == polling_result)
      {
         nvm_dir_rd_status = NVM_MEM_PREV_COMMAND_IN_PROG; 
      }
      else
      {
         nvm_dir_rd_status = NVM_MEM_JOB_FAILED; 
      }
   }
   else
   {
      nvm_dir_rd_status = NVM_MEM_JOB_FAILED;
   }
   return(nvm_dir_rd_status);
}


/*==============================================================================
* FUNCTION: NVM_Direct_Write_By_ID
*===============================================================================
* Return Value:
* Parameters:
*    uint16_t block_id
*
* Description:
*  This function is used to write EEPROM, called by internally
*=============================================================================*/
static NVM_Mem_JobResult_T NVM_Direct_Write_By_ID(uint8_t block_id)
{
   NVM_Mem_JobResult_T nvm_dir_rd_status;
   uint8_t nvm_eel_id;
   uint16_t v_cnt = 0;
   NVM_Mem_Status_T nvm_eel_status = NVM_MEM_BUSY;
   NVM_CMD_STATUS polling_result;


   //before read, check EEL status;
   while((nvm_eel_status == NVM_MEM_BUSY)&&(v_cnt<NVM_MAX_ACCESS_TIME))
   {
       nvm_eel_status = NVM_Get_EEL_Status();
       EEL_Handler(NVM_EEL_POLLING);
       OS_Delay(100);
       v_cnt++;
   }
   //timeout for EEL busy
   if(v_cnt>=NVM_MAX_ACCESS_TIME)
   {
       return (NVM_MEM_PREV_COMMAND_IN_PROG);
   }
   WdgM_Refresh(); //feed dog because the  process need more time to run


   nvm_eel_id = NVM_Mem_config[block_id].Nvm_EEL_Id;
   /* Checks EEL Id is less than MAX EEL Id and sourc pointer is not null 
    * pointer 
    */
   if (((nvm_eel_id > 0) && (nvm_eel_id <= NVM_MAX_EEL_IDENTIFIER)))
   {
      /* Ram starting Address */
      NVM_Eel_Request.address_pu08   = NVM_Mem_config[block_id].Nvm_Srcptr; 
      /* Identifier */     
      NVM_Eel_Request.identifier_u08 = nvm_eel_id;
      /* EE Command */
      NVM_Eel_Request.command_enu    = EEL_CMD_WRITE;  

      polling_result = NVM_CommandExecute_Polling();
      
      //timeout for EEL busy
      if(NVM_CMD_SUCCESSFUL == polling_result)
      {
         nvm_dir_rd_status = NVM_MEM_JOB_OK;   
      }
      else if(NVM_CMD_BUSY == polling_result)
      {
         nvm_dir_rd_status = NVM_MEM_PREV_COMMAND_IN_PROG; 
      }
      else
      {
         nvm_dir_rd_status = NVM_MEM_JOB_FAILED; 
      }
   }
   else
   {
      nvm_dir_rd_status = NVM_MEM_JOB_FAILED;
   }
   return(nvm_dir_rd_status);
}


/*==============================================================================
* FUNCTION: NVM_Get_EEL_Status
*===============================================================================
* Return Value:
*   NVM_Mem_Status_T - NVM_MEM_IDLE/NVM_MEM_BUSY
* Parameters:
*   None    
* External references: EEL_GetDriverStatus
*
* External variables: 
*
*  File scope variables: None
*
* Description: It provide the status of the EEL driver
*  
*=============================================================================*/
static NVM_Mem_Status_T NVM_Get_EEL_Status(void)
{
   NVM_Mem_Status_T eel_status;
   /* Created Structure type variable */
   eel_driver_status_t eel_drv_status;
   /* Get the EEL status and returns EEL is Idle or busy */
   EEL_GetDriverStatus(&eel_drv_status);
   if(EEL_OPERATION_IDLE == eel_drv_status.operationStatus_enu)
   {
      eel_status = NVM_MEM_IDLE;
   }
   else
   {
      eel_status = NVM_MEM_BUSY;
   }
   return(eel_status);
}

/*==============================================================================
* FUNCTION: NVM_EEL_InitStartup
*===============================================================================
* Return Value:
*   None
* Parameters:
*   None    
* External references: EEL_Execute
*                      EEL_Handler
*
* External variables: None
*
*  File scope variables: None
*
* Description: The startup command interpretes the actual status of the EEL 
*   pool. STARTUP command opens the access to the EEL data for the variable 
*   oriented commands.
* wade: initiate startup, need check function later....
*=============================================================================*/
static void NVM_EEL_InitStartup(void)
{
  // static uint16_t decimation_counter = 0;
   //Std_ReturnType timeout_flag = E_OK;
   NVM_CMD_STATUS polling_result;
  
   /* STARTUP command opens the access to the EEL data */
   NVM_Eel_Request.command_enu = EEL_CMD_STARTUP;
   polling_result = NVM_CommandExecute_Polling();

   /* If EEL status is not ok, It will call error handler function */
   if (polling_result!= NVM_CMD_SUCCESSFUL)            
   {
      NVM_EEL_Error_Handler_Ext(NVM_Eel_Request.status_enu);
   }
   else
   {
      /* If EEL status is ok, Updates RW Flag is true */
      NVM_Eel_Handler.RW_Flag = TRUE;
   }
   /* if the timeout occurs  - send DTC INTERNAL_FAULT 
                             - run with default "ROM" values
                             - skip any further NVM (EEL)  access
   */
  /* if (timeout_flag == E_NOT_OK)
   {
      //DDP_RequestContextSave(ECU_INTERNAL_FAULT,START_OF_FAULT_PRESENT);
      //DDP_ConfirmFaultStatus(ECU_INTERNAL_FAULT,FAULT_PRESENT,AUTOTEST_DEFAULT_DEGRADED_MODE);
      NVM_Eel_Handler.RW_Flag = FALSE;
   }*/
} 

/*==============================================================================
* FUNCTION: NVM_EEL_Error_Handler_Ext
*===============================================================================
* Return Value:
*   None
* Parameters:
*   eel_status_t  nvm_eel_status
*      
* External references: EEL_Init, EEL_Open, EEL_Execute
*                      DDP_RequestContextSave, DDP_ConfirmFaultStatus
*
* External variables: None
*
*  File scope variables: None
*
* Description:  Action is taken for EEL error
*  
*=============================================================================*/
static void NVM_EEL_Error_Handler_Ext(eel_status_t nvm_eel_status)
{
    bool_t need_reset = FALSE;
    
    switch(nvm_eel_status)
    {
        /* EEL not initialized or not opened */
        case EEL_ERR_INITIALIZATION:
            /* Initialize and open EEL before using it */
            (void)EEL_Init();
            /* To open access to the EEL-pool EEL_Open() function has to be called */
            EEL_Open(); 
            need_reset = TRUE;
            break;
            
      /* no space in pool, sometimes it happed this case in ICS diagnostics process */
      case EEL_ERR_POOL_FULL:    
      /* EEL pool size smaller i.e < 3 */
      case EEL_ERR_POOL_EXHAUSTED:
      /* EEL pool or EEL discriptor is wrong */
      case EEL_ERR_CONFIGURATION:
      /* Unknown variable identifier - correct the variables in EEL disriptor */
         
      /*changed for ICS, 20110810, data pool have problem, re-format it.
      it always happened when first use the data flash.*/
      case EEL_ERR_POOL_INCONSISTENT:
         NVM_Eel_Request.timeout_u08	= NVM_EEL_POLLING;
	     NVM_Eel_Request.command_enu	= EEL_CMD_FORMAT;
	     do
	     {
	         EEL_Execute(&NVM_Eel_Request);
	         EEL_Handler(0);
	     }while(NVM_Eel_Request.status_enu == EEL_ERR_REJECTED);
	
	     do
	     {
	         EEL_Handler(0);
             WdgM_Refresh();
	     }
         while(NVM_Eel_Request.status_enu == EEL_BUSY);
         
         if(NVM_Eel_Request.status_enu == EEL_OK)
         {
             need_reset = TRUE;
         }
         else
         {
             //error on format....
         }
         break;

      /* unexpected or unkown error code generated in back ground */
      case EEL_ERR_INTERNAL: 
      /* No read or write access to EEL */            
      case EEL_ERR_ACCESS_LOCKED:       
         NVM_Eel_Request.timeout_u08 = NVM_EEL_POLLING;
         NVM_Eel_Request.command_enu = EEL_CMD_STARTUP;       
         
         do
	     {
	         EEL_Handler(0);
             WdgM_Refresh();
	     }
         while(NVM_Eel_Request.status_enu == EEL_BUSY);
         
         if(NVM_Eel_Request.status_enu == EEL_OK)
         {
             need_reset = TRUE;
         }
         else
         {
             //start failed....
         }
         break;

      case EEL_ERR_PARAMETER: 
      /* unknown command used for request */           
      case EEL_ERR_COMMAND:              
          //unknown command, don't handle it.
          break;

      default:
          break; 
   }

    if(need_reset)
    {
        Mcu_PerformReset();
    }
}

/*==============================================================================
* FUNCTION: NVM_EEL_Error_Handler
*===============================================================================
* Return Value:
*   None
* Parameters:
*   eel_status_t  nvm_eel_status
*      
* External references: EEL_Init, EEL_Open, EEL_Execute
*                      DDP_RequestContextSave, DDP_ConfirmFaultStatus
*
* External variables: None
*
*  File scope variables: None
*
* Description:  Action is taken for EEL error
*  
* wade: TBD: save error type
*=============================================================================*/
static void NVM_EEL_Error_Handler(eel_status_t nvm_eel_status)
{
   switch(nvm_eel_status)
   {
      /* EEL not initialized or not opened */
      case EEL_ERR_INITIALIZATION:
         /* Initialize and open EEL before using it */
         (void)EEL_Init();
         /* To open access to the EEL-pool EEL_Open() function has to be called */
         EEL_Open();  
         break;
         
      //changed for ICS, 20110810, data pool have problem, re-format it.
      //it always happened when first use the data flash.
      case EEL_ERR_POOL_INCONSISTENT:
         NVM_Eel_Request.timeout_u08	= 0;
	     NVM_Eel_Request.command_enu	= EEL_CMD_FORMAT;
	     do
	     {
	         EEL_Execute(&NVM_Eel_Request);
	         EEL_Handler(0);
	     }while(NVM_Eel_Request.status_enu == EEL_ERR_REJECTED);
	
	     do
	     {
	         EEL_Handler(0);
             WdgM_Refresh();
	     }while(NVM_Eel_Request.status_enu == EEL_BUSY);
         
         if(NVM_Eel_Request.status_enu == EEL_OK)
         {
             //after format 
             Mcu_PerformReset();
         }
         break;

      /* unexpected or unkown error code generated in back ground */
      case EEL_ERR_INTERNAL: 
      /* No read or write access to EEL */            
      case EEL_ERR_ACCESS_LOCKED:        
         NVM_Eel_Request.command_enu = EEL_CMD_STARTUP;       
         NVM_Eel_Request.timeout_u08 = NVM_EEL_POLLING;
         EEL_Execute(&NVM_Eel_Request); 
         NVM_Eel_Handler.EEL_Command = EEL_CMD_STARTUP;
         NVM_Eel_Handler.RW_Flag = FALSE;
         break;

      /* EEL pool size smaller i.e < 3 */
      case EEL_ERR_POOL_EXHAUSTED:
      /* EEL pool or EEL discriptor is wrong */
      case EEL_ERR_CONFIGURATION:
      /* Unknown variable identifier - correct the variables in EEL disriptor */
      case EEL_ERR_PARAMETER: 
      /* unknown command used for request */           
      case EEL_ERR_COMMAND:              
        // NVM_EEL_Drv_JobResult = NVM_MEM_JOB_FAILED;
         NVM_Eel_Handler.EEL_Command = EEL_CMD_UNDEFINED;
         break;

      /* no space in pool */
      case EEL_ERR_POOL_FULL:            
         NVM_Eel_Request.command_enu = EEL_CMD_CLEANUP;       
         NVM_Eel_Request.timeout_u08 = NVM_EEL_ENFORCE;
         EEL_Execute(&NVM_Eel_Request);
         NVM_Eel_Handler.EEL_Command = EEL_CMD_CLEANUP;
         NVM_Eel_Handler.RW_Flag = FALSE;
         break;
      /* EEL busy, Do nothing */
      case EEL_BUSY:
         /* Do Nothing */
         break;
      /* EEL Job is OK, Update job result to MEM Job OK */
      case EEL_OK:
       //  NVM_EEL_Drv_JobResult = NVM_MEM_JOB_OK;
         NVM_Eel_Handler.RW_Flag = TRUE;
         break;

      default:
         break; 
   }
}

/*==============================================================================
* FUNCTION: NVM_DIAG_EEL_Command_Request
*===============================================================================
* Return Value: eel_status_t
* 
* Parameters: uint8_t rcs_Com
*             uint8_t nvm_diag_com
*
* External references: EEL_Execute
* 
* External variables: None
* 
*  File scope variables: None
* Parameters: None
*
* External references: FAL_Open, EEL_Open
* 
* External variables: None
* 
*  File scope variables: None
*
* Description: This function is called when ECU lifephse enters from sleep mode
* FUNCTION: NVM_Memory_Copy
*===============================================================================
* Return Value: None
* 
* Parameters: uint8_t dest_ptr[]
*             uint8_t src_ptr[]
*             uint8_t length
*
* External references: None
* 
* External variables: None
* 
*  File scope variables: None
*
* Description: This function copies data from one location to another location.
*=============================================================================*/
static void NVM_Memory_Copy(uint8_t dest_ptr[], const uint8_t src_ptr[],uint8_t length)
{
   uint8_t index;
   for(index = 0; index< length; index++)
   {
      /* Copies from source to destination location */
      dest_ptr[index] = src_ptr[index];
   }
}

/*==============================================================================
* FUNCTION: NVM_Get_Block_ID
*===============================================================================
* Return Value: the block number
* 
 * Parameters: the absolute position in EEPROM
*
*
* Description: This function try to get the block number 
*=============================================================================*/
static uint8_t NVM_Get_Block_ID(uint16_t mem_pos)
{
    uint8_t curr_blk = 0;
    
   while(curr_blk <NVM_MAX_B81_ID)
   {
       if((mem_pos >= NVM_Block_Config[curr_blk].mem_pos) && (mem_pos < NVM_Block_Config[curr_blk+1].mem_pos))
       {
           break;
       }
    
     curr_blk++;
   }

   return curr_blk;
}
/*==============================================================================
* FUNCTION: NVM_Get_SubBlock_Addr
*===============================================================================
* Return Value: the relative position in block
* 
 * Parameters: the absolute position in EEPROM
*
*
* Description: This function try to get the block position 
*=============================================================================*/
static uint8_t NVM_Get_SubBlock_Addr(uint16_t mem_pos)
{
    uint8_t curr_id;
    
    curr_id = NVM_Get_Block_ID(mem_pos);
    if(curr_id >= NVM_MAX_B81_ID)
    {
        return 0;
    }

    return (uint8_t)(mem_pos - NVM_Block_Config[curr_id].mem_pos);

}
/*==============================================================================
* FUNCTION: NVM_Get_SubBlock_Size
*===============================================================================
* Return Value: the left size to operature
* 
 * Parameters: 
*   [block_id] the block number 
*   [sub_pos]  the position in block
*
* Description: get the size of block by the sub position
*=============================================================================*/
static uint16_t NVM_Get_SubBlock_Size(uint8_t block_id, uint16_t sub_pos)
{    
    if((block_id >= NVM_MAX_B81_ID) || (sub_pos >= NVM_Mem_config[block_id].Nvm_Length))
    {
        return 0;
    }
    else
    {
       return (NVM_Mem_config[block_id].Nvm_Length - sub_pos);
    }

}
//the main initialization is about 70ms
/*==============================================================================
* FUNCTION: NVM_CommandExecute_Polling
*===============================================================================
* Return Value: the EEPROM API call result
* 
 * Parameters:  none
*
*
* Description: execute the polling command
*=============================================================================*/
static NVM_CMD_STATUS NVM_CommandExecute_Polling(void)
{
   NVM_CMD_STATUS cmd_Status;
   uint32_t v_cnt =0;   

   //added on 20120425, before read/write, confirm the eeprom is available
   if((NVM_Eel_Handler.RW_Flag == FALSE)&&
      ((NVM_Eel_Request.command_enu == EEL_CMD_READ) || (NVM_Eel_Request.command_enu == EEL_CMD_WRITE)))
   {
     return NVM_CMD_ERR;  
   }

   
   NVM_Eel_Request.timeout_u08 = NVM_EEL_POLLING; //wade: polling -->enforce
   WdgM_Refresh(); //before init EEPROM, feed dog because the init process need more time to run
   EEL_Execute(&NVM_Eel_Request);
   
   /* a 1 sec timeout is started for the below while loop */
   while(EEL_BUSY == NVM_Eel_Request.status_enu)
   {
      EEL_Handler(NVM_EEL_POLLING);//added for handle the background command process
      WdgM_Refresh();// This service of WDT is added to satisfy EEL 
      OS_Delay(4);// 1us
      v_cnt++;
      
      if(v_cnt > 1000L*NVM_MAX_ACCESS_TIME)
      {
         break;
      }
   }
   /* If EEL status is not ok, It will call error handler function */
   if (EEL_BUSY == NVM_Eel_Request.status_enu)  
   {
       cmd_Status = NVM_CMD_BUSY;
   }
   else if(EEL_OK == NVM_Eel_Request.status_enu)
   {
       cmd_Status = NVM_CMD_SUCCESSFUL;
   }
   else
   {
       cmd_Status = NVM_CMD_ERR;
       NVM_EEL_Error_Handler_Ext(NVM_Eel_Request.status_enu);
       
   }

   return cmd_Status;
}

/*=========================================================

external interface
=========================================================*/

/*==============================================================================
* FUNCTION: NVM_EEPROM_Shutdowm
*===============================================================================
* Return Value:
*    None
* Parameters:
*    None
*
*
*  External variables: None
* 
*  File scope variables: None
*
* Description:
*  added external interface to shutdown the data flash
*=============================================================================*/
void NVM_EEPROM_Shutdowm(void)
{
    NVM_Eel_Request.command_enu = EEL_CMD_SHUTDOWN;
    NVM_Eel_Request.timeout_u08 = NVM_EEL_ENFORCE;
    WdgM_Refresh(); //feed dog because the  process need more time to run
    EEL_Execute(&NVM_Eel_Request);
    if (EEL_OK == NVM_Eel_Request.status_enu)
    {
        /* close the access to the EEL pool. */
        EEL_Close();
        /* This function deactivates the data flash.*/
        FAL_Close();
    }
    NVM_Eel_Handler.RW_Flag = FALSE;
}

/*.===================================================================*\
 *. FUNCTION: NVM_Set_Rom_To_EE
 *.=====================================================================
 *. Return Value: None
 *.
 *. Parameters: None
 *.
 *.
 *.  External variables: None
 *.
 *.  File scope variables: NVM_Admin_Block_Status
 *.
 *. Description:   reset the eeprom to default rom value
 \*===================================================================*/
void NVM_Set_Rom_To_EE(void)
{
   uint8_t nvm_blockid;
   //uint8_t nvm_crc_state;

   nvm_blockid = 0;
   do
   {
      /* Set CRC validity */      
      NVM_Admin_Block_Status[nvm_blockid].CRC_Validity = NVM_CRC_INVALID;
      /* If CRC is not valid,restore default settings */         
      NVM_Restore_Default(nvm_blockid);//set rom to default
      nvm_blockid++;
      WdgM_Refresh();
   }
   while (nvm_blockid < NVM_MAX_B81_ID);
} /* End of Function */

/*.===================================================================*\
 *. FUNCTION: NVM_Set_DTC_To_Default
 *.=====================================================================
 *. Return Value: None
 *.
 *. Parameters: None
 *.
 *. Description:   This function set the DTC value to default value
 \*===================================================================*/
void NVM_Set_DTC_To_Default(void)
{
    //NVM_Restore_Default(NVM_DTC1_BLK_ID);
   // NVM_Restore_Default(NVM_DTC2_BLK_ID);
   // NVM_Restore_Default(NVM_DTC_CHKSUM_BLK_ID);
}

/*==============================================================================
* FUNCTION: NVM_Direct_Read2
*===============================================================================
* Return Value:
*    NVM_Mem_JobResult_T - Job result[JOB_OK, JOB_FAILED]
* Parameters:
*    uint16_t nvm_eel_id - EEL identifier
*    uint8_t  *NVM_DstPtr - pointer to RAM data block(should be globally
*                                   accessible)
*
* External references: EEL_Execute, EEL_Handler
*
*  External variables: None
*
*  File scope variables: NVM_Eel_Request
*
* Description:
*  here call read by enforce, not polling
*
* Wade: read EEPROM directly, called by APP directly
*=============================================================================*/
NVM_Mem_JobResult_T NVM_Direct_Read2(uint8_t block_id, uint16_t sub_pos, uint8_t *NVM_DstPtr, uint8_t bytes)
{
   NVM_Mem_JobResult_T nvm_dir_rd_status= NVM_MEM_JOB_FAILED;
   //uint8_t nvm_eel_id;
   uint8_t *nvm_srcptr;
   uint16_t length;

   if(block_id>=NVM_MAX_B81_ID)
   {
      return (NVM_MEM_JOB_FAILED);
   }
   if(NVM_Admin_Block_Status[block_id].CRC_Validity == NVM_CRC_VALID)
   {
       length = NVM_Mem_config[block_id].Nvm_Length - sub_pos;
       length = (length < bytes) ? length : bytes;
       nvm_srcptr = NVM_Mem_config[block_id].Nvm_Srcptr;
       NVM_Memory_Copy(NVM_DstPtr, nvm_srcptr+sub_pos, (uint8_t)length); 
       nvm_dir_rd_status = NVM_MEM_JOB_OK;
   }


   return(nvm_dir_rd_status);
}

/*==============================================================================
* FUNCTION: NVM_Direct_Write
*===============================================================================
* Return Value:
*    NVM_Mem_JobResult_T - Job result[JOB_OK, JOB_FAILED]
* Parameters:
*    uint16_t nvm_eel_id - EEL identifier
*    uint8_t  *NVM_DstPtr - pointer to RAM data block(should be globally
*                                   accessible)
*
* External references: EEL_Execute, EEL_Handler
*
*  External variables: None
*
*  File scope variables: NVM_Eel_Request
*
* Description:
*  here call read by enforce, not polling
*
* Wade: read EEPROM directly, called by APP directly
*=============================================================================*/
 NVM_Mem_JobResult_T NVM_Direct_Write(uint8_t block_id, uint8_t sub_pos, uint8_t *NVM_DstPtr, uint8_t bytes)
{
   NVM_Mem_JobResult_T nvm_dir_rd_status;
   uint8_t nvm_eel_id;
   uint8_t *nvm_srcptr;
   uint8_t length;
   //uint16_t calc_crc_value;
   NVM_Mem_Status_T nvm_eel_status = NVM_MEM_BUSY;
   uint16_t v_cnt =0;
   NVM_CMD_STATUS polling_result;

   //before write, check EEL status;
   while((nvm_eel_status == NVM_MEM_BUSY)&&(v_cnt<NVM_MAX_ACCESS_TIME))
   {
       nvm_eel_status = NVM_Get_EEL_Status();
       OS_Delay(100);
       v_cnt++;
   }
   //timeout for EEL busy
   if(v_cnt>=NVM_MAX_ACCESS_TIME)
   {
       return (NVM_MEM_PREV_COMMAND_IN_PROG);
   }
   WdgM_Refresh(); //feed dog because the  process need more time to run
   
   /* To get source pointer */
   nvm_srcptr = NVM_Mem_config[block_id].Nvm_Srcptr;
   /* length is data length excluding CRC bytes */
   length = NVM_Mem_config[block_id].Nvm_Length - sub_pos;
   length = (length < bytes) ? length : bytes;
   
   //step1: copy the data to ram buffer
   NVM_Memory_Copy(nvm_srcptr+sub_pos, NVM_DstPtr, length);  

   //step2: recalculate the checksum, if needed, currently disable it.
   #if 0
   if(NVM_Block_Config[block_id].chksum)
   {
      /* To get source pointer */
      nvm_srcptr = NVM_Mem_config[block_id].Nvm_Srcptr;
      /* length is data length excluding CRC bytes */
      length = NVM_Mem_config[block_id].Nvm_Length - DATA_CRC_SIZE;
      /* CRC is calculated for requested block ID */
      calc_crc_value = CRC_CalcCRC(NVM_CRC_INIT_VALUE, length, nvm_srcptr);
      /* Updates Calculated CRC value at end of Ram location or CRC location 
      * if little endian machine update first LSB and then MSB
      * if it is big endian update MSB first and then LSB.
      */
      nvm_srcptr[length + 1] = (uint8_t)(calc_crc_value >> SHIFT_CONST_VALUE );
      nvm_srcptr[length + 0] = (uint8_t)(calc_crc_value);
   }
   #endif
   //step3: put the ram buffer to data flash
   nvm_eel_id = NVM_Mem_config[block_id].Nvm_EEL_Id;
   /* Checks EEL Id is less than MAX EEL Id and sourc pointer is not null 
    * pointer 
    */
   if (((nvm_eel_id > 0) && (nvm_eel_id <= NVM_MAX_EEL_IDENTIFIER)) && 
       (NVM_NULL_PTR != nvm_srcptr))
   {
      /* Ram starting Address */
      NVM_Eel_Request.address_pu08   = nvm_srcptr; 
      /* Identifier */     
      NVM_Eel_Request.identifier_u08 = nvm_eel_id;
      /* EE Command */
      NVM_Eel_Request.command_enu    = EEL_CMD_WRITE;    
      polling_result = NVM_CommandExecute_Polling();
      
      //timeout for EEL busy
      if(polling_result == NVM_CMD_SUCCESSFUL)
      {
         nvm_dir_rd_status = NVM_MEM_JOB_OK;   
         NVM_Admin_Block_Status[block_id].CRC_Validity = NVM_CRC_VALID;
      }        
      else if(polling_result == NVM_CMD_BUSY)
      {
         nvm_dir_rd_status = NVM_MEM_PREV_COMMAND_IN_PROG; 
         NVM_Admin_Block_Status[block_id].CRC_Validity = NVM_CRC_INVALID;
      }
    
      else
      {
         nvm_dir_rd_status = NVM_MEM_JOB_FAILED; 
         NVM_Admin_Block_Status[block_id].CRC_Validity = NVM_CRC_INVALID;
      }
   }
   else
   {
      nvm_dir_rd_status = NVM_MEM_JOB_FAILED;
   }
   return(nvm_dir_rd_status);
}
/*==============================================================================
* FUNCTION: NVM_read_EE
*===============================================================================
* Return Value:
*    NVM_Mem_JobResult_T - Job result[JOB_OK, JOB_FAILED]
* Parameters:
*    uint32_t dest : save buffer
*    uint32_t src  : the logic address in eeprom, 
*    uint8_t  num_bytes: the size to read     
*
*
*  External variables: None
*
*
* Description:
*  here is the standard interface to eeprom read
*
*=============================================================================*/
NVM_Mem_JobResult_T NVM_Read_EE(uint32_t dest, uint32_t src, uint8_t num_bytes)
{
    uint8_t block1, block2; 
    uint16_t sub_pos1, sub_pos2, sub_size1, sub_size2;
    NVM_Mem_JobResult_T job_result, op1_result, op2_result;
    

    block1 = NVM_Get_Block_ID((uint16_t)src);    
    block2 = NVM_Get_Block_ID((src+num_bytes)-1);
    
    if(block2 >= NVM_MAX_B81_ID)
    {
        job_result = NVM_MEM_JOB_FAILED; //out of size
    }
    //if begin position is not same as end position
    else if(block2!= block1) 
    {
        //check the size in block 1: sub_pos1<-->end
        sub_pos1 = NVM_Get_SubBlock_Addr(src);
        sub_size1 = NVM_Get_SubBlock_Size(block1, sub_pos1);//size in block1
        
        //check the size in block 2: 0<-->sub_pos2
        sub_pos2 = 0;
        //get and check sub_size2
        sub_size2 = NVM_Get_SubBlock_Size(block2, sub_pos2);   //size in block2
        sub_size2 = (sub_size2 < (num_bytes - sub_size1))? sub_size2 : (num_bytes - sub_size1);
        //begin to operate
        op1_result = NVM_Direct_Read2(block1, sub_pos1, (uint8_t *)dest, (uint8_t)sub_size1);
        op2_result = NVM_Direct_Read2(block2, sub_pos2, (uint8_t *)(dest+sub_size1), (uint8_t)sub_size2);
        if((op1_result == NVM_MEM_JOB_OK) && (op2_result == NVM_MEM_JOB_OK))
        {
            job_result = NVM_MEM_JOB_OK; //out of size
        }
        else
        {
            job_result = NVM_MEM_JOB_FAILED; //out of size
        }
    }
    else  //in same block
    {
       sub_pos1 = NVM_Get_SubBlock_Addr(src);
       sub_size1 = NVM_Get_SubBlock_Size(block1, sub_pos1);//size in block1
       op1_result = NVM_Direct_Read2(block1, sub_pos1, (uint8_t *)dest, (uint8_t)num_bytes);
       //return (NVM_MEM_JOB_OK == op1_result);
       job_result = op1_result; 
    }

    return job_result;
}
/*==============================================================================
* FUNCTION: NVM_Write_EE
*===============================================================================
* Return Value:
*    NVM_Mem_JobResult_T - Job result[JOB_OK, JOB_FAILED]
* Parameters:
*    uint8_t* dest : write position in eeprom
*    uint8_t* src: data buffer
*    uint8_t  num_bytes: the size to write     
*                                   accessible)
*
*
*  External variables: None
*
*
* Description:
*  here is the standard interface to eeprom write
*
*=============================================================================*/
NVM_Mem_JobResult_T NVM_Write_EE(uint32_t dest, uint32_t src, uint8_t num_bytes)
{
    uint8_t block1, block2, sub_pos1, sub_pos2, sub_size1, sub_size2, op1_result, op2_result;
    NVM_Mem_JobResult_T job_result;

    
    block1 = NVM_Get_Block_ID(dest);    
    block2 = NVM_Get_Block_ID((dest+num_bytes)-1);

    if(block2 >= NVM_MAX_B81_ID)
    {
        job_result = NVM_MEM_JOB_FAILED; //out of size
    }
    else if(block2!= block1) 
    {
        sub_pos1 = NVM_Get_SubBlock_Addr(dest);
        sub_pos2 = 0;
        sub_size1 = (uint8_t)NVM_Get_SubBlock_Size(block1, sub_pos1);//size in block1
        //get and check sub_size2
        sub_size2 = (uint8_t)NVM_Get_SubBlock_Size(block2, sub_pos2);   //size in block2
        sub_size2 = (sub_size2 < (num_bytes - sub_size1))? sub_size2 : (num_bytes - sub_size1);
        
        op1_result = NVM_Direct_Write(block1, sub_pos1, (uint8_t *)src, (uint8_t)sub_size1);
        op2_result = NVM_Direct_Write(block2, sub_pos2, (uint8_t *)(src+sub_size1), (uint8_t)sub_size2);
        if((op1_result == NVM_MEM_JOB_OK) && (op2_result == NVM_MEM_JOB_OK))
        {
            job_result = NVM_MEM_JOB_OK; //out of size
        }
        else
        {
            job_result = NVM_MEM_JOB_FAILED; //out of size
        }        
    }
    else
    {
        sub_pos1= NVM_Get_SubBlock_Addr(dest);
        job_result = NVM_Direct_Write(block1, sub_pos1, (uint8_t *)src, num_bytes);
    }    

    /*if(block2 == NVM_CAL_DIM8)
    {
        NVM_Update_Block_Chksum(NVM_CAL_DIM8);
    }*/
    return job_result;
}


/*==============================================================================
* FUNCTION: NVM_Get_DIM_Cal_Data
*===============================================================================
* Return Value:
*    boolean - get successful or not
* Parameters:
*    uint8_t channel : pwm channel
*    uint8_t* dest:    saved buffer
*
*
*  External variables: None
*
*
* Description:
*  here is the standard interface to get calibration data
*
*=============================================================================*/
/*
boolean NVM_Get_DIM_Cal_Data(DIM_CHANNEL_T channel, uint8_t* dest)
{
  
}*/
/*==============================================================================
* FUNCTION: NVM_Update_Block_Chksum
*===============================================================================
* Return Value:
*    boolean - update the chksum successful or not
* Parameters:
*    NVM_Block_Id_T : block id
*
*
*  External variables: None
*
*
* Description:
*  external interface to update a specific block chksum
*
*=============================================================================*/
boolean NVM_Update_Block_Chksum(NVM_Block_Id_T block_id)
{
    uint8_t *nvm_srcptr;
    uint8_t data_size;
    uint8_t length;
   
    if((block_id>=NVM_MAX_B81_ID)||(NVM_Block_Config[block_id].chksum == FALSE))
    {
        return FALSE;
    }

     length = NVM_Mem_config[block_id].Nvm_Length;
     nvm_srcptr = NVM_Mem_config[block_id].Nvm_Srcptr;

     data_size = length - DATA_CRC_SIZE;
     if(E_OK != Getsum((uint32_t)nvm_srcptr, data_size, UPDATE_CHECKSUM, TRUE, (uint16_t*)&nvm_srcptr[data_size]))
     {
         return FALSE;
     }
     if(NVM_MEM_JOB_OK != NVM_Direct_Write_By_ID((uint8_t)block_id))
     {
        return FALSE;
     }
     
     /* Updates CRC Validity flag for all the Blocks */
     NVM_Admin_Block_Status[block_id].CRC_Validity = NVM_CRC_VALID;  
     return TRUE;     
}

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------
*
* Changes for ICS  program
*
* Date            By                        Change
* -------------------------------------------------------------------------------
* 14-May-12  Wade  upgrade the EEL/FAL driver
*    EEL: V106(T03)-->V107(T03), change file: eel.r26
*    change log: 
*    V1.0.3  first release
*    V1.0.4  internal improvements
*    V1.0.5  internal improvements
*    V1.0.6  internal improvements (FIP)
*    V1.0.7   foreground/background data inconsistency bug fixed
*       improved startup sequence (shorter response time)
*       corrected segment switching in C examples
*   FAL: V102(T01) -->V110(T01), change file fal.r26
*   change log:
*   V1.0.0  first release                                       
*   V1.0.1  internal improvement of retry circuit initialization
*   V1.0.2  internal improvements                               
*   V1.1.0   Data Flash read access during DMA transfer problem fixed
*    
* 25-Apr-12  Wade  add the nvm error case handler
* 10-Apr-12  Wade  update the NVM interface to get the dim calbration date 
* 19-Sep-11  Wade  update the algorithm of getting EEPROM data by address 
* 11-Aug-11  Wade  update with new B78 baseline, and add ICS feature   
*******************************************************************************************/
