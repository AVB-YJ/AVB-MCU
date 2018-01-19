/*****************************************************************************
*                                                                            *
*               Corporation, Copyright 2008                            *
*                                                                            *
*****************************************************************************/

/****************************************************************************
 * Program Overview
 ****************************************************************************
 *
 * Program Name: PCS (PreCrash Sensor)
 *
 *
 * Description of Major Functions of program:
 *
 *  See bit_flds.h
 *
 ***************************************************************/

#include "bit_flds.h"
#include "bit_flds_config.h"
/**************************************************************
 *  #defines
 **************************************************************/


/*********************************************************
 * Local Prototypes
 *********************************************************/
/* The following functions support conversion of a buffer between
 * big and little endian ordering of the data
 */


/*********************************************************
 * module data
 *********************************************************/

   const static canuint8_t first_bit_mask_8[8] =   
   {0xfe, 0xfc, 0xf8, 0xf0,
    0xe0, 0xc0, 0x80, 0x00};

   const static canuint8_t last_bit_mask_8[8]  =   
   {0x01, 0x03, 0x07,0x0f,
    0x1f, 0x3f, 0x7f,0xff};

   const static canuint16_t first_bit_mask_16[16]= 
   {0xfffe, 0xfffc, 0xfff8, 0xfff0,
    0xffe0, 0xffc0, 0xff80, 0xff00,
    0xfe00, 0xfc00, 0xf800, 0xf000,
    0xe000, 0xc000, 0x8000, 0x0000};

   const static canuint16_t last_bit_mask_16[16] = 
   {0x0001, 0x0003, 0x0007,0x000f,
    0x001f, 0x003f, 0x007f,0x00ff,
    0x01ff, 0x03ff, 0x07ff,0x0fff,
    0x1fff, 0x3fff, 0x7fff,0xffff};

   const static canuint32_t first_bit_mask_32[32]= 
   {0xfffffffe, 0xfffffffc, 0xfffffff8, 0xfffffff0,
    0xffffffe0, 0xffffffc0, 0xffffff80, 0xffffff00,
    0xfffffe00, 0xfffffc00, 0xfffff800, 0xfffff000,
    0xffffe000, 0xffffc000, 0xffff8000, 0xffff0000,
    0xfffe0000, 0xfffc0000, 0xfff80000, 0xfff00000,
    0xffe00000, 0xffc00000, 0xff800000, 0xff000000,
    0xfe000000, 0xfc000000, 0xf8000000, 0xf0000000,
    0xe0000000, 0xc0000000, 0x80000000, 0x00000000};

   const static canuint32_t last_bit_mask_32[32] = 
   {0x00000001, 0x00000003, 0x00000007,0x0000000f,
    0x0000001f, 0x0000003f, 0x0000007f,0x000000ff,
    0x000001ff, 0x000003ff, 0x000007ff,0x00000fff,
    0x00001fff, 0x00003fff, 0x00007fff,0x0000ffff,
    0x0001ffff, 0x0003ffff, 0x0007ffff,0x000fffff,
    0x001fffff, 0x003fffff, 0x007fffff,0x00ffffff,
    0x01ffffff, 0x03ffffff, 0x07ffffff,0x0fffffff,
    0x1fffffff, 0x3fffffff, 0x7fffffff,0xffffffff};


/* LONG_LONG is not yet debugged */








/****************************************************
 *  bit_flds Test Code
 *  comment out this function when through testing
 ****************************************************/

/****************************************************************/
/*         single bit bit field operations                      */
/****************************************************************/

/****************************************************************/
/* FUNCTION NAME: Clear_Byte_Bit                                */
/* Inputs       : bit_fld_addr                                  */
/*                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of an 8 bit  *
 *                variable, and a bit no within this 8 bit bit_fld.*
 *                The function uses this information to set      *
 *                the specified bit to zero (0) (clear the bit.  *
 *                                                               *
 *                This function shifts one(1) left bit_no        *
 *                positions and then takes the one's complement  *
 *                of the resulting value. The result is a mask   *
 *                consisting of all one's except at position     *
 *                bit_no.  ANDing this mask with the variable    *
 *                value zeros the bit in bit_no position.        *
 *                                                               *
 ****************************************************************/





/*  */
/*****************************************************************/
/* FUNCTION NAME: Clear_Word_Bit                                 */
/* Inputs       : bit_fld_addr                                   *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of a 16 bit  *
 *                variable, and a bit no within this 16 bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to zero (0) (clear the bit). *
 *                                                               *
 *                This function shifts one(1) left bit_no        *
 *                positions and then takes the one's complement  *
 *                of the resulting value. The result is a mask   *
 *                consisting of all one's except at position     *
 *                bit_no.  ANDing this mask with the variable    *
 *                value zeros the bit in bit_no position.        *
 *                                                               *
 *                                                               *
 ****************************************************************/


/*****************************************************************/
/* FUNCTION NAME: Clear_Long_Word_Bit                            */
/* Inputs       : bit_fld_addr                                   *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of a 32 bit  *
 *                variable, and a bit no within this 32 bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to zero (0) (clear the bit). *
 *                                                               *
 *                This function shifts one(1) left bit_no        *
 *                positions and then takes the one's complement  *
 *                of the resulting value. The result is a mask   *
 *                consisting of all one's except at position     *
 *                bit_no.  ANDing this mask with the variable    *
 *                value zeros the bit in bit_no position.        *
 *                                                               *
 *                                                               *
 ****************************************************************/


/*****************************************************************/
/* FUNCTION NAME: Clear_Long_Long_Word_Bit                       */
/* Inputs       : bit_fld_addr                                   *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of a 32 bit  *
 *                variable, and a bit no within this 32 bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to zero (0) (clear the bit). *
 *                                                               *
 *                This function shifts one(1) left bit_no        *
 *                positions and then takes the one's complement  *
 *                of the resulting value. The result is a mask   *
 *                consisting of all one's except at position     *
 *                bit_no.  ANDing this mask with the variable    *
 *                value zeros the bit in bit_no position.        *
 *                                                               *
 *                                                               *
 ****************************************************************/

