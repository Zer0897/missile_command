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

void update_garbage_collector(int i) {
	static Canvas* layers[] = {
		&INPUT_CANVAS,
		&ALIEN_CANVAS,
		&DEFENSE_CANVAS,
		&COLLISION_CANVAS,
	};

    Sprite* sprite = &GARBAGE_COLLECTOR_CANVAS.sprites[i];
    if (sprite->alive) {
        for (int l = 0; l < 4; l++) {
            Canvas* layer = layers[l];
            mvwaddch(
                layer->window,
                sprite->path.current.y,
                sprite->path.current.x,
                sprite->view
            );
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
    // if (sprite->view == ' ') {
    //     mvwdelch(
    //         canvas->window,
    //         sprite->path.current.y,
    //         sprite->path.current.x
    //     );
    // } else {
        mvwaddch(
            canvas->window,
            sprite->path.current.y,
            sprite->path.current.x, sprite->view
        );
    // }
}


bool has_object(Canvas* canvas, Coord* coord) {
    chtype c = mvwinch(canvas->window, coord->y, coord->x);
    mvaddch(0, 0, c);

    return (c != ERR && c != ' ');
}