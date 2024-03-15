#include "model.h"
#include "events.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

UINT32 get_time(); 
void delay(int milliseconds); 
void erase_doodle(const Doodle doodle, UINT32 *base); 

int main() {
    Model *model = initialize_model(); 

    UINT32 *base = Physbase();   

    char pressedKey = 0; 

    render(model, base);  /* Render the initial state of the model */

    while (1) { /* Main game loop */
        if (Cconis()) { /* Check if keyboard input is available */
            char key = (char)Cnecin(); /* Read keyboard input */
            if (key == 'a' || key == 'd') { 
                pressedKey = key;
            }
        } else {
            pressedKey = 0; /* Reset pressedKey if no key is pressed */
        }

        switch (pressedKey) { /* Handle the pressed key */
            case 'a':
                erase_doodle(model->doodle, base);  
                model->doodle.x -= 1; /* Move the doodle left */
                render_doodle(&(model->doodle), base); 
                break;
            case 'd':
                erase_doodle(model->doodle, base);  
                model->doodle.x += 1; /* Move the doodle right */
                render_doodle(&(model->doodle), base); 
                break;
            default:
                break;
        }
    }

    return 0;
}

void erase_doodle(const Doodle doodle, UINT32 *base) { 
    plot_bitmap_32(base, doodle.x, doodle.y, clear_bitmap, DOODLE_HEIGHT); 
}

UINT32 get_time() { 
    UINT32 time; 
    long old_ssp = Super(0); 
    time = *((UINT32 *)0x462); 
    Super(old_ssp); 
    return time; 
}
