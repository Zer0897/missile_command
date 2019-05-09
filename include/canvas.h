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
	unsigned long start_time;
} Vector;

typedef struct {
    int view;
    Vector path;
    int active; // number of frames the sprite may remain static.
} Sprite;


typedef struct {
    WINDOW* window;
    Sprite sprites[120];
} Canvas;


void clear_sprite(Sprite*, int);
void draw_sprite(Canvas*, Sprite*);
void add_sprite(Canvas*, Sprite);
void update_sprite(Canvas*, Sprite*);
bool has_object(Canvas*, Coord*);

#endif
