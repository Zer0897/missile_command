#include "animate.h"
#include "math.h"


bool cmp_eq(Coord* c1, Coord* c2) {
    return (c1->y == c2->y && c1->x == c2->x);
}


double distance(Coord* c1, Coord* c2) {
    double dy2 = powf(c2->y - c1->y, 2.0f);
    double dx2 = powf(c2->x - c1->x, 2.0f);

    return sqrt(dy2 + dx2);
}


void lerp(Vector* vec) {
    double total_dist = distance(&vec->beg, &vec->end);
    double elapsed = difftime(time(NULL), vec->start_time);
    double mult = (elapsed * vec->speed) / total_dist;

    Coord curr = {
        .y = vec->beg.y * mult,
        .x = vec->beg.x * mult
    };
    vec->current = curr;
}