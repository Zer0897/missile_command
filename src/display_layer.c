#include <strings.h>
#include "display_layer.h"
#include "defense_layer.h"


static int score = 0;


static void update_score() {
    int x = COLS / 2;
    int y = 1;

    mvwprintw(DISPLAY, y, x, "Score %d", score);
}

static void update_base() {
    struct Base* bases[] = {&BASE_LEFT, &BASE_MID, &BASE_RIGHT};
    for (int i = 0; i < 3; i++) {
        struct Base* base = bases[i];

        int topy = base->position.y - 3;
        int leftx = base->position.x - 2;
        int rightx = base->position.x + 2;

        mvwhline(DISPLAY, topy, leftx, '-', rightx - leftx);
    }
}


void init_display() {
    DISPLAY = newwin(0, 0, 0, 0);
    // init_pair(5, COLOR_GREEN, COLOR_BLACK);
}


void update_display() {
    update_score();
    update_base();
}


void add_score(int x) {
    score += x;
}