/*  */
/*****************************************************************
 * FUNCTION NAME: Set_Word_Bit                                   *
 * Inputs       : bit_fld_addr                                   *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of a 16 bit  *
 *                variable, and a bit no within this 16 bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to one (1) (set   the bit).  *
 *                                                               *
 *                This macro creates a mask of all zero's except *
 *                for a one(1) at bit_no  position.  ORing this  *
 *                mask with the variable value turns on the bit  *
 *                at bit_no position.                            *
 *                                                               *
 *****************************************************************/




/*  */
/*****************************************************************
 * FUNCTION NAME: Set_Byte_Bit                                   *
 * Inputs       : reg_addr                                       *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of an 8 bit  *
 *                variable, and a bit no within this 8  bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to one (1) (set   the bit).  *
 *                                                               *
 *                This macro creates a mask of all zero's except *
 *                for a one(1) at bit_no, position.  ORing this  *
 *                mask with the variable value turns on the bit  *
 *                at bit_no position.                            *
 *                                                               *
 *****************************************************************/


/*****************************************************************
 * FUNCTION NAME: Set_Long_Word_Bit                              *
 * Inputs       : reg_addr                                       *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of an 32 bit *
 *                variable, and a bit no within this 32  bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to one (1) (set   the bit).  *
 *                                                               *
 *                This macro creates a mask of all zero's except *
 *                for a one(1) at bit_no, position.  ORing this  *
 *                mask with the variable value turns on the bit  *
 *                at bit_no position.                            *
 *                                                               *
 *****************************************************************/

/* void Set_Long_Word_Bit(canuint32_t *bit_fld_addr, 
                       canuint8_t   bit_no)
{

   *bit_fld_addr = *bit_fld_addr | (1 << bit_no);
}
*/

/*****************************************************************
 * FUNCTION NAME: Set_Long_Long_Word_Bit                         *
 * Inputs       : reg_addr                                       *
 *                bit_no                                         *
 * Outputs      : none                                           *
 *                                                               *
 * Description  : This function accepts the address of an32 bit  *
 *                variable, and a bit no within this 32  bit bit_fld. *
 *                The function uses this information to set      *
 *                the specified bit to one (1) (set   the bit).  *
 *                                                               *
 *                This macro creates a mask of all zero's except *
 *                for a one(1) at bit_no, position.  ORing this  *
 *                mask with the variable value turns on the bit  *
 *                at bit_no position.                            *
 *                                                               *
 *****************************************************************/



/*  */
/****************************************************************
 * NAME         : Test_Byte_Bit                                 *
 * Inputs       : addr                                          *
 *                bit_no                                        *
 * Outputs      : bit value ( 0 or non 1)                       *
 *                                                              *
 * Description  : This macro returns a non zero value if the    *
 *                specified bit is set, otherwise, it returns   *
 *                zero.                                         *
 *                This subroutine  creates a mask of all zeros  *
 *                except at bit_no position which will contain a 1.*
 *                When ANDed with the register value, the result*
 *                will be all zeros if the bit in bit_no        *
 *                position of the register is zero, or 1 if the *
 *                bit in bit_no position of the register is 1.  *
 *                                                              *
 ***************************************************************/

/*  */
/****************************************************************
 * NAME         : Test_Word_Bit                                 *
 * Inputs       : addr                                          *
 *                bit_no                                        *
 * Outputs      : bit value ( 0 or non 0)                       *
 *                                                              *
 * Description  : This macro returns a non zero value if the    *
 *                specified bit is set, otherwise, it returns   *
 *                zero.                                         *
 *                This subroutine  creates a mask of all zeros  *
 *                except at bit_no position which will contain a 1.*
 *                When ANDed with the register value, the result*
 *                will be all zeros if the bit in bit_no        *
 *                position of the register is zero, or 1 if the *
 *                bit in bit_no position of the register is 1.  *
 *                                                              *
 ***************************************************************/
/****************************************************************
 * NAME         : Test_Long_Word_Bit                            *
 * Inputs       : addr                                          *
 *                bit_no                                        *
 * Outputs      : bit value ( 0 or non 0)                       *
 *                                                              *
 * Description  : This macro returns a non zero value if the    *
 *                specified bit is set, otherwise, it returns   *
 *                zero.                                         *
 *                This subroutine  creates a mask of all zeros  *
 *                except at bit_no position which will contain a 1.*
 *                When ANDed with the register value, the result*
 *                will be all zeros if the bit in bit_no        *
 *                position of the register is zero, or 1 if the *
 *                bit in bit_no position of the register is 1.  *
 *                                                              *
 ***************************************************************/

/****************************************************************
 * NAME         : Test_Long_Long_Word_Bit                       *
 * Inputs       : addr                                          *
 *                bit_no                                        *
 * Outputs      : bit value ( 0 or non 0)                       *
 *                                                              *
 * Description  : This macro returns a non zero value if the    *
 *                specified bit is set, otherwise, it returns   *
 *                zero.                                         *
 *                This subroutine  creates a mask of all zeros  *
 *                except at bit_no position which will contain a 1.*
 *                When ANDed with the register value, the result*
 *                will be all zeros if the bit in bit_no        *
 *                position of the register is zero, or 1 if the *
 *                bit in bit_no position of the register is 1.  *
 *                                                              *
 ***************************************************************/

/*  */
/******************************************************************/
/*         multiple bit bit field operations                      */
/******************************************************************/


