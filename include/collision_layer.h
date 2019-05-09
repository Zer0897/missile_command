#ifndef COLLISION_LAYER_H
#define COLLISION_LAYER_H

#include <ncurses.h>
#include "canvas.h"


Canvas COLLISION_CANVAS;

void init_collision();
void update_collision(int);
void collide_input_defense(Coord*);
bool check_collision_defense(Coord*);


#endif