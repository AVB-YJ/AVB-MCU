#ifndef SYSTYPE_H
#define SYSTYPE_H
/*===================================================================*\
*--------------------------------------------------------------------
* Module Name:     systype.h
* Created By:      fz6q8d
* Created Date:    Wed Dec 26 17:38:47 2007
* %version:        1 %
* %cvtype:         incl %
* %instance:       ctc_aud_5 %
* %derived_by:     lzs7ws %
* %date_created:  Tue Jun 26 15:37:04 2012 %
*--------------------------------------------------------------------
*
* Description:
*   This file contains the generic data type definition
*
* Traces to: NONE
*
*
* Applicable Standards (in order of precedence: highest first):
*     SW REF 264.15D "DE Systems C Coding Standards" dated 12-Mar-2006
*
* Deviations from Delco C Coding standards:
*   1. C46 - Abbreviations are not documented in this source file.
*
*   2. C54 - Function header block is placed at the beginning of
*      function definition instead before function proto type
*      declaration.
*
*   3. C58 - Function header blocks only list global variables that
*      are not accessed by macros or functions.
*
*   4. C60 - The function is pre-emptible or re-entrant is not
*      applicable to this program.
*   <Write any other deviations from Delco C Coding  Standards >
\*===================================================================*/

/*===========================================================================*\
* Standard Header Files
\*===========================================================================*/
#ifndef  CUNIT_TEST
#include "intrinsics.h"
#endif

/*===========================================================================*\
* Other Header Files
\*===========================================================================*/

/*===========================================================================*\
* Exported Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
* Exported Preprocessor #define MACROS
\*===========================================================================*/
/* -------------------------------------------------------------------
* Minimum width integer types
* ---------------------------------------------------------------- */
#define UINT8_MIN    (0)
#define UINT8_MAX    (255)
#define UINT16_MIN   (0)
#define UINT16_MAX   (65535)
#define UINT32_MIN   (0)
#define UINT32_MAX   (4294967295U)

#define INT8_MIN     (-128)
#define INT8_MAX     (127)
#define INT16_MIN    (-32768)
#define INT16_MAX    (32767)
#define INT32_MIN    (-2147483648)
#define INT32_MAX    (2147483647)


/*===========================================================================*\
* Exported Enum constants
\*===========================================================================*/

/*===========================================================================*\
* Exported Type Declarations
\*===========================================================================*/
typedef  unsigned char     uint8_t;
typedef  signed char       int8_t;
typedef  unsigned short    uint16_t;
typedef  signed short      int16_t;

#ifndef  CUNIT_TEST
typedef  unsigned long uint32_t;
typedef  signed long   int32_t;
#else
typedef  unsigned int uint32_t;
typedef  signed int   int32_t;
#endif


typedef  unsigned char     bool_t;
//typedef  unsigned char     bitfield8_t;
typedef  unsigned int      size_t;

typedef unsigned char   uint_fast8_t;     // unsigned fast 8 bits
typedef unsigned int    uint_fast16_t;    // unsigned fast 16 bits
#ifndef  CUNIT_TEST
typedef unsigned long   uint_fast32_t;    // unsigned fast 32 bits
#else
typedef unsigned int   uint_fast32_t;    // unsigned fast 32 bits
#endif

#define BIT15  (0x8000U)
#define BIT14  (0x4000U)
#define BIT13  (0x2000U)
#define BIT12  (0x1000U)
#define BIT11  (0x0800U)
#define BIT10  (0x0400U)
#define BIT9   (0x0200U)
#define BIT8   (0x0100U)
#define BIT7   (0x0080U)
#define BIT6   (0x0040U)
#define BIT5   (0x0020U)
#define BIT4   (0x0010U)
#define BIT3   (0x0008U)
#define BIT2   (0x0004U)
#define BIT1   (0x0002U)
#define BIT0   (0x0001U)
#define NOBIT  (0x0000U)
#define ALLBITS (0xFFFFU)

#undef FALSE
#define FALSE  ((bool_t)(1==0))
#undef TRUE
#define TRUE   ((bool_t)(0==0))

#undef false
#define false  (FALSE)
#undef true
#define true   (TRUE)

#ifndef STD_OFF
#define STD_OFF      (0u)  /** Switch - option disabled */
#endif
#ifndef STD_ON
#define STD_ON       (1u)  /** Switch - option enabled */
#endif


#ifndef NULL
#define NULL   ((void*)0)
#endif

typedef  void (*void_fptr) (void);                 // void void Function pointer typedef


