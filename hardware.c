// Thanks to SimonLothar, cfxm and all the other hackers!

#include "global.h"
#include "hardware.h"

// here are some functions for direct hardware access
// they are splitted to support different calculators

char *vram, *vram2;

// backlight funcions: on, off, switch, check
// if it's unknown hardware we should do nothing
void BacklightOn()
{
	if(!IsEmulator)
	{
		switch(getCalc())
		{
			case UNKNOWN: return;
			case fx9860G_SLIM: (*(volatile struct st_port *)0xA4000126).DR.BIT.B5 = 1; break;
			case fx9860GII: (*(volatile struct st_port *)0xA400012C).DR.BIT.B7 = 1; break;
			case fx9860GII_2: (*(volatile struct st_port *)0xA4050138).DR.BIT.B4 = 1; break;
		}
	}
}

void BacklightOff()
{
	if(!IsEmulator)
	{
		switch(getCalc())
		{
			case UNKNOWN: return;
			case fx9860G_SLIM: (*(volatile struct st_port *)0xA4000126).DR.BIT.B5 = 0; break;
			case fx9860GII: (*(volatile struct st_port *)0xA400012C).DR.BIT.B7 = 0; break;
			case fx9860GII_2: (*(volatile struct st_port *)0xA4050138).DR.BIT.B4 = 0; break;
		}
	}
}

void BacklightChange()
{
	if(!IsEmulator)
	{
		switch(getCalc())
		{
			case UNKNOWN: return;
			case fx9860G_SLIM: (*(volatile struct st_port *)0xA4000126).DR.BIT.B5 = (*(volatile struct st_port *)0xA4000126).DR.BIT.B5 == 0; break;
			case fx9860GII: (*(volatile struct st_port *)0xA400012C).DR.BIT.B7 = (*(volatile struct st_port *)0xA400012C).DR.BIT.B7 == 0; break;
			case fx9860GII_2: (*(volatile struct st_port *)0xA4050138).DR.BIT.B4 = (*(volatile struct st_port *)0xA4050138).DR.BIT.B4 == 0; break;
		}
	}
}

int BacklightIsOn()
{
	if(!IsEmulator)
	{
		switch(getCalc())
		{
			case UNKNOWN: return 0;
			case fx9860G_SLIM: return (*(volatile struct st_port *)0xA4000126).DR.BIT.B5; break;
			case fx9860GII: return (*(volatile struct st_port *)0xA400012C).DR.BIT.B7; break;
			case fx9860GII_2: return (*(volatile struct st_port *)0xA4050138).DR.BIT.B4; break;
		}
	}
}

// change contrast only for known calcs
void set_contrast(int contrast)
{
	if(!getCalc() == UNKNOWN && !IsEmulator)
	{
		char *LCD_register_selector = (char*)0xB4000000, *LCD_data_register = (char*)0xB4010000;
		*LCD_register_selector = 6;
		*LCD_data_register = contrast;
	}
}

// update the display, if secure; otherwise use syscalls (sloooow!)
void display_vram()
{
	if(getCalc() == UNKNOWN && !IsEmulator)
	{
		Bdisp_PutDisp_DD();
	}
	else
	{
		char *LCD_register_selector = (char*)0xB4000000, *LCD_data_register = (char*)0xB4010000, *mvram;
		int i, j;
		mvram = vram;
		for(i=0 ; i<64 ; i++)
		{
			*LCD_register_selector = 4;
			*LCD_data_register = i|192;
			*LCD_register_selector = 4;
			*LCD_data_register = 0;
			*LCD_register_selector = 7;
			for(j=0 ; j<16 ; j++) *LCD_data_register = *mvram++;
		}
	}
}

// clear video ram
void clear_vram()
{
	int i, end;
	int *pointer_long, mvram;
	char *pointer_byte;
	mvram = (int)vram;
	end = 4-mvram&3;
	pointer_byte = (char*)mvram;
	for(i=0 ; i<end ; i++) pointer_byte[i] = 0;
	pointer_long = (int*) (mvram+end);
	for(i=0 ; i<255 ; i++) pointer_long[i] = 0;
	pointer_byte += 1020+end;
	end = mvram&3;
	for(i=0 ; i<end ; i++) pointer_byte[i] = 0;
}

// if possible, let it restart after going to the main menu
short*APP_EnableRestart()
{
	if(getCalc() != UNKNOWN && !IsEmulator)
	{
		unsigned int ea;
		unsigned int j;
		short*pEnableRestartFlag;
		ea = *(unsigned int*)0x8001007C;
		ea += 0x0490*4;
		if ( ea < 0x8001007C ) return 0;
		if ( ea > 0x81000000 ) return 0;
		ea = *(unsigned int*)( ea );
		if ( ea < 0x8001007C ) return 0;
		if ( ea > 0x81000000 ) return 0;
		j = *(unsigned char*)( ea + 1 );
		j *= 4;
		ea = ( ea + j + 4 ) & 0xFFFFFFFC;
		if ( ea < 0x8001007C ) return 0;
		if ( ea > 0x81000000 ) return 0;
		pEnableRestartFlag = (short*)(*( unsigned int*)( ea ) + 8 );
		if ( ( (unsigned int)pEnableRestartFlag & 0xFF000000 ) != 0x88000000 ) return 0;
		if ( pEnableRestartFlag ) *pEnableRestartFlag = 1;
		return pEnableRestartFlag;
	}
	return NULL;
}

// return the model
int getCalc(void)
{
	static int hardware = UNKNOWN;
	if(hardware == UNKNOWN)
	{
		char v1, v2;
		short v3, v4;
	
		// check for calculator hardware type
		if ( *(unsigned int*)0x80000300 == 0x80005D7C ){
			if ( *(unsigned char*)0xA4000128 & 0x08 ){
				hardware = fx9860G;
			}
			else{
				hardware = fx9860G_SLIM;
			}
		}
		else {
			GlibGetOSVersionInfo( &v1, &v2, &v3, &v4 );
			if ( ( v1 == 2 ) && ( v2 == 2 ) ){
				hardware = fx9860GII_2;
			}
			else if ( ( *(unsigned int*)0x80000304 & 0x00FF0000 ) == 0x00AA0000 ){
			// GII
				hardware = fx9860GII;
			}
			else if ( ( *(unsigned int*)0x80000304 & 0x00FF0000 ) == 0x00550000 ){
			// GII (French)
				hardware = fx9860GII;
			}
		}
	}

	return hardware;
}
