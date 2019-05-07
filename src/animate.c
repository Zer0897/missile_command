#include <time.h>
#include <stdlib.h>
#include "animate.h"
#include "math.h"

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


void lerp(Vector* vec) {
    double total_dist = distance(&vec->beg, &vec->end);
    double elapsed = (double) (clock() - vec->start_time) / CLOCKS_PER_SEC;

    double mult = (elapsed / vec->speed);

    if (mult > 1) {
        vec->current = vec->end;
    } else {
        Coord curr = {
            .y = vec->beg.y + (vec->end.y - vec->beg.y) * mult,
            .x = vec->beg.x + (vec->end.x - vec->beg.x) * mult
        };
        vec->current = curr;
    }
}


void update_animations(Canvas* canvas) {
    for (int i = 0; i < 120; i++) {
        if (canvas->sprites[i].active) {
            update_sprite(canvas, &canvas->sprites[i]);
        }
    }
}
