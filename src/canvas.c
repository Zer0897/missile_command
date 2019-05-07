#include "canvas.h"
#include "mainloop.h"
#include "animate.h"


void update_sprite(Canvas* canvas, Sprite* sprite) {
    mvwdelch(canvas->window, sprite->path.current.y, sprite->path.current.x);
    lerp(&sprite->path);
    draw_sprite(canvas, sprite);
}


void clear_sprite(Canvas* canvas, Sprite* sprite) {
    mvwdelch(canvas->window, sprite->path.current.y, sprite->path.current.x);
}


void draw_sprite(Canvas* canvas, Sprite* sprite) {
    sprite->active = true;
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
            draw_sprite(canvas, &sprite);
            canvas->sprites[i] = sprite;
            break;
        }
    }
}


// static void init_commander() {
//     Canvas* canvas = get_canvas(COMMANDER);
//     canvas->window = dupwin(stdscr); // Default.
//     nodelay(canvas->window, true);

// }

// static void update_commander() {
//     Coord click_pos;
//     Canvas* canvas = get_canvas(COMMANDER);
//     if (get_clickpos(canvas->window, &click_pos) == OK) {
//         Sprite crosshair = {};
//         // mvwaddch(crosshair->window, pos.y, pos.x, crosshair->view);
//         // crosshair->coord.y = pos.y;
//         // crosshair->coord.x = pos.x;

//         // wrefresh(crosshair->window);
//     }
// }

// static void draw(Canvas* canvas, Sprite* sprite) {
//     // 4x4 grid, start in the left corner
//     int starty = sprite->path.current.y - 2;
//     int startx = sprite->path.current.x - 2;
//     for (int i = 0; i < 16; i++) {
//         int x = startx + i;
//         int y = starty + i;


//     }
// }