#include "draw.h"

void init_screens() {
    void __init_crosshair();
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
}

void __update_crosshair() {
    int x, y;
}