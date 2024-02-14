#include "raster.h"


void plot_pixel(char *base, int x, int y, const unsigned int SCREEN_HEIGHT, const unsigned int SCREEN_WIDTH)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) 
		*(base + y * 80 + (x >>3)) |= 1 << (7 - (x & 7));
}

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;
    
    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];     /* danger (no bounds checking!) */
        loc += 40;
    }
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;
    
    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];     /* danger (no bounds checking!) */
        loc += 40;
    }
}
