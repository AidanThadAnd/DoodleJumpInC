#include "events.h"
#include <stdio.h>

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
    UINT8 i;
    int heightDifference;
    int distanceFromPlatform;
    bool foundPlatform = false;


/*
Potentially if the y values are not exactly the same == may not work
*/
    
    for(i=0; i<MAX_PLATFORMS && !foundPlatform; i++)
    {
    heightDifference = platform->y + 1 - (doodle->y + DOODLE_HEIGHT);
        if(heightDifference < MAX_VELOCITY-3 && heightDifference > -MAX_VELOCITY+3)
            foundPlatform = true;
        else
            platform++;
            
    }

    if(!foundPlatform)
        return false;


    distanceFromPlatform = (doodle->x + DOODLE_WIDTH) - (platform->x - PLATFORM_WIDTH);
    if (distanceFromPlatform > 0 && distanceFromPlatform < 80)
        {
            return true;
        }
        return false;

}
/*

Doodle is at x=200
Platform is at x=220

Doodle is 32 wide
platform is 10 wide

doodle->x + doodle width = 232

platform->x + platform width = 230

platform goes from 220 --- 230
Doodle is 200 --- 232

*/


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
void doodle_vertical_movement(Model *model)
{
    Doodle *doodle = &(model->doodle);
    Platform *platformsArray = model->platforms;
    Monster *monster = &(model->monster);


    if(check_collision_doodle_platform(doodle, platformsArray))
    {
        doodle->velocity = MAX_VELOCITY;
        doodle->isFalling = false;
        move_doodle(doodle, 0, -(doodle->velocity), doodle->facing);
        return;
    }

    switch(doodle->velocity)
    {
        case(MAX_VELOCITY):
        {
            if(doodle->isFalling)
                move_doodle(doodle, 0, doodle->velocity, doodle->facing);
            else
            {
                move_doodle(doodle, 0, -(doodle->velocity), doodle->facing);
                doodle->velocity -= 1;
            }
        }
        break;
        case(0):
        {
            doodle->isFalling = true;
            doodle->velocity++;
        }
        break;
        default:
        {
            if(doodle->isFalling)
            {
                move_doodle(doodle, 0, (doodle->velocity), doodle->facing);
                doodle->velocity++;
            }
            else
            {
                move_doodle(doodle, 0, -(doodle->velocity), doodle->facing);
                doodle->velocity-= 1;
            }
        }
        break;
    }
}