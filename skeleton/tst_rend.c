#include <osbind.h>
#include "RENDERER.H"
#include "MODEL.H"
#include "system.h"
#include "stdio.h"

int main()
{
    int i;
    int j;
    UINT32 *base = Physbase();

    Model *model = initialize_model();
    Platform *platform = model->platforms;

    clear_screen((UINT8*)base);

    render(model, base);

    /*
    Changing models 
    */

   for(i=0; i <= 400; i++)
   {
    move_doodle(&(model->doodle), 8, 0);
    move_monster(&(model->monster), 8, 0);
    model->doodle.facing = 0;
    for(j=0; j < MAX_PLATFORMS; j++)
    {
        move_platform(platform, 1,0);
        platform++;
    }
    platform = model->platforms;

    render(model, base);
    
   }
   
    return 0;
}
