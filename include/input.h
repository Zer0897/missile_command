#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include "animate.h"

int __get_event(WINDOW*, MEVENT*, int);
int __get_eventpos(WINDOW*, Coord*, int);
int get_clickpos(WINDOW*, Coord*);
int get_mousepos(WINDOW*, Coord*);

#endif