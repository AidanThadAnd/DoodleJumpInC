#include <osbind.h>
#include "RENDERER.H"
#include "MODEL.H"
#include "system.h"

int main()
{
    UINT32 *base = Physbase();

    Model *model = initialize_model();

    clear_screen((UINT8*)base, SCREEN_HEIGHT, SCREEN_WIDTH);

    /*
    render(model, base);
    */
    
    return 0;
}