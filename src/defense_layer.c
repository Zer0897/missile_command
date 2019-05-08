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
    if (!target->active)
        return;

    Sprite* missile = &DEFENSE_CANVAS.sprites[i];
    if (!missile->active) {
        Coord start = { .x = COLS / 2, .y = LINES };

        set_animation(missile, &start, &target->path.current);
        missile->view = ACS_DIAMOND;
        missile->path.speed = 25;
        missile->active = true;

    } else if (cmp_eq(&missile->path.current, &target->path.current)) {
        target->active = false;
        clear_sprite(missile);

        collide_input_defense(&missile->path.current);
    }
}
