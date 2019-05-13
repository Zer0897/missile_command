#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "main.h"
#include "main_menu.h"
#include "canvas.h"
#include "input_layer.h"
#include "alien_layer.h"
#include "defense_layer.h"
#include "collision_layer.h"
#include "ui_layer.h"


bool running = true;
bool lost = false;

static Canvas* layers[] = {
	&INPUT_CANVAS,
	&ALIEN_CANVAS,
	&DEFENSE_CANVAS,
	&COLLISION_CANVAS,
};

static void start_round();
static void reset_round();
static void init();
static void start_game();

int main() {
	init();
	while (main_menu()) {
		start_game();
	}
	teardown();
	return 0;
}

static void start_game() {
	lost = false;
	clear_game();
	while (true) {
		start_round();
		if (!lost)
			reset_round();
		else
			break;
	}
}


static void init() {
	srand(time(NULL)); // seed for random events.
	initscr();
    noecho(); // Don't echo input.
    start_color(); // Enable colored formatting.
	curs_set(0); // Invisible cursor

	init_input();
	init_alien();
	init_defense();
	init_collision();
	init_display();
}

void update() {
	for (int i = 0; i < 120; i++) {
		update_input(i);
		update_alien(i);
		update_defense(i);
		update_display();

		for (int l = 0; l < 4; l++) {
			Canvas* layer = layers[l];
			Sprite* sprite = &layer->sprites[i];

			if (sprite->alive) {
				update_animation(layer, sprite);
			}
		}
	}

	wrefresh(COLLISION_CANVAS.window);
	wrefresh(INPUT_CANVAS.window);
	wrefresh(ALIEN_CANVAS.window);
	wrefresh(DEFENSE_CANVAS.window);
	wrefresh(DISPLAY);
	refresh();


	if (is_alien_done()) {
		running = false;
	}
}


void teardown() {
	endwin();
}

void panic(char* str) {
	teardown();
	printf("Error: %s\n", str);
	exit(0);
}



static void start_round() {
	running = true;
	while (running) {
		update();
	}
}

static void reset_round() {
	increment_round();
	clear_game();
}

void clear_game() {
	wclear(DISPLAY);
	for (int l = 0; l < 4; l++) {
		Canvas* layer = layers[l];
		for (int i = 0; i < 120; i++) {
			layer->sprites[i].alive = false;
		}
		wclear(layer->window);
	}
	reset_alien();
	clear();
	refresh();
}

void lose_game() {
	lost = true;
	running = false;
	clear_game();
}