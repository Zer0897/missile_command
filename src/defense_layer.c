#include "defense_layer.h"
#include "input_layer.h"
#include "animate.h"


static void set_target(Sprite*, Coord*);


void init_defense() {
    DEFENSE_CANVAS.window = newwin(0, 0, 0, 0);
    wattron(DEFENSE_CANVAS.window, COLOR_PAIR(1)); // same as crosshair color;
}


void update_defense() {
    for (int i = 0; i < 120; i++) {
        // Get any existing crosshairs from the input canvas
        Sprite* target = &INPUT_CANVAS.sprites[i];
        if (!target->active) continue;

        // The missile canvas will always match the index
        // for a given crosshair from the input canvas.
        // This means we can check if a crosshair has been targeted
        // already by looking at the corresponding index.
        Sprite* missile = &DEFENSE_CANVAS.sprites[i];
        if (!missile->active) {
            missile->view = ACS_DIAMOND;
            set_target(missile, &target->path.current);
            draw_sprite(&DEFENSE_CANVAS, missile);
        // The missile is at the target
        } else if (cmp_eq(&missile->path.current, &missile->path.end)) {
            clear_sprite(&DEFENSE_CANVAS, missile);
        }
    }
}


static void set_target(Sprite* missile, Coord* target) {
    Coord start = { .x = COLS / 2, .y = LINES };
    set_animation(missile, &start, target);
}