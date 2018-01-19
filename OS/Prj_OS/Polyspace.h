#ifndef _POLYSPACE_H
#define _POLYSPACE_H

#if defined QAC || defined POLYSPACE

//#define __far
//#define near
//#define __near
//#define far
//#define __interrupt
//#define __intrinsic
//#define __root 
//#define __saddr 
//#define __no_init
//#define __no_bit_access
//#define __far_func


void OS_boEnableAllInterrupts(void);
void OS_boDisableAllInterrupts(void);

#endif

#endif
