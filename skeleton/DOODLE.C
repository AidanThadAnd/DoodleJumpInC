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
#include "BITMAP.H"

UINT8 double_buffer[432][80] = {0};

UINT32 get_time();
void delay(int milliseconds);
void input(Model *model, char *pressedKey);
void syncModel(Model *modelSrc, Model *modelDst);

int main() {
    UINT8 *page2 = &double_buffer[0][0];
    UINT8 i;
    int useDoubleBuffer = 1;
    UINT32 timeThen, timeNow, timeElapsed;
    Model modelOne;
    Model modelTwo;
    Model *modelOnePtr = &modelOne;
    Model *modelTwoPtr = &modelTwo;
    
    UINT8 *page1 = Physbase();
    char pressedKey = 0;

    initialize_model(modelOnePtr);
    initialize_model(modelTwoPtr);

    page2 = (UINT8*)((size_t)page2 | 0xff ) + 1;

    clear_screen(page2);
    /*
    printf("Value of page2: %p\n", page2);
    page2 = (UINT8*)(((size_t)page2 + 255) & ~255);
    */
    printf("Value of page2: %p\n", page2);



    /*slight movement to all objects are required as the rendering optimzation requires some movement from initlization of objects 
    to prevent redrawing of still objects  */
    for(i=0; i<MAX_PLATFORMS;i++)
    {
        move_platform_relative(modelOnePtr->platforms, 1, 1, i);
    }
    move_monster(&(modelOnePtr->monster), 8, 8);

    for(i=0; i<MAX_PLATFORMS;i++)
    {
        move_platform_relative(modelOnePtr->platforms, 5, 5, i);
    }



/*
    plot_bitmap_32(page2, SCREEN_WIDTH/2, SCREEN_HEIGHT-DOODLE_HEIGHT+32, doodle_bitmap_right, DOODLE_HEIGHT);
    clear_screen(page2);

    render(model, page2);
    Setscreen(-1, page2, -1);
    Vsync();

    while (pressedKey != 'q') { 
        input(model, &pressedKey);
    }


    Setscreen(-1, page1, -1);
    Vsync();
*/

/*
*/


/*
while (pressedKey != 'q') { 
        timeThen = get_time();
        input(model, &pressedKey);
        render(model,page1);
        
        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if(timeElapsed > 0)
        {
            Setscreen(-1, page1, -1);
            Vsync();
        }
    }
*/

    clear_screen(page1);
    render(modelOnePtr, page1);  /* Render the initial state of the model */
    /*
    syncModel(modelOne, modelTwo);
    */
    timeThen = get_time();

    printf("Model 1 x: %d  Model 2 x: %d\n", modelOnePtr->monster.prev_x, modelTwoPtr->monster.prev_x);

/*
    while (pressedKey != 'q') { /* Main game loop 

        if(useDoubleBuffer == 1)
            input(modelOne, &pressedKey);
        else
            input(modelTwo, &pressedKey);
            

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;

        if(timeElapsed > 0)
        {
            if(useDoubleBuffer == 1)
                {
                    render(modelTwo, page2);
                    Setscreen(-1, page2, -1);
                    Vsync();
                    useDoubleBuffer = 0;
                }
                else
                {
                    render(modelOne,page1);
                    Setscreen(-1, page1, -1);
                    Vsync();
                    useDoubleBuffer = 1;

                }
        }
        timeThen = get_time();
    }

    Setscreen(-1, page1, -1);

*/
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

    modelDst->monster.x = modelSrc->monster.x;
    modelDst->monster.y = modelSrc->monster.y;
    modelDst->monster.prev_x = modelSrc->monster.prev_x;
    modelDst->monster.prev_y = modelSrc->monster.prev_y;


/*
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
*/

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
