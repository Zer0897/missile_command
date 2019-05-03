#ifndef MAINLOOP_H
#define MAINLOOP_H

typedef struct {
	int x;
	int y;
} Coord;

void setup();
void mainloop();
void draw(char*);
int handle_input(Coord*);

#endif