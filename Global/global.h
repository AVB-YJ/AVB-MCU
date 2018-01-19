#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "define.h"

//Global

//delay 1ms
#if 0
#define		Delay_ms(msCount)	for(uint8_t i=0;i<(msCount);i++)	\
								{                   				\
									OS_Wait(250);   				\
									OS_Wait(250);   				\
									OS_Wait(250);   				\
									OS_Wait(250);   				\
								}
#else
#endif
	void Delay_ms(uint8_t msCount);
#endif