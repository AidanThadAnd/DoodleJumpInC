#include "events.h"

int check_collision_doodle_platform(Doodle *d, Platform *p)
{
    if (d->y + doodle_height > p->y &&
        d->y < p->y + platform_height &&
        d->x + doodle_width > p->x &&
        d->x < p->x + platform_width)
    {
        return 1;
    }
        return 0;
}

