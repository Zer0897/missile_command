#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}


void update_alien(int i) {
	Sprite* sprite = &ALIEN_CANVAS.sprites[i];

    static clock_t last_deploy;
    static int missile_count = 5;
    static double rate_limit = CLOCKS_PER_SEC;

    bool ready = ((double) (clock() - last_deploy) >= rate_limit);
    if (sprite->active || !ready || !missile_count) {
        return;
    }

    Coord target = {.x = COLS / 2, .y = LINES / 2};
    Coord start = { .x = rand() % COLS, .y = 0 };

    set_animation(sprite, &start, &target);
    sprite->view = ACS_DIAMOND;
    sprite->active = true;

    last_deploy = clock();
    --missile_count;
}
