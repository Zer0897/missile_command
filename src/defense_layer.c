#include "defense_layer.h"
#include "input_layer.h"
#include "animate.h"
#include "collision_layer.h"


void init_defense() {
    DEFENSE_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wattron(DEFENSE_CANVAS.window, COLOR_PAIR(3)); // same as crosshair color;
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
        int b = (int) ((double) COLS) * 0.9;
        int b1, b2, b3;
        b1 = (COLS - b) / 2;
        b2 = COLS / 2;
        b3 = COLS - b1;

        Coord start1 = { .x = b1, .y = LINES };
        Coord start2 = { .x = b2, .y = LINES };
        Coord start3 = { .x = b3, .y = LINES };

        Coord start = start1;

        if (distance(&start, &target->path.current) > distance(&start2, &target->path.current)) {
            start = start2;
        }

        if (distance(&start, &target->path.current) > distance(&start3, &target->path.current)) {
            start = start3;
        }

        set_animation(missile, &start, &target->path.current, 80);
        missile->view = ACS_DIAMOND;
        missile->keep_alive = SECOND * .5;

    } else if (cmp_eq(&missile->path.current, &missile->path.end)) {
        collide_input_defense(&missile->path.current);
        target->alive = 0;
    }
}
