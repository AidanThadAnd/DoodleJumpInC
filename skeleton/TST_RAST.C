/*
Author: Aidan & Jacky
Date: Jan 29 2024

Purpose: 
				- Displays various bitmaps to the ATARI 68000 screen for testing purposes

Function Details: 
				- Each function will clear the screen after plotting the given bitmap
				- The function "test_plot_bitmap_8" and "test_plot_bitmap_16" will plot the given bit map equally across the entire screen
				- The function "test_plot_bitmap_32" will plot the bitmap horizontally 40 times across the screen, each plot will be cleared

Warning:		- Bitmaps must come with the height defined
				- No error checking on bitmaps, if incorrect height or incorrect size is given the tests will come out incorrect
				- Knowledge of RASTER.H function definitions is required as each function takes a specifically sized pointer, 
				  incorrect use of pointers will result in pointer conversion warnings during compile time

Note:			- clear_screen is implicitly tested as each function relies on the screen being cleared by this function
				- clear_horizontal_line is implicitly tested as clear_screen relies on clear_horizontal_line to clear each line of the screen
*/

#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "font.h"
#include "bitmap.h"
#include "system.h"

void test_plot_horizontal_line(UINT8 *base);
void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height);
void test_plot_bitmap_16(UINT16 *base, const UINT16 *bitmap, const unsigned int height);
void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height);
int log10_custom(UINT32 x);
int countDigits(UINT32 number);
int abs(int *num);

int main()
{
	int i;
    UINT8 *base  = Physbase();
	const UINT8* glyph_num = GLYPH_START(temp%10+ '0');
	const UINT8* glyph_space = GLYPH_START(' ');



    clear_screen((UINT8*)base);
/*
	test_plot_horizontal_line((UINT8*)base);
	test_plot_bitmap_32(base, monster_bitmap, MONSTER_HEIGHT);
    test_plot_bitmap_32(base, broken_platform_bitmap, PLATFORM_HEIGHT);
    test_plot_bitmap_32(base, doodle_bitmap_left, DOODLE_HEIGHT);
    test_plot_bitmap_32(base, platform_bitmap, PLATFORM_HEIGHT);
	plot_horizontal_line(base, SCREEN_HEIGHT/2 + 1);
    test_plot_bitmap_32(base, doodle_bitmap_right, DOODLE_HEIGHT);
	plot_bitmap_32(base, 192, 55, platform_bitmap, PLATFORM_HEIGHT);
	plot_bitmap_32(base, 192, 178, doodle_bitmap_right, DOODLE_HEIGHT);
    test_plot_bitmap_8((UINT16*)base, glyph_num, FONT_HEIGHT);
	test_plot_bitmap_8((UINT16*)base, glyph_space, FONT_HEIGHT);
*/

		



	
	return 0;
}


/*
Function Name: test_plot_horizontal_line

Purpose:
		- Uses the plot_horizontal_line function from RASTER.C to fill the screen with horizontal lines,
		  after all lines are plotted the screen is cleared

Input:
		- A pointer to frame buffer called "base"

Output:
		- Plots 50 lines to the screen, the screen is then cleared
*/
void test_plot_horizontal_line(UINT8 *base)
{
	int i;
	int j;

	for(j = 0; j < SCREEN_HEIGHT; j+=8)
		plot_horizontal_line(base, j);

	clear_screen(base);

}

/*
Function Name: test_plot_bitmap_8

Purpose:
		- Uses the plot_bitmap_8 function from RASTER.C to fill the screen with the supplied bitmap,
		  after each element is plotted the screen is cleared

Input:
		- A pointer to frame buffer called "base"
		- A pointer to a bitmap called "bitmap"
		- A integer which represents the height of the bitmap

Output:
		- Displays the given bitmap in a grid formation to the screen
		- Screen is cleared after function is complete
*/

void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=8)
		for(j = 0; j < SCREEN_HEIGHT; j+=8)
			plot_bitmap_8(base, i, j, bitmap, height);

	clear_screen((UINT8*)base);

}

/*
Function Name: test_plot_bitmap_16

Purpose:
		- Uses the plot_bitmap_16 function from RASTER.C to fill the screen with the supplied bitmap,
		  after each element is plotted the screen is cleared

Input:
		- A pointer to frame buffer called "base"
		- A pointer to a bitmap called "bitmap"
		- A integer which represents the height of the bitmap

Output:
		- Displays the given bitmap in a grid formation to the screen
		- Screen is cleared after function is complete
*/
void test_plot_bitmap_16(UINT16 *base, const UINT16 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=16)
		for(j = 0; j < SCREEN_HEIGHT; j+=16)
			plot_bitmap_16(base, i, j, bitmap, height);


	clear_screen((UINT8*)base);
}

/*
Function Name: test_plot_bitmap_32

Purpose:
		- Uses the plot_bitmap_32 function from RASTER.C to fill the screen with the supplied bitmap,
		  after each element is plotted the screen is cleared

Input:
		- A pointer to frame buffer called "base"
		- A pointer to a bitmap called "bitmap"
		- A integer which represents the height of the bitmap

Output:
		- Displays the given bitmap in a grid formation to the screen
		- Screen is cleared after function is complete
*/
void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height)
{	
    int i=0;
	int j=0;

	for(i = 0; i < SCREEN_WIDTH; i+=64)
		for(j = 0; j < SCREEN_HEIGHT+64; j+=64)
			plot_bitmap_32(base, i, j, bitmap, height);
    
	/*
	clear_screen((UINT8*)base);
	*/
}
