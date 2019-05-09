#include <stdlib.h>
#include <ncurses.h>
#include "collision_layer.h"
#include "animate.h"



static void get_box(Coord* point, int size, Coord* out) {
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
    for (int i = 0; i < 8; i++) {
        out[i] = endpoints[i];
    }

}

void init_collision() {
    COLLISION_CANVAS.window = newwin(0, 0, 0 , 0);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    wattron(COLLISION_CANVAS.window, COLOR_PAIR(4));
}

void update_collision(int i) {
    Sprite* sprite = &COLLISION_CANVAS.sprites[i];

    if (!sprite->active && has_object(&COLLISION_CANVAS, &sprite->path.current)) {
        clear_sprite(sprite, 8);
    }
}


void collide_input_defense(Coord* point) {
    Coord endpoints[8];
    get_box(point, 5, endpoints);

    for (int endpoint_count = 0; endpoint_count < 8; endpoint_count++) {
        for (int i = 0; i < 120; i++) {
            Sprite* flare = &COLLISION_CANVAS.sprites[i];
            if (!flare->active) {
                set_animation(flare, point, &endpoints[endpoint_count]);
                flare->view = ACS_BLOCK;
                flare->path.speed = 10;
                flare->active = 3;
                break;
            }
        }
    }
}


bool check_collision_defense(Coord* point) {
    return (mvwinch(COLLISION_CANVAS.window, point->y, point->x) == ACS_BLOCK);
}
