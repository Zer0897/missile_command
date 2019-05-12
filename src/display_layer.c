#include <strings.h>
#include "display_layer.h"
#include "defense_layer.h"
#include "mainloop.h"
#include "animate.h"



static int score = 0;
static int round = 1;
static int buildings[10];
static struct Base* bases[] = {&BASE_LEFT, &BASE_MID, &BASE_RIGHT};


static void draw_building(Coord*, int);


static void update_score() {
    mvwprintw(DISPLAY, 1, COLS / 2, "Score: %d ", score);
}

static void update_base() {
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
    int leftx = position->x - size * 1.5;
    int rightx = position->x + size * 1.5;

    mvwaddch(DISPLAY, topy, leftx, ACS_ULCORNER);
    mvwhline(DISPLAY, topy, leftx + 1, ACS_HLINE, size * 3 - 1);
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
    mvwprintw(DISPLAY, 1, COLS - 10, "Round %d ", round);
}


void add_score(int val) {
    score += val;
}

void destroy_building() {

}

void increment_round() {
    for (int i = 0; i < 3; i++) {
        long timebuff = get_nanotime();
        while (bases[i]->missile_count) {
            if (get_nanotime() - timebuff > SECOND / 10) {
                --bases[i]->missile_count;
                score += 125;
                timebuff = get_nanotime();
            }
            mvprintw(LINES / 2, COLS / 2, "Success!");
            update();
        }
    }
    reset_defense();
    ++round;
}

int get_round() {
    return round;
}