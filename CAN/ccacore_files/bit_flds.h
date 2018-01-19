#ifndef BIT_FLD_H
#define BIT_FLD_H

#include "can_handler_datatypes.h"
//#include "compiler.h"




/*****************************************************************************
*                                                                            *
*               Corporation, Copyright 2008                            *
*                                                                            *
*****************************************************************************/

/****************************************************************************
 * Program Overview
 ****************************************************************************
 *
 * Program Name: Generic Bit Manipulation Library
 *
 * Version Identifier: 2.0
 *
 * Release Date: tbd
 *
 * Description of Major Functions of program:
 *
 *       This is the header file for bit_fld.c
 *
 * Requirement Reference:
 *
 *  Note: Long_Long types are not yet fully debugged, as no compiler which 
 *  supports long_long types is available at the moment.
 *
 *  Before embarking on a discussion, it is necessary to define a few terms.
 *
 *     1. For the purposes of this libary, the terms used here imply 
 *        integers of the following length in bits:
 *
 *        byte           = 8  bits
 *        word           = 16 bits
 *        long word      = 32 bits
 *        long long word = 64 bits
 *
 *     2. Big Endian/Little Endian refers to which "end" of memory the most 
 *        significant data is stored.  In big endian machines, the most 
 *        significant data (big data) is stored first (lower address), while
 *        in little  endian machines the least signficant data (little data) is
 *        stored first (lower address).  Hence the nomenclature big endian and
 *        little endian. If a big endian machine is used, then data are alwasy
 *        stored in the same order independant of the unit of access(byte,
 *        word, long word, long long word).  That order is:
 *
 *        3,2,1,0 
 *
 *        where 3 is the most signficant byte, word, long word, etc. For 
 *        big endian machines, the data will always be stored in the same
 *        locations no matter whether the data is stored as a bytes, words,
 *        long words or long long words. However, for little endian machines,
 *        the data is stored differently depending on what size integer is
 *        used to store the data. 
 *
 *        For example, if a little endian machine stores
 *        data via a long word, the bytes would be in the following order:
 *        
 *        0,1,2,3
 *
 *        For such an access, the words are reversed in order vs. big endian,
 *        and within the word, the bytes are reversed in order.
 *
 *        On the other hand, if the little endian machine stores the same bytes
 *        via two successive word accesses, the data would be in the following
 *        order:
 * 
 *        2,3,0,1
 *
 *        In this case, only the bytes, and not the words are reversed in the
 *        order they appear in memory.  Therefore, allowing both types of 
 *        access would render an incorrect result. Hence, the user must
 *        be careful not to access the same data with different types or 
 *        via different integer sizes.  The little endian version of this 
 *        library will attempt to mitigate this potential hazard when working
 *        with bit fields and communication buffers.
 *
 *     3. Signed integers and signed bit fields are assumed to be in two's
 *        complement notation.  Signed integers in any other notation may
 *        not work correctly with this library.
 *
 *  C bit fields are not always suitable for two particular applications:
 *  defining communications buffers and defining register bit fields.
 *  The reasons for this inadequacy are documented below.  This library
 *  is intended to provide a suitable bit field capability when C 
 *  bit fields are not adequate.  Note that C bit fields are adequate
 *  for communications buffers when:
 *
 *  (1) The micro-controller is big endian capable and set to un in big endian
 *      mode.
 *  (2) No bit field crosses the boundary of the native word size of the micro
 *      (Note that this may be smaller than the maximum integer supported by
 *      the compiler,e.g. many processors are 16 bit, and therefore C bit 
 *      fields are aligned on 16 bit boundaries even though the compiler
 *      for the microprocessor may support 32 bit integers).
 *
 *  The author believes it is risky to ever use C bit fields for register
 *  definitions.
 * 
 *  While a separate procedure is provided for each capability for each data 
 *  type to support strong type checking in C, macros are also provided for
 *  each capability which call the appropriate function for the specified  data
 *  type.This effectively emulates C++ function overloading, and makes the user
 *  interface simpler.  Additionally, for the single bit operations (set, clear
 *  and test), there is both a macro and function version. The intent is that
 *  if performance is not an overriding consideration, then the "safe" function
 *  version should be used because of its stronger type checking.  However,
 *  there may be applications which can't stand the overhead of a function
 *  call  for these single bit operations which would therefore use the macro
 *  versions.
 *
 *  This library is intended to assist in providing more correct and
 *  reusable code than C bit flds.  C Bit fields have the following 
 *  restrictions:
 *
 *        1.  No bit field can cross the boundary of the native integer
 *            type of a mirco-processor.  Hence, bit fields that would 
 *            cross such a boundary, are aligned on such  boundaries
 *            which is not acceptable for communications buffers which 
 *            are effectively bit arrays where all the bit elements are 
 *            expected to be contiguous.
 *        2.  Bit fields do not adjust for the "endianess" of a micro-
 *            processor to produce a consistent bit array between micro-
 *            processors of differnt "endianess".
 *        3.  Some compilers, when manipulating bit fields, store intermediate
 *            results in the integer data type  containing the bit field.
 *            This is not acceptable when a bit field is mapped to a hardware
 *            register as it may cause erroneous operation.
 *        4.  The order of bits for C bit fields cannot be guranteed between
 *            compilers for a specific micro-processor, much less between 
 *            micro-processors.
 *
 *  The foregoing limitations of C bit fields make it difficult to 
 *  use C bit fields for machine register and communications applications. 
 *
 *  While this library solves many of these shortcomings, it yet falls short
 *  in certain areas as well. 
 *
 *     1. After review, it has been decided to write two separate libraries,
 *        one for big endian processors, and a separate library for little
 *        endian processors.  The big endian version will be completed and
 *        tested first. The little endian version will be released later.
 *
 *     2. This library will only support bit fields which cross the boundary
 *        of the largest integer type supported by the compiler if (1) the
 *        compiler and microprocessor support misaligned integers, and 
 *        (2) the processor is a big endian processor.  The HC12 is big endian
 *        as are all Motorola processors, and supports
 *        misaligned integers.  Misaligned integer support  means that
 *        integers may start on address boundaries which are not an evern 
 *        multiple of the length in bytes of the integer type.  Hence, for 
 *        a 16 bit word, misalignment would consist of allowing words to start
 *        on an odd byte address. Other processors may not support
 *        misalignment. Efforts will be made to remove this restriction in 
 *        the future.
 *
 *  If one is working on a microprocessor which doesn't support misalignment,
 *  or a little endian microprocessor, then the developer should try to
 *  influence the definition of bit fields so that they don't cross the 
 *  boundary of the largest integer type supported by the compiler.  The 
 *  largest integer type supported by the compiler may be larger than the 
 *  word size of the machine.  For instance, it is common for compilers for 
 *  16 bit processors to support 32 bit integers.  It is not yet common for 
 *  compilers for 32 bit microprocessors to support 64 bit integers.
 *
 *  This library, while not as efficient as C bit fields, overcomes sufficient
 *  of the previously identified limitations that it may prove very useful for 
 *  many applications. 

 *  In addition to the foregoing  constraints, the following cautions should
 *  also be  given to a perspective developer.  They are general concerns when
 *  dealing with bit fields using this library.
 *
 *     1. Values provided for writing to bit fields which overflow the 
 *        bit field are not detected.  The least significant bits of the 
 *        value will be written to the bit field.
 *
 *     2. When writing to hardware registers, some registers may not read
 *        back the last value written. To deal with this problem,
 *        it is suggested that the user create a shadow register in RAM, and
 *        define bit fields within this shadow register.  The bit fields in 
 *        the shadow register can be maintained with this library.  After 
 *        updating a bit field within the  shadow register, the user would then
 *        write the entire shadow register to the hardware register.
 *
 *     3. To write to a bit field, this library first performs a read of the
 *        integer type which contains the bit field.  It then updates the bit
 *        field within the integer, and then it writes back to the integer type
 *        which contains the bit field.  The user must make sure this
 *        process does not produce any undesireable side effects for their
 *        application.
 *
 *     4. For little endian machines, it is necessary to restrict access
 *        to bit fields via the longest type supported.  Otherwise, the
 *        results would be incorrect per a previous discussion on this issue.
 *
 * For single bit operations (set, clear, and test) the user can call macros
 * or functions which directly operate on the specified integer. However, for
 * multi bit bit fields,  a bit field is defined by declaring an instance of
 * one of the bit field types delcared in this header file. (See below).
 *
 * Note that the term first_bit refers to the first bit of the 
 * bit field starting with bit 7 for 8 bit integers (most significant bit), 
 * bit 15 for 16 bit integers, bit 31 for 32 bit integers, and bit 63 for 
 * 64 bit registers. while the term last_bit refers to the bit of the bit
 * field closest to bit 0 (least significant bit).  It is understood that 
 * the order of bits within an integer is the same for both big endian and
 * little endian processors.
 *
 * The Signed field of the bit field structure indicates whether the bit
 * field is signed or not.
 *
 * This library then provides routines to read and write multi bit bit
 * fields. These bit fields can exist within  individual bytes, words, 
 * long words, or bit arrays (communication buffers) longer than  a long
 *  word. 
 *
 * When mapping bit fields to registers, these registers should always be one
 * of the native discrete types supported by the micro processor. However, if
 * a 64 bit discrete type is not supported, then the declaration of type for
 * a bit array for a communication buffer longer than 32 bits might appear as
 * follows:
 *
 * see definition below 
 *
 * Remember that to enforce the use of long words or long long words for 
 * communications buffers when the processor type is little endian, then those
 * buffers must be multiples of long words (4/8 bytes).  Failure to abide by 
 * this constraint may produce incorrect results.
 *
 * The following is an example of the declarations of a bit field mapped to
 * a register (see typedefs in this file below):
 *
 *  #define CLK_DIV2           0
 *  #define CLK_DIV4           1
 *  #define CLK_DIV8           2
 *  #define CLK_DIV16          3
 *
 *  const Byte_Bit_Fld_T Clk_Div_Reg = { (canuint8_t *)0xffaa,7,6}
 *
 *  Notice that this declaration is for a constant so that the definition of
 *  the  bit field will be stored in ROM instead of RAM.
 *
 *  After this declaration, it would then be possible to write the following
 *  code:
 *
 *  Write_Byte_Bit_Fld(Clk_Div_Reg, CLK_DIV4);
 *  
 *  Which writes a 1 to bits 7-6 of the byte at 0xffaa.  It should be noted
 *  that this libary prevents the compiler from storing intermediate results in
 *  the register, something that has been observed by some compilers when bit
 *  fields are used.  If intermediate results are stored in a register, then
 *  this normally results in a failure.
 *  
 *  Of course more bit fields could be defined within this byte and manipulated
 *  with this library.  Other bit fields mapped to other registers could also
 *  be defined for word and long word types if appropriate.
 *
 *  The declaration of a communications buffer for a CAN message might be
 *  accomplished  as follows:
 *  
 *  CAN_Msg_Buf_T ECM_CAN_Message;
 *
 *  const Word_Bit_Fld_T CAN_Vehicle_Speed = {&ECM_CAN_Message[2],12,0};
 *  
 *  Note:  It is very important to declare bit fields as constants, since 
 *         this allows the compiler to perform many of the operations
 *         related to bit field management.  Otherwise, these operations
 *         will have to be performed at run time, and this could significantly
 *         degrade performance of this library.
 *
 *  It would then be possible to write the following code:
 *
 *  canuint16_t  Vehicle_Speed = 0;
 *  .
 *  .
 *  .
 *  Write_Word_Bit_Fld(CAN_Vehicle_Speed, Vehicle_Speed);
 *
 *  Which writes the internal 16 bit Vehicle_Speed variable to 12 bits within
 *  the  CAN message, bytes 2 & 3,  bits 0-12 which is the same as byte 2,
 *  bits 7-0, and byte 3, bits 7-4 in big endian notation.
 *
 *  To accomplish the same thing for a bit field which crosses the boudary of
 *  the largest type supported, one can do the following provided that the 
 *  micro-controller is of big endian type and supports misaligned words ( this
 *  is true of the HC12).
 *
 *  CAN_Msg_Buf_T ECM_CAN_Message;
 *
 *  const Word_Bit_Fld_T CAN_Vehicle_Speed = {&ECM_CAN_Message[7],12,0};
 *
 *  It would then be possible to write the following code:
 *
 *  canuint16_t  Vehicle_Speed = 0;
 *  .
 *  .
 *  .
 *  Write_Word_Bit_Fld(CAN_Vehicle_Speed, Vehicle_Speed);
 *
 *  Which writes the internal 16 bit Vehicle_Speed variable to 12 bits within
 *  the CAN message, bytes 7 & 8,  bits 0-12 which is the same as byte 7, bits
 *  7-0,  and byte 8, bits 7-4. 
 *
 *  The capability of working with a bit field which crosses the boundry of 
 *  the largest integer supported by the compiler is not yet supported for
 *  micros which are little endian or which do not support misaligned words.
 *  In such a case, the user will have to hand code such an operation. For
 *  most modern micro processors, this  would involve fields which crossed 32
 *  bit boundaries, since most micro controllers, even 16 bit micro-
 *  controllers, support 32 bit discrete types.
 *
 *  An attempt will be made to come up with a sufficiently efficient solution
 *  to this problem so that this capability can be added in the future.
 *
 *  This library was originally written for register bit fields, but has now
 *  been generalized to handle communications buffers.  The term register is
 *  therefore used frequently, but  the user should think in more general terms
 *  than hardware registers as appropriate.
 *
 ****************************************************************/

