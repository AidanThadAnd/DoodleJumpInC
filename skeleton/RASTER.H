#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void plot_pixel(UINT16 *base, int x, int y);

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
void clear_screen(UINT8 *base, int SCREEN_HEIGHT, int SCREEN_WIDTH);

#endif
