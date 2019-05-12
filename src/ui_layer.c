#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "ui_layer.h"
#include "defense_layer.h"
#include "main.h"
#include "animate.h"



static long int score = 0;
static int round = 1;
static int buildings[10] = { [0 ... 9] = 1 };
static struct Base* bases[] = {&BASE_LEFT, &BASE_MID, &BASE_RIGHT};


static void draw_building(Coord*, int);
static void clear_building(Coord*, int);


static void update_score() {
    mvwprintw(DISPLAY, 1, COLS / 2, "Score: %d ", score);
}

static void update_base() {
    for (int i = 0; i < 3; i++) {
        struct Base* base = bases[i];

        draw_building(&base->position, 5);
        mvwprintw(
            DISPLAY,
            base->position.y - 4,
            base->position.x - 6,
            "%d ", base->missile_count
        );
    }
}

static void update_buildings() {
    int xincrement = COLS * .8 / 10;
    Coord pos = { .x = xincrement * 2, .y = LINES };
    for (int i = 0; i < 10; i++) {
        if (buildings[i]) {
            draw_building(&pos, 1);
        } else {
            clear_building(&pos, 1);
        }
        pos.x += xincrement;
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


static void clear_building(Coord* position, int size) {
    int topy = position->y - size;
    int leftx = position->x - size * 1.5;
    int rightx = position->x + size * 1.5;

    mvwaddch(DISPLAY, topy, leftx, ' ');
    mvwhline(DISPLAY, topy, leftx + 1, ' ', size * 3 - 1);
    mvwaddch(DISPLAY, topy, rightx, ' ');
    mvwvline(DISPLAY, topy + 1, rightx, ' ', LINES - topy - 1);
    mvwvline(DISPLAY, topy + 1, leftx, ' ', LINES - topy - 1);
}


void init_display() {
    DISPLAY = newwin(0, 0, 0, 0);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    wattron(DISPLAY, COLOR_PAIR(5));
}


void update_display() {
    update_buildings();
    update_score();
    update_base();
    mvwprintw(DISPLAY, 1, COLS - 10, "Round %d ", round);
}


void add_score(int val) {
    score += val;
}

void destroy_building() {
    int found = false;
    for (int i = 0; i < 10; i++) {
        if (buildings[i]) {
            buildings[i] = 0;
            found = true;
            break;
        }
    }
    if (!found) {
        teardown();
        exit(0);
    }
}


void increment_round() {
    long timebuff = get_time();

    for (int i = 0; i < 3; i++) {
        while (bases[i]->missile_count) {
            if (get_time() - timebuff > SECOND / 8) {
                --bases[i]->missile_count;
                score += 125;
                timebuff = get_time();
            }
            mvprintw(LINES / 2, COLS / 2, "Success!");
            update();
        }
    }

    timebuff = get_time();
    for (int i = 0; i < 10; i++) {
        if (buildings[i]) {
            score += 300;
            buildings[i] = 0;
        }
        while (get_time() - timebuff < SECOND / 3) {
            update();
        }
        timebuff = get_time();
    }
    for (int i = 0; i < 10; i++) {
        buildings[i] = 1;
    }

    reset_defense();
    ++round;
}

int get_round() {
    return round;
}