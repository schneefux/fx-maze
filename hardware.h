#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#define IsEmulator !( *(int*)0x80000300)

struct st_port {
             union {
                   unsigned char BYTE;
                   struct{
                          unsigned char B7:1;
                          unsigned char B6:1;
                          unsigned char B5:1;
                          unsigned char B4:1;
                          unsigned char B3:1;
                          unsigned char B2:1;
                          unsigned char B1:1;
                          unsigned char B0:1; 
                          }      BIT;
                   }            DR; 
};

void BacklightOn(void);
void BacklightOff(void);
void BacklightChange(void);
int BacklightIsOn(void);

void set_contrast(int);

void display_vram(void);
void clear_vram(void);

short *APP_EnableRestart(void);

int getCalc(void);
#define UNKNOWN 0
#define fx9860G 1
#define fx9860G_SLIM 2
#define fx9860GII_2 3
#define fx9860GII 4

extern char *vram;

#endif