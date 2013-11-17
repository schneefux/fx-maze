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

#ifndef _CALC_H_
#define _CALC_H_

#define Abs(x) ((x < 0)? -x : x)
#define degtorad(x) (x * 0.0174532925)
#define sgn(x) ((int)((x > 0) ? 1 :  (x == 0)?0:-1))

#define GetBit(x, y) (x & (1 << y)) != 0
#define SetBit(x, y) (x |= (1 << y))
#define ClearBit(x, y) (x &= ~(1 << y))

#define crand() random()

void seedrandom(void);
unsigned int random(void);
void table(void);
void fill(unsigned int *, unsigned int, unsigned int);

extern int TDist[64];

#endif