/******************************************************************/
/* FUNCTION NAME: Read_Signed_Byte_Bit_Fld                        */
/* Inputs       : *bit_fld structure containing bit field parameters: */
/*                bit_fld_addr                                    */
/*                first_bit                                       */
/*                last_bit                                        */
/* Outputs      : bit field value read                            */
/*                                                                */
/* Description  : This function accepts as input the parameters   */
/*                which define a bit field within an 8 bit        */
/*                variable.  The function uses these parameters   */
/*                to read the variable and isolate the value      */
/*                of the specified bit field. This value is       */
/*                returned by the function                        */
/*                                                                */
/*                If the sign bit is set, this function right     */
/*                aligns the bit field with the following         */
/*                expression:                                     */
/*                                                                */
/*                   (*bit_fld->addr >> (bit_fld->first_bit))     */
/*                                                                */
/*                It then extends the sign bit left with the      */
/*                following expression:                           */
/*                                                                */
/*                   | last_bit_mask_8[bit_fld->first_bit -       */
/*                   bit_fld->last_bit + 1]                       */
/*                                                                */
/*                Note that the value to be or'ed can be fully    */
/*                resolved by the compiler if the bit field has   */
/*                been declared as a constant as it should be.    */
/*                                                                */
/*                If the sign bit is not set, this function       */
/*                behaves the same as an unsigned read.  See      */
/*                documentation for unsigned read.                */
/*                                                                */
/*                The resulting value is returned to the calling  */
/*                routine.                                        */
/*                                                                */
/******************************************************************/


/******************************************************************/
/* FUNCTION NAME: Read_Unsigned_Byte_Bit_Fld                       */
/* Inputs       : *bit_fld structure containing bit field parameters: */
/*                bit_fld_addr                                    */
/*                first_bit                                       */
/*                last_bit                                        */
/* Outputs      : bit field value read                            */
/*                                                                */
/* Description  : This function accepts as input the parameters   */
/*                which define a bit field within an 8 bit        */
/*                variable.  The function uses these parameters   */
/*                to read the variable and isolate the value      */
/*                of the specified bit field. This value is       */
/*                returned by the function                        */
/*                                                                */
/*                This routine right aligns the requested bit     */
/*                field with the following expression:            */
/*                                                                */
/*                   (*bit_fld->addr >> (bit_fld->last_bit))      */
/*                                                                */
/*                It then sets the high order bits to zero with   */
/*                the following expression:                       */
/*                                                                */
/*                   & last_bit_mask_8[bit_fld->first_bit -       */
/*                   bit_fld->last_bit]                           */
/*                                                                */
/*                Note that this latter expression can be fully   */
/*                resolved by the compiler if the bit_fld is      */
/*                declared as a constant as it should be.         */
/*                                                                */
/*                The resulting value is returned to the calling  */
/*                routine.                                        */
/*                                                                */
/******************************************************************/

canuint8_t  Read_Byte_Bit_Fld(const Byte_Bit_Fld_T *bit_fld)
{
   /* used to prevent compiler from using
    * hardware register as temporary storage
    */
   volatile canuint8_t temp; 

   temp = ((*bit_fld->addr >> (bit_fld->last_bit))
             & (last_bit_mask_8[bit_fld->first_bit-bit_fld->last_bit]));

   return temp;
}

/**********************************************************************/
/* FUNCTION NAME: Read_Unsigned_Word_Bit_Fld                          */
/* Inputs       : *bit_fld16 structure with the following parameters: */
/*                bit_fld_addr                                        */
/*                first_bit                                           */
/*                last_bit                                            */
/* Outputs      : bit field value read                                */
/*                                                                    */
/* Description  : This function accepts as input the parameters       */
/*                which define a bit field within a 16 bit            */
/*                variable.  The function uses these parameters       */
/*                to read the variable and isolate the value          */
/*                of the specified bit field. This value is           */
/*                returned by the function                            */
/*                                                                    */
/*                This routine right aligns the requested bit         */
/*                field with the following expression:                */
/*                                                                    */
/*                   (*bit_fld->addr >> (bit_fld->last_bit))          */
/*                                                                    */
/*                It then sets the high order bits to zero with       */
/*                the following expression:                           */
/*                                                                    */
/*                   & last_bit_mask_16[bit_fld->first_bit -          */
/*                   bit_fld->last_bit + 1]                           */
/*                                                                    */
/*                Note that this latter expression can be fully       */
/*                resolved by the compiler if the bit_fld is          */
/*                declared as a constant as it should be.             */
/*                                                                    */
/*                The resulting value is returned to the calling      */
/*                routine.                                            */
/**********************************************************************/
canuint16_t  Read_Unsigned_Word_Bit_Fld(const Word_Bit_Fld_T *bit_fld)
{
   /* used to prevent compiler from using
    * hardware register as temporary storage
    */
   volatile canuint16_t temp; 
   
   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp = *bit_fld->addr;//No Shift
     #else
     temp = ((*bit_fld->addr & 0x00ff) << 8) | ((*bit_fld->addr >> 8) & 0x00ff);//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((*bit_fld->addr & 0x00ff) << 8) | ((*bit_fld->addr >> 8) & 0x00ff);//Shift
     #else
     temp = *bit_fld->addr;//No Shift
     #endif
   #endif

   temp = ((temp >> (bit_fld->last_bit))
             & (last_bit_mask_16[bit_fld->first_bit-bit_fld->last_bit]));

   return temp;
}

// The above function will fail if word access is requirred from odd memory address
canuint16_t  Read_Unsigned_Word_From_Odd_Add_Bit_Fld(const Word_Bit_Fld_T *bit_fld)
{
   /* used to prevent compiler from using
    * hardware register as temporary storage
    */
   volatile canuint16_t temp;
   canuint8_t* ptr;

   ptr = (canuint8_t*) bit_fld->addr;


   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp = (canuint16_t)(*ptr) | (((canuint16_t) (*(ptr+1)))<< 8);      //No Shift
     #else
     temp = (((canuint16_t)(*ptr)) << 8) | ((canuint16_t) (*(ptr+1)));   //Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = (canuint16_t)(*ptr) | (((canuint16_t) (*(ptr+1)))<< 8);     //No Shift
     #else
     temp = (((canuint16_t)(*ptr)) << 8) | ((canuint16_t) (*(ptr+1)));  //Shift
     #endif
   #endif

   temp = ((temp >> (bit_fld->last_bit))
             & (last_bit_mask_16[bit_fld->first_bit-bit_fld->last_bit]));

   return temp;
}

