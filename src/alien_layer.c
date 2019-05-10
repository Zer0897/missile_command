#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"
#include "collision_layer.h"



void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}


void update_alien(int i) {
	Sprite* sprite = &ALIEN_CANVAS.sprites[i];

    static long last_deploy;
    static int missile_count = 100;
    static int rate_limit = 3;

    bool ready = ((get_nanotime() - last_deploy) / SECOND >= rate_limit);

    if (sprite->alive) {
        Coord hitbox[8];

        get_box(&sprite->path.current, 1, &hitbox);
        for (int i = 0; i < 8; i++) {
            if (check_collision_alien(&hitbox[i])) {
            // if (has_object(&COLLISION_CANVAS, &hitbox[i])) {
                sprite->alive = false;
                clear_sprite(sprite, 160);
                // getch();
                break;
            }
        }
    }

    if (!sprite->alive && ready && missile_count) {
        Coord start = { .x = rand() % COLS, .y = 0 };
        Coord target = { .x = rand() % COLS, .y = LINES };

        set_animation(sprite, &start, &target, 10);
        sprite->view = ACS_DIAMOND;

        last_deploy = get_nanotime();
        --missile_count;
    }
}
