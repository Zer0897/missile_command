#ifndef CANVAS_H
#define CANVAS_H

#include <ncurses.h>
#include <time.h>

typedef struct {
	int x;
	int y;
} Coord;


typedef struct {
	Coord beg;
	Coord current;
	Coord end;
	double speed;
	long start_time;
} Vector;

typedef struct {
    chtype view;
    Vector path;
    long keep_alive; // time before garbage collector gets to it
	bool alive;
} Sprite;


typedef struct {
    WINDOW* window;
    Sprite sprites[120];
} Canvas;


Canvas GARBAGE_COLLECTOR_CANVAS;

void init_garbage_collector();
void update_garbage_collector(int);
void clear_sprite(Sprite*, int);
void draw_sprite(Canvas*, Sprite*);
void update_sprite(Canvas*, Sprite*);
bool has_object(Canvas*, Coord*);

#endif
