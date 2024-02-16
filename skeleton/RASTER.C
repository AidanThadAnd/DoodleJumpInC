#include "raster.h"

void plot_pixel(char *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) 
		*(base + y * 80 + (x >>3)) |= 1 << (7 - (x & 7));
}

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;
    
    if(x < 0 || y < 0 || y + height > 400 || x/32 >=640)
    {
        printf("ERROR: Bitmap out of bounds\n");
    }       
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

    if(x < 0 || y < 0 || y + height > 400 || x/32 >=640)
    {
        printf("ERROR: Bitmap out of bounds\n");
    }    

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];     /* danger (no bounds checking!) */
        loc += 40;
    }
}

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 20) + (x >> 5);
    int row;
    if(x < 0 || y < 0 || y + height > 400 || x/32 >=640)
    {
     	printf("ERROR: Bitmap out of bounds\n");
    }    

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];     
        loc += 20;
    }
}

void plot_bitmap_64(UINT32 *base, int x, int y, UINT32 *bitmap, int height)
{
	int rows;
	int cols;

	if(x < 0 || y < 0 || y + height > 400 || x/32 >=640)
	{
        	printf("ERROR: Bitmap out of bounds\n");
	}    

	UINT32 *loc = base + (y * 20) + (x>>5);
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

	UINT8 *newBase = base;

	for (row = 0; row < SCREEN_HEIGHT; row++) {
		clear_horizontal_line_8(newBase, 0, 0, SCREEN_WIDTH);
		
		newBase += 80;
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
