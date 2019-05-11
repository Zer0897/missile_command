#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"
#include "collision_layer.h"
#include "display_layer.h"
#include "mainloop.h"


static int missile_count = 5;


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}

void reset_alien() {
    missile_count = 45;
}


void update_alien(int i) {
	Sprite* sprite = &ALIEN_CANVAS.sprites[i];

    static long last_deploy;
    int rate_limit = 1.5;

    bool ready = ((get_nanotime() - last_deploy) / SECOND >= rate_limit);

    if (sprite->alive) {
        Coord hitbox[8];

        get_box(&sprite->path.current, 1, &hitbox);
        for (int i = 0; i < 8; i++) {
            if (check_collision_alien(&hitbox[i])) {
                sprite->alive = false;
                clear_sprite(sprite, 160);

                add_score(10);
                break;
            }
        }
    } else if (!sprite->alive && ready && missile_count) {
        Coord start = { .x = rand() % COLS, .y = 0 };
        Coord target = { .x = rand() % COLS, .y = LINES };

        set_animation(sprite, &start, &target, 8 + get_round());
        sprite->view = ACS_DIAMOND;

        last_deploy = get_nanotime();
        --missile_count;
    } else if (!missile_count) {
        end_round();
    }
}
