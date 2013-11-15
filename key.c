#include "global.h"
#include "key.h"
#include "hardware.h"

// SHA4 only
static const unsigned short* keyboard_register = (unsigned short*)0xA44B0000;
static unsigned short lastkey[8];

// syscall getkey (non-blocking)
int PRGM_GetKey()
{
	unsigned char buffer[12];
	Keyboard_PRGM_GetKey( buffer );
	return (buffer[1] & 0x0F) * 10 + ((buffer[2] & 0xF0)  >> 4);
}

// do I have to explain this?
static void delay()
{
	unsigned int i;
	for(i=0 ; i<5 ; i++);
}

// fast function for SH3
static unsigned char CheckKeyRow(int code)
{
	unsigned int result=0;
	short*PORTB_CTRL=(void*)0xA4000102;
	short*PORTM_CTRL=(void*)0xA4000118;
	char*PORTB=(void*)0xA4000122;
	char*PORTM=(void*)0xA4000138;
	char*PORTA=(void*)0xA4000120;
	short smask;
	char cmask;
	unsigned char column, row;

	column = code>>4;
	row = code &0x0F;

	smask = 0x0003 << (( row %8)*2);
	cmask = ~( 1 << ( row %8) );
	if(row <8)
	{
		*PORTB_CTRL = 0xAAAA ^ smask;
		*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
		delay();
		*PORTB = cmask;
		*PORTM = (*PORTM & 0xF0 ) | 0x0F;
	}
	else
	{
		*PORTB_CTRL = 0xAAAA;
		*PORTM_CTRL = ((*PORTM_CTRL & 0xFF00 ) | 0x00AA)  ^ smask;
		delay();
		*PORTB = 0xFF;
		*PORTM = (*PORTM & 0xF0 ) | cmask;
	}
	delay();
	result = (~(*PORTA))>>column & 1;
	delay();
	*PORTB_CTRL = 0xAAAA;
	*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x00AA;
	delay();
	*PORTB_CTRL = 0x5555;
	*PORTM_CTRL = (*PORTM_CTRL & 0xFF00 ) | 0x0055;
	delay();
	
	return result;
}

// update key buffer
void keyupdate()
 {
 	if(getCalc() == fx9860GII_2)
 	{
		memcpy(lastkey, keyboard_register, sizeof(unsigned short) << 3);
    	}
}
 
// check for keypress, depending on the calculator
int keydown(int code)
{
	if(getCalc() != UNKNOWN)
	{
		if(getCalc() == fx9860GII_2)
		{
			unsigned char row = code%10;
			
			return (0 != (lastkey[row >> 1] & 1 << code / 10 - 1 + ((row & 1) << 3)));
		}
		else
		{
			return CheckKeyRow((code % 10) + ((code / 10 - 1) << 4));
		}
	}
	else
	{
		if(IsEmulator)
		{
			return CheckKeyRow((code % 10) + ((code / 10 - 1) << 4));
		}
		else
		{
			return PRGM_GetKey() == code;
		}
	}
}
