#include <ncurses.h>
#include "collision_layer.h"
#include "animate.h"



void init_collision() {
    COLLISION_CANVAS.window = newwin(0, 0, 0 , 0);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    wattron(COLLISION_CANVAS.window, COLOR_PAIR(4));
}

void update_collision(int i) {
    Sprite* sprite = &COLLISION_CANVAS.sprites[i];

}


void collide_input_defense(Coord* point) {
    static int size = 4;


    Coord endpoints[] = {
        { .y = point->y + size, .x = point->x }, // top
        { .y = point->y - size, .x = point->x }, // bottom
        { .y = point->y, .x = point->x - size * 2 }, // left
        { .y = point->y, .x = point->x + size * 2 }, // right
        { .y = point->y - size, .x = point->x + size }, // top right
        { .y = point->y - size, .x = point->x - size }, // top left
        { .y = point->y + size, .x = point->x - size }, // bottom left
        { .y = point->y + size, .x = point->x + size } // bottom right
    };

    for (int endpoint_count = 0; endpoint_count < 8; endpoint_count++) {
        for (int i = 0; i < 120; i++) {
            Sprite* flare = &COLLISION_CANVAS.sprites[i];
            if (!flare->active) {
                set_animation(flare, point, &endpoints[endpoint_count]);
                flare->view = ACS_BLOCK;
                flare->path.speed = 10;
                flare->active = true;
                break;
            }
        }
    }
}