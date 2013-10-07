#ifndef _DRAW_H_
#define _DRAW_H_

void locatePrintMini(int, int, const unsigned char *);

#define pixel(x,y) (*(vram +  (y << 4) + (x >> 3))) |= (128 >> (x & 7))
#define clrpixel(x,y) (*(vram +  (y << 4) + (x >> 3))) &= ~(128>>(x & 7))

void vertical(int, int, int, int, int, int, float);

void drawgun(void);
void showmap(void);
void drawgenmap(void);

void horizontal(int, int, int);
void fillbox(int, int, int, int);

extern int drawtex, drawfloor, drawheight;

#endif