typedef enum   Status_Type_Tag                   // Return status from RTOS functions
   {
      E_IIC_OK             =  0,                    // NO Error, successful
      E_OK = E_IIC_OK,
      E_IIC_ERROR,                                  // General Error
      E_ERROR              = E_IIC_ERROR,
      E_OS_ACCESS,
      E_OS_CALLEVEL,
      E_OS_ID,
      E_OS_LIMIT,
      E_OS_NOFUNC,
      E_OS_RESOURCE,
      E_OS_STATE,
      E_OS_VALUE,
      E_COM_NOMSG,
      E_COM_LOCKED,
      E_TASK_SUSPENDED,
      E_TIMEOUT,                                // Error due to timeout
      E_OUT_OF_RANGE,                           // Error due to parameter out of range
      E_INVALID_CONDITION                       // Error due to invalid conditions
} Status_Type;

typedef unsigned char   bitfield8_t;      // unsigned 8 bits
typedef unsigned short  bitfield16_t;     // unsigned 16 bits
typedef unsigned long int    bitfield32_t;     // unsigned 32 bits

typedef struct                            /* generic type to access INT32 in INT16 size */
{
   uint16_t LS;
   uint16_t MS;
}  INT32_2_INT16_Type;

typedef struct                            /* generic type to access INT32 to INT8s size */
{
   uint8_t  Int8_0;
   uint8_t  Int8_1;
   uint8_t  Int8_2;
   uint8_t  Int8_3;
}  INT32_2_INT8_Type;

/*-----------------------------------
  Data Structure for Word
-----------------------------------*/
typedef struct                            /* generic type to access INT16 in INT8 size */
{
   uint8_t LS;
   uint8_t MS;
}   INT16_2_INT8_Type;

typedef struct                            /* generic type to access INT16 in BIT size */
{
   bitfield16_t Bit0     :1;
   bitfield16_t Bit1     :1;
   bitfield16_t Bit2     :1;
   bitfield16_t Bit3     :1;
   bitfield16_t Bit4     :1;
   bitfield16_t Bit5     :1;
   bitfield16_t Bit6     :1;
   bitfield16_t Bit7     :1;
   bitfield16_t Bit8     :1;
   bitfield16_t Bit9     :1;
   bitfield16_t Bit10    :1;
   bitfield16_t Bit11    :1;
   bitfield16_t Bit12    :1;
   bitfield16_t Bit13    :1;
   bitfield16_t Bit14    :1;
   bitfield16_t Bit15    :1;
}  INT16_2_Bits_Type;

typedef struct                            /* generic type to access INT32 to BIT size*/
{
   bitfield32_t Bit0     :1;
   bitfield32_t Bit1     :1;
   bitfield32_t Bit2     :1;
   bitfield32_t Bit3     :1;
   bitfield32_t Bit4     :1;
   bitfield32_t Bit5     :1;
   bitfield32_t Bit6     :1;
   bitfield32_t Bit7     :1;
   bitfield32_t Bit8     :1;
   bitfield32_t Bit9     :1;
   bitfield32_t Bit10    :1;
   bitfield32_t Bit11    :1;
   bitfield32_t Bit12    :1;
   bitfield32_t Bit13    :1;
   bitfield32_t Bit14    :1;
   bitfield32_t Bit15    :1;
   bitfield32_t Bit16    :1;
   bitfield32_t Bit17    :1;
   bitfield32_t Bit18    :1;
   bitfield32_t Bit19    :1;
   bitfield32_t Bit20    :1;
   bitfield32_t Bit21    :1;
   bitfield32_t Bit22    :1;
   bitfield32_t Bit23    :1;
   bitfield32_t Bit24    :1;
   bitfield32_t Bit25    :1;
   bitfield32_t Bit26    :1;
   bitfield32_t Bit27    :1;
   bitfield32_t Bit28    :1;
   bitfield32_t Bit29    :1;
   bitfield32_t Bit30    :1;
   bitfield32_t Bit31    :1;
}  INT32_2_Bits_Type;

typedef union                             /* generic type to access INT16 */
{
   uint16_t          Int16;
   INT16_2_INT8_Type Int8;
   INT16_2_Bits_Type Bits;
}  Mixed_INT16_Type;

typedef union                             /* generic type to access INT32 */
{
    uint32_t           Int32;
    INT32_2_INT16_Type Int16;
    INT32_2_INT8_Type  Int8;
    INT32_2_Bits_Type  Bits;
}   Mixed_INT32_Type;


typedef unsigned long   u32;

#ifndef BOOLEAN_IS_DEFINED
#define BOOLEAN_IS_DEFINED
typedef  uint8_t  BOOLEAN;                // logical true/false (0 = FALSE)
#endif

/*===========================================================================*\
 * File Revision History (top to bottom: last revision to first revision)
 *===========================================================================
 * Date          userid    (Description on following lines: SCR #, etc.)
 * -----------  --------   --------------------------------------------------
 *
 * 02-May-2011   Wade Li
 * + Created initial file, reused from Corvette project
 *   - Create compilation switch to choose between different hardware version
 *
\*===========================================================================*/
#endif /* SYSTYPE_H   */
