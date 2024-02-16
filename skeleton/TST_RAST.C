#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "font.h"
#include "bitmap.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define CHARACTER_HEIGHT 64

void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height);
void test_plot_bitmap16(UINT16 *base, const UINT16 *bitmap, const unsigned int height);
void test_plot_bitmap_64(UINT32 *base, const UINT32 *bitmap, const unsigned int height);

int main()
{
	UINT16 *base = Physbase();
	const UINT8* glyph_A = GLYPH_START('A');
	int x, y;
    
  	/* Calculate the starting position to center the invader */
 	int start_x = (SCREEN_WIDTH - sizeof(UINT16)) / 2;
  	int start_y = (SCREEN_HEIGHT - CHARACTER_HEIGHT) / 2;

        clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH);

        test_plot_bitmap_8(base, glyph_A, 8);
	test_plot_bitmap_32(base, monster_bitmap, 64);
        test_plot_bitmap_32(base, platform_bitmap, 24);
        test_plot_bitmap_32(base, broken_platform_bitmap, 24);
        test_plot_bitmap_32(base, doodle_bitmap, 64);

	return 0;
}



void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=8)
		for(j = 0; j < SCREEN_HEIGHT; j+=8)
			plot_bitmap_8(base, i, j, bitmap, height);

	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH);

}

/*Test for plot_bitmap_16 and clear_screen*/
void test_plot_bitmap16(UINT16 *base, const UINT16 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=16)
		for(j = 0; j < SCREEN_HEIGHT; j+=16)
			plot_bitmap_16(base, i, j, bitmap, height);


	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH);
}

void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height)
{
       	int i;
	for(i = 0; i < SCREEN_WIDTH; i+=16)
        {
		plot_bitmap_32(base, i, SCREEN_HEIGHT/2, bitmap, height);
                clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH); 
        }

	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH); 
}

void test_plot_bitmap_64(UINT32 *base, const UINT32 *bitmap, const unsigned int height)
{
       	int i;
	for(i = 0; i < SCREEN_WIDTH; i+=32)
        {
		plot_bitmap_64(base, i, SCREEN_HEIGHT/2, bitmap, height);
                clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH); 
        }

	clear_screen(base, SCREEN_HEIGHT, SCREEN_WIDTH); 
}