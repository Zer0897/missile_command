#include <strings.h>
#include "display_layer.h"
#include "defense_layer.h"

static int total = 0;
static int score = 0;
static int round = 1;

static int building_count = 10;
static void draw_building(Coord*, int);


static void update_score() {
    int x = COLS / 2;
    int y = 1;

    mvwprintw(DISPLAY, y, x, "Score %d ", score);
}

static void update_base() {
    struct Base* bases[] = {&BASE_LEFT, &BASE_MID, &BASE_RIGHT};
    for (int i = 0; i < 3; i++) {
        struct Base* base = bases[i];

        draw_building(&base->position, 5);
        mvwprintw(
            DISPLAY,
            base->position.y - 2,
            base->position.x,
            "%d ", base->missile_count
        );
    }
}

static void draw_building(Coord* position, int size) {
    int topy = position->y - size;
    int leftx = position->x - size;
    int rightx = position->x + size;

    mvwaddch(DISPLAY, topy, leftx, ACS_ULCORNER);
    mvwhline(DISPLAY, topy, leftx + 1, ACS_HLINE, size * 2 - 1);
    mvwaddch(DISPLAY, topy, rightx, ACS_URCORNER);
    mvwvline(DISPLAY, topy + 1, rightx, ACS_VLINE, LINES - topy - 1);
    mvwvline(DISPLAY, topy + 1, leftx, ACS_VLINE, LINES - topy - 1);
}

void init_display() {
    DISPLAY = newwin(0, 0, 0, 0);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    wattron(DISPLAY, COLOR_PAIR(5));
}


void update_display() {
    update_score();
    update_base();
}


void add_score(int val) {
    score += val;
}

void increment_round() {
    total += score;
    score = 0;
    ++round;
}

int get_round() {
    return round;
}