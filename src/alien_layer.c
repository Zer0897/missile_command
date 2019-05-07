#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"

static void add_missile(Coord target);
static void deploy_missiles();


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}


void update_alien() {
    deploy_missiles();
    update_animations(&ALIEN_CANVAS);
    wrefresh(ALIEN_CANVAS.window);
}


static void deploy_missiles() {
    static clock_t last_deploy;
    static int missile_count = 5;
    static double rate_limit = CLOCKS_PER_SEC;

    Coord target = {.x = COLS / 2, .y = LINES / 2};

    if ((double) (clock() - last_deploy) >= rate_limit && missile_count) {
        add_missile(target);
        last_deploy = clock();
        --missile_count;
    }
}


static void add_missile(Coord target) {
    Coord start = { .x = rand() % COLS, .y = 0 };
    Sprite missile = {
        .path.current = start,
        .path.beg = start,
        .path.end = target,
        .view = "\u2500",
        .path.speed = 4,
        .path.start_time = clock(),
        .active = true,
    };
    add_sprite(&ALIEN_CANVAS, missile);
}
