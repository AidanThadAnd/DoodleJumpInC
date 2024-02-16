#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "font.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define CHARACTER_HEIGHT 64

void fill_screen_test_8(UINT16 *base, const UINT8 *bitmap);
void fill_screen_test_16(UINT16 *base, const UINT16 *bitmap);

int main()
{
	UINT16 *base = Physbase();
	const UINT8* glyph_A = GLYPH_START('A');
	int x, y;
    
  	/* Calculate the starting position to center the invader */
 	int start_x = (SCREEN_WIDTH - sizeof(UINT16)) / 2;
  	int start_y = (SCREEN_HEIGHT - CHARACTER_HEIGHT) / 2;


	/*fill_screen_test_16(base, testBitmap);
	fill_screen_test_8(base, glyph_A);*/

	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH);
	plot_bitmap_64(base, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, doodle_character, 64);
	/*Plots an 'A' in the centre of the screen*/
	/*plot_bitmap_8(base, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, glyph_A, FONT_HEIGHT);*/

	return 0;
}

void fill_screen_test_8(UINT16 *base, const UINT8 *bitmap)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=8)
		for(j = 0; j < SCREEN_HEIGHT; j+=8)
			plot_bitmap_8(base, i, j, bitmap, 8);

	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH);

}

/*Test for plot_bitmap_16 and clear_screen*/
void fill_screen_test_16(UINT16 *base, const UINT16 *bitmap)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=16)
		for(j = 0; j < SCREEN_HEIGHT; j+=16)
			plot_bitmap_16(base, i, j, bitmap, TEST_BITMAP_HEIGHT);


	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH);
}