/****************************************************************
 * #defines for configuration
 ***************************************************************/


typedef struct {
    canuint8_t *addr;      /* address of byte containing the bit fld    */
    canuint8_t first_bit;  /* bit closest to bit 7                      */
    canuint8_t last_bit;   /* bit closest to bit 0                      */
}Byte_Bit_Fld_T;

typedef struct {
    canuint16_t *addr;     /* address of word containing the bit field  */
    canuint8_t first_bit;  /* bit closest to bit 15                     */
    canuint8_t last_bit;   /* bit closes  to bit 0                      */
}Word_Bit_Fld_T;

typedef struct {
    canuint32_t *addr;     /* address of long word containing bit field */
    canuint8_t first_bit;  /* bit closest to bit 31                     */
    canuint8_t last_bit;   /* bit closest to bit 0                      */
}Long_Word_Bit_Fld_T;






/*****************************************************************
 *  Prototyes
 *****************************************************************/



void Write_Byte_Bit_Fld(const Byte_Bit_Fld_T *Byte_Bit_Fld, 
                          canuint8_t     new_value);

void Write_Word_Bit_Fld(const Word_Bit_Fld_T *Word_Bit_Fld, 
                          canuint16_t    new_value);

void Write_Long_Word_Bit_Fld(const Long_Word_Bit_Fld_T *Long_Word_Bit_Fld, 
                               canuint32_t         new_value);

