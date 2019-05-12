#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"
#include "collision_layer.h"
#include "display_layer.h"
#include "mainloop.h"

// The total missile for a round.
static const int total_missiles = 30;
// The number of missile left in the alien arsenal.
static int missile_count = total_missiles;
// The number of missile that have been either
// destroyed or hit the ground.
static int hit_count = 0;


static void split_alien(Sprite*);

// Arsenal is depleted and there are no more active missiles.
bool is_alien_done() {
    return (!missile_count && hit_count >= total_missiles);
}


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}

void reset_alien() {
    missile_count = total_missiles;
    hit_count = 0;
}


void update_alien(int i) {
    static long last_deploy;
    static long last_split;
    int rate_limit = 2 - log10((double) get_round());
    bool ready = ((get_nanotime() - last_deploy) / SECOND >= rate_limit);

	Sprite* sprite = &ALIEN_CANVAS.sprites[i];
    if (sprite->alive) {
        if (check_hitbox(&COLLISION_CANVAS, &sprite->path.current, 1)) {
            sprite->alive = false;
            clear_sprite(sprite, 160);
            add_score(100);
            ++hit_count;
        } else if (is_animation_done(sprite)) {
            destroy_building();
            ++hit_count;

        } else if (get_nanotime() - last_split > SECOND * 20) {
            split_alien(sprite);
            last_split = get_nanotime();
        }
    } else if (ready && missile_count) {
        Coord start = { .x = rand() % COLS, .y = 0 };
        Coord target = { .x = rand() % COLS, .y = LINES };

        set_animation(sprite, &start, &target, 7 + 2 * log10(get_round()));
        sprite->view = ACS_DIAMOND;

        last_deploy = get_nanotime();
        --missile_count;
    }
}


static void split_alien(Sprite* sprite) {
    sprite->alive = false;
    clear_sprite(sprite, 5);
    --hit_count;

    int currx = sprite->path.current.x;
    Coord targets[] = {
        { .x = rand() % currx, .y = LINES },
        { .x = currx + rand() % (COLS - currx), .y = LINES }
    };

    int count = 0;
    for (int i = 0; i < 120; i++) {
        Sprite* next = &ALIEN_CANVAS.sprites[i];
        if (!next->alive) {
            set_animation(next, &sprite->path.current, &targets[count], sprite->path.speed);
            next->view = sprite->view;
            ++count;
        }

        if (count > 1)
            break;
    }
}