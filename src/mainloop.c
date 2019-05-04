#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "mainloop.h"
#include "input.h"
#include "draw.h"


void setup() {
	initscr();
    // Key configs
    noecho(); // Don't echo input.
	keypad(stdscr, true); // Accept all keys. Needed for mouse.
	halfdelay(1); // Wait 1/10 of a second on input.
	mousemask(BUTTON1_RELEASED | REPORT_MOUSE_POSITION, NULL); // Listen for mouse events
    // Display config
    start_color(); // Enable colored formatting.
	curs_set(2); // Invisible cursor

    init_sprites();
}


void mainloop() {
	setup();

	Coord click;
    bool running = true;
    while (running) {
        update_sprites();
	}
	endwin();
	printf("Clicked y: %d, x: %d\n", click.y, click.x);
}