extern canuint8_t   Read_Byte_Bit_Fld(const Byte_Bit_Fld_T *bit_fld);
extern canuint16_t  Read_Unsigned_Word_Bit_Fld(const Word_Bit_Fld_T *bit_fld);
extern canuint16_t  Read_Unsigned_Word_From_Odd_Add_Bit_Fld(const Word_Bit_Fld_T *bit_fld);
extern cansint16_t  Read_Signed_Word_Bit_Fld(const Word_Bit_Fld_T *bit_fld);
extern canuint32_t  Read_Unsigned_Long_Word_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld);

extern canuint32_t  Read_Unsigned_Long_Word_From_Odd_Add_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld);
extern void Write_Word_Into_Odd_Add_Bit_Fld(const Word_Bit_Fld_T *bit_fld, 
                                          canuint16_t new_value);
extern void Write_Long_Word_Into_Odd_Add_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld, 
                                             canuint32_t new_value);



/* returns TRUE (1) if successful, otherwise returns FALSE (0) 
 * will fail if ENDIANCESS == LITTLE_ENDIAN and buffer is not a
 * multiple of integer size used for little endian (4 or 8). 
 * Will work incorrectly if reverse method is not
 * consistent with the actual byte ordering
 */ 


/*  */
/*********************************************************
 * Function Macros
 *********************************************************/

