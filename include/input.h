#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include "animate.h"

int get_clickpos(WINDOW*, Coord*);
int get_mousepos(WINDOW*, Coord*);

#endif