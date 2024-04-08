#include "events.h"


/***********************************************************************
* Name: check_doodle_death
*
* Purpose: Checks if the doodle has died.
*
* Details: Checks if the doodle has fallen below the screen height
*          or collided with the monster. Updates the endGame flag
*          accordingly if the doodle is dead.
*
* Parameters:
*     - model: Pointer to the game model.
*     - endGame: Pointer to a boolean indicating game end.
***********************************************************************/

void check_doodle_death(Model *model, bool *endGame)
{
    if(model->doodle.y > SCREEN_HEIGHT)
        *endGame = true;
    
    if(check_collision_monster(&(model->doodle), &(model->monster)))
        model->doodle.dead = true;
    return;
}

/***********************************************************************
* Name: doodle_input
*
* Purpose: Handles user input for doodle movement.
*
* Details: Moves the doodle left or right based on the pressed key.
*          If the doodle is dead, no movement is allowed.
*
* Parameters:
*     - character: Pointer to the doodle object.
*     - key: Character representing the pressed key.
***********************************************************************/

void doodle_input(Doodle *character, char key)
{
    if(character->dead)
        return;

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
/***********************************************************************
* Name: replace_off_screen
*
* Purpose: Replaces off-screen platforms and the monster.
*
* Details: Moves off-screen platforms and the monster to a new position
*          horizontally based on a random seed.
*
* Parameters:
*     - model: Pointer to the game model.
*     - seed: Random seed for platform replacement.
***********************************************************************/

void replace_off_screen(Model *model, int seed)
{
    UINT8 i;
    UINT8 totalPlatformsMoved = 1;

    seed = seed % 9;
    seed++;

    for(i=0; i<MAX_PLATFORMS; i++)
    {
        if(model->platforms[i].off_screen)
        {

            if(seed == 1)
                model->platforms[i].is_broken = true;
            else
                model->platforms[i].is_broken = false;
            move_platform_absolute(&(model->platforms[i]), (seed<<6), 0);
            model->platforms[i].off_screen = false;

            totalPlatformsMoved++;
        }
    }
    if(model->monster.off_screen)
    {
        move_monster_absolute(&(model->monster), (seed<<7), 0);
        model->monster.off_screen = false;
    }
}
/***********************************************************************
* Name: check_collision_doodle_platform
*
* Purpose: Checks collision between doodle and platforms.
*
* Details: Checks if the doodle collides with any of the platforms.
*
* Parameters:
*     - doodle: Pointer to the doodle object.
*     - platform: Pointer to the array of platform objects.
* Returns:
*     - bool: True if collision occurs, false otherwise.
***********************************************************************/

bool check_collision_doodle_platform(Doodle *doodle, Platform *platform)
{
    UINT8 i;
    int heightDifference;
    int distanceFromPlatform;

    
    for(i=0; i<MAX_PLATFORMS; i++)
    {
        if (!(platform[i].is_broken) && doodle->x + DOODLE_WIDTH > platform[i].x && doodle->x + 5 < platform[i].x+PLATFORM_WIDTH)
        {
            heightDifference = platform[i].y - (doodle->y + DOODLE_HEIGHT);
            if(heightDifference < MAX_VELOCITY+10 && heightDifference > -(MAX_VELOCITY))
                return true;
        }   
    }
    return false;
}
/***********************************************************************
* Name: check_collision_monster
*
* Purpose: Checks collision between doodle and monster.
*
* Details: Checks if the doodle collides with the monster.
*
* Parameters:
*     - doodle: Pointer to the doodle object.
*     - monster: Pointer to the monster object.
* Returns:
*     - bool: True if collision occurs, false otherwise.
***********************************************************************/

bool check_collision_monster(Doodle *doodle, Monster *monster)
{
    if (doodle->y+DOODLE_HEIGHT > monster->y && 
        doodle->y < monster->y +MONSTER_HEIGHT &&
        doodle->x + DOODLE_WIDTH > monster->x &&
        doodle->x < monster->x + MONSTER_WIDTH)   
    {
        return true;
    }
        return false;
}

/***********************************************************************
* Name: shift_screen_to_doodle
*
* Purpose: Shifts the screen based on doodle movement.
*
* Details: Moves platforms and the monster vertically relative to the
*          doodle's movement. Updates the game score accordingly.
*
* Parameters:
*     - model: Pointer to the game model.
***********************************************************************/

void shift_screen_to_doodle(Model *model)
{
    UINT8 i;
    
    if(model->doodle.isFalling || model->doodle.y > model->doodle.max_y)
        return;

    move_monster_relative(&(model->monster), 0, model->doodle.velocity);
    
    for(i = 0; i < MAX_PLATFORMS; i++){
        move_platform_relative(model->platforms, 0, model->doodle.velocity, i);
    }
    model->score.prev_total = model->score.total;
    model->score.total = model->score.total + model->doodle.velocity+1;

    move_doodle(&(model->doodle), 0, model->doodle.velocity+1, model->doodle.facing);

}
/***********************************************************************
* Name: doodle_vertical_movement
*
* Purpose: Handles vertical movement of the doodle.
*
* Details: Handles doodle's vertical movement, including falling,
*          jumping, and collision detection with platforms.
*
* Parameters:
*     - model: Pointer to the game model.
***********************************************************************/

void doodle_vertical_movement(Model *model)
{
    Doodle *doodle = &(model->doodle);
    Platform *platformsArray = model->platforms;
    Monster *monster = &(model->monster);
    
    if(check_collision_doodle_platform(doodle, platformsArray) && model->doodle.isFalling && !(doodle->dead))
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