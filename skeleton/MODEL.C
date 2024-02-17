#include "model.h"

void move_doodle(Doodle *doodle)
{
    doodle->y += doodle->delta_y;
    doodle->x += doodle->delta_x;
}

void move_platform(Platform *platform)
{
    platform->x += platform->delta_x;
}
