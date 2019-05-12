#ifndef DISPLAY_LAYER_H
#define DISPLAY_LAYER_H

#include <ncurses.h>

WINDOW *DISPLAY;


void init_display();
void update_display();
void add_score(int);
void destroy_building();
int get_round();
void increment_round();

#endif