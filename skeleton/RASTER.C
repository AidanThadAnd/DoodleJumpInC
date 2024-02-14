#include "raster.h"

void plot_bitmap_1(UINT16 *base, int x, int y, ...)
{
	/* [TO DO] delete this example function */
}

void plot_bitmap_2(UINT16 *base, int x, int y, ...)
{
	/* [TO DO] delete this example function */
}

void plotHorizontalLine(UINT8 *base, int y) {
	int row= 0;
	UINT8 *drawLine = base + (y*80);

	while(row++ < 80){
		*(drawLine++) = 0xFFFF;
	} 
}



void clearScreen(UINT8 *base) {
	int row;

	UINT8 *newBase = base;

	for (row = 0; row < SCREEN_HEIGHT; row++) {
		clearHorizontalLine8(newBase, 0, 0, SCREEN_WIDTH);
		
		newBase += 80;
	}
}

void clearHorizontalLine8(UINT8* base, int x, int y, int length) {
	int row;
	int counter = length >> 3;

	UINT8 *clearLine = base + (y * 80) + (x >> 3);

	for (row = 0; row < counter; row++){

		*(clearLine++) &= 0x00;
	}
}
