/*
Author: Aidan & Jacky
Date: Jan 29 2024

Program purpose: Displays various bitmaps to the ATARI 68000 screen for testing purposes

Details:        - Each function will clear the screen after plotting the given bitmap
				- 

Warning:		- Bitmaps must come with the height defined
				- No error checking on bitmaps, if incorrect height or incorrect size is given the tests will come out incorrect
				- Knowledge of RASTER.H function definitions is required as each function takes a specifically sized pointer, 
				  incorrect use of pointers will result in pointer conversion warnings during compile time
*/

#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "font.h"
#include "bitmap.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640

void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height);
void test_plot_bitmap_16(UINT16 *base, const UINT16 *bitmap, const unsigned int height);
void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height);

int main()
{
	
    UINT32 *base  = Physbase(); /* Multiple pointers are created for Physbase to prevent pointer conversion warnings during compile time */
        
	const UINT8* glyph_A = GLYPH_START('A');

    clear_screen((UINT8*)base, SCREEN_HEIGHT, SCREEN_WIDTH);

    test_plot_bitmap_8((UINT16*)base, glyph_A, FONT_HEIGHT);
	test_plot_bitmap_32(base, monster_bitmap, MONSTER_BITMAP_HEIGHT);
    test_plot_bitmap_32(base, platform_bitmap, PLATFORM_BITMAP_HEIGHT);
    test_plot_bitmap_32(base, broken_platform_bitmap, PLATFORM_BITMAP_HEIGHT);
    test_plot_bitmap_32(base, doodle_bitmap, DOODLE_BITMAP_HEIGHT);

	return 0;
}


void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=8)
		for(j = 0; j < SCREEN_HEIGHT; j+=8)
			plot_bitmap_8(base, i, j, bitmap, height);

	clear_screen((UINT8*)base, SCREEN_HEIGHT, SCREEN_WIDTH);

}

void test_plot_bitmap_16(UINT16 *base, const UINT16 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=16)
		for(j = 0; j < SCREEN_HEIGHT; j+=16)
			plot_bitmap_16(base, i, j, bitmap, height);


	clear_screen((UINT8*)base, SCREEN_HEIGHT, SCREEN_WIDTH);
}

void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height)
{
    int i;
	for(i = 0; i < SCREEN_WIDTH; i+=16)
        {
		plot_bitmap_32(base, i, SCREEN_HEIGHT/2, bitmap, height);
        clear_screen((UINT8*)base, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
}
