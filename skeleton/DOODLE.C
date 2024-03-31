/*
  Author: Aidan & Jacky
  Date: March 15, 2024
 
  Purpose:
    - The main function of the game, controlling animation, rendering, input, and event handling.
 
  Functions:
    Function Name: input
      Purpose:
        - Handle keyboard input to update the game state.
      Input:
        - model: Pointer to the Model structure representing the game state.
        - pressedKey: Pointer to the variable storing the pressed key.
 
    Function Name: get_time
      Purpose:
        - Get the current time in milliseconds.
      Output:
        - Returns the current time.
 
  Global Variables:
    - double_buffer: Double buffer for smoother rendering.
 */

#include "model.h"
#include "events.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

UINT8 double_buffer[432][80] = {0};

UINT32 get_time();
void input(Model *model, char *pressedKey);
void syncModel(Model *modelSrc, Model *modelDst);

int main() {
    UINT8 *page1 = Physbase();
    UINT8 *page2 = &double_buffer[0][0];
    UINT8 i;
    UINT8 confirmedInput;

    bool useDoubleBuffer = true;

    UINT32 timeThen, timeNow, timeElapsed;

    Model modelOne, modelTwo;
    Model *modelOnePtr = &modelOne;
    Model *modelTwoPtr = &modelTwo;

    char pressedKey = 0;


    initialize_model(modelOnePtr);
    initialize_model(modelTwoPtr);

    page2 = (UINT8*)((size_t)page2 | 0xff ) + 1; /* finding page aligned address for second page*/

    /*slight movement to all objects are required as the rendering optimzation requires some movement from initlization of objects 
    to prevent redrawing of still objects  */
    for(i=0; i<MAX_PLATFORMS;i++)
    {
        move_platform_relative(modelOnePtr->platforms, 1, 1, i);
    }
    move_monster(&(modelOnePtr->monster), 8, 8);


    /* prepering pages and models for main game loop*/
    clear_screen(page1);
    clear_screen(page2);
    syncModel(modelOnePtr, modelTwoPtr);

    render(modelOnePtr, (UINT32*)page1);  /* Render the initial state of the model */
    
    

    timeThen = get_time();
    while (pressedKey != 'q') { /* Main game loop */

        if(useDoubleBuffer)
            input(modelOnePtr, &pressedKey);
        else
            input(modelTwoPtr, &pressedKey);
            

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;

        if(timeElapsed > 0)
        {
            Vsync();
            if(useDoubleBuffer)
                {
                    double_buffer_render(modelTwoPtr, modelOnePtr, (UINT32*)page1);
                    Setscreen(-1, page1, -1);
                    Vsync();

                    doodle_vertical_movement(modelOnePtr);
                    useDoubleBuffer = true;
                    syncModel(modelOnePtr, modelTwoPtr);
                }
                else
                {
                    double_buffer_render(modelOnePtr, modelTwoPtr, (UINT32*)page2);
                    Setscreen(-1, page2, -1);
                    Vsync();

                    doodle_vertical_movement(modelOnePtr);
                    useDoubleBuffer = false;
                    syncModel(modelTwoPtr, modelOnePtr);
                }
        }
        timeThen = get_time();
    }
    Setscreen(-1, page1, -1);
    Vsync();

    return 0;
}

void syncModel(Model *modelSrc, Model *modelDst)
{
    UINT8 i;
    Platform *srcPlatform, *dstPlatform;

    modelDst->doodle.x = modelSrc->doodle.x;
    modelDst->doodle.y = modelSrc->doodle.y;

    modelDst->doodle.prev_x = modelSrc->doodle.prev_x;
    modelDst->doodle.prev_y = modelSrc->doodle.prev_y;

    modelDst->doodle.facing = modelSrc->doodle.facing;
    modelDst->doodle.prev_facing = modelSrc->doodle.prev_facing;

    modelDst->doodle.velocity = modelSrc->doodle.velocity;


    modelDst->monster.x = modelSrc->monster.x;
    modelDst->monster.y = modelSrc->monster.y;

    modelDst->monster.prev_x = modelSrc->monster.prev_x;
    modelDst->monster.prev_y = modelSrc->monster.prev_y;

    srcPlatform = (modelSrc->platforms);
    dstPlatform = (modelDst->platforms);

    for(i=0; i < MAX_PLATFORMS;i++)
    {
        dstPlatform->x = srcPlatform->x;
        dstPlatform->y = srcPlatform->y;
        dstPlatform->prev_x = srcPlatform->prev_x;
        dstPlatform->prev_y = srcPlatform->prev_y; 

        srcPlatform++;
        dstPlatform++;     
    }
}


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

/*

TODO: Investigate the weird slowdown issue with using Cconis in a wrapper function

bool isKeyPressed()
{
    if(Cconis())
        return true;
    return false;
}
*/

UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0); 
    time = *((UINT32 *)0x462);
    Super(old_ssp); 
    return time;
}
