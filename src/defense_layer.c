#include "defense_layer.h"
#include "input_layer.h"
#include "animate.h"
#include "collision_layer.h"


static struct Base* get_launchpoint(Coord*);

void init_defense() {
    DEFENSE_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wattron(DEFENSE_CANVAS.window, COLOR_PAIR(3));

    int buff = (int) ((double) COLS) * 0.8 / 2;
    BASE_LEFT.position.x = buff / 2;
    BASE_MID.position.x = COLS / 2;
    BASE_RIGHT.position.x = COLS - buff / 2;

    BASE_LEFT.position.y = LINES;
    BASE_MID.position.y = LINES;
    BASE_RIGHT.position.y = LINES;
    reset_defense();
}


void reset_defense() {
    BASE_LEFT.missile_count = 15;
    BASE_MID.missile_count = 15;
    BASE_RIGHT.missile_count = 15;
}


void update_defense(int i) {
    // The missile canvas will always match the index
    // for a given crosshair from the input canvas.
    // This means we can check if a crosshair has been targeted
    // already by looking at the corresponding index.
    Sprite* target = &INPUT_CANVAS.sprites[i];
    if (!target->alive)
        return;

    Sprite* missile = &DEFENSE_CANVAS.sprites[i];
    if (!missile->alive) {

        struct Base* base = get_launchpoint(&target->path.current);
        if (base->missile_count) {
            set_animation(missile, &base->position, &target->path.current, 80);
            missile->view = ACS_DIAMOND;
            missile->keep_alive = SECOND * .5;
            --base->missile_count;
        }

    } else if (cmp_eq(&missile->path.current, &missile->path.end)) {
        collide_input_defense(&missile->path.current);
        target->alive = 0;
    }
}


static struct Base* get_launchpoint(Coord* target) {
    struct Base* bases[] = {&BASE_MID, &BASE_RIGHT};

    struct Base* base = &BASE_LEFT;
    double dist = distance(&base->position, target);
    for (int i = 0; i < 2; i++) {
        double d = distance(&bases[i]->position, target);
        if (d < dist || (bases[i]->missile_count && !base->missile_count)) {
            dist = d;
            base = bases[i];
        }
    }
    return base;
}