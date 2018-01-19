/*-------------------------------------------------------------------------
 *      Declarations of intrinsic functions.
 *
 *      This header file can be used with the
 *      IAR 78K C/C++ compilers, ICC78K and ICC78K0R.
 *
 *      Copyright (c) 2004-2008 IAR Systems AB.
 *
 *      $Revision: 3531 $
 *
 *-----------------------------------------------------------------------*/

#ifndef __INTRINSICS_INCLUDED
#define __INTRINSICS_INCLUDED

#include "Polyspace.h"

#ifndef __ICC78K__
  #error "INTRINSICS.H file for use with ICC78K/ICC78K0R V4.x only"
#endif

#pragma language=extended
#pragma system_include

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char istate_t;

__intrinsic void __disable_interrupt(void);
__intrinsic void __enable_interrupt(void);
__intrinsic istate_t __get_interrupt_state(void);
__intrinsic void __set_interrupt_state(istate_t);

__intrinsic void __no_operation(void);
__intrinsic void __halt(void);
__intrinsic void __stop(void);

#if !(defined QAC || defined POLYSPACE)
#if __CORE__ != __78K0S__ 
__intrinsic void __break(void);
#endif
#endif
__intrinsic __root int __low_level_init(void);

#pragma language=default

#ifdef __cplusplus
}
#endif

#endif  /* __INTRINSICS_INCLUDED */
