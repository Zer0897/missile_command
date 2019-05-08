#ifndef ANIMATE_H
#define ANIMATE_H

#include <ncurses.h>
#include "canvas.h"



void lerp(Vector*);
void set_animation(Sprite*, Coord*, Coord*);
void update_animation(Canvas*, Sprite*);
double distance(Coord*, Coord*);
double slope(Coord*, Coord*);
bool cmp_eq(Coord*, Coord*);
bool cmp_gt(Coord*, Coord*);



#endif