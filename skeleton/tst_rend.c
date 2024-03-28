#include <osbind.h>
#include "RENDERER.H"
#include "MODEL.H"
#include "system.h"
#include "stdio.h"

int main()
{
    int i;
    int j;
    int loop;
    UINT32 *base = Physbase();

    Model *model = initialize_model();
    Platform *platform = model->platforms;
    Platform *save = platform;

    loop = 0;
    clear_screen((UINT8*)base);

    render(model, base);

    /*
    Changing models 
    */

    move_monster(&(model->monster), 8, 0);

   for(i=0; i <= 400; i++)
   {
    move_doodle(&(model->doodle), 8, 0,0);
    move_platform_absolute(model->platforms, i, i, 5);
    render(model, base);
    Vsync();
   }

   for(j=0; j <=400; j++)
   {
        move_monster(&(model->monster), 8, -1);
        render(model,base);
        Vsync();
   }
    
    return 0;
}
