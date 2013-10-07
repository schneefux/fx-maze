#include "global.h"
#include "draw.h"
#include "sprites.h"
#include "hardware.h"
#include "key.h"
#include "syscalls.h"

int drawfloor = FALSE, drawheight = TRUE, drawtex = TRUE;

void horizontal(int y, int x1, int x2)
{
	int checker, i;
	if(y&~63 || (x1<0 && x2<0) || (x1>127 && x2>127)) return;
	if(x1 < 0) x1 = 0;
	if(x2 > 127) x2 = 127;
	if(x1>>3 != x2>>3)
	{
		vram[(y<<4)+(x1>>3)] |= 255 >> (x1&7);
		vram[(y<<4)+(x2>>3)] |= 255 << 7-(x2&7);
		for(i=(x1>>3)+1 ; i<x2>>3 ; i++)
		vram[(y<<4) + i] = 255;
	}
	else vram[(y<<4)+(x1>>3)] |= (255>>(x1%8 + 7-x2%8))<<(7-(x2&7));
}

void fillbox(int x1, int y1, int x2, int y2)
{
	int i;
	if(x1 > x2)
	{
		i = x1;
		x1 = x2;
		x2 = i;
	}
	if(y1 > y2)
	{
		i = y1;
		y1 = y2;
		y2 = i;
	}
	for(i=y1 ; i<=y2 ; i++)
		horizontal(i, x1, x2);
}

void locatePrintMini(int x, int y, const uchar *text)
{
	PrintMini((x - 2) * 6, (y - 2) * 8, text, 0);
}

void drawgenmap()
{
	int x, y;
	
	for(x = 0; x < MAPSIZE; x++)
	{
		for(y = 0; y < MAPSIZE; y++)
		{
			if(map[x][y] == WALL || map[x][y] == CHECKED)
			{
				fillbox(x * sizex, y * sizey, (x + 1) * sizex, (y + 1) * sizey);
			}
		}
	}
}

void showmap()
{
	int x, y, exit = FALSE;
	int windowx = player.x, windowy = player.x, zoom = 8;
	const char plsprite = 0xA9;
	int lastkey, thiskey = 0;
	do
	{
		int skew = 64 / zoom;
		
		while(windowx + zoom * 2 >= MAPSIZE)
		{
			windowx--;
		}
		
		clear_vram();
		
		for(x = windowx; x < windowx + zoom * 2; x++)
		{
			for(y = windowy; y < windowy + zoom; y++)
			{
				if(map[x][y] != SPACE)
				{
					fillbox((x - windowx) * skew, (y - windowy) * skew, (x + 1 - windowx) * skew, (y + 1 - windowy) * skew);
					switch(map[x][y])
					{
						case WALL: break;
						case DOOR:
							PrintMini((x - windowx) * skew, (y - windowy) * skew, "I", MINI_OVER);
							break;
					}
				}
				else if(x == (int)player.x && y == (int)player.y)
				{
					PrintMini((player.x - windowx) * skew + 1, (player.y - windowy) * skew, &plsprite, MINI_OVER);
				}
			}
		}
		
		for(x = 0; x < spritecnt; x++)
		{
			if(sprites[x].x >= windowx && sprites[x].x < windowx + zoom * 2 && sprites[x].y >= windowy && sprites[x].y < windowy + zoom)
			{
				switch(sprites[x].type)
				{
					case TYPE_ENEMY:
						PrintMini((sprites[x].x - windowx) * skew, (sprites[x].y - windowy) * skew, "!", MINI_OVER);
						break;
					case TYPE_PACK:
						PrintMini((sprites[x].x - windowx) * skew, (sprites[x].y - windowy) * skew, "+", MINI_OVER);
						break;
				}
			}
		}
		
		display_vram();
		
		keyupdate();
		
		if(lastkey != thiskey)
		{
			Sleep(500);
		}
		else if(lastkey == thiskey)
		{
			Sleep(125);
		}
		
		lastkey = thiskey;
		
		if(keydown(KEY_CTRL_EXIT))exit = TRUE;
		if(keydown(KEY_CTRL_UP) && windowy > 0)
		{
			windowy--;
			thiskey = KEY_CTRL_UP;
		}
		if(keydown(KEY_CTRL_DOWN) && windowy + zoom < MAPSIZE)
		{
			windowy++;
			thiskey = KEY_CTRL_DOWN;
		}
		if(keydown(KEY_CTRL_LEFT) && windowx > 0)
		{
			windowx--;
			thiskey = KEY_CTRL_LEFT;
		}
		if(keydown(KEY_CTRL_RIGHT) && windowx + zoom * 2 < MAPSIZE)
		{
			windowx++;
			thiskey = KEY_CTRL_RIGHT;
		}
		if(keydown(KEY_CHAR_PLUS) && zoom > 1)
		{
			zoom--;
			thiskey = KEY_CHAR_PLUS;
		}
		if(keydown(KEY_CHAR_MINUS) && zoom < MAPSIZE / 2)
		{
			zoom++;
			thiskey = KEY_CHAR_MINUS;
		}
	}while(exit == FALSE);
}

