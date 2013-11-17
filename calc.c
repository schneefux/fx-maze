/****************************************************************************\
*    																	*
*    Copyright by Casimo, 2013												*
*    																	*
*    This file is part of fxMaze.												*
*    																	*
*    fxMaze is free software: you can redistribute it and/or modify						*
*    it under the terms of the GNU General Public License as published by					*
*    the Free Software Foundation, either version 3 of the License, or					*
*    (at your option) any later version.											*
*    																	*
*    fxMaze is distributed in the hope that it will be useful,							*
*    but WITHOUT ANY WARRANTY; without even the implied warranty of				*
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				*
*    GNU General Public License for more details.									*
*    																	*
*    You should have received a copy of the GNU General Public License					*
*    along with fxMaze.  If not, see <http://www.gnu.org/licenses/>.					*
*    																	*
\****************************************************************************/

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
