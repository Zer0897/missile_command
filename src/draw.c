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

    // First time, need to allocate memory.
    if (!canvas->sprites) {
        canvas->sprite_max = 25;
        canvas->sprites = (Sprite*) malloc(sprite_size * canvas->sprite_max);
    // Not enough space, allocate twice as much as before.
    } else if (canvas->sprite_max == canvas->sprite_count + 1) {
        canvas->sprite_max *= 2;
        canvas->sprites = (Sprite*) realloc(canvas->sprites, sprite_size * canvas->sprite_max);
    }
    // Look for usable memory.
    for (size_t i = 0; i < canvas->sprite_max; i++) {
        if (!canvas->sprites[i]) {
            canvas->sprites[i] = *sprite;
            ++canvas->sprite_count;
            return;
        }
    }
    panic("Could not allocate memory for sprite.");
}

static void collect_garbage(Canvas* canvas) {
    for (size_t i = 0; i < canvas->sprite_max; i++) {
        Sprite* sprite = canvas->sprites[i];
        if (!sprite)
            continue;

        if (cmp_eq(sprite->current, sprite->end)) {
            *sprite = NULL;
            --canvas->sprite_count;
        }
    }
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