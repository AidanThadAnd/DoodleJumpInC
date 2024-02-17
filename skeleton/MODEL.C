#include "model.h"

void move_doodle(Doodle *doodle, int displacement_x, int displacement_y)
{
    doodle->y += displacement_y;
    doodle->x += displacement_x;
}

void move_platform(Platform *platform)
{
    platform->x += platform->delta_x;
}
