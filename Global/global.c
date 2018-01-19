#include "global.h"

void Delay_ms(uint8_t msCount)
{
	uint8_t i = 0;
	for(i=0;i<msCount;i++)	
	{                   				
		OS_Wait(250);   				
		OS_Wait(250);   				
		OS_Wait(250);   				
		OS_Wait(250);   				
	}
}