/*****************************************************************/
/* MACRO NAME   : Clear_Bit                                      */
/* Inputs       : addr                                           *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This macro    accepts the address of a simple  *
 *                register, and a bit no. within this register.  *
 *                The function uses this information to set      *
 *                the specified bit to zero (0) (clear the bit). *
 *                This function is implemented as a #define      *
 *                macro and does no type checking, and so will   *
 *                work on registers of any length.  The user is  *
 *                responsible to provide valid types.            *
 *                This version of the function will also expand  *
 *                in line.                                       *
 *                This function shifts one(1) left bit_no        *
 *                positions and then takes the one's complement  *
 *                of the resulting value. The result is a mask   *
 *                consisting of all one's except at position     *
 *                bit_no.  ANDing this mask with the register    *
 *                value zeros the bit in bit_no position.        *
 *                                                               *
 ****************************************************************/



/*  */
/*****************************************************************/
/* MACRO NAME   : Set_Bit                                        */
/* Inputs       : addr                                           *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This macro    accepts the address of a         *
 *                register, and a bit no. within this reg.       *
 *                The function uses this information to set      *
 *                the specified bit to one (1) (set  the bit).   *
 *                This function is implemented as a #define      *
 *                macro and does no type checking, and so will   *
 *                work on registers of any length.  The user is  *
 *                responsible to provide valid types             *
 *                This version of the function will also expand  *
 *                in line.                                       *
 *                This macro creates a mask of all zero's except *
 *                for a one(1) at bit_no position.  ORing this   *
 *                mask with the register value turns on the bit  *
 *                at bit_no position.                            *
 *                                                               *
 ****************************************************************/




