#ifndef DISPLAY_LAYER_H
#define DISPLAY_LAYER_H

#include <ncurses.h>

WINDOW
    *DISPLAY, *SCORE;


void init_display();
void update_display();
void add_score(int);
int get_round();
void increment_round();

#endif