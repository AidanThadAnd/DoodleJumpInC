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

   for(i=0; i <= 400; i++)
   {
    move_doodle(&(model->doodle), 8, 0);
    move_monster(&(model->monster), 8, 0);
    move_platform_absolute(model->platforms, 300, 200, 1);
    render(model, base);
   }
   
    return 0;
}
