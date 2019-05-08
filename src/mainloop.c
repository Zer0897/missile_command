#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "mainloop.h"
#include "canvas.h"
#include "input_layer.h"
#include "alien_layer.h"
#include "defense_layer.h"


void init() {
	srand(time(NULL)); // seed for random events.
	initscr();
    noecho(); // Don't echo input.
    start_color(); // Enable colored formatting.
	curs_set(0); // Invisible cursor

	init_input();
	init_alien();
	init_defense();
}

void update() {
	static Canvas* layers[] = {
		&INPUT_CANVAS,
		&ALIEN_CANVAS,
		&DEFENSE_CANVAS
	};
	for (int i = 0; i < 120; i++) {
		update_input(i);
		update_alien(i);
		update_defense(i);

		for (int l = 0; l < 3; l++) {
			Canvas* layer = layers[l];
			Sprite* sprite = &layer->sprites[i];

			if (sprite->active) {
				lerp(&sprite->path);
				draw_sprite(layer, sprite);
			}
		}
	}
	wrefresh(INPUT_CANVAS.window);
	wrefresh(ALIEN_CANVAS.window);
	wrefresh(DEFENSE_CANVAS.window);
	refresh();
}


void teardown() {
	endwin();
	exit(0);
}

void panic(char* str) {
	printf("Error: %s", str);
	teardown();
}

void mainloop() {
	init();

    bool running = true;
    while (running) {
		update();
	}
	teardown();
}
