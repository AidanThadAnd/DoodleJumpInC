#include "events.h"
#include "MODEL.H"
#include "BITMAP.H"
#include "system.h"

void doodle_input(Doodle *character, char key)
{
    switch(key)
    {
        case 'a':
            move_doodle(character, -DOODLE_HORIZONTAL_MOVEMENT, 0, 0);
            break;
        case 'd':
            move_doodle(character, DOODLE_HORIZONTAL_MOVEMENT, 0, 1);
            break;
        default:
            break;
    }
}
 
bool check_collision_doodle_platform(Doodle *doodle, Platform *platform)
{
    if (doodle->y + DOODLE_HEIGHT > platform->y &&
        doodle->y < platform->y + PLATFORM_HEIGHT &&
        doodle->x + DOODLE_LEG_WIDTH > platform->x && 
        doodle->x < platform->x + PLATFORM_WIDTH)   
    {
        return true;
    }
        return false;
}

bool check_collision_monster(Doodle *doodle, Monster *monster)
{
    if (doodle->y + DOODLE_HEIGHT > monster->y &&
        doodle->y < monster->y + MONSTER_HEIGHT &&
        doodle->x + DOODLE_WIDTH > monster->x && 
        doodle->x < monster->x + MONSTER_WIDTH)   
    {
        return true;
    }
        return false;
}


