#ifndef _MAPGEN_H_
#define _MAPGEN_H_

union st_field
{
	int byte;
	struct
	{
		int west;
		int east;
		int north;
		int south;
	}side;
};

void maze(void);

#endif