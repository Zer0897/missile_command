#include <ncurses.h>
#include "input_layer.h"


static int get_event(MEVENT*, int);
static int get_clickpos(Coord*);


void update_input() {

}


void init_input() {
	INPUT_CANVAS.window = newwin(0, 0, 0, 0);
	keypad(INPUT_CANVAS.window, true); // Allows input from all keys. Includes mouse.
	mousemask(BUTTON1_RELEASED | REPORT_MOUSE_POSITION, NULL); // Listen for mouse events
}


static int get_event(MEVENT* event, int event_type) {
	int status = ERR;
	int c = wgetch(INPUT_CANVAS.window);
	if (c == KEY_MOUSE && getmouse(event) == OK) {
		status = (event->bstate & event_type) ? OK : ERR; // Check if it's the right event
	}
	return status;
}


static int get_clickpos(Coord* coord) {
	MEVENT event;

	int status = get_event(&event, BUTTON1_RELEASED);
	if (status == OK) {
		coord->x = event.x;
		coord->y = event.y;
	}
	return status;
}
