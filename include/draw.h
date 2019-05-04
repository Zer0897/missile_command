#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>
#include "coord.h"


typedef struct {
    WINDOW *window;
    Coord coord;
    int acs_flag;
} Sprite;

Sprite SPRITES[1];

enum SpriteFlag { CROSSHAIR, MAX_SPRITES };

Sprite* get_sprite(enum SpriteFlag);
void init_sprites();
void update_sprites();
void __update_crosshair();
void __init_crosshair();

#endif
