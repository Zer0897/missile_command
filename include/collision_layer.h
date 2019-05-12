#ifndef COLLISION_LAYER_H
#define COLLISION_LAYER_H

#include <ncurses.h>
#include "canvas.h"


Canvas COLLISION_CANVAS;

void get_box(Coord*, int, Coord[8]);
void init_collision();
void collide_input_defense(Coord*);
bool check_collision_alien(Coord*);
bool check_hitbox(Canvas*, Coord*, int);


#endif