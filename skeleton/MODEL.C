#include "model.h"

void move_doodle(Doodle *doodle, int displacement_x, int displacement_y)
{
    doodle->y += doodle->y;
    doodle->x += doodle->x;
}

void move_platform(Platform *platform)
{
    platform->x += platform->delta_x;
}