/*  */
/****************************************************************
 * MACRO NAME   : Test_Bit                                      *
 * Inputs       : addr                                          *
 *                bit_no                                        *
 * Outputs      : bit value ( 0 or 1)                           *
 *                                                              *
 * Description  : This macro returns a 1 if the                 *
 *                specified bit is set, otherwise, it returns   *
 *                zero.                                         *
 *                This macro creates a mask of all zeros except *
 *                at bit_no position which will contain a 1.    *
 *                When ANDed with the register value, the result*
 *                will be all zeros if the bit in bit_no        *
 *                position of the register is zero, or the value*
 *                2 raised to bit_no power if the bit in bit_no *
 *                position of the register is 1.  To allow the  *
 *                result to fit in a boolean_T or canuint8_t,  *
 *                even if a bit in a longer  integer is being   *
 *                tested, the result bit is shifted back again  *
 *                to the rightmost position.                    *
 *                                                              *
 ***************************************************************/



/*****************************************************************
 * MACRO NAME   : Read_Signed_Bit_Fld                          *
 * Inputs       : Bit Fld Structure of one of the following    *
 *                types:                                         *
 *                Byte_Bit_Fld_T, Word_Bit_Fld_T                 *
 *                Long_Word_Bit_Fld_T, Long_Long_Word_Bit_Fld_T  *
 *                                                               *
 * Outputs      : Var - takes value read                         *
 *                                                               *
 * Description  : This macro performs C++ type function          *
 *                overloading of signed bit field read functions,*
 *                by calling the read function specific to the   *
 *                bit_fld type the user has spcecified via the   *
 *                function parameter list.  While this macro     *
 *                generates extraneous code, the optimizer will  *
 *                remove the extraneous code which turns out     *
 *                to be unreachable, and a good optimizer will   *
 *                recognize that.                                *
 ****************************************************************/

