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
#include "mapgen.h"
#include "draw.h"
#include "hardware.h"
#include "sprites.h"

// this code is a random map generator based on the kill and hunt algorithm

// this counts unempty neighbours
static int cntunvisit(union st_field cnt)
{
	int c = 0;
	if(cnt.side.west != SPACE)c++;
	if(cnt.side.east != SPACE)c++;
	if(cnt.side.north != SPACE)c++;
	if(cnt.side.south != SPACE)c++;
	
	return (c > 1)?c:0;
}

// count empty ones, including ones that are outside which are counted as wall
static int cntempty(int x, int y)
{
	union st_field c;
	int cnt = 0;
	
	c.byte = 0;
	
	if(x - 1 > 0)c.side.west = map[x - 1][y];else c.side.west = WALL;
	if(x + 1 < MAPSIZE - 1)c.side.east = map[x + 1][y];else c.side.east = WALL;
	if(y - 1 > 0)c.side.north = map[x][y - 1];else c.side.north = WALL;
	if(y + 1 < MAPSIZE - 1)c.side.south = map[x][y + 1];else c.side.south = WALL;
	
	if(c.side.west == SPACE)cnt++;
	if(c.side.east == SPACE)cnt++;
	if(c.side.north == SPACE)cnt++;
	if(c.side.south == SPACE)cnt++;
	
	return cnt;
}

// count walls
static int cntwall(int x, int y)
{
	union st_field c;
	int cnt = 0;
	
	c.byte = 0;
	
	if(x - 1 > 0)c.side.west = map[x - 1][y];else c.side.west = WALL;
	if(x + 1 < MAPSIZE - 1)c.side.east = map[x + 1][y];else c.side.east = WALL;
	if(y - 1 > 0)c.side.north = map[x][y - 1];else c.side.north = WALL;
	if(y + 1 < MAPSIZE - 1)c.side.south = map[x][y + 1];else c.side.south = WALL;
	
	if(c.side.west == WALL)cnt++;
	if(c.side.east == WALL)cnt++;
	if(c.side.north == WALL)cnt++;
	if(c.side.south == WALL)cnt++;
	
	return cnt;
}

// return as st_field from map point
static union st_field get(int x, int y)
{
	union st_field c;
	
	c.byte = 0;
	
	if(x - 1 > 0)c.side.west = map[x - 1][y];
	if(x + 1 < MAPSIZE - 1)c.side.east = map[x + 1][y];
	if(y - 1 > 0)c.side.north = map[x][y - 1];
	if(y + 1 < MAPSIZE - 1)c.side.south = map[x][y + 1];
	
	return c;
}

// try to find a wall with unvisited neighbours
static int hunt(int *x, int *y)
{
	for(*x = 1; *x < MAPSIZE - 1; *x+=2)
	{
		for(*y = 1; *y < MAPSIZE - 1; *y+=2)
		{
			if(map[*x][*y] == WALL)
			{
				if(cntunvisit(get(*x, *y)) > 1)
				{
					return TRUE;
				}
			}
		}
	}
	// if there is none, we can start the main game
	return FALSE;
}