/*  */
/**********************************************************************/
/* FUNCTION NAME: Read_Signed_Word_Bit_Fld                            */
/* Inputs       : *bit_fld16 structure with the following parameters: */
/*                bit_fld_addr                                        */
/*                first_bit                                           */
/*                last_bit                                            */
/* Outputs      : bit field value read                                */
/*                                                                    */
/* Description  : This function accepts as input the parameters       */
/*                which define a bit field within a 16 bit            */
/*                variable.  The function uses these parameters       */
/*                to read the variable and isolate the value          */
/*                of the specified bit field. This value is           */
/*                returned by the function                            */
/*                                                                    */
/*                                                                    */
/*                If the sign bit is set, this function right         */
/*                aligns the bit field with the following             */
/*                expression:                                         */
/*                                                                    */
/*                   (*bit_fld->addr >> (bit_fld->first_bit))         */
/*                                                                    */
/*                It then extends the sign bit left with the          */
/*                following expression:                               */
/*                                                                    */
/*                   | last_bit_mask_16[bit_fld->first_bit -          */
/*                   bit_fld->last_bit + 1]                           */
/*                                                                    */
/*                Note that the value to be or'ed can be fully        */
/*                resolved by the compiler if the bit field has       */
/*                been declared as a constant as it should be.        */
/*                                                                    */
/*                If the sign bit is not set, this function           */
/*                behaves the same as an unsigned read.  See          */
/*                documentation for unsigned read.                    */
/*                                                                    */
/*                                                                    */
/*                The resulting value is returned to the calling      */
/*                routine.                                            */
/**********************************************************************/


cansint16_t  Read_Signed_Word_Bit_Fld(const Word_Bit_Fld_T *bit_fld)
{
   /* used to prevent compiler from using
    * hardware register as temporary storage
    */
   canuint8_t* ptr;
   volatile cansint16_t temp;

   ptr = (canuint8_t*) bit_fld->addr;

   temp = ((cansint16_t)(*ptr) << 8) | (*(ptr+1));
   /*temp = ((*ptr & 0x00ff) << 8) | ((*(ptr+1) >> 8) & 0x00ff);*/

   temp<<= (15-bit_fld->first_bit);

   temp>>= (15-bit_fld->first_bit + bit_fld->last_bit);


//   temp = ((*bit_fld->addr & 0x00ff) << 8) | ((*bit_fld->addr >> 8) & 0x00ff);

//   temp = ((temp >> (bit_fld->last_bit))
//             | (last_bit_mask_16[bit_fld->first_bit-bit_fld->last_bit]));

   return temp;
}



/**********************************************************************/
/* FUNCTION NAME: Read_Unsigned_Long_Word_Bit_Fld                     */
/* Inputs       : *bit_fld32 structure with the following parameters: */
/*                bit_fld_addr                                        */
/*                first_bit                                           */
/*                last_bit                                            */
/* Outputs      : bit field value read                                */
/*                                                                    */
/* Description  : This function accepts as input the parameters       */
/*                which define a bit field within a 32 bit            */
/*                variable.  The function uses these parameters       */
/*                to read the variable and isolate the value          */
/*                of the specified bit field. This value is           */
/*                returned by the function                            */
/*                                                                    */
/*                This routine right aligns the requested bit         */
/*                field with the following expression:                */
/*                                                                    */
/*                   (*bit_fld->addr >> (bit_fld->last_bit))          */
/*                                                                    */
/*                It then sets the high order bits to zero with       */
/*                the following expression:                           */
/*                                                                    */
/*                   & last_bit_mask_32[bit_fld->first_bit -          */
/*                   bit_fld->last_bit + 1]                           */
/*                                                                    */
/*                Note that this latter expression can be fully       */
/*                resolved by the compiler if the bit_fld is          */
/*                declared as a constant as it should be.             */
/*                                                                    */
/*                The resulting value is returned to the calling      */
/*                routine.                                            */
/**********************************************************************/

canuint32_t  Read_Unsigned_Long_Word_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld)
{
   /* used to prevent compiler from using
    * hardware register as temporary storage
    */
   volatile canuint32_t temp;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp= *bit_fld->addr;//No Shift
     #else
     temp = ((*bit_fld->addr & 0x000000ff) << 24) | ((*bit_fld ->addr & 0x0000ff00) << 8) | 
              ((*bit_fld ->addr & 0x00ff0000) >> 8) | (*bit_fld ->addr >> 24);//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((*bit_fld->addr & 0x000000ff) << 24) | ((*bit_fld ->addr & 0x0000ff00) << 8) | 
              ((*bit_fld ->addr & 0x00ff0000) >> 8) | (*bit_fld ->addr >> 24);//Shift
     #else
     temp= *bit_fld->addr;//No Shift
     #endif
   #endif

   temp = ((temp >> (bit_fld->last_bit))
             & (last_bit_mask_32[bit_fld->first_bit-bit_fld->last_bit]));

   return temp;
}

