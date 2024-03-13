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

/*
    model->doodle.prevX = -1; /* Sets the previous location state for optimized rendering 
    model->doodle.prevY = -1;
*/


    /* Initialize platforms */
    for (i = 0; i < MAX_PLATFORMS; ++i) {
        model->platforms[i].x = i * 100;
        model->platforms[i].y = SCREEN_HEIGHT - (i * 40);

        /*
        model->platforms[i].prevX = -1;
        model->platforms[i].prevY = -1;
        */
        
    }

    /* Initialize monster */
    model->monster.x = SCREEN_WIDTH / 2;
    model->monster.y = SCREEN_HEIGHT - 100;

    return model;
}

void move_doodle(Doodle *doodle, int displacement_x, int displacement_y)
{

    /*
    doodle->prevY = doodle->y;
    doodle->prevX = doodle->x;
    */


    doodle->y += displacement_y;
    doodle->x += displacement_x;
}

void move_platform(Platform *platform)
{
    
    platform->x += platform->delta_x;
}
