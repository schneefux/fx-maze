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
	// strings for display
	char FPS[9];
	char LIVE[13];
	// fps counter
	static int oldtime;
	static int maintimer = 0;

	// every 100 ms, change contrast
	if(RTC_Elapsed_ms(maintimer, 100))
	{
		// this is a workaround, so that no extra timer is needed
		maintimer = RTC_GetTicks();
		
		if(player.health <= 50)
		{
			// health is low, warn player
			if(contrast > 10 || contrast < -10)
			{
				contradd *= -1;
			}
			contrast += contradd;
			set_contrast(168 + contrast);
		}
		
		// remove status every 100 * 100 ms = 10 sec, IIRC
		if(statustimer++ == 100)
		{
			statustimer = 0;
			status = NULL;
		}
		
		// a hit is shown with a backlight flash
		if(BacklightIsOn() && statustimer % 5 == 0)
		{
			// turn backlight off after 100 ms * 5 = 500 ms
			BacklightOff();
		}
	}
	
	// check keyboard input
	move();
	if(output != 0) // output of move()
	{
		unsigned int time;
		oldtime = RTC_GetTicks(); // init FPS counter
		clear_vram(); // clear display
		cast(); // render image
		
		drawgun(); // show gun
		
		if(output == 2) // if the player moved fw/bw, the gun has to move
		{
			if(player.gunpos > 3 || player.gunpos < -3)
			{
				// move gun from top to bottom and vice-versa
				if(player.gunpos > 3)
				player.gunpos = 3;
				
				gundir *= -1;
			}
			player.gunpos += gundir;
		}	
		
		// print FPS
		sprintf(&FPS, "fps:%2.2f", 1 / fps);
		PrintMini(0, 0, &FPS, MINI_OR);
		
		// print health
		sprintf(&LIVE, "health:%4d", player.health);
		PrintMini(80, 0, &LIVE, MINI_OR);
		
		// and a status message, if available
		if(status != NULL)PrintMini(0, 58, status, MINI_OR);
		
		// update screen
		display_vram();
		if(player.health <= 0)
		{
			// game over
			exit = TRUE;
		}
		// set kind of move (output from move()) to 0 again
		output = 0;
		
		// re-calculate FPS
		fps = (((RTC_GetTicks() * 15.625 - oldtime * 15.625)) / 1000);
	}
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	int c;
	// get the pointer to vram
	vram = Disp_GetVRAMPtr();
	
	// if we ever got a new calc model, this would save us (hopefully)
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
	
	// make it possible to start the game again after [Menu]
	APP_EnableRestart();

	// generate some tables for speed
	table();
	// seed rand()
	seedrandom();
	
	// if we want to have enemies, allocate and create them
	if(ENEMYCNT)
	{
		sprites = (struct st_sprite *) malloc(ENEMYCNT * sizeof(struct st_sprite));
		// these are debug checks; there should be enough memory
		if(sprites == NULL)error();
	}
	
	// spritecnt holds the number of all sprites; enemies, items and whatever else will come
	spritecnt = ENEMYCNT;
	
	// set every enemy into the map
	for(c = 0; c < spritecnt; c++)
	{
		kisetpos(&sprites[c].x, &sprites[c].y);
		sprites[c].texture.ptr = &enemy;
		sprites[c].texture.width = 16;
		sprites[c].texture.height = 32;
		sprites[c].type = TYPE_ENEMY;
		sprites[c].effect = 50;
	}
	
	// create a random maze
	maze();
	
	// init the player's values
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
	
	// this timer handles the enemie's movement. KI is AI in German, I didn't want to rewrite everything :)
	Timer_Install(8, &timer, KISPEED);
	Timer_Start(8);
	
	exit = FALSE;
	
	// main loop
	while(exit == FALSE)
	{
		main();
		// if player won
		if((int)player.x == MAPSIZE - 1 && (int)player.y == MAPSIZE - 1)break;
	}
	
	// kill all timers, set contrast to default
	Timer_Uninstall(8);
	set_contrast(168);
	
	// did he/she loose
	if(player.health > 0 && exit == FALSE)
	{
		clear_vram();
	
		locate(1, 1);
		Print("You found the exit!");
		
		display_vram();
		Sleep(1000);
	}
	// free memory to avoid system errors
	free(sprites);
	
	// clear keyboard buffer, otherwise you could see the cursor move after exit
	Keyboard_ClrBuffer();
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{return INIT_ADDIN_APPLICATION(isAppli, OptionNum);}
#pragma section
