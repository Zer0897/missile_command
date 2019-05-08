#include "canvas.h"
#include "mainloop.h"
#include "animate.h"


// void update_sprite(Canvas* canvas, Sprite* sprite) {
//     Coord curr = sprite->path.current;

//     lerp(&sprite->path);
//     if (!cmp_eq(&curr, &sprite->path.current)) {
//         mvwdelch(canvas->window, curr.y, curr.x);
//         draw_sprite(canvas, sprite);
//     }
// }


void clear_sprite(Canvas* canvas, Sprite* sprite) {
    mvwdelch(canvas->window, sprite->path.current.y, sprite->path.current.x);
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
