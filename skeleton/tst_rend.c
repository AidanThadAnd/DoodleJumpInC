#include <osbind.h>
#include "RENDERER.H"
#include "MODEL.H"
#include "system.h"

int main()
{
    UINT32 *base = Physbase();

    Model *model = initialize_model();

    clear_screen((UINT8*)base);

    render(model, base);

    
    return 0;
}