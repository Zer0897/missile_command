#include "draw.h"
#include "input.h"

void init_screens() {
    __init_crosshair();
}

void update_screens() {
    __update_crosshair();
    refresh();
}

Sprite* get_sprite(enum SpriteFlag flag) {
    static Sprite _sprites[MAX_SPRITES];
    return &_sprites[flag];
}

void __init_crosshair() {
    float ratio = 0.05f;
    int height = LINES * ratio;
    int width = COLS * ratio;
    Sprite* crosshair = get_sprite(CROSSHAIR);

    crosshair->window = newwin(0, 0, 0, 0); // Default.
    nodelay(crosshair->window, true);
    crosshair->acs_flag = ACS_PLUS;
}

void __update_crosshair() {
    Coord pos;
    Sprite* crosshair = get_sprite(CROSSHAIR);
    if (get_clickpos(crosshair->window, &pos) == OK) {
        wdelch(crosshair->window);
        mvwaddch(crosshair->window, pos.y, pos.x, crosshair->acs_flag);
        wrefresh(crosshair->window);
    }
}