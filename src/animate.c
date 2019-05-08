#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "animate.h"


static bool is_smooth(Coord*, Coord*, Coord*);


void lerp(Vector* vec) {
    if (!vec->start_time) return;

    double dist = distance(&vec->beg, &vec->end);
    double total_time = dist / vec->speed;
    double elapsed = (double) (clock() - vec->start_time) / CLOCKS_PER_SEC;
    double mult = elapsed / total_time;

    if (mult > 1) {
        vec->current = vec->end;
    } else {
        Coord next = {
            .y = vec->beg.y + (vec->end.y - vec->beg.y) * mult,
            .x = vec->beg.x + (vec->end.x - vec->beg.x) * mult
        };
        if (next.y != vec->current.y) vec->current = next;
    }
}


static bool is_smooth(Coord* c1, Coord* c2, Coord* end) {
    int s1 = (int) slope(c1, end);
    int s2 = (int) slope(c2, end);

    return (s1 == s2);
}

bool cmp_eq(Coord* c1, Coord* c2) {
    return (c1->y == c2->y && c1->x == c2->x);
}

bool cmp_gt(Coord* c1, Coord* c2) {
    static Coord origin = {.x = 0, .y = 0};
    return distance(&origin, c1) > distance(&origin, c2);
}

double distance(Coord* c1, Coord* c2) {
    double dy2 = pow(abs(c2->y - c1->y), 2.0);
    double dx2 = pow(abs(c2->x - c1->x), 2.0);

    return sqrt(dy2 + dx2);
}

double slope(Coord* c1, Coord* c2) {
    double sx = (double) c2->x - c1->x;
    double sy = (double) c2->y - c1->y;

    return (sx && sy) ? sy / sx : 0;
}


void set_animation(Sprite* sprite, Coord* start, Coord* end) {
    sprite->path.current = *start;
    sprite->path.beg = *start;
    sprite->path.end = *end;
    sprite->path.speed = 10;
    sprite->path.start_time = clock();
}
