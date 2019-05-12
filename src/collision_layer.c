#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "collision_layer.h"
#include "alien_layer.h"
#include "animate.h"
#include "main.h"




void init_collision() {
    COLLISION_CANVAS.window = newwin(0, 0, 0 , 0);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    wattron(COLLISION_CANVAS.window, COLOR_PAIR(4));
}


void collide_input_defense(Coord* point) {
    Coord endpoints[8];
    get_box(point, 4, endpoints);
    for (int endpoint_count = 0; endpoint_count < 8; endpoint_count++) {
        for (int i = 0; i < 120; i++) {
            Sprite* flare = &COLLISION_CANVAS.sprites[i];
            if (!flare->alive) {
                set_animation(flare, point, &endpoints[endpoint_count], 10);
                flare->view = '*';
                flare->keep_alive = SECOND * 1.2;
                break;
            }
        }
    }
}


bool check_collision_alien(Coord* point) {
    char c = mvwinch(COLLISION_CANVAS.window, point->y, point->x);
    return (c == '*');
}

/*
 * Get the surrounding points in an area `size`, starting from `point`. Place
 * them in the given array `out`.
 *
 * Params:
 *  point : Coord*
 *      The starting center of the box.
 *  size : int
 *      Size of box to get.
 *  Out : Coord*
 *      A pointer to an array with 8 Coord positions. All sides and corners
 *      of the box are places in this array.
*/
void get_box(Coord* point, int size, Coord out[8]) {
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


bool check_hitbox(Canvas* canvas, Coord* point, int size) {
    if (size == 0) {
        return false;
    }

    Coord box[8];
    get_box(point, size, &box);
    for (int i = 0; i < 8; i++) {
        if (has_object(canvas, &box[i])) {
            return true;
        }
    }

    return check_hitbox(canvas, point, size - 1);

}