#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <mainloop.h>



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


void draw(char *msg) {
	int row = getmaxy(stdscr) / 2;
	int col = getmaxx(stdscr) / 2;

	// init_pair(1, COLOR_CYAN, COLOR_BLACK);
	// attron(A_REVERSE);
	mvprintw(row, col, msg);
	// attroff(A_REVERSE);
	refresh();
}


int handle_input(Coord *coord) {
	MEVENT mouse_event;
	int status = ERR;

	int c = getch();
	if (c == KEY_MOUSE && getmouse(&mouse_event) == OK) {
		coord->x = mouse_event.x;
		coord->y = mouse_event.y;
		status = OK;
	}
	return status;
}