canuint32_t  Read_Unsigned_Long_Word_From_Odd_Add_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld)
{
   /* used to prevent compiler from using
    * hardware register as temporary storage
    */
   volatile canuint32_t temp;
   canuint8_t *ptr;

   ptr = (canuint8_t*) bit_fld->addr;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp = ((canuint32_t)(*ptr)) | (((canuint32_t) (*(ptr+1))) << 8) | 
             (((canuint32_t) (*(ptr+2))) << 16 ) | (((canuint32_t) (*(ptr+3))) << 24 ); //No Shift
     #else
     temp = (((canuint32_t)(*ptr)) << 24 ) | (((canuint32_t) (*(ptr+1))) << 16 ) | 
             (((canuint32_t) (*(ptr+2))) << 8 ) | ((canuint32_t) (*(ptr+3)));           //Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((canuint32_t)(*ptr)) | (((canuint32_t) (*(ptr+1))) << 8) | 
             (((canuint32_t) (*(ptr+2))) << 16 ) | (((canuint32_t) (*(ptr+3))) << 24 ); //No Shift
     #else
     temp = (((canuint32_t)(*ptr)) << 24 ) | (((canuint32_t) (*(ptr+1))) << 16 ) | 
             (((canuint32_t) (*(ptr+2))) << 8 ) | ((canuint32_t) (*(ptr+3)));           //Shift
     #endif
   #endif

   temp = ((temp >> (bit_fld->last_bit))
             & (last_bit_mask_32[bit_fld->first_bit-bit_fld->last_bit]));

   return temp;
}


/**********************************************************************/
/* FUNCTION NAME: Read_Signed_Long_Word_Bit_Fld                       */
/* Inputs       : *bit_fld32 structure with the following parameters: */
/*                bit_fld_addr                                        */
/*                first_bit                                           */
/*                last_bit                                            */
/* Outputs      : bit fld value read                                  */
/*                                                                    */
/* Description  : This function accepts as input the parameters       */
/*                which define a bit field within a 32 bit            */
/*                variable.  The function uses these parameters       */
/*                to read the variable and isolate the value          */
/*                of the specified bit field. This value is           */
/*                returned by the function                            */
/*                                                                    */
/*                                                                    */
/*                If the sign bit is set, this function right         */
/*                aligns the bit field with the following             */
/*                expression:                                         */
/*                                                                    */
/*                   (*bit_fld->addr >> (bit_fld->first_bit))         */
/*                                                                    */
/*                It then extends the sign bit left with the          */
/*                following expression:                               */
/*                                                                    */
/*                   | last_bit_mask_32[bit_fld->first_bit -          */
/*                   bit_fld->last_bit + 1]                           */
/*                                                                    */
/*                Note that the value to be or'ed can be fully        */
/*                resolved by the compiler if the bit field has       */
/*                been declared as a constant as it should be.        */
/*                                                                    */
/*                If the sign bit is not set, this function           */
/*                behaves the same as an unsigned read.  See          */
/*                documentation for unsigned read.                    */
/*                                                                    */
/*                                                                    */
/*                The resulting value is returned to the calling      */
/*                routine.                                            */
/**********************************************************************/



/**********************************************************************/
/* FUNCTION NAME: Read_Unsigned_Long_Long_Word_Bit_Fld                */
/* Inputs       : *bit_fld64 structure with the following parameters: */
/*                bit_fld_addr                                        */
/*                first_bit                                           */
/*                last_bit                                            */
/* Outputs      : bit field value read                                */
/*                                                                    */
/* Description  : This function accepts as input the parameters       */
/*                which define a bit field within a 64 bit            */
/*                variable.  The function uses these parameters       */
/*                to read the variable and isolate the value          */
/*                of the specified bit field. This value is           */
/*                returned by the function                            */
/*                                                                    */
/*                This routine right aligns the requested bit         */
/*                field with the following expression:                */
/*                                                                    */
/*                   (*bit_fld->addr >> (bit_fld->last_bit))          */
/*                                                                    */
/*                It then sets the high order bits to zero with       */
/*                the following expression:                           */
/*                                                                    */
/*                   & last_bit_mask_32[bit_fld->first_bit -          */
/*                   bit_fld->last_bit + 1]                           */
/*                                                                    */
/*                Note that this latter expression can be fully       */
/*                resolved by the compiler if the bit_fld is          */
/*                declared as a constant as it should be.             */
/*                                                                    */
/*                                                                    */
/*                The resulting value is returned to the calling      */
/*                routine.                                            */
/**********************************************************************/



/*  */
/**********************************************************************/
/* FUNCTION NAME: Read_Signed_Long_Long_Word_Bit_Fld                  */
/* Inputs       : *bit_fld64 structure with the following parameters: */
/*                bit_fld_addr                                        */
/*                first_bit                                           */
/*                last_bit                                            */
/* Outputs      : bit fld value read                                  */
/*                                                                    */
/* Description  : This function accepts as input the parameters       */
/*                which define a bit field within a 64 bit            */
/*                variable.  The function uses these parameters       */
/*                to read the variable and isolate the value          */
/*                of the specified bit field. This value is           */
/*                returned by the function                            */
/*                                                                    */
/*                                                                    */
/*                If the sign bit is set, this function right         */
/*                aligns the bit field with the following             */
/*                expression:                                         */
/*                                                                    */
/*                   (*bit_fld->addr >> (bit_fld->first_bit))         */
/*                                                                    */
/*                It then extends the sign bit left with the          */
/*                following expression:                               */
/*                                                                    */
/*                   | last_bit_mask_64[bit_fld->first_bit -          */
/*                   bit_fld->last_bit + 1]                           */
/*                                                                    */
/*                Note that the value to be or'ed can be fully        */
/*                resolved by the compiler if the bit field has       */
/*                been declared as a constant as it should be.        */
/*                                                                    */
/*                If the sign bit is not set, this function           */
/*                behaves the same as an unsigned read.  See          */
/*                documentation for unsigned read.                    */
/*                                                                    */
/*                                                                    */
/*                The resulting value is returned to the calling      */
/*                routine.                                            */
/**********************************************************************/

