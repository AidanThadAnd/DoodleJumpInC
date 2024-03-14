#include <osbind.h>
#include "RENDERER.H"
#include "MODEL.H"
#include "system.h"

int main()
{
    UINT32 i;
    UINT32 *base = Physbase();

    Model *model = initialize_model();


    clear_screen((UINT8*)base);

    render(model, base);

    /*
    Changing models 
    */
   for(i=0; i<100000; i++){
    model->doodle.delta_x += 5;
    model->doodle.delta_y += 5;
    move_doodle(&(model->doodle));

    render(model, base);
   }
   
    return 0;
}
