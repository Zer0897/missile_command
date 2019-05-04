#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>
#include "coord.h"

typedef struct {
    WINDOW* window;
    Sprite* sprites;
    size_t sprite_count;
} Canvas;

typedef struct {
    Coord coord;
    int acs_flag;
    Vector path;
} Sprite;


enum CanvasFlag { CROSSHAIR, MAX_SPRITES };

Canvas* get_canvas(enum CanvasFlag);
void init_canvas();
void update_canvas();
void __update_crosshair();
void __init_crosshair();

#endif
