#include "canvas.h"
#include "mainloop.h"
#include "animate.h"

#include "collision_layer.h"
#include "alien_layer.h"
#include "input_layer.h"
#include "defense_layer.h"


static Sprite* get_sprite(Canvas*);


void init_garbage_collector() {
    GARBAGE_COLLECTOR_CANVAS.window = newwin(0, 0, 0, 0);
}

// void update_garbage_collector(int i) {
//     Sprite* input = &INPUT_CANVAS.sprites[i];
//     Sprite* defense = &DEFENSE_CANVAS.sprites[i];
//     Sprite* alien = &ALIEN_CANVAS.sprites[i];
//     Sprite* collision = &COLLISION_CANVAS.sprites[i];
// }


void clear_sprite(Sprite* sprite, int speed) {
    Sprite* gc;
    for (int i = 0; i < 120; i++) {
        gc = &GARBAGE_COLLECTOR_CANVAS.sprites[i];
        if (!gc->alive) {
            gc->view = ' ';
            set_animation(gc, &sprite->path.beg, &sprite->path.end, speed);
            break;
        }
    }

    // set_animation(gc, &sprite->path.beg, &sprite->path.end);
}


void draw_sprite(Canvas* canvas, Sprite* sprite) {
    mvwaddch(
        canvas->window, sprite->path.current.y,
        sprite->path.current.x, sprite->view
    );
}


bool has_object(Canvas* canvas, Coord* coord) {
    char c = mvwinch(canvas->window, coord->y, coord->x);
    return (c != ERR && c != ' ');
}