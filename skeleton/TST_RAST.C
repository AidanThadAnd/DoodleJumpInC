#include <osbind.h>
#include "raster.h"
#include "font.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define TEST_BITMAP_HEIGHT 13

int main()
{
	UINT16 *base = Physbase();
	const UINT8* glyph_A = GLYPH_START('A');


	int testBitmap[TEST_BITMAP_HEIGHT] =
	{
		0x0000,
		0x0810,
		0x0810,
		0x0420,
		0x0240,
		0x1FF8,
		0x2004,
		0x4662,
		0x4002,
		0x43C2,
		0x2424,
		0x1008,
		0x0FF0,
	};

  int x, y;
    
  /* Calculate the starting position to center the invader */
  int start_x = (SCREEN_WIDTH - sizeof(UINT16)) / 2;
  int start_y = (SCREEN_HEIGHT - INVADER_HEIGHT) / 2;

	/* Plots a little invader in the top right of the screen*/
	plot_bitmap_16(base, SCREEN_WIDTH/4, SCREEN_HEIGHT/4, testBitmap, TEST_BITMAP_HEIGHT);

	/*Plots an 'A' in the centre of the screen*/
	plot_bitmap_8(base, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, glyph_A, FONT_HEIGHT);

	return 0;
}
