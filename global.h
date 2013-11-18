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

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define MAPSIZE 21

#define ENEMYCNT 10

#define TYPE_ENEMY 1
#define TYPE_PACK 2

#define UNSOLID 0
#define SOLID 1
#define SPRITE 2

#define SPACE 0
#define WALL 1
#define DOOR 2

#define CHECKED 5

#define GUN 1
#define KNIFE 2

#define WEAPON_OVERFLOW 3

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define TRUE 0xFF
#define FALSE 0

#define NULL (void *) 0

typedef unsigned short int usint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef short int sint;
typedef unsigned char bool;

extern uint map[MAPSIZE][MAPSIZE];
extern int heights[MAPSIZE][MAPSIZE];
extern uint solids[MAPSIZE][MAPSIZE];

extern int output;
extern int exit;
extern int demo;

extern int contrast;
extern int contradd;

extern int gundir;

extern const uint sizex, sizey;

extern struct st_player{float dirX, dirY, planeX, planeY, x, y; int weapon, gunpos, health;} player;
extern struct st_sprite{float x, y; int type, effect; struct{int *ptr; uint width, height;} texture;} *sprites;

extern uint spritecnt;

void error(char *);

extern const char *status;
extern unsigned int statustimer;

#endif
