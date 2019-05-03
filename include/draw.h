#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include "coord.h"


typedef struct {
    WINDOW *window;
    Coord coord;
    char* view;
} Sprite;

Sprite SPRITES[1];

enum SpriteFlag { CROSSHAIR, MAX_SPRITES };

Sprite* get_sprite(enum SpriteFlag);
void init_screens();
void update_screens();
void __update_crosshair();
void __init_crosshair();

#endif
