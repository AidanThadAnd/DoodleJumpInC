/*
Author: Aidan & Jacky
Date: Jan 29 2024

Purpose: 
				- Provides various routines to: 
                    - Plot bitmaps of size 8, 16, 32
                    - Plot horizontal lines
                    - Clear horizontal lines
                    - Clear the screen

Functions:

    Function Name: plot_bitmap_8

        Purpose:
            - Plot an 8-bit per pixel bitmap onto the frame buffer.

        Input:
            - base: Pointer to the start of the frame buffer.
            - x: X-coordinate to start plotting.
            - y: Y-coordinate to start plotting.
            - bitmap: Pointer to the bitmap data.
            - height: Height of the bitmap.

        Output:
            - The bitmap is drawn to the screen


    Function Name: plot_bitmap_16

        Purpose:
            - Plot a 16-bit per pixel bitmap onto the frame buffer.

        Input:
            - base: Pointer to the start of the frame buffer.
            - x: X-coordinate to start plotting.
            - y: Y-coordinate to start plotting.
            - bitmap: Pointer to the bitmap data.
            - height: Height of the bitmap.

        Output:
            - The bitmap is drawn to the screen


    Function Name: plot_bitmap_32
        
        Purpose:
             - Plot a 32-bit per pixel bitmap onto the frame buffer.
        
        Input:
             - base: Pointer to the start of the frame buffer.
             - x: X-coordinate to start plotting.
             - y: Y-coordinate to start plotting.
             - bitmap: Pointer to the bitmap data.
             - height: Height of the bitmap.
        Output:
            - The bitmap is drawn to the screen
	
    Function Name: plot_bitmap_screen
	Purpose:
	     - Plot the main menu onto the frame buffer
	Input:
	     - Base: Pointer to the start of the frame buffer
	     - Bitmap: Pointer to the bitmap data
	Output
	     - The bitmap is drawn to the screen

    Function Name: plot_horizontal_line

        Purpose:
             - Plot a horizontal line onto the frame buffer.

        Input:
             - base: Pointer to the start of the frame buffer.
             - y: Y-coordinate of the horizontal line.
        Output:
            - The bitmap is drawn to the screen


    Function Name: clear_screen

        Purpose:
             - Clear the entire screen.

        Input:
             - base: Pointer to the start of the frame buffer.
             - SCREEN_HEIGHT: Height of the screen.
             - SCREEN_WIDTH: Width of the screen.
        Output:
            - An empty frame buffer, creating an empty screen


    Function Name: clear_horizontal_line_8

        Purpose:
             - Clear a horizontal line on the screen.

        Input:
             - base: Pointer to the start of the frame buffer.
             - x: X-coordinate to start clearing.
             - y: Y-coordinate to start clearing.
             - length: Length of the line to clear.
        Output:
            - All memory locations in a row of the frame buffer are set to 0, creating a clear line on the screen



Warning:		- Bitmaps must come with the height defined
				- No error checking on bitmaps, if incorrect height or incorrect size is given the bitmaps will plot incorrectly
*/

#ifndef RASTER_H
#define RASTER_H
#include "types.h"
#include "system.h"

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_screen(UINT8 *base);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
void print_char(UINT8 *base, char character, int x, int y);
void clear_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_screen(UINT32 *base, UINT32* bitmap);

#endif
