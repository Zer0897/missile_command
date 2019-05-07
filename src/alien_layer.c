#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));

    Coord target = {.x = COLS / 2, .y = LINES / 2};
    Coord target2 = {.x = COLS / 2, .y = LINES };
    add_missile(target);
    // add_missile(target2);
    // add_missile(target);
    // add_missile(target);
    // add_missile(target);
}


void update_alien() {
    update_animations(&ALIEN_CANVAS);
    wrefresh(ALIEN_CANVAS.window);

}


void add_missile(Coord target) {
    Coord start = { .x = rand() % COLS, .y = 0 };
    Sprite missile = {
        .path.current = start,
        .path.beg = start,
        .path.end = target,
        .view = 'v',
        .path.speed = 4,
        .path.start_time = clock(),
        .active = true,
    };
    add_sprite(&ALIEN_CANVAS, missile);
}
