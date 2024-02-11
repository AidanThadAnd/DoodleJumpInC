#include <osbind.h>
#include "raster.h"

int main()
{
    UINT16 *base = Physbase();
    int x, y;
    
    /* Calculate the starting position to center the invader */
    int start_x = (SCREEN_WIDTH - sizeof(UINT16)) / 2;
    int start_y = (SCREEN_HEIGHT - INVADER_HEIGHT) / 2;

    /* Plot the new bitmap at the calculated position */
    plot_bitmap_16(base, start_x, start_y, new_bitmap, INVADER_WIDTH);
    
    return 0;
}
