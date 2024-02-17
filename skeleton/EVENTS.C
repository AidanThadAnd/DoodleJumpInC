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

int check_collision_doodle_platform(Doodle *d, Platform *p)
{
    /* Check if the bottom of the Doodle is below the top of the platform
       and if the top of the Doodle is above the bottom of the platform
       Check if the right side of the Doodle is to the right of the left side of the platform
       and if the left side of the Doodle is to the left of the right side of the platform */
    if (d->y + doodle_height > p->y &&
        d->y < p->y + platform_height &&
        d->x + doodle_width > p->x && 
        d->x < p->x + platform_width)   
    {
        return 1;
    }
        return 0;
}

