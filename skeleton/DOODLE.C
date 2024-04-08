#include "model.h"
#include "events.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

UINT8 double_buffer[448][80] = {0};

UINT32 get_time();
void input(Model *model, char *pressedKey);
void syncModel(Model *modelSrc, Model *modelDst);
void process_synchronous_events(Model *model, bool *endGame, int seed);

int main() {
    UINT8 *page1 = Physbase();
    UINT8 *page2 = &double_buffer[0][0];
    UINT8 confirmedInput;
    int seed;

    bool useDoubleBuffer = true;
    bool endGame = false;

    UINT32 timeThen, timeNow, timeElapsed;

    Model modelOne, modelTwo, modelThree;
    Model *modelPtr = &modelOne;
    Model *modelSnapshotOne = &modelTwo;
    Model *modelSnapshotTwo = &modelThree;

    char pressedKey = 0;


    seed = Random();

    initialize_model(modelPtr, seed);
    initialize_model(modelSnapshotOne, seed);
    initialize_model(modelSnapshotTwo, seed);

    page2 = (UINT8*)((size_t)page2 | 0xff ) + 1; /* finding page aligned address for second page*/

    /* prepering models for main game loop*/
    syncModel(modelPtr, modelSnapshotOne);
    syncModel(modelPtr, modelSnapshotTwo);

    /* Preparing pages for main game loop*/
    clear_screen(page1);
    clear_screen(page2);
    render(modelPtr, (UINT32*)page1);
    render(modelPtr, (UINT32*)page2);

    
    

    timeThen = get_time();
    while (pressedKey != 'q' && !endGame) { /* Main game loop */

        input(modelPtr, &pressedKey);

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;

        if(timeElapsed > 0)
        {
            Vsync();
            if(useDoubleBuffer)
                {
                    process_synchronous_events(modelPtr, &endGame, seed);
                    
                    syncModel(modelPtr, modelSnapshotOne);
                    double_buffer_render(modelSnapshotTwo, (UINT32*)page1);
                    
                    Setscreen(-1, page1, -1);
                    
                    useDoubleBuffer = false;
                }
                else
                {
                    process_synchronous_events(modelPtr, &endGame, seed);

                    syncModel(modelPtr, modelSnapshotTwo);
                    double_buffer_render(modelSnapshotOne,(UINT32*)page2);
                    
                    Setscreen(-1, page2, -1);
                    
                    useDoubleBuffer = true;
                }
                seed = seed*3;
                Vsync();
        }
        timeThen = get_time();
    }

    Setscreen(-1, page1, -1);
    Vsync();
    return 0;
}


/***********************************************************************
* Name: syncModel
*
* Purpose: Synchronizes the content of two game models.
*
* Details: Copies data from the source model to the destination model,
*          ensuring consistency between the two models.
*
* Parameters:
*     - modelSrc: Pointer to the source game model.
*     - modelDst: Pointer to the destination game model.
***********************************************************************/
void syncModel(Model *modelSrc, Model *modelDst)
{
    UINT8 i;
    Platform *srcPlatform, *dstPlatform;

    modelDst->doodle.x = modelSrc->doodle.x;
    modelDst->doodle.y = modelSrc->doodle.y;

    modelDst->doodle.facing = modelSrc->doodle.facing;
    modelDst->doodle.prev_facing = modelSrc->doodle.prev_facing;

    modelDst->doodle.velocity = modelSrc->doodle.velocity;
    modelDst->doodle.isFalling = modelSrc->doodle.isFalling;
    modelDst->doodle.max_y = modelSrc->doodle.max_y;
    modelDst->doodle.dead = modelSrc->doodle.dead;

    modelDst->score.total = modelSrc->score.total;
    modelDst->score.prev_total = modelSrc->score.prev_total;
    modelDst->score.digits = modelSrc->score.digits;
    

    modelDst->monster.x = modelSrc->monster.x;
    modelDst->monster.y = modelSrc->monster.y;


    srcPlatform = (modelSrc->platforms);
    dstPlatform = (modelDst->platforms);

    for(i=0; i < MAX_PLATFORMS;i++)
    {
        dstPlatform->x = srcPlatform->x;
        dstPlatform->y = srcPlatform->y;


        dstPlatform->is_broken = srcPlatform->is_broken;

        srcPlatform++;
        dstPlatform++;     
    }
}

/***********************************************************************
* Name: input
*
* Purpose: Handles user input for the game.
*
* Details: Checks if keyboard input is available and reads the key.
*          If the pressed key is 'a', 'd', or 'q', it updates the
*          pressedKey variable accordingly.
*
* Parameters:
*     - model: Pointer to the game model.
*     - pressedKey: Pointer to the variable storing the pressed key.
***********************************************************************/
void input(Model *model, char *pressedKey)
{
    if (Cconis()) /* Check if keyboard input is available */
    { 
        char key = (char)Cnecin(); /* Read keyboard input */
        if (key == 'a' || key == 'd' || key == 'q')
            *pressedKey = key;
    } 
        else 
            *pressedKey = 0; /* Reset pressedKey if no key is pressed */


    doodle_input(&(model->doodle), *pressedKey);
    
}

/***********************************************************************
* Name: process_synchronous_events
*
* Purpose: Processes synchronous events for the game.
*
* Details: Calls functions to handle doodle movement, screen shifting,
*          off-screen replacement, and doodle death checking.
*
* Parameters:
*     - model: Pointer to the game model.
*     - endGame: Pointer to a boolean indicating game end.
*     - seed: Random seed for event generation.
***********************************************************************/
void process_synchronous_events(Model *model, bool *endGame, int seed)
{
    doodle_vertical_movement(model);
    shift_screen_to_doodle(model);
    replace_off_screen(model, seed);
    check_doodle_death(model, endGame);
}

/*
TODO: Investigate the weird slowdown issue with using Cconis in a wrapper function

bool isKeyPressed()
{
    if(Cconis())
        return true;
    return false;
}
*/

/***********************************************************************
* Name: get_time
*
* Purpose: Retrieves the current system time in milliseconds.
*
* Details: Gets the system time value stored at memory address 0x462,
*
* Returns:
*     - UINT32: The current system time in milliseconds.
***********************************************************************/
UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0); 
    time = *((UINT32 *)0x462);
    Super(old_ssp); 
    return time;
}
