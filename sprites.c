#include "global.h"
#include "sprites.h"

const int wall[2][16][16] = {
{
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
},
{
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 1 , 0 , 1 },
	{ 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
}
};

const int door[16][16] = {
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
};

const int pack[8][8] = {
	{ 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 },
	{ 1 , 1 , 1 , 2 , 2 , 1 , 1 , 1 },
	{ 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
	{ 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
	{ 1 , 1 , 1 , 2 , 2 , 1 , 1 , 1 },
	{ 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 },
	{ 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 }
};

const int enemy[32][16] = {
	{ 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 2 , 2 , 2 , 1 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 1 , 0 , 0 },
	{ 0 , 1 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 1 , 0 , 0 },
	{ 0 , 1 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 1 , 0 },
	{ 0 , 1 , 2 , 1 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 1 , 2 , 1 , 0 },
	{ 0 , 1 , 2 , 1 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 1 , 2 , 1 , 0 },
	{ 1 , 2 , 2 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 2 , 1 , 0 },
	{ 1 , 2 , 2 , 1 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 1 , 2 , 2 , 1 },
	{ 1 , 2 , 1 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 1 , 2 , 1 },
	{ 1 , 2 , 1 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 1 , 2 , 1 },
	{ 1 , 2 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 2 , 1 },
	{ 1 , 2 , 2 , 1 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 2 , 2 , 1 },
	{ 1 , 2 , 2 , 1 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 1 , 2 , 2 , 1 },
	{ 0 , 1 , 1 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 1 , 1 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 1 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 1 , 0 , 0 , 1 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 1 , 0 , 0 , 1 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 0 , 1 , 2 , 2 , 2 , 1 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 0 }
};

const int floor[16][16] = {
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
};

const int ceiling[16][16] = {
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
	{ 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 },
	{ 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
};

const int gun[22][21] = {
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 1 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 2 , 1 , 2 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 1 , 2 , 1 , 1 , 2 , 1 , 1 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 2 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 1 , 2 , 1 , 2 , 2 , 1 , 2 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 1 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 2 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 1 , 2 , 2 , 2 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 1 , 1 , 1 , 2 , 1 , 1 , 1 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 1 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 1 , 2 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 1 , 0 },
	{ 0 , 1 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 1 , 1 , 1 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 1 , 0 },
	{ 0 , 1 , 2 , 2 , 2 , 1 , 2 , 1 , 2 , 1 , 1 , 2 , 1 , 2 , 1 , 2 , 2 , 2 , 2 , 1 , 0 },
	{ 1 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 1 , 1 , 1 , 2 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 1 }
};

const int knife[22][21] = {
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 1 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 1 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 1 , 1 , 2 , 2 , 2 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 1 , 2 , 1 , 1 , 2 , 1 , 1 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 2 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 2 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 1 , 2 , 1 , 2 , 2 , 1 , 2 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 1 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 2 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 1 , 2 , 2 , 2 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 1 , 1 , 1 , 2 , 1 , 1 , 1 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 1 , 0 , 0 },
	{ 0 , 0 , 1 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 1 , 2 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 1 , 0 },
	{ 0 , 1 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 1 , 1 , 1 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 1 , 0 },
	{ 0 , 1 , 2 , 2 , 2 , 1 , 2 , 1 , 2 , 1 , 1 , 2 , 1 , 2 , 1 , 2 , 2 , 2 , 2 , 1 , 0 },
	{ 1 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 1 , 1 , 1 , 1 , 2 , 1 , 2 , 1 , 2 , 2 , 2 , 1 , 1 }
};

const char packmsg[11] = "Found pack";
const char hitmsg[19] = "You were attacked!";