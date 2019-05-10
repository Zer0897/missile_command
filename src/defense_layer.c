#include "defense_layer.h"
#include "input_layer.h"
#include "animate.h"
#include "collision_layer.h"


static Coord get_launchpoint(Coord*);

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

        Coord start = get_launchpoint(&target->path.current);
        set_animation(missile, &start, &target->path.current, 80);
        missile->view = ACS_DIAMOND;
        missile->keep_alive = SECOND * .5;

    } else if (cmp_eq(&missile->path.current, &missile->path.end)) {
        collide_input_defense(&missile->path.current);
        target->alive = 0;
    }
}


static Coord get_launchpoint(Coord* target) {
    struct Base* bases[] = {&BASE_MID, &BASE_RIGHT};

    Coord start = BASE_LEFT.position;
    double dist = distance(&start, target);
    for (int i = 0; i < 2; i++) {
        double d = distance(&bases[i]->position, target);
        if (d < dist) {
            dist = d;
            start = bases[i]->position;
        }
    }

    return start;
}