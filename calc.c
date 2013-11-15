#include "global.h"
#include "calc.h"
#include "syscalls.h"

// table that holds precalculated values for the floor and ceiling
int TDist[64];

// random number generator; could be improved
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

// inits constants for floor etc
void table()
{
	int x;
	for(x = 0; x < 64; x++)
	{
		TDist[x] = (64 << 8) / (2.0 * x - 64);
	}
}

// fills an array
void fill(uint *ptr, uint element, uint arraysize)
{
	for(;arraysize > 0; arraysize--, ptr++)
		*ptr = element;
}
