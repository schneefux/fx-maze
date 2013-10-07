#include "global.h"
#include "engine.h"
#include "draw.h"
#include "key.h"
#include "calc.h"
#include "hardware.h"
#include "sprites.h"
#include "menu.h"

#include "mathf.h"

float fps;

void swap(float *a, float *b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

void combSort(int* order, float* dist, int amount)
{
	int gap = amount, i;
	int swapped = FALSE;
	while(gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if(gap == 9 || gap == 10) gap = 11;
		if (gap < 1) gap = 1;
		swapped = FALSE;
		for (i = 0; i < amount - gap; i++)
		{
			int j = i + gap;
			if (dist[i] < dist[j])
			{
				swap(&dist[i], &dist[j]);
				swap(&order[i], &order[j]);
				swapped = TRUE;
			}
		}
	}
}

#define PI 3.141592653589793238464

static void pshoot()
{
	float xadd, yadd, x, y;
	int c;
	
	for(c = 0; c < spritecnt; c++)
	{
		if(sprites[c].type == TYPE_ENEMY)
		{
			 x = player.x;
			 y = player.y;
			if(Abs(x - sprites[c].x) > Abs(y - sprites[c].y))
			{
				xadd = sgn(sprites[c].x - x);
				yadd = ((sprites[c].y - y) / Abs(x - sprites[c].x));
			}
			else
			{
				xadd = ((sprites[c].x - x) / Abs(y - sprites[c].y));
				yadd = sgn(sprites[c].y - y);
			}
			
			if(1/*TODOTODOTODOTODO*/)
			{
				while(x < MAPSIZE && y < MAPSIZE && x >= 0 && y >= 0)
				{
					x += xadd;
					y += yadd;
					
					if((int)y == (int)sprites[c].y && (int)x == (int)sprites[c].x)
					{
						sprites[c].effect -= 5;
						if(sprites[c].effect <= 0)
						{
							sprites[c] = sprites[spritecnt];
							sprites = (struct st_sprite *) realloc(sprites, spritecnt-- * sizeof(struct st_sprite));
							if(sprites == NULL)error();
						}
						return;
					}
					
					if(solids[(int)(x + 0.5)][(int)(y + 0.5)] == SOLID)
					{
						break;
					}
				}
			}
		}
	}
}

void move()
{
	float oldDirX, oldPlaneX, moveSpeed = fps * 1.25, rotSpeed = fps / 1.25;
	float newx = 0, newy = 0;
	keyupdate();
	if(keydown(KEY_CTRL_DOWN) || keydown(KEY_CTRL_UP) || keydown(KEY_CTRL_LEFT) || keydown(KEY_CTRL_RIGHT))
	{
		if(keydown(KEY_CTRL_DOWN))
		{
				newy = player.y - (player.dirY * moveSpeed);
				newx = player.x - (player.dirX * moveSpeed);
				if(newx >= 0 && newx < MAPSIZE)
				if(solids[(int)newx][(int)player.y] != SOLID)
				{
					player.x = newx;
				}

				if(newy >= 0 && newy < MAPSIZE)
				if(solids[(int)player.x][(int)newy] != SOLID)
				{
					player.y = newy;
				}
				output = 2;
		}
		if(keydown(KEY_CTRL_UP))
		{
				newy = player.y + (player.dirY * moveSpeed);
				newx = player.x + (player.dirX * moveSpeed);
				if(newx >= 0 && newx < MAPSIZE)
				if(solids[(int)newx][(int)player.y] != SOLID)
				{
					player.x = newx;
				}
				if(newy >= 0 && newy < MAPSIZE)
				if(solids[(int)player.x][(int)newy] != SOLID)
				{
					player.y = newy;
				}
				output = 2;
		}
		if(keydown(KEY_CTRL_RIGHT))
		{
				oldDirX = player.dirX;
				player.dirX = player.dirX * cosf(-rotSpeed) - player.dirY * sinf(-rotSpeed);
				player.dirY = oldDirX * sinf(-rotSpeed) + player.dirY * cosf(-rotSpeed);
				oldPlaneX = player.planeX;
				player.planeX = player.planeX * cosf(-rotSpeed) - player.planeY * sinf(-rotSpeed);
				player.planeY = oldPlaneX * sinf(-rotSpeed) + player.planeY * cosf(-rotSpeed);
				output = (output < 2)?1:2;
		}
		if(keydown(KEY_CTRL_LEFT))
		{
				oldDirX = player.dirX;
				player.dirX = player.dirX * cosf(rotSpeed) - player.dirY * sinf(rotSpeed);
				player.dirY = oldDirX * sinf(rotSpeed) + player.dirY * cosf(rotSpeed);
				oldPlaneX = player.planeX;
				player.planeX = player.planeX * cosf(rotSpeed) - player.planeY * sinf(rotSpeed);
				player.planeY = oldPlaneX * sinf(rotSpeed) + player.planeY * cosf(rotSpeed);
				output = (output < 2)?1:2;
		}
		if(solids[(int)newx][(int)newy] == SPRITE)
		{
			int c;
			for(c = 0; c < spritecnt; c++)
			{
				if(sprites[c].type == TYPE_PACK && (int)sprites[c].x == (int)newx && (int)sprites[c].y == (int)newy)
				{
					solids[(int)newx][(int)newy] = UNSOLID;
					player.health += sprites[c].effect;
					
					sprites[c] = sprites[spritecnt];
					sprites = (struct st_sprite *) realloc(sprites, spritecnt-- * sizeof(struct st_sprite));
					if(sprites == NULL)error();
					
					output = 2;
					status = packmsg;
					statustimer = 0;
					break;
				}
			}
		}
	}
	else
	{
		if(keydown(KEY_CTRL_MENU))
		{
			openmenu();
			output = (output < 2)?1:2;
			return;
		}
	}
	
	if(keydown(KEY_CTRL_SHIFT))
	{
			switch(player.weapon)
			{
				case GUN:
					pshoot();
					break;
				/*case KNIFE:
					newy = player.y + player.dirY;
					newx = player.x + player.dirX;
					if(newx >= 0 && newx < MAPSIZE)
						if(map[(int)(newx)][(int)(newy)] >= 10)
						{enemies[map[(int)(newx)][(int)(newy)] - 10].health -= 15;}
					break;*/
			}
			
			output = 2;
	}
	if(keydown(KEY_CTRL_ALPHA))
	{
		newy = player.y + player.dirY;
		newx = player.x + player.dirX;
		if(newx >= 0 && newx < MAPSIZE)
		{
			if(map[(int)(newx)][(int)(newy)] == DOOR)
			{
				map[(int)(newx)][(int)(newy)] = SPACE;
				solids[(int)newx][(int)newy] = UNSOLID;
			}
		}
		output = (output < 2)?1:2;
	}
	if(keydown(KEY_CTRL_OPTN))
	{
		player.weapon += 1;
		if(player.weapon == WEAPON_OVERFLOW)
		player.weapon = GUN;
	}
}

void cast()
{
	float cameraX,rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist, wallX, floorXWall, floorYWall, distWall;
	int mapX, mapY, lineHeight, hit, side, x, tex, y, black, floorTexX, floorTexY, actualheight, heightdiff;
	int stepX, drawStart, drawEnd, stepY;
	int weight, currentFloorX, currentFloorY;
	float ZBuffer[128], *spriteDist;
	int *spriteOrder, *spritedrawn;
	int foundsprite = FALSE, spritehere;
	
	spriteDist = (float *) calloc(spritecnt, sizeof(float));
	if(spriteDist == NULL)error();
	spriteOrder = (int *) calloc(spritecnt, sizeof(int));
	if(spriteOrder == NULL)error();

	for(x = 0; x < spritecnt; x++)
	{
		spriteOrder[x] = x;
		spriteDist[x] = ((player.x - sprites[x].x) * (player.x - sprites[x].x) + (player.y - sprites[x].y) * (player.y - sprites[x].y));
	}
	
	combSort(spriteOrder, spriteDist, spritecnt);
	free(spriteDist);

	spritedrawn = (int *) calloc(spritecnt, sizeof(int));

	for(x = 0; x < 128; x++)
	{
		mapX = player.x;
		mapY = player.y;		

		cameraX = x / 64.0 - 1;
		rayDirX = player.dirX + player.planeX * cameraX;
		rayDirY = player.dirY + player.planeY * cameraX;

		deltaDistX = sqrtf(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrtf(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		
		hit = FALSE;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
		}
		
		actualheight = 0;
		
		spritehere = FALSE;
		
		while (mapX < MAPSIZE && mapY < MAPSIZE && mapX >= 0 && mapY >= 0 && hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			
			if(solids[mapX][mapY] == SPRITE)
			{
				foundsprite = TRUE;
				spritehere = TRUE;
			}
			
			if(solids[mapX][mapY] == SOLID)
			{			
				if(heights[mapX][mapY] == 0 || drawheight == FALSE)
				{
					hit = TRUE;
				}
				else
				{
					if (side == 0)
						perpWallDist = Abs((mapX - player.x + (1 - stepX) / 2) / rayDirX);
					else
						perpWallDist = Abs((mapY - player.y + (1 - stepY) / 2) / rayDirY);
										
					lineHeight = Abs((int)((32 - heights[mapX][mapY] )/ perpWallDist));
					      
					if(side == 1) wallX = player.x + ((mapY - player.y + (1 - stepY) / 2) / rayDirY) * rayDirX;
					else wallX = player.y + ((mapX - player.x + (1 - stepX) / 2) / rayDirX) * rayDirY;
					wallX -= floorf((wallX));
				
					tex = (int)(wallX * 64);
					
					drawStart = 32 - (lineHeight >> 1);
					if(drawStart < 0) drawStart = 0;	
					drawEnd = (actualheight == 0)?32 + (Abs((int)(64 / perpWallDist)) >> 1):actualheight;
					if(drawEnd >= 64) drawEnd = 63;	
						
					vertical(x, tex , drawStart, drawEnd, map[mapX][mapY], side, Abs((32 + (Abs((int)(64 / perpWallDist)) >> 1)) - (32 - (Abs((int)(64 / perpWallDist)) >> 1))));
					
					if(side == 0 && rayDirX > 0)
					{
						floorXWall = mapX;
						floorYWall = mapY + wallX;
					}
					else if(side == 0 && rayDirX < 0)
					{
						floorXWall = mapX + 1.0;
						floorYWall = mapY + wallX;
					}
					else if(side == 1 && rayDirY > 0)
					{
						floorXWall = mapX + wallX;
						floorYWall = mapY;
					}
					else
					{
						floorXWall = mapX + wallX;
						floorYWall = mapY + 1.0;
					} 
					      
					distWall = perpWallDist;

					if(drawfloor == TRUE && actualheight == 0)
					{
						for(y = drawEnd + 1; y < 64; y++)
						{
							weight = TDist[y] / distWall;
							         
							currentFloorX = (weight * floorXWall) + ((1 << 8) - weight) * player.x;
							currentFloorY = (weight * floorYWall) + ((1 << 8) - weight) * player.y;
				
							floorTexX = (currentFloorX >> 4) % 16;
							floorTexY = (currentFloorY >> 4) % 16;
				
							black = ((int)(currentFloorX >> 8) + (int)(currentFloorY >> 8)) % 2;
							
							if(floor[floorTexY][floorTexX] == black)
							(*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7));
						}
					}
					actualheight = drawStart;
				}
			}
		}
						
		if(hit == TRUE)
		{
			if (side == 0)
				perpWallDist = Abs((mapX - player.x + (1 - stepX) / 2) / rayDirX);
			else
				perpWallDist = Abs((mapY - player.y + (1 - stepY) / 2) / rayDirY);
			
			ZBuffer[x] = perpWallDist;
			 
			lineHeight = Abs((int)(64 / perpWallDist));
			      
			if(side == 1) wallX = player.x + ((mapY - player.y + (1 - stepY) / 2) / rayDirY) * rayDirX;
			else wallX = player.y + ((mapX - player.x + (1 - stepX) / 2) / rayDirX) * rayDirY;
			wallX -= floorf((wallX));
			      
			tex = (int)(wallX * 64);
			
			drawStart = 32 - (lineHeight >> 1);
			if(drawStart < 0) drawStart = 0;	
			drawEnd = (actualheight == 0)?(lineHeight >> 1) + 32:actualheight;
			if(drawEnd >= 64) drawEnd = 63;
			
			vertical(x, tex , drawStart, drawEnd, map[mapX][mapY], side, (actualheight > 0)?((lineHeight >> 1) + 32) - (32 - (lineHeight >> 1)):0);
			
			if(drawfloor == TRUE)
			{
				if(side == 0 && rayDirX > 0)
				{
					floorXWall = mapX;
					floorYWall = mapY + wallX;
				}
				else if(side == 0 && rayDirX < 0)
				{
					floorXWall = mapX + 1.0;
					floorYWall = mapY + wallX;
				}
				else if(side == 1 && rayDirY > 0)
				{
					floorXWall = mapX + wallX;
					floorYWall = mapY;
				}
				else
				{
					floorXWall = mapX + wallX;
					floorYWall = mapY + 1.0;
				} 
				      
				distWall = perpWallDist;
				
				for(y = drawEnd + 1; y < 64; y++)
				{
					weight = TDist[y] / distWall;
					         
					currentFloorX = (weight * floorXWall) + ((1 << 8) - weight) * player.x;
					currentFloorY = (weight * floorYWall) + ((1 << 8) - weight) * player.y;
		
					floorTexX = (currentFloorX >> 4) % 16;
					floorTexY = (currentFloorY >> 4) % 16;
		
					black = ((int)(currentFloorX >> 8) + (int)(currentFloorY >> 8)) % 2;
					
					if(drawtex == TRUE)
					{
						if(floor[floorTexY][floorTexX] == black && y < 64 - actualheight)
						(*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7));
						if(ceiling[floorTexY][floorTexX] == black)
						(*(vram +  (64 - y << 4) + (x >> 3))) |= (128 >> (x & 7));
					}
					else
					{
						if(black)
						{
							 if(y < 64 - actualheight)
							(*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7));
						}
						else
						(*(vram +  (64 - y << 4) + (x >> 3))) |= (128 >> (x & 7));					
					}
				}
			}
		}
	}
	
	#define uDiv 1
	#define vDiv 1
	#define vMove 0.0
	
	for(x = 0; x < spritecnt; x++)
	{
		float spriteX = sprites[spriteOrder[x]].x - player.x;
		float spriteY = sprites[spriteOrder[x]].y - player.y;
		float invDet = 1.0 / (player.planeX * player.dirY - player.dirX * player.planeY);
		float transformX = invDet * (player.dirY * spriteX - player.dirX * spriteY);
		float transformY = invDet * (-player.planeY * spriteX + player.planeX * spriteY);
		int vMoveScreen = (int)(vMove / transformY);
		int spriteScreenX = (int)(64 * (1 + transformX / transformY));
		int spriteHeight = Abs((int)(64 / transformY)) / vDiv;
		int drawStartY = -spriteHeight / 2 + 32 + vMoveScreen;
		int drawEndY = spriteHeight / 2 + 32 + vMoveScreen;
		int spriteWidth = Abs((int)(64 / transformY)) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		int stripe;
		int y;
		
		if(drawStartY < 0)drawStartY = 0;
		if(drawEndY > 63)drawEndY = 63;
		if(drawStartX < 0)drawStartX = 0;
		if(drawEndX > 127)drawEndX = 127;
		
		for(stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprites[spriteOrder[x]].texture.width / spriteWidth) / 256;
			
			if(transformY > 0 && stripe > 0 && stripe < 128 && transformY < ZBuffer[stripe])
			{
				for(y = drawStartY; y < drawEndY; y++)
				{
					int d = (y - vMoveScreen) * 256 - 8192 + spriteHeight * 128;
					int texY = ((d * sprites[spriteOrder[x]].texture.height) / spriteHeight) / 256;
					
					if(sprites[spriteOrder[x]].texture.ptr[texY * sprites[spriteOrder[x]].texture.width + texX] == 1)
					{
						pixel(stripe, y);
					}
					else
					{
						if(sprites[spriteOrder[x]].texture.ptr[texY * sprites[spriteOrder[x]].texture.width + texX] == 2)
						{
							clrpixel(stripe, y);		
						}
					}
				}
			}
		}
	}
	
	free(spriteOrder);
}
/*void cast()
{
	float cameraX,rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist, wallX, floorXWall, floorYWall, distWall;
	int mapX, mapY, lineHeight, hit, side, x, tex, y, black, floorTexX, floorTexY, actualheight, heightdiff;
	int stepX, drawStart, drawEnd, stepY;
	int weight, currentFloorX, currentFloorY;
	float *ZBuffer[128], *spriteDist;
	int *highest[128], dims[128] = {0};
	int *spriteOrder;
	int foundsprite = FALSE, spritehere;
	
	for(x = 0; x < 128; x++)
	{
		highest[x] = NULL;
		ZBuffer[x] = NULL;
		
		mapX = player.x;
		mapY = player.y;		

		cameraX = x / 64.0 - 1;
		rayDirX = player.dirX + player.planeX * cameraX;
		rayDirY = player.dirY + player.planeY * cameraX;

		deltaDistX = sqrtf(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrtf(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		       
		hit = FALSE;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
		}
		
		actualheight = 0;
		
		spritehere = FALSE;
		
		while (mapX < MAPSIZE && mapY < MAPSIZE && mapX >= 0 && mapY >= 0 && hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			
			if(solids[mapX][mapY] == SPRITE)
			{
				foundsprite = TRUE;
				spritehere = TRUE;
			}
			
			if(solids[mapX][mapY] == SOLID)
			{			
				if(heights[mapX][mapY] == 0 || drawheight == FALSE)
				{
					hit = TRUE;
				}
				else
				{
					if (side == 0)
						perpWallDist = Abs((mapX - player.x + (1 - stepX) / 2) / rayDirX);
					else
						perpWallDist = Abs((mapY - player.y + (1 - stepY) / 2) / rayDirY);
					
					ZBuffer[x] = (float *) realloc(ZBuffer[x], ++dims[x] * sizeof(float));
					*(ZBuffer[x] + dims[x] - 1) = perpWallDist;
					
					lineHeight = Abs((int)((32 - heights[mapX][mapY] )/ perpWallDist));
					      
					if(side == 1) wallX = player.x + ((mapY - player.y + (1 - stepY) / 2) / rayDirY) * rayDirX;
					else wallX = player.y + ((mapX - player.x + (1 - stepX) / 2) / rayDirX) * rayDirY;
					wallX -= floorf((wallX));
				
					tex = (int)(wallX * 64);
					
					drawStart = 32 - (lineHeight >> 1);
					if(drawStart < 0) drawStart = 0;	
					drawEnd = (actualheight == 0)?32 + (Abs((int)(64 / perpWallDist)) >> 1):actualheight;
					if(drawEnd >= 64) drawEnd = 63;	
						
					vertical(x, tex , drawStart, drawEnd, map[mapX][mapY], side, Abs((32 + (Abs((int)(64 / perpWallDist)) >> 1)) - (32 - (Abs((int)(64 / perpWallDist)) >> 1))));
					
					if(side == 0 && rayDirX > 0)
					{
						floorXWall = mapX;
						floorYWall = mapY + wallX;
					}
					else if(side == 0 && rayDirX < 0)
					{
						floorXWall = mapX + 1.0;
						floorYWall = mapY + wallX;
					}
					else if(side == 1 && rayDirY > 0)
					{
						floorXWall = mapX + wallX;
						floorYWall = mapY;
					}
					else
					{
						floorXWall = mapX + wallX;
						floorYWall = mapY + 1.0;
					} 
					      
					distWall = perpWallDist;

					if(drawfloor == TRUE && actualheight == 0)
					{
						for(y = drawEnd + 1; y < 64; y++)
						{
							weight = TDist[y] / distWall;
							         
							currentFloorX = (weight * floorXWall) + ((1 << 8) - weight) * player.x;
							currentFloorY = (weight * floorYWall) + ((1 << 8) - weight) * player.y;
				
							floorTexX = (currentFloorX >> 4) % 16;
							floorTexY = (currentFloorY >> 4) % 16;
				
							black = ((int)(currentFloorX >> 8) + (int)(currentFloorY >> 8)) % 2;
							
							if(floor[floorTexY][floorTexX] == black)
							(*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7));
						}
					}
					actualheight = drawStart;
					
					highest[x] = (int *) realloc(highest[x], dims[x] * sizeof(int));
					*(highest[x] + dims[x] - 1) = actualheight;
				}
			}
		}
		
		if(hit == TRUE)
		{
			if (side == 0)
				perpWallDist = Abs((mapX - player.x + (1 - stepX) / 2) / rayDirX);
			else
				perpWallDist = Abs((mapY - player.y + (1 - stepY) / 2) / rayDirY);
			 
			ZBuffer[x] = (float *) realloc(ZBuffer[x], ++dims[x] * sizeof(float));
			*(ZBuffer[x] + dims[x] - 1) = perpWallDist;
			highest[x] = (int *) realloc(highest[x], dims[x] * sizeof(int));
			*(highest[x] + dims[x] - 1) = actualheight;
					
			 
			lineHeight = Abs((int)(64 / perpWallDist));
			      
			if(side == 1) wallX = player.x + ((mapY - player.y + (1 - stepY) / 2) / rayDirY) * rayDirX;
			else wallX = player.y + ((mapX - player.x + (1 - stepX) / 2) / rayDirX) * rayDirY;
			wallX -= floorf((wallX));
			      
			tex = (int)(wallX * 64);
			
			drawStart = 32 - (lineHeight >> 1);
			if(drawStart < 0) drawStart = 0;	
			drawEnd = (actualheight == 0)?(lineHeight >> 1) + 32:actualheight;
			if(drawEnd >= 64) drawEnd = 63;
			
			vertical(x, tex , drawStart, drawEnd, map[mapX][mapY], side, (actualheight > 0)?((lineHeight >> 1) + 32) - (32 - (lineHeight >> 1)):0);
			
			if(drawfloor == TRUE)
			{
				if(side == 0 && rayDirX > 0)
				{
					floorXWall = mapX;
					floorYWall = mapY + wallX;
				}
				else if(side == 0 && rayDirX < 0)
				{
					floorXWall = mapX + 1.0;
					floorYWall = mapY + wallX;
				}
				else if(side == 1 && rayDirY > 0)
				{
					floorXWall = mapX + wallX;
					floorYWall = mapY;
				}
				else
				{
					floorXWall = mapX + wallX;
					floorYWall = mapY + 1.0;
				} 
				      
				distWall = perpWallDist;
				
				for(y = drawEnd + 1; y < 64; y++)
				{
					weight = TDist[y] / distWall;
					         
					currentFloorX = (weight * floorXWall) + ((1 << 8) - weight) * player.x;
					currentFloorY = (weight * floorYWall) + ((1 << 8) - weight) * player.y;
		
					floorTexX = (currentFloorX >> 4) % 16;
					floorTexY = (currentFloorY >> 4) % 16;
		
					black = ((int)(currentFloorX >> 8) + (int)(currentFloorY >> 8)) % 2;
					
					if(drawtex == TRUE)
					{
						if(floor[floorTexY][floorTexX] == black && y < 64 - actualheight)
						(*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7));
						if(ceiling[floorTexY][floorTexX] == black)
						(*(vram +  (64 - y << 4) + (x >> 3))) |= (128 >> (x & 7));
					}
					else
					{
						if(black)
						{
							 if(y < 64 - actualheight)
							(*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7));
						}
						else
						(*(vram +  (64 - y << 4) + (x >> 3))) |= (128 >> (x & 7));					
					}
				}
			}
		}
	}
	
	if(foundsprite == TRUE)
	{
		spriteDist = (float *) calloc(spritecnt, sizeof(float));
		if(spriteDist == NULL)error();
		spriteOrder = (int *) calloc(spritecnt, sizeof(int));
		if(spriteOrder == NULL)error();
	
		for(x = 0; x < spritecnt; x++)
		{
			spriteOrder[x] = x;
			spriteDist[x] = ((player.x - sprites[x].x) * (player.x - sprites[x].x) + (player.y - sprites[x].y) * (player.y - sprites[x].y));
		}
		
		combSort(spriteOrder, spriteDist, spritecnt);
		
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
			
		for(x = 0; x < spritecnt; x++)
		{
			float spriteX = sprites[spriteOrder[x]].x - player.x;
			float spriteY = sprites[spriteOrder[x]].y - player.y;
			float invDet = 1.0 / (player.planeX * player.dirY - player.dirX * player.planeY);
			float transformX = invDet * (player.dirY * spriteX - player.dirX * spriteY);
			float transformY = invDet * (-player.planeY * spriteX + player.planeX * spriteY);
			int vMoveScreen = (int)(vMove / transformY);
			int spriteScreenX = (int)(64 * (1 + transformX / transformY));
			int spriteHeight = Abs((int)(64 / transformY)) / vDiv;
			int drawStartY = -spriteHeight / 2 + 32 + vMoveScreen;
			int drawEndY = spriteHeight / 2 + 32 + vMoveScreen;
			int spriteWidth = Abs((int)(64 / transformY)) / uDiv;
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			int stripe;
			int y;
			
			if(drawStartY < 0)drawStartY = 0;
			if(drawEndY > 63)drawEndY = 63;
			if(drawStartX < 0)drawStartX = 0;
			if(drawEndX > 127)drawEndX = 127;
			
			//if(drawEndY > highest[x] && highest[x] != 0)drawEndY = highest[x];
			
			for(stripe = drawStartX; stripe < drawEndX; stripe++)
			{
				int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprites[spriteOrder[x]].texture.width / spriteWidth) / 256, c = 0;
				
				do
				{
					c++;
				}while(*(ZBuffer[stripe] + c) != spriteDist[x] && c < dims[stripe]);
				
				if(drawEndY > *(highest[x] + c))drawEndY = *(highest[x] + c);
				
				if(transformY > 0 && stripe > 0 && stripe < 128 && transformY < *(ZBuffer[stripe] + c))
				{
					for(y = drawStartY; y < drawEndY; y++)
					{
						int d = (y - vMoveScreen) * 256 - 8192 + spriteHeight * 128;
						int texY = ((d * sprites[spriteOrder[x]].texture.height) / spriteHeight) / 256;
						
						if(sprites[spriteOrder[x]].texture.ptr[texY * sprites[spriteOrder[x]].texture.width + texX] == 1)
						{
							pixel(stripe, y);
						}
						else
						{
							if(sprites[spriteOrder[x]].texture.ptr[texY * sprites[spriteOrder[x]].texture.width + texX] == 2)
							{
								clrpixel(stripe, y);		
							}
						}
					}
				}
			}
		}
		free(spriteOrder);
		free(spriteDist);
	}
}
*/