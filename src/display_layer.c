#include <strings.h>
#include "display_layer.h"


static int score = 0;



static void update_score() {
    int x = 5;
    int y = 5;

    attron(COLOR_PAIR(5));
    mvprintw(y, x, "Score %d", score);
    attroff(COLOR_PAIR(5));
}


void init_display() {
    DISPLAY = newwin(0, 0, 0, 0);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
}


void update_display() {
    update_score();
}
