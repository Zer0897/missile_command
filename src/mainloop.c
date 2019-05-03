#include <mainloop.h>
#include <ncurses.h>

void draw() {
	printw("Hello, world!");
}


void mainloop() {
	initscr();

    bool running = true;
    while (running) {
		draw();
	    refresh();
		getch();
        running = false;
    }

	endwin();
}
