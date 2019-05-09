#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "collision_layer.h"
#include "alien_layer.h"
#include "animate.h"
#include "mainloop.h"


static void get_box(Coord*, int, Coord*);
static void check_hitbox(Sprite*);


void init_collision() {
    COLLISION_CANVAS.window = newwin(0, 0, 0 , 0);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    wattron(COLLISION_CANVAS.window, COLOR_PAIR(4));
}

void update_collision(int i) {
    Sprite* sprite = &COLLISION_CANVAS.sprites[i];

    if (sprite->active) {
        check_hitbox(sprite);
    } else if (has_object(&COLLISION_CANVAS, &sprite->path.current)) {
        clear_sprite(sprite, 8);
    }
}


static void check_hitbox(Sprite* sprite) {
    // The easiest way to retrace our steps is to send an invisible
    // sprite in reverse.
    Sprite hitbox = { .path.speed = 1500 };
    set_animation(&hitbox, &sprite->path.current, &sprite->path.beg);

    // We want to give the player a buffer, but
    // checking every single coord around a point is expensive.
    // Instead, we find the perpendicular slope to check the
    // two coords on either side.
    double perp_slope;
    double curr_slope = slope(&hitbox.path.beg, &hitbox.path.end);
    if (isnan(curr_slope)) {
        perp_slope = 0;
    } else if (!curr_slope) {
        perp_slope = NAN;
    } else {
        perp_slope = -1 / curr_slope;
    }

    // Now we send our hitbox sprite down the flare's trail.
    // If it finds an alien, it adds its coord to the `collisions` array.
    int count = 0;
    Coord collisions[15];
    Coord* curr = &hitbox.path.current;
    while (!cmp_eq(curr, &hitbox.path.end) && count < 15) {
        Coord p1 = { .y = curr->y, .x = curr->x + 1 };
        Coord p2 = { .y = curr->y, .x = curr->x - 1 };

        if (!isnan(perp_slope)) {
            p1.y += perp_slope * p1.x;
            p2.y += perp_slope * p2.x;
        }

        if (check_collision_alien(curr)) {
            collisions[count++] = *curr;
        }

        if (check_collision_alien(&p1)) {
            collisions[count++] = p1;
        }

        if (check_collision_alien(&p2)) {
            collisions[count++] = p2;
        }

        lerp(&hitbox.path);
    }

    // There's no good way to get a sprite directly from coordinates,
    // so we have to (expensively) iterate over all of the
    // alien sprites and check if it matches any of the collisions.
    // The good news is `count` will rarely be above 2 or 3, so
    // the worst case scenario is unlikely.
    for (int i = 0; i < 120; i++) {
        if (!count)
            break;

        Sprite* alien = &ALIEN_CANVAS.sprites[i];
        if (!sprite->active)
            continue;

        for (int c = count - 1; c >= 0; c--) {
            if (cmp_eq(&alien->path.current, &collisions[c])) {
                clear_sprite(alien, 10);

                --count;
                break;
            }
        }
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


bool check_collision_alien(Coord* point) {
    return has_object(&ALIEN_CANVAS, point);
}


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