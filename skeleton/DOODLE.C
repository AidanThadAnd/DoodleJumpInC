#include "model.h"
#include "events.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

UINT32 get_time();
void delay(int milliseconds);
void input(Model *model, char *pressedKey);

int main() {
    
    UINT32 timeThen, timeNow, timeElapsed;
    
    Model *model = initialize_model();
    UINT32 *base = Physbase();   
    char pressedKey = 0;
    clear_screen((UINT8*)base);

    render(model, base);  /* Render the initial state of the model */

    while (pressedKey != 'q') { /* Main game loop */
        timeThen = get_time();
        input(model, &pressedKey);

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if(timeElapsed > 0)
            {
                render(model,base);
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