/*  */
/*******************************************************************/
/* FUNCTION NAME: Write_Byte_Bit_Fld                               */
/* Inputs       : *bit_fld8 structure with the following paramters:*/
/*                bit_fld_addr                                     */
/*                first_bit                                        */
/*                last_bit                                         */
/*                new value (separate input, not part of structure)*/
/* Outputs      : none                                             */
/*                                                                 */
/* Description  : This function accepts as input the parameters    */
/*                which define a bit field within an 8 bit         */
/*                variable.  The function uses these parameters    */
/*                to write to the variable just the specified      */
/*                bits, leaving the other bits unchanged.          */
/*                                                                 */
/*                This function builds a mask with all bits to     */
/*                the right and left of the bit field set to 1,    */
/*                while the mask for the bits of the bit field     */
/*                itself are set to zero. This mask is then ANDed  */
/*                with the contents of the variable, yielding the  */
/*                original value of the variable in all non bit    */
/*                field positions.  Bit field positions are turned */
/*                to zero by the AND. Next, the new value to be    */
/*                stored in the bit field is lined up on the bit   */
/*                field boundaries, and then ORed with the result  */
/*                of the previous AND operation.  The result is    */
/*                the variable updated with the new value for the  */
/*                bit field.                                       */
/*******************************************************************/



void  Write_Byte_Bit_Fld(const Byte_Bit_Fld_T *bit_fld, 
                         canuint8_t new_value)
{

      canuint8_t mask;

      /* used to prevent compiler from using
       * hardware register as temporary storage
       */
      volatile canuint8_t temp; 

      if( bit_fld->last_bit > 0)
      {

         mask = first_bit_mask_8[bit_fld->first_bit] |
                    last_bit_mask_8[bit_fld->last_bit - 1];
      }
      else
      {
          mask = first_bit_mask_8[bit_fld->first_bit]; 
      }

     /* keep compiler from storing intermediate
      * values in hardware variable
      */

/*      temp =  (*bit_fld->addr & mask)|
              (new_value << bit_fld->last_bit); 
*/
      temp = (*bit_fld->addr & mask)|
             ((new_value & (last_bit_mask_8[bit_fld->first_bit-bit_fld->last_bit]))<< bit_fld->last_bit);


      *bit_fld->addr  = temp;

}

/*  */
/*******************************************************************/
/* FUNCTION NAME: Write_Word_Bit_Fld                               */
/* Inputs       : *bit_fld16 structure with the following paramters:*/
/*                bit_fld_addr                                     */
/*                first_bit                                        */
/*                last_bit                                         */
/*                new value (separate input, not part of structure)*/
/* Outputs      : none                                             */
/*                                                                 */
/* Description  : This function accepts as input the parameters    */
/*                which define a bit field within a 16 bit         */
/*                variable.  The function uses these parameters    */
/*                to write to the variable just the specified      */
/*                bits, leaving the other bits unchanged.          */
/*                                                                 */
/*                This function builds a mask with all bits to     */
/*                the right and left of the bit field set to 1,    */
/*                while the mask for the bits of the bit field     */
/*                itself are set to zero. This mask is then ANDed  */
/*                with the contents of the variable, yielding the  */
/*                original value of the variable in all non bit    */
/*                field positions.  Bit field positions are turned */
/*                to zero by the AND. Next, the new value to be    */
/*                stored in the bit field is lined up on the bit   */
/*                field boundaries, and then ORed with the result  */
/*                of the previous AND operation.  The result is    */
/*                the variable updated with the new value for the  */
/*                bit field.                                       */
/*                                                                 */
/*******************************************************************/

void  Write_Word_Bit_Fld(const Word_Bit_Fld_T *bit_fld, 
                         canuint16_t new_value)
{

   canuint16_t mask;

   /* used to prevent compiler from using hardware
    * variable for temporary storage
    */

   volatile canuint16_t temp;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp = *bit_fld->addr;//No Shift
     #else
     temp = ((*bit_fld->addr & 0x00ff) << 8) | ((*bit_fld->addr >> 8) & 0x00ff);//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((*bit_fld->addr & 0x00ff) << 8) | ((*bit_fld->addr >> 8) & 0x00ff);//Shift
     #else
     temp = *bit_fld->addr;//No Shift
     #endif
   #endif

   if( bit_fld->last_bit > 0 )
   {

      mask = first_bit_mask_16[bit_fld->first_bit] |
                last_bit_mask_16[bit_fld->last_bit - 1];
   }
   else
   {
       mask = first_bit_mask_16[bit_fld->first_bit]; 
   }

   /* don't let compiler store intermediate 
    * results in hardware variable
    */

   /* temp = ((canuint16_t)(*bit_fld->addr) & (canuint16_t) mask) |
             (new_value << bit_fld->last_bit);
*/
   temp = (temp & mask)|
          ((new_value & (last_bit_mask_16[bit_fld->first_bit-bit_fld->last_bit])) 
          << bit_fld->last_bit);

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     *bit_fld->addr = temp;//No Shift
     #else
     *bit_fld->addr = ((temp & 0x00ff) << 8);
     *bit_fld->addr |= ((temp >> 8) & 0x00ff);//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((temp & 0x00ff) << 8) | ((temp >> 8) & 0x00ff);//Shift
     #else
     *bit_fld->addr = temp;//No Shift
     #endif
   #endif

}


