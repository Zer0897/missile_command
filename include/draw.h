#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>
#include "coord.h"

typedef struct {
    WINDOW* window;
    Sprite* sprites;
    size_t sprite_count;
    size_t sprite_max;
} Canvas;


typedef struct {
    Coord coord;
    int acs_flag;
    Vector path;
} Sprite;


enum CanvasFlag { COMMANDER, CANVAS_COUNT };

Canvas* get_canvas(enum CanvasFlag);
void init_canvases();
void update_canvases();


#endif