void drawgun()
{
	int i,u;
	
	const int y = 47 + player.gunpos;
	
	for(i = 0; i < 21; i++)
	{
		for(u = 0; u < 22; u++)
		{
			if(y + u <= 64)
			{
				switch(player.weapon)
				{
					case GUN:
						if(gun[u][i] == 1)
						{
							(*(vram +  ((y + u) << 4) + ((54 + i) >> 3))) |= (128 >> ((54 + i) & 7));
						}
						else
						{
							if(gun[u][i] == 2)
							{
								(*(vram + ((y + u) << 4) + ((54 + i) >> 3))) &= ( ~ (128 >> ((54 + i) & 7)));		
							}
						}
						break;
						
					case KNIFE:
						if(knife[u][i] == 1)
						{
							(*(vram +  ((y + u) << 4) + ((54 + i) >> 3))) |= (128 >> ((54 + i) & 7));
						}
						else
						{
							if(knife[u][i] == 2)
							{
								(*(vram + ((y + u) << 4) + ((54 + i) >> 3))) &= ( ~ (128 >> ((54 + i) & 7)));		
							}
						}
						break;
				}
			}
		}
	}
}

void vertical(int x, int tex, int start, int end, int type, int color, float steps)
{
	int y = start;
	int pos = 1 << 7, step;
	
	uchar xbyte = x & 7;
	uchar shiftbyte = (128 >> xbyte);
	uchar *buffpos = (unsigned char*)(vram + (x >> 3));
		
	if(drawtex == FALSE && type == 1)
	{
		if(start > end)
		{
			int tmp = start;
			start = end;
			end = tmp;
		}
		if(start < 0) start = 0;
		if(end > 63) end = 63;

		for(;start < end; start++)
		pixel(x,start);	
	}
	
	if(start > end)
	{
		int tmp = start;
		start = end;
		end = tmp;
	}
	
	switch(type)
	{
		case 1 :
		if(steps == 0)
		step = (16 << 8) / (end - start);
		else
		step = (16.0 / steps) * 128.0;
	
		for(; y < end;pos += step, y++)
		{
			if(wall[color][pos >> 8][(int)(tex >> 2)] == 1)
			(*(buffpos +  (y << 4))) |= ((1 << 7) >> xbyte);
			/*else
			(*(buffpos +  (y << 4))) &= ~((1 << 7) >> xbyte);*/			
		}
		break;
		
		case 2 :
		if(steps == 0)
		step = (16 << 8) / (end - start);		
		else
		step = (16.0 / steps) * 128.0;
	
		for(; y < end;pos += step, y ++)
		{
			(*(buffpos +  (y << 4))) |= ((door[pos >> 8][(int)(tex >> 2)] << 7) >> xbyte);
		}
		break;
		
		case 3 :
		if(steps == 0)
		step = (8 << 8) / (end - start);
		else
		step = (8.0 / steps) * 128.0;
	
		for(; y < end;pos += step, y ++)
		{
			if(pack[pos >> 8][(int)(tex >> 3)] == 1)
			{
				(*(buffpos +  (y << 4))) |= shiftbyte;
			}
			else
			{
				if(pack[pos >> 8][(int)(tex >> 3)] == 2)
				{
					(*(buffpos + (y << 4))) &= ( ~shiftbyte);		
				}			
			}
		}
		break;
	}
}
