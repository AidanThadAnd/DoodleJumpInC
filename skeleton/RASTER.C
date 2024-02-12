#include "raster.h"

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
	int i=0;
	
	while(i<height)
	{
		*(base + i*40) = bitmap[i];
		i++;
	}
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
	int i=0;
	
	while(i<height)
	{
		*(base + i*40) = bitmap[i];
		i++;
	}
}