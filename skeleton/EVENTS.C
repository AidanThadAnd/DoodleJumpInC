#include "events.h"

void press_key(Doodle *character, char key)
{
    switch(key)
    {
        case 'a':
            move_doodle(character, -1, 0)
            character->facing = 0;
            break;
        case 'd':
            move_doodle(character, 1, 0)
            character->facing = 1;
            break;
        default:
            break:
    }
}
 
/*  Check if the bottom of the Doodle is below the top of the platform
    and if the top of the Doodle is above the bottom of the platform
    Check if the right side of the Doodle is to the right of the left side of the platform
    and if the left side of the Doodle is to the left of the right side of the platform */
int check_collision_doodle_platform(Doodle *d, Platform *p)
{
    if (d->y + DOODLE_HEIGHT > p->y &&
        d->y < p->y + PLATFORM_HEIGHT &&
        d->x + DOODLE_LEG_WIDTH > p->x && 
        d->x < p->x + PLATFORM_WIDTH)   
    {
        return 1;
    }
        return 0;
}

