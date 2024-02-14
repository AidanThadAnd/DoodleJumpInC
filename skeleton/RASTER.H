#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plotHorizontalLine(UINT8 *base, int y);
void clearHorizontalLine8(UINT8* base, int x, int y, int length);
void clearScreen(UINT8 *base, const unsigned int SCREEN_HEIGHT, const unsigned int SCREEN_WIDTH);


#endif
