#include "model.h"
#include "system.h"


Model* initialize_model()
{
    Model *model;
    int i;
    /* Initialize Doodle character */
    model->doodle.x = SCREEN_WIDTH / 2;
    model->doodle.y = SCREEN_HEIGHT / 2;
    model->doodle.delta_x = 0;
    model->doodle.delta_y = 0;
    model->doodle.facing = 1; /* Assuming initially facing right */

    
    model->doodle.prev_x = -1; /* Sets the previous location state for optimized rendering */
    model->doodle.prev_y = -1;
    



    /* Initialize platforms */
    for (i = 0; i < MAX_PLATFORMS; ++i) {
        model->platforms[i].x = i * 100;
        model->platforms[i].y = SCREEN_HEIGHT - (i * 40);

        
        model->platforms[i].prev_x = -1;
        model->platforms[i].prev_y = -1;
        
        
        
    }

    /* Initialize monster */
    model->monster.x = SCREEN_WIDTH / 2;
    model->monster.y = SCREEN_HEIGHT - 100;

    model->monster.prev_x = -1;
    model->monster.prev_y = -1;
    
    return model;
}


void move_doodle(Doodle *doodle, UINT16 displacement_x, UINT16 displacement_y)
{
    doodle->y += displacement_x;
    doodle->x += displacement_y;
}

/*
void move_doodle(Doodle *doodle)
{
    doodle->prev_y = doodle->y;
    doodle->prev_x = doodle->x;
    
    doodle->y += doodle->delta_y;
    doodle->x += doodle->delta_x;
}
*/
/*
As the camera will be locked on the center of the screen (and capped to the highest height achieved) we will need to link the delta y with
the movement of the camera 
*/
void move_platform(Platform *platform)
{
    platform->prev_x = platform->x;
    platform->prev_y = platform->y;

    platform->x += platform->delta_x;
    platform->y += platform->delta_y;
}

void move_monster(Monster *monster)
{
    monster->prev_x = monster->x;
    monster->prev_y = monster->y;

    monster->x += monster->delta_x;
    monster->y += monster->delta_y;
}



UINT8 has_doodle_moved(Doodle *doodle)
{
    if(doodle->prev_x != doodle->x && doodle->prev_y != doodle->y)
        return 1;

    return 0;
}

UINT8 has_monster_moved(Monster *monster)
{
    if(monster->prev_x != monster->x && monster->prev_y != monster->y)
        return 1;

    return 0;
}

UINT8 has_platform_moved(Platform *platform)
{
    if(platform->prev_x != platform->x && platform->prev_y != platform->y)
        return 1;
    
    return 0;
}