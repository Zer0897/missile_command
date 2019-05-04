#include "draw.h"
#include "input.h"
#include "mainloop.h"

extern Canvas;
extern Sprite;

static void add_sprite(Canvas*, Sprite*);
static void remove_sprite(Canvas*, Sprite*);
static void update_commander();
static void init_commander();

void init_canvases() {
    init_commander();
}

void update_canvases() {
    update_commander();
    refresh();
}

Canvas* get_canvas(enum CanvasFlag flag) {
    static Canvas _canvases[CANVAS_COUNT];
    return &_canvases[flag];
}

static void add_sprite(Canvas* canvas, Sprite* sprite) {
    const static sprite_size = sizeof(Sprite);
    size_t current_size = sprite_size * canvas->sprites_max;
    size_t len = current_size / sprite_size;

    // First time adding sprite, need to allocate memory.
    if (current_size == sprite_size) {
        current_size = sprite_size * 25;
        canvas->sprites = (Sprite*) malloc(current_size);
    // Not enough space, allocate twice as much as before.
    } else if (len == canvas->sprite_count + 1) {
        current_size *= 2;
        canvas->sprites = (Sprite*) realloc(canvas->sprites, current_size);
        len = current_size / sprite_size;
    }
    // Look for usable memory.
    size_t i = 0;
    Sprite* sprite = canvas->sprites[i];
    for (; !sprite && i < len; i++) {
        sprite = canvas->sprites[i];
    }
    if (sprite) {
        canvas->sprite_count += 1;
    } else {
        panic("Could not allocate memory for sprite.");
    }
}

static void remove_sprite(Canvas* canvas, Sprite* sprite) {
    const static sprite_size = sizeof(Sprite);
    size_t current_size = sizeof(canvas->sprites);
    size_t len = current_size / sprite_size;
}

static void init_commander() {
    Canvas* canvas = get_canvas(COMMANDER);
    canvas->window = dupwin(stdscr); // Default.
    nodelay(canvas->window, true);

}

static void update_commander() {
    Coord click_pos;
    Canvas* canvas = get_canvas(COMMANDER);
    if (get_clickpos(canvas->window, &click_pos) == OK) {
        Sprite crosshair = {};
        // mvwaddch(crosshair->window, pos.y, pos.x, crosshair->acs_flag);
        // crosshair->coord.y = pos.y;
        // crosshair->coord.x = pos.x;

        // wrefresh(crosshair->window);
    }
}