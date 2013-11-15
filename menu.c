#include "global.h"
#include "menu.h"
#include "key.h"
#include "ki.h"
#include "syscalls.h"
#include "draw.h"

#include "stdio.h"

// in-game menu

void openmenu()
{
	uchar text[30];
	int choose = 0;
	static const char arrow = 0x13;
	
	Timer_Uninstall(8);
	
	while(keydown(KEY_CTRL_MENU)){keyupdate();}
	while(1)
	{
		PopUpWin(6);
		
		sprintf(&text, "show map");
		locatePrintMini(5,3, &text);
		
		if(drawfloor == TRUE)
		{
			sprintf(&text, "disable floor and ceiling");
		}
		else
		{
			sprintf(&text, "enable floor and ceiling");
		}
	
		locatePrintMini(5,4, &text);
		
		if(drawtex == TRUE)
		{
			sprintf(&text, "disable texture");
		}
		else
		{
			sprintf(&text, "enable texture");
		}
	
		locatePrintMini(5,5, &text);
		
		if(drawheight == TRUE)
		{
			sprintf(&text, "disable height difference");
		}
		else
		{
			sprintf(&text, "enable height difference");
		}
		
		locatePrintMini(5,6, &text);

		if(demo == TRUE)
		{
			sprintf(&text, "disable demo mode");
		}
		else
		{
			sprintf(&text, "enable demo mode");
		}
	
		locatePrintMini(5,7, &text);
		
		sprintf(&text, "exit game");
		locatePrintMini(5,8, &text);
		
		locatePrintMini(4,3+choose, &arrow);
		
		while(keydown(KEY_CTRL_UP) || keydown(KEY_CTRL_DOWN) || keydown(KEY_CTRL_EXE) || keydown(KEY_CTRL_MENU)){keyupdate();}
		
		display_vram();
		
		while(!keydown(KEY_CTRL_UP) && !keydown(KEY_CTRL_DOWN) && !keydown(KEY_CTRL_EXE) && !keydown(KEY_CTRL_MENU)){keyupdate();}
		if(keydown(KEY_CTRL_UP))
		{
			choose--;
			if(choose == -1)
			choose = 0;
		}
		if(keydown(KEY_CTRL_DOWN))
		{
			choose++;
			if(choose == 6)
			choose = 5;
		}
		if(keydown(KEY_CTRL_MENU))
		{
			while(keydown(KEY_CTRL_MENU)){keyupdate();}
			Timer_Install(8, &timer, KISPEED);
			Timer_Start(8);
			return;
		}
		if(keydown(KEY_CTRL_EXE))
		{
			switch(choose)
			{
				case 0:
					while(keydown(KEY_CTRL_EXE)){keyupdate();}
					showmap();
					break;
				case 1:
					drawfloor = (drawfloor == TRUE)?FALSE:TRUE;
					break;
				case 2:
					drawtex = (drawtex == TRUE)?FALSE:TRUE;
					break;
				case 3:
					drawheight = (drawheight == TRUE)?FALSE:TRUE;
					break;
				case 4:
					if(demo == TRUE)
					{
						demo = FALSE;
					}
					else
					{
						demo = TRUE;
					}
					break;
				case 5:
					exit = TRUE;
					return;
			}
		}
	}
}