void Write_Word_Into_Odd_Add_Bit_Fld(const Word_Bit_Fld_T *bit_fld, 
                          canuint16_t new_value)
{

   canuint16_t mask;
   volatile canuint16_t temp;
   canuint8_t* ptr;

   ptr = (canuint8_t*) bit_fld->addr;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp = (canuint16_t)(*ptr) | (((canuint16_t) (*(ptr+1)))<< 8);//No Shift
     #else
     temp = (((canuint16_t)(*ptr)) << 8) | ((canuint16_t) (*(ptr+1)));//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = (canuint16_t)(*ptr) | (((canuint16_t) (*(ptr+1)))<< 8);//No Shift
     #else
     temp = (((canuint16_t)(*ptr)) << 8) | ((canuint16_t) (*(ptr+1)));//Shift
     #endif
   #endif

   if( bit_fld->last_bit > 0 )
   {

      mask = first_bit_mask_16[bit_fld->first_bit] |
                last_bit_mask_16[bit_fld->last_bit - 1];
   }
   else
   {
       mask = first_bit_mask_16[bit_fld->first_bit]; 
   }

   temp = (temp & mask)|
             ((new_value & (last_bit_mask_16[bit_fld->first_bit-bit_fld->last_bit]))<< bit_fld->last_bit);

   ptr = (canuint8_t*) bit_fld->addr;


   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     *ptr     = (canuint8_t) (temp & 0x00ff);
     *(ptr+1) = (canuint8_t) ((temp & 0xff00) >> 8);//No Shift
     #else
     *ptr     = (canuint8_t) ((temp & 0xff00) >> 8);
     *(ptr+1) = (canuint8_t) (temp & 0x00ff);       //Shift
     #endif
   #else
     #ifdef INTEL_DBC
     *ptr     = (canuint8_t) (temp & 0x00ff);
     *(ptr+1) = (canuint8_t) ((temp & 0xff00) >> 8);//No Shift
     #else
     *ptr     = (canuint8_t) ((temp & 0xff00) >> 8);
     *(ptr+1) = (canuint8_t) (temp & 0x00ff);       //Shift
     #endif
   #endif

}

/*  */


/*******************************************************************/
/* FUNCTION NAME: Write_Long_Word_Bit_Fld                          */
/* Inputs       : *bit_fld32 structure with the following paramters:*/
/*                bit_fld_addr                                     */
/*                first_bit                                        */
/*                last_bit                                         */
/*                new value (separate input, not part of structure)*/
/* Outputs      : none                                             */
/*                                                                 */
/* Description  : This function accepts as input the parameters    */
/*                which define a bit field within a 32 bit         */
/*                variable.  The function uses these parameters    */
/*                to write to the variable just the specified      */
/*                bits, leaving the other bits unchanged.          */
/*                                                                 */
/*                This function builds a mask with all bits to     */
/*                the right and left of the bit field set to 1,    */
/*                while the mask for the bits of the bit field     */
/*                itself are set to zero. This mask is then ANDed  */
/*                with the contents of the variable, yielding the  */
/*                original value of the variable in all non bit    */
/*                field positions.  Bit field positions are turned */
/*                to zero by the AND. Next, the new value to be    */
/*                stored in the bit field is lined up on the bit   */
/*                field boundaries, and then ORed with the result  */
/*                of the previous AND operation.  The result is    */
/*                the variable updated with the new value for the  */
/*                bit field.                                       */
/*                                                                 */
/*******************************************************************/

void Write_Long_Word_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld, 
                              canuint32_t new_value)
{
   canuint32_t mask;
   /* used to prevent compiler from using 
    * hardware variable for temporary storage
    */

   volatile canuint32_t temp;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp= *bit_fld->addr;//No Shift

     #else
     temp = ((*bit_fld->addr & 0x000000ff) << 24) | ((*bit_fld ->addr & 0x0000ff00) << 8) | 
              ((*bit_fld ->addr & 0x00ff0000) >> 8) | (*bit_fld ->addr >> 24);//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((*bit_fld->addr & 0x000000ff) << 24) | ((*bit_fld ->addr & 0x0000ff00) << 8) | 
              ((*bit_fld ->addr & 0x00ff0000) >> 8) | (*bit_fld ->addr >> 24);//Shift
     #else
     temp= *bit_fld->addr;//No Shift
     #endif
   #endif

  if( bit_fld->last_bit > 0 )
   {

      mask = first_bit_mask_32[bit_fld->first_bit] |
                last_bit_mask_32[bit_fld->last_bit - 1];
   }
   else
   {
       mask = first_bit_mask_32[bit_fld->first_bit]; 
   }

   /* don't let compiler store intermediate 
    * results in hardware variable
    */

   temp = (temp & mask)|
          ((new_value & (last_bit_mask_32[bit_fld->first_bit-bit_fld->last_bit])) 
          << bit_fld->last_bit);

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     *bit_fld->addr = temp;//No Shift
     #else
     *bit_fld->addr = ((temp & 0x000000ff) << 24);
     *bit_fld->addr |= ((temp & 0x0000ff00) << 8);
     *bit_fld->addr |= ((temp & 0x00ff0000) >> 8);
     *bit_fld->addr |= (temp >> 24);//Shift
     #endif
   #else
     #ifdef INTEL_DBC
     *bit_fld->addr = ((temp & 0x000000ff) << 24) | ((temp & 0x0000ff00) << 8) | 
                      ((temp & 0x00ff0000) >> 8) | (temp >> 24);//Shift
     #else
     *bit_fld->addr = temp;//No Shift
   #endif
   #endif
}


