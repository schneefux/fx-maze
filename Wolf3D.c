/* wird zum Waffenwechsel werden.
"Türen kann man nur öffnen" - was willst du sonst damit machen? Aufessen?
*/

#include "key.h"
#include "global.h"
#include "syscalls.h"
#include "hardware.h"
#include "mapgen.h"
#include "ki.h"
#include "engine.h"
#include "sprites.h"

#include "stdio.h"

void main(void)
{
	char FPS[9];
	char LIVE[13];
	static int oldtime;
	static int maintimer = 0;

	if(RTC_Elapsed_ms(maintimer, 100))
	{
		maintimer = RTC_GetTicks();
		
		if(player.health <= 50)
		{
			if(contrast > 10 || contrast < -10)
			{
				contradd *= -1;
			}
			contrast += contradd;
			set_contrast(168 + contrast);
		}
		
		if(statustimer++ == 100)
		{
			statustimer = 0;
			status = NULL;
		}
		
		if(BacklightIsOn() && statustimer % 5 == 0)
		{
			BacklightOff();
		}
	}
	
	move();
	if(output != 0)
	{
		unsigned int time;
		oldtime = RTC_GetTicks();
		clear_vram();
		cast();
		
		drawgun();
		
		if(output == 2)
		{
			if(player.gunpos > 3 || player.gunpos < -3)
			{
				if(player.gunpos > 3)
				player.gunpos = 3;
				
				gundir *= -1;
			}
			player.gunpos += gundir;
		}	
		
		sprintf(&FPS, "fps:%2.2f", 1 / fps);
		PrintMini(0, 0, &FPS, MINI_OR);
		
		sprintf(&LIVE, "health:%4d", player.health);
		PrintMini(80, 0, &LIVE, MINI_OR);
		
		if(status != NULL)PrintMini(0, 58, status, MINI_OR);
		
		display_vram();
		if(player.health <= 0)
		{
			exit = TRUE;
		}
		output = 0;
		
		fps = (((RTC_GetTicks() * 15.625 - oldtime * 15.625)) / 1000);
	}
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	int c;
	vram = Disp_GetVRAMPtr();
	
	if(getCalc() == UNKNOWN)
	{
		clear_vram();
		locate(1,1);
		Print("Unknown hardware");
		locate(1,2);
		Print("detected.");
		locate(1,3);
		Print("All direct hardware");
		locate(1,4);
		Print("functions will be");
		locate(1,5);
		Print("disabled!");
		locate(1,7);
		Print("Press any key");
		locate(1,8);
		Print("to start the game");
		GetKey(&c);
	}
	
	APP_EnableRestart();

	table();
	seedrandom();
	
	if(ENEMYCNT)
	{
		sprites = (struct st_sprite *) malloc(ENEMYCNT * sizeof(struct st_sprite));
		if(sprites == NULL)error();
	}
	
	spritecnt = ENEMYCNT;
	
	for(c = 0; c < spritecnt; c++)
	{
		kisetpos(&sprites[c].x, &sprites[c].y);
		sprites[c].texture.ptr = &enemy;
		sprites[c].texture.width = 16;
		sprites[c].texture.height = 32;
		sprites[c].type = TYPE_ENEMY;
		sprites[c].effect = 50;
	}
	
	maze();
	
	player.x = 1.5;
	player.y = 1.5;
	player.dirX = -1;
	player.dirY = 0;
	player.planeX = 0;
	player.planeY = 0.66;
	player.weapon = GUN;
	player.gunpos = 0;
	player.health = 500;
	contrast = 0;
	
	Timer_Install(8, &timer, KISPEED);
	Timer_Start(8);
	
	exit = FALSE;
	
	while(exit == FALSE)
	{
		main();
		if((int)player.x == MAPSIZE - 1 && (int)player.y == MAPSIZE - 1)break;
	}
	
	Timer_Uninstall(8);
	set_contrast(168);
	
	if(player.health > 0 && exit == FALSE)
	{
		clear_vram();
	
		locate(1, 1);
		Print("You found the exit!");
		
		display_vram();
		Sleep(1000);
	}
	free(sprites);
	
	Keyboard_ClrBuffer();
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{return INIT_ADDIN_APPLICATION(isAppli, OptionNum);}
#pragma section
