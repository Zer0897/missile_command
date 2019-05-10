#include "canvas.h"
#include "mainloop.h"
#include "animate.h"

#include "collision_layer.h"
#include "alien_layer.h"
#include "input_layer.h"
#include "defense_layer.h"


static void draw(Canvas*, Coord*, chtype);


static Canvas* layers[] = {
    &INPUT_CANVAS,
    &ALIEN_CANVAS,
    &DEFENSE_CANVAS,
    &COLLISION_CANVAS,
};


static void update_window_cleaner() {
    static int x = 0;
    static int y = 0;

    Coord box[16];
    Coord point = { .y = y, .x = x };
    get_box(&point, 1, &box);
    get_box(&point, 2, box + 8);

    int neighbor_count = 0;
    for (int l = 0; l < 4; l++) {

        for (int b = 0; b < 16; b++) {
            if (has_object(layers[l], &box[b])) {
                ++neighbor_count;
            }
        }

        if (neighbor_count < 3) {
            // draw(layers[l], &point, ' ');
        }

        neighbor_count = 0;
    }

    ++x;
    if (x > COLS) {
        x = 0;
        ++y;
    }
    if (y > LINES) {
        y = 0;
    }
    mvprintw(0, 0, "%d, %d", y, x);
}


void init_garbage_collector() {
    GARBAGE_COLLECTOR_CANVAS.window = newwin(0, 0, 0, 0);
}

/*
 * Update the garbage collector, removing all the sprites that are
 * no longer active.
 *
 * Our garbage collector sprites only overwrite characters
 * visually. This means the characters still exist on
 * the other ones canvases, which causes issues with our
 * collision detection.
 *
 * In order to compensate, we check the current coord of
 * our gc sprites and make sure all the other canvases are
 * being overwritten as well.
*/
void update_garbage_collector(int i) {

    Sprite* sprite = &GARBAGE_COLLECTOR_CANVAS.sprites[i];
    // if (sprite->alive) {
    //     for (int l = 0; l < 4; l++) {
    //         draw(layers[l], &sprite->path.current, sprite->view);
    //     }
    // }
    update_window_cleaner();
    if (sprite->alive) {
        Coord box[8];
        get_box(&sprite->path.current, 1, &box);

        for (int l = 0; l < 4; l++) {
            Canvas* layer = layers[l];
            draw(layer, &sprite->path.current, sprite->view);
            for (int b = 0; b < 8; b++) {
                mvwaddch(layer->window, box[b].y, box[b].x, sprite->view);
            }
        }
    }
}


void clear_sprite(Sprite* sprite, int speed) {
    if (sprite->view == ' ')
        return;

    Sprite* gc;
    for (int i = 0; i < 120; i++) {
        gc = &GARBAGE_COLLECTOR_CANVAS.sprites[i];
        if (!gc->alive) {
            gc->view = ' ';
            set_animation(gc, &sprite->path.beg, &sprite->path.end, speed);
            sprite->keep_alive = SECOND * .5;
            break;
        }
    }
}


void draw_sprite(Canvas* canvas, Sprite* sprite) {
    draw(canvas, &sprite->path.current, sprite->view);
}


bool has_object(Canvas* canvas, Coord* coord) {
    chtype c = mvwinch(canvas->window, coord->y, coord->x);
    return (c != ERR && c != ' ');
}


static void draw(Canvas* canvas, Coord* point, chtype c) {
    mvwaddch(canvas->window, point->y, point->x, c);
}