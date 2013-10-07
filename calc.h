#ifndef _CALC_H_
#define _CALC_H_

#define Abs(x) ((x < 0)? -x : x)
#define degtorad(x) (x * 0.0174532925)
#define sgn(x) ((int)((x > 0) ? 1 :  (x == 0)?0:-1))

#define GetBit(x, y) (x & (1 << y)) != 0
#define SetBit(x, y) (x |= (1 << y))
#define ClearBit(x, y) (x &= ~(1 << y))

#define crand() random()

void seedrandom(void);
unsigned int random(void);
void table(void);
void fill(unsigned int *, unsigned int, unsigned int);

extern int TDist[64];

#endif
