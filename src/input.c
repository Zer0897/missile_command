#include <ncurses.h>
#include "input.h"


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