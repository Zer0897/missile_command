#include <ncurses.h>
#include "input.h"


static int get_event(WINDOW* win, MEVENT* event, int event_type) {
	int status = ERR;
	int c = wgetch(win);
	if (c == KEY_MOUSE && getmouse(event) == OK) {
		status = (event->bstate & event_type) ? OK : ERR; // Check if it's the right event
	}
	return status;
}


static int get_eventpos(WINDOW* win, Coord* coord, int event_type) {
	MEVENT event;

	int status = __get_event(win, &event, event_type);
	if (status == OK) {
		coord->x = event.x;
		coord->y = event.y;
	}
	return status;
}

int get_clickpos(WINDOW* win, Coord *coord) {
	return __get_eventpos(win, coord, BUTTON1_RELEASED);
}

int get_mousepos(WINDOW* win, Coord* coord) {
	return __get_eventpos(win, coord, REPORT_MOUSE_POSITION);
}
