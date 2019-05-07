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
	update_input();
	update_alien();
	update_defense();

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
