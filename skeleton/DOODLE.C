/*
 * Author: Aidan & Jacky
 * Date: March 15, 2024
 *
 * Purpose:
 *   - The main function of the game, controlling rendering, input, and event handling.
 *
 * Functions:
 *   Function Name: input
 *     Purpose:
 *       - Handle keyboard input to update the game state.
 *     Input:
 *       - model: Pointer to the Model structure representing the game state.
 *       - pressedKey: Pointer to the variable storing the pressed key.
 *
 *   Function Name: get_time
 *     Purpose:
 *       - Get the current time in milliseconds.
 *     Output:
 *       - Returns the current time.
 *
 * Global Variables:
 *   - double_buffer: Double buffer for smoother rendering.
 */

#include "model.h"
#include "events.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

UINT8 double_buffer[512][80];

UINT32 get_time();
void delay(int milliseconds);
void input(Model *model, char *pressedKey);

int main() {
    UINT8 *bufferPtr = double_buffer;
    UINT8 i;
    int useDoubleBuffer = 1;
    UINT32 timeThen, timeNow, timeElapsed;
    Model *model = initialize_model();
    UINT32 *base = Physbase();
    char pressedKey = 0;

    while((int)bufferPtr % 256 != 0)
        bufferPtr++;

    render(model, bufferPtr);

    /*slight movement to all objects are required as the rendering optimzation requires some movement from initlization of objects 
    to prevent redrawing of still objects */
    for(i=0; i<MAX_PLATFORMS;i++)
    {
        move_platform_relative(model->platforms, 1, 1, i);
    }
    move_monster(&(model->monster),1,1);

    render(model, base);  /* Render the initial state of the model */

    while (pressedKey != 'q') { /* Main game loop */
        timeThen = get_time();
        input(model, &pressedKey);
        if(useDoubleBuffer == 1)
        {
            render(model, bufferPtr);
        }
        else
        {
            render(model,base);
        }

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if(timeElapsed > 0)
        {
            if(useDoubleBuffer == 1)
                {
                    Vsync();
                    Setscreen(-1, bufferPtr, -1);
                    useDoubleBuffer = 0;
                }
                else
                {
                    Vsync();
                    Setscreen(-1, base, -1);
                    useDoubleBuffer = 1;
                }
        }
    }

    return 0;
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

    switch (*pressedKey) { /* Handle the pressed key */
        case 'a':  
            model->doodle.facing = 0;
            move_doodle(&(model->doodle), -8, 0); /* Move the doodle left */
            break;
        case 'd':  
            model->doodle.facing = 1;
            move_doodle(&(model->doodle), 8, 0); /* Move the doodle right */
            break;
        default:
            break;
    }
}

UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0); 
    time = *((UINT32 *)0x462);
    Super(old_ssp); 
    return time;
}
