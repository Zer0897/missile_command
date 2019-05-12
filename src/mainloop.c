#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "mainloop.h"
#include "canvas.h"
#include "input_layer.h"
#include "alien_layer.h"
#include "defense_layer.h"
#include "collision_layer.h"
#include "display_layer.h"


bool running = true;

static Canvas* layers[] = {
	&INPUT_CANVAS,
	&ALIEN_CANVAS,
	&DEFENSE_CANVAS,
	&COLLISION_CANVAS,
	&GARBAGE_COLLECTOR_CANVAS,
};

static void start_round();
static void reset_round();


void init() {
	srand(time(NULL)); // seed for random events.
	initscr();
    noecho(); // Don't echo input.
    start_color(); // Enable colored formatting.
	curs_set(0); // Invisible cursor

	init_input();
	init_alien();
	init_defense();
	init_collision();
	init_garbage_collector();
	init_display();
}

void update() {
	for (int i = 0; i < 120; i++) {
		update_input(i);
		update_alien(i);
		update_defense(i);
		update_garbage_collector(i);
		update_display();

		for (int l = 0; l < 5; l++) {
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
	wrefresh(GARBAGE_COLLECTOR_CANVAS.window);
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

void mainloop() {
	init();
	while (1) {
		start_round();
		// getch();
		reset_round();
	}
	teardown();
}


static void start_round() {
	while (running) {
		update();
	}
}

static void reset_round() {
	increment_round();
	wclear(DISPLAY);
	for (int l = 0; l < 5; l++) {
		Canvas* layer = layers[l];
		for (int i = 0; i < 120; i++) {
			layer->sprites[i].alive = false;
		}
		wclear(layer->window);
	}
	reset_alien();
	clear();
	running = true;
}
