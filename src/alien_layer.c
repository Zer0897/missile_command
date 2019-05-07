#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"


static Coord get_startpos() {
    Coord start = { .x = rand() % COLS, .y = 0 };
    return start;
}


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));

    Coord target = {.x = COLS / 2, .y = LINES / 2};
    add_missile(target);
    add_missile(target);
    // add_missile(target);
    // add_missile(target);
    // add_missile(target);
}


void update_alien() {
    update_animations(&ALIEN_CANVAS);
    wrefresh(ALIEN_CANVAS.window);

}


void add_missile(Coord target) {
    Sprite missile;
    Coord start = get_startpos();
    missile.path.current = start;
    missile.path.beg = start;
    missile.path.end = target;
    missile.view = 'v';
    missile.path.speed = 4;
    missile.path.start_time = clock();
    missile.active = true;

    add_sprite(&ALIEN_CANVAS, missile);
}