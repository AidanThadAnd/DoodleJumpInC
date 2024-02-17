#include <osbind.h>
#include "RENDERER.H"
#include "MODEL.H"
#include "system.h"

int main()
{
    UINT32 *base = Physbase();

    Model *model;

    clear_screen((UINT8*)base, SCREEN_HEIGHT, SCREEN_WIDTH);
    initialize_model(model);


    render(model, base);

    return 0;
}