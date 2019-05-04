#ifndef ANIMATE_H
#define ANIMATE_H

#include <time.h>


typedef struct {
	int x;
	int y;
} Coord;


typedef struct {
	Coord beg;
	Coord current;
	Coord end;
	double speed;
	time_t start_time;
} Vector;


void lerp(Vector*);


#endif