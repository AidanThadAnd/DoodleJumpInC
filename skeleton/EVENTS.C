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

void replace_off_screen(Model *model, int seed)
{
    UINT8 i;
    UINT8 totalPlatformsMoved = 1;

    seed = seed % 10;

    for(i=0; i<MAX_PLATFORMS; i++)
    {
        if(model->platforms[i].off_screen)
        {

            move_platform_absolute(&(model->platforms[i]), (seed<<6), 0);
            model->platforms[i].off_screen = false;

            totalPlatformsMoved++;
        }
    }
}
 
bool check_collision_doodle_platform(Doodle *doodle, Platform *platform)
{
    UINT8 i;
    int heightDifference;
    int distanceFromPlatform;

    
    for(i=0; i<MAX_PLATFORMS; i++)
    {
        if (doodle->x + DOODLE_WIDTH > platform[i].x && doodle->x + 5 < platform[i].x+PLATFORM_WIDTH)
        {
            heightDifference = platform[i].y - (doodle->y + DOODLE_HEIGHT);
            if(heightDifference < MAX_VELOCITY+10 && heightDifference > -(MAX_VELOCITY+10))
                return true;
        }   
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


void shift_screen_to_doodle(Model *model)
{
    UINT8 i;
    
    if(model->doodle.isFalling || model->doodle.y > model->doodle.max_y)
        return;

    move_monster(&(model->monster), 0, model->doodle.velocity);
    
    for(i = 0; i < MAX_PLATFORMS; i++){
        move_platform_relative(model->platforms, 0, model->doodle.velocity, i);
    }

    move_doodle(&(model->doodle), 0, model->doodle.velocity+1, model->doodle.facing);

}

void doodle_vertical_movement(Model *model)
{
    Doodle *doodle = &(model->doodle);
    Platform *platformsArray = model->platforms;
    Monster *monster = &(model->monster);
    
    if(check_collision_doodle_platform(doodle, platformsArray) && model->doodle.isFalling)
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
            if(doodle->y < model->doodle.max_y)
                model->doodle.max_y = model->doodle.y;
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