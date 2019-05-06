#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>
#include "animate.h"


enum SpriteState { ACTIVE, GARBAGE, DESTROYED };


typedef struct {
    int acs_flag;
    Vector path;
    enum SpriteState state;
} Sprite;


typedef struct {
    WINDOW* window;
    Sprite sprites[120];
} Canvas;


Canvas INPUT_CANVAS;


void init_canvases();
void update_canvases();


#endif
