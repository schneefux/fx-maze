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

#ifndef _DRAW_H_
#define _DRAW_H_

void locatePrintMini(int, int, const unsigned char *);

#define pixel(x,y) (*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7))
#define clrpixel(x,y) (*(vram +  (y << 4) + (x >> 3))) &= ~(128>>(x & 7))

void vertical(int, int, int, int, int, int, float);

void drawgun(void);
void showmap(void);
void drawgenmap(void);

void horizontal(int, int, int);
void fillbox(int, int, int, int);

extern int drawtex, drawfloor, drawheight;

#endif