static int kill(int *x, int *y, union st_field this)
{
	int fail1 = FALSE, fail2 = FALSE, fail3 = FALSE, fail4 = FALSE;
	while(!keydown(31))
	{
		if(cntunvisit(this) == 0)fail1 = fail2 = fail3 = fail4 = TRUE;
		
		// try to 'digg' in random directions
		switch(random() % 4)
		{
			case 0:
				if(this.side.west == WALL && fail1 == FALSE)
				{
					if(cntunvisit(get(*x - 2, *y)) > 0)
					{
						map[*x - 1][*y] = SPACE;
						*x -= 2;
						return TRUE;
					}
					else
					{
						fail1 = TRUE;
					}
				}
				else
				{
					fail1 = TRUE;
				}
				break;
				
			case 1:
				if(this.side.east == WALL && fail2 == FALSE)
				{
					if(cntunvisit(get(*x + 2, *y)) > 0)
					{
						map[*x + 1][*y] = SPACE;
						*x += 2;
						return TRUE;
					}
					else
					{
						fail2 = TRUE;
					}
				}
				else
				{
					fail2 = TRUE;
				}
				break;
				
			case 2:
				if(this.side.north == WALL && fail3 == FALSE)
				{
					if(cntunvisit(get(*x, *y - 2)) > 0)
					{
						map[*x][*y - 1] = SPACE;
						*y -= 2;
						return TRUE;
					}
					else
					{
						fail3 = TRUE;
					}
				}
				else
				{
					fail3 = TRUE;
				}
				break;
				
			case 3:
				if(this.side.south == WALL && fail4 == FALSE)
				{
					if(cntunvisit(get(*x, *y + 2)) > 0)
					{
						map[*x][*y + 1] = SPACE;
						*y += 2;
						return TRUE;
					}
					else
					{
						fail4 = TRUE;
					}
				}
				else
				{
					fail4 = TRUE;
				}
				break;
		}
		
		if(fail1 == TRUE && fail2 == TRUE && fail3 == TRUE && fail4 == TRUE)
		{
			// dead end, try to find a new starting point
			return hunt(x, y);
		}
	}
	// no possible move left, let's go and kill some robots
	return FALSE;
}

