#include "events.h"

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




/* 
Scaling is going to look werid as going from 5 -> -5 won't be smooth as it'll slow down then speed it.
Maybe the use of a bool to represent the doodle falling then velocity will only be 0->5 will fix this scaling issue
*/
void doodle_vertical_movement(Doodle *doodle)
{
    if(check_collision_doodle_platform)
    {
        doodle->velocity = MAX_VELOCITY;
        move_doodle(doodle, 0, doodle->velocity, doodle->facing);
    }

    if(doodle->velocity == -MAX_VELOCITY || doodle->velocity == MAX_VELOCITY)
    {
        move_doodle(doodle, 0, doodle->velocity, doodle->facing);
        return;
    }

    if(is_doodle_falling && doodle->velocity > -MAX_VELOCITY)
    {
        doodle->velocity -= 1;
        move_doodle(doodle, 0, doodle->velocity, doodle->facing);
        return;
    }

    if(!is_doodle_falling && doodle->velocity < MAX_VELOCITY)
    {
        doodle->velocity += 1;
        move_doodle(doodle, 0, doodle->velocity, doodle->facing);
        return;
    }

}

bool is_doodle_falling(Doodle *doodle)
{
    if(doodle->velocity < 0)
        return true;
    return false;
}