#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "mainloop.h"
#include "input.h"


void setup() {
	initscr();
	noecho(); // Don't echo input.
	keypad(stdscr, true); // Accept all keys. Needed for mouse.
	halfdelay(1); // Wait 1/10 of a second on input.
	mousemask(BUTTON1_RELEASED, NULL); // Listen for mouse click.
	start_color(); // Enable colored formatting.
	curs_set(2); // Invisible cursor
 }


void mainloop() {
	setup();

	Coord click;
    bool running = true;
    while (running) {
		if (handle_input(&click) == OK) {
			running = false;
		}
	}
	endwin();
	printf("Clicked y: %d, x: %d\n", click.y, click.x);
}

