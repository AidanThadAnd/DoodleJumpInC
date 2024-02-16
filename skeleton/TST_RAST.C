#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "font.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define CHARACTER_HEIGHT 64

void fill_screen_test_8(UINT16 *base, const UINT8 *bitmap);
void fill_screen_test_16(UINT16 *base, const UINT16 *bitmap);

const UINT32 doodle_character[] =
	{
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00001f80,
        ~0x00000000, ~0x00007ff0, ~0x00000000,
        ~0x0001fffc, ~0x00000000, ~0x0007fffe,
        ~0x00000000, ~0x000fffff, ~0x80000000,
        ~0x001fffff, ~0xc0000000, ~0x003fffff,
        ~0xc0000000, ~0x007fffff, ~0xe0000000,
        ~0x007fffff, ~0xf0000000, ~0x00ffffff,
        ~0xf0000000, ~0x00ffffff, ~0xf8000000,
        ~0x01ffffff, ~0xf8000000, ~0x01ffffff,
        ~0xfc000000, ~0x01fffff9, ~0xfc000000,
        ~0x03fffff9, ~0xce000000, ~0x03fffff9,
        ~0xce000000, ~0x03fffff9, ~0xcf000000,
        ~0x03ffffff, ~0xff800000, ~0x03ffffff,
        ~0xffe00100, ~0x03ffffff, ~0xfffe1380,
        ~0x03ffffff, ~0xffffff80, ~0x03ffffff,
        ~0xffffffc0, ~0x03ffffff, ~0xffe0ffc0,
        ~0x03ffffff, ~0xff001fc0, ~0x03ffffff,
        ~0xfe000080, ~0x03ffffff, ~0xfc000000,
        ~0x03ffffff, ~0xf8000000, ~0x01ffffff,
        ~0xf8000000, ~0x000003ff, ~0xf8000000,
        ~0x00000000, ~0x00000000, ~0x01fff800,
        ~0x00000000, ~0x01ffffff, ~0xf8000000,
        ~0x01ffffff, ~0xf8000000, ~0x01ffffff,
        ~0xf8000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x01ffffff,
        ~0xf8000000, ~0x00ffffff, ~0xf8000000,
        ~0x00ffffff, ~0xf8000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00ffffff, ~0xe0000000, ~0x000c000c,
        ~0x00000000, ~0x000c000c, ~0x00000000,
        ~0x000c000c, ~0x00000000, ~0x000c000c,
        ~0x00000000, ~0x000ff80f, ~0xf8000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
        ~0x00000000, ~0x00000000, ~0x00000000,
	};

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
