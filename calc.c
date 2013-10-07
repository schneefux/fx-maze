#include "global.h"
#include "calc.h"
#include "syscalls.h"

int TDist[64];

static uint lastrandom = 0x123456;

void seedrandom(void)
{
	lastrandom = RTC_GetTicks();
}

unsigned int random()
{
	lastrandom = (0x41C64E6D*lastrandom) + 0x3039;
	return (lastrandom >> 16);
}

void table()
{
	int x;
	for(x = 0; x < 64; x++)
	{
		TDist[x] = (64 << 8) / (2.0 * x - 64);
	}
}

void fill(uint *ptr, uint element, uint arraysize)
{
	for(;arraysize > 0; arraysize--, ptr++)
		*ptr = element;
}
