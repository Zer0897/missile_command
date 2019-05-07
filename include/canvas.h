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
	clock_t start_time;
} Vector;

typedef struct {
    char view;
    Vector path;
    bool active;
} Sprite;


typedef struct {
    WINDOW* window;
    Sprite sprites[120];
} Canvas;


void draw_sprite(Canvas*, Sprite*);
void add_sprite(Canvas*, Sprite);
void update_sprite(Canvas*, Sprite*);

#endif
