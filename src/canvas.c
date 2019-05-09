#include "canvas.h"
#include "mainloop.h"
#include "animate.h"


void clear_sprite(Sprite* sprite, int speed) {
    if (sprite->view == ' ') return;
    
    set_animation(sprite, &sprite->path.beg, &sprite->path.end);
    sprite->view = ' ';
    sprite->active = 2;
    sprite->path.speed = speed;
}


void draw_sprite(Canvas* canvas, Sprite* sprite) {
    mvwaddch(
        canvas->window, sprite->path.current.y,
        sprite->path.current.x, sprite->view
    );
}

// Might add a sprite to the given canvas.
// If there is no memory left, nothing will happen.
void add_sprite(Canvas* canvas, Sprite sprite) {
    for (int i = 0; i < 120; i++) {
        if (canvas->sprites[i].active == false) {
            canvas->sprites[i] = sprite;
            canvas->sprites[i].active = true;
            break;
        }
    }
}


bool has_object(Canvas* canvas, Coord* coord) {
    return ((bool) mvwinch(canvas->window, coord->y, coord->x));
}