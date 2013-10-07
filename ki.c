#include "global.h"
#include "ki.h"
#include "calc.h"
#include "sprites.h"

#include "mathf.h"

static int kshoot(float x, float y)
{
	float xadd, yadd;
	
	if(Abs(x - player.x) > Abs(y - player.y))
	{
		xadd = sgn(player.x - x);
		yadd = ((player.y - y) / Abs(x - player.x));
	}
	else
	{
		xadd = ((player.x - x) / Abs(y - player.y));
		yadd =sgn(player.y - y);
	}
	
	while(x < MAPSIZE && y < MAPSIZE && x >= 0 && y >= 0)
	{
		if((int)y == (int)player.y && (int)x == (int)player.x)
		{
			return TRUE;
		}
		if(solids[(int)x][(int)y] == SOLID)
		{
			break;
		}
		x += xadd;
		y += yadd;
	}
	return FALSE;
}

static void kimove()
{
	int c;
	int dirx, diry;
	
	for(c = 0; c < spritecnt; c++)
	{
		int fail[4] = {0}, success = FALSE;

		if(sprites[c].type == TYPE_ENEMY)
		{
			while(!(fail[0] == TRUE && fail[1] == TRUE && fail[2] == TRUE && fail[3] == TRUE) && success == FALSE)
			{
				float newx, newy;
				
				if(kshoot(sprites[c].x, sprites[c].y) == TRUE)
				{
					if(Abs((player.x) - sprites[c].x) > 3)
					{
						dirx = (player.x > sprites[c].x)?1:(player.x == sprites[c].x)?0:-1;
					}
					else
					{
						dirx = 0;
					}
					
					if(Abs((player.y) - sprites[c].y) > 3)
					{
						diry = (player.y > sprites[c].y)?1:(player.y == sprites[c].y)?0:-1;
					}
					else
					{
						diry = 0;
					}
					success = TRUE;
				}
				else
				{
					uint num;
					
					do
					{
						num = random() % 4;
					}while(fail[num] == TRUE);
					
					fail[num] = TRUE;
					
					switch(num)
					{
						case 0:
							dirx = 0;
							diry = -1;
							break;
						case 1:
							dirx = 1;
							diry = 0;
							break;
						case 2:
							dirx = 0;
							diry = 1;
							break;
						case 3:
							diry = 0;
							dirx = -1;
							break;
					}
				}
				
				newx = sprites[c].x + dirx;
				newy = sprites[c].y + diry;
				
				if(newx < MAPSIZE && newx >= 0 && newy < MAPSIZE && newy  >= 0)
				{
					if(solids[(int)newx][(int)newy] == UNSOLID)
					{
						solids[(int)sprites[c].x][(int)sprites[c].y] = UNSOLID;
						sprites[c].x = newx;
						sprites[c].y = newy;
						solids[(int)sprites[c].x][(int)sprites[c].y] = SPRITE;
						success = TRUE;
					}
				}
			}
		}
	}
}

static void kishoot(void)
{
	int c;
	
	for(c = 0; c < spritecnt; c++)
	{
		if(sprites[c].type == TYPE_ENEMY)
		{
			if(kshoot(sprites[c].x, sprites[c].y) == TRUE)
			{
				player.health -= 5;
				output = 1;
				statustimer = 0;
				status = hitmsg;
				BacklightOn();
			}
		}
	}
}

void timer(void)
{
	static int ki = 0;
	if(++ki == 10)
	{
		kimove();
		ki = 0;
		output = 1;
	}
	kishoot();
}

void kisetpos(float *x, float *y)
{
	do
	{
		*x = crand() % MAPSIZE + 0.5;
		*y = crand() % MAPSIZE + 0.5;
	}while(solids[(int)*x][(int)*y] != UNSOLID);

	solids[(int)*x][(int)*y] = SPRITE;
}