#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "animate.h"


// static bool is_smooth(Coord*, Coord*, Coord*);


void lerp(Vector* vec) {
    double dist = distance(&vec->beg, &vec->end);
    double total_time = dist / vec->speed;
    double elapsed = (double) (get_nanotime() - vec->start_time) / SECOND;
    double mult = elapsed / total_time;

    if (mult > 1) {
        vec->current = vec->end;
    } else {
        Coord next = {
            .y = vec->beg.y + (vec->end.y - vec->beg.y) * mult,
            .x = vec->beg.x + (vec->end.x - vec->beg.x) * mult
        };
        //if (next.y != vec->current.y)
        vec->current = next;
    }
}


// static bool is_smooth(Coord* c1, Coord* c2, Coord* end) {
//     int s1 = (int) slope(c1, end);
//     int s2 = (int) slope(c2, end);

//     return (s1 == s2);
// }

bool cmp_eq(Coord* c1, Coord* c2) {
    return (c1->y == c2->y && c1->x == c2->x);
}

bool cmp_gt(Coord* c1, Coord* c2) {
    static Coord origin = {.x = 0, .y = 0};
    return distance(&origin, c1) > distance(&origin, c2);
}

double distance(Coord* c1, Coord* c2) {
    double dy = abs(c2->y - c1->y);
    double dx = abs(c2->x - c1->x);

    return hypot(dx, dy);
}

double slope(Coord* c1, Coord* c2) {
    double dx = (double) c2->x - c1->x;
    double dy = (double) c2->y - c1->y;

    return (dx) ? dy / dx : NAN;
}


void set_animation(Sprite* sprite, Coord* start, Coord* end, int speed) {
    sprite->path.current = *start;
    sprite->path.beg = *start;
    sprite->path.end = *end;
    sprite->path.speed = speed;
    sprite->alive = true;
    sprite->path.start_time = get_nanotime();
}

void update_animation(Canvas* canvas, Sprite* sprite) {
    draw_sprite(canvas, sprite);

    if (!is_animation_done(sprite)) {
        lerp(&sprite->path);

    } else {
        long travel_time = (long int) distance(&sprite->path.beg, &sprite->path.end) / sprite->path.speed;
        long elapsed = get_nanotime() - sprite->path.start_time;
        if (sprite->keep_alive < elapsed - travel_time) {
            sprite->alive = false;
            clear_sprite(canvas, sprite);
        }
    }
}


bool is_animation_done(Sprite* sprite) {
    return (cmp_eq(&sprite->path.current, &sprite->path.end));
}


unsigned long get_nanotime() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (unsigned long) ts.tv_sec * SECOND + ts.tv_nsec;
}