#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "mainloop.h"
#include "input_layer.h"
#include "canvas.h"


void init() {
	initscr();
    noecho(); // Don't echo input.
    start_color(); // Enable colored formatting.
	curs_set(0); // Invisible cursor
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
	init_input();

    bool running = true;
    while (running) {
		update_input();
	}
	teardown();
}