/******************************************************************
 *  Read_Signed_Bit_Fld(Var, ______Bit_Fld_T)
 ******************************************************************/



/*****************************************************************
 * MACRO NAME   : Read_Unsigned_Bit_Fld                        *
 * Inputs       : Bit Fld Structure of one of the following    *
 *                types:                                         *
 *                Byte_Bit_Fld_T, Word_Bit_Fld_T                 *
 *                Long_Word_Bit_Fld_T, Long_Long_Word_Bit_Fld_T  *
 *                                                               *
 * Outputs      : Var - takes value read                         *
 *                                                               *
 * Description  : This macro performs C++ type function          *
 *                overloading of unsigned bit field read functions,*
 *                by calling the read function specific to the   *
 *                bit_fld type the user has spcecified via the   *
 *                function parameter list.  While this macro     *
 *                generates extraneous code, the optimizer will  *
 *                remove the extraneous code which turns out     *
 *                to be unreachable, and a good optimizer will   *
 *                recognize that.                                *
 ****************************************************************/

/******************************************************************
 *  Read_Unsigned_Bit_Fld(Var,Bit_Fld_Def)
 ******************************************************************/



/*****************************************************************
 * MACRO NAME   : Write_Bit_Fld                                  *
 * Inputs       : Bit Fld Structure of one of the following      *
 *                types:                                         *
 *                Byte_Bit_Fld_T, Word_Bit_Fld_T                 *
 *                Long_Word_Bit_Fld_T, Long_Long_Word_Bit_Fld_T  *
 *                                                               *
 * Outputs      : Var - Value to be written to bit field         *
 *                                                               *
 * Description  : This macro performs C++ type function          *
 *                overloading of bit field write functions,      *
 *                by calling the write function specific to the  *
 *                bit_fld type the user has spcecified via the   *
 *                function parameter list.  While this macro     *
 *                generates extraneous code, the optimizer will  *
 *                remove the extraneous code which turns out     *
 *                to be unreachable, and a good optimizer will   *
 *                recognize that.                                *
 ****************************************************************/

/******************************************************************
 *  Write_Bit_Fld(Bit_Fld_Def, Var)
 ******************************************************************/


#define Write_Bit_Fld(Bit_Fld_Def, Var)\
do\
{\
     if(1 == sizeof(*Bit_Fld_Def.addr))\
     {\
         Write_Byte_Bit_Fld((Byte_Bit_Fld_T *)(&Bit_Fld_Def),Var);\
     }\
     else if(2 == sizeof(*Bit_Fld_Def.addr))\
     {\
        Write_Word_Bit_Fld((Word_Bit_Fld_T *)(&Bit_Fld_Def),Var);\
     }\
     else if(4 == sizeof(*Bit_Fld_Def.addr))\
     {\
        Write_Long_Word_Bit_Fld((Long_Word_Bit_Fld_T*)(&Bit_Fld_Def),Var);\
     }\
}while(0)

/*  */
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08    Mahipal         Created initial version of this file       *
 ******************************************************************************/

/*
* $SOURCE: misc_project@kokomo.1422:acc2_jaguar:bit_flds.h $
* $REVISION: 1.2 $
* $AUTHOR: kokomo.1422:/users/tcompton/dsds/pcs:tcompton $
*/

#endif