void Write_Long_Word_Into_Odd_Add_Bit_Fld(const Long_Word_Bit_Fld_T *bit_fld, 
                                            canuint32_t new_value)
{
   canuint32_t mask;
   volatile canuint32_t temp;
   canuint8_t *ptr;

   ptr = (canuint8_t*) bit_fld->addr;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     temp = ((canuint32_t)(*ptr)) | (((canuint32_t) (*(ptr+1))) << 8) | 
             (((canuint32_t) (*(ptr+2))) << 16 ) | (((canuint32_t) (*(ptr+3))) << 24 );//No Shift
     #else
     temp = (((canuint32_t)(*ptr)) << 24 ) | (((canuint32_t) (*(ptr+1))) << 16 ) | 
             (((canuint32_t) (*(ptr+2))) << 8 ) | ((canuint32_t) (*(ptr+3)));          //Shift
     #endif
   #else
     #ifdef INTEL_DBC
     temp = ((canuint32_t)(*ptr)) | (((canuint32_t) (*(ptr+1))) << 8) | 
             (((canuint32_t) (*(ptr+2))) << 16 ) | (((canuint32_t) (*(ptr+3))) << 24 );//No Shift
     #else
     temp = (((canuint32_t)(*ptr)) << 24 ) | (((canuint32_t) (*(ptr+1))) << 16 ) | 
             (((canuint32_t) (*(ptr+2))) << 8 ) | ((canuint32_t) (*(ptr+3)));          //Shift
     #endif
   #endif

   if( bit_fld->last_bit > 0 )
   {

      mask = first_bit_mask_32[bit_fld->first_bit] |
                last_bit_mask_32[bit_fld->last_bit - 1];
   }
   else
   {
       mask = first_bit_mask_32[bit_fld->first_bit]; 
   }

   temp = (temp & mask)|
          ((new_value & (last_bit_mask_32[bit_fld->first_bit-bit_fld->last_bit])) 
          << bit_fld->last_bit);

   ptr = (canuint8_t*) bit_fld->addr;

   #ifdef LITTLE_ENDIAN_MICRO
     #ifdef INTEL_DBC
     *ptr     = (canuint8_t) (temp & 0x000000ff);
     *(ptr+1) = (canuint8_t) ((temp & 0x0000ff00) >> 8);
     *(ptr+2) = (canuint8_t) ((temp & 0x00ff0000) >> 16);
     *(ptr+3) = (canuint8_t) ((temp & 0xff000000) >> 24); //No Shift
     #else
     *ptr     = (canuint8_t) ((temp & 0xff000000) >> 24);
     *(ptr+1) = (canuint8_t) ((temp & 0x00ff0000) >> 16);
     *(ptr+2) = (canuint8_t) ((temp & 0x0000ff00) >> 8);
     *(ptr+3) = (canuint8_t) (temp & 0x000000ff);         //Shift
     #endif                                               
   #else
     #ifdef INTEL_DBC
     *ptr     = (canuint8_t) (temp & 0x000000ff);
     *(ptr+1) = (canuint8_t) ((temp & 0x0000ff00) >> 8);
     *(ptr+2) = (canuint8_t) ((temp & 0x00ff0000) >> 16);
     *(ptr+3) = (canuint8_t) ((temp & 0xff000000) >> 24); //No Shift
     #else
     *ptr     = (canuint8_t) ((temp & 0xff000000) >> 24);
     *(ptr+1) = (canuint8_t) ((temp & 0x00ff0000) >> 16);
     *(ptr+2) = (canuint8_t) ((temp & 0x0000ff00) >> 8);
     *(ptr+3) = (canuint8_t) (temp & 0x000000ff);         //Shift
     #endif
   #endif

}

/*******************************************************************/
/* FUNCTION NAME: Write_Long_Long_Word_Bit_Fld                     */
/* Inputs       : *bit_fld64 structure with the following paramters:*/
/*                bit_fld_addr                                     */
/*                first_bit                                        */
/*                last_bit                                         */
/*                new value (separate input, not part of structure)*/
/* Outputs      : none                                             */
/*                                                                 */
/* Description  : This function accepts as input the parameters    */
/*                which define a bit field within a 64 bit         */
/*                variable.  The function uses these parameters    */
/*                to write to the variable just the specified      */
/*                bits, leaving the other bits unchanged.          */
/*                                                                 */
/*                This function builds a mask with all bits to     */
/*                the right and left of the bit field set to 1,    */
/*                while the mask for the bits of the bit field     */
/*                itself are set to zero. This mask is then ANDed  */
/*                with the contents of the variable, yielding the  */
/*                original value of the variable in all non bit    */
/*                field positions.  Bit field positions are turned */
/*                to zero by the AND. Next, the new value to be    */
/*                stored in the bit field is lined up on the bit   */
/*                field boundaries, and then ORed with the result  */
/*                of the previous AND operation.  The result is    */
/*                the variable updated with the new value for the  */
/*                bit field.                                       */
/*                                                                 */
/*******************************************************************/





/*  */
/*******************************************************************/
/* FUNCTION NAME: Reverse_Buf_Endianess                            */
/* Inputs       : *Buf_Addr                                        */
/*                len_in_bytes                                     */
/*                word_size                                        */
/* Outputs      : changes order of bytes in buffer                 */
/*                                                                 */
/* Description  : This function reorders the bytes in the buffer   */
/*                as follows for a 16 bit micro-controller:        */
/*                byte 0 & 1 of each word is reversed              */
/*                                                                 */
/*                For a 32 bit micro-controller the byte orders    */
/*                are reversed as follows:                         */
/*                0,1,2,3 goes to 3,2,1,0                          */
/*                                                                 */
/*******************************************************************/




/*  */
/*******************************************************************/
/* FUNCTION NAME: Exchange_Bytes_In_Words                          */
/* Inputs       : *Buf_Addr                                        */
/*                length_in_bytes                                  */
/* Outputs      : changes order of bytes in words                  */
/*                                                                 */
/* Description  : This function exchanges bytes in words           */
/*                                                                 */
/*******************************************************************/



/*******************************************************************/
/* FUNCTION NAME: Exchange_Words_In_Long_Words                     */
/* Inputs       : *Buf_Addr                                        */
/*                length_in_bytes                                  */
/* Outputs      : changes order of bytes in words                  */
/*                                                                 */
/* Description  : This function exchanges  words in long words     */
/*                                                                 */
/*******************************************************************/

/*******************************************************************/
/* FUNCTION NAME: Exchange_Long_Words_In_Long_Long_Words           */
/* Inputs       : *Buf_Addr                                        */
/*                length_in_bytes                                  */
/* Outputs      : changes order of long words in long long words   */
/*                                                                 */
/* Description  : This function exchanges  long words in long long */
/*                words                                            */
/*                                                                 */
/*******************************************************************/




/*  */
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Nov-08    Mahipal         Created initial version of this file       *
 ******************************************************************************/

/*
* $SOURCE: misc_project@kokomo.1422:acc2_jaguar:bit_flds.c $
* $REVISION: 1.2 $
* $AUTHOR: kokomo.1422:/users/tcompton/dsds/pcs:tcompton $
*/

