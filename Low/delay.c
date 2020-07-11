#include "main.h"

extern void US_Delay(uint32_t load_value)
{
	uint32_t temp;
	SysTick -> LOAD = 9*load_value;
	SysTick -> CTRL = 0x01;
	SysTick -> VAL = 0;
	
	do
	{
		temp = SysTick -> CTRL;
	}
	while((temp & 0x01) && (!(temp & (1 << 16))));
	
	SysTick -> CTRL = 0;
	SysTick -> VAL = 0;
}

extern void MS_Delay(uint32_t load_value)
{
	uint32_t temp;
	SysTick -> LOAD = 9000*load_value;
	SysTick -> CTRL = 0x01;
	SysTick -> VAL = 0;
	
	do
	{
		temp = SysTick -> CTRL;
	}
	while((temp & 0x01) && (!(temp & (1 << 16))));
	
	SysTick -> CTRL = 0;
	SysTick -> VAL = 0;
}

