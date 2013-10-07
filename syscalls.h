#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

char* Disp_GetVRAMPtr(void);

int GetKey(unsigned int *);
void locate(int, int);
void Print(const unsigned char *);
int Timer_Install(int, void (*)(void), int);
int Timer_Uninstall(int);
int Timer_Start(int);
int itoa( int, unsigned char*, int);
void PrintMini(int, int, const unsigned char *, int);
int RTC_Elapsed_ms(int, int);
void Keyboard_ClrBuffer(void);
int RTC_Elapsed_ms(int, int);
int GlibGetOSVersionInfo(char *, char *, short *, short *);
int Keyboard_PRGM_GetKey(uchar *);

#define MINI_OVER 0
#define MINI_OR 1
#define MINI_REV 2
#define MINI_REVOR 3

#endif