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

#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

char* Disp_GetVRAMPtr(void);

int GetKey(unsigned int *);
void locate(int, int);
void Print(const unsigned char *);
int Timer_Install(int, void (*)(void), int);
int Timer_Uninstall(int);
int Timer_Start(int);
int itoa( int, unsigned char*, int);
void PrintMini(int, int, const unsigned char *, int);
int RTC_Elapsed_ms(int, int);
void Keyboard_ClrBuffer(void);
int RTC_Elapsed_ms(int, int);
int GlibGetOSVersionInfo(char *, char *, short *, short *);
int Keyboard_PRGM_GetKey(uchar *);

#define MINI_OVER 0
#define MINI_OR 1
#define MINI_REV 2
#define MINI_REVOR 3

#endif