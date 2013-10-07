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

void error(void);

extern const char *status;
extern unsigned int statustimer;

#endif