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

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#define IsEmulator !( *(int*)0x80000300)

struct st_port {
             union {
                   unsigned char BYTE;
                   struct{
                          unsigned char B7:1;
                          unsigned char B6:1;
                          unsigned char B5:1;
                          unsigned char B4:1;
                          unsigned char B3:1;
                          unsigned char B2:1;
                          unsigned char B1:1;
                          unsigned char B0:1; 
                          }      BIT;
                   }            DR; 
};

void BacklightOn(void);
void BacklightOff(void);
void BacklightChange(void);
int BacklightIsOn(void);

void set_contrast(int);

void display_vram(void);
void clear_vram(void);

short *APP_EnableRestart(void);

int getCalc(void);
#define UNKNOWN 0
#define fx9860G 1
#define fx9860G_SLIM 2
#define fx9860GII_2 3
#define fx9860GII 4

extern char *vram;

#endif