// see if we can walk through that maze
static int solve()
{
	int priotable[4];
	int curx = 1, cury = 1;
	int prex = 0, prey = -1;
	int deltax = 1, deltay = 0;
	int dir, dirx, diry;
start:
	// that's dirty, I know, but it works
	for(curx = 0; curx < MAPSIZE; curx++)
	{
		for(cury = 0; cury < MAPSIZE; cury++)
		{
			if((curx != 1 && cury != 1) && (curx != MAPSIZE - 2 && cury != MAPSIZE - 2))
			{
				if(map[curx][cury] == SPACE)
				{
					if(cntempty(curx, cury) == 1)
					{
						map[curx][cury] = CHECKED;
						clear_vram();
						drawgenmap();
						display_vram();
						goto start;
					}
				}
			}
		}
	}

	curx = cury = 1;
	
	while(curx != MAPSIZE - 2 || cury != MAPSIZE - 2)
	{
		deltax = curx - prex;
		deltay = cury - prey;
		
		if(deltax == 0)
		{
			if(deltay == 1)
				dir = SOUTH;
			else
				dir = NORTH;
		}
		else
		{
			if(deltax == 1)
				dir = EAST;
			else
				dir = WEST;
		}
		
		// this is called the right-hand method, I think
		switch(dir)
		{
			case NORTH:
				priotable[0] = EAST;
				priotable[1] = NORTH;
				priotable[2] = WEST;
				priotable[3] = SOUTH;
				break;
			case SOUTH:
				priotable[0] = WEST;
				priotable[1] = SOUTH;
				priotable[2] = EAST;
				priotable[3] = NORTH;
				break;
			case EAST:
				priotable[0] = SOUTH;
				priotable[1] = EAST;
				priotable[2] = NORTH;
				priotable[3] = WEST;
				break;
			case WEST:
				priotable[0] = NORTH;
				priotable[1] = WEST;
				priotable[2] = SOUTH;
				priotable[3] = EAST;
		}
		
		// try again with left-hand :D
		for(dir = 0; dir < 4; dir++)
		{
			switch(priotable[dir])
			{
				case NORTH:
					dirx = 0;
					diry = -1;
					break;
				case EAST:
					dirx = 1;
					diry = 0;
					break;
				case SOUTH:
					dirx = 0;
					diry = 1;
					break;
				case WEST:
					dirx = -1;
					diry = 0;
					break;			
			}
			if(curx + dirx < MAPSIZE - 1 && curx + dirx > 0 && cury + diry < MAPSIZE - 1 && cury + diry > 0 && map[curx + dirx][cury + diry] == SPACE)
			{
				prex = curx;
				prey = cury;
				curx += dirx;
				cury += diry;
				break;
			}
		}
		
		// we are at the start again?
		if(curx == 1 && cury == 1)
		{
			// this maze has no exit, make another one
			return FALSE;
		}
		
		// debug only
		if(IsEmulator)
		{
			clear_vram();
			drawgenmap();
			pixel((int)(curx * sizex + 1), (int)(cury * sizey + 1));
			display_vram();
		}
	}
	
	// make changes permanent
	for(curx = 0; curx < MAPSIZE; curx++)
	{
		for(cury = 0; cury < MAPSIZE; cury++)
		{
			if(map[curx][cury] == 1)
			{
				map[curx][cury] = 1;
				solids[curx][cury] = SOLID;
			}
			else
			{
				map[curx][cury] = 0;
				solids[curx][cury] = UNSOLID;		
			}
		}
	}
	
	// create packs in dead-ends
	for(curx = 0; curx < MAPSIZE; curx++)
	{
		for(cury = 0; cury < MAPSIZE; cury++)
		{
			if(map[curx][cury] == SPACE)
			{
				if(cntwall(curx, cury) >= 3)
				{
					sprites = (struct st_sprite *) realloc(sprites, (spritecnt + 1) * sizeof(struct st_sprite));
					if(sprites == NULL)error("Memory; create sprites");
					sprites[spritecnt].x = curx + 0.5;
					sprites[spritecnt].y = cury + 0.5;
					sprites[spritecnt].texture.ptr = &pack;
					sprites[spritecnt].texture.width = 8;
					sprites[spritecnt].texture.height = 8;
					sprites[spritecnt].type = TYPE_PACK;
					sprites[spritecnt].effect = 50;
					spritecnt++;
					solids[curx][cury] = SPRITE;
				}
			}
			else if(map[curx][cury] == WALL)
			{
				// reduce the height of low walls, this gives a nice effect
				if(cntwall(curx, cury) == 2)
				{
					heights[curx][cury] = 32;
				}
			}
		}
	}
	
	for(curx = 0; curx < MAPSIZE; curx++)
	{
		for(cury = 0; cury < MAPSIZE; cury++)
		{
			if(map[curx][cury] == SPACE && cntwall(curx, cury) < 2)
			{
				// it is easier with some doors that connect two floors
				int dx, dy, fail1, fail2, fail3, fail4;
				fail1 = fail2 = fail3 = fail4 = FALSE;
				
				while(fail1 == FALSE && fail2 == FALSE && fail3 == FALSE & fail4 == FALSE)
				{
					switch(random() % 4)
					{
						case 0: dx = 0; dy = 1; fail1 = TRUE; break;
						case 1: dx = 0; dy = -1; fail2 = TRUE; break;
						case 2: dx = 1; dy = 0; fail3 = TRUE; break;
						case 3: dx = -1; dy = 0; fail4 = TRUE; break;
					}
					if(curx + dx < MAPSIZE && curx + dx >= 0 && cury + dy < MAPSIZE && cury + dy >= 0)
					{
						if(map[curx + dx][cury + dy] == SPACE)
						{
							map[curx + dx][cury + dy] = DOOR;
							solids[curx + dx][cury + dy] = SOLID;
							fail1 = fail2 = fail3 = fail4 = TRUE;
						}
					}
				}
			}
		}
	}
	
	clear_vram();
	drawgenmap();
	display_vram();
	
	return TRUE;
}

// main loop
void maze()
{
	do
	{
		int x = 1, y = 1, exit = TRUE;

		// create an empty map
		fill(&map, WALL, MAPSIZE * MAPSIZE);
		
		// render it until it is solvable
		while(exit == TRUE)
		{
			map[x][y] = SPACE;
			exit = kill(&x, &y, get(x, y));
			clear_vram();
			drawgenmap();
			display_vram();
		}
	}while(solve() == FALSE);
}
