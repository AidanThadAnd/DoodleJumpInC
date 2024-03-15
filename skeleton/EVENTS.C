#include "events.h"
#include "MODEL.H"
#include "BITMAP.H"
#include "system.h"

void press_key(Doodle *character, char key)
{
    switch(key)
    {
        case 'a':
            move_doodle(character, -1, 0);
            character->facing = 0;
            break;
        case 'd':
            move_doodle(character, 1, 0);
            character->facing = 1;
            break;
        default:
            break;
    }
}
 
/*  Check if the bottom of the Doodle is below the top of the platform
    and if the top of the Doodle is above the bottom of the platform
    Check if the right side of the Doodle is to the right of the left side of the platform
    and if the left side of the Doodle is to the left of the right side of the platform */
int check_collision_doodle_platform(Doodle *doodle, Platform *platform)
{
    if (doodle->y + DOODLE_HEIGHT > platform->y &&
        doodle->y < platform->y + PLATFORM_HEIGHT &&
        doodle->x + DOODLE_LEG_WIDTH > platform->x && 
        doodle->x < platform->x + PLATFORM_WIDTH)   
    {
        return 1;
    }
        return 0;
}

int check_collision_monster(Doodle *doodle, Monster *monster)
{
    if (doodle->y + DOODLE_HEIGHT > monster->y &&
        doodle->y < monster->y + MONSTER_HEIGHT &&
        doodle->x + DOODLE_WIDTH > monster->x && 
        doodle->x < monster->x + MONSTER_WIDTH)   
    {
        return 1;
    }
        return 0;
}


