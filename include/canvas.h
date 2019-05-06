#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>
#include "animate.h"



typedef struct {
    char view;
    Vector path;
    bool active;
} Sprite;


typedef struct {
    WINDOW* window;
    Sprite sprites[120];
} Canvas;


Canvas INPUT_CANVAS;


void add_sprite(Canvas*, Sprite);

#endif
