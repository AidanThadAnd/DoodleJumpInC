#include "model.h"


void initialize_model(Model *model)
{
    int i;
    int randomNumber;
    /* Initialize Doodle character */
    model->doodle.x = SCREEN_WIDTH / 2;
    model->doodle.y = (SCREEN_HEIGHT-64) / 2;
    model->doodle.facing = 1; /* Assuming initially facing right */
    model->doodle.prev_facing = 0;
    
    model->doodle.prev_x = -1; /* Sets the previous location state for optimized rendering, intialzed to an impossible state */
    model->doodle.prev_y = -1;

    model->doodle.velocity = 0;
    model->doodle.isFalling = true;
    model->doodle.max_y = model->doodle.y;


    randomNumber = Random();
    randomNumber = randomNumber % 10;


    /* Initialize platforms */
    for (i=0; i <MAX_PLATFORMS; i++) {
        model->platforms[i].x = i * 64;
        model->platforms[i].y = (i * 60);

        model->platforms[i].prev_x = -1;
        model->platforms[i].prev_y = -1;
        
        model->platforms[i].off_screen = false;
    }
    model->platforms[0].x = model->doodle.x;
    model->platforms[0].y = model->doodle.y + DOODLE_HEIGHT*3;




    /* Initialize monster */
    model->monster.x = SCREEN_WIDTH / 2;
    model->monster.y = SCREEN_HEIGHT - 100;

    model->monster.prev_x = -1;
    model->monster.prev_y = -1;
}


void move_doodle(Doodle *doodle, int displacement_x, int displacement_y, UINT16 newFacing)
{
    int screenBorderCheck;

    doodle->prev_facing = doodle->facing;
    doodle->prev_x = doodle->x;
    doodle->prev_y = doodle->y;

    doodle->x += displacement_x;

    if(doodle->x > SCREEN_WIDTH)
        doodle->x -= SCREEN_WIDTH;
    else 
        if(doodle->x < SCREEN_WIDTH)
            doodle->x += SCREEN_WIDTH;

    doodle->facing = newFacing;
    doodle->y += displacement_y;
}

void move_platform_relative(Platform *platform, int displacement_x, int displacement_y, UINT8 selected_platform)
{
    UINT8 i;

    for(i=0; i<selected_platform;i++)
        platform++;

    platform->x = displacement_x + platform->x;
    platform->y = displacement_y + platform->y;

    if(platform->y > SCREEN_HEIGHT)
        platform->off_screen = true;

    if(platform->x > SCREEN_WIDTH)
    {
        platform->x -= SCREEN_WIDTH;
    }

}

void move_monster(Monster *monster, int displacement_x, int displacement_y)
{
    monster->prev_x = monster->x;
    monster->prev_y = monster->y;

    monster->x += displacement_x;
    monster->y += displacement_y;

    if(monster->y > SCREEN_HEIGHT)
        monster->off_screen = true;

    if(monster->x > SCREEN_WIDTH)
    {
        monster->x -= SCREEN_WIDTH;
    }
}

void move_platform_absolute(Platform *platforms, UINT16 x, UINT16 y)
{
    UINT8 i;

    platforms->x = x;
    platforms->y = y;

    if(platforms->x > SCREEN_WIDTH)
    { 
        platforms->x -= SCREEN_WIDTH;
    }
}


bool has_doodle_moved(Doodle *doodle)
{
    if(doodle->prev_x != doodle->x || doodle->prev_y != doodle->y || doodle->prev_facing != doodle->facing)
        return true;

    return false;
}

bool has_monster_moved(Monster *monster)
{
    if(monster->prev_x != monster->x || monster->prev_y != monster->y)
        return true;

    return false;
}

bool has_platform_moved(Platform *platform)
{
    if(platform->prev_x != platform->x || platform->prev_y != platform->y)
        return true;

    
    
    return false;
}