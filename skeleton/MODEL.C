#include "model.h"

/***********************************************************************
* Name: initialize_model
*
* Purpose: Initializes the game model with default values.
*
* Details: Initializes the doodle character, platforms, and monster
*          with their initial positions, velocities, and other attributes.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
*     - seed: Random seed for generating platform positions.
***********************************************************************/
void initialize_model(Model *model, int seed)
{
    int i;
    int randomNum;
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
    model->doodle.dead = false;

    model->score.digits = 1;
    model->score.total = 1;
    model->score.prev_total = 0;


    /* Initialize platforms */
    for (i=0; i <MAX_PLATFORMS; i++) {
        randomNum = seed % 7;
        randomNum+=2;

        if(randomNum == 2 )
            model->platforms[i].is_broken = true;
        else
            model->platforms[i].is_broken = false;
        model->platforms[i].prev_x = -1;
        model->platforms[i].prev_y = -1;

        move_platform_absolute(&(model->platforms[i]), randomNum*64, i*50);
        
        model->platforms[i].off_screen = false;
        seed = seed * 3;
    }
    model->platforms[0].x = model->doodle.x;
    model->platforms[0].y = model->doodle.y + DOODLE_HEIGHT*3;
    model->platforms[0].is_broken = false;



    /* Initialize monster */
    move_monster_absolute(&(model->monster), randomNum*64, 0);

    model->monster.prev_x = -1;
    model->monster.prev_y = -1;
}

/***********************************************************************
* Name: move_doodle
*
* Purpose: Moves the doodle character.
*
* Details: Moves the doodle character horizontally and vertically
*          based on the given displacement. Updates the previous
*          position and facing direction.
*
* Parameters:
*     - doodle: Pointer to the doodle object to be moved.
*     - displacement_x: Horizontal displacement.
*     - displacement_y: Vertical displacement.
*     - newFacing: New facing direction of the doodle.
***********************************************************************/
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
        if(doodle->x < 0)
            doodle->x += SCREEN_WIDTH;

    doodle->facing = newFacing;
    doodle->y += displacement_y;
}

/***********************************************************************
* Name: move_platform_relative
*
* Purpose: Moves a platform relative to its current position.
*
* Details: Moves the platform horizontally and vertically relative to
*          its current position. Updates the off-screen flag if the
*          platform moves below the screen.
*
* Parameters:
*     - platform: Pointer to the platform object to be moved.
*     - displacement_x: Horizontal displacement.
*     - displacement_y: Vertical displacement.
*     - selected_platform: Index of the platform to be moved.
***********************************************************************/
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

/***********************************************************************
* Name: move_monster_relative
*
* Purpose: Moves the monster relative to its current position.
*
* Details: Moves the monster horizontally and vertically relative to
*          its current position. Updates the off-screen flag if the
*          monster moves below the screen.
*
* Parameters:
*     - monster: Pointer to the monster object to be moved.
*     - displacement_x: Horizontal displacement.
*     - displacement_y: Vertical displacement.
***********************************************************************/
void move_monster_relative(Monster *monster, int displacement_x, int displacement_y)
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

/***********************************************************************
* Name: move_monster_absolute
*
* Purpose: Moves the monster to an absolute position.
*
* Details: Moves the monster to the specified coordinates. Adjusts
*          the position if it goes beyond the screen boundaries.
*
* Parameters:
*     - monster: Pointer to the monster object to be moved.
*     - x: X-coordinate of the new position.
*     - y: Y-coordinate of the new position.
***********************************************************************/
void move_monster_absolute(Monster *monster, int x, int y)
{
    monster->x = x;
    monster->y = y;

    if(monster->x > SCREEN_WIDTH)
    { 
        monster->x -= SCREEN_WIDTH;
    }
    else
        if(monster->x < 0)
            monster->x +=SCREEN_WIDTH;
}

/***********************************************************************
* Name: move_platform_absolute
*
* Purpose: Moves a platform to an absolute position.
*
* Details: Moves the platform to the specified coordinates. Adjusts
*          the position if it goes beyond the screen boundaries.
*
* Parameters:
*     - platforms: Pointer to the platform object to be moved.
*     - x: X-coordinate of the new position.
*     - y: Y-coordinate of the new position.
***********************************************************************/
void move_platform_absolute(Platform *platforms, UINT16 x, UINT16 y)
{
    platforms->x = x;
    platforms->y = y;


    if(platforms->x > SCREEN_WIDTH)
    { 
        platforms->x -= SCREEN_WIDTH;
    }
    else
        if(platforms->x < 0)
            platforms->x +=SCREEN_WIDTH;
}

/***********************************************************************
* Name: has_doodle_moved
*
* Purpose: Checks if the doodle has moved.
*
* Details: Compares the current doodle position and facing direction
*          with the previous state to determine if there's movement.
*
* Parameters:
*     - doodle: Pointer to the doodle object.
* Returns:
*     - bool: True if the doodle has moved, false otherwise.
***********************************************************************/
bool has_doodle_moved(Doodle *doodle)
{
    if(doodle->prev_x != doodle->x || doodle->prev_y != doodle->y || doodle->prev_facing != doodle->facing)
        return true;

    return false;
}

/***********************************************************************
* Name: has_monster_moved
*
* Purpose: Checks if the monster has moved.
*
* Details: Compares the current monster position with the previous
*          state to determine if there's movement.
*
* Parameters:
*     - monster: Pointer to the monster object.
* Returns:
*     - bool: True if the monster has moved, false otherwise.
***********************************************************************/
bool has_monster_moved(Monster *monster)
{
    if(monster->prev_x != monster->x || monster->prev_y != monster->y)
        return true;

    return false;
}

/***********************************************************************
* Name: has_platform_moved
*
* Purpose: Checks if a platform has moved.
*
* Details: Compares the current platform position with the previous
*          state to determine if there's movement.
*
* Parameters:
*     - platform: Pointer to the platform object.
* Returns:
*     - bool: True if the platform has moved, false otherwise.
***********************************************************************/
bool has_platform_moved(Platform *platform)
{
    if(platform->prev_x != platform->x || platform->prev_y != platform->y)
        return true;

    
    
    return false;
}