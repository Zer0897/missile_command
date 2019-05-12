#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"
#include "collision_layer.h"
#include "ui_layer.h"
#include "main.h"

// The total missile for a round.
// Split missiles are not counted.
static const int total_missiles = 25;

// The number of missile left in the alien arsenal.
static int missile_count = total_missiles;

// The number of missile that have been either
// destroyed or hit the ground.
static int hit_count = 0;


static void split_alien(Sprite*);

// Arsenal is depleted and there are no more active missiles.
bool is_alien_done() {
    return (!missile_count && hit_count >= total_missiles); // Missiles may count twice when split.
}


void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}

void reset_alien() { missile_count = total_missiles;
    hit_count = 0;
}


void update_alien(int i) {
    static long last_deploy;
    static long last_split;

    double difficulty_factor = 1 + log10((double) get_round());
    double rate_limit = 0.5 + 1 / difficulty_factor;
    double animation_speed = 8 + 2 * difficulty_factor;
    bool ready = ((get_time() - last_deploy) / SECOND >= rate_limit);

	Sprite* sprite = &ALIEN_CANVAS.sprites[i];
    if (sprite->alive) {

        if (check_hitbox(&COLLISION_CANVAS, &sprite->path.current, 1)) {
            sprite->alive = false;
            clear_sprite(&ALIEN_CANVAS, sprite); add_score(100);
            ++hit_count;

        } else if (is_animation_done(sprite)) {
            destroy_building();
            ++hit_count;

        } else if (get_time() - last_split > SECOND * 20) {
            if (get_round() > 1) {
                split_alien(sprite);
            }
            last_split = get_time();
        }
    } else if (ready && missile_count) {
        Coord start = { .x = rand() % COLS, .y = 0 };
        Coord target = { .x = rand() % COLS, .y = LINES };

        set_animation(sprite, &start, &target, 8 + 2 * log10(get_round()));
        sprite->view = ACS_DIAMOND;
        last_deploy = get_time();
        --missile_count;
    }
}


static void split_alien(Sprite* sprite) {
    sprite->alive = false;
    clear_sprite(&ALIEN_CANVAS, sprite);
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