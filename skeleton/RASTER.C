#include "raster.h"

void plot_bitmap_1(UINT16 *base, int x, int y, ...)
{
	/* [TO DO] delete this example function */
}

void plot_bitmap_2(UINT16 *base, int x, int y, ...)
{
	/* [TO DO] delete this example function */
}

void plotHorizontalLine(UINT8 *base, int x, int y, int length) {
	int i= 0;
	int j = 0;
	int counter = length;
	UINT8 *drawLine = base + (y*80);
	while(i++ < 80){
		*(drawLine++) = 0xffff;
	} 
}

void clearScreen(UINT8 *base) {	
	int i = 0;
	UINT8 *newBase = base;

	for (i = 0; i < SCREEN_HEIGHT; i++) {
		clearHorizontalLine8(newBase, 0, 0, SCREEN_WIDTH);
		newBase += 80;
	}
}

void clearHorizontalLine8(UINT8* base, int x, int y, int length) {
	int i;
	int counter = length >> 3;
	UINT8 *clearLine = base + (y * 80) + (x >> 3);

	for (i = 0; i < counter; i++){
		*(clearLine++) &= 0x00;
	}
}
