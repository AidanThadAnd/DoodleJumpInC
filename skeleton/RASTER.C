#include "raster.h"


void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;
       
	if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}
	
    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];
        loc += 40;
    }
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;    

	if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];     
        loc += 40;
    }
}


void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height)
{
	int rows;
	int cols;

	UINT32 *loc = base + (y * 20) + (x>>5);

	if(y >= SCREEN_HEIGHT)
		return;

	if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}

	for (rows = 0; rows < height; rows++) {
		for(cols = 0; cols < 2; cols++) {
			*loc |= *(bitmap)++;
			*loc ^= 0xFFFFFFFF;
			loc++;
		}
		loc += 18;
	}
}


void plot_horizontal_line(UINT8 *base, int y) {
	int row= 0;

	UINT8 *drawLine = base + (y*80);

	while(row++ < 80){
		*(drawLine++) = 0xFFFF;
	} 
}

void clear_screen(UINT8 *base)
{
	int row;

	for (row = 0; row < SCREEN_HEIGHT; row++) {
		clear_horizontal_line_8(base, 0, 0, SCREEN_WIDTH);
		base += 80;
	}
}

void clear_horizontal_line_8(UINT8* base, int x, int y, int length) {
	int row;
	int counter = length >> 3;

	UINT8 *clearLine = base + (y * 80) + (x >> 3);

	for (row = 0; row < counter; row++){

		*(clearLine++) &= 0x00;
	}
}
