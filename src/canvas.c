#include "canvas.h"
#include "mainloop.h"

extern Canvas;
extern Sprite;

void add_sprite(Canvas*, Sprite);
// static void update_commander();
// static void init_commander();


// Might add a sprite to the given canvas.
// If there is no memory left, nothing will happen.
void add_sprite(Canvas* canvas, Sprite sprite) {
    for (int i = 0; i < 120; i++) {
        if (canvas->sprites[i].active == false) {
            mvwaddch(
                canvas->window, sprite.path.current.y,
                sprite.path.current.x, sprite.view
            );
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